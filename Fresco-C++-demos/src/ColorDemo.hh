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
#ifndef _ColorDemo_hh
#define _ColorDemo_hh

#include "Warsaw/config.hh"
#include "Warsaw/BoundedValue.hh"
#include "Demo.hh"

class ColorDemo : public Demo
{
  class Adapter : public virtual POA_Observer, public virtual PortableServer::RefCountServantBase
  {
  public:
    Adapter(ColorDemo *d, Tag t) : demo(d), tag(t) {}
    virtual void update(const CORBA::Any &) { demo->adjust(tag);}
  private:
    ColorDemo *demo;
    Tag tag;
  };
  friend class Adapter;
public:
  ColorDemo(Application *);
private:
  void adjust(Tag);
  BoundedValue_var red;
  BoundedValue_var green;
  BoundedValue_var blue;
  BoundedValue_var hue;
  BoundedValue_var saturation;
  BoundedValue_var value;
  Adapter *adapter[6];
};

#endif
