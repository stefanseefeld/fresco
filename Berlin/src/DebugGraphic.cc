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
#include <Fresco/Traversal.hh>
#include <Fresco/DrawTraversal.hh>
#include <Fresco/PickTraversal.hh>
#include <Fresco/IO.hh>
#include <Prague/Sys/Tracer.hh>
#include <Berlin/ImplVar.hh>
#include <Berlin/RegionImpl.hh>
#include <Berlin/DebugGraphic.hh>
#include <Berlin/Math.hh>
#include <iomanip>

using namespace Prague;
using namespace Fresco;
using namespace Berlin;

DebugGraphic::DebugGraphic(std::ostream &os, const std::string &msg,
               unsigned int f) :
    my_os(os),
    my_message(msg),
    my_flags(f)
{ }
DebugGraphic::~DebugGraphic() { }

void DebugGraphic::request(Fresco::Graphic::Requisition &r)
{
    Trace trace(this, "DebugGraphic::request");
    MonoGraphic::request(r);
    if (my_flags & requests)
    {
    heading(" request\t");
    my_os << r << std::endl;
    }
}

void DebugGraphic::traverse(Traversal_ptr traversal)
{
    Trace trace(this, "DebugGraphic::traverse");
    if (my_flags & traversals) traversal->visit(Graphic_var(_this()));
    else MonoGraphic::traverse(traversal);
}

void DebugGraphic::draw(DrawTraversal_ptr traversal)
{
    Trace trace(this, "DebugGraphic::draw");
    if (my_flags & draws)
    {
    heading(" draw\t");
    Region_var r = traversal->current_allocation();
    Transform_var t = traversal->current_transformation();
    Impl_var<RegionImpl> region(new RegionImpl(r, t));
    my_os << "region: " << '\n' << Region_var(region->_this())
          << std::endl;
    }
    MonoGraphic::traverse(traversal);
};

void DebugGraphic::pick(PickTraversal_ptr traversal)
{
    Trace trace(this, "DebugGraphic::pick");
    if (my_flags & picks)
    {
    heading(" pick\t");
    Region_var r = traversal->current_allocation();
    Transform_var t = traversal->current_transformation();
    Impl_var<RegionImpl> region(new RegionImpl(r, t));
    my_os << Region_var(region->_this()) << std::endl;
    }
    MonoGraphic::traverse(traversal);
}

void DebugGraphic::allocate(Tag tag, const Allocation::Info &info)
{
    heading(" allocate\t");
    Region_var r = info.allocation;
    Transform_var t = info.transformation;
    Impl_var<RegionImpl> region(new RegionImpl(r, t));
    my_os << Region_var(region->_this()) << std::endl;
    MonoGraphic::allocate(tag, info);
}

void DebugGraphic::heading(const char *s)
{
    Graphic_var g = body();
    my_os << my_message << " (" << g << ')' << s;
}
