/*$Id$
 *
 * This source file is a part of the Fresco Project.
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
#include <Prague/Sys/Tracer.hh>
#include <Fresco/IO.hh>
#include "daVinci/Visitors.hh"

using namespace Prague;
using namespace Fresco;

namespace daVinci
{

Visitor::Visitor() {}
Visitor::~Visitor() {}
bool Visitor::visit(Graphic_ptr) { return false;}
void Visitor::visit_children(Graphic_ptr graphic)
{
  Graphic::Iterator_var iterator = graphic->first_child_graphic();
  if (CORBA::is_nil(iterator)) return;
  for (Graphic_var next = iterator->child(); !CORBA::is_nil(next); iterator->next(), next = iterator->child())
    if (!visit(next)) break;
}

Appender::Appender(Graphic_ptr graphic, bool resize)
  : _graphic(Graphic::_duplicate(graphic)), _resize(resize) {}
Appender::~Appender () {}

bool Appender::visit(Graphic_ptr graphic)
{
  graphic->append(_graphic);
  if (_resize) graphic->need_resize();
  return true;
}

Remover::Remover() {}
Remover::~Remover()
{
//   for (CORBA::Long i = 0; i < list_.count(); i++) {
//     GlyphOffset_ptr offset = list_.item(i);
//     offset->notify_observers();
//     offset->remove();
//   }
}

bool Remover::visit(Graphic_ptr graphic)
{
//   _list.append(graphic);
  return true;
}

Counter::Counter() : _count(0) {}
bool Counter::visit(Graphic_ptr)
{
  ++_count;
  return true;
}

CmdVisitor::CmdVisitor(Command *command, bool execute)
  : _command(command), _execute(execute) {}
CmdVisitor::~CmdVisitor () {}
bool CmdVisitor::visit (Graphic_ptr graphic)
{
  Manipulator* m = Manipulator::_cast(g);
  if (!CORBA::is_nil(m))
    {
      if (_execute) m->execute(_command);
      else        m->unexecute(_command);
    }
  return true;
}
    
RecurCmdVisitor::RecurCmdVisitor (Command *command, bool execute)
  : _command(command), _execute(execute) {}
RecurCmdVisitor::~RecurCmdVisitor () {}
void RecurCmdVisitor::recur_visit_children(Graphic_ptr graphic)
{
  if (CORBA::is_nil(graphic)) return;
  Graphic_var child = graphic->body();
  // if this is a decorator...
  if (!CORBA::is_nil(child) && visit(child)) return;
  // ...else...
  Graphic::Iterator_var iterator = graphic->first_child_graphic();
  if (CORBA::is_nil(iterator)) return;
  for (Graphic_var next = iterator->child(); !CORBA::is_nil(next); iterator->next(), next = iterator->child())
    if (!visit(next))
      recur_visit_children(next);
}

bool RecurCmdVisitor::visit (Graphic_ptr graphic)
{
  Manipulator *m = Manipulator::_cast(graphic);
  if (!CORBA::is_nil(m))
    {
      if (_execute) m->execute(_command);
      else         m->unexecute(_command);
      return true;
    }
  else return false;
}
    
ManipCopier::ManipCopier(bool shallow) : _shallow(shallow) {}
ManipCopier::~ManipCopier()
{
  for (Long i = 0; i < _manipulators->count(); ++i)
    CORBA::release(_manipulators[i]);
}

bool ManipCopier::visit(Graphic_ptr graphic)
{
  Manipulator* m = Manipulator::_cast(g);
  if (!CORBA::is_nil(m))
    {
      if (_shallow) _manipulators->push_back(Manipulator::_duplicate(m));
      else        _manipulators->append(m->deep_copy());
    }
  return true;
}

TAManipCopier::TAManipCopier (Region_ptr a, bool shallow)
  : ManipCopier(shallow),
    _allocation(Region::_duplicate(a))
{}

TAManipCopier::~TAManipCopier ()
{
  CORBA::Long i;
  for (size_t i = 0; i != _allocations->size(); ++i); //free allocation
//     {
//       CORBA::release(alist_->item(i));
//     }
  for (size_t i = 0; i != _transforms->size(); ++i); //free transform
//     {
//       CORBA::release(alist_->item(i));
//     }
}

bool TAManipCopier::visit (Graphic_ptr graphic)
{
  ManipCopier::visit(g, go);
  RegionImpl* r = new RegionImpl;
  TransformImpl* t = new TransformImpl;
  r->copy(a_);
  
    Glyph::AllocationInfo a;
    a.allocation = r;
    a.transformation = t;
    a.damaged = nil;
    
    alist_->append(Region::_duplicate(r));
    tlist_->append(Transform::_duplicate(t));

    go->child_allocate(a);
    
    return true;
}

OffsetVisitor::OffsetVisitor () {
    glist_ = new GlyphOffsetList;
}

OffsetVisitor::~OffsetVisitor () {
    for (CORBA::Long i = 0; i < glist_->count(); i++) {
        CORBA::release(glist_->item(i));
    }
    delete glist_;
}

bool OffsetVisitor::visit (Glyph_ptr, GlyphOffset_ptr go) {
    glist_->append(GlyphOffset::_duplicate(go));
    return true;
}

GlyphOffset_ptr OffsetVisitor::offset (CORBA::ULong i) {
    GlyphOffset_ptr go = nil;
    if (i < CORBA::ULong(glist_->count())) {
        go = glist_->item(i);
    }
    return go;
}

CORBA::ULong OffsetVisitor::offset_count () {
    return CORBA::ULong(glist_->count());
}

Inserter::Inserter(vector<Manipulator *> &manipulators) : _manipulators(manipulators) {}
bool Inserter::visit(Graphic_ptr graphic)
{
  for (size_t i = 0; i != _manipulators.size(); ++i) graphic->append_graphic(_manipulators[i]);
  return true;
}
