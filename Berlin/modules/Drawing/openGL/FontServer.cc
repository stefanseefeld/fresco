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

#include <Drawing/openGL/FontServer.hh>
#include <Drawing/openGL/GLUnifont.hh>
#include <Drawing/openGL/GLPixmapFont.hh>

using namespace Prague;
using namespace Berlin::DrawingKit;

openGL::FontServer::FontServer()
{
    my_size = 16;
    my_weight = 100;
    my_font = new GLUnifont;
    my_fonts[key(16, 100,
		 Unicode::toCORBA(Unicode::String("GNU Unifont")))] =
	my_font;
//    char *env = getenv("BERLIN_ROOT");
//    if (!env)
//    {
//         std::cerr << "Please set environment variable BERLIN_ROOT first"
//                    << std::endl;
//         exit(-1);
//    }
//    string ttf = string(env) + "/etc/Fonts/helv.ttf";
//    FT::Face *face = new FT::Face(ttf.c_str());
//    faces[Unicode::toCORBA(Unicode::String("Helvetica"))] = face;
//    my_font = new GLPixmapFont(*face, 10);
//    my_fonts[key(16, 100,
//             Unicode::toCORBA(Unicode::String("Helvetica")))] = my_font;
}

openGL::FontServer::~FontServer()
{
    for (fmap_t::iterator i = my_fonts.begin(); i != my_fonts.end(); ++i)
        delete (*i).second;
}

void
openGL::FontServer::lookup(unsigned long, unsigned long, const Unistring &)
{ }
