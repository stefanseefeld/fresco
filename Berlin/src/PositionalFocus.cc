/*$Id$
 *
 * This source file is a part of the Fresco Project.
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

#include <Prague/Sys/Tracer.hh>
#include <Fresco/config.hh>
#include <Fresco/IO.hh>
#include "Berlin/PositionalFocus.hh"
#include "Berlin/ScreenImpl.hh"
#include "Berlin/PickTraversalImpl.hh"
#include "Berlin/RegionImpl.hh"
#include "Berlin/Provider.hh"
#include "Berlin/Console.hh"
#include "Berlin/Event.hh"
#include "Berlin/Vertex.hh"
#include "Berlin/RCManager.hh"
#include "Berlin/RasterImpl.hh"

using namespace Prague;
using namespace Fresco;
using namespace Berlin;

namespace Berlin
{
  static bool should_track;

  //. implement a PickTraversal that keeps a fixed pointer to
  //. a memento cache. As there is always exactly one picked
  //. graphic, we are simply using a static pair of traversals
  //. and switch between them as objects are picked
  class PositionalFocus::Traversal : public PickTraversalImpl
  {
    public:
      Traversal(Fresco::Graphic_ptr g, Fresco::Region_ptr a,
        Fresco::Transform_ptr t, PositionalFocus *f) :
      PickTraversalImpl(g, a, t, f),
      my_memento(0),
      my_picked(false)
      { }
      Traversal &operator = (const Traversal &t)
      {
      PickTraversalImpl::operator = (t);
      my_pointer = t.my_pointer; 
      my_picked = false;
      // Do not touch my_memento so we can keep switching between
      // two Traversals (see PositionalFocus::PositionalFocusi() and
      // PositionalFocus::dispatch())
      }
      void pointer(const Fresco::Input::Position &p) { my_pointer = p;}
      void memento(Traversal *m) { my_memento = m;}
      Traversal *memento() { return picked() ? my_memento : 0;}
      virtual CORBA::Boolean intersects_region(Fresco::Region_ptr);
      virtual void hit() { *my_memento = *this, my_picked = true;}
      virtual CORBA::Boolean picked() { return my_picked;}
      void debug();
    private:
      Fresco::Input::Position my_pointer;
      Traversal              *my_memento;
      bool                    my_picked;
  };

} // namespace

struct PositionalFocus::PointerCacheTrait
{
    static Console::Pointer *create(Raster_var raster)
    { return Console::instance()->pointer(raster); }

    static Raster_var remote(Console::Pointer *pointer)
    { return Raster_var(pointer->raster()); }
};

CORBA::Boolean
PositionalFocus::Traversal::intersects_region(Region_ptr region)
{
    const Transform::Matrix &matrix = get_transformation(current())->matrix();
    Coord d = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    if (d == 0.) return false;
    Coord x = my_pointer.x - matrix[0][3];
    Coord y = my_pointer.y - matrix[1][3];
    Vertex local;
    local.x = (matrix[1][1] * x - matrix[0][1] * y)/d;
    local.y = (matrix[0][0] * y - matrix[1][0] * x)/d;
    local.z = 0.0; // initialise the z coordinate. It's not used, but still...
    Vertex lower, upper;
    region->bounds(lower, upper);
    bool inside = lower.x <= local.x && local.x <= upper.x &&
    lower.y <= local.y && local.y <= upper.y;
    if (should_track && inside)
    {
    Region_var r = current_allocation();
    Transform_var t = current_transformation();
    RegionImpl region(r, t);
    Console::instance()->highlight_screen(region.lower.x, region.lower.y,
                          region.upper.x, region.upper.y);
    }
    return inside;
}

void PositionalFocus::Traversal::debug()
{
    std::cout << "PositionalFocus::Traversal::debug : stack size = "
          << size() << std::endl;
    Region_var r = current_allocation();
    Transform_var t = current_transformation();
    RegionImpl region(r, t);
    std::cout << "current allocation is " << region << std::endl;
    std::cout << "pointer is " << my_pointer << std::endl;
    Vertex local = my_pointer;
    Transform::Matrix matrix;
    t->store_matrix(matrix);
    std::cout << "current trafo" << std::endl << matrix;
    t->inverse_transform_vertex(local);
    region.copy(r);
    std::cout << "local CS: current allocation is " << region << std::endl;
    std::cout << "local CS: pointer is " << local << std::endl;      
}

PositionalFocus::PositionalFocus(Input::Device d, Graphic_ptr g,
                 Region_ptr r) :
    FocusImpl(d),
    my_root(g),
    my_default_raster(0),
    my_pointers(new PointerCache(32)),
    my_traversal(0),
    my_grabbed(false)
{
    Trace trace("PositionalFocus::PositionalFocus");
    Prague::Path path = RCManager::get_path("rasterpath");
    std::string name = path.lookup_file("ul-cursor.png");
    if (name.empty())
    {
    std::string msg = "No default cursor found in rasterpath";
    throw std::runtime_error(msg);
    }
    else
    {
    my_default_raster = new RasterImpl(name);
    my_pointer =
        my_pointers->lookup(Raster_var(my_default_raster->_this()));
    my_pointer->save();
    my_pointer->draw();
    }
    // Generate two Traversals
    my_traversal_cache[0] =
    new Traversal(my_root, r, Transform::_nil(), this);
    my_traversal_cache[1] =
    new Traversal(my_root, r, Transform::_nil(), this);
    // have both Traversal's memento point to the other.
    my_traversal_cache[0]->memento(my_traversal_cache[1]);
    my_traversal_cache[1]->memento(my_traversal_cache[0]);
    // Use one of the Traversals.
    my_traversal = my_traversal_cache[0];
}

PositionalFocus::~PositionalFocus()
{
    Trace trace("PositionalFocus::~PositionalFocus");
    Impl_var<Traversal>::deactivate(my_traversal_cache[0]);
    Impl_var<Traversal>::deactivate(my_traversal_cache[1]);  
}

void PositionalFocus::activate_composite()
{ Trace trace("PositionalFocus::activate_composite"); }

void PositionalFocus::grab()
{
    // Prague::Guard<Mutex> guard(mutex);
    my_grabbed = true;
}

void PositionalFocus::ungrab()
{
    // Prague::Guard<Mutex> guard(mutex);
    my_grabbed = false;
}

void PositionalFocus::set_cursor(Raster_ptr r)
{
    Resources &prev = my_resources.top();
    if (!prev.flags & Resources::set_pointer)
    prev.pointer = my_pointer;
    prev.flags |= Resources::set_pointer;
    my_pointer->restore();
    my_pointer = my_pointers->lookup(Raster::_duplicate(r));
    my_pointer->save();
    my_pointer->draw();
}

void PositionalFocus::add_filter(Input::Filter_ptr)
{
    // FIXME: not implemented
}

bool PositionalFocus::request(Controller_ptr c)
{
    return false; // not granted!
}

void PositionalFocus::restore(Region_ptr region)
{
    Vertex l, u;
    region->bounds(l, u);
    if (my_pointer->intersects(l.x, u.x, l.y, u.y)) 
    my_pointer->restore();
}

void PositionalFocus::damage(Region_ptr region)
{
    Trace trace("PositionalFocus::damage");
    Vertex l, u;
    region->bounds(l, u);
    if (my_pointer->intersects(l.x, u.x, l.y, u.y))
    {
    my_pointer->save();
    my_pointer->draw();
    }
    Prague::Guard<Mutex> guard(my_mutex);
    if (!my_grabbed) return;
    Region_var allocation = my_traversal->current_allocation();
    Transform_var transformation = my_traversal->current_transformation();
    allocation->bounds(l, u);
    transformation->transform_vertex(l);
    transformation->transform_vertex(u);
    
    Lease_var<RegionImpl> bbox(Provider<RegionImpl>::provide());

    bbox->valid = true;
    bbox->lower.x = std::min(l.x, u.x);
    bbox->lower.y = std::min(l.y, u.y);
    bbox->upper.x = std::max(l.x, u.x);
    bbox->upper.y = std::max(l.y, u.y);
    if (bbox->intersects(region)) my_traversal->update();
}

/*
 * The dispatching strategy is the following:
 * we keep a PickTraversal cached which points
 * to the controller currently holding focus.
 *
 * Dispatching means to call traverse on this
 * controller which should, if the controller
 * or one of it's children 'hits', result in
 * a memento (traversal->memento()).
 *
 * If the traversal doesn't contain a memento,
 * it means that the controller should lose
 * focus, so we start over at the parent controller...
 */
