/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
 * http://www.berlin-consortium.org
 *
 * this code is based on code from Fresco.
 * Copyright (c) 1987-91 Stanford University
 * Copyright (c) 1991-94 Silicon Graphics, Inc.
 * Copyright (c) 1993-94 Fujitsu, Ltd.
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

#include <string.h>

class Memory
{
public:
  inline static void copy(const void *from, void *to, unsigned long nbytes);
  inline static int compare(const void *, const void *, unsigned long nbytes);
  inline static void zero(void *, unsigned long nbytes);
};

void Memory::copy(const void *from, void *to, unsigned long nbytes)
{
  if (nbytes > 0)
    {
#if defined(__sun) && !defined(__SVR4)
      bcopy(from, to, nbytes);
#else
      memmove(to, from, size_t(nbytes));
#endif
    }
}

int Memory::compare(const void *b1, const void *b2, unsigned long nbytes)
{
  return memcmp(b1, b2, size_t(nbytes)) != 0;
}

void Memory::zero(void* b, unsigned long nbytes)
{
  memset(b, 0, size_t(nbytes));
}

#endif /* _Memory_hh */
