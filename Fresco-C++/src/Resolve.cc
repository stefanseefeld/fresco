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

#include <Prague/Sys/GetOpt.hh>
#include <Server.hh>
#include <Fresco/resolve.hh>
#include <fstream>
#include <iostream>
#include <sys/stat.h> // XXX use prague instead
#include <errno.h>    // XXX use prague instead
#include <Prague/Sys/Env.hh>

// ---------------------------------------------------------------
// Internals
// ---------------------------------------------------------------

// Internal defaults for server-publishing
static std::string const my_default_reference_transfer_method("nameserver");
static std::string const my_default_ior_file_path("/tmp/fresco/");
static std::string const my_default_server_id("FrescoServer");

// Internal stored data for server-publishing
static std::string reference_export_method(my_default_reference_transfer_method);
static PortableServer::POA_var insPOA; // poa for corbaloc use


// Internal method to validate reference_transfer_method's
bool is_valid_reference_transfer_method(std::string transfer_method)
{
  if ( (transfer_method != "ior") &&
       (transfer_method != "corbaloc") &&
       (transfer_method != "nameserver") )
  {
    std::cerr << "ERROR: Invalid method for exporting server reference given." 
              << std::endl << "'" << transfer_method << "' is not one of" 
              << std::endl << "'ior', 'corbaloc' or 'nameserver'" << std::endl;
    return false;
  }
  return true;
}

// Internal method to check if a server can be contacted
// (maybe the reference refers to a non-running server)
bool server_can_be_contacted(Fresco::Server_ptr server)
{
  bool server_can_be_contacted_ = true;
  try
  { 
    if (server->_non_existent()) server_can_be_contacted_ = false;
  }
  catch (CORBA::COMM_FAILURE const &)
  { 
    server_can_be_contacted_ = false;
  }
  catch (CORBA::TRANSIENT const &)
  { 
    server_can_be_contacted_ = false;
  }
  catch (...)
  { 
    server_can_be_contacted_ = false;
  }
  return server_can_be_contacted_;
}

// -----------------------------------------------------------------------------
// How to find default settings for server-reference transfer
// -----------------------------------------------------------------------------
char const * default_reference_transfer_method()
{
  return my_default_reference_transfer_method.c_str();
}
char const * default_server_id()
{
  return my_default_server_id.c_str();
}
char const * default_ior_file_path()
{
  return my_default_ior_file_path.c_str();
}

