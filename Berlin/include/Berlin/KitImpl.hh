/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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
#ifndef _KitImpl_hh
#define _KitImpl_hh

#include <Warsaw/config.hh>
#include <Warsaw/Kit.hh>
#include "Berlin/KitFactory.hh"

class ServerContextImpl;

class KitImpl : public virtual POA_Kit, public virtual PortableServer::RefCountServantBase
{
  friend class ServerContextImpl;
 protected:
  typedef Kit::PropertySeq PropertySeq;
 public:
  KitImpl(KitFactory *f, const PropertySeq &p) : counter(0), fact(f), props(p) { fact->increment();}
  ~KitImpl() { fact->decrement();}
  //. notify the factory about our (non) existence so it knows when it is safe to get unloaded
  virtual PropertySeq *properties() { return new PropertySeq(props);}
  virtual void bind(ServerContext_ptr) { counter = 1;}
  virtual void remove() {}//{ if (!decrement()) _dispose();}
  virtual CORBA::Boolean supports(const PropertySeq &p) { return KitFactory::supports(props, p);}
 protected:
  void increment() { counter++;}
  bool decrement() { return --counter;}
 private:
  unsigned short     counter;
  KitFactory        *fact;
  const PropertySeq &props;
};

template <class T>
class KitFactoryImpl : public KitFactory
{
 public:
  KitFactoryImpl(const string &type, const string *properties, unsigned short size) : KitFactory(type, properties, size) {}
  virtual KitImpl *create(const Kit::PropertySeq &) { return new T(this, *props);}
};

#endif
