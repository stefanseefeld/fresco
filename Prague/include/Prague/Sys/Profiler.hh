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

#include <hashtable.h>
#include <hash_set.h>
#include "time.h"

namespace Prague
{

struct CheckPoint
{
	long line;
	long count;
	clock_t start;
	clock_t stop;
	double elapsed;

	CheckPoint(long ln) : line(ln), count(0), start(0), stop(0), elapsed(0) {}
	CheckPoint(CheckPoint* cp) : line(cp->line), count(cp->count),
		start(cp->start), stop(cp->stop), elapsed(cp->elapsed) {}

	Output()
	{
		cout << "Line: " << line << "  Hit: " << count << " times. Tot Time: ";
		cout << elapsed/CLOCKS_PER_SEC << "  Avg Time PI: ";
		cout << elapsed/count/CLOCKS_PER_SEC << endl;
	}	
};

struct eqchkpt
{
	bool operator()(const Prague::CheckPoint* cp1,
					const Prague::CheckPoint* cp2) const
	{
		return (cp1->line == cp2->line)?true:false;
	}
};

struct hash<Prague::CheckPoint*>
{
	size_t operator()(const Prague::CheckPoint* cp) const
	{
		return cp->line;
	}
};

class Profiler
{
public:
	Profiler(long line) : now(line) 
	{
		if (refCount == 0)
		{
			Set =  new hash_set<CheckPoint*, hash<CheckPoint*>, eqchkpt>;
		}
		
		refCount++;
		// Locate tag if already set
		CheckPoint* current = lookup(&now);
		if (current == NULL)
		{
			current = new CheckPoint(&now);
			Set->insert(current);
		}
		current->count++;
		current->start = clock(); 
	}
	
	~Profiler()
	{
		CheckPoint* current = lookup(&now);
		if (current == NULL)
		{
			cerr << "Problem!" << endl;
			exit(1);
		}
		current->stop = clock();
		current->elapsed += (current->stop - current->start);
		refCount--;
		if (refCount == 0)
		{
			cout << "Dumping Profiling Data..." << endl;
			hash_set<CheckPoint*, hash<Prague::CheckPoint*>,
				eqchkpt>::const_iterator it = Set->begin();
			for (int i=0; i<Set->size(); i++)
			{
				(*it)->Output();
				it++;
			}
		}
	}

	inline static CheckPoint* lookup(Prague::CheckPoint* cp)
	{
		hash_set<Prague::CheckPoint*, hash<Prague::CheckPoint*>,
			eqchkpt>::const_iterator it = Set->find(cp);
		if (it == Set->end())
			return NULL;
		
		return *it;
	}

private:
	static long refCount;
	static hash_set<CheckPoint*, hash<CheckPoint*>, eqchkpt>* Set;
	CheckPoint now;
};

hash_set<CheckPoint*, hash<CheckPoint*>, eqchkpt>* Profiler::Set = NULL;
long Profiler::refCount = 0;

};

#endif /* _Profiler_hh */
