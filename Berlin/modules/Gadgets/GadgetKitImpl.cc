/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 2000 Stefan Seefeld <stefan@fresco.org>
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
#include <Fresco/config.hh>
#include <Fresco/View.hh>
#include <Fresco/Transform.hh>
#include <Fresco/DrawingKit.hh>
#include <Fresco/BoundedValue.hh>
#include <Fresco/DrawTraversal.hh>
#include <Fresco/PickTraversal.hh>
#include <Fresco/resolve.hh>
#include <Berlin/ImplVar.hh>
#include <Berlin/ViewImpl.hh>
#include <Berlin/MonoGraphic.hh>
#include <Berlin/RefCountVar.hh>
#include "GadgetKitImpl.hh"
#include <cmath>

using namespace Fresco;

using namespace Berlin::GadgetKit;

// class AlphaAdjuster : public virtual POA_View, public MonoGraphic
// {
//   public:
//     virtual void traverse(Traversal_ptr traversal)
//     { traversal->visit(Graphic_var(_this())); }
//     virtual void draw(DrawTraversal_ptr traversal)
//     {
//         DrawingKit_var kit = traversal->kit();
// 	   kit->saveState();
// 	   Color color = kit->foreground();
// 	   color.alpha *= my_alpha;
// 	   kit->foreground(color);
// 	   MonoGraphic::traverse(traversal);
// 	   kit->restoreState();
//     }
//     virtual void pick(PickTraversal_ptr traversal)
//     { MonoGraphic::traverse(traversal); }

//     virtual void update(const CORBA::Any &any)
//     { any >>= my_alpha; needRedraw(); }
//   private:
//     Coord my_alpha;
// };

namespace Berlin
{
  namespace GadgetKit
  {
    class RGBAdjuster : public virtual ViewImpl, public MonoGraphic
    {
      public:
        RGBAdjuster(BoundedValue_ptr r, BoundedValue_ptr g,
		    BoundedValue_ptr b) :
	    my_red(RefCount_var<BoundedValue>::increment(r)),
	    my_green(RefCount_var<BoundedValue>::increment(g)),
	    my_blue(RefCount_var<BoundedValue>::increment(b))
        {
            my_color.red = my_red->value();
            my_color.green = my_green->value();
            my_color.blue = my_blue->value();
        }
        virtual void traverse(Traversal_ptr traversal)
        { traversal->visit(Graphic_var(_this())); }
        virtual void draw(DrawTraversal_ptr traversal)
        {
            DrawingKit_var drawing = traversal->drawing();
            drawing->save();
            Color tmp = drawing->foreground();
            my_color.alpha = tmp.alpha;
            drawing->foreground(my_color);
            MonoGraphic::traverse(traversal);
            drawing->restore();
        }
        virtual void pick(PickTraversal_ptr traversal)
        { MonoGraphic::traverse(traversal); }

        virtual void update(const CORBA::Any &)
        {
            my_color.red = my_red->value();
            my_color.green = my_green->value();
            my_color.blue = my_blue->value();
            need_redraw();
        }
      private:
        RefCount_var<BoundedValue> my_red, my_green, my_blue;
        Color my_color;
    };

    class AlphaAdjuster : public virtual ViewImpl,
                          public MonoGraphic
    {
      public:
        AlphaAdjuster(BoundedValue_ptr v) : my_alpha(v->value()) { }
        virtual void traverse(Traversal_ptr traversal)
        { traversal->visit(Graphic_var(_this())); }
        virtual void draw(DrawTraversal_ptr traversal)
        {
            DrawingKit_var drawing = traversal->drawing();
            drawing->save();
            Color color = drawing->foreground();
            color.alpha *= my_alpha;
            drawing->foreground(color);
            MonoGraphic::traverse(traversal);
            drawing->restore();
        }
        virtual void pick(PickTraversal_ptr traversal)
        { MonoGraphic::traverse(traversal); }

        virtual void update(const CORBA::Any &any)
	{ any >>= my_alpha; need_redraw(); }
      private:
        Coord my_alpha;
    };

    class LightingAdjuster : public virtual ViewImpl, public MonoGraphic
    {
      public:
        LightingAdjuster(BoundedValue_ptr r, BoundedValue_ptr g,
			 BoundedValue_ptr b) :
          my_red(RefCount_var<BoundedValue>::increment(r)),
          my_green(RefCount_var<BoundedValue>::increment(g)),
          my_blue(RefCount_var<BoundedValue>::increment(b))
        {
            my_color.red = my_red->value();
            my_color.green = my_green->value();
            my_color.blue = my_blue->value();
        }
        virtual void traverse(Traversal_ptr traversal)
        { traversal->visit(Graphic_var(_this())); }
        virtual void draw(DrawTraversal_ptr traversal)
        {
            DrawingKit_var drawing = traversal->drawing();
            drawing->save();
            Color tmp = drawing->lighting();
            // how is the light attribute concatenated, subtractive,
	    // additive ? -stefan
            tmp.red *= my_color.red;
            tmp.green *= my_color.green;
            tmp.blue *= my_color.blue;
            drawing->lighting(tmp);
            MonoGraphic::traverse(traversal);
            drawing->restore();
        }
        virtual void pick(PickTraversal_ptr traversal)
        { MonoGraphic::traverse(traversal); }

