/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@fresco.org> 
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

#include <Prague/Sys/Memory.hh>
#include "Raster.hh"

/*
 * this file contains modified code from Mesa's GLU (mipmap.c)
 * -stefan
 */

using namespace Prague;
using namespace Fresco;
using namespace Berlin::Console_Extension;
using namespace Berlin::DrawingKit;

template <class T>
T ceiling(T a, T b) { return a % b == 0 ? a/b : a/b + 1; }

inline bool scale_image(GLenum format,
            size_t widthin, size_t heightin, 
            const unsigned char *datain,
            size_t widthout, size_t heightout,
            unsigned char *dataout)
{
    unsigned short components;
    /* Determine number of components per pixel */
    switch (format)
    {
    case GL_COLOR_INDEX:
    case GL_STENCIL_INDEX:
    case GL_DEPTH_COMPONENT:
    case GL_RED:
    case GL_GREEN:
    case GL_BLUE:
    case GL_ALPHA:
    case GL_LUMINANCE:
    components = 1;
    break;
    case GL_LUMINANCE_ALPHA:
    components = 2;
    break;
    case GL_RGB:
    components = 3;
    break;
    case GL_RGBA:
#ifdef GL_EXT_abgr
    case GL_ABGR_EXT:
#endif
    components = 4;
    break;
    default:
    return false;
    }

    /* Get glPixelStore state */
    GLint unpackrowlength, unpackalignment, unpackskiprows,
    unpackskippixels;
    GLint packrowlength, packalignment, packskiprows, packskippixels;
    GLint rowstride, rowlen;
    glGetIntegerv(GL_UNPACK_ROW_LENGTH, &unpackrowlength);
    glGetIntegerv(GL_UNPACK_ALIGNMENT, &unpackalignment);
    glGetIntegerv(GL_UNPACK_SKIP_ROWS, &unpackskiprows);
    glGetIntegerv(GL_UNPACK_SKIP_PIXELS, &unpackskippixels);
    glGetIntegerv(GL_PACK_ROW_LENGTH, &packrowlength);
    glGetIntegerv(GL_PACK_ALIGNMENT, &packalignment);
    glGetIntegerv(GL_PACK_SKIP_ROWS, &packskiprows);
    glGetIntegerv(GL_PACK_SKIP_PIXELS, &packskippixels);

    /* Allocate storage for intermediate images */
    GLfloat *tempin = new GLfloat [widthin * heightin * components];
    if (!tempin) return false;
    GLfloat *tempout = new GLfloat [widthout * heightout * components];
    if (!tempout)
    {
    delete [] tempin;
    return false;
    }

    /*
     * Unpack the pixel data and convert to floating point
     */
    if (unpackrowlength > 0) rowlen = unpackrowlength;
    else rowlen = widthin;
    if (unpackalignment <= 8) rowstride = components * rowlen;
    else
    rowstride = unpackalignment / 8 *
        ceiling(components * rowlen * 8, unpackalignment);
    size_t k = 0;
    for (size_t i = 0; i < heightin; i++)
    {
    const unsigned char *ubptr = datain + i * rowstride +
        unpackskiprows * rowstride + unpackskippixels * components;
    for (size_t j = 0;j < widthin*components; j++)
        tempin[k++] = static_cast<GLfloat>(*ubptr++);
    }

    /*
     * Scale the image!
     */
    GLfloat sx, sy;
    if (widthout > 1) sx = static_cast<GLfloat>(widthin-1) / (widthout-1);
    else sx = static_cast<GLfloat>(widthin-1);
    if (heightout > 1)
    sy = static_cast<GLfloat>(heightin-1) / (heightout-1);
    else sy = static_cast<GLfloat>(heightin-1);

    if (sx < 1. && sy < 1.)
     {
     // magnify both width and height: use weighted sample of 4 pixels
     for (size_t i = 0; i < heightout; i++)
         {
         size_t i0 = static_cast<size_t>(i * sy);
         size_t i1 = static_cast<size_t>(i0 + 1);
         if (i1 >= heightin) i1 = heightin - 1;
             // i1 = (i+1) * sy - EPSILON;
         GLfloat alpha = i*sy - i0;
         for (size_t j = 0; j < widthout; j++)
             {
         size_t j0 = static_cast<size_t>(j * sx);
         size_t j1 = static_cast<size_t>(j0 + 1);
         if (j1 >= widthin) j1 = widthin-1;
         // j1 = (j+1) * sx - EPSILON;
         GLfloat beta = j*sx - j0;
         
         // compute weighted average of pixels in rect
         // (i0,j0)-(i1,j1)
         GLfloat *src00 = tempin +
             (i0 * widthin + j0) * components;
         GLfloat *src01 = tempin +
             (i0 * widthin + j1) * components;
         GLfloat *src10 = tempin +
             (i1 * widthin + j0) * components;
         GLfloat *src11 = tempin +
             (i1 * widthin + j1) * components;

         GLfloat *dst = tempout + (i * widthout + j) * components;

         for (size_t k = 0; k < components; k++)
                 {
             GLfloat s1 = *src00++ * (1.0-beta) + *src01++ * beta;
             GLfloat s2 = *src10++ * (1.0-beta) + *src11++ * beta;
             *dst++ = s1 * (1.0-alpha) + s2 * alpha;
                 }
             }
         }
     }
    else
     {
     // shrink width and/or height:  use an unweighted box filter
     for (size_t i = 0; i < heightout; i++)
         {
         size_t i0 = static_cast<size_t>(i * sy);
         size_t i1 = static_cast<size_t>(i0 + 1);
         if (i1 >= heightin) i1 = heightin-1; 
         //    i1 = (i+1) * sy - EPSILON;
         for (size_t j = 0; j < widthout; j++)
             {
         size_t j0 = static_cast<size_t>(j * sx);
         size_t j1 = static_cast<size_t>(j0 + 1);
         if (j1 >= widthin) j1 = widthin-1;
         // j1 = (j+1) * sx - EPSILON;
         GLfloat *dst = tempout + (i * widthout + j) * components;
         // compute average of pixels in the rectangle
         // (i0,j0)-(i1,j1)
         for (size_t k = 0; k < components; k++)
                 {
             GLfloat sum = 0.0;
             for (size_t ii = i0; ii <= i1; ii++)
             for (size_t jj = j0; jj<= j1; jj++)
                 sum += *(tempin + (ii * widthin + jj) *
                      components + k);
             sum /= (j1-j0+1) * (i1-i0+1);
             *dst++ = sum;
                 }
             }
         }
     }
   
    /*
     * Return output image
     */

    if (packrowlength > 0) rowlen = packrowlength;
    else rowlen = widthout;
    if (packalignment <= 8) rowstride = components * rowlen;
    else
    rowstride = packalignment / 8 * 
        ceiling(components * rowlen * 8, packalignment);
   
    k = 0;
    for (size_t i = 0; i < heightout; i++)
    {
    unsigned char *ubptr =
        dataout + i * rowstride + packskiprows * rowstride +
        packskippixels * components;
    for (size_t j = 0; j < widthout * components; j++)
        *ubptr++ = static_cast<unsigned char>(tempout[k++]);
    }
    // free temporary image storage
    delete [] tempin;
    delete [] tempout;
    return true;
}



