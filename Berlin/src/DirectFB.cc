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

PortableServer::POA_var DirectFBConsole::s_poa;
DirectFBConsole::dlist_t DirectFBConsole::s_drawables;
IDirectFB * DirectFBConsole::s_dfb = 0;
IDirectFB * DirectFBDrawable::s_dfb = 0;

//////////////////////////////////////////////////////////////////////////////
// DirectFBDrawable implementation
//////////////////////////////////////////////////////////////////////////////
DirectFBDrawable::DirectFBDrawable(const char * name,
				   IDirectFB * dfb,
				   DFBSurfaceDescription & dsc)
    : m_name(name) {
    Prague::Trace("DirectFBDrawable::DirectFBDrawable()");

    DFBResult ret;
    ret = dfb->CreateSurface(dfb, &dsc, &m_surface);
    if (ret) {
	cerr << "DirectFBDrawable: Couldn't create surface \"" << name << "\"."<< endl;
	exit(-5);
    }

    if (s_dfb == 0) s_dfb = dfb;

    DFBSurfacePixelFormat pixel_format;
    m_surface->GetPixelFormat(m_surface, &pixel_format);
 
    switch(pixel_format) {
    case DSPF_A1:
        m_format.depth       = 1;    m_format.size        = 1;
        m_format.red_mask    = 0;    m_format.red_shift   = 0;
        m_format.green_mask  = 0;    m_format.green_shift = 0;
        m_format.blue_mask   = 0;    m_format.blue_shift  = 0;
        m_format.alpha_mask  = 1;    m_format.alpha_shift = 0;
        break;
    case DSPF_A8:
	m_format.depth       = 8;    m_format.size        = 8;
        m_format.red_mask    = 0;    m_format.red_shift   = 0;
        m_format.green_mask  = 0;    m_format.green_shift = 0;
        m_format.blue_mask   = 0;    m_format.blue_shift  = 0;
        m_format.alpha_mask  = 0xFF; m_format.alpha_shift = 0;
        break;
    case DSPF_RGB15:
        m_format.depth       = 15;   m_format.size        = 16;
        m_format.red_mask    = 0x1F; m_format.red_shift   = 10;
        m_format.green_mask  = 0x1F; m_format.green_shift = 5;
        m_format.blue_mask   = 0x1F; m_format.blue_shift  = 0;
        m_format.alpha_mask  = 0;    m_format.alpha_shift = 0;
        break;
    case DSPF_RGB16:
        m_format.depth       = 16;   m_format.size        = 16;
        m_format.red_mask    = 0x1F; m_format.red_shift   = 11;
        m_format.green_mask  = 0x3F; m_format.green_shift = 5;
        m_format.blue_mask   = 0x1F; m_format.blue_shift  = 0;
        m_format.alpha_mask  = 0;    m_format.alpha_shift = 0;
        break;
    case DSPF_RGB24:
        m_format.depth       = 24;   m_format.size        = 24;
        m_format.red_mask    = 0xFF; m_format.red_shift   = 16;
        m_format.green_mask  = 0xFF; m_format.green_shift = 8;
        m_format.blue_mask   = 0xFF; m_format.blue_shift  = 0;
        m_format.alpha_mask  = 0;    m_format.alpha_shift = 0;
        break;
   case DSPF_RGB32:
        m_format.depth       = 32;   m_format.size        = 24;
        m_format.red_mask    = 0xFF; m_format.red_shift   = 16;
        m_format.green_mask  = 0xFF; m_format.green_shift = 8;
        m_format.blue_mask   = 0xFF; m_format.blue_shift  = 0;
        m_format.alpha_mask  = 0;    m_format.alpha_shift = 0;
        break;
    case DSPF_ARGB:
        m_format.depth       = 32;   m_format.size        = 32;
        m_format.red_mask    = 0xFF; m_format.red_shift   = 16;
        m_format.green_mask  = 0xFF; m_format.green_shift = 8;
        m_format.blue_mask   = 0xFF; m_format.blue_shift  = 0;
        m_format.alpha_mask  = 0xFF; m_format.alpha_shift = 24;
        break;
    }

    m_surface->GetSize(m_surface, &m_width, &m_height);
    Logger::log(Logger::drawing)
	<< "DirectFBDrawable: Drawable created!" << endl;
}

