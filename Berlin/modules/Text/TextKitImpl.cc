/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Graydon Hoare <graydon@pobox.com> 
 * Copyright (C) 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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

#include <Prague/Sys/Tracer.hh>
#include <Warsaw/config.hh>
#include <Warsaw/resolve.hh>
#include <Warsaw/Server.hh>
#include <Warsaw/DrawingKit.hh>        // for the DK to work on
#include <Warsaw/LayoutKit.hh>        // for the LK to work on
#include <Warsaw/Unicode.hh>           // for toCORBA and friends
#include <Warsaw/TextBuffer.hh>        // for TextBuffer type
#include <Warsaw/StreamBuffer.hh>
#include <Warsaw/IO.hh>
#include <Berlin/GraphicImpl.hh>       // GraphicImpl::initRequisition
#include "Text/TextKitImpl.hh"         // for our own definition
#include "Text/TextChunk.hh"           // the chunk graphic type
#include "Text/TextViewer.hh"          // the viewer polygraphic type
#include "Text/TerminalView.hh"
#include "Text/Compositor.hh"          // the compositor strategy
#include "Text/Strut.hh"               // the compositor strategy
// #include <Drawing/DrawDecorator.hh>    // the decorator monographic template
#include <Prague/Sys/Tracer.hh>

using namespace Prague;
using namespace Warsaw;

Mutex TextKitImpl::staticMutex;
map<Unichar,Impl_var<TextChunk> > TextKitImpl::charCache;
DrawingKit_var TextKitImpl::canonicalDK;

TextKitImpl::TextKitImpl(KitFactory *f, const Warsaw::Kit::PropertySeq &p)
  : KitImpl(f, p),  _strut(0),
    lineCompositor(new LRCompositor()), 
    pageCompositor(new TBCompositor())
{
  Trace trace("TextKitImpl::TextKitImpl");
}

TextKitImpl::~TextKitImpl()
{
  Trace trace("TextKitImpl::~TextKitImpl");
  delete lineCompositor;
  delete pageCompositor;
}

void TextKitImpl::bind(ServerContext_ptr sc)
{
  KitImpl::bind(sc);
  Warsaw::Kit::PropertySeq props;
  props.length(0);
  canonicalDK = DrawingKit::_narrow(sc->getSingleton("IDL:Warsaw/DrawingKit:1.0"));
  layout = resolve_kit<LayoutKit>(sc, "IDL:Warsaw/LayoutKit:1.0", props);
}

// chunks are flyweights
//
// while we have the _capability_ to delegate text chunks to the drawingKit as
// multi-character "might-be-a-glyph" candidates, at the moment we have _no
// idea_ how to compute sane allocations and alignments for such beasts using
// conventional font metrics, as might appear in say a truetype or T1 font file,
// and the attempts we've made at fudging these numbers completley messes up the
// layout caluclations. so instead, the "chunk" facility here will just give you
// back an appropriate alignment box packed with single-character chunks if you
// give it a multi-char chunk; if you give it a single-char chunk you will get
// back just a single chunk graphic. it's transparent enough for now, and if some other
// text genius wants to fix it they can go ahead.

Graphic_ptr TextKitImpl::chunk(const Unistring & u)
{
  MutexGuard guard(staticMutex);
  unsigned long len = u.length();
  if (len == 1) return glyph(u[0]);
  else 
    {
      Graphic_var hbox = layout->hbox();
      hbox->append(Graphic_var(strut()));
      for (unsigned int i = 0; i < len; ++i)
	hbox->append(glyph(u[i]));
      return hbox._retn();
    }
}

Graphic_ptr TextKitImpl::glyph(Unichar ch)
{
  if (charCache.find(ch) == charCache.end())
    {
      Graphic::Requisition r;
      GraphicImpl::initRequisition(r);
      canonicalDK->allocateChar(ch,r);
      Impl_var<TextChunk> t(new TextChunk(ch, r));
      charCache[ch] = t;
    }
  return charCache[ch]->_this();
}

Graphic_ptr TextKitImpl::strut()
{
  MutexGuard guard(localMutex);
  if (! _strut)
    {
      DrawingKit::FontMetrics metrics = canonicalDK->fmetrics();
      Graphic::Requisition r;
      GraphicImpl::initRequisition(r);
      r.y.natural = r.y.minimum = r.y.maximum = static_cast<Coord>(metrics.height >> 6) / canonicalDK->resolution(yaxis);
      r.y.defined = true;
      r.y.align = metrics.height == 0 ? 0.: static_cast<double>(metrics.ascender) / metrics.height; 
      _strut = new Strut(r);
    }
  return _strut->_this();
}

