/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@fresco.org> 
 * http://www.fresco.org
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
/* $Id$ */
#ifndef _cbuf_hh
#define _cbuf_hh

#include <streambuf>

/* @Class {cbuf : public streambuf}
 *
 * @Description {suppress comments from input}
 */
class cbuf: public std::streambuf
{
public:
  cbuf(std::streambuf *sb, char c = '#') : my_sbuf(sb), my_comment(c), my_newline(true) {}
protected:
  int sync() { return my_sbuf->sync();}
  inline int uflow();
  int sungetc() { return my_sbuf->sungetc();}
private:
  cbuf(cbuf const &);
  void operator= (cbuf const &);
  std::streambuf *my_sbuf;
  const char      my_comment;
  bool            my_newline;
};

inline int cbuf::uflow()
{
  int c = my_sbuf->sbumpc();
  if (c == '\n') my_newline = true;
  else if (c == my_comment)
    {
      do // for all lines starting with <comment>
	{
	  do c = my_sbuf->sbumpc();
	  while (c != EOF && c != '\n'); // for all letters of the line
	  if (my_newline && c == '\n') c = my_sbuf->sbumpc();
	}
      while (c == my_comment);
      if (c == '\n') my_newline = true;
    }
  else my_newline = false;
  return c;
}

#endif
