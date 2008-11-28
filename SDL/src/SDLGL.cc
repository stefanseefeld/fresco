/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 2000 Stefan Seefeld <stefan@fresco.org> 
 * Copyright (C) 2001 Philip Philonenko <philonenko@orgacom.ru> 
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
#include <Berlin/Logger.hh>
#include "SDLGL.hh"

// ---------------------------------------------------------------
// class SDL::GLExposeHandler (implementation)
// ---------------------------------------------------------------

class SDL::GLExposeHandler::Callback : public virtual GLContext::Callback {
  public:
    void operator()()
    {
    Berlin::Console::Drawable * drawable =
        dynamic_cast<SDL::Drawable *>(Berlin::Console::instance()->drawable());

    //glDisable(GL_ALPHA_TEST);
    glDisable(GL_BLEND);
    glDisable(GL_SCISSOR_TEST);
    
    glReadBuffer(GL_BACK);
    glDrawBuffer(GL_FRONT);
    glRasterPos2i(0, 0);

    glCopyPixels(0, 0, drawable->width(), drawable->height(),
             GL_COLOR);
    glFlush();

    //glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_SCISSOR_TEST);
    
    glDrawBuffer(GL_BACK);
    delete this;
    }
};

void SDL::GLExposeHandler::refresh_screen()
{
    Prague::Trace trace("SDL::GLExposeHandler::refresh_screen()");
    my_glcontext->add_to_queue(new Callback());
    my_glcontext->flush();
}

// ---------------------------------------------------------------
// Listener thread implementation.
// ---------------------------------------------------------------

void *listen(void *q)
{
    Prague::Thread::Queue<SDL::GLContext::Callback *> *my_queue =
    static_cast<Prague::Thread::Queue<SDL::GLContext::Callback *> *>(q);
    while(1)
    {
    SDL::GLContext::Callback *cb = my_queue->top();
    my_queue->pop();
    (*cb)();
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
        std::cerr << "GL ERROR: " << error << std::endl;
    }
}

// ---------------------------------------------------------------
// class SDL::GLContext (implementation)
// ---------------------------------------------------------------

class SDL::GLContext::Initialize : public virtual GLContext::Callback
{
    friend class SDL::GLContext;
  public:
    Initialize(Fresco::PixelCoord w, Fresco::PixelCoord h) :
    my_width(w), my_height(h), complete(false)
    { }
    void operator()()
    {
    Berlin::Console::Drawable * drawable =
        dynamic_cast<SDL::Drawable *>(Berlin::Console::instance()->drawable());

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    surface = SDL_SetVideoMode(my_width, my_height, 0, SDL_OPENGL);
    SDL_WM_SetCaption("Berlin on SDL (OpenGL)", NULL);

    int bits;
    glGetIntegerv(GL_DEPTH_BITS, &bits);
    switch (bits) 
    {
    case  0:
        depth = 0;
        break;
    case  8:
        depth = 1;
        break;
    case 16:
        depth = 2;
        break;
    case 24:
        depth = 3;
        break;
    case 32:
        depth = 4;
        break;
    default:
        depth = 0;
    }
    glDrawBuffer(GL_BACK);

    // FIXME: decouple SDLGL and GLDrawingKit.
    glViewport(0, 0, my_width, my_height);
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();
    glOrtho(0, my_width/drawable->resolution(Fresco::xaxis),
        my_height/drawable->resolution(Fresco::yaxis),
        0, -5000.0, 5000.0); 
    //glTranslatef(0.375, 0.375, 0.);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glShadeModel(GL_SMOOTH);
    //glFrontFace(GL_CW);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_DITHER);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_SCISSOR_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    complete = true;
    }
  private:
    bool complete;
    Fresco::PixelCoord my_width, my_height;
    SDL_Surface *surface;
    int depth;
};

void SDL::GLContext::add_to_queue(SDL::GLContext::Callback *cb)
{ my_queue->push(cb); }

SDL::GLContext::GLContext()
{
    Prague::Trace trace("SDL::GLContext::GLContext()");

    my_queue = new Prague::Thread::Queue<GLContext::Callback *>(2147000);

    my_gl_thread = new Prague::Thread(listen, my_queue);
    my_gl_thread->start();

    my_drawable =
    dynamic_cast<SDL::Drawable *>(Berlin::Console::instance()->drawable());

    Fresco::PixelCoord w(my_drawable->width());
    Fresco::PixelCoord h(my_drawable->height());
  
    Berlin::Logger::log(Berlin::Logger::loader)
    << "setting video mode GL " << " w=" << w << " h= " << h
    << std::endl;
  
    Initialize *init = new Initialize(w, h);
    // FIXME: instead, the listener thread should do this in its own
    // initialization.
    add_to_queue(init);
    while (!init->complete) { Prague::Thread::delay(Prague::Time(1000)); }

    // HACK: Replace the 'real' drawable with its OpenGL-replacement.
    my_drawable->my_surface = init->surface;
    my_drawable->my_depth = init->depth;
    my_drawable->my_width = w;
    my_drawable->my_height = h;

    // setup PointerManager:
    dynamic_cast<SDL::Console *>(Berlin::Console::instance())->
    set_PointerManager(new SDL::PointerManagerT<GLPointer>(this));

    // setup ExposeHandler:
    dynamic_cast<SDL::Console *>(Berlin::Console::instance())->
    set_ExposeHandler(new SDL::GLExposeHandler(this));

    delete init;
}


