#
# This source file is a part of the Fresco Project.
# Copyright (C) 2000 by Stephen Davies
# http://www.fresco.org
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Library General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Library General Public License for more details.
#
# You should have received a copy of the GNU Library General Public
# License along with this library; if not, write to the
# Free Software Foundation, Inc., 675 Mass Ave, Cambridge,
# MA 02139, USA.
#
# Tabstop is 8, SoftTabStop is 4, ShiftWidth is 4 (as per last line)
#
"""
Import from this module to connect to the Fresco server and access
the kits therein. Use the get_kits() and get_connection() functions to access
instances of the Kits and Connection objects.
"""

import sys, os, string, threading

# Import omniORBpy stuff
from omniORB import CORBA
import omniORB, CosNaming

# Import the Fresco stubs
import Unidraw
import Fresco__POA
from Impl import *

class ExitCommand(Fresco__POA.Command):
    def execute(self, any): app.quit.set()

class ClientContextImpl (Fresco__POA.ClientContext):
    "A default implementation of the ClientContext interface"
    def _get_user_name(self): return US("joe")
    def _get_application_title(self): return US("python demo")
    def exit(self): return ExitCommand()._this()
    def ping(self): return

def US(s):
    "Convert the given python string to a Unistring"
    return map(lambda x:ord(x), s)

# The default kits available. More can be added using kits.add_kit()
# TODO: include version and property information in the tuple
_defaultKitNames = {
    'tools'     : ('Fresco',  'ToolKit'),
    'rasters'   : ('Fresco',  'RasterKit'),
    'figures'   : ('Fresco',  'FigureKit'),
    'primitives': ('Fresco',  'PrimitiveKit'),
    'commands'  : ('Fresco',  'CommandKit'),
    'gadgets'   : ('Fresco',  'GadgetKit'),
    'desktop'   : ('Fresco',  'DesktopKit'),
    'layout'    : ('Fresco',  'LayoutKit'),
    'text'      : ('Fresco',  'TextKit'),
    'widgets'   : ('Fresco',  'WidgetKit'),
    'unidraw'   : ('Unidraw', 'UnidrawKit'),
}

# An empty Any object for sending to Commands
nullAny = CORBA.Any(CORBA.TC_null, None)
    
# You should use these functions instead of directly creating instances
def get_kits():
    "Return a Kits singleton"
    if not kits: return Kits()
    return kits
def get_connection(clientContext = None):
    """Return a Connection singleton. If it doesn't already exist, one is
    created using the ClientContext parameter"""
    if not connection: return Connection(clientContext)
    return connection
# The global vars
kits = None
connection = None

class Kits:
    """This class resolves kits upon request, and caches the resolved kit
    objects. It loads _defaultKitNames as the default set of kits, but more
    can be added using the add_kit method."""
    def __init__(self):
        """Initialise the Kits singleton, and insert it into the global
        (berlin module) namespace"""
        global kits
        kits = self
        self._kitNames = {}
        self._kitNames.update(_defaultKitNames)
        self._kitObjects = {}

    def add_kit(self, name, module, kit):
        """Adds the given kit to the list of accessable kits"""
        self._kitNames[name] = (module, kit)

    def __getattr__(self, kit):
        """Returns a cached kit. If the kit is not already cached, then it is
        looked up using the list of kits that you can update with add_kit()"""
        # Check cache
        if self._kitObjects.has_key(kit):
            return self._kitObjects[kit]
        # Try and resolve
        if self._kitNames.has_key(kit):
            # Find and resolve the kit
            module, name = self._kitNames[kit]
            idl = "IDL:fresco.org/%s/%s:1.0"%self._kitNames[kit]
            obj = connection.context.resolve(idl, [])
            cls = globals()[module].__dict__[name]
            obj = obj._narrow(cls)
            if obj is not None:
                self._kitObjects[kit] = obj
                return obj
        # Raise an exception to signal error
        raise NameError, "Kit '%s' not found."%kit

