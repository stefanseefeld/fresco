/*+P
 * This file is part of OffiX,
 * a C++ API for the X Window System and Unix
 * Copyright (C) 1995-98  Stefan Seefeld
 *
 * This code was originally written by
 * Copyright (C) 1997  Sean Vyain
 * svyain@mail.tds.net
 * smvyain@softart.com
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 675 Mass Ave, Cambridge,
 * MA 02139, USA.
 -P*/
static char *rcsid = "$Id$";
#include <ctype>
#include <cstdlib>
#include "Prague/Sys/regex.hh"
#include "Prague/Network/url.hh"

/*Method{void url::parse(const string &s)}
 *
 * @Description{Parse a url given as a text string into its component parts, as per the algorithm given in RFC1808.  This routine successfully parses all the test cases mentioned in RFC1808.  This algorithm works for partially and fully qualified URLs.}
 */
void url::parse(const string &s)
{
  string tmp(s);
  // Search for a fragment identifier.
  int idx1 = tmp.find('#');
  if (idx1 >= 0)
    {
      fragment = tmp.substr(tmp.length() - idx1 - 1);
      tmp.remove(idx1, tmp.length());
      //printf( "url::parse() -- fragment = '%s', url = '%s'\n", (const char*)_fragment, (const char*)tmp );
    }
  // Search for a scheme (method).
  regex reg("^[a-zA-Z0-9\\+\\.\\-]+:");
  idx1 = reg.search(tmp);
  if (idx1 >= 0)
    {
      int idx2 = tmp.find(':');
      _method = tmp.substr(0, idx2);
      tmp.remove(0, idx2 + 1);
      //		printf( "url::parse() -- method = '%s', url = '%s'\n", (const char*)_method, (const char*)tmp )
    }
  // Search for a network location/login.
  if (tmp[0] == '/' && tmp[1] == '/')
    {
      tmp.remove(0, 2);
      idx1 = tmp.find('/');
      string netloc;
      netloc = tmp.left(idx1);
      tmp.remove(0, idx1);
      //printf( "url::parse() -- netloc = '%s', url = '%s'\n", (const char*)netloc, (const char*)tmp );
      if ((idx1 = netloc.find('@')) >= 0)
	{
	  string login = netloc.left(idx1);
	  netloc.remove(0, idx1 + 1);
	  //printf( "url::parse() -- login = '%s', netloc = '%s'\n", (const char*)login, (const char*)netloc );
	  if ((idx1 = login.find(':')) >= 0)
	    {
	      user = login.left(idx1);
	      password = login.right(login.length() - idx1 - 1);
	    }
	  else user = login;
	  //printf( "url::parse() -- user = '%s', password = '%s'\n", (const char*)_user, (const char*)_password );
	}
      if ((idx1 = netloc.find(':')) >= 0)
	{
	  string port = netloc.right(netloc.length() - idx1 - 1);
	  netloc.remove(idx1, netloc.length());
	  port = atoi((const char *)port);
	  //printf( "url::parse() -- port = %d, netloc = '%s'\n", _port, (const char*)netloc );
	}	
      hostname = netloc;
      //printf( "url::parse() -- hostname = '%s'\n", (const char*)_hostname );
    }
  // Search for a query.
  if ((idx1 = tmp.find('?')) >= 0)
    {
      _query = tmp.right(tmp.length() - idx1 - 1);
      tmp.remove(idx1, tmp.length());
      //printf( "url::parse() -- query = '%s', url = '%s'\n", (const char*)_query, (const char*)tmp );
    }
  // Search for parameters.
  if ((idx1 = tmp.find(';')) >= 0)
    {
      _parameters = tmp.right(tmp.length() - idx1 - 1);
      tmp.remove(idx1, tmp.length());
      //printf( "url::parse() -- parameters = '%s', url = '%s'\n", (const char*)_parameters, (const char*)tmp );
    }
  // The rest is the path.
  path = tmp;
  //printf( "url::parse() -- path = '%s'\n", (const char*)_path );
  if (!method.length()) method = 0;
  if (!user.length()) user = 0;
  if (!password.length()) password = 0;
  if (!hostname.length()) hostname = 0;
  if (!path.length()) path = 0;
  if (!fragment.length()) fragment = 0;
  if (!query.length()) query = 0;
  if (!parameters.length()) parameters = 0;
}

/*
 * @Method{url::url(const string &s)}
 *
 * @Description{Parse a fully qualified URL}
 */
url::url(const string &s) : port(-1)
{
  parse(s);
}

