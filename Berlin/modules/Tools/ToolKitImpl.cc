/*$Id$
 *
 * This source file is a part of the Fresco Project.
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

#include <Prague/Sys/Tracer.hh>
#include <Fresco/config.hh>
#include <Fresco/Server.hh>
#include <Fresco/DrawingKit.hh>
#include <Berlin/ImplVar.hh>
#include <Berlin/DebugGraphic.hh>
#include "ToolKitImpl.hh"
// #include "Filler.hh"
// #include "Indicator.hh"
#include "Frame.hh"
#include "Triangle.hh"
#include "Diamond.hh"
#include "TriggerImpl.hh"
#include "Toggle.hh"
#include "Dragger.hh"
#include "Stepper.hh"
#include "TextInput.hh"
#include "Terminal.hh"
#include "CanvasImpl.hh"
#include "DrawingStateImpl.hh"
#include "MainControllerImpl.hh"

using namespace Prague;
using namespace Fresco;

class RGBDecorator : public MonoGraphic
{
public:
  RGBDecorator(Coord r, Coord g, Coord b) : red(r), green(g), blue(b) {}
  virtual void traverse(Traversal_ptr traversal) { traversal->visit(Graphic_var(_this()));}
  virtual void draw(DrawTraversal_ptr traversal)
  {
    DrawingKit_var drawing = traversal->drawing();
    drawing->save();
    Color color = drawing->foreground();
    color.red = red, color.green = green, color.blue = blue;
    drawing->foreground(color);
    MonoGraphic::traverse(traversal);
    drawing->restore();    
  }
  virtual void pick(PickTraversal_ptr traversal) { MonoGraphic::traverse(traversal);}
private:
  Coord red, green, blue;
};

class LightingDecorator : public MonoGraphic
{
public:
  LightingDecorator(Coord r, Coord g, Coord b) : red(r), green(g), blue(b) {}
  virtual void traverse(Traversal_ptr traversal) { traversal->visit(Graphic_var(_this()));}
  virtual void draw(DrawTraversal_ptr traversal)
  {
    DrawingKit_var drawing = traversal->drawing();
    drawing->save();
    Color color = drawing->lighting();
    color.red *= red, color.green *= green, color.blue *= blue;
    drawing->lighting(color);
    MonoGraphic::traverse(traversal);
    drawing->restore();    
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
    DrawingKit_var drawing = traversal->drawing();
    drawing->save();
    Color color = drawing->foreground();
    color.alpha *= alpha;
    drawing->foreground(color);
    MonoGraphic::traverse(traversal);
    drawing->restore();    
  }
  virtual void pick(PickTraversal_ptr traversal) { MonoGraphic::traverse(traversal);}
private:
  Coord alpha;
};

ToolKitImpl::ToolKitImpl(const std::string &id, const Fresco::Kit::PropertySeq &p)
  : KitImpl(id, p) {}

ToolKitImpl::~ToolKitImpl() { }

Graphic_ptr ToolKitImpl::debugger(Graphic_ptr g, const char *s)
{
  Trace trace("ToolKitImpl::debugger");
  DebugGraphic *debug = new DebugGraphic(std::cout, s);
  activate(debug);
  debug->body(g);
  return debug->_this();
};

DrawingState_ptr ToolKitImpl::decorator(Graphic_ptr g)
{
  Trace trace("ToolKitImpl::decorator");
  DrawingStateImpl *state = new DrawingStateImpl();
  activate(state);
  state->body(g);
  return state->_this();
};

Graphic_ptr ToolKitImpl::rgb(Graphic_ptr gg, Coord r, Coord g, Coord b)
{
  Trace trace("ToolKitImpl::rgb");
  RGBDecorator *decorator = new RGBDecorator(r, g, b);
  activate(decorator);
  decorator->body(gg);
  return decorator->_this();
};

Graphic_ptr ToolKitImpl::alpha(Graphic_ptr g, Coord a)
{
  Trace trace("ToolKitImpl::alpha");
  AlphaDecorator *decorator = new AlphaDecorator(a);
  activate(decorator);
  decorator->body(g);
  return decorator->_this();
};

Graphic_ptr ToolKitImpl::lighting(Graphic_ptr gg, Coord r, Coord g, Coord b)
{
  Trace trace("ToolKitImpl::lighting");
  LightingDecorator *decorator = new LightingDecorator(r, g, b);
  activate(decorator);
  decorator->body(gg);
  return decorator->_this();
};

Graphic_ptr ToolKitImpl::frame(Graphic_ptr g, Coord thickness, const Fresco::ToolKit::FrameSpec &spec, CORBA::Boolean fill)
{
  Trace trace("ToolKitImpl::frame");
  Frame::Renderer *renderer = 0;
  switch (spec._d())
    {
     case Fresco::ToolKit::none: renderer = new InvisibleFrame(thickness, fill); break;
     case Fresco::ToolKit::inset: renderer = new Bevel(thickness, Bevel::inset, spec.brightness(), fill); break;
     case Fresco::ToolKit::outset: renderer = new Bevel(thickness, Bevel::outset, spec.brightness(), fill); break;
     case Fresco::ToolKit::convex: renderer = new Bevel(thickness, Bevel::convex, spec.brightness(), fill); break;
     case Fresco::ToolKit::concav: renderer = new Bevel(thickness, Bevel::concav, spec.brightness(), fill); break;
     case Fresco::ToolKit::colored: renderer = new ColoredFrame(thickness, spec.foreground(), fill); break;
    }
  Frame *f = new Frame(thickness, renderer);
  activate(f);
  f->body(g);
  return f->_this();
}

Graphic_ptr ToolKitImpl::dynamic(Graphic_ptr g, Coord thickness, Fresco::Telltale::Mask mask, const Fresco::ToolKit::FrameSpec &s1,
				 const Fresco::ToolKit::FrameSpec &s2, CORBA::Boolean fill, Telltale_ptr telltale)
{
  Trace trace("ToolKitImpl::dynamic");
  Frame::Renderer *renderer1 = 0;
  switch (s1._d())
    {
     case Fresco::ToolKit::none: renderer1 = new InvisibleFrame(thickness, fill); break;
     case Fresco::ToolKit::inset: renderer1 = new Bevel(thickness, Bevel::inset, s1.brightness(), fill); break;
     case Fresco::ToolKit::outset: renderer1 = new Bevel(thickness, Bevel::outset, s1.brightness(), fill); break;
     case Fresco::ToolKit::convex: renderer1 = new Bevel(thickness, Bevel::convex, s1.brightness(), fill); break;
     case Fresco::ToolKit::concav: renderer1 = new Bevel(thickness, Bevel::concav, s1.brightness(), fill); break;
     case Fresco::ToolKit::colored: renderer1 = new ColoredFrame(thickness, s1.foreground(), fill); break;
    }
  Frame::Renderer *renderer2 = 0;
  switch (s2._d())
    {
     case Fresco::ToolKit::none: renderer2 = new InvisibleFrame(thickness, fill); break;
     case Fresco::ToolKit::inset: renderer2 = new Bevel(thickness, Bevel::inset, s2.brightness(), fill); break;
     case Fresco::ToolKit::outset: renderer2 = new Bevel(thickness, Bevel::outset, s2.brightness(), fill); break;
     case Fresco::ToolKit::convex: renderer2 = new Bevel(thickness, Bevel::convex, s2.brightness(), fill); break;
     case Fresco::ToolKit::concav: renderer2 = new Bevel(thickness, Bevel::concav, s2.brightness(), fill); break;
     case Fresco::ToolKit::colored: renderer2 = new ColoredFrame(thickness, s2.foreground(), fill); break;
    }
  DynamicFrame *f = new DynamicFrame(thickness, mask, renderer1, renderer2);
  activate(f);
  f->attach(telltale);
  f->body(g);
  return f->_this();
}

Graphic_ptr ToolKitImpl::framed_triangle(Graphic_ptr g, Coord thickness, const Fresco::ToolKit::FrameSpec &spec, CORBA::Boolean fill, Fresco::ToolKit::Direction d)
{
  Trace trace("ToolKitImpl::triangle");
  Frame::Renderer *renderer = 0;
  switch (spec._d())
    {
     case Fresco::ToolKit::none: renderer = new InvisibleTriangle(thickness, fill, d); break;
     case Fresco::ToolKit::inset: renderer = new BeveledTriangle(thickness, Bevel::inset, spec.brightness(), fill, d); break;
     case Fresco::ToolKit::outset: renderer = new BeveledTriangle(thickness, Bevel::outset, spec.brightness(), fill, d); break;
     case Fresco::ToolKit::convex: renderer = new BeveledTriangle(thickness, Bevel::convex, spec.brightness(), fill, d); break;
     case Fresco::ToolKit::concav: renderer = new BeveledTriangle(thickness, Bevel::concav, spec.brightness(), fill, d); break;
     case Fresco::ToolKit::colored: renderer = new ColoredTriangle(thickness, spec.foreground(), fill, d); break;
    }
  Frame *f = new Frame(thickness, renderer);
  activate(f);
  f->body(g);
  return f->_this();
}

Graphic_ptr ToolKitImpl::dynamic_triangle(Graphic_ptr g, Coord thickness, Telltale::Mask mask, const Fresco::ToolKit::FrameSpec &s1,
					  const Fresco::ToolKit::FrameSpec &s2, CORBA::Boolean fill, Fresco::ToolKit::Direction d, Telltale_ptr telltale)
{
  Trace trace("ToolKitImpl::dynamic_triangle");
  Frame::Renderer *renderer1 = 0;
  switch (s1._d())
    {
     case Fresco::ToolKit::none: renderer1 = new InvisibleTriangle(thickness, fill, d); break;
     case Fresco::ToolKit::inset: renderer1 = new BeveledTriangle(thickness, Bevel::inset, s1.brightness(), fill, d); break;
     case Fresco::ToolKit::outset: renderer1 = new BeveledTriangle(thickness, Bevel::outset, s1.brightness(), fill, d); break;
     case Fresco::ToolKit::convex: renderer1 = new BeveledTriangle(thickness, Bevel::convex, s1.brightness(), fill, d); break;
     case Fresco::ToolKit::concav: renderer1 = new BeveledTriangle(thickness, Bevel::concav, s1.brightness(), fill, d); break;
     case Fresco::ToolKit::colored: renderer1 = new ColoredTriangle(thickness, s1.foreground(), fill, d); break;
    }
  Frame::Renderer *renderer2 = 0;
  switch (s2._d())
    {
     case Fresco::ToolKit::none: renderer2 = new InvisibleTriangle(thickness, fill, d); break;
     case Fresco::ToolKit::inset: renderer2 = new BeveledTriangle(thickness, Bevel::inset, s2.brightness(), fill, d); break;
     case Fresco::ToolKit::outset: renderer2 = new BeveledTriangle(thickness, Bevel::outset, s2.brightness(), fill, d); break;
     case Fresco::ToolKit::convex: renderer2 = new BeveledTriangle(thickness, Bevel::convex, s2.brightness(), fill, d); break;
     case Fresco::ToolKit::concav: renderer2 = new BeveledTriangle(thickness, Bevel::concav, s2.brightness(), fill, d); break;
     case Fresco::ToolKit::colored: renderer2 = new ColoredTriangle(thickness, s2.foreground(), fill, d); break;
    }
  DynamicFrame *f = new DynamicFrame(thickness, mask, renderer1, renderer2);
  activate(f);
  f->attach(telltale);
  f->body(g);
  return f->_this();
}

Graphic_ptr ToolKitImpl::framed_diamond(Graphic_ptr g, Coord thickness, const Fresco::ToolKit::FrameSpec &spec, CORBA::Boolean fill)
{
  Trace trace("ToolKitImpl::framed_diamond");
  Frame::Renderer *renderer = 0;
  switch (spec._d())
    {
     case Fresco::ToolKit::none: renderer = new InvisibleDiamond(thickness, fill); break;
     case Fresco::ToolKit::inset: renderer = new BeveledDiamond(thickness, Bevel::inset, spec.brightness(), fill); break;
     case Fresco::ToolKit::outset: renderer = new BeveledDiamond(thickness, Bevel::outset, spec.brightness(), fill); break;
     case Fresco::ToolKit::convex: renderer = new BeveledDiamond(thickness, Bevel::convex, spec.brightness(), fill); break;
     case Fresco::ToolKit::concav: renderer = new BeveledDiamond(thickness, Bevel::concav, spec.brightness(), fill); break;
     case Fresco::ToolKit::colored: renderer = new ColoredDiamond(thickness, spec.foreground(), fill); break;
    }
  Frame *f = new Frame(thickness, renderer);
  activate(f);
  f->body(g);
  return f->_this();
}

Graphic_ptr ToolKitImpl::dynamic_diamond(Graphic_ptr g, Coord thickness, Telltale::Mask mask, const Fresco::ToolKit::FrameSpec &s1,
					 const Fresco::ToolKit::FrameSpec &s2, CORBA::Boolean fill, Telltale_ptr telltale)
{
  Trace trace("ToolKitImpl::dynamic_diamond");
  Frame::Renderer *renderer1 = 0;
  switch (s1._d())
    {
     case Fresco::ToolKit::none: renderer1 = new InvisibleDiamond(thickness, fill); break;
     case Fresco::ToolKit::inset: renderer1 = new BeveledDiamond(thickness, Bevel::inset, s1.brightness(), fill); break;
     case Fresco::ToolKit::outset: renderer1 = new BeveledDiamond(thickness, Bevel::outset, s1.brightness(), fill); break;
     case Fresco::ToolKit::convex: renderer1 = new BeveledDiamond(thickness, Bevel::convex, s1.brightness(), fill); break;
     case Fresco::ToolKit::concav: renderer1 = new BeveledDiamond(thickness, Bevel::concav, s1.brightness(), fill); break;
     case Fresco::ToolKit::colored: renderer1 = new ColoredDiamond(thickness, s1.foreground(), fill); break;
    }
  Frame::Renderer *renderer2 = 0;
  switch (s2._d())
    {
     case Fresco::ToolKit::none: renderer2 = new InvisibleDiamond(thickness, fill); break;
     case Fresco::ToolKit::inset: renderer2 = new BeveledDiamond(thickness, Bevel::inset, s2.brightness(), fill); break;
     case Fresco::ToolKit::outset: renderer2 = new BeveledDiamond(thickness, Bevel::outset, s2.brightness(), fill); break;
     case Fresco::ToolKit::convex: renderer2 = new BeveledDiamond(thickness, Bevel::convex, s2.brightness(), fill); break;
     case Fresco::ToolKit::concav: renderer2 = new BeveledDiamond(thickness, Bevel::concav, s2.brightness(), fill); break;
     case Fresco::ToolKit::colored: renderer2 = new ColoredDiamond(thickness, s2.foreground(), fill); break;
    }
  DynamicFrame *f = new DynamicFrame(thickness, mask, renderer1, renderer2);
  activate(f);
  f->attach(telltale);
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

MainController_ptr ToolKitImpl::group(Graphic_ptr g)
{
  Trace trace("ToolKitImpl::group");
  MainControllerImpl *parent = new MainControllerImpl(true);
  activate(parent);
  parent->body(g);
  return parent->_this();
}

Trigger_ptr ToolKitImpl::button(Graphic_ptr g, Command_ptr c)
{
  Trace trace("ToolKitImpl::button");
  TriggerImpl *trigger = new TriggerImpl();
  activate(trigger);
  trigger->action(c);
  trigger->body(g);
  return trigger->_this();
}

Controller_ptr ToolKitImpl::toggle(Graphic_ptr g)
{
  Trace trace("ToolKitImpl::toggle");
  Toggle *t = new Toggle;
  activate(t);
  t->body(g);
  return t->_this();
}

Controller_ptr ToolKitImpl::dragger(Graphic_ptr g, Command_ptr command)
{
  Trace trace("ToolKitImpl::dragger");
  Dragger *dragger = new Dragger(command);
  activate(dragger);
  dragger->body(g);
  return dragger->_this();
}

Controller_ptr ToolKitImpl::stepper(Graphic_ptr g, Command_ptr command)
{
  Trace trace("ToolKitImpl::stepper");
  Stepper *stepper = new Stepper;
  activate(stepper);
  stepper->body(g);
  stepper->action(command);
  return stepper->_this();
}

Controller_ptr ToolKitImpl::text_input(Graphic_ptr g, TextBuffer_ptr buffer)
{
  Trace trace("ToolKitImpl::text_input");
  TextInput *input = new TextInput(buffer);
  activate(input);
  input->body(g);
  return input->_this();
}

Controller_ptr ToolKitImpl::terminal(Graphic_ptr g, StreamBuffer_ptr buffer)
{
  Trace trace("ToolKitImpl::terminal");
  Terminal *input = new Terminal(buffer);
  activate(input);
  input->body(g);
  return input->_this();
}

Canvas_ptr ToolKitImpl::create_canvas(PixelCoord width, PixelCoord height) throw (SecurityException, CreationFailureException)
{
  Trace trace("ToolKitImpl::create_canvas");
  try
    {
      CanvasImpl *canvas = new CanvasImpl(width, height);
      activate(canvas);
      return canvas->_this();
    }
  catch (const std::runtime_error &e) { throw CreationFailureException();}
}

extern "C" KitImpl *load()
{
  static std::string properties[] = {"implementation", "ToolKitImpl"};
  return create_kit<ToolKitImpl> ("IDL:fresco.org/Fresco/ToolKit:1.0", properties, 2);
}