/*
 * openGL requires glTexImage2D to take width and height in the form 2^k
 * se we extract the exponent here and the residue
 */
inline void logbase2(unsigned int n, GLint &v)
{
    unsigned int k;
    for (k = 0; n >>= 1; k++);
    v = 1 << (k + 1);
}

/*
 * Given an pixel format and datatype, return the number of bytes to
 * store one pixel.
 */
static GLint bytes_per_pixel(GLenum format)
{
    switch (format)
    {
    case GL_COLOR_INDEX:
    case GL_STENCIL_INDEX:
    case GL_DEPTH_COMPONENT:
    case GL_RED:
    case GL_GREEN:
    case GL_BLUE:
    case GL_ALPHA:
    case GL_LUMINANCE:
    return 1;
    case GL_LUMINANCE_ALPHA:
    return 2;
    case GL_RGB:
    return 3;
    case GL_RGBA:
#ifdef GL_EXT_abgr
    case GL_ABGR_EXT:
#endif
      return 4;
    default: return 0;
    }
}

inline void resize_image(GLenum format,
             size_t widthin, size_t heightin,
             const unsigned char *datain,
             size_t widthout, size_t heightout,
             unsigned char *dataout)
{
    GLint bpp = bytes_per_pixel(format);
    Memory::zero(dataout, widthout * heightout * bpp);
    for (size_t h = 0;
     h != heightin;
     h++, datain += widthin * bpp, dataout += widthout * bpp)
    Memory::copy(datain, dataout, widthin * bpp);
}

