/*+P
 * This file is part of OffiX,
 * a C++ API for the X Window System and Unix
 * Copyright (C) 1995-98  Stefan Seefeld
 *
 * this file is based on code from the socket++ library
 * Copyright (C) 1992-1996 Gnanasekaran Swaminathan <gs4t@virginia.edu>
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
 -P*/
static char *rcsid = "$Id$";
#include "Prague/IPC/socketbuf.hh"
#include <iostream>
#include <netdb.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

const char *sockerr::errstr () const
{
  return strerror(err);
}

bool sockerr::io () const
// recoverable io error.
{
  switch (err) {
  case EWOULDBLOCK:
  case EINPROGRESS:
  case EALREADY:
    return true;
  }
  return false;
}

bool sockerr::arg () const
// recoverable argument error.
{
  switch (err) {
  case ENOTSOCK:
  case EDESTADDRREQ:
  case EMSGSIZE:
  case EPROTOTYPE:
  case ENOPROTOOPT:
  case EPROTONOSUPPORT:
  case ESOCKTNOSUPPORT:
  case EOPNOTSUPP:
  case EPFNOSUPPORT:
  case EAFNOSUPPORT:
  case EADDRINUSE:
  case EADDRNOTAVAIL:
    return true;
  }
  return false;
}

bool sockerr::op () const
// operational error encountered 
{
  switch (err) {
  case ENETDOWN:
  case ENETUNREACH:
  case ENETRESET:
  case ECONNABORTED:
  case ECONNRESET:
  case ENOBUFS:
  case EISCONN:
  case ENOTCONN:
  case ESHUTDOWN:
  case ETOOMANYREFS:
  case ETIMEDOUT:
  case ECONNREFUSED:
  case ELOOP:
  case ENAMETOOLONG:
  case EHOSTDOWN:
  case EHOSTUNREACH:
  case ENOTEMPTY:
    //  case EPROCLIM:
  case EUSERS:
  case EDQUOT:
    return true;
  }
  return false;
}

bool sockerr::conn () const
// return true if err is EISCONN, ENOTCONN, ECONNRESET, ECONNREFUSED,
// ETIMEDOUT, or EPIPE
{
  switch (err) {
  case EISCONN:
  case ENOTCONN:
  case ECONNRESET:
  case ECONNREFUSED:
  case ETIMEDOUT:
  case EPIPE:
    return true;
  }
  return false;
}

bool sockerr::addr () const
// return true if err is EADDRINUSE or EADDRNOTAVAIL
{
  switch (err) {
  case EADDRINUSE:
  case EADDRNOTAVAIL:
    return true;
  }
  return false;
}

bool sockerr::benign () const
// return true if err is EINTR, EWOULDBLOCK, or EAGAIN
{
  switch (err) {
  case EINTR:
  case EWOULDBLOCK:
    //  case EAGAIN:
    return true;
  }
  return false;
}

sockunixaddr::sockunixaddr (const char *path)
{
  sun_family = sockunixbuf::af_unix;
  ::strcpy (sun_path, path);
}

sockunixaddr::sockunixaddr (const sockunixaddr &suna)
{
  sun_family = sockunixbuf::af_unix;
  ::strcpy (sun_path, suna.sun_path);
}

sockinetaddr::sockinetaddr () 
{
  sin_family	  = sockinetbuf::af_inet;
  sin_addr.s_addr = htonl(INADDR_ANY);
  sin_port	  = 0;
}

sockinetaddr::sockinetaddr(unsigned long addr, int port_no)
// addr and port_no are in host byte order
{
  sin_family      = sockinetbuf::af_inet;
  sin_addr.s_addr = htonl(addr);
  sin_port	  = htons(port_no);
}

sockinetaddr::sockinetaddr(unsigned long addr, const char *sn, const char *pn)
// addr is in host byte order
{
  sin_family      = sockinetbuf::af_inet;
  sin_addr.s_addr = htonl (addr); // Added by cgay@cs.uoregon.edu May 29, 1993
  setport(sn, pn);
}

sockinetaddr::sockinetaddr (const char *host_name, int port_no)
// port_no is in host byte order
{
  setaddr(host_name);
  sin_port = htons(port_no);
}

sockinetaddr::sockinetaddr(const char *hn, const char *sn, const char *pn)
{
  setaddr(hn);
  setport(sn, pn);
}