DirectFBDrawable::~DirectFBDrawable() {
    Prague::Trace("DirectFBDrawable::~DirectFBDrawable()");
    m_surface->Release(m_surface);
}

Warsaw::Drawable::BufferFormat
DirectFBDrawable::buffer_format() {
    Prague::Trace("DirectFBDrawable::buffer_format()");
    Warsaw::Drawable::BufferFormat format;
    format.skip_width = 0;
    format.width = width();
    format.skip_height = 0;
    format.height = height();
    format.row_length = row_length();
    return format;
}


//////////////////////////////////////////////////////////////////////////////
// DirectFBConsole implementation
//////////////////////////////////////////////////////////////////////////////

DirectFBConsole::DirectFBConsole(int &argc,
				 char **argv,
				 PortableServer::POA_ptr poa)// throw (exception)
    : m_autoplay(false) {
    Prague::Trace trace("DirectFBConsole::DirectFBConsole()");  
    Logger::log(Logger::loader) << "trying to open console" << endl;
    
    DFBResult ret;
    DFBSurfaceDescription dsc;
    
    ret = DirectFBInit(&argc, &argv);
    if (ret) {
 	DirectFBError("DirectFBInit failed", ret);
 	Logger::log(Logger::drawing) << "DirectFBInit failed (" << ret << ")" << endl;
 	exit(-1);
    }

    ret = DirectFBCreate(&s_dfb);
    if(ret) {
	DirectFBError("DirectFBCreate failed", ret);
	Logger::log(Logger::drawing) << "DirectFBCreate failed (" << ret << ")" << endl;
	exit(-2);      
    }
    
    Logger::log(Logger::loader)
	<< "DirectFBConsole: DirectFB initialized." << endl;
    
    s_dfb->SetCooperativeLevel(s_dfb, DFSCL_FULLSCREEN);
    
    ret = s_dfb->GetInputDevice(s_dfb, DIDID_MOUSE, &m_mouse);
    if (ret) {
	DirectFBError("DirectFBGetInputDevice (mouse) failed", ret);
	Logger::log(Logger::drawing) << "DirectFBGetInputDevice (mouse) failed (" << ret << ")" << endl;
	s_dfb->Release(s_dfb);
	exit(-3); 
    }
    
    ret = s_dfb->GetInputDevice(s_dfb, DIDID_KEYBOARD, &m_keyboard);
    if (ret) {
	DirectFBError("DirectFBGetInputDevice (keyboard) failed", ret);
	Logger::log(Logger::drawing) << "DirectFBGetInputDevice (keyboard) (" << ret << ")" << endl;
	m_mouse->Release(m_mouse);
	s_dfb->Release(s_dfb);
	exit(-4); 
    }
    ret = m_mouse->CreateInputBuffer(m_mouse, &m_mouse_buf);
    if (ret) {
	DirectFBError("DirectFBCreateInputBuffer (mouse) failed", ret);
	Logger::log(Logger::drawing) << "DirectFBCreateInputBuffer (mouse) failed (" << ret << ")" << endl;
	m_keyboard->Release(m_keyboard);
	m_mouse->Release(m_mouse);
	s_dfb->Release(s_dfb);
	exit(-5);
    }

    ret = m_keyboard->AttachInputBuffer(m_keyboard, m_mouse_buf);
    if (ret) {
	DirectFBError("DirectFB: AttachInputBuffer failed", ret);
	Logger::log(Logger::drawing) << "DirectFB: AttachInputBuffer failed (" << ret << ")" << endl;
	m_mouse_buf->Release(m_mouse_buf);
	m_keyboard->Release(m_keyboard);
	m_mouse->Release(m_mouse);
	s_dfb->Release(s_dfb);
	exit(-6);
    }
    
    Logger::log(Logger::loader) << "DirectFBConsole: Got input devices." << endl;
    
    dsc.flags = DSDESC_CAPS;
    dsc.caps  = DFBSurfaceCapabilities(DSCAPS_PRIMARY);
    
    Drawable * primary_drawable = new DirectFBDrawable("Primary", s_dfb, dsc);
    s_drawables.push_back(new DrawableTie<Drawable>(primary_drawable));
    primary = primary_drawable->surface();
    
    // Enable alpha blending
    primary->SetBlittingFlags(primary, DSBLIT_BLEND_ALPHACHANNEL);
    
    // Get resolutions and sizes needed for event handling later:
    m_size[0] = primary_drawable->width(); m_size[1] = primary_drawable->height();
    m_resolution[0] = primary_drawable->resolution(Warsaw::xaxis);
    m_resolution[1] = primary_drawable->resolution(Warsaw::yaxis);
    
    m_position[0] = 0; m_position[1] = 0;

    // Clear the screen...
    primary_drawable->draw_box(0, 0, m_size[0], m_size[1]);
    primary_drawable->flush();
    // clear other page too!
    primary_drawable->draw_box(0, 0, m_size[0], m_size[1]);
    primary_drawable->flush();
    
    s_poa = PortableServer::POA::_duplicate(poa);
    pipe(m_wakeup_pipe);
}

