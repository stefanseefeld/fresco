/* $Id$ */
#ifndef _cstream_hh
#define _cstream_hh

#include <iostream>
#include <Prague/Filter/cbuf.hh>

/*
 *	Class name : cstream
 *
 *	Description : a specialized istream for input containing comments...
 */
class cstream : public istream
{
public:
  cstream(istream &is, char comment = '#') : istream(new cbuf(is.rdbuf(), comment)) {}
};

#endif
