/*$Id$
 *
 * This source file is a part of the Berlin Project.
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

#include <Warsaw/Server.hh>
#include <Warsaw/DrawingKit.hh>        // for the DK to work on
#include <Warsaw/Unicode.hh>           // for toCORBA and friends
#include <Warsaw/TextBuffer.hh>        // for TextBuffer type
#include <Text/TextKitImpl.hh>         // for our own definition
#include <Text/TextChunk.hh>           // the chunk graphic type
#include <Text/TextViewer.hh>          // the viewer polygraphic type
#include <Text/Compositor.hh>          // the compositor strategy
#include <Text/Strut.hh>               // the compositor strategy
#include <Drawing/DrawDecorator.hh>    // the decorator monographic template
#include <Prague/Sys/Tracer.hh>

using namespace Prague;

Mutex TextKitImpl::staticMutex;
map<Unicode::String,Impl_var<TextChunk> > TextKitImpl::chunkCache;
DrawingKit_var TextKitImpl::canonicalDK;

TextKitImpl::TextKitImpl(KitFactory *f, const PropertySeq &p) : KitImpl(f, p), compositor(new LRCompositor()) {}
TextKitImpl::~TextKitImpl() { delete compositor;}

void TextKitImpl::bind(ServerContext_ptr sc)
{
  canonicalDK = DrawingKit::_narrow(sc->getSingleton(interface(DrawingKit)));
}

// chunks are flyweights

Graphic_ptr TextKitImpl::chunk(const Unistring & u)
{
  MutexGuard guard(staticMutex);
  Unicode::String str = Unicode::toPrague(u);
  if (chunkCache.find(str) == chunkCache.end())
    {
      Graphic::Requisition r;
      canonicalDK->allocateText(u,r);
      Impl_var<TextChunk> t(new TextChunk(str, r));
      chunkCache[str] = t;
    }
  return chunkCache[str]->_this();
}

Graphic_ptr TextKitImpl::strut()
{
  MutexGuard guard(staticMutex);
  Unistring us = Unicode::toCORBA(Unicode::String("M"));
  Graphic::Requisition r;
  canonicalDK->allocateText(us, r);
  Strut *strut = new Strut (r);
  strut->_obj_is_ready(_boa());
  return strut->_this();
}

Graphic_ptr TextKitImpl::simpleViewer(TextBuffer_ptr buf)
{
  Trace trace("TextKitImpl::simpleViewer");
  Impl_var<TextViewer> tv(new TextViewer(buf,this->_this(),canonicalDK, compositor));
  allocations.push_back(tv.get());
  buf->attach(tv.get());
  return tv.release()->_this();
}

///////////////////////
// decorator factories
///////////////////////
  
Graphic_ptr TextKitImpl::size(Graphic_ptr g, CORBA::ULong ems) 
{
  MutexGuard guard(localMutex);
  Impl_var<DrawDecorator<CORBA::ULong> > decor(new DrawDecorator<CORBA::ULong>(&DrawingKit::fontSize, ems));
  decor->body(g);
  allocations.push_back(decor.get());
  return decor.release()->_this();
}

Graphic_ptr TextKitImpl::weight(Graphic_ptr g, CORBA::ULong wt) 
{
  MutexGuard guard(localMutex);
  Impl_var<DrawDecorator<CORBA::ULong> > decor(new DrawDecorator<CORBA::ULong>(&DrawingKit::fontWeight, wt));
  decor->body(g);
  allocations.push_back(decor.get());
  return decor.release()->_this();
}

Graphic_ptr TextKitImpl::family(Graphic_ptr g, const Unistring &fam)
{
  MutexGuard guard(localMutex);
  Impl_var<DrawDecorator<const Unistring &> > decor(new DrawDecorator<const Unistring &>(&DrawingKit::fontFamily, fam));
  decor->body(g);
  allocations.push_back(decor.get());
  return decor.release()->_this();
}

Graphic_ptr TextKitImpl::subFamily(Graphic_ptr g, const Unistring &fam)
{
  MutexGuard guard(localMutex);
  Impl_var<DrawDecorator<const Unistring &> > decor(new DrawDecorator<const Unistring &>(&DrawingKit::fontSubFamily, fam));
  decor->body(g);
  allocations.push_back(decor.get());
  return decor.release()->_this();
}

Graphic_ptr TextKitImpl::fullName(Graphic_ptr g, const Unistring &name)
{
  MutexGuard guard(localMutex);
  Impl_var<DrawDecorator<const Unistring &> > decor(new DrawDecorator<const Unistring &>(&DrawingKit::fontFullName, name));
  decor->body(g);
  allocations.push_back(decor.get());
  return decor.release()->_this();
}

Graphic_ptr TextKitImpl::style(Graphic_ptr g, const Unistring &sty)
{
  MutexGuard guard(localMutex);
  Impl_var<DrawDecorator<const Unistring &> > decor(new DrawDecorator<const Unistring &>(&DrawingKit::fontStyle, sty));
  decor->body(g);
  allocations.push_back(decor.get());
  return decor.release()->_this();
}

Graphic_ptr TextKitImpl::fontAttr(Graphic_ptr g, const NVPair &nvp)
{
  MutexGuard guard(localMutex);
  Impl_var<DrawDecorator<const NVPair &> > decor(new DrawDecorator<const NVPair &>(&DrawingKit::fontAttr, nvp));
  decor->body(g);
  allocations.push_back(decor.get());
  return decor.release()->_this();
}

extern "C" KitFactory *load()
{
  static string properties[] = {"implementation", "TextKitImpl", "locale", "latin"};
  return new KitFactoryImpl<TextKitImpl>(interface(TextKit), properties, 2);
} 
