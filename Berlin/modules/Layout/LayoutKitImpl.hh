/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@berlin-consortium.org> 
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
#ifndef _LayoutKitImpl_hh
#define _LayoutKitImpl_hh

#include <Warsaw/config.hh>
#include <Warsaw/LayoutKit.hh>
#include <Berlin/KitImpl.hh>
#include <vector>

class GraphicImpl;

class LayoutKitImpl : public virtual POA_Warsaw::LayoutKit,
		      public KitImpl
{
public:
  LayoutKitImpl(KitFactory *, const Warsaw::Kit::PropertySeq &);
  ~LayoutKitImpl();
  virtual Warsaw::Coord fil();
  virtual void fil(Warsaw::Coord);
  virtual Warsaw::Graphic_ptr clipper(Warsaw::Graphic_ptr);
//   virtual Graphic_ptr create_backdrop();
//   virtual AutoScroll_ptr create_auto_scroll(Adjustment_ptr x_adjustment, Adjustment_ptr y_adjustment);
//   virtual FullyVisibleConstraint_ptr create_fully_visible_constraint(Float usable, Float align);
//   virtual Scrollable* scroll_box(Axis a);
  virtual Warsaw::Viewport_ptr scrollable(Warsaw::Graphic_ptr);
  virtual Warsaw::Stage_ptr createStage();
  virtual Warsaw::Grid_ptr fixedGrid(const Warsaw::Grid::Index &);
  virtual Warsaw::Graphic_ptr fixedRange(Warsaw::Grid_ptr g, const Warsaw::Grid::Range &);
  virtual Warsaw::Graphic_ptr hbox();
  virtual Warsaw::Graphic_ptr vbox();
  virtual Warsaw::Graphic_ptr hboxFirstAligned();
  virtual Warsaw::Graphic_ptr vboxFirstAligned();
  virtual Warsaw::Graphic_ptr hboxAlignElements(Warsaw::Alignment);
  virtual Warsaw::Graphic_ptr vboxAlignElements(Warsaw::Alignment);
  virtual Warsaw::Graphic_ptr overlay();
  virtual Warsaw::Graphic_ptr deck();
  virtual Warsaw::Graphic_ptr back(Warsaw::Graphic_ptr, Warsaw::Graphic_ptr);
  virtual Warsaw::Graphic_ptr front(Warsaw::Graphic_ptr, Warsaw::Graphic_ptr);
  virtual Warsaw::Graphic_ptr between(Warsaw::Graphic_ptr, Warsaw::Graphic_ptr, Warsaw::Graphic_ptr);
  virtual Warsaw::Graphic_ptr glue(Warsaw::Axis, Warsaw::Coord, Warsaw::Coord, Warsaw::Coord, Warsaw::Alignment);
  virtual Warsaw::Graphic_ptr glueRequisition(const Warsaw::Graphic::Requisition &);
  virtual Warsaw::Graphic_ptr hfil();
  virtual Warsaw::Graphic_ptr hglueFil(Warsaw::Coord);
  virtual Warsaw::Graphic_ptr hglue(Warsaw::Coord, Warsaw::Coord, Warsaw::Coord);
  virtual Warsaw::Graphic_ptr hglueAligned(Warsaw::Coord, Warsaw::Coord, Warsaw::Coord, Warsaw::Alignment);
  virtual Warsaw::Graphic_ptr hspace(Warsaw::Coord);
  virtual Warsaw::Graphic_ptr vfil();
  virtual Warsaw::Graphic_ptr vglueFil(Warsaw::Coord);
  virtual Warsaw::Graphic_ptr vglue(Warsaw::Coord, Warsaw::Coord, Warsaw::Coord);
  virtual Warsaw::Graphic_ptr vglueAligned(Warsaw::Coord, Warsaw::Coord, Warsaw::Coord, Warsaw::Alignment);
  virtual Warsaw::Graphic_ptr vspace(Warsaw::Coord);
  virtual Warsaw::Graphic_ptr shapeOf(Warsaw::Graphic_ptr g);
  virtual Warsaw::Graphic_ptr shapeOfXY(Warsaw::Graphic_ptr, Warsaw::Graphic_ptr);
  virtual Warsaw::Graphic_ptr shapeOfXYZ(Warsaw::Graphic_ptr, Warsaw::Graphic_ptr, Warsaw::Graphic_ptr);
  virtual Warsaw::Graphic_ptr align(Warsaw::Graphic_ptr, Warsaw::Alignment, Warsaw::Alignment);
  virtual Warsaw::Graphic_ptr alignAxis(Warsaw::Graphic_ptr, Warsaw::Axis, Warsaw::Alignment);
  virtual Warsaw::Graphic_ptr halign(Warsaw::Graphic_ptr, Warsaw::Alignment);
  virtual Warsaw::Graphic_ptr valign(Warsaw::Graphic_ptr, Warsaw::Alignment);
  virtual Warsaw::Graphic_ptr fixedSize(Warsaw::Graphic_ptr, Warsaw::Coord, Warsaw::Coord);
  virtual Warsaw::Graphic_ptr fixedAxis(Warsaw::Graphic_ptr, Warsaw::Axis, Warsaw::Coord);
  virtual Warsaw::Graphic_ptr hfixed(Warsaw::Graphic_ptr, Warsaw::Coord);
  virtual Warsaw::Graphic_ptr vfixed(Warsaw::Graphic_ptr, Warsaw::Coord);
  virtual Warsaw::Graphic_ptr flexible(Warsaw::Graphic_ptr, Warsaw::Coord, Warsaw::Coord);
  virtual Warsaw::Graphic_ptr flexibleFil(Warsaw::Graphic_ptr);
  virtual Warsaw::Graphic_ptr flexibleAxis(Warsaw::Graphic_ptr, Warsaw::Axis, Warsaw::Coord, Warsaw::Coord);
  virtual Warsaw::Graphic_ptr hflexible(Warsaw::Graphic_ptr, Warsaw::Coord, Warsaw::Coord);
  virtual Warsaw::Graphic_ptr vflexible(Warsaw::Graphic_ptr, Warsaw::Coord, Warsaw::Coord);
  virtual Warsaw::Graphic_ptr natural(Warsaw::Graphic_ptr, Warsaw::Coord, Warsaw::Coord);
  virtual Warsaw::Graphic_ptr naturalAxis(Warsaw::Graphic_ptr, Warsaw::Axis, Warsaw::Coord);
  virtual Warsaw::Graphic_ptr hnatural(Warsaw::Graphic_ptr, Warsaw::Coord);
  virtual Warsaw::Graphic_ptr vnatural(Warsaw::Graphic_ptr, Warsaw::Coord);
  virtual Warsaw::Graphic_ptr margin(Warsaw::Graphic_ptr, Warsaw::Coord);
  virtual Warsaw::Graphic_ptr marginLRBT(Warsaw::Graphic_ptr, Warsaw::Coord, Warsaw::Coord, Warsaw::Coord, Warsaw::Coord);
  virtual Warsaw::Graphic_ptr marginFlexible(Warsaw::Graphic_ptr, Warsaw::Coord, Warsaw::Coord, Warsaw::Coord);
  virtual Warsaw::Graphic_ptr marginLRBTFlexible(Warsaw::Graphic_ptr, Warsaw::Coord, Warsaw::Coord, Warsaw::Coord,
						 Warsaw::Coord, Warsaw::Coord, Warsaw::Coord,
						 Warsaw::Coord, Warsaw::Coord, Warsaw::Coord,
						 Warsaw::Coord, Warsaw::Coord, Warsaw::Coord);
  virtual Warsaw::Graphic_ptr hmargin(Warsaw::Graphic_ptr, Warsaw::Coord);
  virtual Warsaw::Graphic_ptr hmarginLR(Warsaw::Graphic_ptr, Warsaw::Coord, Warsaw::Coord);
  virtual Warsaw::Graphic_ptr hmarginLRFlexible(Warsaw::Graphic_ptr, Warsaw::Coord, Warsaw::Coord, Warsaw::Coord,
						Warsaw::Coord, Warsaw::Coord, Warsaw::Coord);
  virtual Warsaw::Graphic_ptr vmargin(Warsaw::Graphic_ptr, Warsaw::Coord);
  virtual Warsaw::Graphic_ptr vmarginBT(Warsaw::Graphic_ptr, Warsaw::Coord, Warsaw::Coord);
  virtual Warsaw::Graphic_ptr vmarginBTFlexible(Warsaw::Graphic_ptr, Warsaw::Coord, Warsaw::Coord, Warsaw::Coord,
						Warsaw::Coord, Warsaw::Coord, Warsaw::Coord);
  virtual Warsaw::Graphic_ptr lmargin(Warsaw::Graphic_ptr, Warsaw::Coord);
  virtual Warsaw::Graphic_ptr lmarginFlexible(Warsaw::Graphic_ptr, Warsaw::Coord, Warsaw::Coord, Warsaw::Coord);
  virtual Warsaw::Graphic_ptr rmargin(Warsaw::Graphic_ptr, Warsaw::Coord);
  virtual Warsaw::Graphic_ptr rmarginFlexible(Warsaw::Graphic_ptr, Warsaw::Coord, Warsaw::Coord, Warsaw::Coord);
  virtual Warsaw::Graphic_ptr bmargin(Warsaw::Graphic_ptr, Warsaw::Coord);
  virtual Warsaw::Graphic_ptr bmarginFlexible(Warsaw::Graphic_ptr, Warsaw::Coord, Warsaw::Coord, Warsaw::Coord);
  virtual Warsaw::Graphic_ptr tmargin(Warsaw::Graphic_ptr, Warsaw::Coord);
  virtual Warsaw::Graphic_ptr tmarginFlexible(Warsaw::Graphic_ptr, Warsaw::Coord, Warsaw::Coord, Warsaw::Coord);
private:
  template <typename I, typename Im>
  typename I::_ptr_type create(Im *impl)
  {
    activate(impl);
    return impl->_this();
  }

  Warsaw::Coord fil_;
};

#endif
