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
#ifndef _WidgetKit_Motif_Adjustable_hh
#define _WidgetKit_Motif_Adjustable_hh

#include <Fresco/config.hh>
#include <Fresco/Command.hh>
#include <Berlin/ObserverImpl.hh>
#include <Berlin/ImplVar.hh>
#include <Berlin/ControllerImpl.hh>

namespace Berlin
{
  namespace WidgetKit
  {
    namespace Motif
    {

      class Adjustable : public ControllerImpl
      {
      class Observer : public ObserverImpl
      {
        public:
          Observer(Adjustable *a) : my_adjustable(a)
          { my_adjustable->_add_ref(); }
          ~Observer() { my_adjustable->_remove_ref(); }
          void update(const CORBA::Any &any)
          { my_adjustable->update(any); }
        private:
          Adjustable *my_adjustable;
      };
      friend class Observer;
      class Adjust;
      friend class Adjust;
    public:
      Adjustable();
      Fresco::Command_ptr create_adjust_cmd();
    protected:
      virtual void update(const CORBA::Any &any) = 0;
      virtual void adjust(const Fresco::OriginatedDelta &) = 0;
      Fresco::Observer_ptr observer();
    private:
      Impl_var<Observer> my_translate;
      };

    } // namespace
  } // namespace
} // namespace

#endif
