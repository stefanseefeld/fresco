/*$Id$
 *
 * This source file is a part of the Berlin Project.
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
#include <Prague/Sys/Tracer.hh>
#include <Warsaw/config.hh>
#include <Warsaw/PickTraversal.hh>
#include <Warsaw/IO.hh>
#include <Berlin/RegionImpl.hh>
#include <Berlin/PickTraversalImpl.hh>
#include <Berlin/Provider.hh>
#include "Unidraw/SelectTool.hh"
#include <vector>

using namespace Prague;
using namespace Warsaw;
using namespace Unidraw;

class SelectTraversal : public PickTraversalImpl
{
public:
  SelectTraversal(Warsaw::Graphic_ptr, Warsaw::Region_ptr, Warsaw::Transform_ptr);
  ~SelectTraversal();
  void region(const Vertex &p, const Vertex &q) { _hot.valid = true, _hot.lower = p, _hot.upper = q;}
  size_t selected() const { return _selected.size();}
  SelectTraversal *operator [](size_t i) { return _selected[i];}
  virtual CORBA::Boolean intersects_region(Warsaw::Region_ptr);
  virtual void hit();
  virtual CORBA::Boolean ok() { return true;}
  virtual CORBA::Boolean picked() { return _selected.size();}
  void debug();
private:
  RegionImpl                     _hot;
  std::vector<SelectTraversal *> _selected;
};

SelectTraversal::SelectTraversal(Warsaw::Graphic_ptr g, Warsaw::Region_ptr a, Warsaw::Transform_ptr t)
  : PickTraversalImpl(g, a, t, 0) {}

SelectTraversal::~SelectTraversal()
{
//   for (std::vector<SelectTraversal *>::iterator i = _selected.begin(); i != _selected.end(); ++i) (*i)->deactivate();
}

CORBA::Boolean SelectTraversal::intersects_region(Region_ptr r)
{
  Trace trace("SelectTraversal::intersects_region");
  std::cout << "intersects_region test" << std::endl;
  debug();
  RegionImpl region(r, get_transformation(current()));
  return region.intersects(_hot);
  
}

void SelectTraversal::hit()
{
  Trace trace("SelectTraversal::hit");
  // make sure the controller is really inside the hot region
  std::cout << "hit !" << std::endl;
  SelectTraversal *memento = new SelectTraversal(*this);
//   activate(memento);
  _selected.push_back(memento);
}

void SelectTraversal::debug()
{
  std::cout << "SelectTraversal::debug : stack size = " << size()
	    << std::endl;
//   Region_var r = current_allocation();
//   Transform_var t = current_transformation();
//   RegionImpl region(r, t);
//   std::cout << "current allocation is " << region << std::endl;
}

class SelectCommand : public virtual POA_Unidraw::Command,
		      public ServantBase
{
public:
  SelectCommand();
  virtual void execute();
  virtual void store(Unidraw::Model_ptr, const CORBA::Any &) {}
  virtual CORBA::Any *recall(Unidraw::Model_ptr) { return new CORBA::Any();}
  virtual void destroy() { deactivate();}
private:
};

SelectTool::SelectTool(Graphic_ptr graphic) : _graphic(Graphic::_duplicate(graphic)) {}
SelectTool::~SelectTool() {}
CORBA::Boolean SelectTool::grasp(Warsaw::Controller_ptr controller, Warsaw::PickTraversal_ptr traversal, const Warsaw::Input::Event &event)
{
  Trace trace("SelectTool::grasp");
  _root = Controller::_duplicate(controller);
  _iterator = _root->last_child_graphic();
  _begin = event[1].attr.location();
  Transform_var trafo = traversal->current_transformation();
  trafo->inverse_transform_vertex(_begin);
  _matrix[0][0] = _matrix[0][1] = _matrix[0][2] = 0.;
  _matrix[1][0] = _matrix[1][1] = _matrix[1][2] = 0.;
  _matrix[2][0] = _matrix[2][1] = _matrix[2][2] = 0.;
  _matrix[3][0] = _matrix[3][1] = _matrix[3][2] = 0.;
  _matrix[0][3] = _begin.x;
  _matrix[1][3] = _begin.y;
  _matrix[2][3] = _begin.z;
  Transform_var transform = _graphic->transformation();
  transform->load_matrix(_matrix);
  _iterator->insert(_graphic);
  return true;
}

CORBA::Boolean SelectTool::manipulate(Warsaw::PickTraversal_ptr traversal, const Warsaw::Input::Event &event)
{
  Trace trace("SelectTool::manipulate");
  if (event[0].attr._d() == Warsaw::Input::button) return false;
  _end = event[0].attr.location();
  Transform_var trafo = traversal->current_transformation();
  trafo->inverse_transform_vertex(_end);
  _matrix[0][0] = _end.x - _begin.x;
  _matrix[1][1] = _end.y - _begin.y;
  _matrix[2][2] = _end.z - _begin.z;
  Transform_var transform = _graphic->transformation();
  transform->load_matrix(_matrix);
  _graphic->need_resize();
  return true;
}

Unidraw::Command_ptr SelectTool::effect(Warsaw::PickTraversal_ptr traversal, const Warsaw::Input::Event &event)
{
  Trace trace("SelectTool::effect");
  /*
   * traverse the viewer's children and pick all graphics that intersect with the selected region 
   */
  SelectTraversal *select(new SelectTraversal(_root, Region_var(traversal->current_allocation()), Transform::_nil()));
  select->region(_begin, _end);
//   Impl_var<SelectTraversal> select(new SelectTraversal(_root, Region_var(allocation->_this()), Warsaw::Transform::_nil()));
  _root->traverse(Traversal_var(select->_this()));
  /*
   * now walk down the picked trail and find 'Viewer' objects.
   */
  std::cout << "found " << select->selected() << " objects" << std::endl; 
  _iterator->remove();
  _iterator->destroy();
  SelectCommand *command = new SelectCommand();
  activate(command);
  return command->_this();
}

SelectCommand::SelectCommand() {}
void SelectCommand::execute() {}
