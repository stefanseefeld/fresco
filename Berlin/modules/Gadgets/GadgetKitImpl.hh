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
#ifndef _GadgetKitImpl_hh
#define _GadgetKitImpl_hh

#include <Fresco/config.hh>
#include <Fresco/GadgetKit.hh>
#include <Fresco/CommandKit.hh>
#include <Fresco/FigureKit.hh>
#include <Berlin/KitImpl.hh>
#include <vector>

class GraphicImpl;

class GadgetKitImpl : public virtual POA_Fresco::GadgetKit,
		      public KitImpl
{
 public:
  GadgetKitImpl(const std::string &, const Fresco::Kit::PropertySeq &);
  virtual ~GadgetKitImpl();
  virtual KitImpl *clone(const Fresco::Kit::PropertySeq &p) { return new GadgetKitImpl(repo_id(), p);}
  virtual void bind(Fresco::ServerContext_ptr);
  virtual Fresco::Graphic_ptr rgb(Fresco::Graphic_ptr, Fresco::BoundedValue_ptr, Fresco::BoundedValue_ptr, Fresco::BoundedValue_ptr);
  virtual Fresco::Graphic_ptr alpha(Fresco::Graphic_ptr, Fresco::BoundedValue_ptr);
  virtual Fresco::Graphic_ptr lighting(Fresco::Graphic_ptr, Fresco::BoundedValue_ptr, Fresco::BoundedValue_ptr, Fresco::BoundedValue_ptr);
  virtual Fresco::Graphic_ptr rotator(Fresco::Graphic_ptr, Fresco::BoundedValue_ptr, Fresco::Axis);
  virtual Fresco::Graphic_ptr zoomer(Fresco::Graphic_ptr, Fresco::BoundedValue_ptr);
 private:
  Fresco::CommandKit_var _command;
  Fresco::FigureKit_var  _figure;
};

#endif
