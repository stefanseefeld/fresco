/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Graydon Hoare <graydon@fresco.org> 
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@fresco.org> 
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

#include <Fresco/config.hh>
#include <Fresco/Controller.hh>
#include <Fresco/Server.hh>
#include <Fresco/DrawingKit.hh>
#include <Fresco/resolve.hh>
#include <Berlin/ImplVar.hh>
#include <Berlin/GraphicImpl.hh>
#include <Berlin/DrawTraversalImpl.hh>
#include <Berlin/CommandImpl.hh>
#include "CommandKitImpl.hh"
#include "TelltaleImpl.hh"
#include "SelectionImpl.hh"
#include "BoundedValueImpl.hh"
#include "BoundedRangeImpl.hh"
#include "TextBufferImpl.hh"
#include "StreamBufferImpl.hh"
#include <string>
#include <vector>

using namespace Fresco;

class DebugCommand : public CommandImpl
{
public:
  DebugCommand(Command_ptr c, std::ostream &os, const char *t) : _command(Fresco::Command::_duplicate(c)), _os(os), _text(t) {}
  virtual void execute(const CORBA::Any &any)
  {
    _os << _text << " : entering execute" << std::endl; 
    _command->execute(any);
    _os << _text << " : leaving execute" << std::endl;
  }
 private:
  Command_var   _command;
  std::ostream &_os;
  std::string   _text;
};

class LogCommand : public CommandImpl
{
public:
  LogCommand(std::ostream &os, const char *text) : _os(os), _text(text) {}
  virtual void execute(const CORBA::Any &) { _os << _text << std::endl;}
 private:
  std::ostream &_os;
  std::string   _text;
};

class PrintCommand : public CommandImpl
{
public:
  PrintCommand(Graphic_ptr graphic, ServerContext_ptr server)
    : _graphic(Graphic::_duplicate(graphic)),
      _server(ServerContext::_duplicate(server))
  {}
  virtual void execute(const CORBA::Any &)
  {
    Fresco::Kit::PropertySeq props;
    props.length(1);
    props[0].name = CORBA::string_dup("implementation");
    props[0].value = CORBA::string_dup("PSDrawingKit");
    RefCount_var<DrawingKit> print = resolve_kit<DrawingKit>(_server, "IDL:fresco.org/Fresco/DrawingKit:1.0", props);
    Fresco::Graphic::Requisition r;
    GraphicImpl::init_requisition(r);
    _graphic->request(r);
    Lease_var<RegionImpl> allocation(Provider<RegionImpl>::provide());
    allocation->valid = true;
    allocation->lower.x = allocation->lower.y = allocation->lower.z = 0; 
    allocation->upper.x = r.x.natural;
    allocation->upper.y = r.y.natural;
    allocation->upper.z = 0;
    allocation->xalign = r.x.align;
    allocation->yalign = r.y.align;
    allocation->zalign = r.z.align;

    DrawTraversalImpl *traversal = new DrawTraversalImpl(_graphic,
							 allocation->_this(),
							 Transform::_nil(),
							 print);
    print->start_traversal(Traversal_var(traversal->_this()));
    traversal->init();
    try { _graphic->traverse(Traversal_var(traversal->_this()));}
    catch (const CORBA::OBJECT_NOT_EXIST &) { std::cerr << "PrintCommand: warning: corrupt scene graph!" << std::endl;}
    catch (const CORBA::BAD_PARAM &) { std::cerr << "PrintCommand: caught bad parameter" << std::endl;}
    traversal->finish();
    traversal->_remove_ref();
    print->finish_traversal();
  }
 private:
  Graphic_var       _graphic;
  ServerContext_var _server;
};

class MacroCommandImpl : public virtual POA_Fresco::MacroCommand,
			 public CommandImpl
{
  typedef std::vector<Fresco::Command_var> clist_t;
public:
  virtual ~MacroCommandImpl()
  {
    for (clist_t::iterator i = _commands.begin(); i != _commands.end(); ++i)
      (*i)->destroy();
  }
  virtual void append(Fresco::Command_ptr c)
  {
    _commands.push_back(Fresco::Command::_duplicate(c));
  }
  virtual void prepend(Fresco::Command_ptr c)
  {
    _commands.insert(_commands.begin(), Fresco::Command::_duplicate(c));
  }
  virtual void execute(const CORBA::Any &any)
    {
      for (clist_t::iterator i = _commands.begin(); i != _commands.end(); ++i)
	(*i)->execute(any);
    }
 private:
  clist_t _commands;
};



CommandKitImpl::CommandKitImpl(const std::string &id,
			       const Fresco::Kit::PropertySeq &p,
			       ServerContextImpl *c)
  : KitImpl(id, p, c) { }

CommandKitImpl::~CommandKitImpl() { }

void CommandKitImpl::bind(ServerContext_ptr server)
{
  _server = ServerContext::_duplicate(server);
}

Command_ptr CommandKitImpl::debugger(Fresco::Command_ptr c, const char *text)
{
  // FIXME: Shouldn't this be std::cerr? -- tobias
  DebugCommand *command = new DebugCommand(c, std::cout, text);
  activate(command);
  return command->_this();
}

Command_ptr CommandKitImpl::log(const char *text)
{
  // FIXME: Shouldn't this be std::cerr? -- tobias
  LogCommand *command = new LogCommand(std::cout, text);
  activate(command);
  return command->_this();
}

Command_ptr CommandKitImpl::print(Graphic_ptr graphic)
{
  PrintCommand *command = new PrintCommand(graphic, _server);
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

TelltaleConstraint_ptr CommandKitImpl::selection_required()
{
  SelectionRequired *constraint = new SelectionRequired(Controller::toggled);
  activate(constraint);
  return constraint->_this();
}

Telltale_ptr CommandKitImpl::normal_telltale()
{
  TelltaleImpl *telltale = new TelltaleImpl(TelltaleConstraint::_nil());
  activate(telltale);
  return telltale->_this();
}

Telltale_ptr CommandKitImpl::constrained_telltale(TelltaleConstraint_ptr constraint)
{
    TelltaleImpl *telltale = new TelltaleImpl(constraint);
    activate(telltale);
    constraint->add(Telltale_var(telltale->_this()));
    return telltale->_this();
}

Selection_ptr CommandKitImpl::group(Selection::Policy policy)
{
  TelltaleConstraintImpl *constraint = 0;
  switch (policy)
    {
    case Selection::exclusive:
      constraint = new ExclusiveChoice(Controller::toggled);
      break;
    case Selection::required:
      constraint = new SelectionRequired(Controller::toggled);
      break;
    case Selection::exclusive|Selection::required:
      constraint = new ExclusiveRequired(Controller::toggled);
      break;
    default: break;
    }
  SelectionImpl *selection = 0;
  if (constraint)
    {
      activate(constraint);
      selection = new SelectionImpl(policy, TelltaleConstraint_var(constraint->_this()));
    }
  else selection = new SelectionImpl(policy, TelltaleConstraint::_nil());
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

extern "C" KitImpl *load()
{
  static std::string properties[] = {"implementation", "CommandKitImpl"};
  return create_prototype<CommandKitImpl>("IDL:fresco.org/Fresco/CommandKit:1.0", properties, 2);
}
