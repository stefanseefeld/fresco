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
#include "Widget/TelltaleImpl.hh"
#include "Berlin/Logger.hh"

using namespace Prague;

TelltaleImpl::TelltaleImpl(TelltaleConstraint_ptr c, unsigned long f)
  : flags(f), myConstraint(c)
{}

TelltaleImpl::~TelltaleImpl()
{}

void TelltaleImpl::set(Telltale::Flag f)
{
  SectionLog section(Logger::subject, "TelltaleImpl::set");
  if (!CORBA::is_nil(myConstraint)) myConstraint->trymodify(Telltale_var(_this()), f, true);
  else modify(f, true);
}

void TelltaleImpl::clear(Telltale::Flag f)
{
  SectionLog section(Logger::subject, "TelltaleImpl::clear");
  if (!CORBA::is_nil(myConstraint)) myConstraint->trymodify(Telltale_var(_this()), f, false);
  else modify(f, false);
}

CORBA::Boolean TelltaleImpl::test(Telltale::Flag f)
{
  MutexGuard guard(mutex);
  return flags & (1 << f);
}

void TelltaleImpl::modify(Telltale::Flag f, CORBA::Boolean on)
{
  unsigned long fs = 1 << f;
  unsigned long nf = on ? flags | fs : flags & ~fs;
  {
    MutexGuard guard(mutex);
    if (nf == flags) return;
    else flags = nf;
  }
  CORBA::Any any;
  notify(any);
}

void TelltaleImpl::constraint(TelltaleConstraint_ptr c)
{
  MutexGuard guard(mutex);
  myConstraint = c;
}


TelltaleConstraint_ptr TelltaleImpl::constraint()
{
  MutexGuard guard(mutex);
  return TelltaleConstraint::_duplicate(myConstraint);
}

void TelltaleConstraintImpl::add(Telltale_ptr t)
{
  MutexGuard guard(mutex);
  telltales.push_back(Telltale::_duplicate(t));
}

void TelltaleConstraintImpl::remove(Telltale_ptr t)
{
  MutexGuard guard(mutex);
  for (vector<Telltale_var>::iterator i = telltales.begin(); i != telltales.end(); i++)
    if ((*i) == t)
      {
	telltales.erase(i);
	break;
      }
}

ExclusiveChoice::ExclusiveChoice()
  : choosen(Telltale::_nil())
{}

void ExclusiveChoice::trymodify(Telltale_ptr t, Telltale::Flag f, CORBA::Boolean b)
{
  if (!CORBA::is_nil(choosen)) choosen->modify(f, false);
  t->modify(f, true);
}

SelectionRequired::SelectionRequired()
  : choosen(0)
{}

void SelectionRequired::trymodify(Telltale_ptr t, Telltale::Flag f, CORBA::Boolean b)
{
  if (choosen > 1) t->modify(f, false);
}
