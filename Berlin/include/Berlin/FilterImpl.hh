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
#ifndef _Berlin_FilterImpl_hh
#define _Berlin_FilterImpl_hh

#include <Fresco/config.hh>
#include <Fresco/Input.hh>
#include <Fresco/Command.hh>

namespace Berlin
{

  class Accelerator : public virtual POA_Fresco::Input::Filter,
              public virtual PortableServer::RefCountServantBase
  {
    public:
      Accelerator(Fresco::Input::Device, const Fresco::Input::Toggle &,
          Fresco::Input::Bitset, Fresco::Command_ptr);
      virtual ~Accelerator() { }
      virtual CORBA::Boolean handle(const Fresco::Input::Event &);
    private:
      const Fresco::Input::Device my_device;
      const Fresco::Input::Toggle my_toggle;
      const Fresco::Input::Bitset my_modifier;
      const Fresco::Command_var my_command;
  };

} // namespace

#endif 
