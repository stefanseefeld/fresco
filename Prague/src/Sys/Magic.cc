/*+P
 * This file is part of OffiX,
 * a C++ API for the X Window System and Unix
 * Copyright (C) 1995-98  Stefan Seefeld
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

#include "OffiX/Base/Magic.h"
#include <fstream.h>

class Magic::Number : public Magic::Signum
{
public:
protected:
  long number;
};

class Magic::String : public Magic::Signum
{
public:
protected:
  const char *string;
};

class Magic::Expression : public Magic::Signum
{
public:
protected:
  Regex regex;
};

Magic::Magic(const char *filename)
{
  ifstream ifs (filename);
  int hsiz;
  
  if(!hdrbuf)
    {
      hdrbuf = (char *) malloc(maxhdr + 1);
      hdrbufsiz = maxhdr;
    }
  
  if(!ifs) return;
  while(ifs.getline(linebuf, MAXLIN))
    {
      char *cptr, *sptr;
      int cnt = 0;
      int l;
      l = strlen(linebuf);
      while(l < MAXLIN && linebuf[--l] == '\n' && linebuf[--l] == '\\')
	if(!ifs.getline(linebuf + l, MAXLIN - l)) break;
	else l = strlen(linebuf);
      
      cptr = linebuf;
      if(cptr[0] == '>')	/* Sub-type */
	{
	  cptr++;
	  mtypes[top].subtypes++;
	}
      else if(cptr[0] == '#' || cptr[0] == '\n' || cptr[0] == '\r') continue;
      else
	{
	  top = count;
	  mtypes[top].subtypes = 0;
	}
      mtypes[count].offset = strtol(cptr, &cptr, 0);
      while(isspace(*cptr)) cptr++;
      while(islower(cptr[cnt])) cnt++;
      if(!strncmp("string", cptr, cnt))
	{
	  mtypes[count].flags = M_STRING;
	  cptr += cnt;
	  sptr = parse_string(&cptr);
	  mtypes[count].mask = strlen(sptr);
	  mtypes[count].value.string = strcpy((char *)malloc(mtypes[count].mask + 1), sptr);
	  hsiz = mtypes[count].offset + mtypes[count].mask;
	  if(hsiz > maxhdr) maxhdr = hsiz;
	}
      else if(!strncmp("builtin", cptr, cnt))
	{
	  mtypes[count].flags = M_BUILTIN;
	  cptr += cnt;
	  sptr = parse_string(&cptr);
	  mtypes[count].value.string = strcpy((char *)malloc(strlen(sptr) + 1), sptr);
	}
      else if(!strncmp("regexp", cptr, cnt))
	{
	  mtypes[count].flags = M_REGEXP;
	  cptr += cnt;
	  if(*cptr == '&')
	    {
	      cptr++;
	      mtypes[count].mask = strtol(cptr, &cptr, 0);
	    }
	  else mtypes[count].mask = REGLEN;
	  hsiz = mtypes[count].offset + mtypes[count].mask;
	  if(hsiz > maxhdr) maxhdr = hsiz;
	  sptr = parse_string(&cptr);
	  mtypes[count].value.expr = regcomp(sptr);
	}
      else
	{
	  if (!strncmp("byte", cptr, cnt))
	    {
	      mtypes[count].flags = M_BYTE;
	      hsiz = mtypes[count].offset + 1;
	      if (hsiz > maxhdr) maxhdr = hsiz;
	    }
	  else if (!strncmp("short", cptr, cnt))
	    {
	      mtypes[count].flags = M_SHORT;
	      hsiz = mtypes[count].offset + 2;
	      if (hsiz > maxhdr) maxhdr = hsiz;
	    }
	  else if (!strncmp("long", cptr, cnt))
	    {
	      mtypes[count].flags = M_LONG;
	      hsiz = mtypes[count].offset + 4;
	      if(hsiz > maxhdr) maxhdr = hsiz;
	    }
	  else if (!strncmp("mode", cptr, cnt)) mtypes[count].flags = M_MODE;
	  else if (!strncmp("lmode", cptr, cnt)) mtypes[count].flags = M_LMODE;
	  else continue;		/* Error. Skip line. */
	  cptr += cnt;
	  if (*cptr == '&')
	    {
	      mtypes[count].flags |= M_MASKED;
	      cptr++;
	      mtypes[count].mask = strtol(cptr, &cptr, 0);
	    }
	  while(isspace(*cptr)) cptr++;
	  switch(*cptr)
	    {
	    case '=': mtypes[count].flags |= M_EQ; cptr++; break;
	    case '<': mtypes[count].flags |= M_LT; cptr++; break;
	    case '>': mtypes[count].flags |= M_GT; cptr++; break;
	    case '&': mtypes[count].flags |= M_SET; cptr++; break;
	    case '^': mtypes[count].flags |= M_OR; cptr++; break;
	    case 'x': mtypes[count].flags |= M_ANY; cptr++; break;
	    default:  mtypes[count].flags |= M_EQ;
	    }
	  mtypes[count].value.number = strtol(cptr, &cptr, 0);
	}
      while (isspace(*cptr)) cptr++;
      sptr = cptr;
      while (*cptr != '\n' && *cptr != '\r' && *cptr != '\0') cptr++;
      *cptr = '\0';
      mtypes[count].message = strcpy((char *)malloc(strlen(sptr) + 1), sptr);
      count++;
    }
  if (maxhdr > hdrbufsiz)
    {
      free(hdrbuf);
      hdrbuf = (char *) malloc(maxhdr + 1);
      hdrbufsiz = maxhdr;
    }
}
