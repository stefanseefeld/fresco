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
#include "Switch.hh"
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

using namespace Berlin::ToolKit;

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

ToolKitImpl::ToolKitImpl(const std::string &id,
			 const Fresco::Kit::PropertySeq &p)
  : KitImpl(id, p) {}

ToolKitImpl::~ToolKitImpl() { }

Graphic_ptr ToolKitImpl::debugger(Graphic_ptr g, const char *s)
{
  Graphic_ptr res = create<Graphic>(new DebugGraphic(std::cout, s));
  res->body(g);
  return res;
}

DrawingState_ptr ToolKitImpl::decorator(Graphic_ptr g)
{
  DrawingState_ptr res = create<DrawingState>(new DrawingStateImpl());
  res->body(g);
  return res;
}

Graphic_ptr ToolKitImpl::rgb(Graphic_ptr gg, Coord r, Coord g, Coord b)
{
  Graphic_ptr res = create<Graphic>(new RGBDecorator(r, g, b));
  res->body(gg);
  return res;
}

Graphic_ptr ToolKitImpl::alpha(Graphic_ptr g, Coord a)
{
  Graphic_ptr res = create<Graphic>(new AlphaDecorator(a));
  res->body(g);
  return res;
}

Graphic_ptr ToolKitImpl::lighting(Graphic_ptr gg, Coord r, Coord g, Coord b)
{
  Graphic_ptr res = create<Graphic>(new LightingDecorator(r, g, b));
  res->body(gg);
  return res;
}

Graphic_ptr ToolKitImpl::frame(Graphic_ptr g,
			       Coord thickness,
			       const Fresco::ToolKit::FrameSpec &spec,
			       CORBA::Boolean fill)
{
  Frame::Renderer *renderer = 0;
  switch (spec._d())
  {
  case Fresco::ToolKit::none:
      renderer = new InvisibleFrame(thickness, fill);
      break;
  case Fresco::ToolKit::inset:
      renderer = new Bevel(thickness, Bevel::inset,
			   spec.brightness(), fill);
      break;
  case Fresco::ToolKit::outset:
      renderer = new Bevel(thickness, Bevel::outset,
			   spec.brightness(), fill);
      break;
  case Fresco::ToolKit::convex:
      renderer = new Bevel(thickness, Bevel::convex,
			   spec.brightness(), fill);
      break;
  case Fresco::ToolKit::concav:
      renderer = new Bevel(thickness, Bevel::concav,
			   spec.brightness(), fill);
      break;
  case Fresco::ToolKit::colored:
      renderer = new ColoredFrame(thickness, spec.foreground(), fill);
      break;
  }
  Graphic_ptr res = create<Graphic>(new Frame(thickness, renderer));
  res->body(g);
  return res;
}

Graphic_ptr ToolKitImpl::triangle(Graphic_ptr g, Coord thickness,
				  const Fresco::ToolKit::FrameSpec &spec,
				  CORBA::Boolean fill,
				  Fresco::ToolKit::Direction d)
{
  Frame::Renderer *renderer = 0;
  switch (spec._d())
  {
  case Fresco::ToolKit::none:
      renderer = new InvisibleTriangle(thickness, fill, d); break;
  case Fresco::ToolKit::inset:
      renderer = new BeveledTriangle(thickness, Bevel::inset,
				     spec.brightness(),
				     fill, d);
      break;
  case Fresco::ToolKit::outset:
      renderer = new BeveledTriangle(thickness, Bevel::outset,
				     spec.brightness(), fill, d);
      break;
  case Fresco::ToolKit::convex:
      renderer = new BeveledTriangle(thickness, Bevel::convex,
				     spec.brightness(), fill, d);
      break;
  case Fresco::ToolKit::concav:
      renderer = new BeveledTriangle(thickness, Bevel::concav,
				     spec.brightness(), fill, d);
      break;
  case Fresco::ToolKit::colored:
      renderer = new ColoredTriangle(thickness, spec.foreground(),
				     fill, d);
      break;
  }
  Graphic_ptr res = create<Graphic>(new Frame(thickness, renderer));
  res->body(g);
  return res;
}

