/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@fresco.org> 
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
#ifndef _Application_hh
#define _Application_hh

#include <Prague/Sys/Signal.hh>
#include <Fresco/config.hh>
#include <Fresco/resolve.hh>
#include <Fresco/TextKit.hh>
#include <Fresco/LayoutKit.hh>
#include <Fresco/ToolKit.hh>
#include <Fresco/WidgetKit.hh>
#include <Fresco/FigureKit.hh>
#include <Fresco/CommandKit.hh>
#include <Fresco/DesktopKit.hh>
#include <Fresco/ImageKit.hh>
#include <Fresco/GadgetKit.hh>
#include <Fresco/MainController.hh>
#include <Fresco/Trigger.hh>
#include <Fresco/BoundedValue.hh>
#include <Fresco/Server.hh>
#include <Fresco/ClientContextImpl.hh>
#include <Fresco/Unicode.hh>
#include <Fresco/Selection.hh>
#include <Fresco/Widget.hh>
#include <unistd.h>
#include <iostream>
#include <vector>

class Application
{
  struct Item
  {
    Fresco::Tag id;
    Fresco::Command_var mapper;
    Fresco::BoundedValue_var alpha;
    Fresco::BoundedValue_var red;
    Fresco::BoundedValue_var blue;
    Fresco::BoundedValue_var green;
    Fresco::BoundedValue_var zrotation;
    Fresco::BoundedValue_var yrotation;
    Fresco::BoundedValue_var zoom;
    Fresco::Command_var settings;
  };
  typedef std::vector<Item> list_t;
  class Mapper;
  friend class Mapper;
public:
  class CommandImpl : public virtual POA_Fresco::Command,
                      public virtual PortableServer::RefCountServantBase
  {
  public:
    virtual void execute(const CORBA::Any &) = 0;
    virtual void destroy();
  };
  Application(Fresco::ServerContext_ptr, Fresco::ClientContext_ptr);

  template <typename K>
  typename K::_ptr_type resolve(const char *repoId)
   { return ::resolve_kit<K>(_server, repoId);}

  void append(Fresco::Controller_ptr, const Babylon::String &);
  void run();
protected:
  Item make_item(const Babylon::String &);
private:
  Fresco::ServerContext_var _server;
  Fresco::ClientContext_var _client;
  Fresco::TextKit_var       _tk;
  Fresco::DesktopKit_var    _dk;
  Fresco::LayoutKit_var     _lk;
  Fresco::ToolKit_var       _ttk;
  Fresco::WidgetKit_var     _wk;
  Fresco::FigureKit_var     _fk;
  Fresco::CommandKit_var    _ck;
  Fresco::ImageKit_var      _ik;
  Fresco::GadgetKit_var     _gk;
  Fresco::Graphic_var       _vbox;
  Widget::Choice_var        _choice;
  list_t                    _demos;
  Mapper                   *_mapper;
  Fresco::Color             _background;
  Fresco::Graphic_var       _done;
  Fresco::Graphic_var       _settings;
  Fresco::Graphic_var       _print;
};

#endif
