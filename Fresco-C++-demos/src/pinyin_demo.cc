/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999,2000 Tobias Hunger <tobias@fresco.org>
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

// stuff from stdc++
#include <iostream>
#include <memory>
#include <string>

// everything needed for clients
#include <Fresco/config.hh>
#include <Fresco/resolve.hh>
#include <Fresco/ClientContextImpl.hh>
#include <Fresco/Server.hh>

// need to include the Kits I'll use
#include <Fresco/LayoutKit.hh>
#include <Fresco/TextKit.hh>
#include <Fresco/ToolKit.hh>
#include <Fresco/DesktopKit.hh>
#include <Fresco/CommandKit.hh>
#include <Fresco/WidgetKit.hh>
#include <Fresco/Unicode.hh>

#include <Berlin/ObserverImpl.hh>

// pinyin input class
#include "TextConverter.hh"

#include <Fresco/TextBuffer.hh>
#include <Babylon/Babylon.hh>
#include <Prague/Sys/Path.hh>

#ifdef DATADIR
const std::string data_dir = DATADIR;
#else
const std::string data_dir = "";
#endif

static std::string pinyin_db_file;

class InputObserver : public Berlin::ObserverImpl
{
  public:
    InputObserver(Fresco::TextBuffer_var i,
          Fresco::TextBuffer_var s,
          Fresco::TextBuffer_var o) :
    my_input(i),
    my_select(s),
    my_output(o)
    {
    // get the path of the Memorymap we need from the RCManager
    my_converter = new TextConverter(pinyin_db_file);
    }
    

    // This function gets called as soon as the buffer I observe is
    // updated.
    virtual void update(const CORBA::Any &any)
    {
    Fresco::TextBuffer::Change * change;
    
    if (any >>= change) {
        // 'any' contained a TextBuffer::Change. This is what I
        // expected.
        
        // bs will contain a Babylon::String which is equivalent
        // to the contents of 'input'.
        // Unicode::to_internal() converts from the UCS2 encoded
        // Unistring passed by CORBA to the UCS4 encoded
        // Babylon::String
        Babylon::String bs(Unicode::to_internal(Fresco::Unistring_var(my_input->value())));

        Babylon::Char last = bs[bs.length() - 1];
        if (!bs.empty() && last >= 'A' && last <= 'Z')
        {
        // uppercase letter selects one chinese char out of those
        // shown in 'select'
        
        bs.erase(bs.length() - 1);
        Babylon::String select_from(my_converter->convert(bs));
        
        if ((last.value() - 'A') < select_from.length())
        {
            // recode letter into Unistring and add to 'output'
            // I use insert_string() since the chinese chars might
            // have a codepoint above 0xFFFF which insert_char()
            // is not able to handle.
            my_output->insert_string(Unicode::to_CORBA(Babylon::String(1, select_from[last.value() - 'A'])));
            
// FIXME:           my_input->clear(); // this clears select too:
                            // it results in a call to this function
                            // with an empty 'input'
        }
        else
            // delete the uppercase char since it did not
            // denote a character in 'select':
// FIXME:           my_input->remove_backward(CORBA::ULong(1));
        { }
        }
        else
        {
        // sharpen 'select':
        my_select->clear();
        
        Babylon::String select_from(my_converter->convert(bs));
        
        // Only show the first 26 characters:
        if (select_from.length() > 26)
            select_from.erase(26, select_from.length());
        
        my_select->insert_string(Unicode::to_CORBA(select_from));
        }
    }
    else
        // Our 'any' contains no TextBuffer::Change! Since
        // the TextBuffer only emits that I encountered
        // a really weird error...
        exit(10);
    }
    
  private:
    Fresco::TextBuffer_var my_input;
    Fresco::TextBuffer_var my_select;
    Fresco::TextBuffer_var my_output;
    
    TextConverter * my_converter;
}; // class InputObserver

