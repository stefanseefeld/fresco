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

#ifndef _Berlin_Console_DirectBuffer_hh
#define _Berlin_Console_DirectBuffer_hh

#include <Berlin/config.hh>
#include <Berlin/Console.hh>

namespace Berlin
{
  namespace Console_Extension
  {

    class DirectBuffer : virtual public Console::Drawable::Extension
    {
      public:
    typedef Console::Drawable::data_type data_type;
    
    class Guard
    {
      public:
        Guard(const Console::Drawable *drawable, data_type *data) :
        my_drawable(drawable), my_data(data)
        { }
        
        ~Guard() { }
        
        Guard(const Guard &buffer)
        {
        my_data = buffer.release();
        my_drawable = buffer.my_drawable;
        }
        Guard &operator = (const Guard &buffer)
        {
        my_data = buffer.release();
        my_drawable = buffer.my_drawable;
        return *this;
        }

        data_type *get() const { return my_data; }
        
        data_type *release() const
        {
        data_type *tmp = my_data;
        my_data = 0;
        return tmp;
        }
      private:
        const Console::Drawable *my_drawable;
        mutable data_type       *my_data;
    };
    
    //. Get the read buffer for this Drawable
    virtual Guard read_buffer() = 0;
    //. Get the write buffer for this Drawable
    virtual Guard write_buffer() = 0;
    };

  } // namespace
} // namespace

#endif