Graphic_ptr ToolKitImpl::diamond(Graphic_ptr g, Coord thickness,
				 const Fresco::ToolKit::FrameSpec &spec,
				 CORBA::Boolean fill)
{
  Frame::Renderer *renderer = 0;
  switch (spec._d())
  {
  case Fresco::ToolKit::none:
      renderer = new InvisibleDiamond(thickness, fill);
      break;
  case Fresco::ToolKit::inset:
      renderer = new BeveledDiamond(thickness, Bevel::inset,
				    spec.brightness(), fill);
      break;
  case Fresco::ToolKit::outset:
      renderer = new BeveledDiamond(thickness, Bevel::outset,
				    spec.brightness(), fill);
      break;
  case Fresco::ToolKit::convex:
      renderer = new BeveledDiamond(thickness, Bevel::convex,
				    spec.brightness(), fill);
      break;
  case Fresco::ToolKit::concav:
      renderer = new BeveledDiamond(thickness, Bevel::concav,
				    spec.brightness(), fill);
      break;
  case Fresco::ToolKit::colored:
      renderer = new ColoredDiamond(thickness, spec.foreground(), fill);
      break;
  }
  Graphic_ptr res = create<Graphic>(new Frame(thickness, renderer));
  res->body(g);
  return res;
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

Graphic_ptr ToolKitImpl::create_switch(Graphic_ptr g1, Graphic_ptr g2,
				       Telltale::Mask mask,
				       Telltale_ptr telltale)
{
  Switch *s = new Switch(mask);
  activate(s);
  s->attach(telltale);
  s->init(g1, g2);
  return s->_this();
}

MainController_ptr ToolKitImpl::group(Graphic_ptr g)
{
  MainController_ptr res =
      create<MainController>(new MainControllerImpl(true));
  res->body(g);
  return res;
}

Trigger_ptr ToolKitImpl::button(Graphic_ptr g, Command_ptr c)
{
  Trigger_ptr trigger = create<Trigger>(new TriggerImpl());
  trigger->action(c);
  trigger->body(g);
  return trigger;
}

Controller_ptr ToolKitImpl::toggle(Graphic_ptr g)
{
  Controller_ptr res = create<Controller>(new Toggle);
  res->body(g);
  return res;
}

Controller_ptr ToolKitImpl::dragger(Graphic_ptr g, Command_ptr command)
{
  Controller_ptr res =create<Controller>(new Dragger(command));
  res->body(g);
  return res;
}

Controller_ptr ToolKitImpl::stepper(Graphic_ptr g, Command_ptr command)
{
  Trigger_ptr stepper = create<Trigger>(new Stepper);
  stepper->action(command);
  stepper->body(g);
  return stepper;
}

Controller_ptr ToolKitImpl::text_input(Graphic_ptr g,
				       TextBuffer_ptr buffer)
{
  Controller_ptr res = create<Controller>(new TextInput(buffer));
  res->body(g);
  return res;
}

Controller_ptr ToolKitImpl::terminal(Graphic_ptr g,
				     StreamBuffer_ptr buffer)
{
  Controller_ptr res = create<Controller>(new Terminal(buffer));
  res->body(g);
  return res;
}

Canvas_ptr ToolKitImpl::create_canvas(PixelCoord width,
				      PixelCoord height)
    throw (SecurityException, CreationFailureException)
{
  try
  {
      return create<Canvas>(new CanvasImpl(width, height));
  }
  catch (const std::runtime_error &e)
  {
      throw CreationFailureException();
  }
}



extern "C" KitImpl *load()
{
  static std::string properties[] = {"implementation", "ToolKitImpl"};
  return create_kit<Berlin::ToolKit::ToolKitImpl> ("IDL:fresco.org/Fresco/ToolKit:1.0", properties, 2);
}
