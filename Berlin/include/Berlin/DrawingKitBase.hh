/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@berlin-consortium.ca> 
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
#include <stack>

class DrawingKitBase : lcimplements(DrawingKit)
{
 public:
  void continueRestoring()
    {
      State *state = states.top();
      states.pop();
      state->restore(this);
      delete state;
    }
 private:

  /** we now define a set of mementos which are stored on a state stack inside
   * the DrawingKit. every time you change something in the kit, it pushes a
   * state onto the stack. when you call gsave(), it pushes a StateMaker on the
   * stack. when you call grestore(), it begins restoring from the top of the
   * stack. the StateMarker will stop restoring, whereas all other mementos will
   * restore themselves and continue restoration down the memento stack. in this
   * way, we achieve a simple imperative state system which nonetheless can
   * follow the scene graph's concepts of nesting as the scene is traversed. */

  struct State
  {
    virtual ~State(){}
    virtual void restore(DrawingKitBase *) const {};
  };

  struct StateMarker : State { void restore(DrawingKitBase *) const {}};

  template <class T> struct SimpleState : State
  //. for primitive types...
  {
    typedef void (DrawingKitBase::*method)(T);
    SimpleState(T v, method mm) : val(v), m(mm) {}
    void restore(DrawingKitBase *dk) const
    {
      (dk->*m)(val);
      dk->continueRestoring();
    }
    T val;
    method m;
  };
  template <class T> struct RefState : State
  //. for fixed size structs...
  {
    typedef void (DrawingKitBase::*method)(const T &);
    RefState(const T &v, method mm) : val(v), m(mm) {}
    void restore(DrawingKitBase *dk) const
    {
      (dk->*m)(val);
      dk->continueRestoring();
    }
    T val;
    method m;
  }; 
  template <class T> struct VarState : State
  //. for var size structs...
  {
    typedef void (DrawingKitBase::*method)(const T &);
    VarState(T *v, method mm) : val(v), m(mm) {}
    void restore(DrawingKitBase *dk) const
    {
      (dk->*m)(val);
      dk->continueRestoring();
    }
    typename T::_var_type val;
    method m;
  };
  template <class Ptr> struct PtrState : State
  //. for CORBA object references...
  {
    typedef void (DrawingKitBase::*method)(typename Ptr::_ptr_type);
    PtrState(typename Ptr::_ptr_type v, method mm) : val(v), m(mm) {} // the absence of _duplicate() is intentional...
    void restore(DrawingKitBase *dk) const
    {
      (dk->*m)(val);
      dk->continueRestoring();
    }
    typename Ptr::_var_type val;
    method m;
  };
  typedef stack<State *> stack_t;
public:

  virtual void saveState() { states.push(new StateMarker);}
  virtual void restoreState() { continueRestoring();}

  // drawing business
  virtual void transformation(Transform_ptr);
  virtual Transform_ptr transformation() = 0;
  virtual void clipping(Region_ptr);
  virtual Region_ptr clipping() = 0;
  virtual void foreground(const Color &);
  virtual Color foreground() = 0;
  virtual void pointSize(Coord);
  virtual Coord pointSize() = 0;
  virtual void lineWidth(Coord);
  virtual Coord lineWidth() = 0;
  virtual void lineEndstyle(Endstyle);
  virtual Endstyle lineEndstyle() = 0;
  virtual void surfaceFillstyle(Fillstyle);
  virtual Fillstyle surfaceFillstyle() = 0;
  virtual void texture(Raster_ptr);
  virtual Raster_ptr texture() = 0;

  virtual void flush() = 0;

