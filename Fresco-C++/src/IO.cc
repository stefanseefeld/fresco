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

#include "Warsaw/IO.hh"
#include <iomanip>
/*
 * sorry, quick hack...
 * we need to set up libraries correctly...
 */
#include "../Berlin/Math.hh"

using namespace Warsaw;

ostream &operator << (ostream &os, const Color &c)
{
  if (c.alpha != 1.) os << '(' << c.red << ',' << c.green << ',' << c.blue << ';' << c.alpha << ')';
  else os << '(' << c.red << ',' << c.green << ',' << c.blue << ')';
  return os;
}

ostream &operator << (ostream &os, const Graphic::Requirement &r)
{
  if (!r.defined) os << "undef";
  else
    {
      double tol = 1e-2;
      os << setiosflags(ios::fixed);
      if (Math::equal(r.natural, r.minimum, tol))
	{
	  if (Math::equal(r.natural, r.maximum, tol))
	    os << setprecision(2) << r.natural;
	  else
	    os << '(' << setprecision(2) << r.natural
	       << ',' << setprecision(2) << r.maximum << ')';
	}
      else if (Math::equal(r.natural, r.maximum, tol))
	os << '(' << setprecision(2) << r.minimum
	   << ',' << setprecision(2) << r.natural << ')';
      else
	os << '(' << setprecision(2) << r.minimum
	   << ',' << setprecision(2) << r.natural
	   << ',' << setprecision(2) << r.maximum << ')';
      if (!Math::equal(r.align, 0., tol))
	os << " @ " << setprecision(1) << r.align;
    }
  return os;
};

ostream &operator << (ostream &os, const Graphic::Requisition &r)
{
  return os << r.x << ", " << r.y << ", " << r.z;
}

ostream &operator << (ostream &os, const Region::Allotment &a)
{
  os << setiosflags(ios::fixed) << setprecision(2) << a.begin << ',' << setprecision(2) << a.end;
  if (!Math::equal(a.align, 0., 1e-2)) os << " @ " << setprecision(1) << a.align;
  return os;
}

ostream &operator << (ostream &os, Region_ptr r)
{
  Region::Allotment a;
  os << "X(";
  r->span(xaxis, a);
  os << a << "), Y(";
  r->span(yaxis, a);
  os << a << "), Z(";
  r->span(zaxis, a);
  os << a << ')';
  return os;
}

ostream &operator << (ostream &os, const Transform::Matrix &m)
{
  os << '[' << m[0][0] << ',' << m[0][1] << ',' << m[0][2] << ',' << m[0][3] << "]\n"
     << '[' << m[1][0] << ',' << m[1][1] << ',' << m[1][2] << ',' << m[1][3] << "]\n"
     << '[' << m[2][0] << ',' << m[2][1] << ',' << m[2][2] << ',' << m[2][3] << "]\n"
     << '[' << m[3][0] << ',' << m[3][1] << ',' << m[3][2] << ',' << m[3][3] << ']' << endl;
  return os;
};

ostream &operator << (ostream &os, Transform_ptr transform)
{
  Transform::Matrix matrix;
  transform->store_matrix(matrix);
  return os << matrix;
};
