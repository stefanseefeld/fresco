/*$Id$
 *
 * This source file is a part of the Berlin Project.
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
#ifndef _UnidrawKitImpl_hh
#define _UnidrawKitImpl_hh

#include <Warsaw/config.hh>
#include <Warsaw/FigureKit.hh>
#include <Warsaw/UnidrawKit.hh>
#include <Berlin/KitImpl.hh>
#include <Berlin/RefCountVar.hh>
#include <vector>

class UnidrawKitImpl : public virtual POA_Unidraw::UnidrawKit,
		       public KitImpl
{
public:
  UnidrawKitImpl(KitFactory *, const Warsaw::Kit::PropertySeq &);
  virtual ~UnidrawKitImpl();
  virtual void bind(Warsaw::ServerContext_ptr);
  virtual Warsaw::Controller_ptr editor(Warsaw::Coord, Warsaw::Coord);
private:
  RefCount_var<Warsaw::FigureKit> _figure;
};

#endif