// -----------------------------------------------------------------------------
// Function for resolving a server
// -----------------------------------------------------------------------------
Fresco::Server_ptr resolve_server(std::string server_id,
                                  std::string reference_transfer_method,
                                  std::string ior_file_path,
                                  CORBA::ORB_ptr orb)
{
  Fresco::Server_var server;

  std::string stringified_ior("");
  if (server_id=="" && reference_transfer_method=="" && ior_file_path=="")
  {
    // if can find environment variable, load using that
    stringified_ior = Prague::getenv("FRESCO_DISPLAY");
  }

  // Set defaults
  if (server_id=="") server_id = default_server_id();
  if (reference_transfer_method=="") 
          reference_transfer_method = default_reference_transfer_method();
  if (ior_file_path=="") ior_file_path = default_ior_file_path();

  // Validate reference_transfer_method
  // NOTE: Should always check this first, to avoid user getting confused
  //       and thinking that some values are valid when they aren't
  if (!is_valid_reference_transfer_method(reference_transfer_method))
  {
    exit(1);
  }
  
  CORBA::Object_var obj;
  if (stringified_ior!="")
  try
  { 
      obj = orb->string_to_object(stringified_ior.c_str());
      server = Fresco::Server::_narrow(obj);
      if (CORBA::is_nil(server)) throw;
      if (!server_can_be_contacted(server)) throw;
      return server._retn();
  }
  catch (...)
  { 
    std::cerr << std::endl
              << "WARNING: Server reference from environment-variable "
              << "is invalid." << std::endl
              << "Trying other methods." << std::endl;
  }

  // Check through all non-env-var export methods
  if (reference_transfer_method == "ior")
  {
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
      // Fix form of ior_file_path (append '/' if necessary)
      // NOTE: length() should be >0 since if ==0 we set it to the default above
      if (ior_file_path[ior_file_path.length()-1] != '/') ior_file_path += '/';

      std::string full_path(ior_file_path);
      full_path += server_id;
      std::ifstream ifs(full_path.c_str());
      if (ifs.is_open())
      {
        ifs >> ior_string;
      }
      else
      {
        std::cerr << "ERROR: Cannot open '" << full_path << "'"  << std::endl
                  << "This could signify that the server is not running "
                  << "or that a server is running" << std::endl
                  << "but with a different -I option parameter. If the latter, "
                  << "use the same option" << std::endl
                  << "with this client as with the server." << std::endl
                  << "This could also signify that a server is running but "
                  << "its address is being" << std::endl
                  << "published using another method; try the -R option."
                  << std::endl;
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
      std::cerr << "ERROR: Server reference is invalid." << std::endl;
      exit(1);
    }

  }
  else if (reference_transfer_method == "nameserver")
  {
    CosNaming::NamingContext_var context;
    try
    {
      context = resolve_init<CosNaming::NamingContext>(orb, "NameService");
    }
    catch (...)
    {
      std::cerr << "ERROR: Could not contact nameserver; check it is running."
                << std::endl;
      exit(1);
    }
    try
    {
      server = resolve_name<Fresco::Server>(context, server_id.c_str());
    }
    catch (...)
    {
      std::cerr << "ERROR: Nameservice found, but could not locate server in "
                << "the" << std::endl << "nameservice. The server location may "
                << "have been published using a" << std::endl << "different "
                << "mechanism (see the --export-ref option) or the name given "
                << "to" << std::endl << "the server might have been different "
                << "from '" << server_id << "' (see the " << std::endl
                << "--server-id option)" << std::endl;
      exit(1);
    }
  }
  else if (reference_transfer_method == "corbaloc")
  {
    std::cerr << "ERROR: corbaloc method not yet implemented" << std::endl
              << "See http://issues.fresco.org/bug57" << std::endl;
    exit(1);
  }
  
  if (!server_can_be_contacted(server))
  { 
    std::cerr << "ERROR: Server reference is valid, "
              << "but this server cannot be contacted." << std::endl
              << "This server may have terminated or is suspended." << std::endl
              << "If this is the case, restart or resume the server and "
              << "try again." << std::endl
              << "Alternatively the most recent valid server reference "
              << "may have been published" << std::endl
              << "using a different method, in a different place or under "
              << "another name." << std::endl
              << "If this is the case, try using different paramters to the "
              << "-R, -I or -i options."
              << std::endl;
    exit(1);
  }
  return server._retn();
}

// ---------------------------------------------------------------
// Functions to publish a server (typically called in order)
// ---------------------------------------------------------------

// check export_method is valid, and set it
void set_server_reference_export_method(std::string export_method)
{
  if (is_valid_reference_transfer_method(export_method))
  {
    reference_export_method = export_method;
  }
  else exit(1); // diagnostic message is produced in 'is_valid_ref...'
}

// get poa to use for creating server
PortableServer::POA_ptr get_server_poa(CORBA::ORB_ptr orb,
                                       PortableServer::POA_ptr default_poa)
{
  if ("corbaloc"==reference_export_method)
  {
    insPOA = resolve_init<PortableServer::POA>(orb,"omniINSPOA");
    PortableServer::POAManager_var poam = insPOA->the_POAManager();
    poam->activate();
    return PortableServer::POA::_duplicate(insPOA);
  }
  else
  {
    return default_poa;
  }
}

