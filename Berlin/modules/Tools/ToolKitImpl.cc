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

#include <Warsaw/config.hh>
#include <Warsaw/Server.hh>
#include <Warsaw/DrawingKit.hh>
#include <Berlin/ImplVar.hh>
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
#include "Tool/Terminal.hh"
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

class LightingDecorator : public MonoGraphic
{
public:
  LightingDecorator(Coord r, Coord g, Coord b) : red(r), green(g), blue(b) {}
  virtual void traverse(Traversal_ptr traversal) { traversal->visit(Graphic_var(_this()));}
  virtual void draw(DrawTraversal_ptr traversal)
  {
    DrawingKit_var kit = traversal->kit();
    kit->saveState();
    Color color = kit->lighting();
    color.red *= red, color.green *= green, color.blue *= blue;
    kit->lighting(color);
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
ToolKitImpl::~ToolKitImpl()
{
  for (vector<PortableServer::Servant>::iterator i = graphics.begin(); i != graphics.end(); ++i)
    deactivate(*i);
}

Graphic_ptr ToolKitImpl::debugger(Graphic_ptr g, const char *s)
{
  DebugGraphic *debug = activate(new DebugGraphic(s));
  graphics.push_back(debug);
  debug->body(g);
  return debug->_this();
};

Graphic_ptr ToolKitImpl::rgb(Graphic_ptr gg, Coord r, Coord g, Coord b)
{
  RGBDecorator *decorator = activate(new RGBDecorator(r, g, b));
  graphics.push_back(decorator);
  decorator->body(gg);
  return decorator->_this();
};

Graphic_ptr ToolKitImpl::alpha(Graphic_ptr g, Coord a)
{
  AlphaDecorator *decorator = activate(new AlphaDecorator(a));
  graphics.push_back(decorator);
  decorator->body(g);
  return decorator->_this();
};

Graphic_ptr ToolKitImpl::lighting(Graphic_ptr gg, Coord r, Coord g, Coord b)
{
  LightingDecorator *decorator = activate(new LightingDecorator(r, g, b));
  graphics.push_back(decorator);
  decorator->body(gg);
  return decorator->_this();
};

Graphic_ptr ToolKitImpl::frame(Graphic_ptr g, Coord thickness, const ToolKit::FrameSpec &spec, CORBA::Boolean fill)
{
  Frame::Renderer *renderer = 0;
  switch (spec._d())
    {
     case ToolKit::none: renderer = new InvisibleFrame(thickness, fill); break;
     case ToolKit::inset: renderer = new Bevel(thickness, Bevel::inset, spec.brightness(), fill); break;
     case ToolKit::outset: renderer = new Bevel(thickness, Bevel::outset, spec.brightness(), fill); break;
     case ToolKit::convex: renderer = new Bevel(thickness, Bevel::convex, spec.brightness(), fill); break;
     case ToolKit::concav: renderer = new Bevel(thickness, Bevel::concav, spec.brightness(), fill); break;
     case ToolKit::colored: renderer = new ColoredFrame(thickness, spec.foreground(), fill); break;
    }
  Frame *f = activate(new Frame(thickness, renderer));
  graphics.push_back(f);
  f->body(g);
  return f->_this();
}

Graphic_ptr ToolKitImpl::dynamic(Graphic_ptr g, Coord thickness, Telltale::Mask mask, const ToolKit::FrameSpec &s1,
				 const ToolKit::FrameSpec &s2, CORBA::Boolean fill, Telltale_ptr telltale)
{
  Frame::Renderer *renderer1 = 0;
  switch (s1._d())
    {
     case ToolKit::none: renderer1 = new InvisibleFrame(thickness, fill); break;
     case ToolKit::inset: renderer1 = new Bevel(thickness, Bevel::inset, s1.brightness(), fill); break;
     case ToolKit::outset: renderer1 = new Bevel(thickness, Bevel::outset, s1.brightness(), fill); break;
     case ToolKit::convex: renderer1 = new Bevel(thickness, Bevel::convex, s1.brightness(), fill); break;
     case ToolKit::concav: renderer1 = new Bevel(thickness, Bevel::concav, s1.brightness(), fill); break;
     case ToolKit::colored: renderer1 = new ColoredFrame(thickness, s1.foreground(), fill); break;
    }
  Frame::Renderer *renderer2 = 0;
  switch (s2._d())
    {
     case ToolKit::none: renderer2 = new InvisibleFrame(thickness, fill); break;
     case ToolKit::inset: renderer2 = new Bevel(thickness, Bevel::inset, s2.brightness(), fill); break;
     case ToolKit::outset: renderer2 = new Bevel(thickness, Bevel::outset, s2.brightness(), fill); break;
     case ToolKit::convex: renderer2 = new Bevel(thickness, Bevel::convex, s2.brightness(), fill); break;
     case ToolKit::concav: renderer2 = new Bevel(thickness, Bevel::concav, s2.brightness(), fill); break;
     case ToolKit::colored: renderer2 = new ColoredFrame(thickness, s2.foreground(), fill); break;
    }
  DynamicFrame *f = activate(new DynamicFrame(thickness, mask, renderer1, renderer2));
  f->attach(telltale);
  graphics.push_back(f);
  f->body(g);
  return f->_this();
}

Graphic_ptr ToolKitImpl::framedTriangle(Graphic_ptr g, Coord thickness, const ToolKit::FrameSpec &spec, CORBA::Boolean fill, ToolKit::Direction d)
{
  Frame::Renderer *renderer = 0;
  switch (spec._d())
    {
     case ToolKit::none: renderer = new InvisibleTriangle(thickness, fill, d); break;
     case ToolKit::inset: renderer = new BeveledTriangle(thickness, Bevel::inset, spec.brightness(), fill, d); break;
     case ToolKit::outset: renderer = new BeveledTriangle(thickness, Bevel::outset, spec.brightness(), fill, d); break;
     case ToolKit::convex: renderer = new BeveledTriangle(thickness, Bevel::convex, spec.brightness(), fill, d); break;
     case ToolKit::concav: renderer = new BeveledTriangle(thickness, Bevel::concav, spec.brightness(), fill, d); break;
     case ToolKit::colored: renderer = new ColoredTriangle(thickness, spec.foreground(), fill, d); break;
    }
  Frame *f = activate(new Frame(thickness, renderer));
  graphics.push_back(f);
  f->body(g);
  return f->_this();
}

Graphic_ptr ToolKitImpl::dynamicTriangle(Graphic_ptr g, Coord thickness, Telltale::Mask mask, const ToolKit::FrameSpec &s1,
					 const ToolKit::FrameSpec &s2, CORBA::Boolean fill, ToolKit::Direction d, Telltale_ptr telltale)
{
  Frame::Renderer *renderer1 = 0;
  switch (s1._d())
    {
     case ToolKit::none: renderer1 = new InvisibleTriangle(thickness, fill, d); break;
     case ToolKit::inset: renderer1 = new BeveledTriangle(thickness, Bevel::inset, s1.brightness(), fill, d); break;
     case ToolKit::outset: renderer1 = new BeveledTriangle(thickness, Bevel::outset, s1.brightness(), fill, d); break;
     case ToolKit::convex: renderer1 = new BeveledTriangle(thickness, Bevel::convex, s1.brightness(), fill, d); break;
     case ToolKit::concav: renderer1 = new BeveledTriangle(thickness, Bevel::concav, s1.brightness(), fill, d); break;
     case ToolKit::colored: renderer1 = new ColoredTriangle(thickness, s1.foreground(), fill, d); break;
    }
  Frame::Renderer *renderer2 = 0;
  switch (s2._d())
    {
     case ToolKit::none: renderer2 = new InvisibleTriangle(thickness, fill, d); break;
     case ToolKit::inset: renderer2 = new BeveledTriangle(thickness, Bevel::inset, s2.brightness(), fill, d); break;
     case ToolKit::outset: renderer2 = new BeveledTriangle(thickness, Bevel::outset, s2.brightness(), fill, d); break;
     case ToolKit::convex: renderer2 = new BeveledTriangle(thickness, Bevel::convex, s2.brightness(), fill, d); break;
     case ToolKit::concav: renderer2 = new BeveledTriangle(thickness, Bevel::concav, s2.brightness(), fill, d); break;
     case ToolKit::colored: renderer2 = new ColoredTriangle(thickness, s2.foreground(), fill, d); break;
    }
  DynamicFrame *f = activate(new DynamicFrame(thickness, mask, renderer1, renderer2));
  f->attach(telltale);
  graphics.push_back(f);
  f->body(g);
  return f->_this();
}

Graphic_ptr ToolKitImpl::framedDiamond(Graphic_ptr g, Coord thickness, const ToolKit::FrameSpec &spec, CORBA::Boolean fill)
{
  Frame::Renderer *renderer = 0;
  switch (spec._d())
    {
     case ToolKit::none: renderer = new InvisibleDiamond(thickness, fill); break;
     case ToolKit::inset: renderer = new BeveledDiamond(thickness, Bevel::inset, spec.brightness(), fill); break;
     case ToolKit::outset: renderer = new BeveledDiamond(thickness, Bevel::outset, spec.brightness(), fill); break;
     case ToolKit::convex: renderer = new BeveledDiamond(thickness, Bevel::convex, spec.brightness(), fill); break;
     case ToolKit::concav: renderer = new BeveledDiamond(thickness, Bevel::concav, spec.brightness(), fill); break;
     case ToolKit::colored: renderer = new ColoredDiamond(thickness, spec.foreground(), fill); break;
    }
  Frame *f = activate(new Frame(thickness, renderer));
  graphics.push_back(f);
  f->body(g);
  return f->_this();
}

Graphic_ptr ToolKitImpl::dynamicDiamond(Graphic_ptr g, Coord thickness, Telltale::Mask mask, const ToolKit::FrameSpec &s1,
					const ToolKit::FrameSpec &s2, CORBA::Boolean fill, Telltale_ptr telltale)
{
  Frame::Renderer *renderer1 = 0;
  switch (s1._d())
    {
     case ToolKit::none: renderer1 = new InvisibleDiamond(thickness, fill); break;
     case ToolKit::inset: renderer1 = new BeveledDiamond(thickness, Bevel::inset, s1.brightness(), fill); break;
     case ToolKit::outset: renderer1 = new BeveledDiamond(thickness, Bevel::outset, s1.brightness(), fill); break;
     case ToolKit::convex: renderer1 = new BeveledDiamond(thickness, Bevel::convex, s1.brightness(), fill); break;
     case ToolKit::concav: renderer1 = new BeveledDiamond(thickness, Bevel::concav, s1.brightness(), fill); break;
     case ToolKit::colored: renderer1 = new ColoredDiamond(thickness, s1.foreground(), fill); break;
    }
  Frame::Renderer *renderer2 = 0;
  switch (s2._d())
    {
     case ToolKit::none: renderer2 = new InvisibleDiamond(thickness, fill); break;
     case ToolKit::inset: renderer2 = new BeveledDiamond(thickness, Bevel::inset, s2.brightness(), fill); break;
     case ToolKit::outset: renderer2 = new BeveledDiamond(thickness, Bevel::outset, s2.brightness(), fill); break;
     case ToolKit::convex: renderer2 = new BeveledDiamond(thickness, Bevel::convex, s2.brightness(), fill); break;
     case ToolKit::concav: renderer2 = new BeveledDiamond(thickness, Bevel::concav, s2.brightness(), fill); break;
     case ToolKit::colored: renderer2 = new ColoredDiamond(thickness, s2.foreground(), fill); break;
    }
  DynamicFrame *f = activate(new DynamicFrame(thickness, mask, renderer1, renderer2));
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
  ControllerImpl *parent = activate(new ControllerImpl(true));
  parent->body(g);
  graphics.push_back(parent);
  return parent->_this();
}

Trigger_ptr ToolKitImpl::button(Graphic_ptr g, Command_ptr c)
{
  TriggerImpl *trigger = activate(new TriggerImpl());
  trigger->action(c);
  trigger->body(g);
  graphics.push_back(trigger);
  return trigger->_this();
}

Controller_ptr ToolKitImpl::toggle(Graphic_ptr g)
{
  Toggle *t = activate(new Toggle);
  t->body(g);
  graphics.push_back(t);
  return t->_this();
}

Controller_ptr ToolKitImpl::dragger(Graphic_ptr g, Command_ptr command)
{
  Dragger *dragger = activate(new Dragger(command));
  dragger->body(g);
  graphics.push_back(dragger);
  return dragger->_this();
}

Controller_ptr ToolKitImpl::stepper(Graphic_ptr g, Command_ptr command)
{
  Stepper *stepper = activate(new Stepper);
  stepper->body(g);
  stepper->action(command);
  graphics.push_back(stepper);
  return stepper->_this();
}

Controller_ptr ToolKitImpl::textInput(Graphic_ptr g, TextBuffer_ptr buffer)
{
  TextInput *input = activate(new TextInput(buffer));
  input->body(g);
  graphics.push_back(input);
  return input->_this();
}

Controller_ptr ToolKitImpl::terminal(Graphic_ptr g, StreamBuffer_ptr buffer)
{
  Terminal *input = activate(new Terminal(buffer));
  input->body(g);
  graphics.push_back(input);
  return input->_this();
}

extern "C" KitFactory *load()
{
  static string properties[] = {"implementation", "ToolKitImpl"};
  return new KitFactoryImpl<ToolKitImpl> (ToolKit::_PD_repoId, properties, 1);
}
