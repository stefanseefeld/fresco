/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 2000 Niklas Elmqvist <elm@3dwm.org>
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

#include "Berlin/Console.hh"
#include <Prague/Sys/Tracer.hh>
#include <Prague/Sys/Thread.hh>
#include <Prague/Sys/ThreadQueue.hh>

#include <cmath>

// @@@ Currently hard-coded for the CML 3D-CUBE! (standard cavelib, I
// think)
const int CAVENumComponents = 3;
const int CAVENumButtons = 4;
const float tolerance = 0.1f;
typedef float CAVEPosData[CAVENumComponents];
typedef int CAVEButtonData[CAVENumButtons];

/**
 * CAVE event listener (runs in its own thread and listens for CAVE
 * events to add to the CAVEConsole event queue).
 **/
class EventListener {
    
    EventListener(ThreadQueue<Input::Event> *queue) 
	: _listener(proc, this), _queue(queue) { }
    ~EventListener() { cancel(); }
    void run() { _listener.start(); }
    void cancel() { _listener.join(0); }

private:
    
    /**
     * Listener thread bootstrapping function.
     **/
    static void *proc(void *X) {
	EventListener *listener = reinterpret_cast<EventListener *>(X);
	listener->start();
	return 0;
    }

    /**
     * Main listening function.
     **/
    void start();

    // Listener thread
    Thread _listener;

    // Event queue
    ThreadQueue<Input::Event *> *_queue;
    
};

CAVEConsole::CAVEConsole()
    : _autoplay(false)
{
    cerr << "Initializing CAVELib console " <<
	 << "(CAVELib version " << CAVEVersion << " with "
	 << CAVENumPipes() << " rendering pipes." << endl;
    _drawable = new CAVEDrawable;

    // @@@ Set up callbacks
    
    // @@@ Create event listening thread
}

CAVEConsole::~CAVEConsole()
{
    delete _drawable;
}

DrawableTie<Drawable> *CAVEConsole::drawable()
{
    return 0;
}

DrawableTie<CAVEDrawable> *CAVEConsole::newDrawable(PixelCoord w, PixelCoord h, PixelCoord d)
{
    return 0;
}

Input::Event *CAVEConsole::nextEvent()
{
    return _eventQueue.pop();
}

void CAVEConsole::wakeup()
{
    
}

CAVEDrawable::CAVEDrawable()
{
    // Compute the resolution
    float conv2mm = CAVEConvertFromCAVEUnits(1.0f, CAVE_METERS) * 1000.0f;
    _resolution = 1 / (conv2mm * 10.0f);
}

CAVEDrawable::~CAVEDrawable()
{
    // empty
}

// @@@ Ugly! Need real vector classes...
float dist3d(const CAVEPosData &v1, const CAVEPosData &v2)
{
    float result = 0.0f;
    for (int i = 0; i < CAVENumComponents; i++) {
	float diff = = v1[i] - v2[i];
	diff *= diff;
	result += diff;
    }
    return sqrt(result);
}

void EventListener::start()
{
    CAVEPosData position, old_position;
    CAVEPosData orientation, old_orientation;
    CAVEButtonData buttons, old_buttons;
    
    // @@@ How long should we loop here? Indefinitely at current.
    while (true) {
	
	// Get CAVE input state (only pointer state at the moment!)
	CAVEGetPosition(CAVE_WAND, position);
	CAVEGetOrientation(CAVE_WAND, orientation);
	
	// Yes, this is ugly, but it's cavelib's fault...
	buttons[0] = CAVEBUTTON1; buttons[1] = CAVEBUTTON2; 
	buttons[2] = CAVEBUTTON3; buttons[3] = CAVEBUTTON4;

	Input::Position pos;
	pos.x = position[0] / drawable->resolution(xaxis);
	pos.y = position[1] / drawable->resolution(yaxis);
	pos.z = position[2] / drawable->resolution(zaxis);

	Input::Position ori;	
	ori.x = orientation[0]; ori.y = orientation[1]; ori.z = orientation[2];

	// Orientation or positional changes
	if (dist3d(position, old_position) < tolerance ||
	    dist3d(orientation, old_orientation) < tolerance) {
	    
	    Input::Event_var event = new Input::Event;
	    event->length(2);
	    event[0].dev = 1; 
	    event[0].attr.location(pos);
	    event[1].dev = 1; 
	    event[1].attr.location(ori);

	    // Add the event to the thread queue (producer-consumer)
	    _queue->push(event._retn());
	}
	
	// Check changes in buttons
	for (int i = 0; i < CAVENumButtons; i++) {

	    // @@@ Should probably check for true/false here, not use
	    // equality since these are integers...
	    if (buttons[i] != old_buttons[i]) {

		Input::Toggle toggle;
		if (buttons[i]) 
		    toggle.actuation = Input::Toggle::press;
		else
		    toggle.actuation = Input::Toggle::release;
		toggle.number = i;
		
		Input::Event_var event = new Input::Event;
		event->length(3);
		event[0].dev = 1; 
		event[0].attr.selection(toggle);
		event[0].attr._d(Input::button);
		event[1].dev = 1; 
		event[1].attr.location(pos);
		event[2].dev = 1; 
		event[2].attr.location(ori);
		
		// Add the event to the thread queue (producer-consumer)
		_queue->push(event._retn());
	    }
	}

	// @@@ Need 3D vectors here...
	memcpy(old_position, position, sizeof(position));
	memcpy(old_orientation, orientation, sizeof(orientation));
	memcpy(old_buttons, buttons, sizeof(buttons));
    }
}
