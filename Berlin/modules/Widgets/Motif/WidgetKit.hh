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
#include <Warsaw/WidgetKit.hh>
#include <Warsaw/CommandKit.hh>
#include <Warsaw/LayoutKit.hh>
#include <Warsaw/ToolKit.hh>
#include <Warsaw/TextKit.hh>
#include <Berlin/KitImpl.hh>
#include <Berlin/RefCountBaseImpl.hh>
#include <vector>

class GraphicImpl;

namespace Motif
{

class WidgetKit : public virtual POA_WidgetKit, public KitImpl
{
 public:
  class CommandImpl : public virtual POA_Command,
		      public virtual PortableServer::RefCountServantBase,
		      public virtual RefCountBaseImpl
  {};

  WidgetKit(KitFactory *, const PropertySeq &);
  virtual ~WidgetKit();
  virtual void bind(ServerContext_ptr sc);
  
  Trigger_ptr      button(Graphic_ptr, Command_ptr);
  Controller_ptr   toggle(Graphic_ptr);
  Graphic_ptr      gauge(BoundedValue_ptr);
  Controller_ptr   slider(BoundedValue_ptr, Axis);
  Controller_ptr   panner(BoundedRange_ptr, BoundedRange_ptr);
  Controller_ptr   scrollbar(BoundedRange_ptr, Axis);
  Choice_ptr       toggleChoice();
  Choice_ptr       checkboxChoice();
  Controller_ptr   terminal();

  Controller_ptr   scrollable(Graphic_ptr);
 private:
  LayoutKit_var layout;
  CommandKit_var   command;
  ToolKit_var   tool;
  TextKit_var   text;
  vector<PortableServer::Servant> servants;
};

};

#endif /* _Motif_WidgetKit_hh */
