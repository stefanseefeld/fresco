/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@berlin-consortium.org> 
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
#ifndef _MainControllerImpl_hh
#define _MainControllerImpl_hh

#include <Warsaw/config.hh>
#include <Warsaw/Raster.hh>
#include <Warsaw/MainController.hh>
#include <Berlin/ControllerImpl.hh>
#include <Berlin/RefCountVar.hh>

class MainControllerImpl : public virtual POA_Warsaw::MainController,
			   public ControllerImpl
{
 public:
  MainControllerImpl(bool);
  virtual ~MainControllerImpl();
  virtual void cursor(Warsaw::Raster_ptr);
  virtual Warsaw::Raster_ptr cursor();

  virtual CORBA::Boolean receive_focus(Warsaw::Focus_ptr f);
 private:
  Prague::Mutex      _mutex;
  Warsaw::Raster_var _cursor;
};

#endif