sockinetaddr::sockinetaddr (const sockinetaddr &sina)
{
  sin_family      = sockinetbuf::af_inet;
  sin_addr.s_addr = sina.sin_addr.s_addr;
  sin_port	  = sina.sin_port;
}   

void sockinetaddr::setport(const char *sn, const char *pn)
{
  servent *sp = getservbyname(sn, pn);
  if (sp == 0) throw sockerr (EADDRNOTAVAIL);
  sin_port = sp->s_port;
}

int sockinetaddr::getport () const
{
  return ntohs (sin_port);
}

void sockinetaddr::setaddr(const char *host)
{
#if 0
  if ((sin_addr.s_addr = inet_addr(host)) == -1)
    {
      hostent *hp = gethostbyname(host);
      memcpy(&sin_addr, hp->h_addr, hp->h_length);
      sin_family = hp->h_addrtype;
    }
  else sin_family = sockinetbuf::af_inet;
#else
  in_addr ia;
  if (inet_aton(host, &ia) == 0)
    {
      hostent *hp = gethostbyname(host);
      memcpy(&sin_addr, hp->h_addr, hp->h_length);
      sin_family = hp->h_addrtype;
    }
  else
    {
      sin_addr.s_addr = inet_lnaof(ia);
      sin_family = sockinetbuf::af_inet;
    }
#endif
}

const char* sockinetaddr::gethostname () const
{
  if (sin_addr.s_addr == htonl(INADDR_ANY))
    {
      static char hostname[64];
      if (::gethostname(hostname, 63) == -1) return "";
      return hostname;		
    }
  hostent *hp = gethostbyaddr((const char *) &sin_addr, sizeof(sin_addr), family());
  if (hp == 0) return "";
  if (hp->h_name) return hp->h_name;
  return "";
}

socketbuf::socketbuf (int domain, socketbuf::type st, int proto)
  : ipcbuf(ios::in|ios::out)
{
  data->fd = ::socket (domain, st, proto);
  if (data->fd == -1) throw sockerr (errno);
}

int socketbuf::getopt (int op, void *buf, socklen_t len, int level) const
{
  if (::getsockopt (data->fd, level, op, (char *)buf, &len) == -1) throw sockerr (errno);
  return len;
}

void socketbuf::setopt (int op, void *buf, socklen_t len, int level) const
{
  if (::setsockopt (data->fd, level, op, (char *) buf, len) == -1) throw sockerr (errno);
}

void socketbuf::bind (const socketaddr &sa)
{
  if (::bind (data->fd, sa.addr(), sa.size()) == -1) throw sockerr (errno);
}

void socketbuf::connect (const socketaddr &sa)
{
  if (::connect(data->fd, sa.addr(), sa.size()) == -1) throw sockerr (errno);
}

void socketbuf::listen (int num)
{
  if (::listen (data->fd, num) == -1) throw sockerr (errno);
}

int socketbuf::accept (const socketaddr &sa)
{
  socklen_t len = sa.size();
  int soc = -1;
  if ((soc = ::accept (data->fd, sa.addr(), &len)) == -1) throw sockerr (errno);
  return soc;
}

int socketbuf::accept()
{
  int soc = -1;
  if ((soc = ::accept (data->fd, 0, 0)) == -1) throw sockerr (errno);
  return soc;
}

socketbuf::socklinger socketbuf::linger () const
{
  socklinger old (0, 0);
  getopt (so_linger, &old, sizeof (old));
  return old;
}

socketbuf::socklinger socketbuf::linger (socketbuf::socklinger opt) const
{
  socklinger old (0, 0);
  getopt (so_linger, &old, sizeof (old));
  setopt (so_linger, &opt, sizeof (opt));
  return old;
}

socketbuf::type socketbuf::gettype () const
{
  int ty=0;
  getopt (so_type, &ty, sizeof (ty));
  return socketbuf::type(ty);
}

int socketbuf::clearerror () const
{
  int err=0;
  getopt (so_error, &err, sizeof (err));
  return err;
}

bool socketbuf::debug () const
{
  int old = 0;
  getopt (so_debug, &old, sizeof (old));
  return old;
}

bool socketbuf::debug (bool set) const
{
  int old=0;
  int opt = set;
  getopt (so_debug, &old, sizeof (old));
  try
    {
      setopt (so_debug, &opt, sizeof (opt));
    }
  catch (sockerr e) { cerr << errno << ' ' << e.errstr() << endl;}
  return old;
}

