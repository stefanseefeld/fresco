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
#include <Prague/Sys/Tracer.hh>
#include <Fresco/config.hh>
#include <Fresco/resolve.hh>
#include "UnidrawKitImpl.hh"
#include "ViewImpl.hh"
#include "SelectTool.hh"
#include "EditorImpl.hh"

using namespace Prague;
using namespace Fresco;

using namespace Berlin::UnidrawKit;

UnidrawKitImpl::UnidrawKitImpl(const std::string &id,
			       const Fresco::Kit::PropertySeq &p)
  : KitImpl(id, p)
{ }

UnidrawKitImpl::~UnidrawKitImpl()
{ }

void UnidrawKitImpl::bind(ServerContext_ptr context)
{
  Trace trace("UnidrawKitImpl::bind");
  KitImpl::bind(context);
  Fresco::Kit::PropertySeq props;
  props.length(0);
  _figures = resolve_kit<FigureKit>(context,
				    "IDL:fresco.org/Fresco/FigureKit:1.0",
				    props);
  _tools   = resolve_kit<ToolKit>(context,
				  "IDL:fresco.org/Fresco/ToolKit:1.0",
				  props);
  _widgets = resolve_kit<WidgetKit>(context,
				    "IDL:fresco.org/Fresco/WidgetKit:1.0",
				    props);
}

Unidraw::Tool_ptr UnidrawKitImpl::select_tool()
{
  Graphic_var box = _figures->rectangle(0., 0., 1., 1.);
  return create<Unidraw::Tool>(new SelectTool(box));
}

Unidraw::Editor_ptr UnidrawKitImpl::create_editor()
{
  return create<Unidraw::Editor>(new EditorImpl(this));
}

Unidraw::View_ptr UnidrawKitImpl::create_view(Graphic_ptr g, Unidraw::Model_ptr m)
{
  return create_and_set_body<Unidraw::View>(new UViewImpl(m), g);
}

Fresco::FigureKit_ptr UnidrawKitImpl::figures()
{
    return RefCount_var<Fresco::FigureKit>::increment(_figures);
}

Fresco::ToolKit_ptr UnidrawKitImpl::tools()
{
    return RefCount_var<Fresco::ToolKit>::increment(_tools);
}

Fresco::WidgetKit_ptr UnidrawKitImpl::widgets()
{
    return RefCount_var<Fresco::WidgetKit>::increment(_widgets);
}



extern "C" KitImpl *load()
{
  static std::string properties[] = {"implementation", "UnidrawKitImpl"};
  return create_kit<UnidrawKitImpl>("IDL:fresco.org/Unidraw/UnidrawKit:1.0", properties, 2);
} 
