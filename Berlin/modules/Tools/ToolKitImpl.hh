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
#ifndef _ToolKitImpl_hh
#define _ToolKitImpl_hh

#include <Fresco/config.hh>
#include <Fresco/ToolKit.hh>
#include <Fresco/State.hh>
#include <Berlin/KitImpl.hh>
#include <vector>

class GraphicImpl;

class ToolKitImpl : public virtual POA_Fresco::ToolKit,
		    public KitImpl
{
 public:
  ToolKitImpl(const std::string &, const Fresco::Kit::PropertySeq &);
  virtual ~ToolKitImpl();
  virtual KitImpl *clone(const Fresco::Kit::PropertySeq &p) { return new ToolKitImpl(repo_id(), p);}

  Fresco::Graphic_ptr      debugger(Fresco::Graphic_ptr, const char *);
  Fresco::DrawingState_ptr decorator(Fresco::Graphic_ptr);
  Fresco::Graphic_ptr      rgb(Fresco::Graphic_ptr, Fresco::Coord, Fresco::Coord, Fresco::Coord);
  Fresco::Graphic_ptr      alpha(Fresco::Graphic_ptr, Fresco::Coord);
  Fresco::Graphic_ptr      lighting(Fresco::Graphic_ptr, Fresco::Coord, Fresco::Coord, Fresco::Coord);

  Fresco::Graphic_ptr      frame(Fresco::Graphic_ptr, Fresco::Coord, const Fresco::ToolKit::FrameSpec &, CORBA::Boolean);
  Fresco::Graphic_ptr      triangle(Fresco::Graphic_ptr, Fresco::Coord, const Fresco::ToolKit::FrameSpec &, CORBA::Boolean,
					   Fresco::ToolKit::Direction d);
  Fresco::Graphic_ptr      diamond(Fresco::Graphic_ptr, Fresco::Coord, const Fresco::ToolKit::FrameSpec &, CORBA::Boolean);
//   Graphic_ptr      filler(Graphic_ptr, const Color &);
//   Graphic_ptr      indicator(Graphic_ptr, const Color &, Telltale_ptr);
  Fresco::Graphic_ptr      create_switch(Fresco::Graphic_ptr, Fresco::Graphic_ptr, Fresco::Telltale::Mask, Fresco::Telltale_ptr);
  Fresco::Trigger_ptr      button(Fresco::Graphic_ptr, Fresco::Command_ptr);
  Fresco::Controller_ptr   dragger(Fresco::Graphic_ptr, Fresco::Command_ptr);
  Fresco::Controller_ptr   stepper(Fresco::Graphic_ptr, Fresco::Command_ptr);
  Fresco::Controller_ptr   text_input(Fresco::Graphic_ptr, Fresco::TextBuffer_ptr);
  Fresco::Controller_ptr   terminal(Fresco::Graphic_ptr, Fresco::StreamBuffer_ptr);
  Fresco::MainController_ptr   group(Fresco::Graphic_ptr);
  Fresco::Controller_ptr   toggle(Fresco::Graphic_ptr);
  Fresco::Canvas_ptr       create_canvas(Fresco::PixelCoord, Fresco::PixelCoord) throw (Fresco::SecurityException, Fresco::CreationFailureException);
};

#endif
