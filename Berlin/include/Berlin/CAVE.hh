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

#ifndef _CAVE_hh
#define _CAVE_hh

#include <Warsaw/config.hh>
#include <Warsaw/Types.hh>
#include <Warsaw/Input.hh>
#include <Prague/Sys/Thread.hh>
#include <Prague/Sys/ThreadQueue.hh>
#include <vector>

// Cavelib OpenGL bindings
extern "C" {
#include <cave_ogl.h>
}

// -- Forward Declarations
class CAVEConsole;

// -- Class Declarations

/**
 * Cavelib drawable implementation (used as a tie implementation).  A
 * large part of the cavelib drawable has been left out since it is
 * not needed (and indeed, not supported) by the OpenGL CAVELib.  The
 * CAVEConsole/CAVEDrawable will be used by the GLDrawingKit
 * exclusively, so this is not an issue.
 **/
class CAVEDrawable {

private:
    
    friend class CAVEConsole;
    friend class DrawableTie<CAVEDrawable>;
  
public:
    typedef long Pixel;
    DrawableTie<CAVEDrawable>::PixelFormat pixelFormat();
    
    PixelCoord width() const { return _width; }
    PixelCoord height() const { return _height; }
    PixelCoord vwidth() const { return _width;}
    PixelCoord vheight() const { return _height;}
    Coord resolution(Axis a) const { return _resolution; }
    Coord dpi(Axis a) const { return resolution(a) * 254.0; }
    PixelCoord rowlength() { }
    Pixel map(const Color &) { }
    void *readBuffer() { /* no idea */ }
    void *writeBuffer() { /* no idea */ }
    
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
    void blit(PixelCoord, PixelCoord, PixelCoord, PixelCoord, PixelCoord, PixelCoord) { }
    void blit(const GGIDrawable &, PixelCoord, PixelCoord, PixelCoord, PixelCoord, PixelCoord, PixelCoord) { }
    
    void flush() { }
    void flush(PixelCoord x, PixelCoord y, PixelCoord w, PixelCoord h) { }
    
private:
    
    // Constructor and destructor (this is a tie, so they are private)
    CAVEDrawable(const char *);
    ~CAVEDrawable();
    
    // Display width (set once from a rendering process)
    int _width;
    
    // Display height (set once from a rendering process)
    int _height;
  
    // Resolution 
    float _resolution;
};


/**
 * Cavelib console implementation (also a tie implementation).
 **/
class CAVEConsole {
  
public:
    
    typedef CAVEDrawable Drawable;
    CAVEConsole();
    ~CAVEConsole();
    static DrawableTie<Drawable> *drawable() { return _drawable; }
    static DrawableTie<Drawable> *newDrawable(PixelCoord, PixelCoord, PixelCoord);
    
    Input::Event *nextEvent();
    void wakeup();
    void activate_autoplay() { autoplay = true; }
    
private:
    
    /// Single CAVE drawable instance
    DrawableTie<Drawable> *_drawable;

    /// Event producer-consumer queue (for threads)
    ThreadQueue<Input::Event *> _eventQueue;
    
    // Factor for converting from CAVE units to Berlin units
    float _caveToBerlinUnitFactor;

};


// -- Inline functions

inline Coord CAVEDrawable::resolution(Axis a) const
{
    // @@@ For now, hardcode the size of the CML 3D-CUBE (in mm:s)

    const Coord CUBEWallSize = 3000.0f;
    return a == xaxis ?
	0.1 * _width / CUBEWallSize :
	0.1 * _height / CUBEWallSize;
}

#endif /* CAVE.hh */
