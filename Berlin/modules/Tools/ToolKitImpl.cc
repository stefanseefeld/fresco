/*$Id$
 *
 * This source file is a part of the Berlin Project.
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
#include "Warsaw/Server.hh"
#include "Warsaw/DrawingKit.hh"
#include "Tool/ToolKitImpl.hh"
// #include "Tool/Filler.hh"
// #include "Tool/Indicator.hh"
#include "Tool/Frame.hh"
#include "Tool/Triangle.hh"
#include "Tool/Diamond.hh"
#include "Tool/TriggerImpl.hh"
#include "Tool/Toggle.hh"
#include "Tool/Dragger.hh"
#include "Tool/Stepper.hh"
#include "Tool/TextInput.hh"
#include "Berlin/DebugGraphic.hh"

class RGBDecorator : public MonoGraphic
{
public:
  RGBDecorator(Coord r, Coord g, Coord b) : red(r), green(g), blue(b) {}
  virtual void traverse(Traversal_ptr traversal) { traversal->visit(Graphic_var(_this()));}
  virtual void draw(DrawTraversal_ptr traversal)
  {
    DrawingKit_var kit = traversal->kit();
    kit->saveState();
    Color color = kit->foreground();
    color.red = red, color.green = green, color.blue = blue;
    kit->foreground(color);
    MonoGraphic::traverse(traversal);
    kit->restoreState();    
  }
  virtual void pick(PickTraversal_ptr traversal) { MonoGraphic::traverse(traversal);}
private:
  Coord red, green, blue;
};

class AlphaDecorator : public MonoGraphic
{
public:
  AlphaDecorator(Coord a) : alpha(a) {}
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
private:
  Coord alpha;
};

ToolKitImpl::ToolKitImpl(KitFactory *f, const PropertySeq &p) : KitImpl(f, p) {}
ToolKitImpl::~ToolKitImpl() {}

Graphic_ptr ToolKitImpl::debugger(Graphic_ptr g, const char *s)
{
  DebugGraphic *debug = new DebugGraphic(s);
  debug->_obj_is_ready(_boa());
  graphics.push_back(debug);
  debug->body(g);
  return debug->_this();
};

Graphic_ptr ToolKitImpl::rgb(Graphic_ptr gg, Coord r, Coord g, Coord b)
{
  RGBDecorator *decorator = new RGBDecorator(r, g, b);
  decorator->_obj_is_ready(_boa());
  graphics.push_back(decorator);
  decorator->body(gg);
  return decorator->_this();
};

Graphic_ptr ToolKitImpl::alpha(Graphic_ptr g, Coord a)
{
  AlphaDecorator *decorator = new AlphaDecorator(a);
  decorator->_obj_is_ready(_boa());
  graphics.push_back(decorator);
  decorator->body(g);
  return decorator->_this();
};

Graphic_ptr ToolKitImpl::frame(Graphic_ptr g, Coord thickness, const FrameSpec &spec, CORBA::Boolean fill)
{
  Frame::Renderer *renderer = 0;
  switch (spec._d())
    {
     case none: renderer = new InvisibleFrame(thickness, fill); break;
     case inset: renderer = new Bevel(thickness, Bevel::inset, spec.bbrightness(), fill); break;
     case outset: renderer = new Bevel(thickness, Bevel::outset, spec.abrightness(), fill); break;
     case convex: renderer = new Bevel(thickness, Bevel::convex, spec.cbrightness(), fill); break;
     case concav: renderer = new Bevel(thickness, Bevel::concav, spec.dbrightness(), fill); break;
     case colored: renderer = new ColoredFrame(thickness, spec.foreground(), fill); break;
    }
  Frame *f = new Frame(thickness, renderer);
  f->_obj_is_ready(_boa());
  graphics.push_back(f);
  f->body(g);
  return f->_this();
}

Graphic_ptr ToolKitImpl::dynamic(Graphic_ptr g, Coord thickness, Telltale::Mask mask, const FrameSpec &s1, const FrameSpec &s2, CORBA::Boolean fill, Telltale_ptr telltale)
{
  Frame::Renderer *renderer1 = 0;
  switch (s1._d())
    {
     case none: renderer1 = new InvisibleFrame(thickness, fill); break;
     case inset: renderer1 = new Bevel(thickness, Bevel::inset, s1.bbrightness(), fill); break;
     case outset: renderer1 = new Bevel(thickness, Bevel::outset, s1.abrightness(), fill); break;
     case convex: renderer1 = new Bevel(thickness, Bevel::convex, s1.cbrightness(), fill); break;
     case concav: renderer1 = new Bevel(thickness, Bevel::concav, s1.dbrightness(), fill); break;
     case colored: renderer1 = new ColoredFrame(thickness, s1.foreground(), fill); break;
    }
  Frame::Renderer *renderer2 = 0;
  switch (s2._d())
    {
     case none: renderer2 = new InvisibleFrame(thickness, fill); break;
     case inset: renderer2 = new Bevel(thickness, Bevel::inset, s2.bbrightness(), fill); break;
     case outset: renderer2 = new Bevel(thickness, Bevel::outset, s2.abrightness(), fill); break;
     case convex: renderer2 = new Bevel(thickness, Bevel::convex, s2.cbrightness(), fill); break;
     case concav: renderer2 = new Bevel(thickness, Bevel::concav, s2.dbrightness(), fill); break;
     case colored: renderer2 = new ColoredFrame(thickness, s2.foreground(), fill); break;
    }
  DynamicFrame *f = new DynamicFrame(thickness, mask, renderer1, renderer2);
  f->_obj_is_ready(_boa());
  f->attach(telltale);
  graphics.push_back(f);
  f->body(g);
  return f->_this();
}

Graphic_ptr ToolKitImpl::framedTriangle(Graphic_ptr g, Coord thickness, const FrameSpec &spec, CORBA::Boolean fill, Direction d)
{
  Frame::Renderer *renderer = 0;
  switch (spec._d())
    {
     case none: renderer = new InvisibleTriangle(thickness, fill, d); break;
     case inset: renderer = new BeveledTriangle(thickness, Bevel::inset, spec.bbrightness(), fill, d); break;
     case outset: renderer = new BeveledTriangle(thickness, Bevel::outset, spec.abrightness(), fill, d); break;
     case convex: renderer = new BeveledTriangle(thickness, Bevel::convex, spec.cbrightness(), fill, d); break;
     case concav: renderer = new BeveledTriangle(thickness, Bevel::concav, spec.dbrightness(), fill, d); break;
     case colored: renderer = new ColoredTriangle(thickness, spec.foreground(), fill, d); break;
    }
  Frame *f = new Frame(thickness, renderer);
  f->_obj_is_ready(_boa());
  graphics.push_back(f);
  f->body(g);
  return f->_this();
}

Graphic_ptr ToolKitImpl::dynamicTriangle(Graphic_ptr g, Coord thickness, Telltale::Mask mask, const FrameSpec &s1, const FrameSpec &s2, CORBA::Boolean fill, Direction d, Telltale_ptr telltale)
{
  Frame::Renderer *renderer1 = 0;
  switch (s1._d())
    {
     case none: renderer1 = new InvisibleTriangle(thickness, fill, d); break;
     case inset: renderer1 = new BeveledTriangle(thickness, Bevel::inset, s1.bbrightness(), fill, d); break;
     case outset: renderer1 = new BeveledTriangle(thickness, Bevel::outset, s1.abrightness(), fill, d); break;
     case convex: renderer1 = new BeveledTriangle(thickness, Bevel::convex, s1.cbrightness(), fill, d); break;
     case concav: renderer1 = new BeveledTriangle(thickness, Bevel::concav, s1.dbrightness(), fill, d); break;
     case colored: renderer1 = new ColoredTriangle(thickness, s1.foreground(), fill, d); break;
    }
  Frame::Renderer *renderer2 = 0;
  switch (s2._d())
    {
     case none: renderer2 = new InvisibleTriangle(thickness, fill, d); break;
     case inset: renderer2 = new BeveledTriangle(thickness, Bevel::inset, s2.bbrightness(), fill, d); break;
     case outset: renderer2 = new BeveledTriangle(thickness, Bevel::outset, s2.abrightness(), fill, d); break;
     case convex: renderer2 = new BeveledTriangle(thickness, Bevel::convex, s2.cbrightness(), fill, d); break;
     case concav: renderer2 = new BeveledTriangle(thickness, Bevel::concav, s2.dbrightness(), fill, d); break;
     case colored: renderer2 = new ColoredTriangle(thickness, s2.foreground(), fill, d); break;
    }
  DynamicFrame *f = new DynamicFrame(thickness, mask, renderer1, renderer2);
  f->_obj_is_ready(_boa());
  f->attach(telltale);
  graphics.push_back(f);
  f->body(g);
  return f->_this();
}

Graphic_ptr ToolKitImpl::framedDiamond(Graphic_ptr g, Coord thickness, const FrameSpec &spec, CORBA::Boolean fill)
{
  Frame::Renderer *renderer = 0;
  switch (spec._d())
    {
     case none: renderer = new InvisibleDiamond(thickness, fill); break;
     case inset: renderer = new BeveledDiamond(thickness, Bevel::inset, spec.bbrightness(), fill); break;
     case outset: renderer = new BeveledDiamond(thickness, Bevel::outset, spec.abrightness(), fill); break;
     case convex: renderer = new BeveledDiamond(thickness, Bevel::convex, spec.cbrightness(), fill); break;
     case concav: renderer = new BeveledDiamond(thickness, Bevel::concav, spec.dbrightness(), fill); break;
     case colored: renderer = new ColoredDiamond(thickness, spec.foreground(), fill); break;
    }
  Frame *f = new Frame(thickness, renderer);
  f->_obj_is_ready(_boa());
  graphics.push_back(f);
  f->body(g);
  return f->_this();
}

Graphic_ptr ToolKitImpl::dynamicDiamond(Graphic_ptr g, Coord thickness, Telltale::Mask mask, const FrameSpec &s1, const FrameSpec &s2, CORBA::Boolean fill, Telltale_ptr telltale)
{
  Frame::Renderer *renderer1 = 0;
  switch (s1._d())
    {
     case none: renderer1 = new InvisibleDiamond(thickness, fill); break;
     case inset: renderer1 = new BeveledDiamond(thickness, Bevel::inset, s1.bbrightness(), fill); break;
     case outset: renderer1 = new BeveledDiamond(thickness, Bevel::outset, s1.abrightness(), fill); break;
     case convex: renderer1 = new BeveledDiamond(thickness, Bevel::convex, s1.cbrightness(), fill); break;
     case concav: renderer1 = new BeveledDiamond(thickness, Bevel::concav, s1.dbrightness(), fill); break;
     case colored: renderer1 = new ColoredDiamond(thickness, s1.foreground(), fill); break;
    }
  Frame::Renderer *renderer2 = 0;
  switch (s2._d())
    {
     case none: renderer2 = new InvisibleDiamond(thickness, fill); break;
     case inset: renderer2 = new BeveledDiamond(thickness, Bevel::inset, s2.bbrightness(), fill); break;
     case outset: renderer2 = new BeveledDiamond(thickness, Bevel::outset, s2.abrightness(), fill); break;
     case convex: renderer2 = new BeveledDiamond(thickness, Bevel::convex, s2.cbrightness(), fill); break;
     case concav: renderer2 = new BeveledDiamond(thickness, Bevel::concav, s2.dbrightness(), fill); break;
     case colored: renderer2 = new ColoredDiamond(thickness, s2.foreground(), fill); break;
    }
  DynamicFrame *f = new DynamicFrame(thickness, mask, renderer1, renderer2);
  f->_obj_is_ready(_boa());
  f->attach(telltale);
  graphics.push_back(f);
  f->body(g);
  return f->_this();
}

// Graphic_ptr ToolKitImpl::filler(Graphic_ptr g, const Color &c)
// {
//   Filler *f = new Filler(c);
//   f->_obj_is_ready(_boa());
//   graphics.push_back(f);
//   f->body(g);
//   return f->_this();
// }

// Graphic_ptr ToolKitImpl::indicator(Graphic_ptr g, const Color &c, Telltale_ptr t)
// {
//   Indicator *i = new Indicator(c);
//   i->_obj_is_ready(_boa());
//   i->attach(t);
//   i->body(g);
//   graphics.push_back(i);
//   return i->_this();
// }

Controller_ptr ToolKitImpl::group(Graphic_ptr g)
{
  ControllerImpl *parent = new ControllerImpl(true);
  parent->_obj_is_ready(_boa());
  parent->body(g);
  graphics.push_back(parent);
  return parent->_this();
}

Trigger_ptr ToolKitImpl::button(Graphic_ptr g, Command_ptr c)
{
  TriggerImpl *trigger = new TriggerImpl();
  trigger->_obj_is_ready(_boa());
  trigger->action(c);
  trigger->body(g);
  graphics.push_back(trigger);
  return trigger->_this();
}

Controller_ptr ToolKitImpl::toggle(Graphic_ptr g)
{
  Toggle *t = new Toggle;
  t->_obj_is_ready(_boa());
  t->body(g);
  graphics.push_back(t);
  return t->_this();
}

Controller_ptr ToolKitImpl::dragger(Graphic_ptr g, Command_ptr command)
{
  Dragger *dragger = new Dragger(command);
  dragger->_obj_is_ready(_boa());
  dragger->body(g);
  graphics.push_back(dragger);
  return dragger->_this();
}

Controller_ptr ToolKitImpl::stepper(Graphic_ptr g, Command_ptr command)
{
  Stepper *stepper = new Stepper;
  stepper->_obj_is_ready(_boa());
  stepper->body(g);
  stepper->action(command);
  graphics.push_back(stepper);
  return stepper->_this();
}

Controller_ptr ToolKitImpl::textInput(Graphic_ptr g, TextBuffer_ptr buffer)
{
  TextInput *input = new TextInput(buffer);
  input->_obj_is_ready(_boa());
  input->body(g);
  graphics.push_back(input);
  return input->_this();
}

extern "C" KitFactory *load()
{
  static string properties[] = {"implementation", "ToolKitImpl"};
  return new KitFactoryImpl<ToolKitImpl> (interface(ToolKit), properties, 1);
}
