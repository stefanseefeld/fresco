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
#ifndef _TextKitImpl_hh
#define _TextKitImpl_hh

#include <Warsaw/config.hh>
#include <Warsaw/TextKit.hh>           // for our IDL definition
#include <Text/TextChunk.hh>           // for our chunks
#include <Berlin/MonoGraphic.hh>       // for our decorators
#include <Prague/Unicode/Unistring.hh> // for Unicode::String
#include <Berlin/CloneableImpl.hh>     // for our parent impl
#include <Berlin/Thread.hh>            // for the mutex
#include <Berlin/ImplVar.hh>           // for the impls
#include <map>                         // for the cache
#include <vector>                      // for the gc

declare_corba_ptr_type(DrawingKit)

class TextKitImpl : lcimplements(TextKit), 
		    public virtual CloneableImpl 
{

  static Mutex staticMutex;
  static map< Unicode::String, Impl_var<TextChunk> > chunkCache;
  static DrawingKit_var canonicalDK;

  Mutex localMutex;
  vector<MonoGraphic *> myDecorators;
  
 public:

    TextKitImpl();
    virtual ~TextKitImpl();
    virtual void bind(ServerContext_ptr);

    Graphic_ptr chunk(const Unistring & u);
    Graphic_ptr size(Graphic_ptr body, CORBA::ULong ems);
    Graphic_ptr weight(Graphic_ptr body, CORBA::ULong wt);
    Graphic_ptr family(Graphic_ptr body, const Unistring & fam);
    Graphic_ptr subFamily(Graphic_ptr body, const Unistring & fam);
    Graphic_ptr fullName(Graphic_ptr body, const Unistring & name);
    Graphic_ptr style(Graphic_ptr body, const Unistring & sty);
    Graphic_ptr fontAttr(Graphic_ptr body, const NVPair & nvp);
};



#endif