class openGL::Texture::Activate : public virtual GLContext::Callback
{
  public:
    Activate::Activate(GLuint *tx, Fresco::PixelCoord *width,
               Fresco::PixelCoord *height) :
    my_tx(tx),
    my_width(width),
    my_height(height)
    { }
    void operator()()
    {
    Berlin::Console::Drawable *drawable =
        Berlin::Console::instance()->drawable();

    glBindTexture(GL_TEXTURE_2D, *my_tx);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    GLfloat sPlane[4] = {drawable->resolution(Fresco::xaxis) /
                 (*my_width), 0.0, 0.0, 0.0 };
    GLfloat tPlane[4] = { 0.0, -drawable->resolution(Fresco::yaxis) /
                  (*my_height), 0.0, 0.0 };
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGenfv(GL_S, GL_OBJECT_PLANE, sPlane);
    glTexGenfv(GL_T, GL_OBJECT_PLANE, tPlane);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  }
  private:
    GLuint *my_tx;
    Fresco::PixelCoord *my_width, *my_height;
};

class openGL::Texture::Bind : public virtual GLContext::Callback 
{
  public:
    Bind::Bind(GLint c, GLenum f, unsigned char *d, Texture *t) :
    my_components(c), 
    my_format(f),
    my_data(d),
    my_that(t)
    { }
    void operator()()
    {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    GLint w, h;
    unsigned char *image, *newimage;
    GLint neww, newh, level, bpp;
    int error;
    GLint unpackrowlength, unpackalignment,
        unpackskiprows, unpackskippixels;
    GLint packrowlength, packalignment, packskiprows, packskippixels;
    
    GLint maxsize;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxsize);
    logbase2(my_that->width, w);
    if (w > maxsize) w = maxsize;
    logbase2(my_that->height, h);
    if (h > maxsize) h = maxsize;
    bpp = bytes_per_pixel(my_format);
    
    // Get current glPixelStore values
    glGetIntegerv(GL_UNPACK_ROW_LENGTH, &unpackrowlength);
    glGetIntegerv(GL_UNPACK_ALIGNMENT, &unpackalignment);
    glGetIntegerv(GL_UNPACK_SKIP_ROWS, &unpackskiprows);
    glGetIntegerv(GL_UNPACK_SKIP_PIXELS, &unpackskippixels);
    glGetIntegerv(GL_PACK_ROW_LENGTH, &packrowlength);
    glGetIntegerv(GL_PACK_ALIGNMENT, &packalignment);
    glGetIntegerv(GL_PACK_SKIP_ROWS, &packskiprows);
    glGetIntegerv(GL_PACK_SKIP_PIXELS, &packskippixels);
    
    // set pixel packing
    glPixelStorei(GL_PACK_ROW_LENGTH, 0);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_SKIP_ROWS, 0);
    glPixelStorei(GL_PACK_SKIP_PIXELS, 0);
    
    bool done = false;
    
    if (w != my_that->width || h != my_that->height)
    {
        image = new unsigned char [(w+4) * h * bpp];
        scale_image(my_format, my_that->width, my_that->height,
            my_data, w, h, image);
    }
    else image = my_data;
    
    level = 0;
    while (!done)
    {
        if (image != my_data)
        {
        // set pixel unpacking
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
        glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
        }
        glTexImage2D(GL_TEXTURE_2D, level, my_components, w, h, 0,
             my_format, GL_UNSIGNED_BYTE, image);
        my_that->texgen_w = w;
        my_that->texgen_h = h;
        if (w==1 && h==1)  break;
        
        neww = (w < 2) ? 1 : w / 2;
        newh = (h < 2) ? 1 : h / 2;
        newimage = new unsigned char [(neww + 4) * newh * bpp];
        error = scale_image(my_format, w, h, 
                image, neww, newh, newimage);
        if (error) done = true;
        if (image != my_data) delete [] image;
        image = newimage;
        w = neww;
        h = newh;
        level++;
    }
    if (image != my_data) delete [] image;
    
    // Restore original glPixelStore state
    glPixelStorei(GL_UNPACK_ROW_LENGTH, unpackrowlength);
    glPixelStorei(GL_UNPACK_ALIGNMENT, unpackalignment);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, unpackskiprows);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, unpackskippixels);
    glPixelStorei(GL_PACK_ROW_LENGTH, packrowlength);
    glPixelStorei(GL_PACK_ALIGNMENT, packalignment);
    glPixelStorei(GL_PACK_SKIP_ROWS, packskiprows);
    glPixelStorei(GL_PACK_SKIP_PIXELS, packskippixels);
    my_that->texture = texture;
    }
  private:
    GLint my_components;
    GLenum my_format;
    unsigned char *my_data;
    Texture *my_that;
};

