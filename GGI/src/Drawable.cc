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
#include <Prague/Sys/Memory.hh>
#include <Prague/Sys/Tracer.hh>
#include <Berlin/Logger.hh>
#include "Drawable.hh"

using namespace Prague;
using namespace Fresco;

GGI::Drawable::Drawable(const char *display,
            PixelCoord w, PixelCoord h, PixelCoord d) :
    // throw (exception)
    my_name(display ? display : "")
{
    if (display) my_visual = ggiOpen(display, 0);
    else my_visual = ggiOpen(0);
    if (!my_visual) throw std::exception();

    long depth = GGI_AUTO;
    switch (d)
    {
    case 0:
    depth = GGI_AUTO;
    break;
    case 1:
    depth = GT_8BIT;
    break;
    case 2:
    depth = GT_16BIT;
    break;
    case 3:
    depth = GT_24BIT;
    break;
    case 4:
    depth = GT_32BIT;
    break;
    default:
    std::cerr << "GGIDrawable: Warning: " << d
          << " bytes per pixel not supported" << std::endl;
    break;
    };
    my_mode.visible.x = my_mode.virt.x = w ? w : GGI_AUTO;
    my_mode.visible.y = my_mode.virt.y = h ? h : GGI_AUTO;
    my_mode.size.x = GGI_AUTO;
    my_mode.size.y = GGI_AUTO;
    my_mode.dpp.x = my_mode.dpp.y = 1;
    my_mode.graphtype = depth;
    my_mode.frames = 1;
    if (ggiCheckMode(my_visual, &my_mode) == 0)
    { if (ggiSetMode(my_visual, &my_mode) != 0) throw std::exception(); }
    else
    if (ggiCheckMode(my_visual, &my_mode) != 0 ||
        ggiSetMode(my_visual, &my_mode) != 0) throw std::exception();
    my_mode.size = my_mode.visible; // awful hack around a ggi bug...
    ggiAddFlags(my_visual, GGIFLAG_ASYNC);

    if (ggiDBGetNumBuffers(my_visual)==0)
    {
    std::cerr << "ERROR: GGI Console requires direct-buffer support"
          << std::endl;
    throw std::exception();
    }
}

GGI::Drawable::~Drawable()
{ ggiClose(my_visual); }

Fresco::Drawable::PixelFormat GGI::Drawable::pixel_format()
{
    Fresco::Drawable::PixelFormat format;
    const ggi_pixelformat *pf = ggiGetPixelFormat(my_visual);
    format.depth       = pf->depth;
    format.size        = pf->size;
    format.red_mask    = pf->red_mask;
    format.red_shift   = pf->red_shift;
    format.green_mask  = pf->green_mask;
    format.green_shift = pf->green_shift;
    format.blue_mask   = pf->blue_mask;
    format.blue_shift  = pf->blue_shift;
    format.alpha_mask  = pf->alpha_mask;
    format.alpha_shift = pf->alpha_shift;
    return format;
}

Fresco::Drawable::BufferFormat GGI::Drawable::buffer_format()
{
    Fresco::Drawable::BufferFormat format;
    format.skip_width = 0;
    format.width = width();
    format.skip_height = 0;
    format.height = height();
    format.row_length = row_length();
    return format;
}

Fresco::PixelCoord GGI::Drawable::width() const
{ return my_mode.visible.x; }
Fresco::PixelCoord GGI::Drawable::height() const
{ return my_mode.visible.y; }
Fresco::PixelCoord GGI::Drawable::vwidth() const
{ return my_mode.virt.x; }
Fresco::PixelCoord GGI::Drawable::vheight() const
{ return my_mode.virt.y; }

Fresco::Coord GGI::Drawable::resolution(Fresco::Axis a) const
{
  /*
   * mode.size is in mm
   * our base unit is 0.1 mm...
   */
    return a == Fresco::xaxis ?
    0.1 * my_mode.visible.x / my_mode.size.x :
    0.1 * my_mode.visible.y / my_mode.size.y;
}
Fresco::Coord GGI::Drawable::dpi(Fresco::Axis a) const
{ return resolution(a) * 254.0; }
Fresco::PixelCoord GGI::Drawable::row_length() const
{ return ggiDBGetBuffer(my_visual, 0)->buffer.plb.stride; }

void GGI::Drawable::flush() { ggiFlush(my_visual); }
void GGI::Drawable::flush(Fresco::PixelCoord x, Fresco::PixelCoord y,
              Fresco::PixelCoord w, Fresco::PixelCoord h)
{ ggiFlushRegion(my_visual, x, y, w, h); }

void GGI::Drawable::init() { }
void GGI::Drawable::finish() { }

ggi_pixel GGI::Drawable::map(const Fresco::Color &c) const
{
    ggi_color c2;
    // GGI _appears_ to use 16 bit color + alpha throughout. *sigh*
    static double scale = 0xffff;
    c2.r = static_cast<uint16>(c.red * scale);
    c2.g = static_cast<uint16>(c.green * scale);
    c2.b = static_cast<uint16>(c.blue * scale);
    c2.a = static_cast<uint16>(c.alpha * scale);
    return ggiMapColor(my_visual, &c2);
}

void GGI::Drawable::blit(Fresco::PixelCoord x1, Fresco::PixelCoord y1,
             Fresco::PixelCoord w, Fresco::PixelCoord h,
             Fresco::PixelCoord x2, Fresco::PixelCoord y2)
{ ggiCopyBox(my_visual, x1, y1, w, h, x2, y2); }
void GGI::Drawable::blit(const GGI::Drawable &d,
             Fresco::PixelCoord x1, Fresco::PixelCoord y1,
             Fresco::PixelCoord w, Fresco::PixelCoord h,
             Fresco::PixelCoord x2, Fresco::PixelCoord y2)
{ ggiCrossBlit(d.my_visual, x1, y1, w, h, my_visual, x2, y2); }
void GGI::Drawable::blit(const Berlin::Console::Drawable &d,
             Fresco::PixelCoord x1, Fresco::PixelCoord y1,
             Fresco::PixelCoord w, Fresco::PixelCoord h,
             Fresco::PixelCoord x2, Fresco::PixelCoord y2)
{
  const Drawable &drawable = dynamic_cast<const GGI::Drawable &>(d);
  ggiCrossBlit(drawable.my_visual, x1, y1, w, h, my_visual, x2, y2);
}
void GGI::Drawable::blit(Fresco::Drawable_ptr d,
             Fresco::PixelCoord x1, Fresco::PixelCoord y1,
             Fresco::PixelCoord w, Fresco::PixelCoord h,
             Fresco::PixelCoord x2, Fresco::PixelCoord y2)
{
    GGI::Drawable *servant =
    dynamic_cast<GGI::Drawable *>(Berlin::Console::instance()->
                      reference_to_servant(d));
    if (servant) blit(*servant, x1, y1, w, h, x2, y2);
    else
    Berlin::Logger::log(Berlin::Logger::drawing)
        << "GGI::Drawable::blit: unable to obtain servant from "
        << "reference." << std::endl;
}

