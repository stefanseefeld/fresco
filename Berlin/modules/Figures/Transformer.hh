/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@fresco.org> 
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

#ifndef _Transformer_hh
#define _Transformer_hh

#include <Fresco/config.hh>
#include <Berlin/TransformImpl.hh>
#include <Berlin/Allocator.hh>
#include <Berlin/ImplVar.hh>

namespace Berlin
{
  namespace FigureKit
  {

    class Transformer : public Allocator
    {
    public:
	Transformer();
	virtual ~Transformer();
	virtual void request(Fresco::Graphic::Requisition &);
	virtual void traverse(Fresco::Traversal_ptr);
	virtual Fresco::Transform_ptr transformation();
	void allocate(Fresco::Tag, const Fresco::Allocation::Info &);
    private:
	Impl_var<TransformImpl> transform;
    };

    class BodyTransformer : public Transformer
    {
    public:
	BodyTransformer(Transformer*, unsigned d = 0);
	BodyTransformer(Fresco::Transform_ptr, unsigned d = 0);
	virtual void body(Fresco::Graphic_ptr);
	virtual Fresco::Graphic_ptr body();
      protected:
	unsigned depth;
    };

  } // namespace
} // namespace

#endif