        virtual void update(const CORBA::Any &)
        {
            my_color.red = my_red->value();
            my_color.green = my_green->value();
            my_color.blue = my_blue->value();
            need_redraw();
        }
      private:
        RefCount_var<BoundedValue> my_red, my_green, my_blue;
        Color my_color;
    };

    class RotationAdjuster : public virtual ViewImpl, public MonoGraphic
    {
      public:
        RotationAdjuster(Axis a) : my_axis(a) { }
        virtual void update(const CORBA::Any &any)
        {
            Graphic_var child = body(); if (CORBA::is_nil(child)) return;
            Transform_var transformation =
		child->transformation();
	    if (CORBA::is_nil(transformation)) return;
            Coord phi;
            any >>= phi;
            transformation->load_identity();
            transformation->rotate(phi, my_axis);
            need_resize();
        }
      private:
        Axis my_axis;
    };

    class ZoomAdjuster : public virtual ViewImpl, public MonoGraphic
    {
      public:
        virtual void update(const CORBA::Any &any)
        {
            Graphic_var child = body();
	    if (CORBA::is_nil(child)) return;
            Transform_var transformation =
            child->transformation();
	    if (CORBA::is_nil(transformation)) return;
            Coord scale;
            any >>= scale;
            Vertex s;
            s.x = s.y = s.z = exp(scale);
            transformation->load_identity();
            transformation->scale(s);
            need_resize();
        }
    };

  } // namespace
} // namespace

GadgetKitImpl::GadgetKitImpl(const std::string &id,
                             const Fresco::Kit::PropertySeq &p,
                             ServerContextImpl *c) :
    KitImpl(id, p, c)
{ }
GadgetKitImpl::~GadgetKitImpl() { }
void GadgetKitImpl::bind(ServerContext_ptr context)
{
    KitImpl::bind(context);
    Fresco::Kit::PropertySeq props;
    props.length(0);
    my_command =
	resolve_kit<CommandKit>(context,
				"IDL:fresco.org/Fresco/CommandKit:1.0",
				props);
    my_figure =
	resolve_kit<FigureKit>(context,
			       "IDL:fresco.org/Fresco/FigureKit:1.0",
			       props);
}


Graphic_ptr GadgetKitImpl::rgb(Graphic_ptr gg,
                               BoundedValue_ptr r,
                               BoundedValue_ptr g,
                               BoundedValue_ptr b)
{
    Graphic_var adjuster =
      create_and_set_body<Graphic>(new RGBAdjuster(r, g, b), gg,
                                   "FadgetKit/rgb");
    r->attach(Observer_ptr(Graphic_ptr(adjuster)));
    g->attach(Observer_ptr(Graphic_ptr(adjuster)));
    b->attach(Observer_ptr(Graphic_ptr(adjuster)));
    return adjuster;
}

Graphic_ptr GadgetKitImpl::alpha(Graphic_ptr g, BoundedValue_ptr value)
{
    Graphic_var adjuster =
      create_and_set_body<Graphic>(new AlphaAdjuster(value), g,
                                   "GadgetKit/alpha");
    value->attach(Observer_ptr(Graphic_ptr(adjuster)));
    return adjuster;
}

Graphic_ptr GadgetKitImpl::lighting(Graphic_ptr gg,
                                    BoundedValue_ptr r,
                                    BoundedValue_ptr g,
                                    BoundedValue_ptr b)
{
    Graphic_var adjuster =
      create_and_set_body<Graphic>(new LightingAdjuster(r, g, b), gg,
                                   "GadgetKit/lighting");
    r->attach(Observer_ptr(Graphic_ptr(adjuster)));
    g->attach(Observer_ptr(Graphic_ptr(adjuster)));
    b->attach(Observer_ptr(Graphic_ptr(adjuster)));

    return adjuster;
}

Graphic_ptr GadgetKitImpl::rotator(Graphic_ptr g,
                                   BoundedValue_ptr value,
                                   Axis axis)
{
    Graphic_var transformer = my_figure->transformer(g);
    Graphic_var adjuster =
	create_and_set_body<Graphic>(new RotationAdjuster(axis),
				     transformer, "GadgetKit/rotator");
    value->attach(Observer_ptr(Graphic_ptr(adjuster)));
    return adjuster;
}

Graphic_ptr GadgetKitImpl::zoomer(Graphic_ptr g, BoundedValue_ptr value)
{
    Graphic_var transformer = my_figure->transformer(g);
    Graphic_var adjuster =
	create_and_set_body<Graphic>(new ZoomAdjuster(), transformer,
				     "GadgetKit/zoomer");
    value->attach(Observer_ptr(Graphic_ptr(adjuster)));
    return adjuster;
}

extern "C" Berlin::KitImpl *load()
{
    static std::string properties[] = {"implementation", "GadgetKitImpl"};
    return Berlin::create_prototype<GadgetKitImpl>("IDL:fresco.org/Fresco/GadgetKit:1.0", properties, 2);
}