  // font business
  virtual CORBA::ULong fontSize() = 0;
  virtual void fontSize(CORBA::ULong);
  virtual CORBA::ULong fontWeight() = 0;
  virtual void fontWeight(CORBA::ULong);
  virtual Unistring* fontFamily() = 0;
  virtual void fontFamily(const Unistring&);
  virtual Unistring* fontSubFamily() = 0;
  virtual void fontSubFamily(const Unistring&);
  virtual Unistring* fontFullName() = 0;
  virtual void fontFullName(const Unistring&);
  virtual Unistring* fontStyle() = 0;
  virtual void fontStyle(const Unistring&);
  virtual FontMetrics metrics() = 0;
  virtual void fontAttr(const NVPair & nvp);
  virtual CORBA::Any * getFontAttr(const Unistring & name) = 0;

  // if you subclass this, you'll need to provide these
  // mechanisms in addition to the getters above.

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

private:
  stack_t states;
};

inline void DrawingKitBase::transformation(Transform_ptr t)
{
  states.push(new PtrState<Transform>(transformation(), &DrawingKitBase::setTransformation));
  setTransformation(t);
}

inline void DrawingKitBase::clipping(Region_ptr c)
{
  states.push(new PtrState<Region>(clipping(), &DrawingKitBase::setClipping));
  setClipping(c);
}

inline void DrawingKitBase::foreground(const Color &c)
{
  states.push(new RefState<Color>(foreground(), &DrawingKitBase::setForeground));
  setForeground(c);
}

inline void DrawingKitBase::pointSize(Coord s)
{
 states.push(new SimpleState<Coord>(pointSize(), &DrawingKitBase::setPointSize));
 setPointSize(s);
}

inline void DrawingKitBase::lineWidth(Coord w)
{
  states.push(new SimpleState<Coord>(lineWidth(), &DrawingKitBase::setLineWidth));
  setLineWidth(w);
}

inline void DrawingKitBase::lineEndstyle(Endstyle s)
{
  states.push(new SimpleState<Endstyle>(lineEndstyle(), &DrawingKitBase::setLineEndstyle));
  setLineEndstyle(s);
}

inline void DrawingKitBase::surfaceFillstyle(Fillstyle s)
{
  states.push(new SimpleState<Fillstyle>(surfaceFillstyle(), &DrawingKitBase::setSurfaceFillstyle));
  setSurfaceFillstyle(s);
}

inline void DrawingKitBase::texture(Raster_ptr t)
{
  states.push(new PtrState<Raster>(texture(), &DrawingKitBase::setTexture));
  setTexture(t);
}

////////
// text
////////

inline void DrawingKitBase::fontSize(CORBA::ULong s)
{
  states.push(new SimpleState<CORBA::ULong>(fontSize(), &DrawingKitBase::setFontSize));
  setFontSize(s);
}

inline void DrawingKitBase::fontWeight(CORBA::ULong w)
{
  states.push(new SimpleState<CORBA::ULong>(fontWeight(), &DrawingKitBase::setFontWeight));
  setFontWeight(w);
}

inline void DrawingKitBase::fontFamily(const Unistring &f)
{
  states.push(new VarState<Unistring>(fontFamily(), &DrawingKitBase::setFontFamily));
  setFontFamily(f);
}

inline void DrawingKitBase::fontSubFamily(const Unistring &f)
{
  states.push(new VarState<Unistring>(fontSubFamily(), &DrawingKitBase::setFontSubFamily));
  setFontSubFamily(f);
}

inline void DrawingKitBase::fontFullName(const Unistring &f)
{
  states.push(new VarState<Unistring>(fontFullName(), &DrawingKitBase::setFontFullName));
  setFontFullName(f);
}

inline void DrawingKitBase::fontStyle(const Unistring &s)
{
  states.push(new VarState<Unistring>(fontStyle(), &DrawingKitBase::setFontStyle));
  setFontStyle(s);
}

inline void DrawingKitBase::fontAttr(const NVPair &nvp)
{
//   NVPair save;
//   save.name = nvp.name;
//   save.val = getFontAttr(nvp.name);
//   states.push(new RefState<NVPair>(save, &DrawingKitBase::setFontAttr));
//   setFontAttr(nvp);
}


#endif /* _DrawingKitBase_hh */
