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
#ifndef _daVinci_Document_hh
#define _daVinci_Document_hh

#include <Fresco/config.hh>
#include <Fresco/Subject.hh>
#include <Fresco/UnidrawKit.hh>
#include <daVinci/RefCountBase.hh>
#include <vector>

namespace daVinci
{

class Document : public virtual POA_Unidraw::Model,
		 public virtual RefCountBase
{
  typedef std::vector<Model *> mlist_t;
  typedef std::vector<Fresco::Graphic_var> vlist_t;
public:
  // make it a singleton for now...
  static Document *instance();
  virtual Unidraw::View_ptr create_view();
  void attach_view(Fresco::Graphic_ptr);
  void append_model(Model *);
private:
  vlist_t          _views;
  mlist_t          _models;
  static Document *_document;
};
};

#endif