/*
 * @Method{url::url(const url &absurl, const string &relurl)}
 *
 * @Description{Parse a partially qualified URL, and then resolve it with the given absolute URL}
 */
url::url(const url &absurl, const string &relurl) : port(-1)
{
  parse(relurl);
  if (!absurl) return;
  if (!url())
    {
      *this = *absurl;
      return;
    }
  if (method()) return;
  method = absurl->method();
  if (!hostname())
    {
      _user     = absurl->user();
      _password = absurl->password();
      _hostname = absurl->hostname();
      _port     = absurl->port();
      if (!path() || _path[0] != '/')
	{
	  if (!path())
	    {
	      _path = absurl->path();
	      if (!parameters())
		{
		  _parameters = absurl->parameters();
		  if (!query()) _query = absUrl->query();
		}
	    }
	  else
	    {
				// Step 6...
	      string newPath;
	      int idx1 = 0;
	      newPath = absurl->path();
	      if ((idx1 = newPath.findRev('/')) >= 0) newPath.truncate(idx1 + 1);
	      else newPath.truncate( 0 );
	      newPath += path();
	      idx1 = 0;
	      if (newPath[0] == '/') idx1++;
	      while (idx1 < int(newPath.length()))
		{
		  if (newPath.mid(idx1, 2) == "./")
		    {
		      newPath.remove(idx1, 2);
		      //printf( "Url::Url() -- (1)path = '%s'\n", (const char*)newPath );
		    }
		  else
		    {
		      idx1 = newPath.find('/', idx1 + 1);
		      if (idx1 < 0) idx1 = newPath.length();
		      else idx1++;
		    }
		}
	      if (newPath.right(2) == "/.")
		{
		  newPath.truncate(newPath.length() - 1);
		  //printf( "Url::Url() -- (2)path = '%s'\n", (const char*)newPath );
		}		
	      bool found = true;
	      while (found)
		{
		  found = false;
		  idx1 = 0;
		  if (newPath.left(1) == '/') idx1++;
		  while (!found && (idx1 < int(newPath.length())))
		    {
		      int idx2 = newPath.find('/', idx1 + 1);
		      if (idx2 > idx1 && newPath.mid(idx1, 3) != "../" && newPath.mid(idx2, 4) == "/../")
			{
			  found = true;
			  newPath.remove(idx1, idx2 - idx1 + 4);
			  //printf( "Url::Url() -- (3)path = '%s'\n", (const char*)newPath );
			}
		      else
			{
			  if (idx2 < 0) idx1 = newPath.length();
			  else idx1 = idx2 + 1;
			}
		    }
		}
	      if (newPath.right(3) == "/..")
		{
		  idx1 = newPath.findRev('/', newPath.length() - 4) + 1;
		  if (newPath.mid(idx1, 3) != "../")
		    {
		      newPath.truncate(idx1);
		      //printf( "Url::Url() -- (4)path = '%s'\n", (const char*)newPath );
		    }
		}
	      _path = newPath;
	    }
	}
    }
}

/*
 * @Method{}
 *
 * @Description{Return the fully qualified URL as a string}
 */
url::operator const string &() const
{
  string tmp;
  if (method())
    {
      tmp += method();
      tmp += ":";
    }
  if (hostname())
    {
      tmp += "//";
      if (user())
	{
	  tmp += user();
	  if (password())
	    {
	      tmp += ":";
	      tmp += password();
	    }
	  tmp += "@";
	}
      tmp += hostname();
      if (port() >= 0)
	{
	  tmp += ":";
	  tmp += string().setNum(port());
	}
      if (path() && path()[0] != '/')
	{
	  //printf( "Url::url() -- path() = '%s'\n", path() );
	  tmp += "/";
	}
    }
  tmp += path();
  if (parameters())
    {
      tmp += ";";
      tmp += parameters();
    }
  if (query())
    {
      tmp += "?";
      tmp += query();
    }
  if (fragment())
    {
      tmp += "#";
      tmp += fragment();
    }
  return tmp;
}

void url::encode(const string &s)
{
  unsigned int  i;
  unsigned char c;
  string escaped;
  for (i = 0; i < s.length(); i++)
    {
      c = s[i];
      if (c < 32       ||
	  c > 126      ||
	  isspace(c)   ||
	  strchr("<>\"#%{}|\\^~[]'`;/?:@=&", c))
	{
	  // Escape the character.
	  escaped.sprintf("%%%02X", c);
	  s.replace( i, 1, escaped);
	  i += 2;
	}
    }
}
