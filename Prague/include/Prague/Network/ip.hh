// ip.h -*- C++ -*- socket library
// Copyright (C) 1992-1996 Gnanasekaran Swaminathan <gs4t@virginia.edu>
//
// Permission is granted to use at your own risk and distribute this software
// in source and  binary forms provided  the above copyright notice and  this
// paragraph are  preserved on all copies.  This software is provided "as is"
// with no express or implied warranty.
//
// Version: 12Jan97 1.11

#ifndef _ip_hh
#define _ip_hh

#include <Prague/IPC/sockstream.hh>

/* @Class{ip : public iosockstream}
 *
 * @Description{abstract base for internet protocols}
 */
class ip : public iosockstream
{
public:
  enum p_name
  {
    nil = 0,
    tcp = socketbuf::sock_stream,
    udp = socketbuf::sock_dgram
  };
  class ipbuf : public sockinetbuf
  {
  public:
    ipbuf (sockinetbuf& si): sockinetbuf (si), pn (ip::nil) {}
    ipbuf (ip::p_name pname) : sockinetbuf ((socketbuf::type) pname, 0), pn (pname) {}
    void                bind () { serve_clients (); }
    void                connect ();
    void                connect (unsigned long addr);
    void                connect (const char* host);
    void                connect (const char* host, int portno);

    const char*         ip_name () const;

    virtual void        serve_clients (int portno = -1) = 0;
    virtual const char *rfc_name () const = 0;
    virtual const char *rfc_doc  () const = 0;
  private:
    ip::p_name pn;
    void bind (socketaddr &sa) { socketbuf::bind(sa);}
    void connect (socketaddr &sa) { socketbuf::connect(sa);}
  };
  ip () : ios (0) {}
};

#endif /* ip_hh */
