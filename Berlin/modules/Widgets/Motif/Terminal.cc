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
#include <Prague/IPC/ptybuf.hh>
#include "Terminal.hh"

using namespace Prague;
using namespace Fresco;
using namespace Berlin::WidgetKit::Motif;

void Terminal::Input::update(const CORBA::Any &)
{
    Trace trace("Terminal::Input::update");

    // the source
    Fresco::StreamBuffer::Data_var data = my_terminal->my_ibuf->read();
    char *begin = (char *)data->get_buffer();
    char *end   = begin + data->length();

    // the sink
    std::ostream os(my_terminal->my_agent->ibuf());
    for (char *i = begin; i != end; i++) os.put(*i);
    os.flush();
}


bool Terminal::Output::notify(Agent::iomask mask)
{
    Trace trace("Terminal::output::notify");
    if (mask != Agent::outready) return false;

    // the source
    std::istream is(my_terminal->my_agent->obuf());
    std::string line;
    while (getline(is, line))
    {
    StreamBuffer::Data data(line.length(), line.length(),
                (CORBA::Octet *)line.data(), false);
    my_terminal->my_obuf->write(data);
    my_terminal->my_obuf->flush();
    }
    return true;
}

Terminal::Terminal(CommandKit_ptr command) :
    // ControllerImpl(false),
    my_input(new Input(this)),
    my_output(new Output(this)),
    my_agent(new TTYAgent("sh", my_output, 0)),
    my_ibuf(RefCount_var<StreamBuffer>::increment(command->stream(1))),
    my_obuf(RefCount_var<StreamBuffer>::increment(command->stream(1024)))
{
    Trace trace("Terminal::Terminal");
    my_ibuf->attach(Observer_var(my_input->_this()));
    my_agent->start();
}
