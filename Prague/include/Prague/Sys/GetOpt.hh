/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
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

#ifndef _GetOpt_hh
#define _GetOpt_hh

#include <iostream>
#include <vector>
#include <string>

namespace Prague
{

/* @Class{GetOpt}
 *
 * @Description{replacement for GNU GetOpt, adds handling of long options: proposed interface:
 @itemize @bullet
 @item try complience to standard getopt functions
 @item work as a filter, enabling subsequent option extraction by different GetOpt instances
 @item use '-' for short and '--' for long option styles
 @end itemize
 }
 */
class GetOpt
{
public:
  enum type { novalue, optional, mandatory};
  enum order { inorder, require, permute};
  GetOpt(const char *, const char * = 0);
  ~GetOpt();
  void Usage() const;
  int parse(int, char **);
  int parse(char *);
  void add(char, const string &, type, const string & = "no description available");
  void get(char, string *) const;
  void get(const string &, string *) const;
private:
  struct cell
  {
    cell(char oo, const string &opt, type tt, const string &des)
      : o(oo), option(opt), t(tt), description(des) {}
    char        o;            // option char
    string      option;       // option name
    type        t;	      // option type
    string      description;  // a description of option
    string      value;	      // value of option (string)    
  };
  vector<cell *> table;	      // option table
  typedef vector<cell *>::iterator iterator;
  typedef vector<cell *>::const_iterator const_iterator;
  const char *pname;	      // program basename
  const char *usage;	      // usage message
  order ordering;
  unsigned int getlongopt(int, char **);
  unsigned int getopt(int, char **);
  const_iterator find(const string &) const;
  const_iterator find(char) const;
  void exchange(char **, char **, char **);
  struct comp_string
  {
    comp_string(const string &n) : name(n) {}
    bool operator () (cell *c) { return name == c->option;}
    const string name;
  };
  struct comp_char
  {
    comp_char(char n) : name(n) {}
    bool operator () (cell *c) { return name == c->o;}
    char name;
  };
};

};

#endif /* _GetOpt_hh */
