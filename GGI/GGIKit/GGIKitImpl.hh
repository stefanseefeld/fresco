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
#ifndef _GGIKit_GGIKitImpl_hh
#define _GGIKIT_GGIKitImpl_hh

#include "config.hh"
#include <Fresco/GGIKit.hh>
#include <Berlin/KitImpl.hh>
#include <vector>

namespace GGIKit
{

  class GGIKitImpl : public virtual POA_GGI::GGIKit,
                     public Berlin::KitImpl
  {
    public:
      GGIKitImpl(const std::string &,
                 const Fresco::Kit::PropertySeq &,
                 Berlin::ServerContextImpl *);
      virtual ~GGIKitImpl();
      virtual Berlin::KitImpl *clone(const Fresco::Kit::PropertySeq &p,
                     Berlin::ServerContextImpl *c)
      { return new GGIKitImpl(repo_id(), p, c); }
      virtual GGI::Visual_ptr
      create_visual(Fresco::PixelCoord, Fresco::PixelCoord);
  };

} // namespace

#endif
