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

// -- OpenGL Includes
extern "C" {
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
}

class GLUTHandler {
    
public:
    GLUTHandler() { }
    ~GLUTHandler() { }

    static void init(GLUTConsole *console, int &argc, char **argv, const char *name, int w, int h);
    
private:
    
    static void *start(void *p) {
	glutMainLoop();
    }
    
    static void render();
    static void reshape(int width, int height);
    static void keyboard(unsigned char key, int x, int y);
    static void special(int key, int x, int y);
    static void mouse(int button, int state, int x, int y);
    static void mouseMotion(int x, int y);
 
    static Thread _glutThread;
    static GLUTConsole *_console;

    static const int numbuttons = 3;
    static int button_state[numbuttons];
};

// -- Static member variable initializations
Thread GLUTHandler::_glutThread(GLUTHandler::start, 0);
int GLUTHandler::button_state[3];
GLUTConsole *GLUTHandler::_console = 0;
DrawableTie<GLUTDrawable> *GLUTConsole::_drawable = 0;

// -- Code Segment

void GLUTHandler::init(GLUTConsole *console, int &argc, char **argv, const char *name, int w, int h)
{
    _console = console;

    // Initialize the GLUT library
    glutInit(&argc, argv);
    
    // Initialize display mode and the window
    //glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(w, h);
    
    // Okay, create the window
    glutCreateWindow(name);
    
    // Specify the display callback functions
    glutDisplayFunc(render);
    glutReshapeFunc(reshape);
    
    // Install input handlers
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutMotionFunc(mouseMotion);
    glutPassiveMotionFunc(mouseMotion);

    for (int i = 0; i < numbuttons; i++) button_state[i];

    // Start the GLUT thread
    _glutThread.start();
}

void GLUTHandler::render()
{
    cerr << "GLUTHandler::render() -- enter" << endl;
    
    // Clear the canvas
    //glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    // Render the Berlin scene graph!
    _console->drawable()->impl().render();

    // Need to flip, we're double-buffered!
    glutSwapBuffers();
    cerr << "GLUTHandler::render() -- done" << endl;
}

void GLUTHandler::reshape(int width, int height)
{
    _console->drawable()->impl().reshape(width, height);
    glutPostRedisplay();
}

void GLUTHandler::keyboard(unsigned char key, int x, int y)
{
    Input::Event_var event = new Input::Event;
    
    // Keyboard event
    Input::Toggle toggle;
    toggle.actuation = Input::Toggle::press;
    toggle.number = key;
    event->length(1);
    event[0].dev = 0;
    event[0].attr.selection(toggle); event[0].attr._d(Input::key);
    
    // Add the event to the queue
    _console->_eventQueue.push(event._retn());

    glutPostRedisplay();
}

void GLUTHandler::special(int key, int x, int y)
{
    // @@@ How to handle special keystrokes?
}

void GLUTHandler::mouse(int button, int state, int x, int y)
{
    // Is this change in button state?
    if (button_state[button] != state) {
	
	Input::Event_var event = new Input::Event;
	
	// Fill out the event object
	Input::Toggle toggle;
	if (state == GLUT_DOWN)
	    toggle.actuation = Input::Toggle::press;
	else
	    toggle.actuation = Input::Toggle::release;
 	toggle.number = button;
	Input::Position position;
	position.x = x / _console->drawable()->resolution(xaxis);
	position.y = y / _console->drawable()->resolution(yaxis);
	position.z = 0;
	event->length(2);
	event[0].dev = 1;
	event[0].attr.selection(toggle); event[0].attr._d(Input::button);
	event[1].dev = 1;
	event[1].attr.location(position);

	// Add the event to the queue and update state info
	_console->_eventQueue.push(event._retn());
	button_state[button] = state;
    }
    glutPostRedisplay();
}

void GLUTHandler::mouseMotion(int x, int y)
{
    Input::Event_var event = new Input::Event;
    
    // Mouse movement function (we rely on this being called only when
    // changes in the cursor are detected).
    Input::Position position;
    position.x = x / _console->drawable()->resolution(xaxis);
    position.y = y / _console->drawable()->resolution(yaxis);
    position.z = 0;
    event->length(1);
    event[0].dev = 1;
    event[0].attr.location(position);    
    
    _console->_eventQueue.push(event._retn());

    glutPostRedisplay();
}


// -- GLUTDrawable implementation

GLUTDrawable::GLUTDrawable()
    : _displist(0)
{
    // empty (can't allocate display lists before GLUT is initialized)
}

GLUTDrawable::~GLUTDrawable()
{
    MutexGuard guard(_mutex);
    glDeleteLists(_displist, 1);
}

void GLUTDrawable::init()
{
    // Start the definition of the display list
    _mutex.lock();
    if (_displist == 0) {
	_displist = glGenLists(1);
	if (_displist == 0) throw 0;
    }
    cerr << "Locking and rendering in display list " << _displist << endl; 
    glNewList(_displist, GL_COMPILE);
}

void GLUTDrawable::finish()
{
    // End display list definition and tell GLUT to redraw
    glEndList();
    _mutex.unlock();
    cerr << "Display list finished and unlocked." << endl;
    glutPostRedisplay();
}

void GLUTDrawable::render()
{
    // Get access to display list and call it
    MutexGuard guard(_mutex);
    if (_displist != 0) {
	glCallList(_displist);
	cerr << "Rendered display list " << _displist << endl;
    }
}

void GLUTDrawable::reshape(int width, int height)
{
    _width = width; _height = height;

    float _fov = 60.0f; 
    float _near = 1.0f;
    float _far = 1000.0f;

    // Reset the viewport
    glViewport(0, 0, (GLsizei) _width, (GLsizei) _height);
    
    // Set up a new projection mode
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective(_fov, (GLfloat) _width / (GLfloat) _height, _near, _far);
    glOrtho(0, _width / resolution(xaxis), _height / resolution(yaxis),
	    0, -1000.0, 1000.0); 
    glTranslatef(0.375, 0.375, 0.);
}

DrawableTie<GLUTDrawable>::PixelFormat GLUTDrawable::pixelFormat()
{
    // Load dummy values (@@@ How do we fill in this correctly?)
    DrawableTie<GLUTDrawable>::PixelFormat pft = {
	32, 32, 0xff000000, 24, 0x00ff0000, 16, 0x0000ff00, 8, 0x000000ff, 0
    };
    /*    DrawableTie<GLUTDrawable>::PixelFormat pft = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};
    */
    return pft;
}


// -- GLUTConsole implementation 

GLUTConsole::GLUTConsole()
    : _eventQueue(eventQueueCapacity)
{
    _drawable = new DrawableTie<Drawable>(new GLUTDrawable);

    // @@@ Hardcoded stuff for simplicity!
    int argc = 1;
    char *argv[] = { "dummy" };
    int winwidth = 640;
    int winheight = 480;
	
    // Initialize and launch the GLUT handling thread
    GLUTHandler::init(this, argc, argv, "Berlin-on-glut", winwidth, winheight);
}

GLUTConsole::~GLUTConsole()
{
    // @@@ Stop the GLUT thread somehow
    delete _drawable;
}

Input::Event *GLUTConsole::nextEvent()
{
    return _eventQueue.pop();
}

void GLUTConsole::wakeup()
{
    // Add an empty event to the event queue to wake up the combined
    // rendering/input thread. In the event manager, an empty event
    // pointer (NULL or 0) will cause a window repair, so this is
    // correct behavior.
    _eventQueue.push(0);
}