// publish server reference
void publish_server(Fresco::Server_ptr server,
                    std::string exported_server_id,
                    std::string ior_file_path,
                    CORBA::ORB_ptr orb)
{
  if (exported_server_id=="") { exported_server_id = default_server_id(); }
  if (ior_file_path=="") { ior_file_path = default_ior_file_path(); }

  // Check through all export methods
  if (reference_export_method == "ior")
  {
    if (ior_file_path == "stdout")
    {
      CORBA::String_var s = orb->object_to_string(server);
      std::cout << "Export Reference:" << std::endl
                << exported_server_id << "= " << s << std::endl;
    }
    else
    {
      if (ior_file_path[ior_file_path.length()-1] != '/')
      {
        ior_file_path += '/';
      }

      std::string full_path(ior_file_path);
      full_path += exported_server_id;
      std::ifstream ifs(full_path.c_str());
      bool server_id_file_available = false;
      if (ifs.is_open())
      {
        std::string ior;
        ifs >> ior;
        CORBA::Object_var obj;
        try
        {
          obj = orb->string_to_object(ior.c_str());
        }
        catch(...)
        {
          // => ior is not a valid IOR
          // It cannot be used to contact a server, so it may as
          // well be reused
          std::cerr << std::endl << "WARNING: id is invalid" << std::endl;
          server_id_file_available = true;
        }
        if (CORBA::is_nil(obj)) server_id_file_available = true;
        else
        try
        {
          if (obj->_non_existent()) server_id_file_available = true;
        }
        catch (CORBA::TRANSIENT const &)
        {
          // Could not decide if object exists; assume it doesn't
          server_id_file_available = true;
          std::cerr << std::endl << 
                  "WARNING: id might exist (TRANSIENT)" << std::endl;
        }
        catch (CORBA::COMM_FAILURE const &)
        {
          // Could not decide if object exists; assume it doesn't
          server_id_file_available = true;
          std::cerr << std::endl <<
                  "WARNING: id might exist (COMM_FAILURE)" << std::endl;
        }
        catch (...)
        {
          server_id_file_available = false;
        }
        ifs.close();
        if (server_id_file_available)
        {
          std::cerr << std::endl << "WARNING: Overwriting stale server-id [" 
                    << exported_server_id << "]" << std::endl;
        }

      }
      else
      {
        server_id_file_available = true;
      }

      // If server-id is unavailable
      if (!server_id_file_available)
      {
        std::cerr << std::endl
                  << "ERROR: A server corresponding to '" << full_path
                  << "' appears to already be running." << std::endl
                  << "If you are sure the server has crashed, "
                  << "remove '" << full_path
                  << "' and run the server again." << std::endl
                  << "Alternatively specify a different path "
                  << "using the -I option."
                  << std::endl;
        exit(1);
      }

      // Create/update the ior in the file
      if ((mkdir(ior_file_path.c_str(),0777) != 0) && (errno != EEXIST))
      {
        // TODO Include more error checking for the user here
        std::cerr << "ERROR: Could not create directory '"
                  << ior_file_path << "' to store ior" << std::endl
                  << "Check the access permissions or try specifying a "
                  << "different directory " << std::endl
                  << "with the -I option."
                  << std::endl;
        exit(1);
      }
      std::ofstream ofs(full_path.c_str());
      if (ofs.is_open())
      {
        CORBA::String_var s = orb->object_to_string(server);
        ofs << s << std::endl;
      }
      else
      {
        std::cerr << "ERROR: Could not open file '"
                  << full_path << "' to save ior" << std::endl
                  << "Check the access permissions for file creation"
                  << "in the '" << ior_file_path << "'" << std::endl
                  << "directory or try specifying a different directory "
                  << "using --ior-file-path."
                  << std::endl;
        exit(1);
      }
    }
  }
  else if (reference_export_method == "nameserver")
  {
    try
    {
       bind_name(orb, server, exported_server_id.c_str());
    }
    catch (CORBA::COMM_FAILURE)
    {
      std::cerr << "ERROR: Could not publish server in nameserver; "
                << "make certain that the nameservice is is running."
                << std::endl;
      exit(1);
    }
    catch (...)
    {
      std::cerr << "ERROR: Unknown exception when publishing reference " 
                << "in nameserver." << std::endl;
      exit(1);
    }
  }
  else if (reference_export_method == "corbaloc")
  { // not fully implemented, and activate_object_with_id doesn't work when
    // within this function; will need doing outside of here
#if 0
    PortableServer::ObjectId_var oid =
       PortableServer::string_to_ObjectId("FrescoServer");
    insPOA->activate_object_with_id(oid,server);

    // TODO: Look for host name here
    std::cout << "Export Reference: FrescoServer="
              << "corbaloc::localhost/FrescoServer" << std::endl;
#endif
  }

  // Reference is published externally, now publish in environment
  CORBA::String_var const s = orb->object_to_string(server);
  std::string const stringified_ior(s);
  Prague::putenv("FRESCO_DISPLAY", stringified_ior);
}
// ---------------------------------------------------------------
// Helpers if using external Prague::GetOpt
// ---------------------------------------------------------------

