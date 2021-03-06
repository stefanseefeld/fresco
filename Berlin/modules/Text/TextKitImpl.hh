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
#ifndef _TextKit_TextKitImpl_hh
#define _TextKit_TextKitImpl_hh

#include <Prague/Sys/Thread.hh>        // for Mutex
#include <Babylon/String.hh>           // for Babylon::String
#include <Fresco/config.hh>
#include <Fresco/TextKit.hh>           // for our IDL definition
#include <Berlin/MonoGraphic.hh>       // for our decorators
#include <Berlin/KitImpl.hh>           // for our parent impl
#include <Berlin/ImplVar.hh>           // for the impls
#include <Berlin/RefCountVar.hh>       // for the RefCount_var
#include "TextChunk.hh"                // for our chunks
#include <map>                         // for the cache

namespace Berlin 
{
  namespace TextKit 
  {

    class Compositor;
    class Strut;
    
    class TextKitImpl : public virtual POA_Fresco::TextKit,
            public KitImpl
    {
    typedef std::map<Fresco::Unichar, Fresco::Graphic_var> cache_t;
      public:
    TextKitImpl(const std::string &,
            const Fresco::Kit::PropertySeq &,
            ServerContextImpl *);
    virtual ~TextKitImpl();
    virtual Berlin::KitImpl *clone(const Fresco::Kit::PropertySeq &p,
                       ServerContextImpl *c)
    { return new TextKitImpl(repo_id(), p, c);}
    virtual void bind(Fresco::ServerContext_ptr);

    Fresco::Graphic_ptr chunk(const Fresco::Unistring &u);
    Fresco::Graphic_ptr glyph(Fresco::Unichar c);
    Fresco::Graphic_ptr strut();
    Fresco::Graphic_ptr simple_viewer(Fresco::TextBuffer_ptr);  
    Fresco::Graphic_ptr terminal(Fresco::StreamBuffer_ptr);
    Fresco::Graphic_ptr size(Fresco::Graphic_ptr, CORBA::ULong);
    Fresco::Graphic_ptr weight(Fresco::Graphic_ptr, CORBA::ULong);
    Fresco::Graphic_ptr family(Fresco::Graphic_ptr,
                   const Fresco::Unistring &);
    Fresco::Graphic_ptr subfamily(Fresco::Graphic_ptr,
                      const Fresco::Unistring &);
    Fresco::Graphic_ptr fullname(Fresco::Graphic_ptr,
                     const Fresco::Unistring &);
    Fresco::Graphic_ptr style(Fresco::Graphic_ptr,
                  const Fresco::Unistring &);
    Fresco::Graphic_ptr font_attribute(Fresco::Graphic_ptr,
                       const Fresco::NVPair &);
      private:
    cache_t                my_cache;
    Fresco::DrawingKit_var my_canonicalDK;
    
    RefCount_var<Fresco::LayoutKit> my_layout;
    Impl_var<Strut>       my_strut;
    Prague::Mutex         my_mutex;
    Compositor           *my_lineCompositor;
    Compositor           *my_pageCompositor;
    };
    
  } // namespace
} // namespace

#endif
