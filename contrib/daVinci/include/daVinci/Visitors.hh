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
#ifndef _daVinci_Visitors_hh
#define _daVinci_Visitors_hh

#include <Fresco/config.hh>
#include <Fresco/Graphic.hh>

namespace daVinci
{

class Command;
class ManipList;

class Visitor
{
public:
  Visitor();
  virtual ~Visitor();
  virtual bool visit(Graphic_ptr);
  virtual void visit_children(Graphic_ptr);
};

class Appender : public Visitor
{
public:
  Appender(Graphic_ptr, bool resize = true);
  virtual ~Appender();
  virtual bool visit(Graphic_ptr);
private:
  Graphic_var _graphic;
  bool        _resize;
};

class Remover : public Visitor
{
public:
  Remover();
  virtual ~Remover();
  virtual bool visit(Graphic_ptr);
private:
//   GlyphOffsetList list_;
};

class Counter : public Visitor
{
public:
  Counter();
  virtual bool visit(Graphic_ptr);
  CORBA::ULong count() { return _count;}
private:
  CORBA::ULong _count;
};

class CmdVisitor : public Visitor
{
public:
  CmdVisitor(Command *, bool execute = true);
  ~CmdVisitor();
  bool visit(Graphic_ptr);
protected:
  Command *_command;
  bool     _execute;
};

class RecurCmdVisitor : public Visitor
{
public:
  RecurCmdVisitor(FCommand* cmd, bool execute = true);
  ~RecurCmdVisitor();
  bool visit(Graphic_ptr);
  void recur_visit_children(Graphic_ptr);
protected:
  Command *_command;
  bool     _execute;
};

class ManipCopier : public Visitor
{
public:
  typedef vector<Manipulator *> mlist_t;
  ManipCopier(bool shallow = true);
  ~ManipCopier();
  bool visit(Graphic_ptr);
  *manipulators() { return _manipulators;}
private:
  mlist_t _manipulators;
  bool    _shallow;
};

class TAManipCopier : public ManipCopier
{
public:
  typedef vector<Region_var> alist_t;
  typedef vector<Transform_var> tlist_t;
  TAManipCopier(Region_ptr allocation, bool shallow = true);
  ~TAManipCopier();
  
  bool visit(Graphic_ptr);

  alist_t allocations() { return _allocations;}
  tlist_t transforms() { return _transforms;}
private:
  AllocationList *_allocations;
  TransformList  *_transforms;
  Region_ptr      _allocation;
};

class OffsetVisitor : public Visitor
{
public:
  OffsetVisitor();
  ~OffsetVisitor();
  
  bool visit(Glyph_ptr, GlyphOffset_ptr);
  GlyphOffset_ptr offset(CORBA::ULong);
  CORBA::ULong offset_count();
protected:
  GlyphOffsetList* glist_;
};

class Inserter : public Visitor
{
public:
  Inserter(vector<Manipulator *> &);
  bool visit(Graphic_ptr);
private:
  vector<Manipulator *> _manipulators;
};

#endif
