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
#ifndef _Motif_Choice_hh
#define _Motif_Choice_hh

#include <Fresco/config.hh>
#include <Fresco/Widget.hh>
#include <Fresco/Selection.hh>
#include <Fresco/CommandKit.hh>
#include <Fresco/LayoutKit.hh>
#include <Fresco/ToolKit.hh>
#include <Fresco/WidgetKit.hh>
#include <Berlin/ImplVar.hh>
#include <Berlin/ControllerImpl.hh>
#include <vector>

namespace Motif
{

class Choice : public virtual POA_Widget::Choice,
	       public ControllerImpl
{
 public:
  Choice(Fresco::Selection_ptr, Fresco::LayoutKit_ptr, Fresco::ToolKit_ptr, Fresco::WidgetKit_ptr);
  virtual ~Choice();
  virtual Fresco::Selection_ptr state();
  virtual Fresco::Tag append_item(Fresco::Graphic_ptr) = 0;
  virtual Fresco::Tag prepend_item(Fresco::Graphic_ptr) = 0;
  virtual void remove_item(Fresco::Tag) = 0;
 protected:
  RefCount_var<Fresco::Selection> selection;
  RefCount_var<Fresco::LayoutKit> layout;
  RefCount_var<Fresco::ToolKit>   tools;
  RefCount_var<Fresco::WidgetKit> widgets;
};

class ToggleChoice : public Choice
{
 public:
  ToggleChoice(Fresco::Selection_ptr, Fresco::LayoutKit_ptr, Fresco::ToolKit_ptr, Fresco::WidgetKit_ptr);
  virtual Fresco::Tag append_item(Fresco::Graphic_ptr);
  virtual Fresco::Tag prepend_item(Fresco::Graphic_ptr);
  void remove_item(Fresco::Tag);
 private:
  RefCount_var<Fresco::Graphic> create_item(Fresco::Graphic_ptr, Fresco::Tag &);
};

class CheckboxChoice : public Choice
{
 public:
  CheckboxChoice(Fresco::Selection_ptr, Fresco::LayoutKit_ptr, Fresco::ToolKit_ptr, Fresco::WidgetKit_ptr);
  virtual Fresco::Tag append_item(Fresco::Graphic_ptr);
  virtual Fresco::Tag prepend_item(Fresco::Graphic_ptr);
  void remove_item(Fresco::Tag);
 private:
  RefCount_var<Fresco::Graphic> create_item(Fresco::Graphic_ptr, Fresco::Tag &);
};

class ToolChoice : public Choice
{
 public:
  ToolChoice(Fresco::Selection_ptr, Fresco::LayoutKit_ptr, Fresco::ToolKit_ptr, Fresco::WidgetKit_ptr);
  virtual Fresco::Tag append_item(Fresco::Graphic_ptr);
  virtual Fresco::Tag prepend_item(Fresco::Graphic_ptr);
  void remove_item(Fresco::Tag);
};

};
#endif
