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
#ifndef _Berlin_ControllerImpl_hh
#define _Berlin_ControllerImpl_hh

#include <Prague/Sys/Thread.hh>
#include <Prague/Sys/Tracer.hh>
#include <Fresco/config.hh>
#include <Fresco/Controller.hh>
#include <Fresco/Input.hh>
#include <Fresco/DrawTraversal.hh>
#include <Fresco/PickTraversal.hh>
#include <Berlin/SubjectImpl.hh>
#include <Berlin/MonoGraphic.hh>
#include <Berlin/RefCountVar.hh>
#include <vector>

namespace Berlin
{

  class ControllerImpl : public virtual POA_Fresco::Controller,
             public MonoGraphic,
             public SubjectImpl
  {
      typedef std::vector<RefCount_var<Fresco::Controller> > clist_t;
      class Iterator;
      friend class Iterator;
    public:
      ControllerImpl(bool);
      virtual ~ControllerImpl();
      virtual void deactivate();
      
      virtual void traverse(Fresco::Traversal_ptr);
      virtual void draw(Fresco::DrawTraversal_ptr);
      virtual void pick(Fresco::PickTraversal_ptr);

      virtual void append_controller(Fresco::Controller_ptr);
      virtual void prepend_controller(Fresco::Controller_ptr);
      virtual void remove_controller(Fresco::Controller_ptr);
      virtual void set_parent_controller(Fresco::Controller_ptr);
      virtual void remove_parent_controller();

      virtual Fresco::Controller_ptr parent_controller();
      virtual Fresco::ControllerIterator_ptr first_child_controller();
      virtual Fresco::ControllerIterator_ptr last_child_controller();

      virtual CORBA::Boolean request_focus(Fresco::Controller_ptr,
                       Fresco::Input::Device);
      virtual CORBA::Boolean receive_focus(Fresco::Focus_ptr);
      virtual void lose_focus(Fresco::Input::Device);
      
      virtual CORBA::Boolean first_focus(Fresco::Input::Device);
      virtual CORBA::Boolean last_focus(Fresco::Input::Device);
      virtual CORBA::Boolean next_focus(Fresco::Input::Device);
      virtual CORBA::Boolean prev_focus(Fresco::Input::Device);
      virtual CORBA::Boolean handle_positional(Fresco::PickTraversal_ptr,
                           const Fresco::Input::Event &);
      virtual CORBA::Boolean
      handle_non_positional(const Fresco::Input::Event &);

      virtual void set(Fresco::Telltale::Mask);
      virtual void clear(Fresco::Telltale::Mask);
      virtual CORBA::Boolean test(Fresco::Telltale::Mask);
      virtual void modify(Fresco::Telltale::Mask, CORBA::Boolean);
      virtual void constraint(Fresco::TelltaleConstraint_ptr);
      virtual Fresco::TelltaleConstraint_ptr constraint();
    protected:
      virtual bool inside(Fresco::PickTraversal_ptr);
      virtual void move(Fresco::PickTraversal_ptr,
            const Fresco::Input::Event &);
      virtual void press(Fresco::PickTraversal_ptr,
             const Fresco::Input::Event &);
      virtual void drag(Fresco::PickTraversal_ptr,
            const Fresco::Input::Event &);
      virtual void release(Fresco::PickTraversal_ptr,
               const Fresco::Input::Event &);
      virtual void double_click(Fresco::PickTraversal_ptr,
                const Fresco::Input::Event &);
      virtual void key_press(const Fresco::Input::Event &);
      virtual void key_release(const Fresco::Input::Event &);
      virtual void other(const Fresco::Input::Event &);
      void grab(Fresco::PickTraversal_ptr);
      void ungrab(Fresco::PickTraversal_ptr);
      bool grabbed(Fresco::Input::Device d) { return my_grabs & (1 << d); }
      void set_focus(Fresco::Input::Device d)
      { my_focus |= 1 << d; update_state(); }
      void clear_focus(Fresco::Input::Device d)
      { my_focus &= ~(1 << d); update_state(); }
      bool have_focus(Fresco::Input::Device d) { return my_focus & (1 << d); }
      virtual void update_state();
    private:
      Fresco::Controller_var         my_parent;
      clist_t                        my_children;
      CORBA::ULong                   my_telltale;
      CORBA::ULong                   my_focus;
      CORBA::ULong                   my_grabs;
      bool                           my_transparent;
      Fresco::TelltaleConstraint_var my_constraint;
      Prague::Mutex                  my_pmutex; // for the parent link
      Prague::Mutex                  my_cmutex; // for the children links
      Prague::Mutex                  my_mutex;  // for the state
  };

} // namespace

#endif 
