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
#ifndef _EditorImpl_hh
#define _EditorImpl_hh

#include <Warsaw/config.hh>
#include <Warsaw/FigureKit.hh>
#include <Warsaw/ToolKit.hh>
#include <Warsaw/UnidrawKit.hh>
#include <Berlin/RefCountBaseImpl.hh>

class EditorImpl : public virtual POA_Unidraw::Editor,
		   public RefCountBaseImpl
{
public:
  EditorImpl(Warsaw::FigureKit_ptr, Warsaw::ToolKit_ptr);
  virtual ~EditorImpl();
  virtual Unidraw::Tool_ptr current_tool();
  virtual void current_tool(Unidraw::Tool_ptr);
  virtual Warsaw::Controller_ptr create_viewer(Warsaw::Coord, Warsaw::Coord);
private:
  Warsaw::FigureKit_var _figure;
  Warsaw::ToolKit_var   _tool;
};

#endif
