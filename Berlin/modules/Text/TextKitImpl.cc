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

#include <Warsaw/DrawingKit.hh>        // for the DK to work on
#include <Warsaw/Unicode.hh>           // for toCORBA and friends
#include <Text/TextKitImpl.hh>         // for our own definition
#include <Text/TextChunk.hh>           // the chunk subtype
#include <Drawing/DrawDecorator.hh>
#include <Berlin/Plugin.hh>

Mutex TextKitImpl::staticMutex;
map<Unicode::String,Impl_var<TextChunk> > TextKitImpl::chunkCache;
DrawingKit_var TextKitImpl::canonicalDK;

TextKitImpl::TextKitImpl() {}
TextKitImpl::~TextKitImpl() {}

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

///////////////////////
// decorator factories
///////////////////////
  
Graphic_ptr TextKitImpl::size(Graphic_ptr body, CORBA::ULong ems) 
{
  MutexGuard guard(localMutex);
  Impl_var<DrawDecorator<CORBA::ULong> > 
    decor(new DrawDecorator<CORBA::ULong>(ems,&DrawingKit::fontSize,body));
  myDecorators.push_back(decor.get());
  return decor.release()->_this();
}

Graphic_ptr TextKitImpl::weight(Graphic_ptr body, CORBA::ULong wt) 
{
  MutexGuard guard(localMutex);
  Impl_var<DrawDecorator<CORBA::ULong> > 
    decor(new DrawDecorator<CORBA::ULong>(wt,&DrawingKit::fontWeight,body));
  myDecorators.push_back(decor.get());
  return decor.release()->_this();
}

Graphic_ptr TextKitImpl::family(Graphic_ptr body, const Unistring & fam)
{
  MutexGuard guard(localMutex);
  Impl_var<DrawDecorator<const Unistring &> > 
    decor(new DrawDecorator<const Unistring &>(fam,&DrawingKit::fontFamily,body));
  myDecorators.push_back(decor.get());
  return decor.release()->_this();
}

Graphic_ptr TextKitImpl::subFamily(Graphic_ptr body, const Unistring & fam)
{
  MutexGuard guard(localMutex);
  Impl_var<DrawDecorator<const Unistring &> > 
    decor(new DrawDecorator<const Unistring &>(fam,&DrawingKit::fontSubFamily,body));
  myDecorators.push_back(decor.get());
  return decor.release()->_this();
}

Graphic_ptr TextKitImpl::fullName(Graphic_ptr body, const Unistring & name)
{
  MutexGuard guard(localMutex);
  Impl_var<DrawDecorator<const Unistring &> > 
    decor(new DrawDecorator<const Unistring &>(name,&DrawingKit::fontFullName,body));
  myDecorators.push_back(decor.get());
  return decor.release()->_this();
}

Graphic_ptr TextKitImpl::style(Graphic_ptr body, const Unistring & sty)
{
  MutexGuard guard(localMutex);
  Impl_var<DrawDecorator<const Unistring &> > 
    decor(new DrawDecorator<const Unistring &>(sty,&DrawingKit::fontStyle,body));
  myDecorators.push_back(decor.get());
  return decor.release()->_this();
}

Graphic_ptr TextKitImpl::fontAttr(Graphic_ptr body, const NVPair & nvp) {
  MutexGuard guard(localMutex);
  Impl_var<DrawDecorator<const NVPair &> > 
    decor(new DrawDecorator<const NVPair &>(nvp,&DrawingKit::fontAttr,body));
  myDecorators.push_back(decor.get());
  return decor.release()->_this();
}



EXPORT_PLUGIN(TextKitImpl, interface(TextKit))
