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
#include <Fresco/config.hh>
#include <Fresco/PickTraversal.hh>
#include <Fresco/IO.hh>
#include <Berlin/RegionImpl.hh>
#include <Berlin/PickTraversalImpl.hh>
#include <Berlin/Provider.hh>
#include "SelectTool.hh"
#include <vector>

using namespace Prague;
using namespace Fresco;
using namespace Unidraw;

namespace Berlin
{
  namespace UnidrawKit
  {

    class SelectTraversal : public PickTraversalImpl
    {
      public:
        SelectTraversal(Fresco::Graphic_ptr, Fresco::Region_ptr,
            Fresco::Transform_ptr);
        ~SelectTraversal();
        void region(const Vertex &p, const Vertex &q)
        { my_hot.valid = true, my_hot.lower = p, my_hot.upper = q; }
        size_t selected() const { return my_selected.size(); }
        SelectTraversal *operator [](size_t i) { return my_selected[i]; }
        virtual CORBA::Boolean intersects_region(Fresco::Region_ptr);
        virtual void hit();
        virtual CORBA::Boolean ok() { return true; }
        virtual CORBA::Boolean picked() { return my_selected.size(); }
        void debug();
      private:
        RegionImpl my_hot;
        std::vector<SelectTraversal *> my_selected;
    };

    SelectTraversal::SelectTraversal(Fresco::Graphic_ptr g,
                     Fresco::Region_ptr a,
                                     Fresco::Transform_ptr t) :
    PickTraversalImpl(g, a, t, 0)
    { }

    SelectTraversal::~SelectTraversal()
    {
        // for (std::vector<SelectTraversal *>::iterator i =
    //      my_selected.begin(); i != _selected.end();
    //      ++i)
        //     (*i)->deactivate();
    }

    CORBA::Boolean SelectTraversal::intersects_region(Region_ptr r)
    {
        Trace trace("SelectTraversal::intersects_region");
        std::cout << "intersects_region test" << std::endl;
        debug();
        RegionImpl region(r, get_transformation(current()));
        return region.intersects(my_hot);
    }

    void SelectTraversal::hit()
    {
        Trace trace("SelectTraversal::hit");
        // make sure the controller is really inside the hot region
        std::cout << "hit !" << std::endl;
        SelectTraversal *memento = new SelectTraversal(*this);
        // activate(memento);
        my_selected.push_back(memento);
    }

    void SelectTraversal::debug()
    {
        std::cout << "SelectTraversal::debug : stack size = " << size()
                  << std::endl;
        // Region_var r = current_allocation();
        // Transform_var t = current_transformation();
        // RegionImpl region(r, t);
        // std::cout << "current allocation is " << region << std::endl;
    }

    class SelectCommand : public virtual POA_Unidraw::Command,
              public ServantBase
    {
      public:
        SelectCommand();
        virtual void execute();
        virtual void store(Unidraw::Model_ptr, const CORBA::Any &) {}
        virtual CORBA::Any *recall(Unidraw::Model_ptr)
    { return new CORBA::Any(); }
        virtual void destroy() { deactivate(); }
      private:
    };

    SelectTool::SelectTool(Graphic_ptr graphic) :
    my_graphic(Graphic::_duplicate(graphic))
    { }
    SelectTool::~SelectTool() { }
    CORBA::Boolean SelectTool::grasp(Fresco::Controller_ptr controller,
                                     Fresco::PickTraversal_ptr traversal,
                                     const Fresco::Input::Event &event)
    {
        Trace trace("SelectTool::grasp");
        my_root = Controller::_duplicate(controller);
        my_iterator = my_root->last_child_graphic();
        my_begin = event[1].attr.location();
        Transform_var trafo = traversal->current_transformation();
        trafo->inverse_transform_vertex(my_begin);
        my_matrix[0][0] = my_matrix[0][1] = my_matrix[0][2] = 0.;
        my_matrix[1][0] = my_matrix[1][1] = my_matrix[1][2] = 0.;
        my_matrix[2][0] = my_matrix[2][1] = my_matrix[2][2] = 0.;
        my_matrix[3][0] = my_matrix[3][1] = my_matrix[3][2] = 0.;
        my_matrix[0][3] = my_begin.x;
        my_matrix[1][3] = my_begin.y;
        my_matrix[2][3] = my_begin.z;
        Transform_var transform = my_graphic->transformation();
        transform->load_matrix(my_matrix);
        my_iterator->insert(my_graphic);
        return true;
    }

    CORBA::Boolean
    SelectTool::manipulate(Fresco::PickTraversal_ptr traversal,
               const Fresco::Input::Event &event)
    {
        Trace trace("SelectTool::manipulate");
        if (event[0].attr._d() == Fresco::Input::button) return false;
        my_end = event[0].attr.location();
        Transform_var trafo = traversal->current_transformation();
        trafo->inverse_transform_vertex(my_end);
        my_matrix[0][0] = my_end.x - my_begin.x;
        my_matrix[1][1] = my_end.y - my_begin.y;
        my_matrix[2][2] = my_end.z - my_begin.z;
        Transform_var transform = my_graphic->transformation();
        transform->load_matrix(my_matrix);
        my_graphic->need_resize();
        return true;
    }
    
    Unidraw::Command_ptr
    SelectTool::effect(Fresco::PickTraversal_ptr traversal,
               const Fresco::Input::Event &event)
    {
        Trace trace("SelectTool::effect");
        // traverse the viewer's children and pick all graphics that
    // intersect with the selected region
        SelectTraversal *
        select(new SelectTraversal(my_root,
                       Region_var(traversal->current_allocation()),
                       Transform::_nil()));
        select->region(my_begin, my_end);
        // Impl_var<SelectTraversal>
    //     select(new SelectTraversal(my_root,
    //                                Region_var(allocation->_this()),
        //                                Fresco::Transform::_nil()));
        my_root->traverse(Traversal_var(select->_this()));

        // now walk down the picked trail and find 'Viewer' objects.
        std::cout << "found " << select->selected() << " objects"
          << std::endl;
        my_iterator->remove();
        my_iterator->destroy();
        SelectCommand *command = new SelectCommand();
        activate(command);
        return command->_this();
    }
    
    SelectCommand::SelectCommand() { }
    void SelectCommand::execute() { }
    
  } // namespace
} // namespace