Graphic_ptr TextKitImpl::simpleViewer(TextBuffer_ptr buf)
{
  Trace trace("TextKitImpl::simpleViewer");
  TextViewer *tv = new TextViewer(buf, TextKit_var(_this()), canonicalDK, lineCompositor);
  activate(tv);
  buf->attach(Observer_var(tv->_this()));
  return tv->_this();
}

Graphic_ptr TextKitImpl::terminal(StreamBuffer_ptr buf)
{
  Trace trace("TextKitImpl::terminal");
  TerminalView *tv = new TerminalView(buf, TextKit_var(_this()), canonicalDK, lineCompositor, pageCompositor);
  activate(tv);
  buf->attach(Observer_var(tv->_this()));
  return tv->_this();
}

///////////////////////
// decorator factories
///////////////////////
  
Graphic_ptr TextKitImpl::size(Graphic_ptr g, CORBA::ULong ems) 
{
//   MutexGuard guard(localMutex);
//   Impl_var<DrawDecorator<CORBA::ULong> > decor(new DrawDecorator<CORBA::ULong>(&DrawingKit::fontSize, ems));
//   decor->body(g);
//   allocations.push_back(decor.get());
//   return decor.release()->_this();
  return Graphic::_nil();
}

Graphic_ptr TextKitImpl::weight(Graphic_ptr g, CORBA::ULong wt) 
{
//   MutexGuard guard(localMutex);
//   Impl_var<DrawDecorator<CORBA::ULong> > decor(new DrawDecorator<CORBA::ULong>(&DrawingKit::fontWeight, wt));
//   decor->body(g);
//   allocations.push_back(decor.get());
//   return decor.release()->_this();
  return Graphic::_nil();
}

Graphic_ptr TextKitImpl::family(Graphic_ptr g, const Unistring &fam)
{
//   MutexGuard guard(localMutex);
//   Impl_var<DrawDecorator<const Unistring &> > decor(new DrawDecorator<const Unistring &>(&DrawingKit::fontFamily, fam));
//   decor->body(g);
//   allocations.push_back(decor.get());
//   return decor.release()->_this();
  return Graphic::_nil();
}

Graphic_ptr TextKitImpl::subFamily(Graphic_ptr g, const Unistring &fam)
{
//   MutexGuard guard(localMutex);
//   Impl_var<DrawDecorator<const Unistring &> > decor(new DrawDecorator<const Unistring &>(&DrawingKit::fontSubFamily, fam));
//   decor->body(g);
//   allocations.push_back(decor.get());
//   return decor.release()->_this();
  return Graphic::_nil();
}

Graphic_ptr TextKitImpl::fullName(Graphic_ptr g, const Unistring &name)
{
//   MutexGuard guard(localMutex);
//   Impl_var<DrawDecorator<const Unistring &> > decor(new DrawDecorator<const Unistring &>(&DrawingKit::fontFullName, name));
//   decor->body(g);
//   allocations.push_back(decor.get());
//   return decor.release()->_this();
  return Graphic::_nil();
}

Graphic_ptr TextKitImpl::style(Graphic_ptr g, const Unistring &sty)
{
//   MutexGuard guard(localMutex);
//   Impl_var<DrawDecorator<const Unistring &> > decor(new DrawDecorator<const Unistring &>(&DrawingKit::fontStyle, sty));
//   decor->body(g);
//   allocations.push_back(decor.get());
//   return decor.release()->_this();
  return Graphic::_nil();
}

Graphic_ptr TextKitImpl::fontAttr(Graphic_ptr g, const NVPair &nvp)
{
//   MutexGuard guard(localMutex);
//   Impl_var<DrawDecorator<const NVPair &> > decor(new DrawDecorator<const NVPair &>(&DrawingKit::fontAttr, nvp));
//   decor->body(g);
//   allocations.push_back(decor.get());
//   return decor.release()->_this();
  return Graphic::_nil();
}

extern "C" KitFactory *load()
{
  static string properties[] = {"implementation", "TextKitImpl", "locale", "latin"};
  return new KitFactoryImpl<TextKitImpl>("IDL:Warsaw/TextKit:1.0", properties, 2);
} 
