/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1998 Graydon Hoare <graydon@fresco.org> 
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
#ifndef _Fresco_ClientContextImpl_hh
#define _Fresco_ClientContextImpl_hh

#include <Prague/Sys/User.hh>
#include <Babylon/Babylon.hh>
#include <Fresco/config.hh>
#include <Fresco/ClientContext.hh>
#include <Fresco/Command.hh>

//. This is a handle to a client application that the display server holds. It
//. provides the display server with enough mechanisms to check to see if the
//. client is alive and to determine the client's security rights. It is
//. instantiated within the client address space.
class ClientContextImpl : public virtual POA_Fresco::ClientContext
{
public:
  ClientContextImpl(const char *);

  Fresco::Unistring *user_name();
  Fresco::Unistring *application_title();
  Fresco::Command_ptr exit();
  void ping() {}
protected:
  Babylon::String _title;
  Prague::User   *_user;
};

#endif
