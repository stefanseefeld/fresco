/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Graydon Hoare <graydon@pobox.com> 
 * Copyright (C) 2000 Stefan Seefeld <stefan@berlin-consortium.org>
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
#ifndef _CommandKitImpl_hh
#define _CommandKitImpl_hh

#include <Warsaw/config.hh>
#include <Warsaw/CommandKit.hh>
#include <Berlin/KitImpl.hh>
#include <vector>

class CommandImpl;
class SubjectImpl;

class CommandKitImpl : public virtual POA_Warsaw::CommandKit,
		       public KitImpl
{
 public:
  CommandKitImpl(KitFactory *, const Warsaw::Kit::PropertySeq &);
  virtual ~CommandKitImpl();
  Warsaw::Command_ptr log(const char *);
  Warsaw::MacroCommand_ptr composite();
  Warsaw::TelltaleConstraint_ptr exclusive(Warsaw::Telltale::Mask);
  Warsaw::TelltaleConstraint_ptr selection_required();
  Warsaw::Telltale_ptr     constrained_telltale(Warsaw::TelltaleConstraint_ptr);
  Warsaw::Telltale_ptr     normal_telltale();
  Warsaw::Selection_ptr    group(Warsaw::Selection::Policy);
  Warsaw::BoundedValue_ptr bvalue(Warsaw::Coord, Warsaw::Coord, Warsaw::Coord, Warsaw::Coord, Warsaw::Coord);
  Warsaw::BoundedRange_ptr brange(Warsaw::Coord, Warsaw::Coord, Warsaw::Coord, Warsaw::Coord, Warsaw::Coord, Warsaw::Coord);
  Warsaw::TextBuffer_ptr   text();
  Warsaw::StreamBuffer_ptr stream(CORBA::Long);
 private:
};

#endif
