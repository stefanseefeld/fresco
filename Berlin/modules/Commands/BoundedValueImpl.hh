/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@fresco.org>
 * Copyright (C) 1999 Graydon Hoare <graydon@fresco.org>
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
#ifndef _BoundedValueImpl_hh
#define _BoundedValueImpl_hh

#include <Prague/Sys/Thread.hh>
#include <Fresco/config.hh>
#include <Fresco/BoundedValue.hh>
#include <Berlin/SubjectImpl.hh>
#include <vector>

namespace Berlin
{
  namespace CommandKit
  {

    class BoundedValueImpl : public virtual POA_Fresco::BoundedValue,
                             public SubjectImpl
    {
      public:
        BoundedValueImpl(Fresco::Coord, Fresco::Coord,
                        Fresco::Coord, Fresco::Coord, Fresco::Coord);
        virtual ~BoundedValueImpl();
        virtual Fresco::Coord lower();
        virtual void lower(Fresco::Coord);
        virtual Fresco::Coord upper();
        virtual void upper(Fresco::Coord);
        virtual Fresco::Coord step();
        virtual void step(Fresco::Coord);
        virtual Fresco::Coord page();
        virtual void page(Fresco::Coord);
        virtual Fresco::Coord value();
        virtual void value(Fresco::Coord);

        virtual void forward();
        virtual void backward();
        virtual void fastforward();
        virtual void fastbackward();
        virtual void begin();
        virtual void end();
        virtual void adjust(Fresco::Coord);
      private:
        Fresco::Coord _l;
        Fresco::Coord _u;
        Fresco::Coord _v;
        Fresco::Coord _s;
        Fresco::Coord _p;
        Prague::Mutex _mutex;
    };

  } // namespace
} // namespace

#endif