SDL::GLContext::~GLContext()
{ Prague::Trace trace("SDL::GLContext::~SDLGLContext()"); }


class SDL::GLContext::Flush : public virtual GLContext::Callback
{
    friend class GLContext;
  public:
    Flush(Fresco::PixelCoord width, Fresco::PixelCoord height) :
    my_width(width), my_height(height)
    { }
    void operator()()
    {
    SDL_GL_SwapBuffers();

    //glDisable(GL_ALPHA_TEST);
    glDisable(GL_BLEND);
    glDisable(GL_SCISSOR_TEST);

    glReadBuffer(GL_FRONT);
    glDrawBuffer(GL_BACK);
    glRasterPos2i(0, 0);

    glCopyPixels(0, 0, my_width, my_height, GL_COLOR);

    //glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_SCISSOR_TEST);
    delete this;
    }
  private:
    Fresco::PixelCoord my_width, my_height;
};

void SDL::GLContext::flush()
{
    Prague::Trace trace("SDL::GLContext::flush()");
    add_to_queue(new Flush(my_drawable->width(), my_drawable->height()));
}

// ---------------------------------------------------------------
// class SDL::GLPointer (implementation)
// ---------------------------------------------------------------

SDL::GLPointer::GLPointer(Drawable * drawable, Fresco::Raster_ptr raster,
                          GLContext *glcontext) :
    my_raster(Fresco::Raster::_duplicate(raster)),
    my_glcontext(glcontext)
{
    Prague::Trace trace("SDL::GLPointer::GLPointer(...)");

    // copy over the Raster:
    my_raster = Fresco::Raster::_duplicate(raster);

    // get screensizes:
    my_max_y_size = drawable->height();

    // Disable SDL default mousecursor
    SDL_ShowCursor(0);

    // Copy the raster over into the Drawable:
    Fresco::Raster::Info info = raster->header();
    Fresco::Raster::ColorSeq_var pixels;
    Fresco::Raster::Index lower, upper;
    lower.x = lower.y = 0;
    upper.x = info.width, upper.y = info.height;
    raster->store_pixels(lower, upper, pixels);
    my_origin[0] = my_origin[1] = 0;
    my_size[0] = info.width;
    my_size[1] = info.height;
    my_scale[0] = 1.0/drawable->resolution(Fresco::xaxis);
    my_scale[1] = 1.0/drawable->resolution(Fresco::yaxis);

    // RGBA
    my_cursor = std::vector<unsigned char>(my_size[0]*my_size[1] * 4);
    // RGB
    my_saved_area = std::vector<unsigned char>(my_size[0]*my_size[1] * 3);

    unsigned pos = 0;
    Fresco::Color c;

    for (unsigned short y = 0; y != my_size[1]; ++y)
    for (unsigned short x = 0; x != my_size[0]; ++x)
    {
        c = (*(pixels->get_buffer() + y * info.width + x));

        pos = (((my_size[1] - 1 - y) * my_size[0] + x) << 2);

        my_cursor[pos + 0] =
        static_cast<unsigned char>(c.red   * 0xFF);
        my_cursor[pos + 1] =
        static_cast<unsigned char>(c.green * 0xFF);
        my_cursor[pos + 2] =
        static_cast<unsigned char>(c.blue  * 0xFF);
        my_cursor[pos + 3] =
        static_cast<unsigned char>(c.alpha * 0xFF);
    }
    
    // set position
    my_position[0] = my_position[1] = 8;
}


SDL::GLPointer::~GLPointer()
{ restore(); }

class SDL::GLPointer::Save : public virtual GLContext::Callback
{
    friend class SDL::GLPointer;
  public:
    Save(Fresco::PixelCoord x, Fresco::PixelCoord y,
         Fresco::PixelCoord width, Fresco::PixelCoord height,
         Fresco::Coord xscale, Fresco::Coord yscale,
         std::vector<unsigned char> &buffer) :
    my_x(x), my_y(y),
    my_width(width), my_height(height),
    my_xscale(xscale), my_yscale(yscale),
    my_buffer(buffer)
    { }
    void operator()()
    {
    // FIXME: pixelstore, transfer and map could be corrupted.
    GLint buffer;
    glGetIntegerv(GL_READ_BUFFER, &buffer);
    glReadBuffer(GL_FRONT);
    //glReadPixels(my_x * my_xscale, my_y * my_yscale,
    //             my_width, my_height,
    glReadPixels(my_x, my_y, my_width, my_height,
             GL_RGB, GL_UNSIGNED_BYTE, &my_buffer[0]);
    glReadBuffer(buffer);
    delete this;
    }
  private:
    Fresco::PixelCoord my_x, my_y;
    Fresco::PixelCoord my_width, my_height;
    Fresco::Coord my_xscale, my_yscale;
    std::vector<unsigned char> &my_buffer;
};

