//
// Copyright (c) 1987-91 Stanford University
// Copyright (c) 1991-94 Silicon Graphics, Inc.
// Copyright (c) 1993-94 Fujitsu, Ltd.
//
// Permission to use, copy, modify, distribute, and sell this software and 
// its documentation for any purpose is hereby granted without fee, provided
// that (i) the above copyright notices and this permission notice appear in
// all copies of the software and related documentation, and (ii) the names
// of Stanford, Silicon Graphics, and Fujitsu may not be used in any
// advertising or publicity relating to the software without the specific,
// prior written permission of Stanford, Silicon Graphics, and Fujitsu.
// 
// THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND, 
// EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY 
// WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  
//
// IN NO EVENT SHALL STANFORD, SILICON GRAPHICS, OR FUJITSU BE LIABLE FOR
// ANY SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
// OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
// WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF 
// LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE 
// OF THIS SOFTWARE.
//

#include "Layout/LayoutKitImpl.h"
#include "Layout/Box.h"
#include "Layout/Deck.h"
#include "Layout/Grid.h"
#include "Layout/Glue.h"
#include "Layout/Placement.h"
#include "Layout/ShapeOf.h"


// class LayoutKitImpl
// #ifdef DISABLE_DLL
// dload(LayoutKitImpl, layouts)
// #else
// dload(LayoutKitImpl)
// #endif

template <class I, class P>
P create(I *i)
{
  i->_obj_is_ready();
  return i->_this();
}

LayoutKitImpl::LayoutKitImpl() { fil_ = infinity;}
LayoutKitImpl::~LayoutKitImpl() {}
void LayoutKitImpl::fil(Coord c) { fil_ = c;}
Coord LayoutKitImpl::fil() { return fil_;}
Graphic_ptr LayoutKitImpl::clipper(Graphic_ptr g)
{
  return create<Clipper, Graphic_ptr> (new Clipper(g));
}

// Graphic_ptr LayoutKitImpl::create_backdrop() { return new Backdrop;}
// AutoScroll_ptr LayoutKitImpl::create_auto_scroll(Adjustment_ptr x_adjustment, Adjustment_ptr y_adjustment)
// {
//   return new AutoScrollImpl(x_adjustment, y_adjustment);
// }
// FullyVisibleConstraint_ptr LayoutKitImpl::create_fully_visible_constraint(Float usable, Float align)
// {
//   return new FullyVisibleConstraintImpl(usable, align);
// }
// Scrollable* LayoutKitImpl::scroll_box(Axis a)
// {
//   ScrollBox* b = nil;
//   switch (a)
//     {
//     case X_axis:
//       // unimplemented
//       break;
//     case Y_axis:
//       b = new TBScrollBox();
//       break;
//     case Z_axis:
//       // should raise an exception
//       break;
//     }
//   Scrollable* s = new Scrollable();
//   if (is_not_nil(b))
//     {
//       s->glyph_ptr = b;
//       s->adjustment_ptr = b->scroll_adjustment(Y_axis);
//     }
//   else fresco_fail("Layout kit can't create scroll box for given axis");
//   return s;
// }
// Viewport_ptr LayoutKitImpl::create_viewport(Graphic_ptr g) { return new ViewportImpl(g);}
// Stage_ptr LayoutKitImpl::create_stage() { return new StageImpl;}

Grid_ptr LayoutKitImpl::fixedGrid(const Grid::Index &upper)
{
//   GridImpl *grid = new GridImpl(upper);
//   grid->_obj_is_ready(_boa());
//   return grid->_this();
  return create<GridImpl, Grid_ptr>(new GridImpl(upper));
}

Graphic_ptr LayoutKitImpl::fixedRange(Grid_ptr g, const Grid::Range &r)
{
  return create<SubGridImpl, Graphic_ptr>(new SubGridImpl(g, r));
}


Graphic_ptr LayoutKitImpl::hbox()
{
  return create<HBox, Graphic_ptr>(new HBox);
}

Graphic_ptr LayoutKitImpl::vbox()
{
  return create<VBox, Graphic_ptr>(new HBox);
}

Graphic_ptr LayoutKitImpl::hboxFirstAligned()
{
  return create<HBoxFirstAligned, Graphic_ptr>(new HBoxFirstAligned);
}

Graphic_ptr LayoutKitImpl::vboxFirstAligned()
{
  return create<VBoxFirstAligned, Graphic_ptr>(new VBoxFirstAligned);
}

Graphic_ptr LayoutKitImpl::hboxAlignElements(Alignment align)
{
  return create<HBoxAlignElements, Graphic_ptr>(new HBoxAlignElements(align));
}

