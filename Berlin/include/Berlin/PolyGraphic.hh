/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@berlin-consortium.org> 
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
#ifndef _PolyGraphic_hh
#define _PolyGraphic_hh

#include <Berlin/GraphicImpl.hh>
#include <Berlin/Pool.hh>
#include <vector>

class PolyGraphic : public GraphicImpl
{
public:
  PolyGraphic();
  virtual ~PolyGraphic();

  virtual void append(Warsaw::Graphic_ptr);
  virtual void prepend(Warsaw::Graphic_ptr);
  virtual void remove(Warsaw::Tag);
  virtual void removeChild(Warsaw::Tag);
  virtual Iterator_ptr firstChild();
  virtual Iterator_ptr lastChild();

  virtual void needResize();
  virtual void needResize(Warsaw::Tag);
protected:
  CORBA::Long numChildren();
  Warsaw::Tag uniqueChildId();
  glist_t::iterator childIdToIterator(Warsaw::Tag);
  CORBA::Long childIdToIndex(Warsaw::Tag);
  Warsaw::Graphic::Requisition *childrenRequests();
  void deallocateRequisitions(Warsaw::Graphic::Requisition *);
  void childExtension(size_t, const Warsaw::Allocation::Info &, Warsaw::Region_ptr);
// private:
  static Pool<Warsaw::Graphic::Requisition> pool;
  glist_t children;
  Prague::Mutex childMutex;
};

/*
 * the following methods are inlined for speed.
 * Attention : they must be used within a PolyGraphic::childMutex locked section !
 */
inline Warsaw::Tag PolyGraphic::uniqueChildId()
{
  Warsaw::Tag localId = 0;
  do
    if (find_if(children.begin(), children.end(), localId_eq(localId)) == children.end())
      return localId;
  while(++localId);
}

inline PolyGraphic::glist_t::iterator PolyGraphic::childIdToIterator(Warsaw::Tag localId)
{
  return find_if(children.begin(), children.end(), localId_eq(localId));
}

inline CORBA::Long PolyGraphic::childIdToIndex(Warsaw::Tag localId)
{
  return find_if(children.begin(), children.end(), localId_eq(localId)) - children.begin();
}

#endif 
