/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
 * http://www.berlin-consortium.org
 *
 * this file is based on code from the socket++ library
 * Copyright (C) 1992-1996 Gnanasekaran Swaminathan <gs4t@virginia.edu>
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
 */
#ifndef _sockstream_hh
#define _sockstream_hh

#include <Prague/IPC/socketbuf.hh>
#include <iostream>

namespace Prague
{

/* @Class{isockstream : public istream}
 *
 * @Description{an istream for sockets}
 */
class isockstream : public istream
{
public:
  isockstream(socketbuf *sb) : ios (sb) {}
  virtual ~isockstream () {}        
  socketbuf *rdbuf () { return static_cast<socketbuf *> (ios::rdbuf()); }
  socketbuf *operator -> () { return rdbuf(); }
protected:
  isockstream () : ios (0) {}
};

/* @Class{osockstream : public ostream}
 *
 * @Description{an ostream for sockets}
 */
class osockstream : public ostream
{
public:
  osockstream(socketbuf *sb) : ios (sb) {}
  virtual ~osockstream () {}
  socketbuf *rdbuf () { return static_cast<socketbuf *> (ios::rdbuf());}
  socketbuf *operator -> () { return rdbuf();}
protected:
  osockstream () : ios (0) {}
};

/* @Class{iosockstream : public iostream}
 *
 * @Description{an iostream for sockets}
 */
class iosockstream : public iostream
{
public:
  iosockstream(socketbuf* sb): ios (sb) {}
  virtual ~iosockstream () {}
  socketbuf *rdbuf () { return static_cast<socketbuf *> (ios::rdbuf());}
  socketbuf *operator -> () { return rdbuf();}
protected:
  iosockstream () : ios (0) {}
};

// manipulators
// inline osockstream &crlf (osockstream &o)
// {
//   o << "\r\n";
//   o.rdbuf ()->sync ();
//   return o;
// }

// inline osockstream &lfcr (osockstream &o)
// {
//   o << "\n\r";
//   o.rdbuf ()->sync ();
//   return o;
// }

/* @Class{isockunix : public isockstream}
 *
 * @Description{an istream for unix sockets}
 */
class isockunix : public isockstream
{
public:
  isockunix (int s) : ios (new sockunixbuf (s)) {}
  isockunix (const sockunixbuf& sb) : ios (new sockunixbuf (sb)) {}
  isockunix (socketbuf::type ty = socketbuf::sock_stream, int proto = 0) : ios (new sockunixbuf (ty, proto)) {}
  ~isockunix() { delete ios::rdbuf ();}
  sockunixbuf *operator -> () { return static_cast<sockunixbuf *> (rdbuf ()); }
};

/* @Class{osockunix : public osockstream}
 *
 * @Description{an ostream for unix sockets}
 */
class osockunix : public osockstream
{
public:
  osockunix (int s) : ios (new sockunixbuf (s)) {}
  osockunix (const sockunixbuf& sb) : ios (new sockunixbuf (sb)) {}
  osockunix (socketbuf::type ty=socketbuf::sock_stream, int proto = 0) : ios (new sockunixbuf (ty, proto)) {}
  ~osockunix () { delete ios::rdbuf ();}
  sockunixbuf *operator -> () { return static_cast<sockunixbuf *> (rdbuf()); }
};

/* @Class{iosockunix : public iosockstream}
 *
 * @Description{an iostream for unix sockets}
 */
class iosockunix : public iosockstream
{
public:
  iosockunix (int s) : ios (new sockunixbuf (s)) {}
  iosockunix (const sockunixbuf &sb) : ios (new sockunixbuf (sb)) {}
  iosockunix (socketbuf::type ty=socketbuf::sock_stream, int proto = 0) : ios (new sockunixbuf (ty, proto)) {}
  ~iosockunix () { delete ios::rdbuf ();}
  sockunixbuf *operator -> () { return static_cast<sockunixbuf *> (rdbuf()); }
};

/* @Class{isockinet : public isockstream}
 *
 * @Description{an istream for internet sockets}
 */
class isockinet : public isockstream
{
public:
  isockinet (int s) : ios (new sockinetbuf (s)) {}
  isockinet (const sockinetbuf &sb) : ios (new sockinetbuf (sb)) {}
  isockinet (socketbuf::type ty=socketbuf::sock_stream, int proto = 0) : ios (new sockinetbuf (ty, proto)) {}
  ~isockinet () { delete ios::rdbuf();}
  sockinetbuf *rdbuf () { return static_cast<sockinetbuf *> (ios::rdbuf());}
  sockinetbuf *operator -> () { return rdbuf();}
};

/* @Class{osockinet : public osockstream}
 *
 * @Description{an ostream for internet sockets}
 */
class osockinet : public osockstream
{
public:
  osockinet (int s) : ios (new sockinetbuf (s)) {}
  osockinet (const sockinetbuf &sb) : ios (new sockinetbuf (sb)) {}
  osockinet (socketbuf::type ty=socketbuf::sock_stream, int proto = 0) : ios (new sockinetbuf (ty, proto)) {}
  ~osockinet () { delete ios::rdbuf();}
  sockinetbuf *rdbuf () { return static_cast<sockinetbuf *> (ios::rdbuf()); }
  sockinetbuf *operator -> () { return rdbuf();}
};

/* @Class{iosockinet : public iosockstream}
 *
 * @Description{an iostream for internet sockets}
 */
class iosockinet : public iosockstream
{
public:
  iosockinet (int s) : ios (new sockinetbuf (s)) {}
  iosockinet (const sockinetbuf &sb) : ios (new sockinetbuf (sb)) {}
  iosockinet (socketbuf::type ty = socketbuf::sock_stream, int proto = 0) : ios (new sockinetbuf (ty, proto)) {}
  ~iosockinet () { delete ios::rdbuf();}
  sockinetbuf *rdbuf () { return static_cast<sockinetbuf *> (ios::rdbuf());}
  sockinetbuf *operator -> () { return rdbuf();}
};

};

#endif /* _sockstream_hh */
