/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Graydon Hoare <graydon@pobox.com> 
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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

#include <Warsaw/config.hh>
#include <Warsaw/Controller.hh>
#include <Berlin/ImplVar.hh>
#include <Berlin/CommandImpl.hh>
#include "Command/CommandKitImpl.hh"
#include "Command/TelltaleImpl.hh"
#include "Command/SelectionImpl.hh"
#include "Command/BoundedValueImpl.hh"
#include "Command/BoundedRangeImpl.hh"
#include "Command/TextBufferImpl.hh"
#include "Command/StreamBufferImpl.hh"
#include <string>
#include <vector>

using namespace Warsaw;

class MacroCommandImpl : public virtual POA_Warsaw::MacroCommand,
			 public CommandImpl
{
public:
  virtual ~MacroCommandImpl()
  {
    for (vector<Warsaw::Command_var>::iterator i = commands.begin(); i != commands.end(); ++i)
      (*i)->destroy();
  }
  virtual void append(Warsaw::Command_ptr c)
  {
    commands.push_back(Warsaw::Command::_duplicate(c));
  }
  virtual void prepend(Warsaw::Command_ptr c)
  {
    commands.insert(commands.begin(), Warsaw::Command::_duplicate(c));
  }
  virtual void execute(const CORBA::Any &any)
    {
      for (vector<Warsaw::Command_var>::iterator i = commands.begin(); i != commands.end(); ++i)
	(*i)->execute(any);
    }
 private:
  vector<Warsaw::Command_var> commands;
};

class LogCommand : public CommandImpl
{
public:
  LogCommand(ostream &oss, const char *t) : os(oss), text(t) {}
  virtual void execute(const CORBA::Any &) { os << text << endl;}
 private:
  ostream &os;
  string text;
};

CommandKitImpl::CommandKitImpl(KitFactory *f, const Warsaw::Kit::PropertySeq &p)
  : KitImpl(f, p) {}
CommandKitImpl::~CommandKitImpl() {}
Command_ptr CommandKitImpl::log(const char *text)
{
  LogCommand *command = new LogCommand(cout, text);
  activate(command);
  return command->_this();
}

MacroCommand_ptr CommandKitImpl::composite()
{
  MacroCommandImpl *command = new MacroCommandImpl();
  activate(command);
  return command->_this();
}

TelltaleConstraint_ptr CommandKitImpl::exclusive(Telltale::Mask m)
{
  ExclusiveChoice *constraint = new ExclusiveChoice(m);
  activate(constraint);
  return constraint->_this();
}

TelltaleConstraint_ptr CommandKitImpl::selectionRequired()
{
  SelectionRequired *constraint = new SelectionRequired();
  activate(constraint);
  return constraint->_this();
}

Telltale_ptr CommandKitImpl::normalTelltale()
{
  TelltaleImpl *telltale = new TelltaleImpl(TelltaleConstraint::_nil());
  activate(telltale);
  return telltale->_this();
}

Telltale_ptr CommandKitImpl::constrainedTelltale(TelltaleConstraint_ptr constraint)
{
    TelltaleImpl *telltale = new TelltaleImpl(constraint);
    activate(telltale);
    constraint->add(Telltale_var(telltale->_this()));
    return telltale->_this();
}

Selection_ptr CommandKitImpl::group(Selection::Policy policy)
{
  TelltaleConstraint_var constraint;
  if (policy == Warsaw::Selection::exclusive) constraint = exclusive(Warsaw::Controller::toggled);
  SelectionImpl *selection = new SelectionImpl(policy, constraint);
  activate(selection);
  return selection->_this();
}

BoundedValue_ptr CommandKitImpl::bvalue(Coord l, Coord u, Coord v, Coord s, Coord p)
{
  BoundedValueImpl *bounded = new BoundedValueImpl(l, u, v, s, p);
  activate(bounded);
  return bounded->_this();
}

BoundedRange_ptr CommandKitImpl::brange(Coord l, Coord u, Coord lv, Coord uv, Coord s, Coord p)
{
  BoundedRangeImpl *bounded = new BoundedRangeImpl(l, u, lv, uv, s, p);
  activate(bounded);
  return bounded->_this();
}

TextBuffer_ptr CommandKitImpl::text()
{
  TextBufferImpl *buffer = new TextBufferImpl();
  activate(buffer);
  return buffer->_this();  
}

StreamBuffer_ptr CommandKitImpl::stream(CORBA::Long b)
{
  StreamBufferImpl *buffer = new StreamBufferImpl(b);
  activate(buffer);
  return buffer->_this();  
}

extern "C" KitFactory *load()
{
  static string properties[] = {"implementation", "CommandKitImpl"};
  return new KitFactoryImpl<CommandKitImpl>("IDL:Warsaw/CommandKit:1.0", properties, 1);
}
