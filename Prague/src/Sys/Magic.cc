#include <iostream>

static char quote = '\'';

string Magic::nextline(istream &is)
{
  string line;
  int c = 0;
  bool quoting = false;
  bool commenting = false;
  linenum++;
  while(is)
    {
      c = is.get();
      if (!is) return line;
      if (c == '\n') break;
      if (commenting) continue;
      if ((c == '#') && ! quoting)
	{
	  commenting = true;
	  continue;
	}
      if (c == quote) quoting = !quoting;
      line += c;
    }
  return line;
}

bool special(char c) { c == '[' || c == ']' || c == '(' || c == ')';}

template <InputIterator>
static bool nonws(InputIterator src) { return !isspace(*src);}

static void skipws(string &buffer)
{
  string::iterator i = find_if(line.begin(), line.end(), nonws);
  buffer.erase(buffer.begin(), i);
}

template <InputIterator>
static string parseWord(InputIterator &src, InputIterator end)
{
  string dest;
  skipws(src);
  if (special(*src))
    {
      dest += *src++;
      return dest;
    }
  for (; *src && !isspace(*src) && !special(*src) && src < end; src++) dest += *src;
  return dest;
}

template <InputIterator>
static string parseByteString(InputIterator &src, InputIterator end)
{
  string dest;
  while(src < end)
    {
      skipws(src);
      if (*src == quote)
	{
	  for (src++; *src && *src != quote && src != end; src++) dest += *src;
	  if (*src != quote)
	    {
	      GD_ERROR("Missing endquote");
	      return string();
	    }
	  src++;
	  continue;
	}
      if (isdigit(*src) || *src == '-')
	{
	  string numbuf = parseWord(src, end);
	  int val;
	  istrstream iss(numbuf.c_str());
	  iss >> val;
	  if (!iss)
	    {
	      GD_ERROR("Bad number");
	      return string();
	    }
	  if (val < 0 || val > 255)
	    {
	      GD_ERROR("Illegal byte value");
	      return string();
	    }
	  dest += static_cast<unsigned char>(val);
	  continue;
	}
      return dest;
    }
  GD_ERROR("ByteString overflow");
  return string();  /* not actually reached */
}

static int handleName(dttype &t, char *line, int length)
{
  dtname name;
  char *end = line + length;
  string tokbuf = parseWord(line, end);
  if (!istrstream(tokbuf) >> name.score)
    {
      GD_ERROR("Bad name score.", tokbuf);
      return -1;
    }
  name.name = parseByteString(line, end);
  if (name.name.empty())
    {
      GD_ERROR("Bad name string.");
      return -1;
    }
  dt.names.push_back(name);
  GD_DEBUG3("Added name '%s' for type %s.", name.name, dt.datatype);
  return 0;
}