class openGL::Texture::Delete : public virtual GLContext::Callback
{
  public:
    Delete::Delete(GLuint *tx) : my_tx(tx) { }
    void operator()() { glDeleteTextures(1, my_tx); }
  private:
    GLuint *my_tx;
};

openGL::Texture::Texture(Fresco::Raster_var r) :
    remote(Fresco::Raster::_duplicate(r)),
    texture(0),
    my_is_bound(false)
{
    Fresco::Raster::Info info = remote->header();
    Fresco::Raster::ColorSeq_var pixels;
    Fresco::Raster::Index lower, upper;
    lower.x = lower.y = 0;
    upper.x = info.width, upper.y = info.height;
    remote->store_pixels(lower, upper, pixels);
    width = info.width;
    height = info.height;
    my_data.resize(4*width*height);
    std::vector<unsigned char>::iterator pixel = my_data.begin();
    for (int y = height - 1; y >= 0; y--)
    for (int x = 0; x != width; x++)
    {
        Color &color = pixels[y * info.width + x];
        *pixel++ = static_cast<char>(color.red * 255);
        *pixel++ = static_cast<char>(color.green * 255);
        *pixel++ = static_cast<char>(color.blue * 255);
        *pixel++ = static_cast<char>(color.alpha * 255);
    }
}

openGL::Texture::~Texture()
{ if (my_is_bound) my_glcontext->add_to_queue(new Delete(&texture)); }

void openGL::Texture::activate(GLContext *glcontext)
{
    if (!my_is_bound)
    {
    glcontext->add_to_queue(new Bind(GL_RGBA, GL_RGBA,
                     &my_data[0], this));
    my_glcontext = glcontext;
    my_is_bound = true;
    }
    // assert(glcontext == my_glcontext);
    glcontext->add_to_queue(new Activate(&texture,
                     &texgen_w, &texgen_h));
}

class openGL::Image::Activate : public virtual GLContext::Callback
{
  public:
    Activate::Activate(GLuint *tx,
               Fresco::PixelCoord *width,
               Fresco::PixelCoord *height, Fresco::PixelCoord *h2) :
    my_tx(tx),
    my_width(width),
    my_height(height),
    my_lesser_height(h2)
    { }
    void operator()()
    {
    Berlin::Console::Drawable *drawable =
        Berlin::Console::instance()->drawable();

    glBindTexture(GL_TEXTURE_2D, *my_tx);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    // GLfloat sPlane[4] = { drawable->resolution(Fresco::xaxis)/
    //                       (*my_width), 0.0, 0.0, 0.0 };
    // GLfloat tPlane[4] = { 0.0,
    //                       -drawable->resolution(Fresco::yaxis)/
    //                       (*my_height),
    //                       0.0,
    //                       (float)(*my_lesser_height)/
    //                       (float)(*my_height) };
    GLfloat sPlane[4] = { 0.1/(*my_width), 0.0, 0.0, 0.0 };
    GLfloat tPlane[4] = { 0.0,
                  -0.1/(*my_height),
                  0.0,
                  (float)(*my_lesser_height)/
                  (float)(*my_height) };
    glTexGenfv(GL_S, GL_OBJECT_PLANE, sPlane);
    glTexGenfv(GL_T, GL_OBJECT_PLANE, tPlane);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }
  private:
    GLuint *my_tx;
    Fresco::PixelCoord *my_width, *my_height;
    Fresco::PixelCoord *my_lesser_height;
};

class openGL::Image::Bind : public virtual GLContext::Callback 
{
  public:
    Bind::Bind(GLint c, GLenum f, unsigned char *d, Image *i) :
    my_components(c),
    my_format(f),
    my_data(d),
    my_that(i)
    { }
    void operator()()
    {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    GLint w, h;
    unsigned char *image, *newimage;
    GLint neww, newh, level, bpp;
    int error;
    GLint unpackrowlength, unpackalignment,
        unpackskiprows, unpackskippixels;
    GLint packrowlength, packalignment, packskiprows, packskippixels;
    
    GLint maxsize;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxsize);
    logbase2(my_that->width, w);
    if (w > maxsize) w = maxsize;
    logbase2(my_that->height, h);
    if (h > maxsize) h = maxsize;
    bpp = bytes_per_pixel(my_format);
    
    // Get current glPixelStore values
    glGetIntegerv(GL_UNPACK_ROW_LENGTH, &unpackrowlength);
    glGetIntegerv(GL_UNPACK_ALIGNMENT, &unpackalignment);
    glGetIntegerv(GL_UNPACK_SKIP_ROWS, &unpackskiprows);
    glGetIntegerv(GL_UNPACK_SKIP_PIXELS, &unpackskippixels);
    glGetIntegerv(GL_PACK_ROW_LENGTH, &packrowlength);
    glGetIntegerv(GL_PACK_ALIGNMENT, &packalignment);
    glGetIntegerv(GL_PACK_SKIP_ROWS, &packskiprows);
    glGetIntegerv(GL_PACK_SKIP_PIXELS, &packskippixels);
    
