/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Graydon Hoare <graydon@fresco.org> 
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

#include <Prague/Sys/Tracer.hh>
#include <Fresco/config.hh>
#include <Fresco/resolve.hh>
#include <Fresco/Server.hh>
#include <Fresco/DrawingKit.hh>        // for the DK to work on
#include <Fresco/LayoutKit.hh>        // for the LK to work on
#include <Fresco/Unicode.hh>           // for toCORBA and friends
#include <Fresco/TextBuffer.hh>        // for TextBuffer type
#include <Fresco/StreamBuffer.hh>
#include <Fresco/IO.hh>
#include <Berlin/GraphicImpl.hh>       // GraphicImpl::initRequisition
#include "TextKitImpl.hh"         // for our own definition
#include "TextChunk.hh"           // the chunk graphic type
#include "TextViewer.hh"          // the viewer polygraphic type
#include "TerminalView.hh"
#include "Compositor.hh"          // the compositor strategy
#include "Strut.hh"               // the compositor strategy
// #include <Drawing/DrawDecorator.hh>    // the decorator monographic template

using namespace Prague;
using namespace Fresco;
using namespace Berlin::TextKit;

TextKitImpl::TextKitImpl(const std::string &id,
             const Fresco::Kit::PropertySeq &p,
             ServerContextImpl *c) :
    KitImpl(id, p, c),
    my_strut(0),
    my_lineCompositor(new LRCompositor()), 
    my_pageCompositor(new TBCompositor())
{ }

TextKitImpl::~TextKitImpl()
{
    delete my_lineCompositor;
    delete my_pageCompositor;
}

void TextKitImpl::bind(ServerContext_ptr sc)
{
    KitImpl::bind(sc);
    Fresco::Kit::PropertySeq props;
    props.length(0);
    my_canonicalDK =
    DrawingKit::_narrow(sc->get_singleton("IDL:fresco.org/Fresco/DrawingKit:1.0"));
    my_layout = resolve_kit<LayoutKit>(sc,
                       "IDL:fresco.org/Fresco/LayoutKit:1.0",
                       props);
}

// chunks are flyweights
//
// while we have the _capability_ to delegate text chunks to the
// drawingKit as multi-character "might-be-a-glyph" candidates, at the
// moment we have _no idea_ how to compute sane allocations and alignments
// for such beasts using conventional font metrics, as might appear in say
// a truetype or T1 font file, and the attempts we've made at fudging these
// numbers completley messes up the layout caluclations. so instead, the
// "chunk" facility here will just give you back an appropriate alignment
// box packed with single-character chunks if you give it a multi-char
// chunk; if you give it a single-char chunk you will get back just a
// single chunk graphic. it's transparent enough for now, and if some other
// text genius wants to fix it they can go ahead.

Graphic_ptr TextKitImpl::chunk(const Unistring & u)
{
    unsigned long len = u.length();
    if (len == 1) return glyph(u[0]);
    else 
    {
    Graphic_var hbox = my_layout->hbox();
    hbox->append_graphic(Graphic_var(strut()));
    Babylon::String tmp(Unicode::to_internal(u));
    for(Babylon::String::iterator i = tmp.begin();
        i != tmp.end();
        ++i)
        hbox->append_graphic(Graphic_var(glyph(Unicode::to_CORBA(*i))));
    return hbox._retn();
    }
}

Graphic_ptr TextKitImpl::glyph(Unichar ch)
{
    Prague::Guard<Mutex> guard(my_mutex);
    if (my_cache.find(ch) == my_cache.end())
    {
    Graphic::Requisition r;
    GraphicImpl::init_requisition(r);
    my_canonicalDK->allocate_char(ch, r);
    TextChunk *chunk = new TextChunk(ch, r);
    activate(chunk);
    my_cache[ch] = chunk->_this();
    }
    return Graphic::_duplicate(my_cache[ch]);
}

Graphic_ptr TextKitImpl::strut()
{
    Prague::Guard<Mutex> guard(my_mutex);
    if (!my_strut)
    {
    DrawingKit::FontMetrics metrics = my_canonicalDK->font_metrics();
    Graphic::Requisition r;
    GraphicImpl::init_requisition(r);
    r.y.natural = r.y.minimum = r.y.maximum =
        static_cast<Coord>(metrics.height >> 6) /
        my_canonicalDK->resolution(yaxis);
    r.y.defined = true;
    r.y.align = metrics.height == 0 ? 0.0 :
        static_cast<double>(metrics.ascender) / metrics.height; 
    my_strut = new Strut(r); // activated via Impl_var
    }
    return my_strut->_this();
}

