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
#ifndef _DefaultPOA_hh
#define _DefaultPOA_hh

#include <Warsaw/config.hh>
#include <Warsaw/Types.hh>

//. A mixin class to use a single global POA as the default POA. This is used
//. by the "shortcut POA" for omniORB so that all objects (using the class)
//. use the POA with the shortcut policy.
class DefaultPOA
{
public:
  //. Set the global poa. This should only be called once, in whatever method
  //. creates the global poa (eg: the main() function creating the shortcut poa
  //. for omniORB in server/server.cc)
  static void default_POA(PortableServer::POA_ptr);

  //. Mixin virtual method to return a duplicate ptr to the global poa.
  virtual PortableServer::POA_ptr _default_POA();

private:
  //. The global poa
  static PortableServer::POA_var _default_poa;
};

#endif
