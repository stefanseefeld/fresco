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

#include <Prague/Sys/Tracer.hh>
#include <Fresco/config.hh>
#include <Fresco/DrawTraversal.hh>
#include <Fresco/DrawingKit.hh>
#include <Fresco/Subject.hh>
#include <Berlin/TransformImpl.hh>
#include <Berlin/RegionImpl.hh>
#include <Berlin/Provider.hh>
#include "Switch.hh"

using namespace Prague;
using namespace Fresco;

using namespace Berlin::ToolKit;

Switch::Switch(Telltale::Mask m)
  : my_on(true), my_mask(m)
{
  Trace trace("Switch::Switch");
}

Switch::~Switch()
{
  Trace trace("Switch::~Switch");
}

void Switch::init(Graphic_ptr g1, Graphic_ptr g2)
{
  if (CORBA::is_nil(my_telltale) || my_on)
    set(g1, g2);
  else
    set(g2, g1);
}

void Switch::attach(Telltale_ptr subject)
{
  Trace trace("Switch::attach");
  if (!CORBA::is_nil(my_telltale)) my_telltale->detach(Observer_var(_this()));
  if (!CORBA::is_nil(subject))
    {
      my_telltale = RefCount_var<Telltale>::increment(subject);
      my_telltale->attach(Observer_var(_this()));
      bool flag = my_telltale->test(my_mask);
      if (flag == my_on) return;
      my_on = flag;
      set(my_alternate, body());
      need_resize();
    }
  else my_telltale = Telltale::_nil();
}

void Switch::update(const CORBA::Any &)
{
  Trace trace("Switch::update");
  bool flag = my_telltale->test(my_mask);
  if (flag == my_on) return;
  my_on = flag;
  need_resize(); // FIXME race condition, see bug256.
  set(my_alternate, body());
  need_resize();
}

void Switch::set(Graphic_ptr g1, Graphic_ptr g2)
{
  body(g1);
  my_alternate = Fresco::Graphic::_duplicate(g2);
}

