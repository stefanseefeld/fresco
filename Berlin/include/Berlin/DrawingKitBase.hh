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
#include <Warsaw/DrawingKit3D.hh>
#include <Warsaw/Region.hh>
#include <Warsaw/Transform.hh>
#include <Warsaw/Raster.hh>
/*
 * bitset is buggy. Sorry, try again later...
 */
// #include <bitset>
#include <stack>

class DrawingKitBase : public virtual POA_Warsaw::DrawingKit
{
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
    Warsaw::Transform_var saved_trafo;
    Warsaw::Region_var saved_clip;
    Warsaw::Color saved_fg_color;
    Warsaw::Color saved_lt_color;
    Warsaw::Coord saved_point_size;
    Warsaw::Coord saved_line_width;
    Warsaw::DrawingKit::Endstyle saved_line_end_style;
    Warsaw::DrawingKit::Fillstyle saved_surface_fill_style;
    Warsaw::Raster_var saved_texture;
    CORBA::ULong saved_font_size;
    CORBA::ULong saved_font_weight;
    Warsaw::Unistring_var saved_font_family;
    Warsaw::Unistring_var saved_font_subfamily;
    Warsaw::Unistring_var saved_font_fullname;
    Warsaw::Unistring_var saved_font_style;
    // something here...
    // for holding NVPair saved_font_attr;
  };
 public:
  virtual void saveState() { DrawState st; states.push(st);}
  virtual void restoreState();
  //######################################################
  //############### subclass signatures ##################
  //######################################################

  virtual Warsaw::Transform_ptr transformation() = 0;
  virtual void transformation(Warsaw::Transform_ptr);
  virtual Warsaw::Region_ptr clipping() = 0;
  virtual void clipping(Warsaw::Region_ptr);
  virtual Warsaw::Color foreground() = 0;
  virtual void foreground(const Warsaw::Color &);
  virtual Warsaw::Color lighting() = 0;
  virtual void lighting(const Warsaw::Color &);
  virtual Warsaw::Coord pointSize() = 0;
  virtual void pointSize(Warsaw::Coord);
  virtual Warsaw::Coord lineWidth() = 0;
  virtual void lineWidth(Warsaw::Coord);
  virtual Warsaw::DrawingKit::Endstyle lineEndstyle() = 0;
  virtual void lineEndstyle(Warsaw::DrawingKit::Endstyle);
  virtual Warsaw::DrawingKit::Fillstyle surfaceFillstyle() = 0;
  virtual void surfaceFillstyle(Warsaw::DrawingKit::Fillstyle);
  virtual Warsaw::Raster_ptr texture() = 0;
  virtual void texture(Warsaw::Raster_ptr);

  virtual CORBA::ULong fontSize() = 0;
  virtual void fontSize(CORBA::ULong);
  virtual CORBA::ULong fontWeight() = 0;
  virtual void fontWeight(CORBA::ULong);
  virtual Warsaw::Unistring *fontFamily() = 0;
  virtual void fontFamily(const Warsaw::Unistring &);
  virtual Warsaw::Unistring *fontSubFamily() = 0;
  virtual void fontSubFamily(const Warsaw::Unistring &);
  virtual Warsaw::Unistring *fontFullName() = 0;
  virtual void fontFullName(const Warsaw::Unistring &);
  virtual Warsaw::Unistring *fontStyle() = 0;
  virtual void fontStyle(const Warsaw::Unistring &);
  virtual Warsaw::DrawingKit::FontMetrics fmetrics() = 0;
  virtual Warsaw::DrawingKit::GlyphMetrics gmetrics(Warsaw::Unichar) = 0;
  virtual CORBA::Any *getFontAttr(const Warsaw::Unistring &) = 0;
  virtual void fontAttr(const Warsaw::NVPair &);

  virtual void init() { }
  virtual void finish() { }
  virtual void flush() = 0;

  virtual Warsaw::DrawingKit3D_ptr dk3D() { return Warsaw::DrawingKit3D::_nil(); }

  virtual void setTransformation (Warsaw::Transform_ptr) = 0;
  virtual void setClipping(Warsaw::Region_ptr) = 0;
  virtual void setForeground(const Warsaw::Color &) = 0;
  virtual void setLighting(const Warsaw::Color &) = 0;
  virtual void setPointSize(Warsaw::Coord) = 0;
  virtual void setLineWidth(Warsaw::Coord) = 0;
  virtual void setLineEndstyle(Warsaw::DrawingKit::Endstyle) = 0;
  virtual void setSurfaceFillstyle(Warsaw::DrawingKit::Fillstyle) = 0;
  virtual void setTexture(Warsaw::Raster_ptr) = 0;

  virtual void setFontSize(CORBA::ULong) = 0;
  virtual void setFontWeight(CORBA::ULong) = 0;
  virtual void setFontFamily(const Warsaw::Unistring &) = 0;
  virtual void setFontSubFamily(const Warsaw::Unistring &) = 0;
  virtual void setFontFullName(const Warsaw::Unistring &) = 0;
  virtual void setFontStyle(const Warsaw::Unistring &) = 0;
  virtual void setFontAttr(const Warsaw::NVPair &) = 0;

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
  if(prev.flags & (1 << st_font_family))        setFontFamily((Warsaw::Unistring &)prev.saved_font_family);
  if(prev.flags & (1 << st_font_subfamily))     setFontSubFamily((Warsaw::Unistring &)prev.saved_font_subfamily);
  if(prev.flags & (1 << st_font_fullname))      setFontFullName((Warsaw::Unistring &)prev.saved_font_fullname);
  if(prev.flags & (1 << st_font_style))         setFontStyle((Warsaw::Unistring &)prev.saved_font_style);
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

