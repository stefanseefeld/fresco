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
#ifndef _DirectFB_hh
#define _DirectFB_hh

#include <Warsaw/config.hh>
#include <Warsaw/Types.hh>
#include <Warsaw/Input.hh>
#include <Prague/Sys/Tracer.hh>
#include <Berlin/Logger.hh>
#include <vector>
extern "C"
{
#include <directfb.h>
}

class DirectFBConsole;

////////////////////////////////////////////////////////////////////////////////
// DirectFBDrawable declaration
////////////////////////////////////////////////////////////////////////////////

class DirectFBDrawable {
    friend class DirectFBConsole;
    friend class DrawableTie<DirectFBDrawable>;
public:
    DirectFBDrawable(const char *, Warsaw::PixelCoord = 0, Warsaw::PixelCoord = 0, Warsaw::PixelCoord = 0);
    ~DirectFBDrawable();
    
    typedef unsigned int Pixel; // unsigned int should be 32 bit:-)
    
    Warsaw::Drawable::PixelFormat pixel_format();
    Warsaw::Drawable::BufferFormat buffer_format();
    Warsaw::PixelCoord width() const;
    Warsaw::PixelCoord height() const;
    Warsaw::PixelCoord vwidth() const;
    Warsaw::PixelCoord vheight() const;
    Warsaw::Coord resolution(Warsaw::Axis a) const;
    Warsaw::Coord dpi(Warsaw::Axis a) const;
    Warsaw::PixelCoord row_length() const;
    Pixel map(const Warsaw::Color &) const;
    void *read_buffer() const;
    void *write_buffer() const;
    /*
     * read one or more pixels from framebuffer
     */
    void read_pixel(Warsaw::PixelCoord, Warsaw::PixelCoord, Pixel &);
    void read_pixels(Warsaw::PixelCoord, Warsaw::PixelCoord, Warsaw::PixelCoord, Warsaw::PixelCoord, void *);
    /*
     * draw primitives with the current color (Pixel)
     */
    void set_color(Pixel);
    void draw_pixel(Warsaw::PixelCoord,
		    Warsaw::PixelCoord);
    void draw_hline(Warsaw::PixelCoord,
		    Warsaw::PixelCoord,
		    Warsaw::PixelCoord);
    void draw_vline(Warsaw::PixelCoord,
		    Warsaw::PixelCoord,
		    Warsaw::PixelCoord);
    void draw_line(Warsaw::PixelCoord,
		   Warsaw::PixelCoord,
		   Warsaw::PixelCoord,
		   Warsaw::PixelCoord);
    void draw_box(Warsaw::PixelCoord,
		  Warsaw::PixelCoord,
		  Warsaw::PixelCoord,
		  Warsaw::PixelCoord);
    /*
     * draw primitives with the given color (Pixel)
     */
    void put_pixel(Warsaw::PixelCoord,
		   Warsaw::PixelCoord,
		   Pixel);
    void put_hline(Warsaw::PixelCoord,
		   Warsaw::PixelCoord,
		   Warsaw::PixelCoord,
		   void *);
    void put_vline(Warsaw::PixelCoord,
		   Warsaw::PixelCoord,
		   Warsaw::PixelCoord,
		   void *);
    void draw_pixels(Warsaw::PixelCoord,
		     Warsaw::PixelCoord,
		     Warsaw::PixelCoord,
		     Warsaw::PixelCoord,
		     void *);
    /*
     * fast blits
     */
    void blit(Warsaw::PixelCoord,
	      Warsaw::PixelCoord,
	      Warsaw::PixelCoord,
	      Warsaw::PixelCoord,
	      Warsaw::PixelCoord,
	      Warsaw::PixelCoord);
    void blit(const DirectFBDrawable &,
	      Warsaw::PixelCoord,
	      Warsaw::PixelCoord,
	      Warsaw::PixelCoord,
	      Warsaw::PixelCoord,
	      Warsaw::PixelCoord,
	      Warsaw::PixelCoord);
    void blit(Warsaw::Drawable_ptr,
	      Warsaw::PixelCoord,
	      Warsaw::PixelCoord,
	      Warsaw::PixelCoord,
	      Warsaw::PixelCoord,
	      Warsaw::PixelCoord,
	      Warsaw::PixelCoord);
    
