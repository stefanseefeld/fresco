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
#ifndef _regex_hh
#define _regex_hh

#include <string>
#include <sys/types.h>
#include <regex.h>

namespace Prague
{

/* @Class{rxmatch}
 *
 * @Description{represents matches of a regular expression search}
 */
class rxmatch
{
public:
  typedef regmatch_t *iterator;
  rxmatch() : n(0), r(0) {}
  ~rxmatch() { delete [] r;}
  size_t size() const { return n;}
  iterator begin() const { return r;}
  iterator end() const { return r + n;}
  string substr(iterator i) const { return s.substr(i->rm_so, i->rm_eo - i->rm_so);}
  operator bool () const { return n;}
  friend class regex;
private:
  string      s;
  size_t      n;
  regmatch_t *r;
  rxmatch(const string &ss, int p, int nn, regmatch_t *rr) : s(ss), n(nn), r(rr)
    {
      if (p == -1) n = 0;
      for (size_t i = 0; i != n; i++)
	if (rr[i].rm_so == -1) { n = i; break;}
	else rr[i].rm_so += p, rr[i].rm_eo += p;
    }
};

/* @Class{regex}
 *
 * @Description{}
 */
class regex
{
public:
  enum syntax { extended = REG_EXTENDED, basic};
  regex(const string &, int = extended);
  ~regex();
  string::size_type match(const string &, int = 0) const;
  rxmatch search(const string &, int = 0) const;
  bool OK() const { return rx;}
protected:
  regex_t *rx;
  size_t nexprs() const;
  string error(int);
private:
  regex(const regex &);
  regex &operator = (const regex &);
};

inline size_t regex::nexprs() const
{
  return rx->re_nsub + 1;
}

extern const regex rxwhite;          // = "[ \n\t\r\v\f]+"
extern const regex rxint;            // = "-?[0-9]+"
extern const regex rxdouble;         // = "-?(([0-9]+.[0-9]*)|
                                     //    ([0-9]+)|(.[0-9]+))
                                     //    ([eE][---+]?[0-9]+)?"
extern const regex rxalpha;          // = "[A-Za-z]+"
extern const regex rxlowercase;      // = "[a-z]+"
extern const regex rxuppercase;      // = "[A-Z]+"
extern const regex rxalphanum;       // = "[0-9A-Za-z]+"
extern const regex rxidentifier;     // = "[A-Za-z_][A-Za-z0-9_]*"

};

#endif /* _regex_hh */
