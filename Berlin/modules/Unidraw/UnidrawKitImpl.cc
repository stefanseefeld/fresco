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
#include <Prague/Sys/Tracer.hh>
#include <Warsaw/config.hh>
#include <Warsaw/resolve.hh>
#include "Unidraw/UnidrawKitImpl.hh"
#include "Unidraw/Editor.hh"

using namespace Prague;
using namespace Warsaw;
// using namespace Unidraw;

UnidrawKitImpl::UnidrawKitImpl(KitFactory *f, const Warsaw::Kit::PropertySeq &p)
  : KitImpl(f, p) {}
UnidrawKitImpl::~UnidrawKitImpl() {}
void UnidrawKitImpl::bind(ServerContext_ptr context)
{
  Trace trace("UnidrawKitImpl::bind");
  KitImpl::bind(context);
  Warsaw::Kit::PropertySeq props;
  props.length(0);
  _figure = resolve_kit<FigureKit>(context, "IDL:Warsaw/FigureKit:1.0", props);
}

Controller_ptr UnidrawKitImpl::editor(Coord width, Coord height)
{
  Editor *editor = new Editor(width, height, _figure);
  activate(editor);
  return editor->_this();
}

extern "C" KitFactory *load()
{
  static string properties[] = {"implementation", "UnidrawKitImpl"};
  return new KitFactoryImpl<UnidrawKitImpl>("IDL:Unidraw/UnidrawKit:1.0", properties, 1);
} 