int main(int argc, char ** argv) 
{
    // Parse args:
    Prague::GetOpt getopt(argv[0], "a simple pinyin input application.");
    getopt.add('h', "help", Prague::GetOpt::novalue, "help text");
    getopt.add('p', "pinyin-db-path", Prague::GetOpt::mandatory,
           "path to the pinyin database file to load");
    add_resolving_options_to_getopt(getopt);
    size_t argo = getopt.parse(argc, argv);
    argc -= argo;
    argv += argo;

    if (getopt.is_set("help"))
    {
    getopt.usage();
    return 0;
    }

    // find the pinyin database
    std::string pinyin_path;
    getopt.get("pinyin-db-path", &pinyin_path);
    if (pinyin_path=="") pinyin_path = data_dir;
    Prague::Path path(pinyin_path);
    pinyin_db_file = path.lookup_file("pinyin.db");
    
    // do the real work:
    CORBA::ORB_var orb;
    PortableServer::POA_var poa;
    PortableServer::POAManager_var pman;
    ClientContextImpl *client;
    Fresco::ServerContext_var server;
    
    try
    {
    orb = CORBA::ORB_init(argc, argv);
    poa = resolve_init<PortableServer::POA>(orb, "RootPOA");
    pman = poa->the_POAManager();
    pman->activate();
    
    client = new ClientContextImpl("Pinyin Demo");
    
    Fresco::Server_var s = resolve_server(getopt, orb);
    
    server = s->create_server_context(Fresco::ClientContext_var(client->_this()));
    } 
    catch (const CORBA::COMM_FAILURE &)
    {
    std::cerr << "Could not connect to the berlin server "
          << "(CORBA::COMM_FAILURE)." << std::endl;
    }
    
    // Get Kits:

    Fresco::LayoutKit_var lk = resolve_kit<Fresco::LayoutKit>(server);
    Fresco::TextKit_var tk = resolve_kit<Fresco::TextKit>(server);
    Fresco::ToolKit_var tlk = resolve_kit<Fresco::ToolKit>(server);
    Fresco::DesktopKit_var dk = resolve_kit<Fresco::DesktopKit>(server);
    Fresco::CommandKit_var ck = resolve_kit<Fresco::CommandKit>(server);
    Fresco::WidgetKit_var wk = resolve_kit<Fresco::WidgetKit>(server);
    
    // Create the GUI:
    
    // Create Textlabels:
    
    // A rather complex command:
    // - Create a Babylon::String containing "PinYin Input Applet"
    // - Change that string into something CORBA understands
    // - Create a text chunk containing said string
    // - Make it black using the ToolKit's rgb decorator.
    Fresco::Graphic_var title = tlk->rgb(Fresco::Graphic_var(tk->chunk(Unicode::to_CORBA(Babylon::String("PinYin Input Applet")))), 0.0, 0.0, 0.0);
    
    // create additional labels:
    Fresco::Graphic_var chinese_label =
    tlk->rgb(Fresco::Graphic_var(tk->chunk(Unicode::to_CORBA(Babylon::String("Possible Matches:")))), 0.0, 0.0, 0.0);
    Fresco::Graphic_var input_label =
    tlk->rgb(Fresco::Graphic_var(tk->chunk(Unicode::to_CORBA(Babylon::String("Input:")))), 0.0, 0.0, 0.0);
    Fresco::Graphic_var output_label =
    tlk->rgb(Fresco::Graphic_var(tk->chunk(Unicode::to_CORBA(Babylon::String("Chinese Text:")))), 0.0, 0.0, 0.0);
    
    // We'll need three buffers to hold our text:
    Fresco::TextBuffer_var input_buf = ck->text();
    Fresco::TextBuffer_var chinese_buf = ck->text();
    Fresco::TextBuffer_var output_buf = ck->text();
    
    // These buffers need associated views, else they are invisible:
    // Since both ASCII and chinese do not need bidirectional output
    // I use the buffers in memory-order. That way I don't need to do
    // and reordering of the strings. If you can't be sure that
    // no text in araqbic, hebrew or whatever will ever be entered,
    // get a TextBuffer in visual order by calling get_visual_buffer() on
    // the standard, memory-ordered TextBuffer.
    // This line with a simple textviewer displaying in visual order would
    // look like this:
    // Fresco::Graphic_var input_view =
    //     tk->simple_viewer(input_buf->get_visual_buffer());
    Fresco::Graphic_var input_view = tk->simple_viewer(input_buf);
    Fresco::Graphic_var chinese_view = tk->simple_viewer(chinese_buf);
    Fresco::Graphic_var output_view = tk->simple_viewer(output_buf);
    
    // Construct a frame. It will be drawn around each buffer later:
    Fresco::ToolKit::FrameSpec frame;
    frame.brightness(0.5); frame._d(Fresco::ToolKit::inset);
    
    // Add text in front of the views:
    // We use a hbox which will layout it's children one after another.
    Fresco::Graphic_var input_line = lk->hbox();
    
    // The first thing to add is the label
    input_line->append_graphic(input_label);
    // Now we add glue: a strechable, invisible graphic
    input_line->append_graphic(Fresco::Graphic_var(lk->hglue(100.0, lk->fill(), 0.0)));
    // Then the viewer created earlier. We add some decorations while we are
    // at it anyway. Looks awfully complex, but is rather easy:-)
    input_line->append_graphic(tlk->frame(Fresco::Graphic_var(lk->margin(Fresco::Graphic_var(lk->hfixed(Fresco::Graphic_var(tlk->rgb(input_view, 0.0, 0.0, 0.0)), 4000)), 50.0)), 20.0, frame, true));
    // This line does a lot of things:
    // - It adds a decorator to 'input_view' which makes it display it's
    //   contents in black (0.0, 0.0, 0.0). White would be (1.0, 1.0, 1.0).
    //   To do this it asks the ToolKit for an rgb-Graphic which wraps the
    //   simple_viewer.
    // - Another decorator fixes the horizontal size. This graphic is
    //   requested from the LayoutKit.
    // - Another decorator from the LayoutKit is applied: it draws a
    //   margin around what we have so far.
    // - Finally the frame we constructed earlier is used by the
    //   frame-graphic (obtained from the ToolKit) to wrap everything
    //   in a nive beleveled frame.
    
    // The same again for the other viewers:
    Fresco::Graphic_var output_line = lk->hbox();
    output_line->append_graphic(output_label);
    output_line->append_graphic(Fresco::Graphic_var(lk->hglue(100.0, lk->fill(), 0.0)));
    output_line->append_graphic(tlk->frame(Fresco::Graphic_var(lk->margin(Fresco::Graphic_var(lk->hfixed(Fresco::Graphic_var(tlk->rgb(output_view, 0.0, 0.0, 0.0)), 4000)), 50.0)), 20.0, frame, true));
    Fresco::Graphic_var chinese_line = lk->hbox();
    
    chinese_line->append_graphic(chinese_label);
    chinese_line->append_graphic(Fresco::Graphic_var(lk->hglue(100.0, lk->fill(), 0.0)));
    chinese_line->append_graphic(tlk->frame(Fresco::Graphic_var(lk->margin(Fresco::Graphic_var(lk->hfixed(Fresco::Graphic_var(tlk->rgb(chinese_view, 0.0, 0.0, 0.0)), 4000)), 50.0)), 20.0, frame, true));
    
    // This was the hard part!
    // Now we only need to arrange our graphics one above the other:
    
    // I ask the LayoutKit for a vbox
    Fresco::Graphic_var vbox = lk->vbox();
    
    // Add the title created earlier ...
    vbox->append_graphic(Fresco::Graphic_var(lk->margin_lrbt_flexible(title, 0., 1e10, 0., 0., 1e10, 0., 50., 0., 0., 50., 0., 0.)));
    
    // ... and then the lines.
    vbox->append_graphic(chinese_line);    
    vbox->append_graphic(input_line);    
    vbox->append_graphic(output_line);
    
    // 'vbox' contains the complete graphics of our little application now!
    // It will even display whatever is in the buffers as '*_view' each
    // observes one of the buffers.
    
    // Now we only need to get something into those buffers:
    
    // Construct my observer and make it observe 'input_buf'
    InputObserver *observer = new InputObserver(input_buf, chinese_buf, output_buf);
    poa->activate_object(observer);
    input_buf->attach(Fresco::Observer_var(observer->_this()));
    // The 'observer' will now watch 'input_buf' for changes
    // and alter the other buffers as necessary.
    
    // Now we only need to request a window that will contain our UI:
    // While we are at it we will wrap it into a text_input Controller.
    // This controller accepts keyboard-events and updates a TextBuffer.
    // It does not draw anything! That's done by the observers of
    // 'input_buf' (which are 'observer' and 'input_view' in this applet).
    Fresco::ToolKit::FrameSpec spec;
    spec.brightness(0.5); spec._d(Fresco::ToolKit::outset);
    Fresco::Graphic_var body = tlk->frame(vbox, 20., spec, true);
    Fresco::Window_var window =
    dk->shell(tlk->text_input(body, input_buf), 
          Fresco::ClientContext_var(client->_this()));
    
    // Don't quit but idle around a bit so the server has the chance
    // to do its work:-)
    //while(true) Prague::Thread::delay(Prague::Time(1000));
    orb->run();
    
    // Did you notice that everything besides 'observer' was
    // actually created in the server? We asked it for the Kits
    // (which get loaded into the server) and those in turn created
    // the graphics we used.
    
    return 0;
} // main
