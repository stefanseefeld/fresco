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
#ifndef _Prague_Plugin_hh
#define _Prague_Plugin_hh

#include <Prague/Sys/DLL.hh>

namespace Prague
{

  //. a special kind of a smart pointer which implements a plugin behavior.
  //. It assumes a special layout of the library, with a special factory
  //. that manufactures objects of type T.
  template <class T>
  class Plugin : public DLL
  {
    public:
      //. create a Plugin from the given file, using a factory with name loader
      //. to create the actual object
      Plugin(const std::string &file, const std::string &loader = "load")
        throw(std::runtime_error, std::logic_error) :
        DLL(file)
      {
          typedef T *(* DL) ();
          DL dl = (DL) resolve(loader);
          _t = dl ? (T *) dl() : 0;
      }
      ~Plugin() { delete _t; }
      T &operator *() const { return *_t; }
      T *operator->() const { return  _t; }
      T *get() const { return _t; }
    private:
      T *_t;
  };

} // namespace

#define dload(T) extern "C" T *load() { return new T;}

#endif
