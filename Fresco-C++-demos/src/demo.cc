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

#include "Warsaw/Warsaw.hh"
#include "Application.hh"
#include "LayoutDemo.hh"
#include "TextDemo.hh"
#include "EditTextDemo.hh"
#include "RasterDemo.hh"
#include "ColorDemo.hh"
#include "LogoDemo.hh"
#include "FocusDemo.hh"
#include "ViewportDemo.hh"
#include "DocDemo.hh"
#include "TermDemo.hh"

using namespace Prague;

bool running;

int main(int argc, char **argv)
{
  Warsaw *warsaw = new Warsaw(argc, argv);
  Application *application = new Application(warsaw);
  LayoutDemo *layout = new LayoutDemo(application);
  TextDemo *text = new TextDemo(application);
  EditTextDemo *etext = new EditTextDemo(application);
  RasterDemo *raster = new RasterDemo(application);
  ColorDemo *color = new ColorDemo(application);
  LogoDemo *logo = new LogoDemo(application);
  FocusDemo *focus = new FocusDemo(application);
  ViewportDemo *viewport = new ViewportDemo(application);
  DocDemo *document = new DocDemo(application);
  TermDemo *terminal = new TermDemo(application);
  application->run();
  delete terminal;
  delete document;
  delete viewport;
  delete focus;
  delete logo;
  delete color;
  delete raster;
  delete etext;
  delete text;
  delete layout;
  delete application;
  delete warsaw;
}
