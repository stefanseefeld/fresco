/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 2002 Neil Pilgrim <neiljp@fresco.org> 
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

#include "Fresco/resolve.hh"

#include <Prague/Sys/GetOpt.hh>
#include <Server.hh>
#include <Fresco/resolve.hh>
#include <fstream>
#include <iostream>

static std::string const default_reference_import_method("nameserver");

Fresco::Server_ptr resolve_server(int argc, char *argv[], CORBA::ORB_ptr orb)
{
  // XXX Does not pass through the '-h' option if the client already uses it
  Prague::GetOpt getopt(argv[0], "fresco client");
  getopt.add('h', "help", Prague::GetOpt::novalue, "help message");
  getopt.add('I', "ior-file-path", Prague::GetOpt::mandatory,
             "location where server (CORBA) locations are published. "
             "Use stdin to input stringified ior from console");
  getopt.add('R', "export-ref", Prague::GetOpt::mandatory,
             "means of exporting server reference[ior|corbaloc|nameserver] "
             "Default is 'ior'");
  size_t argo = getopt.parse(argc, argv);
  argc -= argo;
  argv += argo;

  if (getopt.is_set('h'))
  {
    getopt.usage();
    exit(0);
  }

  // Determine method of importing server reference
  // Use a variable rather than checking against the value in "export-ref"
  // since this allows a default method, plus ensures that the value is valid
  std::string reference_import_method(default_reference_import_method);
  if (getopt.is_set("export-ref"))
  {
    getopt.get("export-ref", &reference_import_method);
    if ( (reference_import_method != "ior") &&
         (reference_import_method != "corbaloc") &&
         (reference_import_method != "nameserver") )
    {
      std::cerr << "ERROR: "
                << "Invalid method for importing server reference given.\n"
                << "'" << reference_import_method << "' is not one of\n"
                << "'ior', 'corbaloc' or 'nameserver'" << endl;
      exit(1);
    }
  }

  Fresco::Server_var server = Fresco::Server::_nil();

  // nameserver
  if (reference_import_method == "nameserver")
  {
    CosNaming::NamingContext_var context;
    try
    {
      context = resolve_init<CosNaming::NamingContext>(orb, "NameService");
    }
    catch (...)
    {
      std::cerr << "ERROR: "
                << "Could not contact nameserver; check it is running."
                << endl;
      exit(1);
    }
    try
    {
      server = resolve_name<Fresco::Server>(context, 
                                     "IDL:fresco.org/Fresco/Server:1.0");
    }
    catch (...)
    {
      std::cerr << "ERROR: "
                << "Nameservice found, but could not locate server\n"
                << "in the nameservice. Did you specify the \"nameserver\"\n"
                << "parameter to the -R option when starting the server?\n"
                << "If not, then you need not specify it here."
                << endl;
      exit(1);
    }
  }

  // ior
  if (reference_import_method == "ior")
  {
    // Determine server-id to use
    std::string server_id("server_ior"); // default server-id

    // Determine directory in which ior is saved ("ior" method only)
    std::string ior_file_path("/tmp/fresco/"); // default path
    // XXX Ideally the default path is stored in *one* place, maybe libfresco
    if (getopt.is_set("ior-file-path"))
    {
      getopt.get("ior-file-path", &ior_file_path);
      if ((ior_file_path != "stdin") &&
          (ior_file_path[ior_file_path.length()-1] != '/')) 
        ior_file_path += '/';
    }

    // Find the ior-string
    std::string ior_string;
    if (ior_file_path == "stdin")
    {
      unsigned IOR_position;
      do{
        std::cin >> ior_string;
        IOR_position = ior_string.find("IOR:");
      }while (IOR_position == std::string::npos);
      ior_string = ior_string.substr(IOR_position,ior_string.size());
    }
    else
    {
      std::string full_path(ior_file_path);
      full_path += server_id;
      std::ifstream ifs(full_path.c_str());
      if (ifs.is_open())
      {
        ifs >> ior_string;
      }
      else
      {
        std::cerr << endl
                  << "ERROR: Cannot open '" << full_path << "'\n" 
                  << "This could signify that the server is not running\n"
                  << "or that a server is running but with a different\n"
                  << "-I option parameter. If the latter, use the same\n"
                  << "option with this client as with the server.\n"
                  << "This could also signify that a server is running but\n"
                  << "its address is being published using another method -\n"
                  << "try the -R option."
                  << endl;
        exit(1);
      }
    }

    // Check that the ior-string is valid
    CORBA::Object_var obj;
    try
    { 
      obj = orb->string_to_object(ior_string.c_str());
      server = Fresco::Server::_narrow(obj);
      if (CORBA::is_nil(server)) throw;
    }
    catch (...)
    { 
      std::cerr << endl
                << "ERROR: Server reference is invalid." << endl;
      exit(1);
    }

  }

  // corbaloc
  if (reference_import_method == "corbaloc")
  {
    std::cerr << "ERROR: corbaloc method not completed in clients" << endl;
    exit(1);
  }
  
  // Check that the server can be contacted
  // (maybe the reference refers to a non-running server)
  bool server_can_be_contacted = true;
  try
  { 
    if (server->_non_existent()) server_can_be_contacted = false;
  }
  catch (CORBA::COMM_FAILURE const &)
  { 
    server_can_be_contacted = false;
  }
  catch (CORBA::TRANSIENT const &)
  { 
    server_can_be_contacted = false;
  }
  catch (...)
  { 
    server_can_be_contacted = false;
  }

  if (!server_can_be_contacted)
  { 
    std::cerr << endl
              << "ERROR: Server reference is valid, "
              << "but this server cannot be contacted.\n"
              << "This server may have terminated or is suspended.\n"
              << "If this is the case, restart or resume the server and try again.\n"
              << "Alternatively the most recent valid server reference\n"
              << "may have been published using a different method or\n"
              << "in a different place - if this is the case, try using\n"
              << "different parameters to the -R or -I options."
              << endl;
    exit(1);
  }
  return server._retn();
}