Graphic_ptr TextKitImpl::simple_viewer(TextBuffer_ptr buf)
{
    Graphic_var tv = create<Graphic>(new TextViewer(buf,
                            TextKit_var(_this()),
                            my_canonicalDK,
                            my_lineCompositor));
    buf->attach(Observer_ptr(Graphic_ptr(tv)));
    return tv;
}

Graphic_ptr TextKitImpl::terminal(StreamBuffer_ptr buf)
{
    Graphic_var tv = create<Graphic>(new TerminalView(buf,
                              TextKit_var(_this()),
                              my_canonicalDK,
                              my_lineCompositor,
                              my_pageCompositor));
    buf->attach(Observer_ptr(Graphic_ptr(tv)));
    return tv;
}

///////////////////////
// decorator factories
///////////////////////
  
Graphic_ptr TextKitImpl::size(Graphic_ptr g, CORBA::ULong ems) 
{
//   Prague::Guard<Mutex> guard(localMutex);
//   Impl_var<DrawDecorator<CORBA::ULong> > decor(new DrawDecorator<CORBA::ULong>(&DrawingKit::fontSize, ems));
//   decor->body(g);
//   allocations.push_back(decor.get());
//   return decor.release()->_this();
    return Graphic::_nil();
}

Graphic_ptr TextKitImpl::weight(Graphic_ptr g, CORBA::ULong wt) 
{
//   Prague::Guard<Mutex> guard(localMutex);
//   Impl_var<DrawDecorator<CORBA::ULong> > decor(new DrawDecorator<CORBA::ULong>(&DrawingKit::fontWeight, wt));
//   decor->body(g);
//   allocations.push_back(decor.get());
//   return decor.release()->_this();
    return Graphic::_nil();
}

Graphic_ptr TextKitImpl::family(Graphic_ptr g, const Unistring &fam)
{
//   Prague::Guard<Mutex> guard(localMutex);
//   Impl_var<DrawDecorator<const Unistring &> > decor(new DrawDecorator<const Unistring &>(&DrawingKit::fontFamily, fam));
//   decor->body(g);
//   allocations.push_back(decor.get());
//   return decor.release()->_this();
    return Graphic::_nil();
}

Graphic_ptr TextKitImpl::subfamily(Graphic_ptr g, const Unistring &fam)
{
//   Prague::Guard<Mutex> guard(localMutex);
//   Impl_var<DrawDecorator<const Unistring &> > decor(new DrawDecorator<const Unistring &>(&DrawingKit::fontSubFamily, fam));
//   decor->body(g);
//   allocations.push_back(decor.get());
//   return decor.release()->_this();
    return Graphic::_nil();
}

Graphic_ptr TextKitImpl::fullname(Graphic_ptr g, const Unistring &name)
{
//   Prague::Guard<Mutex> guard(localMutex);
//   Impl_var<DrawDecorator<const Unistring &> > decor(new DrawDecorator<const Unistring &>(&DrawingKit::fontFullName, name));
//   decor->body(g);
//   allocations.push_back(decor.get());
//   return decor.release()->_this();
    return Graphic::_nil();
}

Graphic_ptr TextKitImpl::style(Graphic_ptr g, const Unistring &sty)
{
//   Prague::Guard<Mutex> guard(localMutex);
//   Impl_var<DrawDecorator<const Unistring &> > decor(new DrawDecorator<const Unistring &>(&DrawingKit::fontStyle, sty));
//   decor->body(g);
//   allocations.push_back(decor.get());
//   return decor.release()->_this();
    return Graphic::_nil();
}

Graphic_ptr TextKitImpl::font_attribute(Graphic_ptr g, const NVPair &nvp)
{
//   Prague::Guard<Mutex> guard(localMutex);
//   Impl_var<DrawDecorator<const NVPair &> > decor(new DrawDecorator<const NVPair &>(&DrawingKit::fontAttr, nvp));
//   decor->body(g);
//   allocations.push_back(decor.get());
//   return decor.release()->_this();
    return Graphic::_nil();
}

extern "C" Berlin::KitImpl *load()
{
    static std::string properties[] = {"implementation", "TextKitImpl", "locale", "latin"};
    return Berlin::create_prototype<TextKitImpl>("IDL:fresco.org/Fresco/TextKit:1.0", properties, 4);
} 
