// ip.h -*- C++ -*- socket library
// Copyright (C) 1992-1996 Gnanasekaran Swaminathan <gs4t@virginia.edu>
//
// Permission is granted to use at your own risk and distribute this software
// in source and  binary forms provided  the above copyright notice and  this
// paragraph are  preserved on all copies.  This software is provided "as is"
// with no express or implied warranty.

#include <Prague/Network/ip.hh>

const char *ip::ipbuf::ip_name () const
{
  char *ret = "";
  if (pn == ip::tcp) ret = "tcp";
  if (pn == ip::udp) ret = "udp";
  return ret;
}

void ip::ipbuf::connect ()
{
  //  if (pn == ip::nil) throw socketerr (EPROTONOSUPPORT);
  sockinetbuf::connect (localhost (), rfc_name (), ip_name ());
}

void ip::ipbuf::connect (unsigned long addr)
     // addr is in host byte order
{
  //  if (pn == ip::nil) throw sockerr (EPROTONOSUPPORT);
  sockinetbuf::connect (addr, rfc_name (), ip_name ());
}

void ip::ipbuf::connect (const char* host)
{
//   if (pn == ip::nil) throw sockerr (EPROTONOSUPPORT);
  sockinetbuf::connect (host, rfc_name (), ip_name ());
}

void ip::ipbuf::connect (const char* host, int portno)
{
//   if (pn == ip::nil) throw sockerr (EPROTONOSUPPORT);
  sockinetbuf::connect (host, portno);
}

