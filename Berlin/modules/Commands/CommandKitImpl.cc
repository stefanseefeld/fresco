/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Graydon Hoare <graydon@pobox.com> 
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

#include <Command/CommandKitImpl.hh>
#include <Command/ReactorImpl.hh>

CommandKitImpl::CommandKitImpl() {}
CommandKitImpl::~CommandKitImpl() {}

Reactor_ptr CommandKitImpl::asyncReactor() {
  AsyncReactorImpl *r = new AsyncReactorImpl();
  r->active(true);
  r->_obj_is_ready(_boa());
  return r->_this();
}

Reactor_ptr CommandKitImpl::syncReactor() {
  ReactorImpl *r = new ReactorImpl();
  r->active(true);
  r->_obj_is_ready(_boa());
  return r->_this();
}

// Command_ptr CommandKitImpl::sendMessage(Message &m, MessageListener_ptr recipient) {
//   SendMessageImpl *c = new SendMessageImpl(m,recipient);
//   c->_obj_is_ready(_boa());
//   return c->_this();
// }

// Command_ptr CommandKitImpl::forwardMessage(MessageListener_ptr recipient) {
//   ForwardMessageImpl *c = new ForwardMessageImpl(m,recipient);
//   c->_obj_is_ready(_boa());
//   return c->_this();
// }

// Command_ptr CommandKitImpl::forwardByGeometry(MessageListener_ptr recipient, Graphic_ptr geom) {
//   ForwardByGeometryImpl *c = new ForwardByGeometryImpl(recipient, geom);
//   c->_obj_is_ready(_boa());
//   return c->_this();
// }
