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
#ifndef _Motif_Choice_hh
#define _Motif_Choice_hh

#include <Warsaw/config.hh>
#include <Warsaw/Choice.hh>
#include <Warsaw/CommandKit.hh>
#include <Warsaw/LayoutKit.hh>
#include <Warsaw/ToolKit.hh>
#include <Warsaw/WidgetKit.hh>
#include <Berlin/ControllerImpl.hh>
#include <vector>

namespace Motif
{

class Choice : implements(Choice), public ControllerImpl
{
  class Observer;
  friend class Observer;
  class Observer : implements(Observer)
    {
    public:
      Observer(Choice *, Controller_ptr, Tag);
      Tag tag() const { return t;}
      void update(const CORBA::Any &);
    private:
      Choice *choice;
      Controller_var item;
      bool cached;
      Tag t;
    };
  typedef vector<Tag> slist_t;
  typedef vector<Observer *> olist_t;
 public:
  Choice(Policy, CommandKit_ptr, LayoutKit_ptr, ToolKit_ptr, WidgetKit_ptr);
  virtual ~Choice();
  virtual Policy type() { return policy;}
  virtual CORBA::Long selection();
  virtual SelectionSeq *selections();
 protected:
  void appendController(Controller_ptr);
  void prependController(Controller_ptr);
  void update(Tag, bool);
  Tag tag();
  CORBA::Long index(Tag); 
//  private:
  Policy policy;
  slist_t _selections;
  olist_t observers;
//  protected:
  TelltaleConstraint_var constraint;
  CommandKit_var command;
  LayoutKit_var layout;
  ToolKit_var   tools;
  WidgetKit_var widgets;
};

class ToggleChoice : public Choice
{
 public:
  ToggleChoice(Policy, CommandKit_ptr, LayoutKit_ptr, ToolKit_ptr, WidgetKit_ptr);
  virtual void append(Graphic_ptr);
  virtual void prepend(Graphic_ptr);
  virtual void remove(Tag);
};

class CheckboxChoice : public Choice
{
 public:
  CheckboxChoice(Policy, CommandKit_ptr, LayoutKit_ptr, ToolKit_ptr, WidgetKit_ptr);
  virtual void append(Graphic_ptr);
  virtual void prepend(Graphic_ptr);
  virtual void remove(Tag);
};

};
#endif /* _Choice_hh */