void SDL::GLPointer::save()
{
    Prague::Trace trace("SDL::GLPointer::save()");

    Fresco::PixelCoord x = my_position[0] - my_origin[0];
    Fresco::PixelCoord y = my_max_y_size - my_position[1] -
    my_size[1] + my_origin[1];
    int offset = 0;
    if (y >= my_max_y_size)
    {
    offset = y - my_max_y_size + 1;
    y = my_max_y_size-1;
    }

    my_glcontext->add_to_queue(new Save(x, y,
                    my_size[0], my_size[1]-offset,
                    my_scale[0], my_scale[1],
                    my_saved_area));
}

class SDL::GLPointer::Restore : public virtual GLContext::Callback
{
    friend class SDL::GLPointer;
  public:
    Restore(Fresco::PixelCoord x, Fresco::PixelCoord y,
            Fresco::PixelCoord width, Fresco::PixelCoord height,
            Fresco::Coord xscale, Fresco::Coord yscale,
            unsigned char *buffer) :
    my_x(x), my_y(y),
    my_width(width), my_height(height),
    my_xscale(xscale), my_yscale(yscale),
    my_buffer(buffer)
    { }
    void operator()()
    {
    GLint buffer;
    glGetIntegerv(GL_DRAW_BUFFER, &buffer);
    glDisable(GL_BLEND);
    //glDisable(GL_ALPHA_TEST);
    glDisable(GL_SCISSOR_TEST);
    
    glDrawBuffer(GL_FRONT);
    glRasterPos2i((int)(my_x * my_xscale), (int)(my_y * my_yscale));
    //glRasterPos2i((int)(my_x * 10), (int)(my_y * 10));
    glDrawPixels(my_width, my_height, GL_RGB, GL_UNSIGNED_BYTE,
             my_buffer);
    glDrawBuffer(buffer);

    glEnable(GL_BLEND);
    //glEnable(GL_ALPHA_TEST);
    glEnable(GL_SCISSOR_TEST);
    delete this;
    }
  private:
    Fresco::PixelCoord my_x, my_y;
    Fresco::PixelCoord my_width, my_height;
    Fresco::Coord my_xscale, my_yscale;
    unsigned char *my_buffer;
};

void SDL::GLPointer::restore()
{
    Prague::Trace trace("SDL::GLPointer::restore()");

    Fresco::PixelCoord x = my_position[0] - my_origin[0];
    Fresco::PixelCoord y = my_position[1] + my_size[1] - my_origin[1];
    int offset = 0;
    if (y >= my_max_y_size)
    {
    offset = y - my_max_y_size;
    y = my_max_y_size;
    }
    my_glcontext->add_to_queue(new Restore(x, y,
                       my_size[0], my_size[1]-offset,
                       my_scale[0], my_scale[1],
                       &my_saved_area[offset*3*my_size[0]]));
}

class SDL::GLPointer::Draw : public virtual GLContext::Callback
{
    friend class SDL::GLPointer;
  public:
    Draw(Fresco::PixelCoord x, Fresco::PixelCoord y,
         Fresco::PixelCoord width, Fresco::PixelCoord height,
         Fresco::Coord xscale, Fresco::Coord yscale,
         unsigned char *cursor) :
    my_x(x), my_y(y),
    my_width(width), my_height(height),
    my_xscale(xscale), my_yscale(yscale),
    my_cursor(cursor)
    { }
    void operator()()
    {
    GLint buffer;
    glGetIntegerv(GL_DRAW_BUFFER, &buffer);
    glDisable(GL_SCISSOR_TEST);

    glDrawBuffer(GL_FRONT);
    glRasterPos2i((int)(my_x * my_xscale), (int)(my_y * my_yscale));
    //glWindowPos2iARB(my_x, my_y);
    glDrawPixels(my_width, my_height, GL_RGBA, GL_UNSIGNED_BYTE,
             my_cursor);
    glDrawBuffer(buffer);
    
    glEnable(GL_SCISSOR_TEST);
    glFlush();
    delete this;
    }
  private:
    Fresco::PixelCoord my_x, my_y;
    Fresco::PixelCoord my_width, my_height;
    Fresco::Coord my_xscale, my_yscale;
    unsigned char *my_cursor;
};

void SDL::GLPointer::draw()
{
    Prague::Trace trace("SDL::GLPointer::draw()");

    Fresco::PixelCoord x = my_position[0] - my_origin[0];
    Fresco::PixelCoord y = my_position[1] + my_size[1] - my_origin[1];
    int offset = 0;
    if (y >= my_max_y_size)
    {
    offset = y - my_max_y_size + 1;
    y = my_max_y_size-1;
    }

    my_glcontext->add_to_queue(new Draw(x, y,
                    my_size[0], my_size[1]-offset,
                    my_scale[0], my_scale[1],
                    &my_cursor[offset*my_size[0]*4]));
}

// ---------------------------------------------------------------
// externs
// ---------------------------------------------------------------

extern "C" Berlin::Console::Extension *load()
{ return new SDL::GLContext(); }
