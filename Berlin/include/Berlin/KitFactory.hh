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
#ifndef _KitFactory_hh
#define _KitFactory_hh

#include <Warsaw/config.hh>
#include <Warsaw/Kit.hh>
#include <string>

class ServerContextImpl;
class KitImpl;

class KitFactory
{
  friend class KitImpl;
public:
  KitFactory(const string &, const string *, unsigned short);
  virtual ~KitFactory() { delete props;}
  const string &type() const { return id;}
  Kit::PropertySeq *properties() const { return new Kit::PropertySeq(*props);}  
  virtual KitImpl *create(const Kit::PropertySeq &p) = 0;
  virtual bool supports(const Kit::PropertySeq &p) { return supports(*props, p);}
  static bool supports(const Kit::PropertySeq &, const Kit::PropertySeq &);
protected:
  void increment() { counter++;}
  void decrement() { counter--;}
  Kit::PropertySeq *props;
private:
  const string      id;
  unsigned short    counter;
};

#endif
