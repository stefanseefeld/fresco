/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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

#include "Widget/Motif/Terminal.hh"
#include <Prague/Sys/Tracer.hh>

using namespace Motif;
using namespace Prague;

void Terminal::Input::update(const CORBA::Any &)
{
  Trace trace("Terminal::Input::update");
  /*
   * the source
   */
  StreamBuffer::Data_var data = terminal->ibuf->read();
  char *begin = (char *)data->get_buffer();
  char *end   = begin + data->length();
  /*
   * the sink
   */
  ostream os(terminal->agent->ibuf());
  for (char *i = begin; i != end; i++) os.put(*i);
  os.flush();
}


bool Terminal::Output::notify(Agent::iomask_t mask)
{
  Trace trace("Terminal::output::notify");
  if (mask != Agent::outready) return false;
  /*
   * the source
   */
  istream is(terminal->agent->obuf());
  string line;
  while (is)
    {
      getline(is, line);
//       if (is) line += '\n';
//       cout << line << flush;
//       StreamBuffer::Data data(line.length(), line.length(), (CORBA::Octet *)line.data(), false);
      if (is)
	{
	  StreamBuffer::Data data(line.length(), line.length(), (CORBA::Octet *)line.data(), false);
	  terminal->obuf->write(data);
	}
    }
  return true;
}

Terminal::Terminal(CommandKit_ptr command)
  : // ControllerImpl(false),
    _input(new Input(this)),
    _output(new Output(this)),
    agent(new TTYAgent("sh", _output, 0)),
    ibuf(StreamBuffer::_duplicate(command->stream(1))),
    obuf(StreamBuffer::_duplicate(command->stream(1)))
{
  Trace trace("Terminal::Terminal");
  _input->_obj_is_ready(CORBA::BOA::getBOA());
  ibuf->attach(Observer_var(_input->_this()));
  agent->start();
}