class Connection:
    """Connection wrapper that does all the CORBA stuff"""
    def __init__(self, clientContext=None):
        """Initialises the singleton, inserts it into the global (berlin
        module) namespace, and finds the Berlin server. You may pass your own
        ClientContext object (not CORBA var!), else a ClientContextImpl will
        be used."""
        global connection
        connection = self

        # Initialise the ORB
        #omniORB.maxTcpConnectionPerServer(100)
        self.orb = CORBA.ORB_init(sys.argv, CORBA.ORB_ID)

        # Find the POA
        self.poa = self.orb.resolve_initial_references("RootPOA")
        # Activate the POA
        self.poaManager = self.poa._get_the_POAManager()
        self.poaManager.activate()

        # Create an ClientContext
        if clientContext is None: clientContext = ClientContextImpl()
        # Create an object reference, and implicitly activate the object
        self.clientContext = clientContext._this()

        # Default arguments
        export_ref = ior_file_path = server_id = stringified_ior = ""

        # Parse argument list
        try:
            index = sys.argv.index("-R") or sys.argv.index("--export-ref")
            if index >= 1: export_ref = sys.argv[index+1]
        except:
            pass

        try:
            index = sys.argv.index("-I") or sys.argv.index("--ior-file-path")
            if index >= 1: ior_file_path = sys.argv[index+1]
        except:
            pass

        try:
            index = sys.argv.index("-i") or sys.argv.index("--server-id")
            if index >= 1: server_id = sys.argv[index+1]
        except:
            pass

        # Use $FRESCO_DISPLAY if the argument list is empty
        if export_ref == "" and ior_file_path == "" and server_id == "":
             if os.environ.has_key("FRESCO_DISPLAY"):
                stringified_ior = os.environ["FRESCO_DISPLAY"]

        # Set defaults
        if export_ref == "": export_ref = "ior"
        if ior_file_path == "": ior_file_path = "/tmp/fresco"
        if server_id == "": server_id = "FrescoServer"

        # Try with $FRESCO_DISPLAY
        if stringified_ior != "":
            object = self.orb.string_to_object(stringified_ior)
        else:
            # Try with other methods
            if export_ref == "nameserver":
                object = self.orb.resolve_initial_references("NameService")
                context = object._narrow(CosNaming.NamingContext)
                try:
                  name = [CosNaming.NameComponent(server_id, "Object")]
                  object = context.resolve(name)
                except:
                  print >> sys.stderr, \
                        "ERROR: Could not find specified server-id in" \
                        "nameservice\n"
                  sys.exit(1)
            elif export_ref == "corbaloc":
                print "Not implemented yet"
                sys.exit(1)
            elif export_ref == "ior":
                ior_filename = os.path.join(ior_file_path, server_id)
                try:
                    ior_file = open(ior_filename)
                    stringified_ior = ior_file.readline().rstrip()
                except:
                    print >> sys.stderr, "ERROR: Cannot open %s\n" \
                      "This could signify that the server is not running\n" \
                      "or that a server is running" \
                      "but with a different -I option parameter.\n" \
                      "If the latter, use the same option\n" \
                      "with this client as with the server.\n" \
                      "This could also signify that a server is running but\n" \
                      "its address is being\n" \
                      "published using another method; try the -R option." \
                      % ior_filename
                    sys.exit(1)
                object = self.orb.string_to_object(stringified_ior)
                ior_file.close()
                del ior_file
        self.server = object._narrow(Fresco.Server)
        self.context  = self.server.create_server_context(self.clientContext)
        #print "Got Server var =",self.server
        #print "Client Context var =",self.clientContext

class KBThread (threading.Thread):
    """A thread that waits for the user to hit enter, and then signals an
    application quit. This assumes there is a global var called 'app' with an
    attribute called 'quit' that is a threading.Event object"""
    def run(self):
        "Run until enter"
        print "Hit ENTER to quit."
        while 1:
            line = sys.stdin.readline()
            if len(line) == 1: break
        self.do_quit()
    def do_quit(self):
        "Override if you want to quit some other way"
        app.quit.set()

class App:
    "Base class for applications with some default useful functionality"
    def __init__(self):
        """Creates global kits and connection objects, the app.quit Event
        object, and a KBThread to set it."""
        global app
        app = self
        self.quit = threading.Event() # set quit to.. quit :)
        self.kbthread = KBThread()
        self.kbthread.setDaemon(1) # dont wait for kb thread :)
        self.kbthread.start()


def Label(string):
    "Creates a black label from the given string"
    return kits.tool.rgb(kits.text.chunk(US(string)),0.,0.,0.)

class Callback(Fresco__POA.Command):
    """Small wrapper command which calls a python function with a single
    argument which is the Any."""
    def __init__(self, callback):
        self.callback = callback
    def execute(self, any):
        print "Callback to",self.callback,"with",any
        if self.callback:
            self.callback(any)


# vim: ts=8:sts=4:sw=4
