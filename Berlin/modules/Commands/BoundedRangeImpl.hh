/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@fresco.org>
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
#ifndef _CommandKit_BoundedRangeImpl_hh
#define _CommandKit_BoundedRangeImpl_hh

#include <Prague/Sys/Thread.hh>
#include <Fresco/config.hh>
#include <Fresco/BoundedRange.hh>
#include <Berlin/SubjectImpl.hh>
#include <vector>

namespace Berlin
{
  namespace CommandKit
  {
    class BoundedRangeImpl : public virtual POA_Fresco::BoundedRange,
                             public SubjectImpl
    {
      public:
        BoundedRangeImpl(Fresco::Coord, Fresco::Coord, Fresco::Coord,
                         Fresco::Coord, Fresco::Coord, Fresco::Coord);
        virtual ~BoundedRangeImpl();
        virtual Fresco::BoundedRange::Settings state();
        virtual void state(const Fresco::BoundedRange::Settings &);
        virtual Fresco::Coord lower();
        virtual void lower(Fresco::Coord);
        virtual Fresco::Coord upper();
        virtual void upper(Fresco::Coord);
        virtual Fresco::Coord step();
        virtual void step(Fresco::Coord);
        virtual Fresco::Coord page();
        virtual void page(Fresco::Coord);
        virtual Fresco::Coord lvalue();
        virtual void lvalue(Fresco::Coord);
        virtual Fresco::Coord uvalue();
        virtual void uvalue(Fresco::Coord);

        virtual void forward();
        virtual void backward();
        virtual void fastforward();
        virtual void fastbackward();
        virtual void begin();
        virtual void end();
        virtual void adjust(Fresco::Coord);
      private:
        Fresco::BoundedRange::Settings my_settings;
        Fresco::Coord                  my_s;
        Fresco::Coord                  my_p;
        Prague::Mutex                  my_mutex;
    };

  } // namespace
} // namespace

#endif