Graphic_ptr LayoutKitImpl::vboxAlignElements(Alignment align)
{
  return create<VBoxAlignElements, Graphic_ptr>(new VBoxAlignElements(align));
}

Graphic_ptr LayoutKitImpl::overlay()
{
  return create<Overlay, Graphic_ptr>(new Overlay);
}

Graphic_ptr LayoutKitImpl::deck()
{
  return create<Deck, Graphic_ptr>(new Deck);
}

Graphic_ptr LayoutKitImpl::back(Graphic_ptr g, Graphic_ptr under)
{
  return create<LayoutLayer, Graphic_ptr>(new LayoutLayer(g, under, nil));
}

Graphic_ptr LayoutKitImpl::front(Graphic_ptr g, Graphic_ptr over)
{
  return create<LayoutLayer, Graphic_ptr>(new LayoutLayer(g, nil, over));
}

Graphic_ptr LayoutKitImpl::between(Graphic_ptr g, Graphic_ptr under, Graphic_ptr over)
{
  return create<LayoutLayer, Graphic_ptr>(new LayoutLayer(g, under, over));
}

Graphic_ptr LayoutKitImpl::glue(Axis a, Coord natural, Coord stretch, Coord shrink, Alignment align)
{
  return create<Glue, Graphic_ptr>(new Glue(a, natural, stretch, shrink, align));
}

Graphic_ptr LayoutKitImpl::glueRequisition(const Graphic::Requisition &r)
{
  return create<Glue, Graphic_ptr>(new Glue(r));
}

Graphic_ptr LayoutKitImpl::hfil()
{
  return create<Glue, Graphic_ptr>(new Glue(xaxis, 0., fil_, 0., 0.));
}

Graphic_ptr LayoutKitImpl::hglueFil(Coord natural)
{
  return create<Glue, Graphic_ptr>(new Glue(xaxis, natural, fil_, 0., 0.));
}

Graphic_ptr LayoutKitImpl::hglue(Coord natural, Coord stretch, Coord shrink)
{
  return create<Glue, Graphic_ptr>(new Glue(xaxis, natural, stretch, shrink, 0.));
}

Graphic_ptr LayoutKitImpl::hglueAligned(Coord natural, Coord stretch, Coord shrink, Alignment a)
{
  return create<Glue, Graphic_ptr>(new Glue(xaxis, natural, stretch, shrink, a));
}

Graphic_ptr LayoutKitImpl::hspace(Coord natural)
{
  return create<Glue, Graphic_ptr>(new Glue(xaxis, natural, 0., 0., 0.));
}

Graphic_ptr LayoutKitImpl::vfil()
{
  return create<Glue, Graphic_ptr>(new Glue(yaxis, 0., fil_, 0., 0.));
}

Graphic_ptr LayoutKitImpl::vglueFil(Coord natural)
{
  return create<Glue, Graphic_ptr>(new Glue(yaxis, natural, fil_, 0., 0.));
}

Graphic_ptr LayoutKitImpl::vglue(Coord natural, Coord stretch, Coord shrink)
{
  return create<Glue, Graphic_ptr>(new Glue(yaxis, natural, stretch, shrink, 0.));
}

Graphic_ptr LayoutKitImpl::vglueAligned(Coord natural, Coord stretch, Coord shrink, Alignment a)
{
  return create<Glue, Graphic_ptr>(new Glue(yaxis, natural, stretch, shrink, a));
}

Graphic_ptr LayoutKitImpl::vspace(Coord natural)
{
  return create<Glue, Graphic_ptr>(new Glue(yaxis, natural, 0., 0., 0.));
}

Graphic_ptr LayoutKitImpl::shapeOf(Graphic_ptr g)
{
  return create<ShapeOf, Graphic_ptr>(new ShapeOf(g, 0, 0));
}

Graphic_ptr LayoutKitImpl::shapeOfXY(Graphic_ptr gx, Graphic_ptr gy)
{
  return create<ShapeOf, Graphic_ptr>(new ShapeOf(gx, gy, 0));
}

Graphic_ptr LayoutKitImpl::shape_of_xyz(Graphic_ptr gx, Graphic_ptr gy, Graphic_ptr gz)
{
  return create<ShapeOf, Graphic_ptr>(new ShapeOf(gx, gy, gz));
}

// Graphic_ptr LayoutKitImpl::strut(Font_ptr f, Coord natural, Coord stretch, Coord shrink)
// {
//   return new Strut(f, natural, stretch, shrink);
// }

