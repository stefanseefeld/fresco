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
#ifndef _TerminalView_hh
#define _TerminalView_hh

#include <Fresco/config.hh>
#include <Fresco/View.hh>
#include <Fresco/TextKit.hh>
#include <Berlin/ViewImpl.hh>
#include "Composition.hh"
#include <map>
#include <vector>

class TerminalView : public virtual ViewImpl,
		     public Composition
{
  typedef std::vector<Composition *> lines_t;
 public:
  TerminalView(Fresco::StreamBuffer_ptr, Fresco::TextKit_ptr, Fresco::DrawingKit_ptr, Compositor *, Compositor *);
  virtual ~TerminalView();
  virtual void request(Fresco::Graphic::Requisition &);
  virtual void need_resize();
  virtual void update(const CORBA::Any &);
 protected:
  void begin();
  void end();
  Fresco::StreamBuffer_ptr _stream;
  Fresco::TextKit_var      _kit;
  Fresco::DrawingKit_var   _canonicalDK;
  Compositor              *_compositor;
  lines_t                  _lines;
  bool                     _locked;
};

#endif
