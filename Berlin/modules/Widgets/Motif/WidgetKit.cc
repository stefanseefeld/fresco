/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Graydon Hoare <graydon@pobox.com> 
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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

#include "Warsaw/config.hh"
#include "Warsaw/LayoutKit.hh"
#include "Warsaw/Server.hh"
#include "Warsaw/resolve.hh"
#include "Warsaw/Trigger.hh"
#include "Widget/Motif/WidgetKit.hh"
#include "Widget/Motif/Gauge.hh"
// #include "Widget/Motif/Slider.hh"
#include "Widget/Motif/Panner.hh"
#include "Widget/Motif/Scrollbar.hh"

using namespace Motif;

Motif::WidgetKit::WidgetKit(KitFactory *f, const PropertySeq &p) : KitImpl(f, p) {}
Motif::WidgetKit::~WidgetKit() {}

void Motif::WidgetKit::bind(ServerContext_ptr context)
{
  KitImpl::bind(context);
  PropertySeq props;
  props.length(0);
  layout = resolve_kit<LayoutKit>(context, interface(LayoutKit), props);
  tool = resolve_kit<ToolKit>(context, interface(ToolKit), props);
}

Trigger_ptr Motif::WidgetKit::button(Graphic_ptr g, Command_ptr c)
{
  Trigger_var trigger = tool->button(g, c);
  ToolKit::FrameSpec s1, s2;
  s1.abrightness(0.5);
  s2.bbrightness(0.5);
  Graphic_var frame = tool->dynamic(g, 20., Telltale::toggle, s1, s2, true, trigger);
  trigger->body(frame);
  return trigger._retn();
}

Controller_ptr Motif::WidgetKit::toggle(Graphic_ptr g)
{
  Controller_var toggle = tool->toggle(g);
  ToolKit::FrameSpec s1, s2;
  s1.abrightness(0.5);
  s2.bbrightness(0.5);
  Graphic_var frame = tool->dynamic(g, 20., Telltale::chosen, s1, s2, true, toggle);
  toggle->body(frame);
  return toggle._retn();
}

Graphic_ptr Motif::WidgetKit::gauge(BoundedValue_ptr value)
{
  Color gray = {0.5, 0.5, 0.5, 1.0};
  Gauge *g = new Gauge(value, gray);
  g->_obj_is_ready(_boa());
  value->attach(g);
  graphics.push_back(g);

  ToolKit::FrameSpec spec;
  spec.abrightness(0.5);

  Graphic_var frame = tool->frame(Graphic_var(g->_this()), 20., spec, false);
  return frame._retn();
}

Controller_ptr Motif::WidgetKit::slider(BoundedValue_ptr value)
{
//   Graphic::Requisition req;
//   req.x.defined = true;
//   req.x.minimum = 100.;
//   req.x.natural = 100.;
//   req.x.maximum = 100.;
//   req.x.align = 0.;
//   req.y.defined = true;
//   req.y.minimum = 100.;
//   req.y.natural = 100.;
//   req.y.maximum = 100.;
//   req.y.align = 0;
//   Controller_var thumb;// = dragger(Graphic_var(outset(lk->glueRequisition(req), color, true)));
//   Slider1D *s = new Slider1D(xaxis);
//   s->_obj_is_ready(_boa());
//   s->init(thumb, value);
//   req.x.minimum = 100.;
//   req.x.natural = 100.;
//   req.x.maximum = 100.;
//   req.x.align = 0.;
//   req.y.minimum = 12.;
//   req.y.natural = 12.;
//   req.y.maximum = 12.;
//   req.y.align = 0;
// //   s->body(Graphic_var(tool->inset(Graphic_var(layout->glueRequisition(req)), color, true)));
//   graphics.push_back(s);
//   return s->_this();
  return Controller::_nil();
}

Controller_ptr Motif::WidgetKit::panner(BoundedRange_ptr x, BoundedRange_ptr y)
{
  Panner *panner = new Panner(x, y);
  panner->_obj_is_ready(_boa());
  ToolKit::FrameSpec spec1;
  spec1.abrightness(0.5);
  Graphic_var fixed = layout->fixedSize(Graphic_var(Graphic::_nil()), 1000., 1000.);
  Graphic_var inset = tool->frame(fixed, 20., spec1, true);
  panner->body(inset);
  ToolKit::FrameSpec spec2;
  spec1.bbrightness(0.5);
  Graphic_var outset = tool->frame(Graphic_var(Graphic::_nil()), 20., spec2, true);
  Controller_var thumb = tool->dragger(outset, Command_var(panner->drag()));
  panner->init(thumb);
  return panner->_this();
}

Controller_ptr Motif::WidgetKit::scrollbar(BoundedRange_ptr x, Axis a)
{
  Scrollbar *scrollbar = new Scrollbar(x, a);
  scrollbar->_obj_is_ready(_boa());
  Graphic::Requirement fixed;
  Graphic::Requirement flexible;
  flexible.defined = true;
  flexible.minimum = 0.;
  flexible.natural = 0.;
  flexible.maximum = layout->fil();
  flexible.align = 0.;
  fixed.defined = true;
  fixed.minimum = 200.;
  fixed.natural = 200.;
  fixed.maximum = 200.;
  fixed.align = 0;
  Graphic::Requisition req;
  if (a == xaxis) req.x = flexible, req.y = fixed;
  else            req.x = fixed, req.y = flexible;
  ToolKit::FrameSpec spec1;
  spec1.abrightness(0.5);
  Graphic_var inset = tool->frame(Graphic_var(layout->glueRequisition(req)), 20., spec1, true);
  scrollbar->body(inset);
  ToolKit::FrameSpec spec2;
  spec2.bbrightness(0.5);
  Graphic_var outset = tool->frame(Graphic_var(Graphic::_nil()), 20., spec2, true);
  Controller_var thumb = tool->dragger(outset, Command_var(scrollbar->drag()));
  scrollbar->init(thumb);
  return scrollbar->_this();
}

extern "C" KitFactory *load()
{
  static string properties[] = {"implementation", "Motif::WidgetKit", "style", "Motif"};
  return new KitFactoryImpl<Motif::WidgetKit> (interface(WidgetKit), properties, 2);
}
