/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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

#ifndef _DrawingKitBase_hh
#define _DrawingKitBase_hh

#include <Warsaw/config.hh>
#include <Warsaw/DrawingKit.hh>
#include <Warsaw/Region.hh>
#include <Warsaw/Transform.hh>
#include <Warsaw/Raster.hh>
#include <bitset>
#include <stack>

class DrawingKitBase : implements(DrawingKit)
{

 private:
  typedef enum {
    st_trafo = 0, 
    st_clip,
    st_fg_color, 
    st_point_size, 
    st_line_width,
    st_line_end_style, 
    st_surface_fill_style,
    st_texture, 
    st_font_size, 
    st_font_weight,
    st_font_family, 
    st_font_subfamily,
    st_font_fullname,
    st_font_style, 
    st_font_attr = 14
  } gstate;  

  static const gstate last_state = st_font_attr;
  typedef struct {
    bitset<15> flags;
    Transform_var saved_trafo;
    Region_var saved_clip;
    Color saved_fg_color;
    Coord saved_point_size;
    Coord saved_line_width;
    Endstyle saved_line_end_style;
    Fillstyle saved_surface_fill_style;
    Raster_var saved_texture;
    CORBA::ULong saved_font_size;
    CORBA::ULong saved_font_weight;
    Unistring_var saved_font_family;
    Unistring_var saved_font_subfamily;
    Unistring_var saved_font_fullname;
    Unistring_var saved_font_style;
    // something here...
    // for holding NVPair saved_font_attr;
  } DrawState;

  stack<DrawState> myStates;

 public:
  virtual void saveState() { DrawState st; myStates.push(st);}
  virtual void restoreState() {

    if (myStates.empty()) return; // no state to restore
    
    DrawState &prev = myStates.top();

    if(prev.flags[st_trafo])
      setTransformation(prev.saved_trafo);
    
    if(prev.flags[st_clip])
      setClipping(prev.saved_clip);
    
    if(prev.flags[st_fg_color])
      setForeground(prev.saved_fg_color);
    
    if(prev.flags[st_point_size])
      setPointSize(prev.saved_point_size);
    
    if(prev.flags[st_line_width])
      setLineWidth(prev.saved_line_width);
    
    if(prev.flags[st_line_end_style])
      setLineEndstyle(prev.saved_line_end_style);
    
    if(prev.flags[st_surface_fill_style])
      setSurfaceFillstyle(prev.saved_surface_fill_style);
    
    if(prev.flags[st_texture])
      setTexture(prev.saved_texture);
    
    if(prev.flags[st_font_size])
      setFontSize(prev.saved_font_size);
    
    if(prev.flags[st_font_weight])
      setFontWeight(prev.saved_font_weight);
    
    if(prev.flags[st_font_family])
      setFontFamily(prev.saved_font_family);
    
    if(prev.flags[st_font_subfamily])
      setFontSubFamily(prev.saved_font_subfamily);
    
    if(prev.flags[st_font_fullname])
      setFontFullName(prev.saved_font_fullname);
    
    if(prev.flags[st_font_style])
      setFontStyle(prev.saved_font_style);
    
    //    if(prev.flags[st_font_attr]) {
    //       for (unsigned long i = 0; i < prev.saved_font_attr.length())
    // 	     setFontAttr(prev.saved_font_attr[i]);
    //    }

    myStates.pop();
  }

  //######################################################
  //############### subclass signatures ##################
  //######################################################


  virtual Transform_ptr transformation() = 0;
  virtual Region_ptr clipping() = 0;
  virtual Color foreground() = 0;
  virtual Coord pointSize() = 0;
  virtual Coord lineWidth() = 0;
  virtual Endstyle lineEndstyle() = 0;
  virtual Fillstyle surfaceFillstyle() = 0;
  virtual Raster_ptr texture() = 0;

  virtual void flush() = 0;

