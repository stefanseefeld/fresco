/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
 * Copyright (C) 1999 Graydon Hoare <graydon@pobox.com> 
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
#ifndef _TelltaleImpl_hh
#define _TelltaleImpl_hh

#include <Warsaw/config.hh>
#include <Warsaw/Telltale.hh>
#include <Berlin/SubjectImpl.hh>
#include <Prague/Sys/Thread.hh>
#include <vector>

class TelltaleImpl : public virtual POA_Warsaw::Telltale,
		     public SubjectImpl
{
 public:
  TelltaleImpl(Warsaw::TelltaleConstraint_ptr, CORBA::ULong m = 0);
  virtual ~TelltaleImpl();
  virtual void set(Warsaw::Telltale::Mask);
  virtual void clear(Warsaw::Telltale::Mask);
  virtual CORBA::Boolean test(Warsaw::Telltale::Mask);
  virtual void modify(Warsaw::Telltale::Mask, CORBA::Boolean);
  CORBA::ULong state() { return mask;}

  virtual void constraint(Warsaw::TelltaleConstraint_ptr);
  virtual Warsaw::TelltaleConstraint_ptr constraint();

 protected:
  CORBA::ULong mask;
  Warsaw::TelltaleConstraint_var myConstraint;
  Prague::Mutex mutex;
};

class TelltaleConstraintImpl : public virtual POA_Warsaw::TelltaleConstraint,
			       public virtual PortableServer::RefCountServantBase,
			       public virtual RefCountBaseImpl
{
  typedef vector<Warsaw::Telltale_var> tlist_t;
 public:
  TelltaleConstraintImpl() {}
  virtual ~TelltaleConstraintImpl() {}
  void add(Warsaw::Telltale_ptr);
  void remove(Warsaw::Telltale_ptr);
  virtual void trymodify(Warsaw::Telltale_ptr, Warsaw::Telltale::Mask, CORBA::Boolean) = 0;
 protected:
  tlist_t telltales;
  Prague::Mutex mutex;
};

class ExclusiveChoice : public TelltaleConstraintImpl
{
public:
  ExclusiveChoice(Warsaw::Telltale::Mask);
  virtual void trymodify(Warsaw::Telltale_ptr, Warsaw::Telltale::Mask, CORBA::Boolean);  
private:
  Warsaw::Telltale::Mask mask;
};

class SelectionRequired : public TelltaleConstraintImpl
{
public:
  SelectionRequired();
  virtual void trymodify(Warsaw::Telltale_ptr, Warsaw::Telltale::Mask, CORBA::Boolean);  
};

#endif
