/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@fresco.org> 
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
#ifndef _LayoutKitImpl_hh
#define _LayoutKitImpl_hh

#include <Fresco/config.hh>
#include <Fresco/LayoutKit.hh>
#include <Berlin/KitImpl.hh>
#include <vector>

class GraphicImpl;

namespace Berlin {
namespace LayoutKit {

class LayoutKitImpl : public virtual POA_Fresco::LayoutKit,
		      public KitImpl
{
public:
  LayoutKitImpl(const std::string &, const Fresco::Kit::PropertySeq &);
  ~LayoutKitImpl();
  virtual KitImpl *clone(const Fresco::Kit::PropertySeq &p) { return new LayoutKitImpl(repo_id(), p);}

  virtual Fresco::Coord fill();
  virtual void fill(Fresco::Coord);
  virtual Fresco::Graphic_ptr clipper(Fresco::Graphic_ptr);
//   virtual Graphic_ptr create_backdrop();
//   virtual AutoScroll_ptr create_auto_scroll(Adjustment_ptr x_adjustment, Adjustment_ptr y_adjustment);
//   virtual FullyVisibleConstraint_ptr create_fully_visible_constraint(Float usable, Float align);
//   virtual Scrollable* scroll_box(Axis a);
  virtual Layout::Viewport_ptr scrollable(Fresco::Graphic_ptr);
//   virtual Layout::Splitter_ptr splitter(Fresco::Graphic_ptr, Fresco::Graphic_ptr, Fresco::Axis);
  virtual Layout::Stage_ptr create_stage();
  virtual Layout::Grid_ptr fixed_grid(const Layout::Grid::Index &);
  virtual Fresco::Graphic_ptr fixed_range(Layout::Grid_ptr g, const Layout::Grid::Range &);
  virtual Fresco::Graphic_ptr hbox();
  virtual Fresco::Graphic_ptr vbox();
  virtual Fresco::Graphic_ptr hbox_first_aligned();
  virtual Fresco::Graphic_ptr vbox_first_aligned();
  virtual Fresco::Graphic_ptr hbox_align_elements(Fresco::Alignment);
  virtual Fresco::Graphic_ptr vbox_align_elements(Fresco::Alignment);
  virtual Fresco::Graphic_ptr overlay();
  virtual Fresco::Graphic_ptr deck();
  virtual Fresco::Graphic_ptr back(Fresco::Graphic_ptr, Fresco::Graphic_ptr);
  virtual Fresco::Graphic_ptr front(Fresco::Graphic_ptr, Fresco::Graphic_ptr);
  virtual Fresco::Graphic_ptr between(Fresco::Graphic_ptr, Fresco::Graphic_ptr, Fresco::Graphic_ptr);
  virtual Fresco::Graphic_ptr glue(Fresco::Axis, Fresco::Coord, Fresco::Coord, Fresco::Coord, Fresco::Alignment);
  virtual Fresco::Graphic_ptr glue_requisition(const Fresco::Graphic::Requisition &);
  virtual Fresco::Graphic_ptr hfill();
  virtual Fresco::Graphic_ptr hglue_fill(Fresco::Coord);
  virtual Fresco::Graphic_ptr hglue(Fresco::Coord, Fresco::Coord, Fresco::Coord);
  virtual Fresco::Graphic_ptr hglue_aligned(Fresco::Coord, Fresco::Coord, Fresco::Coord, Fresco::Alignment);
  virtual Fresco::Graphic_ptr hspace(Fresco::Coord);
  virtual Fresco::Graphic_ptr vfill();
  virtual Fresco::Graphic_ptr vglue_fill(Fresco::Coord);
  virtual Fresco::Graphic_ptr vglue(Fresco::Coord, Fresco::Coord, Fresco::Coord);
  virtual Fresco::Graphic_ptr vglue_aligned(Fresco::Coord, Fresco::Coord, Fresco::Coord, Fresco::Alignment);
  virtual Fresco::Graphic_ptr vspace(Fresco::Coord);
  virtual Fresco::Graphic_ptr shape_of(Fresco::Graphic_ptr g);
  virtual Fresco::Graphic_ptr shape_of_xy(Fresco::Graphic_ptr, Fresco::Graphic_ptr);
  virtual Fresco::Graphic_ptr shape_of_xyz(Fresco::Graphic_ptr, Fresco::Graphic_ptr, Fresco::Graphic_ptr);
  virtual Fresco::Graphic_ptr align(Fresco::Graphic_ptr, Fresco::Alignment, Fresco::Alignment);
  virtual Fresco::Graphic_ptr align_axis(Fresco::Graphic_ptr, Fresco::Axis, Fresco::Alignment);
  virtual Fresco::Graphic_ptr halign(Fresco::Graphic_ptr, Fresco::Alignment);
  virtual Fresco::Graphic_ptr valign(Fresco::Graphic_ptr, Fresco::Alignment);
  virtual Fresco::Graphic_ptr fixed_size(Fresco::Graphic_ptr, Fresco::Coord, Fresco::Coord);
  virtual Fresco::Graphic_ptr fixed_axis(Fresco::Graphic_ptr, Fresco::Axis, Fresco::Coord);
  virtual Fresco::Graphic_ptr hfixed(Fresco::Graphic_ptr, Fresco::Coord);
  virtual Fresco::Graphic_ptr vfixed(Fresco::Graphic_ptr, Fresco::Coord);
  virtual Fresco::Graphic_ptr flexible(Fresco::Graphic_ptr, Fresco::Coord, Fresco::Coord);
  virtual Fresco::Graphic_ptr flexible_fill(Fresco::Graphic_ptr);
  virtual Fresco::Graphic_ptr flexible_axis(Fresco::Graphic_ptr, Fresco::Axis, Fresco::Coord, Fresco::Coord);
  virtual Fresco::Graphic_ptr hflexible(Fresco::Graphic_ptr, Fresco::Coord, Fresco::Coord);
  virtual Fresco::Graphic_ptr vflexible(Fresco::Graphic_ptr, Fresco::Coord, Fresco::Coord);
  virtual Fresco::Graphic_ptr natural(Fresco::Graphic_ptr, Fresco::Coord, Fresco::Coord);
  virtual Fresco::Graphic_ptr natural_axis(Fresco::Graphic_ptr, Fresco::Axis, Fresco::Coord);
  virtual Fresco::Graphic_ptr hnatural(Fresco::Graphic_ptr, Fresco::Coord);
  virtual Fresco::Graphic_ptr vnatural(Fresco::Graphic_ptr, Fresco::Coord);
  virtual Fresco::Graphic_ptr margin(Fresco::Graphic_ptr, Fresco::Coord);
  virtual Fresco::Graphic_ptr margin_lrbt(Fresco::Graphic_ptr, Fresco::Coord, Fresco::Coord, Fresco::Coord, Fresco::Coord);
  virtual Fresco::Graphic_ptr margin_flexible(Fresco::Graphic_ptr, Fresco::Coord, Fresco::Coord, Fresco::Coord);
  virtual Fresco::Graphic_ptr margin_lrbt_flexible(Fresco::Graphic_ptr, Fresco::Coord, Fresco::Coord, Fresco::Coord,
						   Fresco::Coord, Fresco::Coord, Fresco::Coord,
						   Fresco::Coord, Fresco::Coord, Fresco::Coord,
						   Fresco::Coord, Fresco::Coord, Fresco::Coord);
  virtual Fresco::Graphic_ptr hmargin(Fresco::Graphic_ptr, Fresco::Coord);
  virtual Fresco::Graphic_ptr hmargin_lr(Fresco::Graphic_ptr, Fresco::Coord, Fresco::Coord);
  virtual Fresco::Graphic_ptr hmargin_lr_flexible(Fresco::Graphic_ptr, Fresco::Coord, Fresco::Coord, Fresco::Coord,
						  Fresco::Coord, Fresco::Coord, Fresco::Coord);
  virtual Fresco::Graphic_ptr vmargin(Fresco::Graphic_ptr, Fresco::Coord);
  virtual Fresco::Graphic_ptr vmargin_bt(Fresco::Graphic_ptr, Fresco::Coord, Fresco::Coord);
  virtual Fresco::Graphic_ptr vmargin_bt_flexible(Fresco::Graphic_ptr, Fresco::Coord, Fresco::Coord, Fresco::Coord,
						  Fresco::Coord, Fresco::Coord, Fresco::Coord);
  virtual Fresco::Graphic_ptr lmargin(Fresco::Graphic_ptr, Fresco::Coord);
  virtual Fresco::Graphic_ptr lmargin_flexible(Fresco::Graphic_ptr, Fresco::Coord, Fresco::Coord, Fresco::Coord);
  virtual Fresco::Graphic_ptr rmargin(Fresco::Graphic_ptr, Fresco::Coord);
  virtual Fresco::Graphic_ptr rmargin_flexible(Fresco::Graphic_ptr, Fresco::Coord, Fresco::Coord, Fresco::Coord);
  virtual Fresco::Graphic_ptr bmargin(Fresco::Graphic_ptr, Fresco::Coord);
  virtual Fresco::Graphic_ptr bmargin_flexible(Fresco::Graphic_ptr, Fresco::Coord, Fresco::Coord, Fresco::Coord);
  virtual Fresco::Graphic_ptr tmargin(Fresco::Graphic_ptr, Fresco::Coord);
  virtual Fresco::Graphic_ptr tmargin_flexible(Fresco::Graphic_ptr, Fresco::Coord, Fresco::Coord, Fresco::Coord);
private:
  Fresco::Coord _fill;
};

} // namespace
} // namespace

#endif
