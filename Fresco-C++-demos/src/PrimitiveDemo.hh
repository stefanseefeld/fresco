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
#ifndef _PrimitiveDemo_hh
#define _PrimitiveDemo_hh

#include <Warsaw/config.hh>
#include <Warsaw/Command.hh>
#include <Warsaw/BoundedValue.hh>
#include <Berlin/TransformImpl.hh>
#include <Berlin/ObserverImpl.hh>
#include <Berlin/ImplVar.hh>
#include "Demo.hh"

class PrimitiveDemo : public Demo
{
  class Rotator : public ObserverImpl
  {
  public:
    Rotator(Warsaw::BoundedValue_ptr, Warsaw::Graphic_ptr, Warsaw::Graphic_ptr, Warsaw::Axis);
    void update(const CORBA::Any &);
  private:
    Warsaw::BoundedValue_var value;
    Warsaw::Graphic_var child;
    Warsaw::Graphic_var parent;
    Warsaw::Axis axis;
  };

public:
  PrimitiveDemo(Application *);
  Warsaw::Graphic_ptr make_controller(Warsaw::BoundedValue_ptr, const Warsaw::Color &);
private:
  Warsaw::BoundedValue_var phi;
  Warsaw::BoundedValue_var psi;
  Impl_var<TransformImpl> tx1;
  Impl_var<TransformImpl> tx2;
  Impl_var<Rotator> rotator1;
  Impl_var<Rotator> rotator2;
};

#endif
