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
/*$Id$*/
#ifndef _url_hh
#define _url_hh

#include <string>

/* @Class{url}
 *
 * @Description{The url class parses and stores a Uniform Resource Locator, as specified in RFC1738 and RFC1808. This class can take a partially or fully qualified URL as a string, and parse it into its component parts. It can also resolve a partially qualified URL to a fully qualified URL using a fully qualified "base" URL.}
 */
class url
{
public:
  url(const string &);
  url(const url &, const string &);
  operator const string &() const;
  const string &Method() const { return method;}
  const string &User() const { return user;}
  const string &Password() const { return password;}
  const string &Hostname() const { return hostname;}
  const string &Path() const { return path;}
  void setPath(const char *p) { path = p;}
  const string &Fragment() const { return fragment;}
  const string Query() const { return query;}
  void setQuery(const string &q) { query = q;}
  const string &Parameters() const { return parameters;}
  int Port() const { return port;}
  static void encode(const string &);
protected:
  string method;
  string user;
  string password;
  string hostname;
  string path;
  string fragment;
  string query;
  string parameters;
  int    port;
  void parse(const string &);
};

#endif /* _url_hh */
