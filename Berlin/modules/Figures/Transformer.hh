/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@berlin-consortium.org> 
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

#ifndef _Transformer_hh
#define _Transformer_hh

#include "Warsaw/config.hh"
#include "Berlin/TransformImpl.hh"
#include "Berlin/Allocator.hh"

class Transformer : public Allocator
{
 public:
  Transformer();
  virtual ~Transformer();
  virtual void request(Requisition &);
  virtual void traverse(Traversal_ptr);
  virtual Transform_ptr transformation();
  void allocate(Tag, const Allocation::Info &);
 private:
  TransformImpl *transform;
};

class BodyTransformer : public Transformer
{
public:
  BodyTransformer(Transformer*, unsigned d = 0);
  BodyTransformer(Transform_ptr, unsigned d = 0);
  virtual void body(Graphic_ptr);
  virtual Graphic_ptr body();
protected:
  unsigned depth;
};

#endif /* _Transformer_hh */
