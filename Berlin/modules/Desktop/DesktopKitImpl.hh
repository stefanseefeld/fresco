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
#ifndef _DesktopKitImpl_hh
#define _DesktopKitImpl_hh

#include <Fresco/config.hh>
#include <Fresco/DesktopKit.hh>
#include <Fresco/LayoutKit.hh>
#include <Fresco/ToolKit.hh>
#include <Fresco/WidgetKit.hh>
#include <Fresco/TextKit.hh>
#include <Fresco/ImageKit.hh>
#include <Fresco/Image.hh>
#include <Fresco/FigureKit.hh>
#include <Fresco/Desktop.hh>
#include <Berlin/KitImpl.hh>
#include <Berlin/RefCountVar.hh>

namespace Berlin 
{
namespace DesktopKit 
{

class WindowImpl;
class DesktopImpl;

class DesktopKitImpl : public virtual POA_Fresco::DesktopKit,
		       public KitImpl
{
public:
  DesktopKitImpl(const std::string &,
		 const Fresco::Kit::PropertySeq &,
		 ServerContextImpl *);
  virtual ~DesktopKitImpl();
  virtual KitImpl *clone(const Fresco::Kit::PropertySeq &p, ServerContextImpl *c)
  { return new DesktopKitImpl(repo_id(), p, c);}
  virtual void bind(Fresco::ServerContext_ptr);
  virtual Fresco::Desktop_ptr desk();
  virtual Fresco::Window_ptr shell(Fresco::Controller_ptr, Fresco::ClientContext_ptr);
  virtual Fresco::Window_ptr transient(Fresco::Controller_ptr);
  virtual Fresco::Window_ptr pulldown(Fresco::Controller_ptr);

  virtual Fresco::Command_ptr move(Fresco::Window_ptr);
  virtual Fresco::Command_ptr resize(Fresco::Window_ptr);
  virtual Fresco::Command_ptr move_resize(Fresco::Window_ptr, Fresco::Alignment, Fresco::Alignment, CORBA::Short);
  virtual Fresco::Command_ptr relayer(Fresco::Window_ptr);
  virtual Fresco::Command_ptr map(Fresco::Window_ptr, CORBA::Boolean);
 private:
  RefCount_var<Fresco::Desktop>    _desktop;
  RefCount_var<Fresco::LayoutKit>  _layout;
  RefCount_var<Fresco::ToolKit>    _tool;
  RefCount_var<Fresco::WidgetKit>  _widget;
  RefCount_var<Fresco::TextKit>    _text;
  RefCount_var<Fresco::ImageKit>   _image;
  RefCount_var<Fresco::FigureKit>  _figure;
  Fresco::Command_var              _exit;
};

} // namespace
} // namespace

#endif
