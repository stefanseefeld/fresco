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
#include "Gadget/GadgetKitImpl.hh"
#include <Warsaw/View.hh>
#include <Warsaw/Transform.hh>
#include <Warsaw/DrawingKit.hh>
#include <Warsaw/BoundedValue.hh>
#include <Warsaw/DrawTraversal.hh>
#include <Warsaw/PickTraversal.hh>
#include <Warsaw/resolve.hh>
#include <Berlin/MonoGraphic.hh>

class AlphaAdjuster : implements(View), public MonoGraphic
{
 public:
  virtual void traverse(Traversal_ptr traversal) { traversal->visit(Graphic_var(_this()));}
  virtual void draw(DrawTraversal_ptr traversal)
  {
    DrawingKit_var kit = traversal->kit();
    kit->saveState();
    Color color = kit->foreground();
    color.alpha *= alpha;
    kit->foreground(color);
    MonoGraphic::traverse(traversal);
    kit->restoreState();    
  }
  virtual void pick(PickTraversal_ptr traversal) { MonoGraphic::traverse(traversal);}

  virtual void update(const CORBA::Any &any) { any >>= alpha; needRedraw();}
 private:
  Coord alpha;
};

class TransformAdjuster : implements(View), public MonoGraphic
{
 public:
  virtual void update(const CORBA::Any &any)
    {
      Graphic_var child = body(); if (CORBA::is_nil(child)) return;
      Transform_var transformation = child->transformation(); if (CORBA::is_nil(transformation)) return;
      Coord phi;
      any >>= phi;
      transformation->loadIdentity();
      transformation->rotate(phi, zaxis);
      needResize();
    }
};

GadgetKitImpl::GadgetKitImpl(KitFactory *f, const PropertySeq &p) : KitImpl(f, p) {}
GadgetKitImpl::~GadgetKitImpl() {}
void GadgetKitImpl::bind(ServerContext_ptr context)
{
  KitImpl::bind(context);
  PropertySeq props;
  props.length(0);
  command = resolve_kit<CommandKit>(context, interface(CommandKit), props);
  figure = resolve_kit<FigureKit>(context, interface(FigureKit), props);
}

Graphic_ptr GadgetKitImpl::alpha(Graphic_ptr g, BoundedValue_ptr value)
{
  AlphaAdjuster *adjuster = new AlphaAdjuster;
  adjuster->_obj_is_ready(_boa());
  value->attach(Observer_var(adjuster->_this()));
  adjuster->body(g);
  return adjuster->_this();
}

Graphic_ptr GadgetKitImpl::transformer(Graphic_ptr g, BoundedValue_ptr value)
{
  TransformAdjuster *adjuster = new TransformAdjuster;
  adjuster->_obj_is_ready(_boa());
  value->attach(Observer_var(adjuster->_this()));
  Graphic_var transformer = figure->projection(g);
  adjuster->body(transformer);
  return adjuster->_this();
}

extern "C" KitFactory *load()
{
  static string properties[] = {"implementation", "GadgetKitImpl"};
  return new KitFactoryImpl<GadgetKitImpl>(interface(GadgetKit), properties, 1);
} 
