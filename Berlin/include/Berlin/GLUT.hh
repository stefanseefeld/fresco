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

#ifndef _GLUT_hh
#define _GLUT_hh

#include <Warsaw/config.hh>
#include <Warsaw/Types.hh>
#include <Warsaw/Input.hh>
#include <Prague/Sys/Thread.hh>
#include <Prague/Sys/ThreadQueue.hh>
#include <vector>

// @@@ FIXME! Need a better way for this (can't hardcode it!)
// Screen resolution (in pixels)
const Coord screenx = 1024;
const Coord screeny = 786;

// Screen dimensions (physical size in millimeters)
const Coord screendimx = 360.0f;
const Coord screendimy = 270.0f;


using namespace Prague;

// -- Forward Declarations
class GLUTConsole;
class GLUTHandler;

// -- Class Declarations

/**
 * GLUT drawable implementation. This drawable will be used by the
 * GLDrawingKit only.
 **/
class GLUTDrawable {

private:
    
    friend class GLUTConsole;
    friend class DrawableTie<GLUTDrawable>;
  
public:
    typedef long Pixel;
    DrawableTie<GLUTDrawable>::PixelFormat pixelFormat();
    
    PixelCoord width() const { return _width; }
    PixelCoord height() const { return _height; }
    PixelCoord vwidth() const { return _width;}
    PixelCoord vheight() const { return _height;}
    Coord resolution(Axis a) const;
    Coord dpi(Axis a) const { return resolution(a) * 254.0; }
    PixelCoord rowlength() { return 0; }
    Pixel map(const Color &) { return 0; }
    void *readBuffer() { return 0; }
    void *writeBuffer() { return 0; }
    
    /*
     * Read one or more pixels from framebuffer
     */
    void readPixel(PixelCoord x, PixelCoord y, Pixel &p) { }
    void readPixels(PixelCoord, PixelCoord, PixelCoord, PixelCoord, void *) { }
    
    /*
     * Draw primitives with the current color (Pixel)
     */
    void setColor(Pixel p) { } 
    void drawPixel(PixelCoord x, PixelCoord y) { }
    void drawHLine(PixelCoord x, PixelCoord y, PixelCoord w) { }
    void drawVLine(PixelCoord x, PixelCoord y, PixelCoord h) { }
    void drawLine(PixelCoord x, PixelCoord y, PixelCoord w, PixelCoord h) { }
    void drawBox(PixelCoord x, PixelCoord y, PixelCoord w, PixelCoord h) { }
    
    /*
     * Draw primitives with the given color (Pixel). 
     */
    void putPixel(PixelCoord x, PixelCoord y, Pixel p) { }
    void putHLine(PixelCoord x, PixelCoord y, PixelCoord w, void *p) { }
    void putVLine(PixelCoord x, PixelCoord y, PixelCoord h, void *p) { }
    void drawPixels(PixelCoord x, PixelCoord y, PixelCoord w, PixelCoord h, void *p) { }
    
    /*
     * Fast blits
     */
    void blit(PixelCoord, PixelCoord, PixelCoord, PixelCoord, PixelCoord, PixelCoord);
    void blit(const GLUTDrawable &, PixelCoord, PixelCoord, PixelCoord, PixelCoord, PixelCoord, PixelCoord);
    
    void flush() { }
    void flush(PixelCoord x, PixelCoord y, PixelCoord w, PixelCoord h) { }

    void init();
    void finish();
    
    /**
     * Render the "cached" scene (i.e. the display lists comprising
     * the scene). This is a slight breach of abstraction, but it is
     * by far the easiest solution.
     **/
    void render();

    
    /**
     * GLUT window may be reshaped by the user.
     **/
    void reshape(int width, int height);
			
private:
    
    // Constructor and destructor
    GLUTDrawable();
    ~GLUTDrawable();
    
    /// Display width
    int _width;
    
    /// Display height
    int _height;

    /// Main display list
    unsigned int _displist;
    
    /// Access mutex (to control access to display lists)
    Mutex _mutex;

};


/**
 * GLUT console implementation.
 **/
class GLUTConsole {

    friend class GLUTHandler;
    
public:
    
    typedef GLUTDrawable Drawable;
    GLUTConsole();
    ~GLUTConsole();
    static DrawableTie<Drawable> *drawable() { return _drawable; }
    static DrawableTie<Drawable> *newDrawable(PixelCoord, PixelCoord, PixelCoord) { return 0; }
    
    Input::Event *nextEvent();
    void wakeup();
    void activate_autoplay() { _autoplay = true; }
    
private:

    bool _autoplay;

    /// Capacity of event queue
    static const int eventQueueCapacity = 100;

    /// Drawable vector
    //static vector<DrawableTie<Drawable> *> _drawables;
    static DrawableTie<Drawable> *_drawable;

    /// Event producer-consumer queue (for polling threads)
    Thread::Queue<Input::Event *> _eventQueue;
    
};


// -- Inline functions

inline Coord GLUTDrawable::resolution(Axis a) const
{
    // Return the resolution as dots/pixels per tenth of a millimeter    
    return a == xaxis 
	? 0.1 * screenx / screendimx 
	: 0.1 * screeny / screendimy;
}

#endif /* GLUT.hh */
