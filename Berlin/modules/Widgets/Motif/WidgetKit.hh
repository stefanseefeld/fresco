/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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
#ifndef _Motif_WidgetKitImpl_hh
#define _Motif_WidgetKitImpl_hh

#include <Warsaw/config.hh>
#include <Warsaw/Widget.hh>
#include <Warsaw/WidgetKit.hh>
#include <Warsaw/CommandKit.hh>
#include <Warsaw/LayoutKit.hh>
#include <Warsaw/ToolKit.hh>
#include <Warsaw/TextKit.hh>
#include <Berlin/KitImpl.hh>
#include <Berlin/RefCountBaseImpl.hh>
#include <Berlin/RefCountVar.hh>
#include <vector>

class GraphicImpl;

namespace Motif
{

class WidgetKit : public virtual POA_Warsaw::WidgetKit,
		  public KitImpl
{
 public:
  WidgetKit(const std::string &, const Warsaw::Kit::PropertySeq &);
  virtual ~WidgetKit();
  virtual KitImpl *clone(const Warsaw::Kit::PropertySeq &p) { return new WidgetKit(repo_id(), p);}
  virtual void bind(Warsaw::ServerContext_ptr);
  
  Warsaw::Trigger_ptr      button(Warsaw::Graphic_ptr, Warsaw::Command_ptr);
  Warsaw::Controller_ptr   toggle(Warsaw::Graphic_ptr);
  Warsaw::Graphic_ptr      gauge(Warsaw::BoundedValue_ptr);
  Warsaw::Controller_ptr   slider(Warsaw::BoundedValue_ptr, Warsaw::Axis);
  Warsaw::Controller_ptr   panner(Warsaw::BoundedRange_ptr, Warsaw::BoundedRange_ptr);
  Warsaw::Controller_ptr   scrollbar(Warsaw::BoundedRange_ptr, Warsaw::Axis);
  Widget::Choice_ptr       toggle_choice();
  Widget::Choice_ptr       checkbox_choice();
  Widget::Choice_ptr       toolbar();
  Warsaw::Controller_ptr   terminal();
//   Widget::Splitter_ptr     splitter(Warsaw::Graphic_ptr, Warsaw::Graphic_ptr, Warsaw::Axis);
  Warsaw::Controller_ptr   scrollable(Warsaw::Graphic_ptr);
 private:
  RefCount_var<Warsaw::LayoutKit>  _layout;
  RefCount_var<Warsaw::CommandKit> _commands;
  RefCount_var<Warsaw::ToolKit>    _tools;
  RefCount_var<Warsaw::TextKit>    _text;
};

};

#endif