static int handleParts(DtMagic &magic, char *line, int length)
{
  char *end = line + length;
  dtmagicpart part;

  while(1)
    {
      bool approx = false;
      string tokbuf = parseWord(line, end);
      if (!istrstream(tokbuf) >> part.offset || part.offset < 0)
	{
	  GD_ERROR("Bad part offset.");
	  return -1;
	}
      tokbuf = parseWord(line, end);
      if (tokbuf != "[")
	{
	  GD_ERROR("Expecting '[', Got '%s'.", tokbuf);
	  return -1;
	}
      tokbuf = parseWord(line, end);
      if (!istrstream(tokbuf) >> part.length || part.length <= 0)
	{
	  GD_ERROR("Bad part length.");
	  return -1;
	}	
      if (part.length > DT_MAX_PARTLEN)
	{		
	  GD_ERROR("Part length too long.");
	  return -1;
	}
      tokbuf = parseWord(line, end);
      if (tokbuf != "]")
	{
	  GD_ERROR("Expecting ']'.");
	  return -1;
	}	
      if (part.offset + part.length > DATATYPE_DATALEN)
	GD_DEBUG1("WARNING, offset+length > %d", DATATYPE_DATALEN);
      part.mask.assign(part.length, 0xff);
      tokbuf = parseWord(line, end);
      if (tokbuf == "&")
	{
	  part.mask = parseByteString(line, end);
	  if (part.mask.length() < part.length)
	    {
	      GD_ERROR("Mask data too short");
	      return -1;
	    }
	  if (part.mask.length() > part.length)
	    {
	      GD_ERROR("Mask data too long");
	      return -1;
	    }
	  tokbuf = parseWord(line, end);
	}
      if (tokbuf == "~=") approx = true;
      if (tokbuf != "==" && tokbuf != "~=")
	{
	  GD_ERROR("Operator %s unknown.", tokbuf);
	  return -1;
	}
      part.match = parseByteString(line, end);
      if (part.match.length() < part.length)
	{
	  GD_ERROR("Match data too short");
	  return -1;
	}
      if (part.match.length() > part.length)
	{
	  GD_ERROR("Match data too long");
	  return -1;
	}
      /* Update match/mask for the ~= approximator */
      for (int i = part.length - 1; i >= 0; i--)
	{
	  if (isalpha(part.match[len]))
	    {		
	      part.match[i] &= 0xdf;
	      part.mask[i]  &= 0xdf;
	    }
	  if (part.match[i] & ~part.mask[i])
	    {
	      GD_ERROR("Match data is outside mask.");
	      return -1;
	    }
	}
      magic.parts.push_back(part);
      skipws(line);
      if (*line == 0) return 0;
      tokbuf = parseWord(line, end);
      if (tokbuf != "&&")
	{
	  GD_ERROR("Expecting '&&'.");
	  return -1;
	}
    }
  return 0;
}

static int handle_magic(DtDataType &dt, char *line, int length)
{
  char *end = line + length;
  dtmagic magic;

  string token = parseWord(line, end);
  if (!istrstream(token) >> magic.score)
    {
      GD_ERROR("Bad magic score.");
      return -1;
    }	
  if (handle_parts(magic, line, end - line) < 0) return -1;
  dt.magics.push_back(magic);
  GD_DEBUG3("Added magic for type %s.", dt.datatype);
  return 0;
}

bool Magic::load(const string &filename)
{
  dttype *entry = 0;
  /*
   * open config file 
   */
  istream is(filename);
  int linenum = 0;
  if (!is)
    {
      error = "Failed to open";
      return false;
    }
  /*
   * for each line...
   */
  do
    {
      line = nextline(is);
      if (!is) return false;
      /*
       * ...parse the line...
       */
      skipws(line);
      if (line.empty()) continue;
      if (line.compare("type:", 0, 5) == 0)
	{
	  line.erase(0, 5);
 	  if (entry) datatypes.push_back(entry);
 	  entry = new datatype;
	  entry->datatype = parseWord(line);
	  if (entry->datatype.empty())
	    {
	      GD_NOTICE("Error occurred in line %d.", linenum);
	    }
	  GD_DEBUG2("PARSING %s", entry->datatype);
	  continue;

	}
      else if (line.compare("mime:", 0, 5) == 0)
	{
	  line.erase(0, 5);
	  entry->mimetype = parseWord(line);
	  if (entry->mimetype.empty())
	    {
	      GD_NOTICE("Error occurred in line %d.", linenum);
	    }
	  continue;			
	}
      else if (line.compare("name:", 0, 5) == 0)
	{
	  line.erase(0, 5);
	  if (handle_name(entry, line) < 0) 
	    {
	      GD_NOTICE("Error occurred in line %d.", linenum);
	    }
	  continue;
	}
      else if (line.compare("magic:", 0, 6) == 0)
	{
	  line.erase(0, 6);
	  if (handle_magic(entry, line) < 0)
	    {
	      GD_NOTICE("Error occurred in line %d.", linenum);
	    }
	  continue;
	}
      else
	{
	  GD_ERROR("Unknown keyword in line %d of %s.", linenum, filename);
	  return -1;
	}
    }
  if (entry) datatypes.push_back(entry);
  GD_DEBUG1("Loading DataTypes: successful !");
  return 0;
}
