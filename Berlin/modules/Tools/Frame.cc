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

#include "Tool/Frame.hh"
#include "Tool/Beveler.hh"
#include <Warsaw/DrawTraversal.hh>
#include <Warsaw/DrawingKit.hh>
#include <Warsaw/Subject.hh>
#include <Berlin/TransformImpl.hh>
#include <Berlin/RegionImpl.hh>
#include <Berlin/Providers.hh>
#include <Berlin/ImplVar.hh>
#include <Berlin/Color.hh>
#include <Prague/Sys/Tracer.hh>

using namespace Prague;

Frame::Frame(Coord t, Frame::Renderer *r)
  : thickness(t), renderer(r)
{
  allocation = new RegionImpl;
  allocation->_obj_is_ready(_boa());
}

Frame::~Frame()
{
  allocation->_dispose();
}

void Frame::request(Requisition &requisition)
{
  MonoGraphic::request(requisition);
  Coord t = thickness + thickness;
  if (requisition.x.defined)
    {
      requisition.x.natural += t;
      requisition.x.maximum += t;
      requisition.x.minimum += t;
    }
  if (requisition.y.defined)
    {
      requisition.y.natural += t;
      requisition.y.maximum += t;
      requisition.y.minimum += t;
    }
}

void Frame::traverse(Traversal_ptr traversal)
{
  Trace trace("Frame::traverse");
  if (!traversal->intersectsAllocation()) return;
  traversal->visit(Graphic_var(_this()));
  Graphic_var child = body();
  if (!CORBA::is_nil(child))
    {
      Lease<RegionImpl> allocation;
      Providers::region.provide(allocation);
      allocation->copy(traversal->allocation());

      Lease<TransformImpl> tx;
      Providers::trafo.provide(tx);
      tx->loadIdentity();

      Allocation::Info info;
      info.allocation = allocation->_this();
      info.transformation = tx->_this();
      allocate(0, info);
      traversal->traverseChild(child, 0, info.allocation, info.transformation);
    }
}

void Frame::extension(const Allocation::Info &info, Region_ptr region)
{
  if (!CORBA::is_nil(info.allocation)) defaultExtension(info, region);
  else MonoGraphic::extension(info, region);
}

void Frame::allocate(Tag, const Allocation::Info &info)
{
  Requisition req;
  GraphicImpl::initRequisition(req);
  MonoGraphic::request(req);
  allocation->valid = true;
  Region::Allotment a;
  /*
   * same as Placement::normalTransform...
   */
  Vertex o;

  Lease<RegionImpl> region;
  Providers::region.provide(region);
  region->copy(info.allocation);

  region->normalize(o);
  info.transformation->translate(o);
  info.allocation->copy(Region_var(region->_this()));
  
  Vertex delta;
  info.allocation->span(xaxis, a);
  allocateSpan(req.x, a, thickness, 0.);
  allocation->lower.x = -(a.end - a.begin) * a.align;
  allocation->upper.x = allocation->lower.x + (a.end - a.begin);
  allocation->xalign = a.align;
  delta.x = a.begin - allocation->lower.x;

  info.allocation->span(yaxis, a);
  allocateSpan(req.y, a, thickness, 0.);
  allocation->lower.y = -(a.end - a.begin) * a.align;
  allocation->upper.y = allocation->lower.y + (a.end - a.begin);
  allocation->yalign = a.align;
  delta.y = a.begin - allocation->lower.y;
  delta.z = 0;
  
  info.allocation->copy(Region_var(allocation->_this()));
  info.transformation->translate(delta);
}

void Frame::allocateSpan(const Requirement &r, Region::Allotment &a, Coord margin, Alignment align)
{
  a.begin += margin;
  a.end -= margin;
}

DynamicFrame::DynamicFrame(Coord t, Telltale::Mask m, Frame::Renderer *r1, Frame::Renderer *r2)
  : Frame(t, r2), renderer1(r1), renderer2(r2), on(true), mask(m)
{
}

DynamicFrame::~DynamicFrame()
{
  if (!CORBA::is_nil(telltale)) telltale->detach(View_var(_this()));
  delete renderer1;
  delete renderer2;
}

