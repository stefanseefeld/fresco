/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Graydon Hoare <graydon@pobox.com> 
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

#include "Drawing/openGL/GLUnifont.hh"
#include <GL/gl.h>
#include <string>
#include <string.h>
#include <iostream>
#include <stdlib.h>

// This is a default font, just in case -- a character cell bitmapped unicode
// font which is generated "on the fly" from the GNU unifont, which we're storing
// in a berkeley DB file. this is so that, even if all the font manufactureres
// in the world turn against us, we can still render multilingual text, albeit
// not quite as well as certain (ahem) proprietary text systems

static Unistring UNIFY(const char *c) {
  Unistring tmp;
  unsigned int len = strlen(c);
  tmp.length(len);
  for (unsigned long i = 0; i < len; i++) {
      tmp[i] = (Unichar)(c[i]);
  }
  return tmp;
}

GLUnifont::GLUnifont() : rendered(65536)
{
    myDescriptor.pointsize = 16;
    myDescriptor.name = UNIFY("GNU Unifont");
    char *glyphdbName = getenv("GLYPH_DB");
    if (Db::open(glyphdbName, DB_BTREE, DB_RDONLY|DB_NOMMAP, 0644, NULL, NULL,&glyphdb) == DB_RUNRECOVERY) {
      perror("Unifont initialization");
    }
    myDisplaylistOffset = glGenLists(65536);
}

GLUnifont::~GLUnifont() {}

void GLUnifont::setColor(Color c) 
{
    myColor = c;
}

void GLUnifont::drawText(const Unistring &u, const Vertex &p) 
{
  // record from DB
  GLubyte glyphbuf[32]; 
  Dbt glyph;
  glyph.set_flags(DB_DBT_USERMEM);
  glyph.set_data(glyphbuf); 
  glyph.set_ulen(32);
  
  // reuseable key for DB fetch
  Dbt key;
  key.set_size(2); // unicode values -- 2 bytes
  
  // prepare GL to draw
  glColor4d(myColor.red,myColor.green,myColor.blue,myColor.alpha); // load color
  glPixelStorei(GL_UNPACK_ROW_LENGTH,0);
  glPixelStorei(GL_UNPACK_ALIGNMENT,1); // set to byte-aligned unpacking
#if 0
  glDisable(GL_CLIP_PLANE0);
  glDisable(GL_CLIP_PLANE1);
  glDisable(GL_CLIP_PLANE2);
  glDisable(GL_CLIP_PLANE3);
#endif
  glRasterPos2i((int)(p.x),(int)(p.y));  // position pen
#if 0
  glEnable(GL_CLIP_PLANE0);
  glEnable(GL_CLIP_PLANE1);
  glEnable(GL_CLIP_PLANE2);
  glEnable(GL_CLIP_PLANE3);
#endif
  GLushort idx[u.length()];
  
  for(unsigned long i = 0; i < u.length(); i++) {
    unsigned short tmpchr = (unsigned short)(u[i]);
    if (! rendered[tmpchr]) {
      glNewList(myDisplaylistOffset + tmpchr, GL_COMPILE);
//       cerr << "(" << tmpchr << ") ";
      key.set_data((void *)(&tmpchr)); // discard const ! 
      if (glyphdb->get(NULL,&key,&glyph,0) == 0) {
	int height = 16;
	int width = (glyph.get_size() * 8) / height;
	glBitmap(width, height, 0.0, 0.0, (float)width, 0.0, (const GLubyte *)(glyph.get_data()));
	glEndList();
      }
      rendered[tmpchr] = true;
    }
      idx[i] = u[i];
  }
    glListBase(myDisplaylistOffset);
    glCallLists(u.length(),GL_UNSIGNED_SHORT,(GLvoid *)(idx));
}


void GLUnifont::acceptFontVisitor(Text::FontVisitor_ptr v)
{
    v->visitBaseFont(this->_this());
    CORBA::release(v);
}

void GLUnifont::allocateText(const Unistring &u, Graphic::Requisition &r)
{
    // record from DB
    GLubyte glyphbuf[32]; 
    Dbt glyph;

    glyph.set_flags(DB_DBT_USERMEM);
    glyph.set_data(glyphbuf); 
    glyph.set_ulen(32);

    // reuseable key for DB fetch
    Dbt key;
    key.set_size(2); // unicode values -- 2 bytes
    
    int width = 0;
    int height = 16;

    for(unsigned int i = 0; i < u.length(); i++) {
	unsigned short tmpchr = (unsigned short)(u[i]);
	key.set_data((void *)(&tmpchr)); // discard const ! 
	if (glyphdb->get(NULL,&key,&glyph,0) == 0) {
	    width += (glyph.get_size() * 8) / height;
	}
    }

    r.x.natural = r.x.minimum = r.x.maximum = width;
    r.x.defined = true;
    r.x.align = 0.;
    r.y.natural = r.y.minimum = r.y.maximum = height;
    r.y.defined = true;
    r.y.align = 0.;
}

CORBA::Boolean  GLUnifont::canDrawText(const Unistring &u){
  return true;
}

Text::FontDescriptor *GLUnifont::descriptor(){
  return &myDescriptor;
}

FeatureValueList *GLUnifont::queryFeature(FeatureType ft) { return new FeatureValueList(); }
void GLUnifont::setFeature(FeatureType ft, FeatureValue fv) {}
