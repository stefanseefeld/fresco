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
/*$Id$*/
#ifndef _socketbuf_hh
#define _socketbuf_hh
#include <Prague/IPC/ipcbuf.hh>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>

#ifdef __linux__
#  define MSG_MAXIOVLEN	 16
#endif // __linux__

#ifdef __sgi__
typedef int socklen_t;
#endif // __sgi__

// socket exception classes
class sockerr
{
public:
  sockerr (int e): err (e) {}
  const char* what () const { return "sockerr"; }
  int number () const { return err; }
  const char *errstr () const;
  bool error (int eno) const { return eno == err; }
  bool io () const;     // non-blocking and interrupt io recoverable error.
  bool arg () const;    // incorrect argument supplied. recoverable error.
  bool op () const;     // operational error. recovery difficult.
  bool conn () const;   // connection error
  bool addr () const;   // address error
  bool benign () const; // recoverable read/write error like EINTR etc.
private:
  int  err;
};

class sockoob
{
public:
  const char* what () const { return "sockoob"; }
};

struct sockaddr;

/* @Class{socketaddr}
 *
 * @Description{abstract base for socket addresses}
 */
class socketaddr
{
public:
  virtual	   ~socketaddr() {}
  virtual operator void *() const =0;
  operator sockaddr *() const { return addr ();}
  virtual int	    size() const =0;
  virtual int	    family() const =0;
  virtual sockaddr *addr() const =0;
};

/* @Class{sockunixaddr : public socketaddr, public sockaddr_un}
 *
 * @Description{socket unix address representation}
 */
class sockunixaddr: public socketaddr, public sockaddr_un
{
public:
  ~sockunixaddr () {}
  sockunixaddr (const char *path);
  sockunixaddr (const sockunixaddr &suna);
  operator void *() const { return addr_un();}
  sockaddr_un   *addr_un() const { return (sockaddr_un *)(this);}
  int            size () const { return sizeof (sockaddr_un);}
  int            family () const { return sun_family; }
  sockaddr      *addr() const {return (sockaddr *)(addr_un ());}
};

/* @Class{sockinetaddr : public socketaddr, public sockaddr_in}
 *
 * @Description{socket internet address representation}
 */
class sockinetaddr : public socketaddr, public sockaddr_in
{
protected:
  void setport (const char *, const char* pn = "tcp");
  void setaddr (const char *);
public:
  ~sockinetaddr () {}
  sockinetaddr ();
  sockinetaddr (unsigned long, int port_no=0);
  sockinetaddr (const char *, int port_no=0);
  sockinetaddr (unsigned long, const char *, const char *protocol_name = "tcp");
  sockinetaddr (const char *, const char *, const char *protocol_name = "tcp");
  sockinetaddr (const sockinetaddr& sina);
  operator void *() const { return addr_in ();}
  sockaddr_in   *addr_in() const { return (sockaddr_in*) this; }
  int            size() const { return sizeof (sockaddr_in); }
  int            family() const { return sin_family; }
  sockaddr      *addr  () const { return (sockaddr *)(addr_in()); }
  int            getport    () const;
  const char    *gethostname() const;
};

struct msghdr;

/* @Class{socketbuf : public ipcbuf}
 *
 * @Description{an ipcbuf based on a socket}
 */
class socketbuf : public ipcbuf
{
public:
  enum type
  {
    sock_stream	        = SOCK_STREAM,
    sock_dgram	        = SOCK_DGRAM,
    sock_raw	        = SOCK_RAW,
    sock_rdm	        = SOCK_RDM,
    sock_seqpacket      = SOCK_SEQPACKET
  };
  enum option
  {
    so_debug	        = SO_DEBUG,
    so_reuseaddr	= SO_REUSEADDR,
    so_keepalive	= SO_KEEPALIVE,
    so_dontroute	= SO_DONTROUTE,
    so_broadcast	= SO_BROADCAST,
    so_linger	        = SO_LINGER,
    so_oobinline	= SO_OOBINLINE,
    so_sndbuf		= SO_SNDBUF,
    so_rcvbuf		= SO_RCVBUF,
    so_error		= SO_ERROR,
    so_type		= SO_TYPE
  };	
  enum level
  {
    sol_socket          = SOL_SOCKET
  };
  enum msgflag
  {
    msg_oob		= MSG_OOB,
    msg_peek	        = MSG_PEEK,
    msg_dontroute	= MSG_DONTROUTE,
	
    msg_maxiovlen	= MSG_MAXIOVLEN
  };
  enum shuthow
  {
    shut_read,
    shut_write,
    shut_readwrite
  };
  enum { somaxconn	= SOMAXCONN };
  struct socklinger
  {
    int	l_onoff;	// option on/off
    int	l_linger;	// linger time
    socklinger (int a, int b): l_onoff (a), l_linger (b) {}
  };

