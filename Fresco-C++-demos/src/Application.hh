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
#ifndef _Application_hh
#define _Application_hh

#include <Warsaw/Warsaw.hh>
#include <Warsaw/TextKit.hh>
#include <Warsaw/LayoutKit.hh>
#include <Warsaw/ToolKit.hh>
#include <Warsaw/WidgetKit.hh>
#include <Warsaw/FigureKit.hh>
#include <Warsaw/CommandKit.hh>
#include <Warsaw/DesktopKit.hh>
#include <Warsaw/ImageKit.hh>
#include <Warsaw/GadgetKit.hh>
#include <Warsaw/Trigger.hh>
#include <Warsaw/BoundedValue.hh>
#include <Warsaw/Server.hh>
#include <Warsaw/ClientContextImpl.hh>
#include <Prague/Sys/Signal.hh>
#include <Warsaw/Unicode.hh>
#include <Warsaw/Selection.hh>
#include <Warsaw/Choice.hh>
#include <Berlin/ImplVar.hh>
#include <unistd.h>
#include <iostream>
#include <vector>

class Application
{
  struct Item
  {
    Tag id;
    Command_var mapper;
    BoundedValue_var alpha;
    BoundedValue_var red;
    BoundedValue_var blue;
    BoundedValue_var green;
    BoundedValue_var zrotation;
    BoundedValue_var yrotation;
    BoundedValue_var zoom;
    Command_var settings;
  };
  typedef vector<Item> list_t;
  class Mapper : public virtual POA_Command, public virtual PortableServer::RefCountServantBase
  {
  public:
    Mapper(Application::list_t &d, Selection_ptr s) : demos(d), selection(Selection::_duplicate(s)) {}
    virtual void execute(const CORBA::Any &);
  private:
    Application::list_t &demos;
    Selection_var selection;
  };
  friend class Mapper;
public:
  Application(Warsaw *);
  TextKit_ptr text() { return TextKit::_duplicate(tk);}
  DesktopKit_ptr desktop() { return DesktopKit::_duplicate(dk);}
  LayoutKit_ptr layout() { return LayoutKit::_duplicate(lk);}
  ToolKit_ptr tool() { return ToolKit::_duplicate(ttk);}
  WidgetKit_ptr widget() { return WidgetKit::_duplicate(wk);}
  FigureKit_ptr figure() { return FigureKit::_duplicate(fk);}
  CommandKit_ptr command() { return CommandKit::_duplicate(ck);}
  ImageKit_ptr image() { return ImageKit::_duplicate(ik);}
  GadgetKit_ptr gadget() { return GadgetKit::_duplicate(gk);}
  void append(Controller_ptr, const Unicode::String &);
  void run();
protected:
  Item makeItem(const Unicode::String &);
private:
  TextKit_var tk;
  DesktopKit_var dk;
  LayoutKit_var lk;
  ToolKit_var ttk;
  WidgetKit_var wk;
  FigureKit_var fk;
  CommandKit_var ck;
  ImageKit_var ik;
  GadgetKit_var gk;
  Graphic_var vbox;
  Choice_var  choice;
  list_t demos;
  Impl_var<Mapper> mapper;
  Color background;
  Graphic_var done;
  Graphic_var settings;
};

#endif /* _Application_hh */
