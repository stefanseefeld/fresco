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
#include <Warsaw/Selection.hh>
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
  class State;
 public:
  Choice(Selection::Policy, CommandKit_ptr, LayoutKit_ptr, ToolKit_ptr, WidgetKit_ptr);
  virtual ~Choice();
  virtual Selection_ptr state();
  virtual Tag appendItem(Graphic_ptr) = 0;
  virtual Tag prependItem(Graphic_ptr) = 0;
  void removeItem(Tag) = 0;
 protected:
  State *_state;
  LayoutKit_var layout;
  ToolKit_var   tools;
  WidgetKit_var widgets;
};

class ToggleChoice : public Choice
{
 public:
  ToggleChoice(Selection::Policy, CommandKit_ptr, LayoutKit_ptr, ToolKit_ptr, WidgetKit_ptr);
  virtual Tag appendItem(Graphic_ptr);
  virtual Tag prependItem(Graphic_ptr);
  void removeItem(Tag);
};

class CheckboxChoice : public Choice
{
 public:
  CheckboxChoice(Selection::Policy, CommandKit_ptr, LayoutKit_ptr, ToolKit_ptr, WidgetKit_ptr);
  virtual Tag appendItem(Graphic_ptr);
  virtual Tag prependItem(Graphic_ptr);
  void removeItem(Tag);
};

};
#endif /* _Choice_hh */