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
    myMutex.lock();
    if (!CORBA::is_nil(myConstraint)) myConstraint->trymodify(_this(), f, true);
    else modify(f, true);
    myMutex.unlock();
}

void TelltaleImpl::clear(Telltale::Flag f)
{
    myMutex.lock();
    if (!CORBA::is_nil(myConstraint)) myConstraint->trymodify(_this(), f, false);
    else modify(f, false);
    myMutex.unlock();
}

CORBA::Boolean TelltaleImpl::test(Telltale::Flag f)
{
    myMutex.lock();
    CORBA::Boolean tmp = flags & (1 << f);
    myMutex.unlock();
    return tmp;
}

void TelltaleImpl::constraint(TelltaleConstraint_ptr c) {
    myMutex.lock();
    myConstraint = c;
    myMutex.unlock();
}


TelltaleConstraint_ptr TelltaleImpl::constraint() {    
    myMutex.lock();
    TelltaleConstraint_ptr tmp = TelltaleConstraint::_duplicate(myConstraint);
    myMutex.unlock();
    return tmp;
}


void TelltaleImpl::modify(Telltale::Flag f, CORBA::Boolean on)
{
    myMutex.lock();
    unsigned long fs = 1 << f;
    unsigned long nf = on ? flags | fs : flags & ~fs;
    if (nf != flags)
	{
	    flags = nf;
	    notify();
	}
    myMutex.unlock();
}

void TelltaleConstraintImpl::add(Telltale_ptr t)
{
    myMutex.lock();
    telltales.push_back(t);
    myMutex.unlock();
}

void TelltaleConstraintImpl::remove(Telltale_ptr t)
{
    myMutex.lock();
    for (vector<Telltale_var>::iterator i = telltales.begin(); i != telltales.end(); i++)
	if ((*i) == t)
	    {
		telltales.erase(i);
		break;
	    }
    myMutex.unlock();    
}

ExclusiveChoice::ExclusiveChoice()
  : choosen(Telltale::_nil())
{}

void ExclusiveChoice::trymodify(Telltale_ptr t, Telltale::Flag f, CORBA::Boolean b)
{
    myMutex.lock();
    if (!CORBA::is_nil(choosen)) choosen->modify(f, false);
    t->modify(f, true);
    myMutex.unlock();        
}

SelectionRequired::SelectionRequired()
  : choosen(0)
{}

void SelectionRequired::trymodify(Telltale_ptr t, Telltale::Flag f, CORBA::Boolean b)
{
    myMutex.lock();
    if (choosen > 1) t->modify(f, false);
    myMutex.unlock();        
}