inline void DrawingKitBase::transformation(Warsaw::Transform_ptr t)
{
  REMEMBER(trafo, Warsaw::Transform_var,transformation());
  setTransformation(t);
}

inline void DrawingKitBase::clipping(Warsaw::Region_ptr c)
{
  REMEMBER(clip, Warsaw::Region_var, clipping());
  setClipping(c);
}

inline void DrawingKitBase::foreground(const Warsaw::Color &c)
{
  REMEMBER(fg_color, Warsaw::Color, foreground())
  setForeground(c);
}

inline void DrawingKitBase::lighting(const Warsaw::Color &c)
{
  REMEMBER(lt_color, Warsaw::Color, lighting())
  setLighting(c);
}

inline void DrawingKitBase::pointSize(Warsaw::Coord s)
{
  REMEMBER(point_size, Warsaw::Coord, pointSize());
  setPointSize(s);
}

inline void DrawingKitBase::lineWidth(Warsaw::Coord w)
{
  REMEMBER(line_width, Warsaw::Coord, lineWidth());
  setLineWidth(w);
}

inline void DrawingKitBase::lineEndstyle(Warsaw::DrawingKit::Endstyle s)
{
  REMEMBER(line_end_style, Warsaw::DrawingKit::Endstyle, lineEndstyle());
  setLineEndstyle(s);
}

inline void DrawingKitBase::surfaceFillstyle(Warsaw::DrawingKit::Fillstyle s)
{
  REMEMBER(surface_fill_style, Warsaw::DrawingKit::Fillstyle, surfaceFillstyle());
  setSurfaceFillstyle(s);
}

inline void DrawingKitBase::texture(Warsaw::Raster_ptr t)
{
  REMEMBER(texture, Warsaw::Raster_var, texture());
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

inline void DrawingKitBase::fontFamily(const Warsaw::Unistring &f)
{
  REMEMBER(font_family, Warsaw::Unistring_var, fontFamily());
  setFontFamily(f);
}

inline void DrawingKitBase::fontSubFamily(const Warsaw::Unistring &f)
{
  REMEMBER(font_subfamily, Warsaw::Unistring_var, fontSubFamily());
  setFontSubFamily(f);
}

inline void DrawingKitBase::fontFullName(const Warsaw::Unistring &f)
{
  REMEMBER(font_fullname, Warsaw::Unistring_var, fontFullName());
  setFontFullName(f);
}

inline void DrawingKitBase::fontStyle(const Warsaw::Unistring &s)
{
  REMEMBER(font_style, Warsaw::Unistring_var, fontStyle());
  setFontStyle(s);
}

inline void DrawingKitBase::fontAttr(const Warsaw::NVPair &nvp)
{
  // !FIXME! fill this in.. it's not _too_ hard
}

#endif