// Internal method to parse getopt entries
void parse_getopt_for_resolve_options(Prague::GetOpt const &getopt,
                                      std::string &server_id,
                                      std::string &reference_transfer_method,
                                      std::string &ior_file_path)
{
  // Determine server-id to use
  server_id = ""; // default server-id
  if (getopt.is_set("server-id"))
  {
    getopt.get("server-id", &server_id);
  }
 
  // Determine method of importing server reference
  // Use a variable rather than checking against the value in "export-ref"
  // since this allows a default method, plus ensures that the value is valid
  bool allow_I;
  reference_transfer_method = ""; // signifying default
  if (getopt.is_set("export-ref"))
  {
    getopt.get("export-ref", &reference_transfer_method);
    if (reference_transfer_method == "ior") allow_I = true;
    else allow_I = false;
  }
  else
  {
    if (my_default_reference_transfer_method == "ior") allow_I = true;
    else allow_I = false;
  }
 
  if (allow_I) ior_file_path = my_default_ior_file_path;
  else         ior_file_path = "";

  // Determine directory in which ior is saved ("ior" method only)
  if (getopt.is_set("ior-file-path"))
  {
    if (!allow_I)
    {
      std::cerr << std::endl
                << "WARNING: Path for ior to be published has been specified "
                << "but the" << std::endl << "method of publishing is not the "
                << "filesystem. The --ior-file-path option" << std::endl
                << "will be ignored." << std::endl;
    }
    else
    {
      getopt.get("ior-file-path", &ior_file_path);
    }
  }
}

// add options to getopt
void add_resolving_options_to_getopt(Prague::GetOpt &getopt)
{
  {
    std::string export_ref_text =
         "Reference export method: ior|corbaloc|nameserver "
         "(default: ";
    export_ref_text += my_default_reference_transfer_method;
    export_ref_text += ")";
    getopt.add('R', "export-ref", Prague::GetOpt::mandatory, export_ref_text);
  }
  getopt.add('I', "ior-file-path", Prague::GetOpt::mandatory,
             "location where server (CORBA) locations are published. "
             "Use stdin to input stringified ior from console");
  {
    std::string server_id_text = "name to give server (default: ";
    server_id_text += my_default_server_id;
    server_id_text += ")";
    getopt.add('i', "server-id", Prague::GetOpt::mandatory, server_id_text);
  }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// resolve server by parsing getopt
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Fresco::Server_ptr resolve_server(Prague::GetOpt const &getopt, 
                                  CORBA::ORB_ptr orb)
{
  std::string server_id, reference_transfer_method, ior_file_path;
  parse_getopt_for_resolve_options(getopt, server_id, reference_transfer_method,
                                   ior_file_path);
  return resolve_server(server_id, reference_transfer_method, 
                        ior_file_path, orb);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// publish server by parsing getopt
// NOTE: call set_server_reference_export_method and get_server_poa as with
//       non-getopt publish_server variant
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void publish_server(Fresco::Server_ptr server,
                    Prague::GetOpt const &getopt,
                    CORBA::ORB_ptr orb)
{
  std::string server_id, dummy_method, ior_file_path;
  parse_getopt_for_resolve_options(getopt, server_id, dummy_method,
                                   ior_file_path);
  publish_server(server, server_id, ior_file_path, orb);
}
