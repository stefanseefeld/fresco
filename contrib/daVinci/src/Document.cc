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
#include "daVinci/Document.hh"

using namespace Prague;
using namespace Fresco;
using namespace Unidraw;

static Mutex mutex;

namespace daVinci
{
Document *Document::_document = 0;

Document *Document::instance()
{
  Guard<Mutex> guard(mutex);
  if (!_document) _document = new Document();
  return _document;
}

Unidraw::View_ptr Document::create_view()
{
  return Unidraw::View::_nil();
}

void Document::attach_view(Graphic_ptr view)
{
  _views.push_back(Graphic::_duplicate(view));
  Graphic_var body = view->body();
}

void Document::append_model(Model *model)
{
  _models.push_back(model);
  for (vlist_t::iterator i = _views.begin(); i != _views.end(); ++i)
    {
      Graphic_var view = model->create_view();
      (*i)->append_graphic(view);
    }
}

};