void PositionalFocus::dispatch(Input::Event &event)
{
  Prague::Guard<Mutex> guard(my_mutex);
  Trace trace("PositionalFocus::dispatch");
  Input::Position position;
  int pidx = Input::get_position(event, position);
  if (pidx == -1)
  {
      std::cerr << "PositionalFocus::dispatch error: nonpositional event"
            << std::endl;
      return;
  }
  /*
   * update the pointer object / image
   */
  my_pointer->move(position.x, position.y);
  my_traversal->pointer(position);
  if (!my_grabbed)
  {
      my_traversal->reinit();
      my_root->traverse(Traversal_var(my_traversal->_this()));
      Traversal *picked = my_traversal->memento();
      if (!picked)
      {
      std::cerr << "PositionalFocus::dispatch : no Controller found!"
                << " (position is " << position << ")" << std::endl;
      return;
      }
      else my_traversal = picked; // picked == _traversal->memento():
                                  // switching mentioned above happens here.

      should_track = false;
      if (event[0].attr._d() == Input::button)
      {
      const Input::Toggle &toggle = event[0].attr.selection();
      if (toggle.actuation == Input::Toggle::press) should_track = true;
      }
      /*
       * ...now do the [lose/receive]Focus stuff,...
       */
      std::vector<Controller_var>::const_iterator nf =
      my_traversal->controllers().begin();
      cstack_t::iterator of = my_controllers.begin();
      /*
       * ...skip the unchanged controllers,...
       */
      while (nf != my_traversal->controllers().end() &&
         of != my_controllers.end() &&
         (*nf)->is_identical(*of)) ++nf, ++of;
      /*
       * ...remove the old controllers in reverse order,...
       */
      for (cstack_t::reverse_iterator o = my_controllers.rbegin();
       o.base() != of;
       ++o)
      try
      {
          (*o)->lose_focus(device());
          Resources &prev = my_resources.top();
          if (prev.flags & Resources::set_pointer)
          {
          my_pointer->restore();
          my_pointer = prev.pointer;
          my_pointer->save();
          my_pointer->draw();
          }
          my_resources.pop();
      }
      catch (const CORBA::OBJECT_NOT_EXIST &) { }
      catch (const CORBA::COMM_FAILURE &) { }
      catch (const CORBA::TRANSIENT &) { }
      my_controllers.erase(of, my_controllers.end());
      // ...add the new controllers,...
      Focus_var my_this = _this();
      for (; nf != picked->controllers().end(); ++nf)
      {
      my_resources.push(Resources());
      (*nf)->receive_focus (my_this);
       my_controllers.push_back(*nf);
      }
  }
  // ...and finally dispatch the event

//   my_traversal->debug();
//   Transform_var(my_traversal->current_transformation())->
//   inverse_transform_vertex(position);
//   event[pidx].attr.location(position);
//   std::cout << "distributing positional event at " << position
//             << std::endl;
  try
  {
      my_controllers.back()->
      handle_positional(PickTraversal_var(my_traversal->_this()), event);
  }
  catch (const CORBA::OBJECT_NOT_EXIST &) { my_controllers.pop_back(); }
  catch (const CORBA::COMM_FAILURE &) { my_controllers.pop_back(); }
  catch (const CORBA::TRANSIENT &) { my_controllers.pop_back(); }
}
