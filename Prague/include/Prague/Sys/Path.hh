/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@berlin-consortium.org> 
 * http://www.berlin-consortium.org
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
#ifndef _Prague_Path_hh
#define _Prague_Path_hh

#include <string>
#include <vector>

namespace Prague
{

//. Path implements the Unix Path functionality, i.e. file lookup.
class Path
{
  typedef vector<string> rep_type;
  typedef rep_type::iterator iterator;
public:
  struct predicate { virtual bool operator()(const string &name) const = 0;};
  //. construct an empty path
  Path() : paths(0) {}
  //. construct a path out of 'path', typically an environment variable; use c as separator
  Path(const string &path, char c = ':');
  ~Path();
  //. append a directory
  void append(const string &directory) { _directories.push_back(directory);}
  //. look up a file, using the predicate functor, if non-zero
  string lookup_file(const string &, predicate * = 0) const;
  //. expand a directory, if it is provided as '~joe/foo'
  static string expand_user(const string &);
  //. return begin iterator
  iterator begin() { return _directories.begin();}
  //. return end iterator
  iterator end() { return _directories.end();}
  //. return the size, i.e. the number of directories contained in the path
  size_t size() { return _directories.size();}
  //. return ith directory
  const string &operator [] (size_t i) { return _directories[i];}
private:
  rep_type _directories;
};

};

#endif
