/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 2003 Tobias Hunger <tobias@fresco.org>
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
#ifndef _Berlin_GraphDebugger_hh
#define _Berlin_GraphDebugger_hh

#include <Fresco/Graphic.hh>
#include <string>
#include <vector>

namespace Berlin
{

  class GraphicImpl;

  class GraphDebugger
  {
    public:
      //. This implizitly activates the GraphicDictionary.
      GraphDebugger(Fresco::Graphic_ptr);
      ~GraphDebugger();
      
      //. Starts the debugging session. For now all this does is
      //. to dump the scenegraph in graphviz's dot-file format into
      //. /tmp/debug.dot.
      //. You can turn this file into a Postscript drawing of the
      //. SceneGraph by running "dot -Tps /tmp/debug.dot".
      void debug();
    private:
      GraphDebugger(const GraphDebugger &) { }

      void dump_graphic(Fresco::Graphic_ptr, std::ostream &);

      Fresco::Graphic_ptr my_root;

      struct graphic_info
      {
      Fresco::Graphic_var graphic;
      GraphicImpl * impl;
      unsigned long hash;
      unsigned long id;
      bool dumped;
      std::string name;

      graphic_info(Fresco::Graphic_ptr g, const GraphicImpl * const im,
               unsigned long h, unsigned long i,
               std::string n, bool d = false) :
          graphic(Fresco::Graphic::_duplicate(g)),
          impl(const_cast<GraphicImpl *>(im)),
          hash(h),
          id(i),
          name(n),
          dumped(d)
      { }
      };

      graphic_info & find_or_insert(Fresco::Graphic_ptr);

      static unsigned long my_current_id;

      std::vector<graphic_info> my_known_graphics;
  };

} // namespace

#endif