// Graphic_ptr LayoutKitImpl::hstrut(Coord right_bearing, Coord left_bearing, Coord natural, Coord stretch, Coord shrink)
// {
//   return new HStrut(right_bearing, left_bearing, natural, stretch, shrink);
// }

// Graphic_ptr LayoutKitImpl::vstrut(Coord ascent, Coord descent, Coord natural, Coord stretch, Coord shrink)
// {
//   return new VStrut(ascent, descent, natural, stretch, shrink);
// }

// Graphic_ptr LayoutKitImpl::spaces(Long count, Coord each, Font_ptr f, Color_ptr c)
// {
//   return new Space(count, each, f, c);
// }

Graphic_ptr LayoutKitImpl::align(Graphic_ptr g, Alignment x, Alignment y)
{
  return create<Placement, Graphic_ptr>(new Placement(g, new LayoutSuperpose(new LayoutCenter(xaxis, x),
									     new LayoutCenter(yaxis, y))));
}

Graphic_ptr LayoutKitImpl::alignAxis(Graphic_ptr g, Axis a, Alignment align)
{
  return create<Placement, Graphic_ptr>(new Placement(g, new LayoutCenter(a, align)));
}
 
Graphic_ptr LayoutKitImpl::halign(Graphic_ptr g, Alignment x)
{
  return alignAxis(g, xaxis, x);
}
 
Graphic_ptr LayoutKitImpl::valign(Graphic_ptr g, Alignment y)
{
  return alignAxis(g, yaxis, y);
}

Graphic_ptr LayoutKitImpl::fixed(Graphic_ptr g, Coord x, Coord y)
{
  return create<Placement, Graphic_ptr>(new Placement(g, new LayoutSuperpose(new LayoutFixed(xaxis, x),
									     new LayoutFixed(yaxis, y))));
}

Graphic_ptr LayoutKitImpl::fixedAxis(Graphic_ptr g, Axis a, Coord size)
{
  return create<Placement, Graphic_ptr>(new Placement(g, new LayoutFixed(a, size)));
}

Graphic_ptr LayoutKitImpl::hfixed(Graphic_ptr g, Coord x)
{
  return fixedAxis(g, xaxis, x);
}

Graphic_ptr LayoutKitImpl::vfixed(Graphic_ptr g, Coord y)
{
  return fixedAxis(g, yaxis, y);
}

Graphic_ptr LayoutKitImpl::flexible(Graphic_ptr g, Coord stretch, Coord shrink)
{
  return create<Placement, Graphic_ptr>(new Placement(g, new LayoutSuperpose(new LayoutVariable(xaxis, stretch, shrink),
									     new LayoutVariable(yaxis, stretch, shrink))));
}

Graphic_ptr LayoutKitImpl::flexibleFil(Graphic_ptr g)
{
  return flexible(g, fil_, 0.);
}

Graphic_ptr LayoutKitImpl::flexibleAxis(Graphic_ptr g, Axis a, Coord stretch, Coord shrink)
{
  return create<Placement, Graphic_ptr>(new Placement(g, new LayoutVariable(a, stretch, shrink)));
}

Graphic_ptr LayoutKitImpl::hflexible(Graphic_ptr g, Coord stretch, Coord shrink)
{
  return flexibleAxis(g, xaxis, stretch, shrink);
}

Graphic_ptr LayoutKitImpl::vflexible(Graphic_ptr g, Coord stretch, Coord shrink)
{
  return flexibleAxis(g, yaxis, stretch, shrink);
}

Graphic_ptr LayoutKitImpl::natural(Graphic_ptr g, Coord x, Coord y)
{
  return create<Placement, Graphic_ptr>(new Placement(g, new LayoutSuperpose(new LayoutNatural(xaxis, x),
									     new LayoutNatural(yaxis, y))));
}

Graphic_ptr LayoutKitImpl::naturalAxis(Graphic_ptr g, Axis a, Coord size)
{
  return create<Placement, Graphic_ptr>(new Placement(g, new LayoutNatural(a, size)));
}

Graphic_ptr LayoutKitImpl::hnatural(Graphic_ptr g, Coord x)
{
  return naturalAxis(g, xaxis, x);
}

Graphic_ptr LayoutKitImpl::vnatural(Graphic_ptr g, Coord y)
{
  return naturalAxis(g, yaxis, y);
}

Graphic_ptr LayoutKitImpl::margin(Graphic_ptr g, Coord all)
{
  return create<Placement, Graphic_ptr>(new Placement(g, new LayoutMargin(all)));
}

