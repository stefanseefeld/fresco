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
#ifndef _GadgetKitImpl_hh
#define _GadgetKitImpl_hh

#include <Warsaw/config.hh>
#include <Warsaw/GadgetKit.hh>
#include <Warsaw/CommandKit.hh>
#include <Warsaw/FigureKit.hh>
#include <Berlin/KitImpl.hh>
#include <vector>

class GraphicImpl;

class GadgetKitImpl : public virtual POA_GadgetKit, public KitImpl
{
 public:
  GadgetKitImpl(KitFactory *, const PropertySeq &);
  virtual ~GadgetKitImpl();
  virtual void bind(ServerContext_ptr);
  virtual Graphic_ptr rgb(Graphic_ptr, BoundedValue_ptr, BoundedValue_ptr, BoundedValue_ptr);
  virtual Graphic_ptr alpha(Graphic_ptr, BoundedValue_ptr);
  virtual Graphic_ptr lighting(Graphic_ptr, BoundedValue_ptr, BoundedValue_ptr, BoundedValue_ptr);
  virtual Graphic_ptr rotator(Graphic_ptr, BoundedValue_ptr, Axis);
  virtual Graphic_ptr zoomer(Graphic_ptr, BoundedValue_ptr);
 private:
  CommandKit_var command;
  FigureKit_var figure;
  vector<PortableServer::Servant> gadgets;
};

#endif /* _GadgetKitImpl_hh */