DirectFBConsole::~DirectFBConsole() {
    Prague::Trace trace("DirectFBConsole::~DirectFBConsole()");
    
    for (dlist_t::iterator i = s_drawables.begin();
	 i != s_drawables.end(); ++i)
	delete *i;
    
    m_keyboard->Release(m_keyboard);
    m_mouse_buf->Release(m_mouse_buf);
    m_mouse->Release(m_mouse);
    s_dfb->Release(s_dfb);
    close(m_wakeup_pipe[0]);
    close(m_wakeup_pipe[1]);
}

DrawableTie<DirectFBDrawable> *
DirectFBConsole::drawable() {
    Prague::Trace trace("DirectFBConsole::drawable()");
    assert(s_drawables.size());
    return s_drawables.front();
}

DrawableTie<DirectFBDrawable> *
DirectFBConsole::create_drawable(PixelCoord w, PixelCoord h, PixelCoord d) {
    DFBSurfaceDescription dsc;
    switch (d) {
    case 1:
	dsc.pixelformat = DSPF_A8;
	break;
    case 2:
	dsc.pixelformat = DSPF_RGB16;
	break;
    case 3:
	dsc.pixelformat = DSPF_RGB24;
	break;
    default:
	dsc.pixelformat = DSPF_ARGB;
    }
    dsc.width = w;
    dsc.height = h;
    dsc.caps  = DFBSurfaceCapabilities(DSCAPS_VIDEOONLY);
    dsc.flags = DFBSurfaceDescriptionFlags(DSDESC_PIXELFORMAT |
					   DSDESC_WIDTH |
					   DSDESC_HEIGHT |
					   DSDESC_CAPS);

    s_drawables.push_back(new DrawableTie<DirectFBDrawable>(
			    new DirectFBDrawable("display-memory", s_dfb, dsc))
			  );
    return s_drawables.back();
}

DrawableTie<DirectFBDrawable> *
DirectFBConsole::create_drawable(DirectFBDrawable *drawable) {
    Prague::Trace("DirectFBConsole::create_drawable(DirectFBDrawable *, ...)");
    s_drawables.push_back(new DrawableTie<DirectFBDrawable>(drawable));
    return s_drawables.back();
}

Warsaw::Drawable_ptr
DirectFBConsole::activate_drawable(DrawableTie<DirectFBDrawable> *d) {
    Prague::Trace("DirectFBConsole::activate_drawable()");
    PortableServer::ObjectId *oid = s_poa->activate_object(d);
    d->_remove_ref();
    delete oid;
    return d->_this();
}

