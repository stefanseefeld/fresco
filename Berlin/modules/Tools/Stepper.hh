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
#ifndef _ToolKit_Stepper_hh
#define _ToolKit_Stepper_hh

#include <Prague/Sys/Time.hh>
#include <Prague/Sys/Timer.hh>
#include "TriggerImpl.hh"

namespace Berlin
{
  namespace ToolKit
  {

    //. The Stepper class implements a button with autorepeat.
    class Stepper : public TriggerImpl
    {
    class Notifier;
    friend class Notifier;
      public:
    Stepper();
    ~Stepper();
//      protected:
    virtual void press(Fresco::PickTraversal_ptr,
               const Fresco::Input::Event &);
    virtual void release(Fresco::PickTraversal_ptr,
                 const Fresco::Input::Event &);
    virtual void step();
      private:
    void start();
    void stop();
    Prague::Time  my_delay;
    Prague::Time  my_delta;
    Notifier     *my_notifier;
    Prague::Timer my_timer;
    };

  } // namespace
} // namespace

#endif
