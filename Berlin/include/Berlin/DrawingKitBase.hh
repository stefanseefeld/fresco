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
/*
 * bitset is buggy. Sorry, try again later...
 */
// #include <bitset>
#include <stack>

class DrawingKitBase : public virtual POA_DrawingKit
{
 private:
  enum gstate
  {
    st_trafo, 
    st_clip,
    st_fg_color,
    st_lt_color, 
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
    st_font_attr,
    st_last
  };

  struct DrawState
  {
    DrawState() : flags(0) {}
//     bitset<st_last> flags;
    unsigned long flags;
    Transform_var saved_trafo;
    Region_var saved_clip;
    Color saved_fg_color;
    Color saved_lt_color;
    Coord saved_point_size;
    Coord saved_line_width;
    DrawingKit::Endstyle saved_line_end_style;
    DrawingKit::Fillstyle saved_surface_fill_style;
    Raster_var saved_texture;
    CORBA::ULong saved_font_size;
    CORBA::ULong saved_font_weight;
    Unistring_var saved_font_family;
    Unistring_var saved_font_subfamily;
    Unistring_var saved_font_fullname;
    Unistring_var saved_font_style;
    // something here...
    // for holding NVPair saved_font_attr;
  };
 public:
  virtual void saveState() { DrawState st; states.push(st);}
  virtual void restoreState();
  //######################################################
  //############### subclass signatures ##################
  //######################################################

  virtual Transform_ptr transformation() = 0;
  virtual void transformation(Transform_ptr);
  virtual Region_ptr clipping() = 0;
  virtual void clipping(Region_ptr);
  virtual Color foreground() = 0;
  virtual void foreground(const Color &);
  virtual Color lighting() = 0;
  virtual void lighting(const Color &);
  virtual Coord pointSize() = 0;
  virtual void pointSize(Coord);
  virtual Coord lineWidth() = 0;
  virtual void lineWidth(Coord);
  virtual DrawingKit::Endstyle lineEndstyle() = 0;
  virtual void lineEndstyle(DrawingKit::Endstyle);
  virtual DrawingKit::Fillstyle surfaceFillstyle() = 0;
  virtual void surfaceFillstyle(DrawingKit::Fillstyle);
  virtual Raster_ptr texture() = 0;
  virtual void texture(Raster_ptr);

  virtual CORBA::ULong fontSize() = 0;
  virtual void fontSize(CORBA::ULong);
  virtual CORBA::ULong fontWeight() = 0;
  virtual void fontWeight(CORBA::ULong);
  virtual Unistring *fontFamily() = 0;
  virtual void fontFamily(const Unistring &);
  virtual Unistring *fontSubFamily() = 0;
  virtual void fontSubFamily(const Unistring &);
  virtual Unistring *fontFullName() = 0;
  virtual void fontFullName(const Unistring &);
  virtual Unistring *fontStyle() = 0;
  virtual void fontStyle(const Unistring &);
  virtual DrawingKit::FontMetrics fmetrics() = 0;
  virtual DrawingKit::GlyphMetrics gmetrics(Unichar) = 0;
  virtual CORBA::Any *getFontAttr(const Unistring & name) = 0;
  virtual void fontAttr(const NVPair &nvp);

  virtual void init() { }
  virtual void finish() { }
  virtual void flush() = 0;

  virtual void setTransformation(Transform_ptr) = 0;
  virtual void setClipping(Region_ptr) = 0;
  virtual void setForeground(const Color &) = 0;
  virtual void setLighting(const Color &) = 0;
  virtual void setPointSize(Coord) = 0;
  virtual void setLineWidth(Coord) = 0;
  virtual void setLineEndstyle(DrawingKit::Endstyle) = 0;
  virtual void setSurfaceFillstyle(DrawingKit::Fillstyle) = 0;
  virtual void setTexture(Raster_ptr) = 0;

  virtual void setFontSize(CORBA::ULong) = 0;
  virtual void setFontWeight(CORBA::ULong) = 0;
  virtual void setFontFamily(const Unistring&) = 0;
  virtual void setFontSubFamily(const Unistring&) = 0;
  virtual void setFontFullName(const Unistring&) = 0;
  virtual void setFontStyle(const Unistring&) = 0;
  virtual void setFontAttr(const NVPair & nvp) = 0;

private:
  stack<DrawState> states;
};