DrawableTie<DirectFBDrawable> *
DirectFBConsole::reference_to_servant(Warsaw::Drawable_ptr drawable) {
    Trace trace("DirectFBConsole::reference_to_servant()");
    try	{
	PortableServer::Servant servant = s_poa->reference_to_servant(drawable);
	for (dlist_t::iterator i = s_drawables.begin();
	     i != s_drawables.end();
	     ++i)
	    if (*i == servant) return *i;
    }
    catch (const PortableServer::POA::ObjectNotActive &) {}
    catch (const PortableServer::POA::WrongAdapter &) {}
    catch (const CORBA::OBJECT_NOT_EXIST &) {}
    return 0;
}

/*
static void readEvent(DFBInputEvent &e) {
    cerr << "readEvent()" << endl;
    Prague::Trace("DirectFBConsole::readEvent()");
    Logger::log(Logger::drawing)
	<< "DirectFBConsole::readEvent(...) ignored for now."
	<< endl;
}

static void writeEvent(DFBInputEvent &e) {
    cerr << "writeEvent()" << endl;
    Prague::Trace("DirectFBConsole::writeEvent()");
    Logger::log(Logger::drawing)
	<< "DirectFBConsole::writeEvent(...) ignored for now."
	<< endl;
}
*/

void DirectFBConsole::device_info(std::ostream &os) {
  os << "sorry, device info isn't available for DirectFB at this time" << std::endl;
}


Input::Event * DirectFBConsole::next_event() {
    Prague::Trace trace("DirectFB::Console::next_event()");
    DFBInputEvent event;
    m_mouse_buf->WaitForEvent(m_mouse_buf);
    m_mouse_buf->GetEvent(m_mouse_buf, &event);
    return synthesize(event);
}

void DirectFBConsole::wakeup() {
    Prague::Trace("DirectFBConsole::wakeup()");
    char c = 'z'; write(m_wakeup_pipe[1],&c,1);
}

Input::Event *DirectFBConsole::synthesize(const DFBInputEvent &e) {
    Prague::Trace("DirectFBConsole::synthesize(...)");
    Input::Event_var event = new Input::Event;
    Input::Position position;

    switch (e.flags) {
    case DIEF_AXISABS:
	switch(e.axis) {
	case DIAI_X:
	    m_position[0] = e.axisabs;
	    break;
	case DIAI_Y:
	    m_position[1] = e.axisabs;
	    break;
	case DIAI_Z:
	    return event._retn();
	default:
	    return event._retn();
	}
	position.x = m_position[0] / m_resolution[0];
	position.y = m_position[1] / m_resolution[1];
	event->length(1);
	event[0].dev = 1;
	event[0].attr.location(position);
	break;
    case DIEF_AXISREL:
	switch(e.axis) {
	case DIAI_X:
	    if (m_position[0] + e.axisrel >= 0 &&
		m_position[0] + e.axisrel <= m_size[0])
		m_position[0] += e.axisrel;
	    break;
	case DIAI_Y:
	    if (m_position[1] + e.axisrel >= 0 &&
		m_position[1] + e.axisrel <= m_size[1])
		m_position[1] += e.axisrel;
	    break;
	case DIAI_Z:
	    return event._retn();
	default:
	    return event._retn();
	}
	position.x = m_position[0] / m_resolution[0];
	position.y = m_position[1] / m_resolution[1];
	event->length(1);
	event[0].dev = 1;
	event[0].attr.location(position);
	break;
    case DIEF_BUTTON:
	Input::Toggle toggle;
	if (e.type == DIET_BUTTONPRESS)
	    toggle.actuation = Input::Toggle::press;
	else
	    toggle.actuation = Input::Toggle::release;
	toggle.number = e.button - DIBI_FIRST;
	position.x = m_position[0]/m_resolution[0];
	position.y = m_position[1]/m_resolution[1];
	position.z = 0;
	event->length(2);
	event[0].dev = 1;
	event[0].attr.selection(toggle);
	event[0].attr._d(Input::button);
	event[1].dev = 1;
	event[1].attr.location(position);
	break;
    case DIEF_KEYCODE:
	break;
    case DIEF_MODIFIERS:
	break;
    default:
	Logger::log(Logger::drawing)
	    << "DirectFBConsole: Unknown DirectFB Input Event recieved."
	    << endl;
    }
    return event._retn();
}

