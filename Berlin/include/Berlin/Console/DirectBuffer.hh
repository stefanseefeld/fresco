/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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

#ifndef _DirectBuffer_hh
#define _DirectBuffer_hh

#include <Berlin/config.hh>
#include <Berlin/Console.hh>

class DirectBuffer : virtual public Console::Extension
{
public:
  typedef Console::Drawable::data_type data_type;

  class Guard
  {
  public:
    Guard(const Console::Drawable *drawable, data_type *data)
      : _drawable(drawable), _data(data) {}
    ~Guard() {}
    Guard(const Guard &buffer)
    {
      _data = buffer.release();
      _drawable = buffer._drawable;
    }
    Guard &operator = (const Guard &buffer)
    {
      _data = buffer.release();
      _drawable = buffer._drawable;
      return *this;
    }
    data_type *get() const { return _data;}
    data_type *release() const
    {
      data_type *tmp = _data;
      _data = 0;
      return tmp;
    }
  private:
    const Console::Drawable *_drawable;
    mutable data_type       *_data;
  };

  //. Get the read buffer for this Drawable
  virtual Guard read_buffer() = 0;
  //. Get the write buffer for this Drawable
  virtual Guard write_buffer() = 0;
};

#endif
