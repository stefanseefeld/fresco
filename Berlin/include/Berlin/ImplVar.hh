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
#ifndef _Impl_var_hh
#define _Impl_var_hh

#include <Warsaw/config.hh>
#include <Warsaw/Types.hh>

// there is an annoying warning message produced by gcc.
// unless I find out how to supress that I'm going to use ObjectId *
// instead of the more convenient ObjectId_var...
// -stefan
template <typename Servant>
inline Servant activate(Servant servant)
{
  PortableServer::POA_var poa = servant->_default_POA();
//   PortableServer::ObjectId_var oid = poa->servant_to_id(servant);
  PortableServer::ObjectId *oid = poa->activate_object(servant);
  servant->_remove_ref();
  delete oid;
  return servant;
}

inline void deactivate(PortableServer::Servant servant)
{
  PortableServer::POA_var poa = servant->_default_POA();
//   PortableServer::ObjectId_var oid = poa->servant_to_id(servant);
  PortableServer::ObjectId *oid = poa->servant_to_id(servant);
  poa->deactivate_object(*oid);
  delete oid;
}

template <class T>
class Impl_var
//. a special kind of a smart pointer
//. which hides the BOA/POA details
//.
//. update: 15.07.00
//. now assumes that the wrapper types use a PortableServer::RefCountServantBase
//. -stefan
{
public:
  explicit Impl_var(T *tt = 0) : t(tt) { if (t) activate(t);}
  Impl_var(Impl_var &i) : t(i._retn()) {}
  Impl_var &operator = (Impl_var &i) { if (&i != this) { if (t) deactivate(t); t = i._retn();} return *this;}
  ~Impl_var() { if (t) deactivate(t);}
  Impl_var &operator = (T *tt) { if (t) deactivate(t); t = tt; if (t) activate(t); return *this;}
  T *get() const { return t;}
  T &operator *() const { return *t;}
  T *operator->() const { return  t;}
  operator T *() const { return  t;}
  T *_retn() { T *tmp = t; t = 0; return tmp;}
private:
  T *t;
};

#endif
