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
#include "Warsaw/Command.hh"
#include "Widget/Motif/WidgetKit.hh"
#include "Widget/Motif/Gauge.hh"
#include "Widget/Motif/Slider.hh"
#include "Widget/Motif/Panner.hh"
#include "Widget/Motif/Scrollbar.hh"
#include "Widget/Motif/Choice.hh"

namespace Motif
{

WidgetKit::WidgetKit(KitFactory *f, const PropertySeq &p) : KitImpl(f, p) {}
WidgetKit::~WidgetKit() {}

template <class Observer>
class Adapter0 : public WidgetKit::CommandImpl
{
public:
  typedef void (Observer::*Method)();
  Adapter0(typename Observer::_ptr_type o, Method m) : observer(o), method(m) {}
  virtual void execute(const CORBA::Any &) { (observer->*method)();}
private:
  typename Observer::_ptr_type observer;
  Method method;
};

// template <class Observer, class Argument>
// class Adapter1 : public WidgetKit::CommandImpl
// {
// public:
//   typedef void (Observer::*Method)();
//   Adapter1(typename Observer::_ptr_type o, Method m) : observer(o), method(m) {}
//   virtual void execute(const CORBA::Any &) { (observer->*method)();}
// private:
//   typename Observer::_ptr_type observer;
//   Method method;
// };

void WidgetKit::bind(ServerContext_ptr context)
{
  KitImpl::bind(context);
  PropertySeq props;
  props.length(0);
  command = resolve_kit<CommandKit>(context, interface(CommandKit), props);
  layout = resolve_kit<LayoutKit>(context, interface(LayoutKit), props);
  tool = resolve_kit<ToolKit>(context, interface(ToolKit), props);
}

Trigger_ptr WidgetKit::button(Graphic_ptr g, Command_ptr c)
{
  Trigger_var trigger = tool->button(g, c);
  ToolKit::FrameSpec s1, s2;
  s1.abrightness(0.5);
  s2.bbrightness(0.5);
  Graphic_var frame = tool->dynamic(g, 20., Controller::pressed, s1, s2, true, trigger);
  trigger->body(frame);
  return trigger._retn();
}

Controller_ptr WidgetKit::toggle(Graphic_ptr g)
{
  Controller_var toggle = tool->toggle(Graphic_var(Graphic::_nil()));
  ToolKit::FrameSpec s1, s2;
  s1.abrightness(0.5);
  s2.bbrightness(0.5);
  Graphic_var frame = tool->dynamic(g, 20., Controller::toggled, s1, s2, true, toggle);
  toggle->body(frame);
  return toggle._retn();
}

Graphic_ptr WidgetKit::gauge(BoundedValue_ptr value)
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

Controller_ptr WidgetKit::slider(BoundedValue_ptr value, Axis axis)
{
  ToolKit::FrameSpec spec;
  /*
   * the bar
   */
  Graphic::Requirement fixed;
  Graphic::Requirement flexible;
  flexible.defined = true;
  flexible.minimum = 2000.;
  flexible.natural = 2000.;
  flexible.maximum = 2000.;
  flexible.align = 0.;
  fixed.defined = true;
  fixed.minimum = 120.;
  fixed.natural = 120.;
  fixed.maximum = 120.;
  fixed.align = 0;
  Graphic::Requisition req;
  if (axis == xaxis) req.x = flexible, req.y = fixed;
  else               req.x = fixed, req.y = flexible;
  Slider *slider = new Slider(value, axis, req);
  slider->_obj_is_ready(_boa());
  /*
   * the thumb
   */
  Graphic_var box = axis == xaxis ? layout->hbox() : layout->vbox();
  spec.bbrightness(0.5);
  Graphic_var quad = layout->fixedSize(Graphic_var(Graphic::_nil()), 80., 80.);
  box->append(Graphic_var(tool->frame(quad, 20., spec, true)));
  box->append(Graphic_var(tool->frame(quad, 20., spec, true)));
  Controller_var thumb = tool->dragger(box, Command_var(slider->drag()));
  slider->init(thumb);
  /*
   * now put it into an inset
   */
  spec.abrightness(0.5);
  Graphic_var inset = tool->frame(box, 20., spec, false);
  Controller_var root = tool->group(inset);
  /*
   * now wire up the control structure
   */
  root->appendController(Controller_var(slider->_this()));
  return root._retn();
}

Controller_ptr WidgetKit::panner(BoundedRange_ptr x, BoundedRange_ptr y)
{
  Panner *panner = new Panner(x, y);
  panner->_obj_is_ready(_boa());
  ToolKit::FrameSpec spec;
  spec.abrightness(0.5);
  Graphic_var fixed = layout->fixedSize(Graphic_var(Graphic::_nil()), 1000., 1000.);
  Graphic_var inset = tool->frame(fixed, 20., spec, true);
  panner->body(inset);
  spec.bbrightness(0.5);
  Graphic_var outset = tool->frame(Graphic_var(Graphic::_nil()), 20., spec, true);
  Controller_var thumb = tool->dragger(outset, Command_var(panner->drag()));
  panner->init(thumb);
  return panner->_this();
}

Controller_ptr WidgetKit::scrollbar(BoundedRange_ptr x, Axis a)
{
  ToolKit::FrameSpec spec;
  /*
   * the bar
   */
  Graphic::Requirement fixed;
  Graphic::Requirement flexible;
  flexible.defined = true;
  flexible.minimum = 0.;
  flexible.natural = 0.;
  flexible.maximum = layout->fil();
  flexible.align = 0.;
  fixed.defined = true;
  fixed.minimum = 120.;
  fixed.natural = 120.;
  fixed.maximum = 120.;
  fixed.align = 0;
  Graphic::Requisition req;
  if (a == xaxis) req.x = flexible, req.y = fixed;
  else            req.x = fixed, req.y = flexible;
  Scrollbar *scrollbar = new Scrollbar(x, a, req);
  scrollbar->_obj_is_ready(_boa());
  /*
   * the thumb
   */
  spec.bbrightness(0.5);
  Graphic_var outset = tool->frame(Graphic_var(Graphic::_nil()), 20., spec, true);
  Controller_var thumb = tool->dragger(outset, Command_var(scrollbar->drag()));
  scrollbar->init(thumb);
  /*
   * the triangles
   */
  ToolKit::FrameSpec in, out;
  in.abrightness(0.5);
  out.bbrightness(0.5);
  CommandImpl *backward = new Adapter0<BoundedRange>(x, &BoundedRange::backward);
  backward->_obj_is_ready(_boa());
  commands.push_back(backward);
  Controller_var lower = tool->stepper(Graphic_var(Graphic::_nil()), Command_var(backward->_this()));
  outset = layout->fixedSize(Graphic_var(tool->dynamicTriangle(Graphic_var(Graphic::_nil()), 20.,
							       Controller::pressed, in, out, true,
							       a == xaxis ? ToolKit::left : ToolKit::up, lower)), 120., 120.);
  lower->body(outset);

  CommandImpl *forward = new Adapter0<BoundedRange>(x, &BoundedRange::forward);
  forward->_obj_is_ready(_boa());
  commands.push_back(forward);
  Controller_var upper = tool->stepper(Graphic_var(Graphic::_nil()), Command_var(forward->_this()));
  outset = layout->fixedSize(Graphic_var(tool->dynamicTriangle(Graphic_var(Graphic::_nil()), 20.,
							       Controller::pressed, in, out, true,
							       a == xaxis ? ToolKit::right : ToolKit::down, upper)), 120., 120.);
  upper->body(outset);

  Graphic_var box = a == xaxis ? layout->hbox() : layout->vbox();
  box->append(lower);
  box->append(Controller_var(scrollbar->_this()));
  box->append(upper);
  /*
   * now put it into an inset
   */
  spec.abrightness(0.5);
  Graphic_var inset = tool->frame(box, 20., spec, false);
  Controller_var root = tool->group(inset);
  /*
   * now wire up the control structure
   */
  root->appendController(lower);
  root->appendController(Controller_var(scrollbar->_this()));
  root->appendController(upper);
  return root._retn();
}

Choice_ptr WidgetKit::toggleChoice()
{
  Choice *choice = new ToggleChoice(Choice::exclusive, command, layout, tool, WidgetKit_var(_this()));
  choice->_obj_is_ready(_boa());
  choice->body(Graphic_var(layout->vbox()));
  graphics.push_back(choice);
  return choice->_this();
}

Choice_ptr WidgetKit::checkboxChoice()
{
  Choice *choice = new CheckboxChoice(Choice::exclusive, command, layout, tool, WidgetKit_var(_this()));
  choice->_obj_is_ready(_boa());
  choice->body(Graphic_var(layout->vbox()));
  graphics.push_back(choice);
  return choice->_this();
}

};

extern "C" KitFactory *load()
{
  static string properties[] = {"implementation", "Motif::WidgetKit", "style", "Motif"};
  return new KitFactoryImpl<Motif::WidgetKit> (interface(WidgetKit), properties, 2);
}