inline void DrawingKitBase::restoreState()
{
  if (states.empty()) return; // no state to restore
  DrawState &prev = states.top();
  if(prev.flags & (1 << st_trafo))              setTransformation(prev.saved_trafo);
  if(prev.flags & (1 << st_clip))               setClipping(prev.saved_clip);
  if(prev.flags & (1 << st_fg_color))           setForeground(prev.saved_fg_color);
  if(prev.flags & (1 << st_lt_color))           setLighting(prev.saved_lt_color);
  if(prev.flags & (1 << st_point_size))         setPointSize(prev.saved_point_size);
  if(prev.flags & (1 << st_line_width))         setLineWidth(prev.saved_line_width);
  if(prev.flags & (1 << st_line_end_style))     setLineEndstyle(prev.saved_line_end_style);
  if(prev.flags & (1 << st_surface_fill_style)) setSurfaceFillstyle(prev.saved_surface_fill_style);
  if(prev.flags & (1 << st_texture))            setTexture(prev.saved_texture);
  if(prev.flags & (1 << st_font_size))          setFontSize(prev.saved_font_size);
  if(prev.flags & (1 << st_font_weight))        setFontWeight(prev.saved_font_weight);
  if(prev.flags & (1 << st_font_family))        setFontFamily((Unistring &)prev.saved_font_family);
  if(prev.flags & (1 << st_font_subfamily))     setFontSubFamily((Unistring &)prev.saved_font_subfamily);
  if(prev.flags & (1 << st_font_fullname))      setFontFullName((Unistring &)prev.saved_font_fullname);
  if(prev.flags & (1 << st_font_style))         setFontStyle((Unistring &)prev.saved_font_style);
    //    if(prev.flags[st_font_attr]) {
    //       for (unsigned long i = 0; i < prev.saved_font_attr.length())
    // 	     setFontAttr(prev.saved_font_attr[i]);
    //    }
  states.pop();
}

//########################################################
//############### public setter methods ##################
//########################################################

// sorry, I hate macros as much as the next guy,
// but in this case, templates are simply not cutting it.

#define REMEMBER(state,ty,val) \
 if (!(states.empty() || states.top().flags & (1 << st_## state)))\
{ \
  DrawState &st = states.top(); \
  ty tmp(val); \
  st.saved_## state = tmp; \
  st.flags |= (1 << st_## state); \
}

inline void DrawingKitBase::transformation(Transform_ptr t)
{
  REMEMBER(trafo,Transform_var,transformation());
  setTransformation(t);
}

inline void DrawingKitBase::clipping(Region_ptr c)
{
  REMEMBER(clip,Region_var,clipping());
  setClipping(c);
}

inline void DrawingKitBase::foreground(const Color &c)
{
  REMEMBER(fg_color,Color,foreground())
  setForeground(c);
}

inline void DrawingKitBase::lighting(const Color &c)
{
  REMEMBER(lt_color,Color,lighting())
  setLighting(c);
}

inline void DrawingKitBase::pointSize(Coord s)
{
  REMEMBER(point_size,Coord,pointSize());
  setPointSize(s);
}

inline void DrawingKitBase::lineWidth(Coord w)
{
  REMEMBER(line_width,Coord,lineWidth());
  setLineWidth(w);
}

inline void DrawingKitBase::lineEndstyle(DrawingKit::Endstyle s)
{
  REMEMBER(line_end_style,DrawingKit::Endstyle,lineEndstyle());
  setLineEndstyle(s);
}

inline void DrawingKitBase::surfaceFillstyle(DrawingKit::Fillstyle s)
{
  REMEMBER(surface_fill_style,DrawingKit::Fillstyle,surfaceFillstyle());
  setSurfaceFillstyle(s);
}

inline void DrawingKitBase::texture(Raster_ptr t)
{
  REMEMBER(texture,Raster_var,texture());
  setTexture(t);
}

  ////////
  // text
  ////////

inline void DrawingKitBase::fontSize(CORBA::ULong s)
{
  REMEMBER(font_size,CORBA::ULong,fontSize());
  setFontSize(s);
}

inline void DrawingKitBase::fontWeight(CORBA::ULong w)
{
  REMEMBER(font_weight,CORBA::ULong,fontWeight());
  setFontWeight(w);
}

inline void DrawingKitBase::fontFamily(const Unistring &f)
{
  REMEMBER(font_family,Unistring_var,fontFamily());
  setFontFamily(f);
}

inline void DrawingKitBase::fontSubFamily(const Unistring &f)
{
  REMEMBER(font_subfamily,Unistring_var,fontSubFamily());
  setFontSubFamily(f);
}

inline void DrawingKitBase::fontFullName(const Unistring &f)
{
  REMEMBER(font_fullname,Unistring_var,fontFullName());
  setFontFullName(f);
}

inline void DrawingKitBase::fontStyle(const Unistring &s)
{
  REMEMBER(font_style,Unistring_var,fontStyle());
  setFontStyle(s);
}

inline void DrawingKitBase::fontAttr(const NVPair &nvp)
{
  // !FIXME! fill this in.. it's not _too_ hard
}

#endif