    void flush();
    void flush(Warsaw::PixelCoord,
	       Warsaw::PixelCoord,
	       Warsaw::PixelCoord,
	       Warsaw::PixelCoord);
    void init() {
	Prague::Trace("DirectFBConsole::init");
    }
    void finish() {
	Prague::Trace("DirectFBConsole::finish");
    }
    
private:
};


////////////////////////////////////////////////////////////////////////////////
// DirectFBConsole declaration
////////////////////////////////////////////////////////////////////////////////

class DirectFBConsole {
    typedef DirectFBDrawable Drawable;
    
public:
    DirectFBConsole(int &, char **, PortableServer::POA_ptr);
    ~DirectFBConsole();
    static DrawableTie<Drawable> * drawable();
    static DrawableTie<Drawable> * create_drawable(Warsaw::PixelCoord,
						   Warsaw::PixelCoord,
						   Warsaw::PixelCoord);
    static DrawableTie<Drawable> * create_drawable(Drawable *);
    static Warsaw::Drawable_ptr activate_drawable(DrawableTie<DirectFBDrawable> *);
    static DrawableTie<Drawable> * reference_to_servant(Warsaw::Drawable_ptr);
    
    Warsaw::Input::Event *next_event();
    void wakeup();
    void activate_autoplay() { m_autoplay = true;}
    
private:
    Warsaw::Input::Event *synthesize(const DFBInputEvent &);

    IDirectFB            * m_dfb;
    IDirectFBInputDevice * m_keyboard;
    IDirectFBInputDevice * m_mouse;
    IDirectFBInputBuffer * m_keyboard_buf;
    IDirectFBInputBuffer * m_mouse_buf;
    
    bool   m_autoplay;
    static PortableServer::POA_var m_poa;  
};


////////////////////////////////////////////////////////////////////////////////
// DirectFBDrawable inlines
////////////////////////////////////////////////////////////////////////////////
inline void *DirectFBDrawable::read_buffer() const
{ 
    Prague::Trace("DirectFBDrawable::read_buffer");
}

inline void *DirectFBDrawable::write_buffer() const
{ 
    Prague::Trace("DirectFBDrawable::write_buffer");
}

inline Warsaw::PixelCoord DirectFBDrawable::width() const { 
    Prague::Trace("DirectFBDrawable::width");
}

inline Warsaw::PixelCoord DirectFBDrawable::height() const { 
    Prague::Trace("DirectFBDrawable::height");
}

inline Warsaw::PixelCoord DirectFBDrawable::vwidth() const { 
    Prague::Trace("DirectFBDrawable::vwidth");
}

inline Warsaw::PixelCoord DirectFBDrawable::vheight() const { 
    Prague::Trace("DirectFBDrawable::vheight");
}

inline Warsaw::Coord DirectFBDrawable::resolution(Warsaw::Axis a) const
{
    Prague::Trace("DirectFBDrawable::resolution");
}

inline Warsaw::Coord DirectFBDrawable::dpi(Warsaw::Axis a) const
{
    Prague::Trace("DirectFBDrawable::dpi");
}


inline Warsaw::PixelCoord DirectFBDrawable::row_length() const
{ 
    // return bytes-per-row
    Prague::Trace("DirectFBDrawable::row_length");
}

inline DirectFBDrawable::Pixel DirectFBDrawable::map(const Warsaw::Color &c) const
{
    Prague::Trace("DirectFBDrawable::map");
}

inline void DirectFBDrawable::set_color(Pixel c)
{
    Prague::Trace("DirectFBDrawable::set_color");
}

