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
#ifndef _LibArtFTFont_hh
#define _LibArtFTFont_hh

#include <Warsaw/config.hh>
#include <Warsaw/Types.hh>
#include <Warsaw/Graphic.hh>
#include <Prague/Sys/MMap.hh>
#include <Drawing/libArt/LibArtFont.hh>
#include <freetype2/freetype.h>
#include <Warsaw/Unicode.hh>

class LibArtFTFont : public LibArtFont
//. this is a simple Freetype font, which doesn't support
//. ligatures or complex layout features
{
public:
  LibArtFTFont(GGI::Drawable *drawable);
  virtual ~LibArtFTFont();
  virtual unsigned long size();
  virtual void size(unsigned long);
  virtual unsigned long weight();
  virtual void weight(unsigned long);
  virtual void family(const Unistring &);
  virtual void subfamily(const Unistring &);
  virtual void fullname(const Unistring &);
  virtual void style(const Unistring &);
  virtual Unistring *family();
  virtual Unistring *subfamily();
  virtual Unistring *fullname();
  virtual Unistring *style();

  void segments(const Unistring u, vector< pair<double,ArtPixBuf *> > &segs);
  void allocateText(const Unistring &u, Graphic::Requisition &r);
protected:
  
  typedef unsigned int atom;
  
  class atomizer {
  protected:
    atom curr_atom;
    map<string,atom> atom_map;
  public:
    atom atomize(const string &u) {
      map<string,atom>::iterator i;
      i = atom_map.find(u);
      if (i == atom_map.end()) {	
	atom_map[u] = ++curr_atom;
	return curr_atom;
      } else {
	return i->second;
      }
    }
  }
  
  atomizer _a;
  atom atomize(const string &u) {return _a.atomize(u);}
  void setup_face(FT_Face &f);
  void setup_size(FT_Face &f);
  bool load_glyph(Unichar c, FT_Face &f);
    
  double xdpi, ydpi;  
  typedef pair<atom,atom> famStyle;
  typedef string filename;
  typedef unsigned int size;
  typedef pair<size,famStyle> faceSpec;
  typedef pair<Unichar,faceSpec> cachespec;
  typedef map<Unichar,ArtPixBuf *>::iterator cacheiter;
  
  map<Unichar,ArtPixBuf *> cache;
  map<famStyle,FT_Face> facemap;

  atom my_fam, my_style;
  string my_famstr, my_stylestr;
  size my_size;
  FT_Library library;
  FT_Face face;
};

#endif
