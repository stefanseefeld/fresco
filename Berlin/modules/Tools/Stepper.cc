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
#include <Prague/Sys/Tracer.hh>
#include <Berlin/Vertex.hh>
#include "Stepper.hh"

using namespace Prague;
using namespace Fresco;

using namespace Berlin::ToolKit;

class Stepper::Notifier : public Timer::Notifier
{
  public:
    Notifier(Stepper *s) : my_stepper(s) { }
    virtual void notify() { my_stepper->step(); }
  private:
    Stepper *my_stepper;
};

Stepper::Stepper() :
    my_delay(500),
    my_delta(300),
    my_notifier(new Notifier(this)),
    my_timer(my_notifier)
{ }

Stepper::~Stepper()
{
    Trace trace("Stepper::~Stepper");
    stop();
    delete my_notifier;
}

void Stepper::press(PickTraversal_ptr traversal, const Input::Event &event)
{
    Trace trace("Stepper::press");
    ControllerImpl::press(traversal, event);
    start();
}

void Stepper::release(PickTraversal_ptr traversal,
		      const Input::Event &event)
{
    Trace trace("Stepper::release");
    stop();
    ControllerImpl::release(traversal, event);
}

void Stepper::step()
{
    Trace trace("Stepper::step");
    execute();
}

void Stepper::start()
{
    my_timer.start(Prague::Time::currentTime() + my_delay, my_delta);
}

void Stepper::stop()
{
    my_timer.stop();
}