inline void DirectFBDrawable::draw_pixel(Warsaw::PixelCoord x,
					 Warsaw::PixelCoord y) {
    Prague::Trace("DirectFBDrawable::draw_pixel");
}

inline void DirectFBDrawable::draw_hline(Warsaw::PixelCoord x,
					 Warsaw::PixelCoord y,
					 Warsaw::PixelCoord w) {
    Prague::Trace("DirectFBDrawable::draw_hline");
}

inline void DirectFBDrawable::draw_vline(Warsaw::PixelCoord x,
					 Warsaw::PixelCoord y,
					 Warsaw::PixelCoord h) {
    Prague::Trace("DirectFBDrawable::draw_vline");
}

inline void DirectFBDrawable::draw_line(Warsaw::PixelCoord x,
					Warsaw::PixelCoord y,
					Warsaw::PixelCoord w,
					Warsaw::PixelCoord h) {
    Prague::Trace("DirectFBDrawable::draw_line");
}

inline void DirectFBDrawable::draw_box(Warsaw::PixelCoord x,
				       Warsaw::PixelCoord y,
				       Warsaw::PixelCoord w,
				       Warsaw::PixelCoord h) {
    Prague::Trace("DirectFBDrawable::draw_box");
}

inline void DirectFBDrawable::put_pixel(Warsaw::PixelCoord x,
					Warsaw::PixelCoord y,
					Pixel c) {
    Prague::Trace("DirectFBDrawable::put_pixel");
}

inline void DirectFBDrawable::put_hline(Warsaw::PixelCoord,
					Warsaw::PixelCoord,
					Warsaw::PixelCoord,
					void *) {
  Prague::Trace("DirectFBDrawable::put_hline");
}

inline void DirectFBDrawable::put_vline(Warsaw::PixelCoord,
					Warsaw::PixelCoord,
					Warsaw::PixelCoord,
					void *) {
  Prague::Trace("DirectFBDrawable::put_vline");
}

inline void DirectFBDrawable::draw_pixels(Warsaw::PixelCoord x,
					  Warsaw::PixelCoord y,
					  Warsaw::PixelCoord w,
					  Warsaw::PixelCoord h,
					  void * ptr)
{
    Prague::Trace("DirectFBDrawable::draw_pixels");
}

inline void DirectFBDrawable::blit(Warsaw::PixelCoord x1,
				   Warsaw::PixelCoord y1, 
				   Warsaw::PixelCoord w,
				   Warsaw::PixelCoord h, 
				   Warsaw::PixelCoord x2,
				   Warsaw::PixelCoord y2)
{
    Prague::Trace("DirectFBDrawable::blit local");
}
    
inline void DirectFBDrawable::blit(const DirectFBDrawable &src,
				   Warsaw::PixelCoord x1,
				   Warsaw::PixelCoord y1, 
				   Warsaw::PixelCoord w,
				   Warsaw::PixelCoord h,
				   Warsaw::PixelCoord x2,
				   Warsaw::PixelCoord y2) {
    Prague::Trace("DirectFBDrawable::blit from");
}
    
inline void DirectFBDrawable::blit(Warsaw::Drawable_ptr d, 
				   Warsaw::PixelCoord x1,
				   Warsaw::PixelCoord y1, 
				   Warsaw::PixelCoord w,
				   Warsaw::PixelCoord h, 
				   Warsaw::PixelCoord x2,
				   Warsaw::PixelCoord y2) {
    Prague::Trace("DirectFBDrawable::blit to");
}

inline void DirectFBDrawable::flush() {
    Prague::Trace("DirectFBDrawable::flush");
}

inline void DirectFBDrawable::flush(Warsaw::PixelCoord x,
				    Warsaw::PixelCoord y,
				    Warsaw::PixelCoord w,
				    Warsaw::PixelCoord h) {
    Prague::Trace("DirectFBDrawable::flush area");
}


#endif
