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
#ifndef _UnidrawKitImpl_hh
#define _UnidrawKitImpl_hh

#include <Fresco/config.hh>
#include <Fresco/FigureKit.hh>
#include <Fresco/ToolKit.hh>
#include <Fresco/WidgetKit.hh>
#include <Fresco/UnidrawKit.hh>
#include <Berlin/KitImpl.hh>
#include <Berlin/RefCountVar.hh>

namespace Berlin {
namespace UnidrawKit {

class UnidrawKitImpl : public virtual POA_Unidraw::UnidrawKit,
		       public KitImpl
{
public:
  UnidrawKitImpl(const std::string &, const Fresco::Kit::PropertySeq &);
  virtual ~UnidrawKitImpl();
  virtual KitImpl *clone(const Fresco::Kit::PropertySeq &p) { return new UnidrawKitImpl(repo_id(), p);}
  virtual void bind(Fresco::ServerContext_ptr);
  virtual Unidraw::Tool_ptr select_tool();
  virtual Unidraw::Editor_ptr create_editor();
  virtual Unidraw::View_ptr   create_view(Fresco::Graphic_ptr g, Unidraw::Model_ptr);
  Fresco::FigureKit_ptr figures();
  Fresco::ToolKit_ptr tools();
  Fresco::WidgetKit_ptr widgets();
private:
  RefCount_var<Fresco::FigureKit> _figures;
  RefCount_var<Fresco::ToolKit>   _tools;
  RefCount_var<Fresco::WidgetKit> _widgets;
};

} // namespace
} // namespace

#endif
