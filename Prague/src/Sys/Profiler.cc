/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Brent A. Fulgham <bfulgham@debian.org>
 * Copyright (C) 1999,2000 Stefan Seefeld <stefan@berlin-consortium.org>
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

#include "Prague/Sys/Profiler.hh"

using namespace Prague;

Profiler::Guard    Profiler::guard;
Profiler::table_t *Profiler::table = 0;
Profiler::item_t  *Profiler::current = 0;
Mutex              Profiler::mutex;

void Profiler::CheckPoint::output(ostream &os, unsigned short ind)
{
  if (elapsed > 0.)
    {
      indent(os, ind);
      os << name << ": " << setw(10) << count;
      os << " Times.  Total Time: ";
      os << setprecision(8) << setw(12);
      os.setf( ios::fixed, ios::floatfield);
      os << elapsed/CLOCKS_PER_SEC;
      os  << "  Avg/Iter.: ";
      os << setprecision(8) << setw(12);
      os << elapsed/count/CLOCKS_PER_SEC << endl;
    }
}
