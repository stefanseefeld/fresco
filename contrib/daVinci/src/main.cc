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
#include <Prague/Sys/GetOpt.hh>
#include <Fresco/config.hh>
#include <Fresco/ToolKit.hh>
#include <Fresco/FigureKit.hh>
#include <Fresco/ImageKit.hh>
#include <Fresco/Image.hh>
#include <Fresco/UnidrawKit.hh>
#include <Fresco/DesktopKit.hh>
#include <Fresco/ClientContextImpl.hh>
#include <Fresco/resolve.hh>
#include <Fresco/IO.hh>
#include "daVinci/Models.hh"
#include "daVinci/Tools.hh"
#include "daVinci/Create.hh"
#include "daVinci/Document.hh"
#include <string>

#ifdef VERSION
const string version = VERSION;
#else
const string version = "unknown";
#endif

using namespace Prague;
using namespace Fresco;
using namespace Unidraw;
using namespace daVinci;

int main(int argc, char **argv)
{
  GetOpt getopt(argv[0], "an experimental vector drawing tool");
  getopt.add('h', "help", GetOpt::novalue, "help message");
  getopt.add('v', "version", GetOpt::novalue, "version number");
  getopt.add('l', "logging", GetOpt::novalue, "switch logging on");
  add_resolving_options_to_getopt(getopt);
  size_t argo = getopt.parse(argc, argv);
  argc -= argo;
  argv += argo;
  string value;
  getopt.get("version", &value);
  if (value == "true") { cout << "version is " << version << endl; exit(0);}
  value = "";
  getopt.get("help", &value);
  if (value == "true") { getopt.usage(); return 0;}
  try
  {
    CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);
    PortableServer::POA_var poa = 
      resolve_init<PortableServer::POA>(orb, "RootPOA");
    ServantBase::poa(poa);
    PortableServer::POAManager_var pman = poa->the_POAManager();
    pman->activate();

    Server_var s = resolve_server(getopt, orb);

    ClientContextImpl *client_impl = new ClientContextImpl("daVinci");
    ClientContext_var client = client_impl->_this();

    ServerContext_var server = s->create_server_context(client);

    FigureKit_var figures = resolve_kit<FigureKit>(server, "IDL:fresco.org/Fresco/FigureKit:1.0");
    ToolKit_var tools = resolve_kit<ToolKit>(server, "IDL:fresco.org/Fresco/ToolKit:1.0");
    ImageKit_var images = resolve_kit<ImageKit>(server, "IDL:fresco.org/Fresco/ImageKit:1.0");
    UnidrawKit_var unidraw = resolve_kit<UnidrawKit>(server, "IDL:fresco.org/Unidraw/UnidrawKit:1.0");
    DesktopKit_var desktop = resolve_kit<DesktopKit>(server, "IDL:fresco.org/Fresco/DesktopKit:1.0");

    daVinci::Model::figures(figures);
    daVinci::Model::tools(tools);
    daVinci::Model::unidraw(unidraw);
    
    daVinci::Tool *rect = new CreateTool<RectangleCreator>();
    daVinci::Tool *polygon = new CreateTool<PolygonCreator>();
    Unidraw::Tool_var select = unidraw->select_tool();
    Editor_var editor = unidraw->create_editor();
    Raster_var slabel = images->create("/data1/seefelds/projects/berlin/Berlin/contrib/daVinci/src/select.png");
    Raster_var rlabel = images->create("/data1/seefelds/projects/berlin/Berlin/contrib/daVinci/src/rectangle.png");
    //   Raster_var clabel = images->create("/data1/seefelds/projects/berlin/Berlin/contrib/daVinci/src/circle.png");
    Raster_var tlabel = images->create("/data1/seefelds/projects/berlin/Berlin/contrib/daVinci/src/triangle.png");
    Image_var simage = figures->pixmap(slabel);
    Image_var rimage = figures->pixmap(rlabel);
    //   Image_var cimage = figures->pixmap(clabel);
    Image_var timage = figures->pixmap(tlabel);
    editor->append_tool(select, simage);
    editor->append_tool(Tool_var(rect->_this()), rimage);
    //   editor->append_tool(Tool_var(circle->_this()), cimage);
    editor->append_tool(Tool_var(polygon->_this()), timage);
    editor->current_tool(Tool_var(rect->_this()));
    Controller_var viewer = editor->create_viewer(Unidraw::Model::_nil(), 3000., 3000.);
    Document::instance()->attach_view(viewer);
    Controller_var toolbar = editor->toolbar();
    
    Window_var root = desktop->shell(viewer, client);
    Window_var popup = desktop->shell(toolbar, client);
    while (true) Thread::delay(Prague::Time(1000));
  }
  catch (const CORBA::COMM_FAILURE &c)
  {
     std::cerr << "Could not connect to the display server "
               << "(CORBA::COMM_FAILURE)." << std::endl;
  }
  catch (const std::exception &e)
  {
     std::cerr << "Exception: " << e.what() << std::endl;
  }
}
