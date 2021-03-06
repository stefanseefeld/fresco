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

namespace Berlin
{
  namespace CommandKit
  {

    class DebugCommand : public CommandImpl
    {
      public:
        DebugCommand(Command_ptr c, std::ostream &os, const char *t) :
          my_command(Fresco::Command::_duplicate(c)), my_os(os), my_text(t) { }
        virtual void execute(const CORBA::Any &any)
        {
            my_os << my_text << " : entering execute" << std::endl;
            my_command->execute(any);
            my_os << my_text << " : leaving execute" << std::endl;
        }
      private:
        Command_var   my_command;
        std::ostream &my_os;
        std::string   my_text;
    };

    class LogCommand : public CommandImpl
    {
      public:
        LogCommand(std::ostream &os, const char *text) : my_os(os), my_text(text) {}
        virtual void execute(const CORBA::Any &) { my_os << my_text << std::endl;}
      private:
        std::ostream &my_os;
        std::string   my_text;
    };

    class PrintCommand : public CommandImpl
    {
      public:
        PrintCommand(Graphic_ptr graphic, ServerContext_ptr server) :
          my_graphic(Graphic::_duplicate(graphic)),
          my_server(ServerContext::_duplicate(server))
        { }
        virtual void execute(const CORBA::Any &)
        {
            Fresco::Kit::PropertySeq props;
            props.length(1);
            props[0].name = CORBA::string_dup("implementation");
            props[0].value = CORBA::string_dup("PSDrawingKit");
            RefCount_var<DrawingKit> print =
              resolve_kit<DrawingKit>(my_server, "IDL:fresco.org/Fresco/DrawingKit:1.0", props);
            Fresco::Graphic::Requisition r;
            GraphicImpl::init_requisition(r);
            my_graphic->request(r);
            Lease_var<RegionImpl> allocation(Provider<RegionImpl>::provide());
            allocation->valid = true;
            allocation->lower.x = allocation->lower.y = allocation->lower.z = 0;
            allocation->upper.x = r.x.natural;
            allocation->upper.y = r.y.natural;
            allocation->upper.z = 0;
            allocation->xalign = r.x.align;
            allocation->yalign = r.y.align;
            allocation->zalign = r.z.align;

            DrawTraversalImpl *traversal =
              new DrawTraversalImpl(my_graphic, allocation->_this(),
                                    Transform::_nil(), print);
            print->start_traversal(Traversal_var(traversal->_this()));
            traversal->init();
            try { my_graphic->traverse(Traversal_var(traversal->_this())); }
            catch (const CORBA::OBJECT_NOT_EXIST &)
            {
                std::cerr << "PrintCommand: warning: corrupt scene graph!" << std::endl;
            }
            catch (const CORBA::BAD_PARAM &)
            {
                std::cerr << "PrintCommand: caught bad parameter" << std::endl;
            }
            traversal->finish();
            traversal->_remove_ref();
            print->finish_traversal();
        }
      private:
        Graphic_var       my_graphic;
        ServerContext_var my_server;
    };

    class MacroCommandImpl : public virtual POA_Fresco::MacroCommand, public CommandImpl
    {
        typedef std::vector<Fresco::Command_var> clist_t;
      public:
        virtual ~MacroCommandImpl()
        {
            for (clist_t::iterator i = my_commands.begin(); i != my_commands.end(); ++i)
            (*i)->destroy();
        }
        virtual void append(Fresco::Command_ptr c)
        {
            my_commands.push_back(Fresco::Command::_duplicate(c));
        }
        virtual void prepend(Fresco::Command_ptr c)
        {
            my_commands.insert(my_commands.begin(), Fresco::Command::_duplicate(c));
        }
        virtual void execute(const CORBA::Any &any)
        {
            for (clist_t::iterator i = my_commands.begin(); i != my_commands.end(); ++i)
                (*i)->execute(any);
        }
      private:
        clist_t my_commands;
    };

  } // namespace
} // namespace


