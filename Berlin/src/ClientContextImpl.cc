//
// $Id$
//
// This source file is a part of the Berlin Project.
// Copyright (C) 1998 Graydon Hoare <graydon@pobox.com> 
// http://www.berlin-consortium.org
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public License
// as published by the Free Software Foundation; either version 2 of
// the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
//

// this is the simple representation of a principal within the berlin security system.
// since we don't have any security experts onboard, right now this is a skeletal
// principal which has no checking done against it, but you could work in a pretty
// sophisticated security system just by hacking this, sessionManager, and session

#include "Berlin/ClientContextImpl.hh"
#include <iostream>

ClientContextImpl::ClientContextImpl() {
  MutexGuard guard(_ClientContext_mutex);
  _ClientUser = new Prague::User(-1);
};  
  
Unistring *ClientContextImpl::userName() {
  const char *_userName = _ClientUser->Name();
  const unsigned int length = strlen(_userName);
  Unistring * theString = new Unistring[length];

  for( unsigned int i = 0; i < length; i++) {
    theString[i] = _userName[i];
  }

  return theString;
}


CORBA::Boolean ClientContextImpl::stillAlive() {return (unsigned char)true;}
