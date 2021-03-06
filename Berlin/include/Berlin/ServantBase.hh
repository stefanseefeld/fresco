/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 2000 Stefan Seefeld <stefan@fresco.org> 
 * http://www.fresco.org
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
#ifndef _Berlin_ServantBase_hh
#define _Berlin_ServantBase_hh

#include <Prague/Sys/Tracer.hh>
#include <Fresco/config.hh>
#include <Fresco/Types.hh>
#include <Berlin/DefaultPOA.hh>
#include <cassert>

namespace Berlin
{

  class ServantBase : virtual public PortableServer::ServantBase,
              private DefaultPOA
  {
      friend class KitImpl;
      friend class IdentifiableImpl;
    public:
      ServantBase();
      ServantBase(const ServantBase &);
      virtual ~ServantBase();
      ServantBase &operator = (const ServantBase &);
      virtual PortableServer::POA_ptr _default_POA();
      virtual void _add_ref();
      virtual void _remove_ref();
      virtual void deactivate();
    protected:
      static void deactivate(ServantBase *);
      //. In case this object serves as a factory,
      //. this method allows to activate the manufactored objects
      //. with the same POA this object is registered with
      void activate(ServantBase *);
      //. If the servant is a composite, it needs to implement this method
      //. to activate the child servants
      virtual void activate_composite() { }
    private:
      int                     my_refcount;
      PortableServer::POA_var my_poa;
};

} // namespace

#endif
