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
#ifndef _Manipulator_hh
#define _Manipulator_hh

#include <Prague/Sys/Tracer.hh>
#include <Fresco/config.hh>
#include <Fresco/Window.hh>
#include <Fresco/Desktop.hh>
#include <Berlin/CommandImpl.hh>
#include <Berlin/RefCountVar.hh>

namespace Berlin {
namespace DesktopKit {

class Manipulator : public CommandImpl
{
public:
  Manipulator(Fresco::Window_ptr w) : window(Fresco::Window::_duplicate(w)) {}
  virtual ~Manipulator() { Prague::Trace trace("Manipulator::~Manipulator");}
  virtual void execute(const CORBA::Any &) = 0;
protected:
  Fresco::Window_var window;
};

class Mover : public Manipulator
{
public:
  Mover(Fresco::Window_ptr window) : Manipulator(window) {}
  virtual void execute(const CORBA::Any &);
};

class Resizer : public Manipulator
{
public:
  Resizer(Fresco::Window_ptr window) : Manipulator(window) {}
  virtual void execute(const CORBA::Any &);
};

class MoveResizer : public Manipulator
{
public:
  MoveResizer(Fresco::Window_ptr, Fresco::Desktop_ptr, Fresco::Alignment, Fresco::Alignment, CORBA::Short);
  virtual void execute(const CORBA::Any &);
private:
  Fresco::Desktop_var desktop;
  Fresco::Alignment xalign, yalign;
  CORBA::Short border;
};

class Relayerer: public Manipulator
{
public:
  Relayerer(Fresco::Window_ptr window) : Manipulator(window) {}
  virtual void execute(const CORBA::Any &);
};

class Mapper : public Manipulator
{
public:
  Mapper(Fresco::Window_ptr window) : Manipulator(window) {}
  virtual void execute(const CORBA::Any &);
};

class Unmapper : public Manipulator
{
public:
  Unmapper(Fresco::Window_ptr window) : Manipulator(window) {}
  virtual void execute(const CORBA::Any &);
};

} // namespace
} // namespace

#endif
