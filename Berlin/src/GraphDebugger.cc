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

#include <Fresco/Controller.hh>
#include <Fresco/Transform.hh>

#include <Berlin/GraphDebugger.hh>
#include <Berlin/GraphicImpl.hh>
#include <Berlin/GraphicDictionary.hh>

#include <limits>
#include <iostream>
#include <fstream>
#include <typeinfo>

unsigned long Berlin::GraphDebugger::my_current_id = 0;


Berlin::GraphDebugger::GraphDebugger(Fresco::Graphic_ptr r) :
    my_root(r),
    my_known_graphics()
{
    Berlin::GraphicDictionary::instance()->activate();
}

Berlin::GraphDebugger::~GraphDebugger()
{ }

void Berlin::GraphDebugger::debug()
{
    my_current_id = 0;
    std::ofstream out("/tmp/debug.dot");
    
    out << "digraph SceneGraph {" << std::endl;
    dump_graphic(my_root, out);
    out << "}" << std::endl;
    
    my_known_graphics.clear();
}

void Berlin::GraphDebugger::dump_graphic(Fresco::Graphic_ptr g,
					 std::ostream & out)
{
    if (CORBA::is_nil(g)) return;
    
    graphic_info & info = find_or_insert(g);
    if (info.dumped) return;
    
    // dump output:
    
    // node id:
    out << "    n" << info.id << " ";
    
    // label: name
    out << "[label=\"" << info.name << "(n" << info.id << ")\\n";

    // label: allocation
    Fresco::Graphic::Requisition r;
    g->request(r);
    out << "X(";
    if (r.x.defined)
	out << r.x.minimum << ","
	    << r.x.natural << ","
	    << r.x.maximum << ")";
    else
	out << "-";
    out << "):Y(";
    if (r.y.defined)
	out << r.y.minimum << ","
	    << r.y.natural << ","
	    << r.y.maximum << ")";
    else
	out << "-";
    out << "):Z(";
    if (r.z.defined)
	out << r.z.minimum << ","
	    << r.z.natural << ","
	    << r.z.maximum << ")";
    else
	out << "-";
    out << ")";
    
    // label: transformation
    Fresco::Transform_var t = g->transformation();
    if (!CORBA::is_nil(t) && !t->identity())
    {
	Fresco::Transform::Matrix m;
	t->store_matrix(m);
	out << "[" << m[0][0] << ", " << m[0][1] << ", "
	    << m[0][2] << ", "  << m[0][3] << "]\\n";
	out << "[" << m[1][0] << ", " << m[1][1] << ", "
	    << m[1][2] << ", "  << m[1][3] << "]\\n";
	out << "[" << m[2][0] << ", " << m[2][1] << ", "
	    << m[2][2] << ", "  << m[2][3] << "]\\n";
	out << "[" << m[3][0] << ", " << m[3][1] << ", "
	    << m[3][2] << ", "  << m[3][3] << "]\\n";
    }
    out << "\"," << std::endl;
    
    // shape (depending on type of g)
    out << "        shape=\"";
    if (CORBA::is_nil(Fresco::Controller::_narrow(g)))
	out << "ellipse";
    else
	out << "box";
    out << "\"]" << std::endl;
    
    
    info.dumped = true;
    
    
    // recursion:
    // calculate graphics to traverse:
    std::vector<Fresco::Graphic_ptr> children;

    if (CORBA::is_nil(g->body()))
    {
	Fresco::GraphicIterator_var i = g->first_child_graphic();
	if (CORBA::is_nil(i)) return; // leaf graphic!

	for ( ; !CORBA::is_nil(i->child()); i->next())
	{
	    children.push_back(i->child());
	}
    }
    else
	children.push_back(g->body());

    // children contain all childgraphics now!
    for (std::vector<Fresco::Graphic_ptr>::const_iterator i =
	     children.begin();
	 i != children.end();
	 ++i)
    {
	graphic_info & target = find_or_insert(*i);
	out << "    n" << info.id << " -> n" << target.id << std::endl;
    }

    for (std::vector<Fresco::Graphic_ptr>::const_iterator i =
	     children.begin();
	 i != children.end();
	 ++i)
	dump_graphic(*i, out);
}


Berlin::GraphDebugger::graphic_info &
Berlin::GraphDebugger::find_or_insert(Fresco::Graphic_ptr g)
{
    unsigned long hash =
	g->_hash(std::numeric_limits<unsigned int>::max());
    const GraphicImpl * const p(Berlin::GraphicDictionary::instance()->
				implementation(g));

    for (std::vector<graphic_info>::iterator i =
	     my_known_graphics.begin();
	 i != my_known_graphics.end();
	 ++i)
	if (hash == i->hash &&
	    g->_is_equivalent(i->graphic))
		return *i; // we allready know this one

    // the graphic is unknown: register it and return a reference to it.
    my_known_graphics.push_back(
	graphic_info(g, p, hash, my_current_id,
		     Berlin::GraphicDictionary::instance()->name(g)));
    ++my_current_id;

    return my_known_graphics.back();
}
