/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@fresco.org>
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
#ifndef _CommandKit_TelltaleImpl_hh
#define _CommandKit_TelltaleImpl_hh

#include <Prague/Sys/Thread.hh>
#include <Fresco/config.hh>
#include <Fresco/Telltale.hh>
#include <Berlin/SubjectImpl.hh>
#include <vector>

namespace Berlin
{
  namespace CommandKit
  {
    class TelltaleImpl : public virtual POA_Fresco::Telltale,
                         public SubjectImpl
    {
      public:
        TelltaleImpl(Fresco::TelltaleConstraint_ptr, CORBA::ULong m = 0);
        virtual ~TelltaleImpl();
        virtual void set(Fresco::Telltale::Mask);
        virtual void clear(Fresco::Telltale::Mask);
        virtual CORBA::Boolean test(Fresco::Telltale::Mask);
        virtual void modify(Fresco::Telltale::Mask, CORBA::Boolean);
        CORBA::ULong state() { return my_mask;}

        virtual void constraint(Fresco::TelltaleConstraint_ptr);
        virtual Fresco::TelltaleConstraint_ptr constraint();

      protected:
        Prague::Mutex                  my_mutex;
        CORBA::ULong                   my_mask;
        Fresco::TelltaleConstraint_var my_constraint;
    };

    class TelltaleConstraintImpl : public virtual POA_Fresco::TelltaleConstraint,
                                   public virtual RefCountBaseImpl
    {
      public:
        TelltaleConstraintImpl() {}
        virtual ~TelltaleConstraintImpl() {}
        void add(Fresco::Telltale_ptr);
        void remove(Fresco::Telltale_ptr);
        virtual void trymodify(Fresco::Telltale_ptr, Fresco::Telltale::Mask,
                               CORBA::Boolean) = 0;
      protected:
        typedef std::vector<Fresco::Telltale_var> tlist_t;

        Prague::Mutex my_mutex;
        tlist_t       my_telltales;
    };

    class ExclusiveChoice : public TelltaleConstraintImpl
    {
      public:
        ExclusiveChoice(Fresco::Telltale::Mask);
        virtual void trymodify(Fresco::Telltale_ptr, Fresco::Telltale::Mask,
                               CORBA::Boolean);
      private:
        Fresco::Telltale::Mask my_mask;
    };

    class SelectionRequired : public TelltaleConstraintImpl
    {
      public:
        SelectionRequired(Fresco::Telltale::Mask);
        virtual void trymodify(Fresco::Telltale_ptr, Fresco::Telltale::Mask,
                               CORBA::Boolean);
      private:
        Fresco::Telltale::Mask my_mask;
    };

    class ExclusiveRequired : public TelltaleConstraintImpl
    {
      public:
        ExclusiveRequired(Fresco::Telltale::Mask);
        virtual void trymodify(Fresco::Telltale_ptr, Fresco::Telltale::Mask,
                               CORBA::Boolean);
      private:
        Fresco::Telltale::Mask my_mask;
    };

  } // namespace
} // namespace

#endif
