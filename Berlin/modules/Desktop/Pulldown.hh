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
#ifndef _Pulldown_hh
#define _Pulldown_hh

#include "WindowImpl.hh"

namespace Berlin {
namespace DesktopKit {

class Pulldown : public WindowImpl
{
public:
  virtual CORBA::Boolean receive_focus(Fresco::Focus_ptr);
  virtual void lose_focus(Fresco::Input::Device);
  virtual void mapped(CORBA::Boolean);
};

} // namespace
} // namespace

#endif
