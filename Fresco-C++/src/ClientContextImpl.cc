/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1998 Graydon Hoare <graydon@pobox.com> 
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
#include "Warsaw/ClientContextImpl.hh"
#include "Warsaw/Unicode.hh"
#include <iostream>
#include <string>

using namespace Warsaw;

namespace
{
  class ExitCommand : public virtual POA_Warsaw::Command,
		      public virtual PortableServer::RefCountServantBase
  {
  public:
    virtual void execute(const CORBA::Any &) { exit(0);} // the point of no return...
    virtual void destroy()
    {
      PortableServer::POA_var poa = _default_POA();
      PortableServer::ObjectId *oid = poa->servant_to_id(this);
      poa->deactivate_object(*oid);
      delete oid;
    }
  };
};

ClientContextImpl::ClientContextImpl(const char *title)
  : _title(title),
    _user(new Prague::User())
{};  
  
Unistring *ClientContextImpl::user_name()
{
  std::string name = _user->name();
  Unistring *ustring = new Unistring;
  ustring->length(name.length());
  for(unsigned int i = 0; i < name.length(); i++) ustring[i] = name[i];
  return ustring;
}

Unistring *ClientContextImpl::application_title()
{
  Unistring *ustring = new Unistring;
  *ustring = Unicode::to_CORBA(Babylon::String(_title));
  return ustring;
}

Command_ptr ClientContextImpl::exit()
{
  ExitCommand *command = new ExitCommand();
  PortableServer::POA_var poa = _default_POA();
  PortableServer::ObjectId *oid = poa->activate_object(command);
  command->_remove_ref();
  delete oid;
  return command->_this();
}
