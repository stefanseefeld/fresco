/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Graydon Hoare <graydon@fresco.org> 
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
#ifndef _CommandKitImpl_hh
#define _CommandKitImpl_hh

#include <Fresco/config.hh>
#include <Fresco/CommandKit.hh>
#include <Fresco/Graphic.hh>
#include <Berlin/KitImpl.hh>
#include <vector>

class CommandImpl;
class SubjectImpl;

class CommandKitImpl : public virtual POA_Fresco::CommandKit,
		       public KitImpl
{
 public:
  CommandKitImpl(const std::string &, const Fresco::Kit::PropertySeq &);
  virtual ~CommandKitImpl();
  virtual KitImpl *clone(const Fresco::Kit::PropertySeq &p) { return new CommandKitImpl(repo_id(), p);}
  virtual void bind(Fresco::ServerContext_ptr);

  virtual Fresco::Command_ptr debugger(Fresco::Command_ptr, const char *);
  virtual Fresco::Command_ptr log(const char *);
  virtual Fresco::Command_ptr print(Fresco::Graphic_ptr);
  virtual Fresco::MacroCommand_ptr composite();
  virtual Fresco::TelltaleConstraint_ptr exclusive(Fresco::Telltale::Mask);
  virtual Fresco::TelltaleConstraint_ptr selection_required();
  virtual Fresco::Telltale_ptr     constrained_telltale(Fresco::TelltaleConstraint_ptr);
  virtual Fresco::Telltale_ptr     normal_telltale();
  virtual Fresco::Selection_ptr    group(Fresco::Selection::Policy);
  virtual Fresco::BoundedValue_ptr bvalue(Fresco::Coord, Fresco::Coord, Fresco::Coord, Fresco::Coord, Fresco::Coord);
  virtual Fresco::BoundedRange_ptr brange(Fresco::Coord, Fresco::Coord, Fresco::Coord, Fresco::Coord, Fresco::Coord, Fresco::Coord);
  virtual Fresco::TextBuffer_ptr   text();
  virtual Fresco::StreamBuffer_ptr stream(CORBA::Long);
 private:
  Fresco::ServerContext_var _server;
};

#endif
