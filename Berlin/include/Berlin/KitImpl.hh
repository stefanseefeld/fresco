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

#include <Prague/Sys/Tracer.hh>
#include <Warsaw/config.hh>
#include <Warsaw/Kit.hh>

class ServerImpl;
class ServantBase;

class KitImpl : public virtual POA_Warsaw::Kit,
		public virtual PortableServer::RefCountServantBase
{
  friend class ServerImpl;
public:
  KitImpl(const std::string &, const Warsaw::Kit::PropertySeq &);
  ~KitImpl();
  virtual KitImpl *clone(const Warsaw::Kit::PropertySeq &) = 0;
  const std::string &repo_id() const { return _repo_id;}
  virtual Warsaw::Kit::PropertySeq *properties() { return new Warsaw::Kit::PropertySeq(*_props);}
  virtual void bind(Warsaw::ServerContext_ptr) {};
  virtual CORBA::Boolean supports(const Warsaw::Kit::PropertySeq &);

  void activate(::ServantBase *);
  void deactivate(::ServantBase *);

  virtual void increment() { _refcount++;}
  virtual void decrement() { if (!--_refcount) deactivate();}
private:
  void activate(PortableServer::POA_ptr);
  void deactivate();
  PortableServer::POA_var         _poa;
  const std::string               _repo_id;
  const Warsaw::Kit::PropertySeq *_props;
  int                             _refcount;
};

template <typename T>
inline T *create_kit(const std::string &repo, std::string props[], size_t n)
{
  Warsaw::Kit::PropertySeq properties;
  properties.length(n);
  for (size_t i = 0; i != n/2; ++i)
    {
      properties[i].name = CORBA::string_dup((props++)->c_str());
      properties[i].value = CORBA::string_dup((props++)->c_str());
    }
  return new T(repo, properties);
}


#endif
