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
#ifndef _ServantBase_hh
#define _ServantBase_hh

#include <Prague/Sys/Tracer.hh>
#include <Warsaw/config.hh>
#include <Warsaw/Types.hh>
#include <Berlin/KitImpl.hh>
#include <cassert>

class ServantBase : public virtual PortableServer::RefCountServantBase
{
  friend class KitImpl;
public:
  ServantBase(): kit(0) {}
  ~ServantBase() {}
  void deactivate() { assert(kit); kit->deactivate(this);}
protected:
  //.in case this object serves as a factory,
  //.this method allows to activate the manufactored objects
  //.with the same POA this object is registered with
  void activate(ServantBase *servant) { assert(kit); kit->activate(servant);}
  //.if the servant is a composite, it needs to implement this method
  //.to activate the child servants
  virtual void activateComposite() {}
private:
  KitImpl *kit;
};

#endif
