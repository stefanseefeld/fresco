//
// $Id$
//
// This source file is a part of the Berlin Project.
// Copyright (C) 1998 Graydon Hoare <graydon@pobox.com> 
// http://www.berlin-consortium.org
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public License
// as published by the Free Software Foundation; either version 2 of
// the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
//

#include <Warsaw/Server.hh>
#include <Warsaw/DrawingKit.hh>        // for the DK to work on
#include <Warsaw/Unicode.hh>           // for toCORBA and friends
#include <Warsaw/TextBuffer.hh>           // for TextBuffer type
#include <Text/TextKitImpl.hh>         // for our own definition
#include <Text/TextChunk.hh>           // the chunk graphic type
#include <Text/TextViewer.hh>           // the viewer polygraphic type
#include <Text/Compositor.hh>           // the compositor strategy
#include <Drawing/DrawDecorator.hh> // the decorator monographic template

Mutex TextKitImpl::staticMutex;
map<Unicode::String,Impl_var<TextChunk> > TextKitImpl::chunkCache;
DrawingKit_var TextKitImpl::canonicalDK;

TextKitImpl::TextKitImpl(KitFactory *f, const PropertySeq &p) : KitImpl(f, p), myCompositor(new IdentityCompositor(xaxis)) {}
TextKitImpl::~TextKitImpl() { delete myCompositor;}

void TextKitImpl::bind(ServerContext_ptr sc)
{
  canonicalDK = DrawingKit::_narrow(sc->getSingleton(interface(DrawingKit)));
}

Graphic_ptr TextKitImpl::simpleViewer(TextBuffer_ptr buf)
{
  Impl_var<TextViewer> tv(new TextViewer(buf,this->_this(),canonicalDK,myCompositor));
  myAllocations.push_back(tv.get());
  buf->attach(tv.get());
  return tv.release()->_this();
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

///////////////////////
// decorator factories
///////////////////////
  
Graphic_ptr TextKitImpl::size(Graphic_ptr body, CORBA::ULong ems) 
{
  MutexGuard guard(localMutex);
  Impl_var<DrawDecorator<CORBA::ULong> > 
    decor(new DrawDecorator<CORBA::ULong>(ems,&DrawingKit::fontSize,body));
  myAllocations.push_back(decor.get());
  return decor.release()->_this();
}

Graphic_ptr TextKitImpl::weight(Graphic_ptr body, CORBA::ULong wt) 
{
  MutexGuard guard(localMutex);
  Impl_var<DrawDecorator<CORBA::ULong> > 
    decor(new DrawDecorator<CORBA::ULong>(wt,&DrawingKit::fontWeight,body));
  myAllocations.push_back(decor.get());
  return decor.release()->_this();
}

Graphic_ptr TextKitImpl::family(Graphic_ptr body, const Unistring & fam)
{
  MutexGuard guard(localMutex);
  Impl_var<DrawDecorator<const Unistring &> > 
    decor(new DrawDecorator<const Unistring &>(fam,&DrawingKit::fontFamily,body));
  myAllocations.push_back(decor.get());
  return decor.release()->_this();
}

Graphic_ptr TextKitImpl::subFamily(Graphic_ptr body, const Unistring & fam)
{
  MutexGuard guard(localMutex);
  Impl_var<DrawDecorator<const Unistring &> > 
    decor(new DrawDecorator<const Unistring &>(fam,&DrawingKit::fontSubFamily,body));
  myAllocations.push_back(decor.get());
  return decor.release()->_this();
}

Graphic_ptr TextKitImpl::fullName(Graphic_ptr body, const Unistring & name)
{
  MutexGuard guard(localMutex);
  Impl_var<DrawDecorator<const Unistring &> > 
    decor(new DrawDecorator<const Unistring &>(name,&DrawingKit::fontFullName,body));
  myAllocations.push_back(decor.get());
  return decor.release()->_this();
}

Graphic_ptr TextKitImpl::style(Graphic_ptr body, const Unistring & sty)
{
  MutexGuard guard(localMutex);
  Impl_var<DrawDecorator<const Unistring &> > 
    decor(new DrawDecorator<const Unistring &>(sty,&DrawingKit::fontStyle,body));
  myAllocations.push_back(decor.get());
  return decor.release()->_this();
}

Graphic_ptr TextKitImpl::fontAttr(Graphic_ptr body, const NVPair & nvp) {
  MutexGuard guard(localMutex);
  Impl_var<DrawDecorator<const NVPair &> > 
    decor(new DrawDecorator<const NVPair &>(nvp,&DrawingKit::fontAttr,body));
  myAllocations.push_back(decor.get());
  return decor.release()->_this();
}

extern "C" KitFactory *load()
{
  static string properties[] = {"implementation", "TextKitImpl", "locale", "latin",};
  return new KitFactoryImpl<TextKitImpl>(interface(TextKit), properties, 2);
} 
