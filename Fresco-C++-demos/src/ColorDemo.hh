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
#ifndef _CXX_demos_ColorDemo_hh
#define _CXX_demos_ColorDemo_hh

#include <Fresco/config.hh>
#include <Fresco/BoundedValue.hh>
#include <Berlin/ObserverImpl.hh>
#include "Demo.hh"

class ColorDemo : public Demo
{
    class Adapter : public Berlin::ObserverImpl
    {
      public:
    Adapter(ColorDemo *d, Fresco::Tag t) : my_demo(d), my_tag(t) { }
    virtual void update(const CORBA::Any &)
    { my_demo->adjust(my_tag); }
      private:
    ColorDemo *my_demo;
    Fresco::Tag my_tag;
    };
    friend class Adapter;
  public:
    ColorDemo(Application *);
  private:
    void adjust(Fresco::Tag);
    Fresco::BoundedValue_var my_red;
    Fresco::BoundedValue_var my_green;
    Fresco::BoundedValue_var my_blue;
    Fresco::BoundedValue_var my_hue;
    Fresco::BoundedValue_var my_saturation;
    Fresco::BoundedValue_var my_value;
    Adapter *my_adapter[6];
};

#endif
