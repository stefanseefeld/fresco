/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 2000 Stefan Seefeld <stefan@fresco.org> 
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
#ifndef _Motif_WidgetKitImpl_hh
#define _Motif_WidgetKitImpl_hh

#include <Fresco/config.hh>
#include <Fresco/Widget.hh>
#include <Fresco/WidgetKit.hh>
#include <Fresco/CommandKit.hh>
#include <Fresco/LayoutKit.hh>
#include <Fresco/ToolKit.hh>
#include <Fresco/TextKit.hh>
#include <Berlin/KitImpl.hh>
#include <Berlin/RefCountBaseImpl.hh>
#include <Berlin/RefCountVar.hh>
#include <vector>

class GraphicImpl;

namespace Motif
{

class WidgetKit : public virtual POA_Fresco::WidgetKit,
		  public KitImpl
{
 public:
  WidgetKit(const std::string &, const Fresco::Kit::PropertySeq &);
  virtual ~WidgetKit();
  virtual KitImpl *clone(const Fresco::Kit::PropertySeq &p) { return new WidgetKit(repo_id(), p);}
  virtual void bind(Fresco::ServerContext_ptr);
  
  Fresco::Trigger_ptr      button(Fresco::Graphic_ptr, Fresco::Command_ptr);
  Fresco::Controller_ptr   toggle(Fresco::Graphic_ptr);
  Fresco::Graphic_ptr      gauge(Fresco::BoundedValue_ptr);
  Fresco::Controller_ptr   slider(Fresco::BoundedValue_ptr, Fresco::Axis);
  Fresco::Controller_ptr   panner(Fresco::BoundedRange_ptr, Fresco::BoundedRange_ptr);
  Fresco::Controller_ptr   scrollbar(Fresco::BoundedRange_ptr, Fresco::Axis);
  Widget::Choice_ptr       toggle_choice();
  Widget::Choice_ptr       checkbox_choice();
  Widget::Choice_ptr       toolbar();
  Fresco::Controller_ptr   terminal();
//   Widget::Splitter_ptr     splitter(Fresco::Graphic_ptr, Fresco::Graphic_ptr, Fresco::Axis);
  Fresco::Controller_ptr   scrollable(Fresco::Graphic_ptr);
 private:
  RefCount_var<Fresco::LayoutKit>  _layout;
  RefCount_var<Fresco::CommandKit> _commands;
  RefCount_var<Fresco::ToolKit>    _tools;
  RefCount_var<Fresco::TextKit>    _text;
};

};

#endif
