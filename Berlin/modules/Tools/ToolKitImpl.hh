/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@berlin-consortium.org> 
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
#ifndef _ToolKitImpl_hh
#define _ToolKitImpl_hh

#include "Warsaw/config.hh"
#include "Warsaw/ToolKit.hh"
#include "Berlin/KitImpl.hh"
#include <vector>

class GraphicImpl;

class ToolKitImpl : implements(ToolKit), public KitImpl
{
 public:
  ToolKitImpl(KitFactory *, const PropertySeq &);
  virtual ~ToolKitImpl();

  Graphic_ptr      debugger(Graphic_ptr, const char *);
  Graphic_ptr      rgb(Graphic_ptr, Coord, Coord, Coord);
  Graphic_ptr      alpha(Graphic_ptr, Coord);
  Graphic_ptr      lighting(Graphic_ptr, Coord, Coord, Coord);

  Graphic_ptr      frame(Graphic_ptr, Coord, const FrameSpec &, CORBA::Boolean);
  Graphic_ptr      dynamic(Graphic_ptr, Coord, Telltale::Mask, const FrameSpec &, const FrameSpec &, CORBA::Boolean, Telltale_ptr);
  Graphic_ptr      framedTriangle(Graphic_ptr, Coord, const FrameSpec &, CORBA::Boolean, Direction d);
  Graphic_ptr      dynamicTriangle(Graphic_ptr, Coord, Telltale::Mask, const FrameSpec &, const FrameSpec &, CORBA::Boolean, Direction d, Telltale_ptr);
  Graphic_ptr      framedDiamond(Graphic_ptr, Coord, const FrameSpec &, CORBA::Boolean);
  Graphic_ptr      dynamicDiamond(Graphic_ptr, Coord, Telltale::Mask, const FrameSpec &, const FrameSpec &, CORBA::Boolean, Telltale_ptr);
//   Graphic_ptr      filler(Graphic_ptr, const Color &);
//   Graphic_ptr      indicator(Graphic_ptr, const Color &, Telltale_ptr);
  Trigger_ptr      button(Graphic_ptr, Command_ptr);
  Controller_ptr   dragger(Graphic_ptr, Command_ptr);
  Controller_ptr   stepper(Graphic_ptr, Command_ptr);
  Controller_ptr   textInput(Graphic_ptr, TextBuffer_ptr);
  Controller_ptr   terminal(Graphic_ptr, StreamBuffer_ptr);
  Controller_ptr   group(Graphic_ptr);
  Controller_ptr   toggle(Graphic_ptr);
 private:
  vector<GraphicImpl *> graphics;
};

#endif /* _ToolKitImpl_hh */
