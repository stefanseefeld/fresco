/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
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
#include <Warsaw/Raster.hh>
#include <stack>

class DrawingKitBase : lcimplements(DrawingKit)
{
 public:
  void continueRestoring()
    {
      State *state = states.top();
      states.pop();
      state->restore(*this);
      delete state;
    }
 private:
  struct State
  {
    virtual ~State(){}
    virtual void restore(DrawingKitBase &) const = 0;
//     void *operator new(size_t);
//     void operator delete(void *, size_t);
  };
  struct StateMarker : State { void restore(DrawingKitBase &) const {}};
  struct TransformationState : State
  {
    TransformationState(Transform_ptr t) : transformation(Transform::_duplicate(t)) {}
    void restore(DrawingKitBase &dk) const
    {
      dk.setTransformation(transformation);
      dk.continueRestoring();
    }
    Transform_var transformation;
  };
  struct ClippingState : State
  {
    ClippingState(Region_ptr c) : clipping(Region::_duplicate(c)) {}
    void restore(DrawingKitBase &dk) const
    {
      dk.setClipping(clipping);
      dk.continueRestoring();
    }
    Region_var clipping;
  };
  struct ForegroundState : State
  {
    ForegroundState(const Color &c) : color(c) {}
    void restore(DrawingKitBase &dk) const
    {
      dk.setForeground(color);
      dk.continueRestoring();
    }
    Color color;
  };
  struct PointSizeState : State
  {
    PointSizeState(Coord s) : size(s) {}
    void restore(DrawingKitBase &dk) const
    {
      dk.setPointSize(size);
      dk.continueRestoring();
    }
    Coord size;
  };
  struct LineWidthState : State
  {
    LineWidthState(Coord w) : width(w) {}
    void restore(DrawingKitBase &dk) const
    {
      dk.setLineWidth(width);
      dk.continueRestoring();
    }
    Coord width;
  };
  struct LineEndstyleState : State
  {
    LineEndstyleState(Endstyle s) : style(s) {}
    void restore(DrawingKitBase &dk) const
    {
      dk.setLineEndstyle(style);
      dk.continueRestoring();
    }
    Endstyle style;
  };
  struct SurfaceFillstyleState : State
  {
    SurfaceFillstyleState(Fillstyle s) : style(s) {}
    void restore(DrawingKitBase &dk) const
    {
      dk.setSurfaceFillstyle(style);
      dk.continueRestoring();
    }
    Fillstyle style;
  };
  struct TextureState : State
  {
    TextureState(Raster_ptr t) : texture(Raster::_duplicate(t)) {}
    void restore(DrawingKitBase &dk) const
    {
      dk.setTexture(texture);
      dk.continueRestoring();
    }
    Raster_var texture;
  };
 
  typedef stack<State *> stack_t;
public:
  virtual void transformation(Transform_ptr t) { states.push(new TransformationState(t)); setTransformation(t);}
  virtual void clipping(Region_ptr c) { states.push(new ClippingState(c)); setClipping(c);}
  virtual void foreground(const Color &c) { states.push(new ForegroundState(c)); setForeground(c);}
  virtual void pointSize(Coord s) { states.push(new PointSizeState(s)); setPointSize(s);}
  virtual void lineWidth(Coord w) { states.push(new LineWidthState(w)); setLineWidth(w);}
  virtual void lineEndstyle(Endstyle s) { states.push(new LineEndstyleState(s)); setLineEndstyle(s);}
  virtual void surfaceFillstyle(Fillstyle s) { states.push(new SurfaceFillstyleState(s)); setSurfaceFillstyle(s);}
  virtual void texture(Raster_ptr t) { states.push(new TextureState(t)); setTexture(t);}

  virtual void saveState() { states.push(new StateMarker);}
  virtual void restoreState() { continueRestoring();}

  virtual void setTransformation(Transform_ptr) = 0;
  virtual void setClipping(Region_ptr) = 0;
  virtual void setForeground(const Color &) = 0;
  virtual void setPointSize(Coord) = 0;
  virtual void setLineWidth(Coord) = 0;
  virtual void setLineEndstyle(Endstyle) = 0;
  virtual void setSurfaceFillstyle(Fillstyle) = 0;
  virtual void setTexture(Raster_ptr) = 0;
private:
  stack_t states;
};

#endif /* _DrawingKitBase_hh */
