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
#ifndef _WidgetKit_Motif_Terminal_hh
#define _WidgetKit_Motif_Terminal_hh

#include <Fresco/config.hh>
#include <Fresco/CommandKit.hh>
#include <Fresco/StreamBuffer.hh>
#include <Berlin/ImplVar.hh>
#include <Berlin/ObserverImpl.hh>
#include <Berlin/ControllerImpl.hh>
#include <Berlin/RefCountVar.hh>
#include <Prague/IPC/TTYAgent.hh>

namespace Berlin
{
  namespace WidgetKit
  {
    namespace Motif
    {

      class Terminal : public MonoGraphic
      {
	  class Input : public ObserverImpl
	  {
	    public:
	      Input(Terminal *t) : my_terminal(t) { }
	      virtual void update(const CORBA::Any &);
	    private:
	      Terminal *my_terminal;
	  };
	  class Output : public Prague::Coprocess::IONotifier
	  {
	    public:
	      Output(Terminal *t) : my_terminal(t) { }
	      virtual bool notify(Prague::Agent::iomask);
	    private:
	      Terminal *my_terminal;
	  };
	  friend class Input;
	  friend class Output;
	public:
	  Terminal(Fresco::CommandKit_ptr);
	  Fresco::StreamBuffer_ptr input()
	  { return Fresco::StreamBuffer::_duplicate(my_ibuf); }
	  Fresco::StreamBuffer_ptr output()
	  { return Fresco::StreamBuffer::_duplicate(my_obuf); }
	private:
	  Input *my_input;
	  Output *my_output;
	  Prague::TTYAgent *my_agent;
	  RefCount_var<Fresco::StreamBuffer> my_ibuf;
	  RefCount_var<Fresco::StreamBuffer> my_obuf;
      };

    } // namespace
  } // namespace
} // namespace

#endif