Graphic_ptr LayoutKitImpl::marginFlexible(Graphic_ptr g, Coord margin, Coord stretch, Coord shrink)
{
  return create<Placement, Graphic_ptr>(new Placement(g, new LayoutMargin(margin, stretch, shrink, margin, stretch, shrink,
									  margin, stretch, shrink, margin, stretch, shrink)));
}

Graphic_ptr LayoutKitImpl::marginLRBT(Graphic_ptr g, Coord lmargin, Coord rmargin, Coord bmargin, Coord tmargin)
{
  return create<Placement, Graphic_ptr>(new Placement(g, new LayoutMargin(lmargin, rmargin, bmargin, tmargin)));
}

Graphic_ptr LayoutKitImpl::marginLRBTFlexible(Graphic_ptr g, Coord lmargin, Coord lstretch, Coord lshrink,
					      Coord rmargin, Coord rstretch, Coord rshrink,
					      Coord bmargin, Coord bstretch, Coord bshrink,
					      Coord tmargin, Coord tstretch, Coord tshrink)
{
  return create<Placement, Graphic_ptr>(new Placement(g, new LayoutMargin(lmargin, lstretch, lshrink, rmargin, rstretch, rshrink,
									  bmargin, bstretch, bshrink, tmargin, tstretch, tshrink)));
}

Graphic_ptr LayoutKitImpl::hmargin(Graphic_ptr g, Coord both)
{
  return marginLRBT(g, both, both, 0., 0.);
}

Graphic_ptr LayoutKitImpl::hmarginLR(Graphic_ptr g, Coord lmargin, Coord rmargin)
{
  return marginLRBT(g, lmargin, rmargin, 0., 0.);
}

Graphic_ptr LayoutKitImpl::hmarginLRFlexible(Graphic_ptr g, Coord lmargin, Coord lstretch, Coord lshrink,
					     Coord rmargin, Coord rstretch, Coord rshrink)
{
  return marginLRBTFlexible(g, lmargin, lstretch, lshrink, rmargin, rstretch, rshrink,
			    0., 0., 0., 0., 0., 0.);
}

Graphic_ptr LayoutKitImpl::vmargin(Graphic_ptr g, Coord both) { return marginLRBT(g, 0., 0., both, both);}

Graphic_ptr LayoutKitImpl::vmarginBT(Graphic_ptr g, Coord bmargin, Coord tmargin)
{
  return marginLRBT(g, 0., 0., bmargin, tmargin);
}

Graphic_ptr LayoutKitImpl::vmarginBTFlexible(Graphic_ptr g, Coord bmargin, Coord bstretch, Coord bshrink,
					     Coord tmargin, Coord tstretch, Coord tshrink)
{
  return marginLRBTFlexible(g, 0., 0., 0., 0., 0., 0., bmargin, bstretch, bshrink, tmargin, tstretch, tshrink);
}

Graphic_ptr LayoutKitImpl::lmargin(Graphic_ptr g, Coord natural)
{
  return marginLRBT(g, natural, 0., 0., 0.);
}

Graphic_ptr LayoutKitImpl::lmarginFlexible(Graphic_ptr g, Coord natural, Coord stretch, Coord shrink)
{
  return marginLRBTFlexible(g, natural, stretch, shrink, 0., 0., 0., 0., 0., 0., 0., 0., 0.);
}

Graphic_ptr LayoutKitImpl::rmargin(Graphic_ptr g, Coord natural)
{
  return marginLRBT(g, 0., natural, 0., 0.);
}

Graphic_ptr LayoutKitImpl::rmarginFlexible(Graphic_ptr g, Coord natural, Coord stretch, Coord shrink)
{
  return marginLRBTFlexible(g, 0., 0., 0., natural, stretch, shrink, 0., 0., 0., 0., 0., 0.);
}

Graphic_ptr LayoutKitImpl::bmargin(Graphic_ptr g, Coord natural)
{
  return marginLRBT(g, 0., 0., natural, 0.);
}

Graphic_ptr LayoutKitImpl::bmarginFlexible(Graphic_ptr g, Coord natural, Coord stretch, Coord shrink)
{
  return marginLRBTFlexible(g, 0., 0., 0., 0., 0., 0., natural, stretch, shrink, 0., 0., 0.);
}

Graphic_ptr LayoutKitImpl::tmargin(Graphic_ptr g, Coord natural)
{
  return marginLRBT(g, 0., 0., 0., natural);
}

Graphic_ptr LayoutKitImpl::tmarginFlexible(Graphic_ptr g, Coord natural, Coord stretch, Coord shrink)
{
  return marginLRBTFlexible(g, 0., 0., 0., 0., 0., 0., 0., 0., 0., natural, stretch, shrink);
}