  virtual CORBA::ULong fontSize() = 0;
  virtual CORBA::ULong fontWeight() = 0;
  virtual Unistring* fontFamily() = 0;
  virtual Unistring* fontSubFamily() = 0;
  virtual Unistring* fontFullName() = 0;
  virtual Unistring* fontStyle() = 0;
  virtual FontMetrics metrics() = 0;
  virtual CORBA::Any * getFontAttr(const Unistring & name) = 0;

  virtual void setTransformation(Transform_ptr) = 0;
  virtual void setClipping(Region_ptr) = 0;
  virtual void setForeground(const Color &) = 0;
  virtual void setPointSize(Coord) = 0;
  virtual void setLineWidth(Coord) = 0;
  virtual void setLineEndstyle(Endstyle) = 0;
  virtual void setSurfaceFillstyle(Fillstyle) = 0;
  virtual void setTexture(Raster_ptr) = 0;

  virtual void setFontSize(CORBA::ULong) = 0;
  virtual void setFontWeight(CORBA::ULong) = 0;
  virtual void setFontFamily(const Unistring&) = 0;
  virtual void setFontSubFamily(const Unistring&) = 0;
  virtual void setFontFullName(const Unistring&) = 0;
  virtual void setFontStyle(const Unistring&) = 0;
  virtual void setFontAttr(const NVPair & nvp) = 0;

  //########################################################
  //############### public setter methods ##################
  //########################################################

  // sorry, I hate macros as much as the next guy,
  // but in this case, templates are simply not cutting it.

#define REMEMBER(state,ty,val) \
 if (!(myStates.empty() || myStates.top().flags[st_## state])) { \
  DrawState &st = myStates.top(); \
  ty tmp(val); \
  st.saved_## state = tmp; \
  st.flags[st_## state] = true; \
 }

  
  inline void transformation(Transform_ptr t)
    {
      REMEMBER(trafo,Transform_var,transformation());
      setTransformation(t);
    }

  inline void clipping(Region_ptr c)
    {
      REMEMBER(clip,Region_var,clipping());
      setClipping(c);
    }

  inline void foreground(const Color &c)
    {
      REMEMBER(fg_color,Color,foreground())
      setForeground(c);
    }

  inline void pointSize(Coord s)
    {
      REMEMBER(point_size,Coord,pointSize());
      setPointSize(s);
    }

  inline void lineWidth(Coord w)
    {
      REMEMBER(line_width,Coord,lineWidth());
      setLineWidth(w);
    }

  inline void lineEndstyle(Endstyle s)
    {
      REMEMBER(line_end_style,Endstyle,lineEndstyle())
      setLineEndstyle(s);
    }

  inline void surfaceFillstyle(Fillstyle s)
    {
      REMEMBER(surface_fill_style,Fillstyle,surfaceFillstyle());
      setSurfaceFillstyle(s);
    }

  inline void texture(Raster_ptr t)
    {
      REMEMBER(texture,Raster_var,texture());
      setTexture(t);
    }

  ////////
  // text
  ////////

  inline void fontSize(CORBA::ULong s)
    {
      REMEMBER(font_size,CORBA::ULong,fontSize());
      setFontSize(s);
    }

  inline void fontWeight(CORBA::ULong w)
    {
      REMEMBER(font_weight,CORBA::ULong,fontWeight());
      setFontWeight(w);
    }

  inline void fontFamily(const Unistring &f)
    {
      REMEMBER(font_family,Unistring_var,fontFamily());
      setFontFamily(f);
    }

  inline void fontSubFamily(const Unistring &f)
    {
      REMEMBER(font_subfamily,Unistring_var,fontSubFamily());
      setFontSubFamily(f);
    }

  inline void fontFullName(const Unistring &f)
    {
      REMEMBER(font_fullname,Unistring_var,fontFullName());
      setFontFullName(f);
    }

  inline void fontStyle(const Unistring &s)
    {
      REMEMBER(font_style,Unistring_var,fontStyle());
      setFontStyle(s);
    }

  inline void fontAttr(const NVPair &nvp)
    {
      // !FIXME! fill this in.. it's not _too_ hard
    }

};
  
#endif
