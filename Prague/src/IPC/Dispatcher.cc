/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@fresco.org>
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

#include "Prague/Sys/Signal.hh"
#include "Prague/Sys/Tracer.hh"
#include "Prague/IPC/Dispatcher.hh"
#include <queue>
#include <algorithm>
#include <ctime>
#include <cerrno>
#include <sys/types.h>

using namespace Prague;

Dispatcher *Dispatcher::dispatcher = 0;
Mutex Dispatcher::singletonMutex;
Dispatcher::Cleaner Dispatcher::cleaner;

struct Dispatcher::task
{
    task() : fd(-1), agent(0), mask(Agent::none), released(false) {}
    task(int ffd, Agent *a, Agent::iomask m) : fd(ffd), agent(a), mask(m) {}
    bool operator < (const task &t) const { return fd < t.fd;}
    int fd;
    Agent *agent;
    Agent::iomask mask;
    bool released;
};

Dispatcher::Cleaner::~Cleaner()
{
    // Prague::Guard<Mutex> guard(singletonMutex);
    delete dispatcher;
}

Dispatcher *Dispatcher::instance()
{
    Prague::Guard<Mutex> guard(singletonMutex);
    if (!dispatcher) dispatcher = new Dispatcher;
    return dispatcher;
}

//. create a queue of up to 64 tasks
//. and a thread pool with 16 threads
Dispatcher::Dispatcher() :
  my_tasks(64),
  my_workers(my_tasks, my_acceptor, 4),
  my_server(&Dispatcher::run, this)
{
    Signal::mask(Signal::pipe);
}

Dispatcher::~Dispatcher() { }

void Dispatcher::bind(Agent *agent, int fd, Agent::iomask mask)
  throw(std::invalid_argument)
{
    Trace trace("Dispatcher::bind");
    if (my_server.state() == Thread::READY)
    {
        pipe(my_wakeup);
        my_rfds.set(my_wakeup[0]);
        my_server.start();
    }
    Prague::Guard<Mutex> guard(my_mutex);
    if (find(my_agents.begin(), my_agents.end(), agent) == my_agents.end())
    {
        my_agents.push_back(agent);
        agent->add_ref();
    }
    if (mask & Agent::in)
    {
        if (mask & Agent::inready)
        {
            my_wfds.set(fd);
            if (my_wchannel.find(fd) == my_wchannel.end())
                my_wchannel[fd] = new task(fd, agent, Agent::inready);
            else throw std::invalid_argument("file descriptor already in use");
        }
        if (mask & Agent::inexc)
        {
            my_xfds.set(fd);
            if (my_xchannel.find(fd) == my_xchannel.end())
            my_xchannel[fd] = new task(fd, agent, Agent::inexc);
        }
    }
    if (mask & Agent::out)
    {
        if (mask & Agent::outready)
        {
            my_rfds.set(fd);
            if (my_rchannel.find(fd) == my_rchannel.end())
                my_rchannel[fd] = new task(fd, agent, Agent::outready);
            else throw std::invalid_argument("file descriptor already in use");
        }
        if (mask & Agent::outexc)
        {
            my_xfds.set(fd);
            if (my_xchannel.find(fd) == my_xchannel.end())
                my_xchannel[fd] = new task(fd, agent, Agent::outexc);
        }
    }
    if (mask & Agent::err)
    {
        if (mask & Agent::errready)
        {
            my_rfds.set(fd);
            if (my_rchannel.find(fd) == my_rchannel.end())
                my_rchannel[fd] = new task(fd, agent, Agent::errready);
            else throw std::invalid_argument("file descriptor already in use");
        }
        if (mask & Agent::errexc)
        {
            my_xfds.set(fd);
            if (my_xchannel.find(fd) == my_xchannel.end())
                my_xchannel[fd] = new task(fd, agent, Agent::errexc);
        }
    }
    notify();
}

