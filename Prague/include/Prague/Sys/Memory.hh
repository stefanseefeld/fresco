/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
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
#ifndef _Memory_hh
#define _Memory_hh

#include <cstring>

namespace Prague
{

/* @Class {Memory}
 *
 * @Description{wrappes low level memory manipulation}
 */
class Memory
{
public:
  inline static void *copy(const void *, void *, unsigned long);
  inline static void *move(const void *, void *, unsigned long);
  inline static void *zero(void *, unsigned long);
  inline static int  compare(const void *, const void *, unsigned long);
};

/* @Method{void Memory::copy(const void *from, void *to, unsigned long n)}
 *
 * @Description{copies @var{n} bytes from position @var{from} to position @var{to}}
 */
void *Memory::copy(const void *from, void *to, unsigned long n)
{
  if (n > 0)
    {
#if defined(__sun) && !defined(__SVR4)
      return bcopy(from, to, n);
#else
      return memmove(to, from, size_t(n));
#endif
    }
  return to;
}

/* @Method{void Memory::move(const void *from, void *to, unsigned long n)}
 *
 * @Description{moves @var{n} bytes from position @var{from} to position @var{to}}
 */
void *Memory::move(const void *from, void *to, unsigned long n)
{
  if (n > 0) return memmove(to, from, size_t(n));
  else return to;
}

/* @Method{void Memory::zero(void *b, unsigned long n)}
 *
 * @Description{sets @var{n} bytes to zero starting at @var{b}}
 */
void *Memory::zero(void *b, unsigned long n)
{
  return memset(b, 0, size_t(n));
}

/* @Method{void Memory::compare(const void *p, const void *q, unsigned long n)}
 *
 * @Description{compares @var{n} bytes starting at @var{p} and @var{q}. The returned value is the position of the first mismatch.}
 */
int Memory::compare(const void *p, const void *q, unsigned long n)
{
  return memcmp(p, q, size_t(n)) != 0;
}

};

#endif /* _Memory_hh */
