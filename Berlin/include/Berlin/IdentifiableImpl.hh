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
#ifndef _Berlin_IdentifiableImpl_hh
#define _Berlin_IdentifiableImpl_hh

#include <Fresco/config.hh>
#include <Fresco/Identifiable.hh>
#include <Berlin/ServantBase.hh>

namespace Berlin
{

  class IdentifiableImpl : public virtual POA_Fresco::Identifiable,
			   public virtual ServantBase,
			   public virtual Prague::NamedObject

  {
    public:
      CORBA::Boolean is_identical(Fresco::Identifiable_ptr);

      //. Default implementation of this method from NamedObject. Remove
      //. this to let the compiler tell you which classes you forgot to
      // fix this in :)
      virtual const char *object_name() { return 0;}  
  };

} // namespace

#endif