    // set pixel packing
    glPixelStorei(GL_PACK_ROW_LENGTH, 0);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_SKIP_ROWS, 0);
    glPixelStorei(GL_PACK_SKIP_PIXELS, 0);
    
    bool done = false;
    
    if (w != my_that->width || h != my_that->height)
    {
        // just copy the raster into a larger image, adapting the
        // texture coordinates
        image = new unsigned char [(w+4) * h * bpp];
        resize_image(my_format,
             my_that->width, my_that->height,
             my_data, w, h, image);
        my_that->s = static_cast<GLfloat>(my_that->width)/w;
        my_that->t = static_cast<GLfloat>(my_that->height)/h;
    }
    else image = my_data;
    
    level = 0;
    while (!done)
    {
        if (image != my_data)
        {
        /* set pixel unpacking */
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
        glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
        }
        glTexImage2D(GL_TEXTURE_2D, level, my_components, w, h, 0, 
             my_format, GL_UNSIGNED_BYTE, image);
        my_that->texgen_w = w;
        my_that->texgen_h = h;
        if (w==1 && h==1)  break;

        neww = (w < 2) ? 1 : w / 2;
        newh = (h < 2) ? 1 : h / 2;
        newimage = new unsigned char [(neww + 4) * newh * bpp];
        error = scale_image(my_format, w, h, image,
                neww, newh, newimage);
        if (error) done = true;
        if (image != my_data) delete [] image;
        image = newimage;
        w = neww;
        h = newh;
        level++;
    }
    if (image != my_data) delete [] image;
    
    /* Restore original glPixelStore state */
    glPixelStorei(GL_UNPACK_ROW_LENGTH, unpackrowlength);
    glPixelStorei(GL_UNPACK_ALIGNMENT, unpackalignment);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, unpackskiprows);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, unpackskippixels);
    glPixelStorei(GL_PACK_ROW_LENGTH, packrowlength);
    glPixelStorei(GL_PACK_ALIGNMENT, packalignment);
    glPixelStorei(GL_PACK_SKIP_ROWS, packskiprows);
    glPixelStorei(GL_PACK_SKIP_PIXELS, packskippixels);
    my_that->texture = texture;
    }
  private:
    GLint my_components;
    GLenum my_format;
    unsigned char *my_data;
    Image *my_that;
};

class openGL::Image::Delete : public virtual GLContext::Callback
{
  public:
    Delete::Delete(GLuint *tx) : my_tx(tx) { }
    void operator()() {    glDeleteTextures(1, my_tx); }
  private:
    GLuint *my_tx;
};

openGL::Image::Image(Fresco::Raster_var r) :
    remote(Fresco::Raster::_duplicate(r)),
    texture(0),
    my_is_bound(false)
{
    Fresco::Raster::Info info = remote->header();
    Fresco::Raster::ColorSeq_var pixels;
    Fresco::Raster::Index lower, upper;
    lower.x = lower.y = 0;
    upper.x = info.width, upper.y = info.height;
    remote->store_pixels(lower, upper, pixels);
    width = info.width;
    height = info.height;
    my_data.resize(4*width*height);
    std::vector<unsigned char>::iterator pixel = my_data.begin();
    for (int y = height - 1; y >= 0; y--)
    for (int x = 0; x != width; x++)
    {
        Color &color = pixels[y * info.width + x];
        *pixel++ = static_cast<char>(color.red * 255);
        *pixel++ = static_cast<char>(color.green * 255);
        *pixel++ = static_cast<char>(color.blue * 255);
        *pixel++ = static_cast<char>(color.alpha * 255);
    }
}

openGL::Image::~Image()
{ if (my_is_bound) my_glcontext->add_to_queue(new Delete(&texture)); }

void openGL::Image::activate(GLContext *glcontext)
{
    if (!my_is_bound)
    {
    glcontext->add_to_queue(new Bind(GL_RGBA, GL_RGBA, &my_data[0],
                     this));
    my_glcontext = glcontext;
    my_is_bound = true;
    }
    // assert(glcontext == my_glcontext);
    my_glcontext->add_to_queue(new Activate(&texture,
                        &texgen_w, &texgen_h,
                        &height));
}