  socketbuf (int s) : ipcbuf(ios::in|ios::out) { data->fd = s;}
  socketbuf (int, type, int);
  socketbuf (const socketbuf &sb) : ipcbuf(sb) {}
  virtual           ~socketbuf () {}
  virtual void       bind (const socketaddr &);
  virtual void       connect(const socketaddr &);
  void               listen(int num = somaxconn);
  virtual int        accept();
  virtual int        accept(const socketaddr &);
  int                read(void *, int);
  int		     recv(void *, int, int msgf = 0);
  int		     recvfrom(socketaddr &, void *, int, int msgf = 0);
#ifndef __linux__
  int		     recvmsg(msghdr *, int msgf = 0);
  int		     sendmsg(msghdr *, int msgf = 0);
#endif
  int		     write(const void *, int);
  int		     send(const void *, int, int msgf = 0);
  int		     sendto(socketaddr &, const void *, int, int msgf = 0);
  int		     sendtimeout(int wp = -1);
  int		     recvtimeout(int wp = -1);
  void		     shutdown(shuthow);
  int		     getopt(int, void *, socklen_t, int level = sol_socket) const;
  void		     setopt(int, void *, socklen_t, int level = sol_socket) const;
  type		     gettype () const;
  int		     clearerror () const;
  bool		     debug() const;
  bool		     debug(bool) const;
  bool		     reuseaddr() const;
  bool		     reuseaddr(bool) const;
  bool		     keepalive() const;
  bool		     keepalive(bool) const;
  bool		     dontroute() const;
  bool		     dontroute(bool) const;
  bool		     broadcast() const;
  bool		     broadcast(bool) const;
  bool		     oobinline() const;
  bool		     oobinline(bool) const;
  bool               oob() const { return data->oobbit;}
  bool               oob(bool);
  int		     sendbufsz() const;
  int		     sendbufsz(int)   const;
  int		     recvbufsz() const;
  int		     recvbufsz(int)   const;
  socklinger       linger() const;
  socklinger       linger(socklinger) const;
  socklinger       linger(int onoff, int tm) const { return linger(socklinger(onoff, tm));}
  bool               atmark() const;  
  int                pgrp() const;
  int                pgrp(int) const;
  void               closeonexec(bool set = true) const;
  long               nread() const;
  long               howmanyc() const;
  void               nbio(bool set = true) const;
  void               async(bool set = true) const;
protected:
};

/* @Class{sockunixbuf : public socketbuf}
 *
 * @Description{a socketbuf for the unix domain}
 */
class sockunixbuf : public socketbuf
{
public:
  enum domain { af_unix = AF_UNIX };
  sockunixbuf(int s) : socketbuf(s) {}
  sockunixbuf (const sockunixbuf &su) : socketbuf(su) {}
  sockunixbuf (socketbuf::type ty, int proto = 0) : socketbuf(af_unix, ty, proto) {}
  sockunixbuf &operator = (const sockunixbuf &);
  ~sockunixbuf () {}
  virtual void bind (const socketaddr &sa) { socketbuf::bind(sa);}
  void         bind (const char *path) { bind(sockunixaddr(path));}
  virtual void connect (const socketaddr &sa) { socketbuf::connect(sa);}
  void         connect (const char *path) { connect(sockunixaddr(path));}
};

/* @Class{sockinetbuf : public socketbuf}
 *
 * @Description{a socketbuf for the internet domain}
 */
class sockinetbuf : public socketbuf
{
public:
  enum domain { af_inet = AF_INET };
  sockinetbuf (int s) : socketbuf(s) {}
  sockinetbuf (const sockinetbuf &si): socketbuf (si) {}
  sockinetbuf (socketbuf::type ty, int proto = 0) : socketbuf(af_inet, ty, proto) {}
  sockinetbuf &operator = (const sockinetbuf &);
  ~sockinetbuf () {}
  sockinetaddr localaddr() const;
  int          localport() const;
  const char  *localhost() const;
  sockinetaddr peeraddr() const;
  int          peerport() const;
  const char  *peerhost() const;
  void         bind_until_success (int);
  virtual void bind(const socketaddr &sa) { socketbuf::bind(sa);}
  void	       bind(int port = 0) { bind(sockinetaddr((unsigned long) INADDR_ANY, port));}
  void	       bind(unsigned long addr, int port) { bind(sockinetaddr(addr, port));}
  void	       bind(const char *host, int port = 0) { bind(sockinetaddr(host, port));}
  void	       bind(unsigned long, const char *, const char *protocol = "tcp");
  void	       bind(const char *, const char *, const char *protocol_name = "tcp");
  virtual void connect (const socketaddr &sa) {socketbuf::connect(sa);}
  void	       connect (unsigned long addr, int port) { connect(sockinetaddr(addr, port));}
  void	       connect (const char *host, int port) { connect(sockinetaddr(host, port));}
  void	       connect (unsigned long, const char *, const char *protocol_name = "tcp");
  void         connect (const char *, const char *, const char *protocol_name = "tcp");
  virtual int  accept ();
  virtual int  accept (const socketaddr &);
  int          accept (unsigned long, int);
  int          accept (const char *, int);
  bool         tcpnodelay () const;
  bool         tcpnodelay (bool set) const;
};

#endif /* _socketbuf_hh */
