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
#ifndef _Motif_Terminal_hh
#define _Motif_Terminal_hh

#include <Fresco/config.hh>
#include <Fresco/CommandKit.hh>
#include <Fresco/StreamBuffer.hh>
#include <Berlin/ImplVar.hh>
#include <Berlin/ObserverImpl.hh>
#include <Berlin/ControllerImpl.hh>
#include <Berlin/RefCountVar.hh>
#include <Prague/IPC/TTYAgent.hh>
#include <vector>

namespace Motif
{

class Terminal : public MonoGraphic
{
  class Input : public ObserverImpl
  {
  public:
    Input(Terminal *t) : terminal(t) {}
    virtual void update(const CORBA::Any &);
  private:
    Terminal *terminal;
  };
  class Output : public Prague::Coprocess::IONotifier
  {
  public:
    Output(Terminal *t) : terminal(t) {}
    virtual bool notify(Prague::Agent::iomask);
  private:
    Terminal *terminal;
  };
  friend class Input;
  friend class Output;
 public:
  Terminal(Fresco::CommandKit_ptr);
  Fresco::StreamBuffer_ptr input() { return Fresco::StreamBuffer::_duplicate(ibuf);}
  Fresco::StreamBuffer_ptr output() { return Fresco::StreamBuffer::_duplicate(obuf);}
 private:
  Input *_input;
  Output *_output;
  Prague::TTYAgent *agent;
  RefCount_var<Fresco::StreamBuffer> ibuf;
  RefCount_var<Fresco::StreamBuffer> obuf;
};

};
#endif