void Dispatcher::release(Agent *agent, int fd)
{
    Trace trace("Dispatcher::release");
    // release file descriptors
    Prague::Guard<Mutex> guard(my_mutex);
    for (repository_t::iterator i = my_rchannel.begin(); i != my_rchannel.end(); i++)
        if ((*i).second->agent == agent && (fd == -1 || fd == (*i).second->fd))
        {
            deactivate((*i).second);
            (*i).second->released = true;
            my_rchannel.erase(i);
        }
    for (repository_t::iterator i = my_wchannel.begin(); i != my_wchannel.end(); i++)
        if ((*i).second->agent == agent && (fd == -1 || fd == (*i).second->fd))
        {
            deactivate((*i).second);
            (*i).second->released = true;
            my_wchannel.erase(i);
        }
    for (repository_t::iterator i = my_xchannel.begin(); i != my_xchannel.end(); i++)
        if ((*i).second->agent == agent && (fd == -1 || fd == (*i).second->fd))
        {
            deactivate((*i).second);
            (*i).second->released = true;
            my_xchannel.erase(i);
        }
    // release Agent if no more file descriptors left
    for (repository_t::iterator i = my_rchannel.begin(); i != my_rchannel.end(); i++)
        if ((*i).second->agent == agent) return;
    for (repository_t::iterator i = my_wchannel.begin(); i != my_wchannel.end(); i++)
        if ((*i).second->agent == agent) return;
    for (repository_t::iterator i = my_xchannel.begin(); i != my_xchannel.end(); i++)
        if ((*i).second->agent == agent) return;

    alist_t::iterator i = find(my_agents.begin(), my_agents.end(), agent);
    if (i != my_agents.end())
    {
        my_agents.erase(i);
        agent->remove_ref();
    }
}

void *Dispatcher::run(void *X)
{
    Dispatcher *dispatcher = reinterpret_cast<Dispatcher *>(X);
    dispatcher->my_workers.start();
    do
        dispatcher->wait();
    while (true);
    return 0;
}

void Dispatcher::dispatch(task *t)
{
    deactivate(t);
    my_tasks.push(t);
}

void Dispatcher::process(task *t)
{
    Trace trace("Dispatcher::process");
    Agent *agent = t->agent;
    // save the agent from being deleted while it processes i/o
    agent->add_ref();
    bool done = !agent->process(t->fd, t->mask);
    agent->remove_ref();
    // now look whether the agent is released and the task should be deleted
    Prague::Guard<Mutex> guard(my_mutex);
    if (!done)
    {
        if (t->released) delete t;
        else activate(t);
    }
}

void Dispatcher::deactivate(task *t)
{
    switch (t->mask)
    {
      case Agent::inready:
         my_wfds.clear(t->fd);
         break;
      case Agent::outready:
      case Agent::errready:
        my_rfds.clear(t->fd);
        break;
      case Agent::inexc:
      case Agent::outexc:
      case Agent::errexc:
        my_xfds.clear(t->fd);
        break;
      default:
        break;
    }
}

void Dispatcher::activate(task *t)
{
    switch (t->mask)
    {
      case Agent::inready:
        my_wfds.set(t->fd);
        break;
      case Agent::outready:
      case Agent::errready:
        my_rfds.set(t->fd);
        break;
      case Agent::inexc:
      case Agent::outexc:
      case Agent::errexc:
        my_xfds.set(t->fd);
        break;
      default:
          break;
    }
    notify();
}

void Dispatcher::wait()
{
    Trace trace("Dispatcher::wait");
    FdSet tmprfds = my_rfds;
    FdSet tmpwfds = my_wfds;
    FdSet tmpxfds = my_xfds;
    unsigned int fdsize = std::max(std::max(tmprfds.max(), tmpwfds.max()),
                                   tmpxfds.max()) + 1;
    int nsel = select(fdsize, tmprfds, tmpwfds, tmpxfds, 0);
    Thread::testcancel();
    if (nsel == -1)
    {
        if (errno == EINTR || errno == EAGAIN) errno = 0;
    }
    else if (nsel > 0 && fdsize)
    {
        Prague::Guard<Mutex> guard(my_mutex);
        for (repository_t::iterator i = my_rchannel.begin(); i != my_rchannel.end(); i++)
            if (tmprfds.isset((*i).first))
        dispatch((*i).second);
        for (repository_t::iterator i = my_wchannel.begin(); i != my_wchannel.end(); i++)
            if (tmpwfds.isset((*i).first))
        dispatch((*i).second);
        for (repository_t::iterator i = my_xchannel.begin(); i != my_xchannel.end(); i++)
            if (tmpxfds.isset((*i).first))
        dispatch((*i).second);
        if (tmprfds.isset(my_wakeup[0]))
        {
            char c[1];
            read(my_wakeup[0], c, 1);
        }
    }
}