bool socketbuf::reuseaddr () const
{
  int old = 0;
  getopt (so_reuseaddr, &old, sizeof (old));
  return old;
}

bool socketbuf::reuseaddr (bool set) const
{
  int old=0;
  int opt = set;
  getopt (so_reuseaddr, &old, sizeof (old));
  setopt (so_reuseaddr, &opt, sizeof (opt));
  return old;
}

bool socketbuf::keepalive () const
{
  int old = 0;
  getopt (so_keepalive, &old, sizeof (old));
  return old;
}

bool socketbuf::keepalive (bool set) const
{
  int old=0;
  int opt = set;
  getopt (so_keepalive, &old, sizeof (old));
  setopt (so_keepalive, &opt, sizeof (opt));
  return old;
}

sockunixbuf &sockunixbuf::operator = (const sockunixbuf &su)
{
  socketbuf::operator = (su);
  return *this;
}

sockinetbuf &sockinetbuf::operator = (const sockinetbuf &si)
{
  socketbuf::operator = (si);
  return *this;
}

sockinetaddr sockinetbuf::localaddr() const
{
  sockinetaddr sin;
  socklen_t len = sin.size();
  if (::getsockname(data->fd, sin.addr(), &len) == -1) throw sockerr (errno);
  return sin;
}

int sockinetbuf::localport() const
{
  sockinetaddr sin = localaddr();
  if (sin.family() != af_inet) return -1;
  return sin.getport();
}

const char *sockinetbuf::localhost() const
{
  sockinetaddr sin = localaddr();
  if (sin.family() != af_inet) return "";
  return sin.gethostname();
}

sockinetaddr sockinetbuf::peeraddr() const
{
  sockinetaddr sin;
  socklen_t len = sin.size();
  if (::getpeername(data->fd, sin.addr(), &len) == -1) throw sockerr (errno);
  return sin;
}

int sockinetbuf::peerport() const
{
  sockinetaddr sin = peeraddr();
  if (sin.family() != af_inet) return -1;
  return sin.getport();
}

const char *sockinetbuf::peerhost() const
{
  sockinetaddr sin = peeraddr();
  if (sin.family() != af_inet) return "";
  return sin.gethostname();
}

void sockinetbuf::bind_until_success (int portno)
// a. bind to (INADDR_ANY, portno)
// b. if success return
// c. if failure and errno is EADDRINUSE, portno++ and go to step a.
{
  for (;;)
    {
      try
	{
	  bind (portno++);
	}
      catch (sockerr e)
	{
	  if (e.number() != EADDRINUSE) throw;
	  continue;
	}
      break;
    }
}

void sockinetbuf::bind (unsigned long addr, const char *service, const char *protocol)
{
  bind(sockinetaddr(addr, service, protocol));
}

void sockinetbuf::bind (const char *host, const char *service, const char *protocol)
{
  bind(sockinetaddr(host, service, protocol));
}

void sockinetbuf::connect (unsigned long addr, const char *service, const char *protocol)
{
  connect(sockinetaddr(addr, service, protocol));
}

void sockinetbuf::connect (const char *host, const char *service, const char *protocol)
{
  connect(sockinetaddr(host, service, protocol));
}

int sockinetbuf::accept ()
{
  return socketbuf::accept ();
}

int sockinetbuf::accept (const socketaddr &sa)
{
  return socketbuf::accept(sa);
}

int sockinetbuf::accept (unsigned long addr, int port)
{
  return accept(sockinetaddr(addr, port));
}

int sockinetbuf::accept (const char *host, int port)
{
  return accept(sockinetaddr(host, port));
}

bool sockinetbuf::tcpnodelay () const
{
  struct protoent *proto = getprotobyname ("tcp");
  if (proto == 0) throw sockerr (ENOPROTOOPT);
  int old = 0;
  getopt (TCP_NODELAY, &old, sizeof (old), proto->p_proto);
  return old;
}

bool sockinetbuf::tcpnodelay (bool set) const
{
  struct protoent *proto = getprotobyname ("tcp");
  if (proto == 0) throw sockerr (ENOPROTOOPT);
  int old = 0;
  int opt = set;
  getopt (TCP_NODELAY, &old, sizeof (old), proto->p_proto);
  setopt (TCP_NODELAY, &opt, sizeof (opt), proto->p_proto);
  return old;
}


