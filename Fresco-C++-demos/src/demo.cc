 /*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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

#include "Warsaw/config.hh"
#include "Warsaw/resolve.hh"
#include "Warsaw/Server.hh"
#include "Application.hh"
#include "LayoutDemo.hh"
#include "TextDemo.hh"
#include "EditTextDemo.hh"
#include "RasterDemo.hh"
#include "TransformDemo.hh"
#include "LogoDemo.hh"
#include "FocusDemo.hh"
#include "ViewportDemo.hh"
#include "DocDemo.hh"

using namespace Prague;

bool running;

int main(int argc, char **argv)
{
  CORBA::ORB_ptr orb = CORBA::ORB_init(argc,argv,"omniORB2");
  CORBA::BOA_ptr boa = orb->BOA_init(argc,argv,"omniORB2_BOA");
  boa->impl_is_ready(0,1);

  CosNaming::NamingContext_var context = resolve_init<CosNaming::NamingContext>(orb, "NameService");
  Server_var server = resolve_name<Server>(context, interface(Server));
  Application *application = new Application(server);
  LayoutDemo *layout = new LayoutDemo(application);
  TextDemo *text = new TextDemo(application);
  EditTextDemo *etext = new EditTextDemo(application);
  RasterDemo *raster = new RasterDemo(application);
  TransformDemo *transform = new TransformDemo(application);
  LogoDemo *logo = new LogoDemo(application);
  FocusDemo *focus = new FocusDemo(application);
  ViewportDemo *viewport = new ViewportDemo(application);
  DocDemo *document = new DocDemo(application);
  application->run();
  delete document;
  delete viewport;
  delete focus;
  delete logo;
  delete transform;
  delete raster;
  delete etext;
  delete text;
  delete layout;
  delete application;
}
