/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Graydon Hoare <graydon@fresco.org> 
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@fresco.org> 
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

#include <Fresco/config.hh>
#include <Fresco/LayoutKit.hh>
#include <Fresco/Server.hh>
#include <Fresco/resolve.hh>
#include <Fresco/Trigger.hh>
#include <Fresco/MainController.hh>
#include <Fresco/Command.hh>
#include <Fresco/Viewport.hh>
#include <Fresco/Selection.hh>
#include <Berlin/CommandImpl.hh>
#include "WidgetKit.hh"
#include "Gauge.hh"
#include "Slider.hh"
#include "Panner.hh"
#include "Scrollbar.hh"
#include "Choice.hh"
#include "Terminal.hh"
// #include "Splitter.hh"

using namespace Fresco;
using namespace Widget;

namespace Motif
{

class Forward : public CommandImpl
{
public:
  Forward(BoundedRange_ptr m) : model(RefCount_var<BoundedRange>::increment(m)) {}
  virtual void execute(const CORBA::Any &) { model->forward();}
private:
  RefCount_var<BoundedRange> model;
};

class Backward : public CommandImpl
{
public:
  Backward(BoundedRange_ptr m) : model(RefCount_var<BoundedRange>::increment(m)) {}
  virtual void execute(const CORBA::Any &) { model->backward();}
private:
  RefCount_var<BoundedRange> model;
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

WidgetKit::WidgetKit(const std::string &id, const Fresco::Kit::PropertySeq &p)
  : KitImpl(id, p) {}
WidgetKit::~WidgetKit() {}

void WidgetKit::bind(ServerContext_ptr context)
{
  KitImpl::bind(context);
  Fresco::Kit::PropertySeq props;
  props.length(0);
  my_commands = resolve_kit<CommandKit>(context, "IDL:fresco.org/Fresco/CommandKit:1.0", props);
  my_layout = resolve_kit<LayoutKit>(context, "IDL:fresco.org/Fresco/LayoutKit:1.0", props);
  my_tools = resolve_kit<ToolKit>(context, "IDL:fresco.org/Fresco/ToolKit:1.0", props);
  my_text = resolve_kit<TextKit>(context, "IDL:fresco.org/Fresco/TextKit:1.0", props);

  Fresco::ToolKit::FrameSpec in, out;
  in.brightness(0.5); in._d(Fresco::ToolKit::inset);
  out.brightness(0.5); out._d(Fresco::ToolKit::outset);

  my_strut = my_layout->fixed_size(Fresco::Graphic::_nil(), 80., 80.);
  my_in_square = my_tools->frame(my_strut, 20., in, true);
  my_out_square = my_tools->frame(my_strut, 20., out, true);
  my_in_diamond = my_tools->diamond(my_strut, 20., in, true);
  my_out_diamond = my_tools->diamond(my_strut, 20., out, true);
  my_up_in_triangle = my_tools->triangle(my_strut, 20., in, true, ToolKit::up);
  my_up_out_triangle = my_tools->triangle(my_strut, 20., out, true, ToolKit::up);
  my_down_in_triangle = my_tools->triangle(my_strut, 20., in, true, ToolKit::down);
  my_down_out_triangle = my_tools->triangle(my_strut, 20., out, true, ToolKit::down);
  my_left_in_triangle = my_tools->triangle(my_strut, 20., in, true, ToolKit::left);
  my_left_out_triangle = my_tools->triangle(my_strut, 20., out, true, ToolKit::left);
  my_right_in_triangle = my_tools->triangle(my_strut, 20., in, true, ToolKit::right);
  my_right_out_triangle = my_tools->triangle(my_strut, 20., out, true, ToolKit::right);
}

Trigger_ptr WidgetKit::button(Graphic_ptr g, Command_ptr c)
{
  Trigger_var trigger = my_tools->button(g, c);
  Fresco::ToolKit::FrameSpec s1, s2;
  s1.brightness(0.5); s1._d(Fresco::ToolKit::inset);
  Graphic_var inset = my_tools->frame(g, 20, s1, true);
  s2.brightness(0.5); s2._d(Fresco::ToolKit::outset);
  Graphic_var outset = my_tools->frame(g, 20, s2, true);
  Graphic_var frame = my_tools->create_switch(inset, outset, Fresco::Controller::pressed, trigger);
  trigger->body(frame);
  return trigger._retn();
}

Controller_ptr WidgetKit::toggle(Graphic_ptr g)
{
  Controller_var toggle = my_tools->toggle(Fresco::Graphic::_nil());
  Fresco::ToolKit::FrameSpec s1, s2;
  s1.brightness(0.5); s1._d(ToolKit::inset);
  Graphic_var inset = my_tools->frame(g, 20, s1, true);
  s2.brightness(0.5); s2._d(ToolKit::outset);
  Graphic_var outset = my_tools->frame(g, 20, s2, true);
  Graphic_var frame = my_tools->create_switch(inset, outset, Fresco::Controller::toggled, toggle);
  toggle->body(frame);
  return toggle._retn();
}

Graphic_ptr WidgetKit::gauge(BoundedValue_ptr value)
{
  Color gray = {0.5, 0.5, 0.5, 1.0};
  Gauge *g = new Gauge(value, gray);
  activate(g);
  value->attach(Observer_var(g->_this()));

  Fresco::ToolKit::FrameSpec spec;
  spec.brightness(0.5); spec._d(Fresco::ToolKit::outset);

  Graphic_var frame = my_tools->frame(Graphic_var(g->_this()), 20., spec, false);
  return frame._retn();
}

Controller_ptr WidgetKit::slider(BoundedValue_ptr value, Axis axis)
{
  Fresco::ToolKit::FrameSpec spec;
  /*
   * the bar
   */
  Fresco::Graphic::Requirement fixed;
  Fresco::Graphic::Requirement flexible;
  flexible.defined = true;
  flexible.minimum = 2000.;
  flexible.natural = 2000.;
  flexible.maximum = 2000.;
  flexible.align = 0.;
  fixed.defined = true;
  fixed.minimum = 120.;
  fixed.natural = 120.;
  fixed.maximum = 120.;
  fixed.align = 0.;
  Fresco::Graphic::Requisition req;
  if (axis == xaxis)
    {
      req.x = flexible;
      req.y = fixed;
      req.z.defined = false;
      req.preserve_aspect = false;
    }
  else
    {
      req.x = fixed;
      req.y = flexible;
      req.z.defined = false;
      req.preserve_aspect = false;
    }
  // FIXME: What happens if the axis == zaxis? Throw an exception since it
  //        is a stupid idea to request it? -- tobias
  Slider *slider = new Slider(value, axis, req);
  activate(slider);
  /*
   * the thumb
   */
  Graphic_var box = axis == xaxis ? my_layout->hbox() : my_layout->vbox();
  spec.brightness(0.5); spec._d(Fresco::ToolKit::outset);
  box->append_graphic(Graphic_var(my_tools->frame(my_strut, 20., spec, true)));
  box->append_graphic(Graphic_var(my_tools->frame(my_strut, 20., spec, true)));
  Controller_var thumb = my_tools->dragger(box, Command_var(slider->create_adjust_cmd()));
  slider->init(thumb);
  /*
   * now put it into an inset
   */
  spec.brightness(0.5); spec._d(Fresco::ToolKit::inset);
  Graphic_var inset = my_tools->frame(Graphic_var(slider->_this()), 20., spec, false);
  Controller_var root = my_tools->group(Graphic_var(my_layout->align_axis(inset, axis == xaxis ? yaxis : xaxis, 1.0)));
  /*
   * now wire up the control structure
   */
  root->append_controller(Controller_var(slider->_this()));
  return root._retn();
}

Controller_ptr WidgetKit::panner(BoundedRange_ptr x, BoundedRange_ptr y)
{
  Panner *panner = new Panner(x, y);
  activate(panner);
  Fresco::ToolKit::FrameSpec spec;
  spec.brightness(0.5); spec._d(Fresco::ToolKit::outset);
  Graphic_var outset = my_tools->frame(Fresco::Graphic::_nil(), 20., spec, true);
  Controller_var thumb = my_tools->dragger(outset, Command_var(panner->create_adjust_cmd()));
  panner->init(thumb);

  spec.brightness(0.5); spec._d(Fresco::ToolKit::inset);
  Graphic_var fixed = my_layout->fixed_size(Graphic_var(panner->_this()), 1000., 1000.);
  Graphic_var inset = my_tools->frame(fixed, 20., spec, true);
  Controller_var root = my_tools->group(inset);
  /*
   * now wire up the control structure
   */
  root->append_controller(Controller_var(panner->_this()));
  return root._retn();
}

Controller_ptr WidgetKit::scrollbar(BoundedRange_ptr x, Axis a)
{
  Fresco::ToolKit::FrameSpec spec;
  /*
   * the bar
   */
  Fresco::Graphic::Requirement fixed;
  Fresco::Graphic::Requirement flexible;
  flexible.defined = true;
  flexible.minimum = 0.;
  flexible.natural = 0.;
  flexible.maximum = my_layout->fill();
  flexible.align = 0.;
  fixed.defined = true;
  fixed.minimum = 120.;
  fixed.natural = 120.;
  fixed.maximum = 120.;
  fixed.align = 0;
  Fresco::Graphic::Requisition req;
  if (a == xaxis)
    {
      req.x = flexible;
      req.y = fixed;
      req.z.defined = false;
      req.preserve_aspect = false;
    }
  else
    {
      req.x = fixed;
      req.y = flexible;
      req.z.defined = false;
      req.preserve_aspect = false;
    }
  // FIXME: Again, what happens with axis==zaxis? -- tobias
  Scrollbar *scrollbar = new Scrollbar(x, a, req);
  activate(scrollbar);
  /*
   * the thumb
   */
  spec.brightness(0.5); spec._d(Fresco::ToolKit::outset);
  Graphic_var f = my_tools->frame(Fresco::Graphic::_nil(), 20., spec, true);
  Controller_var thumb = my_tools->dragger(f, Command_var(scrollbar->create_adjust_cmd()));
  scrollbar->init(thumb);
  /*
   * the triangles
   */
  CommandImpl *backward = new Backward(x);
  activate(backward);
  Controller_var lower = my_tools->stepper(Graphic::_nil(), Command_var(backward->_this()));

  CommandImpl *forward = new Forward(x);
  activate(forward);
  Controller_var upper = my_tools->stepper(Graphic::_nil(), Command_var(forward->_this()));

  Graphic_var lower_triangle, upper_triangle;
  if (a == xaxis)
  {
    lower_triangle = my_tools->create_switch(my_left_in_triangle, my_left_out_triangle, Fresco::Controller::pressed, lower);
    upper_triangle = my_tools->create_switch(my_right_in_triangle, my_right_out_triangle, Fresco::Controller::pressed, upper);
  }
  else // assume yaxis
  {
    lower_triangle = my_tools->create_switch(my_up_in_triangle, my_up_out_triangle, Fresco::Controller::pressed, lower);
    upper_triangle = my_tools->create_switch(my_down_in_triangle, my_down_out_triangle, Fresco::Controller::pressed, upper);
  }

  lower->body(lower_triangle);
  upper->body(upper_triangle);

  Graphic_var box = a == xaxis ? my_layout->hbox() : my_layout->vbox();
  box->append_graphic(lower);
  box->append_graphic(Controller_var(scrollbar->_this()));
  box->append_graphic(upper);
  /*
   * now put it into an inset
   */
  spec.brightness(0.5); spec._d(Fresco::ToolKit::inset);
  Graphic_var inset = my_tools->frame(box, 20., spec, false);
  Controller_var root = my_tools->group(inset);
  /*
   * now wire up the control structure
   */
  root->append_controller(lower);
  root->append_controller(Controller_var(scrollbar->_this()));
  root->append_controller(upper);
  return root._retn();
}

Choice_ptr WidgetKit::toggle_choice()
{
  RefCount_var<Selection> selection = my_commands->group(Selection::exclusive);
  Choice *choice = new ToggleChoice(selection, my_in_square, my_out_square,
				    my_layout, my_tools);
  activate(choice);
  choice->body(Graphic_var(my_layout->vbox()));
  return choice->_this();
}

Choice_ptr WidgetKit::checkbox_choice()
{
  RefCount_var<Selection> selection = my_commands->group(0);
  Choice *choice = new CheckboxChoice(selection, my_in_diamond, my_out_diamond,
				      my_layout, my_tools);
  activate(choice);
  choice->body(Graphic_var(my_layout->vbox()));
  return choice->_this();
}

Choice_ptr WidgetKit::toolbar()
{
  RefCount_var<Selection> selection = my_commands->group(Selection::exclusive|Selection::required);
  Choice *choice = new ToolChoice(selection, my_layout, my_tools);
  activate(choice);
  choice->body(Graphic_var(my_layout->vbox()));
  return choice->_this();
}

Controller_ptr WidgetKit::terminal()
{
  Terminal *terminal = new Terminal(my_commands);
  activate(terminal);
  Graphic_var view = my_text->terminal(StreamBuffer_var(terminal->output()));
  terminal->body(view);
  Controller_var input = my_tools->terminal(Graphic_var(terminal->_this()), StreamBuffer_var(terminal->input()));
//   input->appendController(Controller_var(terminal->_this()));
  return input._retn();
}

// Widget::Splitter_ptr WidgetKit::splitter(Graphic_ptr left, Graphic_ptr right, Axis a)
// {
//   BoundedValue_var adjustment = my_commands->bvalue(0., 1., 0., 0.01, 0.1);
//   Splitter *splitter = new Splitter(adjustment, a);
//   activate(splitter);
//   /*
//    * the thumb
//    */
//   Fresco::ToolKit::FrameSpec spec;  
//   spec.brightness(0.5); spec._d(Fresco::ToolKit::outset);
//   Graphic_var quad = my_tools->frame(Graphic_var(_layout->fixed_size(Fresco::Graphic::_nil(), 80., 80.)), 20., spec, true);
//   Controller_var thumb = my_tools->dragger(quad, Command_var(splitter->create_adjust_cmd()));
//   splitter->init(thumb, left, right);
//   return splitter->_this();
// }

Controller_ptr WidgetKit::scrollable(Graphic_ptr g)
{
  Layout::Viewport_var viewport = my_layout->scrollable(g);
  Controller_var xscroller = scrollbar(viewport->adjustment(xaxis), xaxis);
  Controller_var yscroller = scrollbar(viewport->adjustment(yaxis), yaxis);
  Graphic_var hbox1 = my_layout->hbox();
  Fresco::ToolKit::FrameSpec inset;
  inset.brightness(0.5); inset._d(Fresco::ToolKit::inset);
  hbox1->append_graphic(Graphic_var(my_tools->frame(viewport, 20, inset, false)));
  hbox1->append_graphic(yscroller);
  Graphic_var hbox2 = my_layout->hbox();
  hbox2->append_graphic(xscroller);
  hbox2->append_graphic(Graphic_var(my_layout->fixed_size(Fresco::Graphic::_nil(), 160., 160.)));
  Graphic_var vbox = my_layout->vbox();
  vbox->append_graphic(hbox1);
  vbox->append_graphic(hbox2);
  Controller_var group = my_tools->group(vbox);
  group->append_controller(xscroller);
  group->append_controller(yscroller);
  return group._retn();
}

};

extern "C" KitImpl *load()
{
  static std::string properties[] = {"implementation", "Motif::WidgetKit", "style", "Motif"};
  return create_kit<Motif::WidgetKit> ("IDL:fresco.org/Fresco/WidgetKit:1.0", properties, 4);
}
