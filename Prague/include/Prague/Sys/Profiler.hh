/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Brent A. Fulgham <bfulgham@debian.org>
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

#ifndef _Profiler_hh
#define _Profiler_hh

#include <Prague/Sys/ntree.hh>
#include <ctime>
#include <iostream>
#include <string>
#include <iomanip.h>

namespace Prague
{

struct CheckPoint
{
  CheckPoint(const string &s) : name(s), count(0), start(0), stop(0), elapsed(0) {}
  CheckPoint(CheckPoint *cp)
    : name(cp->name),
      count(cp->count),
      start(cp->start),
      stop(cp->stop),
      elapsed(cp->elapsed)
    {}
  void indent(ostream &os, unsigned short ind) { while (ind--) os.put(' ');}
  void output(ostream &os, unsigned short ind)
    {
      indent(os, ind); os << name << ": " << setw(10) << count;
      indent(os, ind); os << " Times.  Total Time: ";
      indent(os, ind); os << setprecision(8) << setw(12);
      indent(os, ind); os.setf( ios::fixed, ios::floatfield);
      indent(os, ind); os << elapsed/CLOCKS_PER_SEC;
      indent(os, ind); os  << "  Avg/Iter.: ";
      indent(os, ind); os << setprecision(8) << setw(12);
      indent(os, ind); os << elapsed/count/CLOCKS_PER_SEC << endl;
    }
  string name;
  long count;
  clock_t start;
  clock_t stop;
  double elapsed;
};
 
class Profiler
{
  typedef ntree<CheckPoint *> table_t;
  typedef ntree<CheckPoint *>::node item_t;
  typedef ntree<CheckPoint *>::node::child_iterator child_iterator;
  typedef ntree<CheckPoint *>::node::const_child_iterator const_child_iterator;
  typedef ntree<CheckPoint *>::node::up_iterator up_iterator;
public:
  Profiler(const string &name)
    {
      if (!count++)
	{
	  table = new table_t(new CheckPoint("root"));
	  current = &table->root();
	  os = &cout;
	}
      child_iterator i = lookup(name);
      current = &*i;
      current->value->count++;
      current->value->start = clock(); 
    }
  ~Profiler()
    {
      current->value->stop = clock();
      current->value->elapsed += (current->value->stop - current->value->start);
      up_iterator i = current->up_begin();
      current = &*++i;
      if (!--count)
	{
	  dump(*current, 0);
	  clean(*current);
	}
    }
  static void setOutput(ostream &o) { os = &o;}
private:
  static child_iterator lookup(const string &name)
    {
      for (child_iterator i = current->child_begin(); i != current->child_end(); i++)
	if ((*i).value->name == name) return i;
      return current->push_back(new CheckPoint(name));
    }
  static void dump(const item_t &root, unsigned short ind)
    {
      for (const_child_iterator i = root.child_begin(); i != root.child_end(); i++)
	dump(*i, ind + 1);
      if (ind) root.value->output(*os, ind); // don't output the root
    }
  static void clean(const item_t &root)
    {
      for (const_child_iterator i = root.child_begin(); i != root.child_end(); i++)
	clean(*i);
      delete root.value;
    }
  static long     count;
  static table_t *table;
  static item_t  *current;
  static ostream *os;
};

};

#endif /* _Profiler_hh */
