/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@fresco.org> 
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
#ifndef _Berlin_ObserverImpl_hh
#define _Berlin_ObserverImpl_hh

#include <Fresco/config.hh>
#include <Fresco/Observer.hh>
#include <Fresco/Subject.hh>
#include <Berlin/ServantBase.hh>
#include <Berlin/IdentifiableImpl.hh>

namespace Berlin
{

  class ObserverImpl : public virtual POA_Fresco::Observer,
               public virtual ServantBase,
               public virtual IdentifiableImpl
  {
    public:
      virtual void destroy() { deactivate(); }
  };

} // namespace

#endif 
