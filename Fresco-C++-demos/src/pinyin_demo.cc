/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999,2000 Tobias Hunger <Tobias@berlin-consortium.org>
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

// stuff from stdc++
#include <iostream>
#include <memory>
#include <string>

// everything needed for clients
#include <client.hh>

// need to include the Kits I'll use
#include <Warsaw/LayoutKit.hh>
#include <Warsaw/TextKit.hh>
#include <Warsaw/ToolKit.hh>
#include <Warsaw/DesktopKit.hh>
#include <Warsaw/CommandKit.hh>
#include <Warsaw/WidgetKit.hh>
#include <Warsaw/Unicode.hh>

#include <Berlin/ObserverImpl.hh>

// pinyin input class
#include "TextConverter.hh"

#include <Warsaw/TextBuffer.hh>
#include <Babylon/Babylon.hh>
#include <Prague/Sys/Path.hh>
#include <Prague/Sys/GetOpt.hh>
#include <Berlin/RCManager.hh>

class InputObserver : public ObserverImpl {
public:
    InputObserver(Warsaw::TextBuffer_var i,
		  Warsaw::TextBuffer_var s,
		  Warsaw::TextBuffer_var o) : input(i),
					      select(s),
					      output(o)
    {
	cerr << "IO: creating";
	Prague::Path path = RCManager::get_path("pinyindbpath");
	string pinyinDB = path.lookup_file("pinyin.db");
	converter = new TextConverter(pinyinDB);
	cerr << " done" << endl;
    }
	

    virtual void update(const CORBA::Any &any) {
	cerr << "IO: update called" << endl;
	Warsaw::TextBuffer::Change * change;

	if (any >>= change) {
	    Warsaw::Unistring_var us(input->get_chars(0, input->size()));
	    Babylon::String bs(Unicode::to_internal(us));

	    Babylon::Char last = bs[bs.length() - 1];
	    if (last >= 'A' && last <= 'Z') {
		cerr << "Last letter (" << last << ") of " << bs.length() << " is uppercase." << endl;
		// select a chinese letter:
		bs.erase(bs.length() - 1);
		cerr << "  new bs: " << bs << endl;
		Babylon::String select_from(converter->convert(bs));
		cerr << "  select_from generated." << endl;
		
		if ((last.value() - 'A') < select_from.length()) {
		    cerr << "  my letter is valid." << endl;
		    select->clear_buffer();

		    cerr << "  Inserting \"" << select_from[last.value() - 'A'] << "\" into output." << endl;
		    
		    output->insert_char(Unicode::to_CORBA(select_from[last.value() - 'A']));
		    cerr << "  Done inserting char into output." << endl;
		    input->clear_buffer();
		    cerr << "  Input cleaned." << endl;
		} else {
		    // delete the uppercase char:
		    cerr << "  no such character in select-String." << endl;

		    input->remove_backward(1);
		}
	    } else {
		cerr << "bs: \"" << bs << "\" (with first character = " << hex << bs[0].value()<< dec << ") ";

		Babylon::String select_from(converter->convert(bs));
		
		cerr << " results in " << select_from.length() << " answers." << endl;
		select->clear_buffer();
		cerr << "  select cleared!" << endl;

		// FIXME: substr() is broken! So this is rather clumpsy.
		if (select_from.length() > 26)
		    select_from.erase(26, select_from.length());

		cerr << "  new select_from shortened to " << select_from.length() << " answers." << endl;  

		cerr << "Inserting \"" << select_from << "\" into selection (" << select_from.length() << " characters)." << endl;
		select->insert_string(Unicode::to_CORBA(select_from));
	    }
	} else
	    cerr << "How did I get here?" << endl;

	cerr << "IO: update finished" << endl;
    }
    
private:
    Warsaw::TextBuffer_var input;
    Warsaw::TextBuffer_var select;
    Warsaw::TextBuffer_var output;
    
    TextConverter * converter;
}; // class InputObserver

int main(int argc, char ** argv) {
    Prague::GetOpt getopt(argv[0], "a simple pinyin input application.");
    getopt.add('r', "resource", Prague::GetOpt::mandatory, "the resource file to load");
    size_t argo = getopt.parse(argc, argv);
    argc -= argo;
    argv += argo;
    std::string value;
    getopt.get("resource", &value);
    if (!value.empty()) RCManager::read(Prague::Path::expand_user(value));

    try {
	// Do CORBA-magic and connect to server:
	Berlin_Server server(argc, argv);

	// Get Kits:
	REGISTER_KIT(server, lk, LayoutKit, 1.0);
	REGISTER_KIT(server, tk, TextKit, 1.0);
	REGISTER_KIT(server, tlk, ToolKit, 1.0);
	REGISTER_KIT(server, dk, DesktopKit, 1.0);
	REGISTER_KIT(server, ck, CommandKit, 1.0);
	REGISTER_KIT(server, wk, WidgetKit, 1.0);

	// Create Graphics:
	Warsaw::TextBuffer_var input_buf = ck->text();
	Warsaw::TextBuffer_var chinese_buf = ck->text();
	Warsaw::TextBuffer_var output_buf = ck->text();

	Warsaw::Graphic_var input_view = tk->simple_viewer(input_buf);
	Warsaw::Graphic_var chinese_view = tk->simple_viewer(chinese_buf);
	Warsaw::Graphic_var output_view = tk->simple_viewer(output_buf);

	Warsaw::ToolKit::FrameSpec frame;
	frame.brightness(0.5); frame._d(Warsaw::ToolKit::inset);

	Warsaw::Graphic_var vbox = lk->vbox();
	vbox->append_graphic(tlk->frame(Warsaw::Graphic_var(lk->margin(Warsaw::Graphic_var(lk->hfixed(Warsaw::Graphic_var(tlk->rgb(chinese_view, 0.0, 0.0, 0.0)), 4000)), 50.0)), 20.0, frame, true));
	vbox->append_graphic(tlk->frame(Warsaw::Graphic_var(lk->margin(Warsaw::Graphic_var(lk->hfixed(Warsaw::Graphic_var(tlk->rgb(input_view, 0.0, 0.0, 0.0)), 4000)), 50.0)), 20.0, frame, true));	
	vbox->append_graphic(tlk->frame(Warsaw::Graphic_var(lk->margin(Warsaw::Graphic_var(lk->hfixed(Warsaw::Graphic_var(tlk->rgb(output_view, 0.0, 0.0, 0.0)), 4000)), 50.0)), 20.0, frame, true));

	InputObserver observer(input_buf, chinese_buf, output_buf);
	input_buf->attach(Warsaw::Observer_var(observer._this()));

	Warsaw::Window_var window = dk->shell(tlk->text_input(vbox, input_buf));

	// Wait...
	while(true) Prague::Thread::delay(Prague::Time(1000));

    } catch (const CORBA::Exception & e) {
	cerr << "Uncaught CORBA exception! " << e << endl;
	return 1;
    } catch (const std::exception & e) {
	cerr << "Uncaught exception: " << e.what() << endl; 
	return 2;
    }
    return 0;
} // main
