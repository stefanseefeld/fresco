/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 2001 Tobias Hunger <tobias@berlin-consortium.org> 
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
#include <Prague/Sys/FdSet.hh>
#include <Prague/Sys/Tracer.hh>
#include "Berlin/Console.hh"

#include <unistd.h>

using namespace Prague;
using namespace Warsaw;

PortableServer::POA_var DirectFBConsole::m_poa;


////////////////////////////////////////////////////////////////////////////////
// DirectFBDrawable implementation
////////////////////////////////////////////////////////////////////////////////
DirectFBDrawable::DirectFBDrawable(const char *,
				   Warsaw::PixelCoord w,
				   Warsaw::PixelCoord h,
				   Warsaw::PixelCoord d) {
    Prague::Trace("DirectFBDrawable::DirectFBDrawable");    
}

DirectFBDrawable::~DirectFBDrawable() {
    Prague::Trace("DirectFBDrawable::~DirectFBDrawable");
}

Warsaw::Drawable::PixelFormat DirectFBDrawable::pixel_format() {
    Prague::Trace("DirectFBDrawable::pixel_format");
}


Warsaw::Drawable::BufferFormat DirectFBDrawable::buffer_format() {
    Prague::Trace("DirectFBDrawable::buffer_format");
}


////////////////////////////////////////////////////////////////////////////////
// DirectFBConsole implementation
////////////////////////////////////////////////////////////////////////////////

DirectFBConsole::DirectFBConsole(int &argc, char **argv, PortableServer::POA_ptr poa)// throw (exception)
  : m_autoplay(false)
{
  Logger::log(Logger::loader) << "trying to open console" << endl;
  Trace trace("DirectFBConsole::DirectFBConsole");

  DFBSurfaceDescription dsc;
  DirectFBCreate (&argc, &argv, &m_dfb);

  m_dfb->SetCooperativeLevel(m_dfb, DFSCL_FULLSCREEN);
  m_dfb->GetInputDevice(m_dfb, DIDID_KEYBOARD, &m_keyboard);
  m_dfb->GetInputDevice(m_dfb, DIDID_MOUSE, &m_mouse);
  m_keyboard->CreateInputBuffer(m_keyboard, &m_keyboard_buf);
  m_mouse->CreateInputBuffer(m_mouse, &m_mouse_buf);

  m_poa = PortableServer::POA::_duplicate(poa);
}

DirectFBConsole::~DirectFBConsole()
{
  Trace trace("DirectFBConsole::~DirectFBConsole");
  
  m_keyboard->Release(m_keyboard);
  m_mouse->Release(m_mouse);
  m_dfb->Release(m_dfb);
}

DrawableTie<DirectFBDrawable> * DirectFBConsole::drawable()
{
  Trace trace("DirectFBConsole::drawable");
}

DrawableTie<DirectFBDrawable> * DirectFBConsole::create_drawable(PixelCoord w, PixelCoord h, PixelCoord d)
{
    Prague::Trace("DirectFBConsole::create_drawable new");
}

DrawableTie<DirectFBDrawable> *DirectFBConsole::create_drawable(DirectFBDrawable *drawable)
{
    Prague::Trace("DirectFBConsole::create_drawable copy");
}

Warsaw::Drawable_ptr DirectFBConsole::activate_drawable(DrawableTie<DirectFBDrawable> *d)
{
    Prague::Trace("DirectFBConsole::activate_drawable");
}

DrawableTie<DirectFBDrawable> *DirectFBConsole::reference_to_servant(Warsaw::Drawable_ptr drawable)
{
  Trace trace("DirectFBConsole::reference_to_servant");
  try
    {
      PortableServer::Servant servant = m_poa->reference_to_servant(drawable);
    }
  catch (const PortableServer::POA::ObjectNotActive &) {}
  catch (const PortableServer::POA::WrongAdapter &) {}
  catch (const CORBA::OBJECT_NOT_EXIST &) {}
  return 0;
}

static void readEvent(DFBInputEvent &e)
{
    Prague::Trace("DirectFBConsole::readEvent");
}

static void writeEvent(DFBInputEvent &e)
{
    Prague::Trace("DirectFBConsole::writeEvent");
}

Input::Event *DirectFBConsole::next_event()
{
  Trace trace("DirectFB::Console::next_event");
}

void DirectFBConsole::wakeup() {
    Prague::Trace("DirectFBConsole::wakeup");
}

Input::Event *DirectFBConsole::synthesize(const DFBInputEvent &e)
{
    Prague::Trace("DirectFBConsole::synthesize");
}

