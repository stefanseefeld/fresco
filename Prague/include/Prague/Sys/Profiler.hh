/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Brent A. Fulgham <bfulgham@debian.org>
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

#include <hash_set>
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
  void Output()
    {
      cout << setw(5) << name << ": " << setw(10) << count;
      cout << " Times.  Total Time: ";
      cout << setprecision(8) << setw(12);
      cout.setf( ios::fixed, ios::floatfield);
      cout << elapsed/CLOCKS_PER_SEC;
      cout  << "  Avg/Iter.: ";
      cout << setprecision(8) << setw(12);
      cout << elapsed/count/CLOCKS_PER_SEC << endl;
    }
  string name;
  long count;
  clock_t start;
  clock_t stop;
  double elapsed;
};
 
struct eqchkpt
{
  bool operator()(const Prague::CheckPoint *cp1, const Prague::CheckPoint *cp2) const
    { return cp1->name == cp2->name;}
};

};

struct hash<Prague::CheckPoint *>
{
  size_t operator()(const Prague::CheckPoint *cp) const
    {
      unsigned long h = 0; 
      for (string::const_iterator s = cp->name.begin(); s != cp->name.end(); ++s)
	h = 5*h + *s;
      return size_t(h);
    }
};

namespace Prague
{

class Profiler
{
  typedef hash_set<CheckPoint *, hash<Prague::CheckPoint *>, eqchkpt> table_t;
public:
  Profiler(const string &name) : now(name) 
    {
      if (!count++) table = new table_t;
      CheckPoint *current = lookup(&now);
      if (!current)
	{
	  current = new CheckPoint(&now);
	  table->insert(current);
	}
      current->count++;
      current->start = clock(); 
    }
  ~Profiler()
    {
      CheckPoint *current = lookup(&now);
      if (!current)
	{
	  cerr << "Problem!" << endl;
	  exit(1);
	}
      current->stop = clock();
      current->elapsed += (current->stop - current->start);
      if (!--count)
	{
	  cout << "Dumping Profiling Data..." << endl;
	  for (table_t::const_iterator i = table->begin(); i != table->end(); i++)
	    (*i)->Output();
	}
    }
  static CheckPoint *lookup(Prague::CheckPoint *cp)
    {
      table_t::iterator i = table->find(cp);
      return i == table->end() ? 0 : *i;
    }
private:
  static long count;
  static table_t *table;
  CheckPoint now;
};

};

#endif /* _Profiler_hh */