void DynamicFrame::attach(Telltale_ptr subject)
{
  if (!CORBA::is_nil(telltale)) telltale->detach(View_var(_this()));
  telltale = Telltale::_duplicate(subject);
  telltale->attach(View_var(_this()));
  bool flag = telltale->test(mask);
  if (flag == on) return;
  on = flag;
  renderer = on ? renderer1 : renderer2;
  needRedraw();
}

void DynamicFrame::update(const CORBA::Any &)
{
  Trace trace("DynamicFrame::update");
  bool flag = telltale->test(mask);
  if (flag == on) return;
  on = flag;
  renderer = on ? renderer1 : renderer2;
  needRedraw();
}

void InvisibleFrame::draw(DrawTraversal_ptr traversal)
{
  Region_var allocation = traversal->allocation();
  Vertex l, u;
  allocation->bounds(l, u);
  DrawingKit_var drawing = traversal->kit();
  DrawingKit::Fillstyle style = drawing->surfaceFillstyle();
  if (style != DrawingKit::outlined && fill) drawing->drawRect(l, u);
  else if (fill)
    {
      drawing->saveState();
      drawing->surfaceFillstyle(DrawingKit::solid);
      drawing->drawRect(l, u);
      drawing->restoreState();
    }
  else
    {
      Vertex ltmp = l, utmp = u;
      utmp.y = ltmp.y + thickness;
      drawing->drawRect(ltmp, utmp);
      ltmp.x = utmp.x - thickness, ltmp.y = utmp.y;
      utmp.y = u.y - thickness;
      drawing->drawRect(ltmp, utmp);
      ltmp.x = l.x, utmp.x = l.x + thickness;
      drawing->drawRect(ltmp, utmp);
      ltmp.y = u.y - thickness;
      utmp = u;
      drawing->drawRect(ltmp, utmp);
    }
}

void Bevel::draw(DrawTraversal_ptr traversal)
{
  Region_var allocation = traversal->allocation();
  Vertex u, l;
  allocation->bounds(l, u);
  DrawingKit_var drawing = traversal->kit();
  Color color = drawing->foreground();
  Color light = brightness(color, bright);
  Color dark  = brightness(color,-bright);
  switch (style)
    {
    case inset:
      Beveler::rect(traversal, thickness, color, dark, light, l.x, u.x, l.y, u.y, fill);
      break;
    case outset:
      Beveler::rect(traversal, thickness, color, light, dark, l.x, u.x, l.y, u.y, fill);
      break;
    case convex:
      Beveler::rect(traversal, thickness/2, color, light, dark, l.x, u.x, l.y, u.y, false);
      l.x += thickness/2, u.x -= thickness/2, l.y += thickness/2, u.y -= thickness/2;
      Beveler::rect(traversal, thickness/2, color, dark, light, l.x, u.x, l.y, u.y, fill);
      break;
    case concav:
      Beveler::rect(traversal, thickness/2, color, dark, light, l.x, u.x, l.y, u.y, false);
      l.x += thickness/2, u.x -= thickness/2, l.y += thickness/2, u.y -= thickness/2;
      Beveler::rect(traversal, thickness/2, color, light, dark, l.x, u.x, l.y, u.y, fill);
      break;
    }
}

void ColoredFrame::draw(DrawTraversal_ptr traversal)
{
  Region_var allocation = traversal->allocation();
  Vertex l, u;
  allocation->bounds(l, u);
  DrawingKit_var drawing = traversal->kit();
  DrawingKit::Fillstyle style = drawing->surfaceFillstyle();
  drawing->saveState();
  drawing->foreground(color);
  if (style == DrawingKit::outlined) drawing->surfaceFillstyle(DrawingKit::solid);
  if (fill) drawing->drawRect(l, u);
  else
    {
      Vertex ltmp = l, utmp = u;
      utmp.y = ltmp.y + thickness;
      drawing->drawRect(ltmp, utmp);
      ltmp.x = utmp.x - thickness, ltmp.y = utmp.y;
      utmp.y = u.y - thickness;
      drawing->drawRect(ltmp, utmp);
      ltmp.x = l.x, utmp.x = l.x + thickness;
      drawing->drawRect(ltmp, utmp);
      ltmp.y = u.y - thickness;
      utmp = u;
      drawing->drawRect(ltmp, utmp);
    }
  drawing->restoreState();
}

