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

TelltaleImpl::TelltaleImpl(TelltaleConstraint_ptr c, unsigned long f)
  : flags(f), myConstraint(c)
{}

TelltaleImpl::~TelltaleImpl()
{}

void TelltaleImpl::set(Telltale::Flag f)
{
  MutexGuard guard(myMutex);
  if (!CORBA::is_nil(myConstraint)) myConstraint->trymodify(_this(), f, true);
  else modify(f, true);
}

void TelltaleImpl::clear(Telltale::Flag f)
{
  MutexGuard guard(myMutex);
  if (!CORBA::is_nil(myConstraint)) myConstraint->trymodify(_this(), f, false);
  else modify(f, false);
}

CORBA::Boolean TelltaleImpl::test(Telltale::Flag f)
{
  MutexGuard guard(myMutex);
  return flags & (1 << f);
}

void TelltaleImpl::constraint(TelltaleConstraint_ptr c)
{
  MutexGuard guard(myMutex);
  myConstraint = c;
}


TelltaleConstraint_ptr TelltaleImpl::constraint()
{    
  MutexGuard guard(myMutex);
  return TelltaleConstraint::_duplicate(myConstraint);
}


void TelltaleImpl::modify(Telltale::Flag f, CORBA::Boolean on)
{
  MutexGuard guard(myMutex);
  unsigned long fs = 1 << f;
  unsigned long nf = on ? flags | fs : flags & ~fs;
  if (nf != flags)
    {
      flags = nf;
      notify();
    }
}

void TelltaleConstraintImpl::add(Telltale_ptr t)
{
  MutexGuard guard(myMutex);
  telltales.push_back(Telltale_var(t));
}

void TelltaleConstraintImpl::remove(Telltale_ptr t)
{
  Telltale_var telltale = t;
  MutexGuard guard(myMutex);
  for (vector<Telltale_var>::iterator i = telltales.begin(); i != telltales.end(); i++)
    if ((*i) == telltale)
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
  Telltale_var telltale = t;
  MutexGuard guard(myMutex);
  if (!CORBA::is_nil(choosen)) choosen->modify(f, false);
  telltale->modify(f, true);
}

SelectionRequired::SelectionRequired()
  : choosen(0)
{}

void SelectionRequired::trymodify(Telltale_ptr t, Telltale::Flag f, CORBA::Boolean b)
{ 
  Telltale_var telltale = t;
  MutexGuard guard(myMutex);
  if (choosen > 1) telltale->modify(f, false);
}
