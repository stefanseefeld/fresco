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
#ifndef _Motif_Terminal_hh
#define _Motif_Terminal_hh

#include <Warsaw/config.hh>
#include <Warsaw/CommandKit.hh>
#include <Warsaw/StreamBuffer.hh>
#include <Berlin/ImplVar.hh>
#include <Berlin/ControllerImpl.hh>
#include <Prague/IPC/TTYAgent.hh>
#include <vector>

namespace Motif
{

class Terminal : public MonoGraphic
{
  class Input : public virtual POA_Observer, public virtual PortableServer::RefCountServantBase
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
    virtual bool notify(Prague::Agent::iomask_t);
  private:
    Terminal *terminal;
  };
  friend class Input;
  friend class Output;
 public:
  Terminal(CommandKit_ptr);
  StreamBuffer_ptr input() { return StreamBuffer::_duplicate(ibuf);}
  StreamBuffer_ptr output() { return StreamBuffer::_duplicate(obuf);}
 private:
  Impl_var<Input> _input;
  Output *_output;
  Prague::TTYAgent *agent;
  StreamBuffer_var ibuf;
  StreamBuffer_var obuf;
};

};
#endif /* _Motif_Terminal_hh */