Berlin::CommandKit::CommandKitImpl::CommandKitImpl(const std::string &id,
                               const Fresco::Kit::PropertySeq &p,
                               ServerContextImpl *c) :
  KitImpl(id, p, c) { }

Berlin::CommandKit::CommandKitImpl::~CommandKitImpl() { }

void Berlin::CommandKit::CommandKitImpl::bind(ServerContext_ptr server)
{
    my_server = ServerContext::_duplicate(server);
}

Command_ptr Berlin::CommandKit::CommandKitImpl::debugger(Fresco::Command_ptr c, const char *text)
{
  // FIXME: Shouldn't this be std::cerr? -- tobias
  DebugCommand *command = new DebugCommand(c, std::cout, text);
  activate(command);
  return command->_this();
}

Command_ptr Berlin::CommandKit::CommandKitImpl::log(const char *text)
{
  // FIXME: Shouldn't this be std::cerr? -- tobias
  LogCommand *command = new LogCommand(std::cout, text);
  activate(command);
  return command->_this();
}

Command_ptr Berlin::CommandKit::CommandKitImpl::print(Graphic_ptr graphic)
{
  PrintCommand *command = new PrintCommand(graphic, my_server);
  activate(command);
  return command->_this();
}

MacroCommand_ptr Berlin::CommandKit::CommandKitImpl::composite()
{
  MacroCommandImpl *command = new MacroCommandImpl();
  activate(command);
  return command->_this();
}

TelltaleConstraint_ptr Berlin::CommandKit::CommandKitImpl::exclusive(Telltale::Mask m)
{
  ExclusiveChoice *constraint = new ExclusiveChoice(m);
  activate(constraint);
  return constraint->_this();
}

TelltaleConstraint_ptr Berlin::CommandKit::CommandKitImpl::selection_required()
{
  SelectionRequired *constraint = new SelectionRequired(Controller::toggled);
  activate(constraint);
  return constraint->_this();
}

Telltale_ptr Berlin::CommandKit::CommandKitImpl::normal_telltale()
{
  TelltaleImpl *telltale = new TelltaleImpl(TelltaleConstraint::_nil());
  activate(telltale);
  return telltale->_this();
}

Telltale_ptr Berlin::CommandKit::CommandKitImpl::constrained_telltale(TelltaleConstraint_ptr constraint)
{
    TelltaleImpl *telltale = new TelltaleImpl(constraint);
    activate(telltale);
    constraint->add(Telltale_var(telltale->_this()));
    return telltale->_this();
}

Selection_ptr Berlin::CommandKit::CommandKitImpl::group(Selection::Policy policy)
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

BoundedValue_ptr Berlin::CommandKit::CommandKitImpl::bvalue(Coord l, Coord u, Coord v, Coord s, Coord p)
{
  BoundedValueImpl *bounded = new BoundedValueImpl(l, u, v, s, p);
  activate(bounded);
  return bounded->_this();
}

BoundedRange_ptr Berlin::CommandKit::CommandKitImpl::brange(Coord l, Coord u, Coord lv, Coord uv, Coord s, Coord p)
{
  BoundedRangeImpl *bounded = new BoundedRangeImpl(l, u, lv, uv, s, p);
  activate(bounded);
  return bounded->_this();
}

TextBuffer_ptr Berlin::CommandKit::CommandKitImpl::text()
{
  TextBufferImpl *buffer = new TextBufferImpl();
  activate(buffer);
  return buffer->_this();
}

StreamBuffer_ptr Berlin::CommandKit::CommandKitImpl::stream(CORBA::Long b)
{
  StreamBufferImpl *buffer = new StreamBufferImpl(b);
  activate(buffer);
  return buffer->_this();
}

extern "C" Berlin::KitImpl *load()
{
  static std::string properties[] = {"implementation", "CommandKitImpl"};
  return Berlin::create_prototype<Berlin::CommandKit::CommandKitImpl>
    ("IDL:fresco.org/Fresco/CommandKit:1.0", properties, 2);
}
