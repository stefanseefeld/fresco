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
#include <Command/CommandImpl.hh>

CommandKitImpl::CommandKitImpl(KitFactory *f, const PropertySeq &p) : KitImpl(f, p) {}
CommandKitImpl::~CommandKitImpl()
{
  for (vector<CommandImpl *>::iterator i = commands.begin(); i != commands.end(); i++) (*i)->_dispose();
}

Command_ptr CommandKitImpl::log(const char *text)
{
  LogCommand *command = new LogCommand(text);
  command->_obj_is_ready(_boa());
  commands.push_back(command);
  return command->_this();
}

MacroCommand_ptr CommandKitImpl::composite()
{
  MacroCommandImpl *command = new MacroCommandImpl();
  command->_obj_is_ready(_boa());
  commands.push_back(command);
  return command->_this();
}

extern "C" KitFactory *load()
{
  static string properties[] = {"implementation", "CommandKitImpl"};
  return new KitFactoryImpl<CommandKitImpl>(interface(CommandKit), properties, 1);
}
