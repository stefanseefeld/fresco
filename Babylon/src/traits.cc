/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999-2003 Tobias Hunger <Tobias@fresco.org>
 * http://www.fresco.org
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

#if __GNUC__ >= 3

#include <Babylon/internal/traits.hh>

#include <cstring>

namespace std {

char_traits<Babylon::Char>::char_type *
std::char_traits<Babylon::Char>::move(char_type * s,
                      const char_type * s2,
                      size_t n)
{
  return static_cast<char_type *>
    (std::memmove(s, s2, n * sizeof(char_type)));
}
std::char_traits<Babylon::Char>::char_type *
std::char_traits<Babylon::Char>::copy(char_type * s,
                      const char_type * s2,
                      size_t n)
{
  return static_cast<char_type *>
    (std::memcpy(s, s2, n * sizeof(char_type)));
}

std::char_traits<Babylon::Char>::char_type *
std::char_traits<Babylon::Char>::assign(char_type * s,
                    size_t n,
                    char_type a)
{
  for (size_t i = 0; i < n; ++i)
    assign(s[i], a);
  return s; 
}

int
std::char_traits<Babylon::Char>::compare(const char_type * s,
                     const char_type * s2,
                     size_t n)
{
  for (size_t i = 0; i < n; ++i)
    {
      if (eq(s[i], s2[i])) continue;
      if (lt(s[i], s2[i])) return -1;
      else return 1;
    }
  return 0;
}

size_t
std::char_traits<Babylon::Char>::length(const char_type * s)
{
  size_t i = 0;
  while (!(eq(s[i], Babylon::Char(Babylon::UC_NULL)))) ++i;
  return i;
}

const std::char_traits<Babylon::Char>::char_type *
std::char_traits<Babylon::Char>::find(const char_type * s,
                      size_t n,
                      const char_type& c)
{
  size_t i = 0;
  while (!(eq(s[i], c))) ++i;
  
  return s + i;
}

std::char_traits<Babylon::Char>::int_type
std::char_traits<Babylon::Char>::not_eof(const int_type & i)
{
  if (eof() == i)
    return(Babylon::UC_NOT_A_CHAR);
  return(i);
}



void
std::char_traits<Babylon::UCS2>::assign(char_type & c1,
                    const char_type & c2)
{ c1 = c2; }

std::char_traits<Babylon::UCS2>::char_type
std::char_traits<Babylon::UCS2>::to_char_type(const int_type& i) { return(i); }
  
std::char_traits<Babylon::UCS2>::int_type
std::char_traits<Babylon::UCS2>::to_int_type(const char_type& c) { return(c); }

bool
std::char_traits<Babylon::UCS2>::eq_int_type(const int_type& i1,
                         const int_type& i2)
{
  return(i1 == i2);
}

bool
std::char_traits<Babylon::UCS2>::eq(const char_type& c1,
                    const char_type& c2) { return(c1 == c2); }

bool
std::char_traits<Babylon::UCS2>::lt(const char_type& c1,
                    const char_type& c2) { return(c1 < c2); }

char_traits<Babylon::UCS2>::char_type *
std::char_traits<Babylon::UCS2>::move(char_type * s,
                      const char_type * s2,
                      size_t n)
{
  return static_cast<char_type *>
    (std::memmove(s, s2, n * sizeof(char_type)));
}
std::char_traits<Babylon::UCS2>::char_type *
std::char_traits<Babylon::UCS2>::copy(char_type * s,
                      const char_type * s2,
                      size_t n)
{
  return static_cast<char_type *>
    (std::memcpy(s, s2, n * sizeof(char_type)));
}

std::char_traits<Babylon::UCS2>::char_type *
std::char_traits<Babylon::UCS2>::assign(char_type * s,
                    size_t n,
                    char_type a)
{
  for (size_t i = 0; i < n; ++i)
    assign(s[i], a);
  return s; 
}

int
std::char_traits<Babylon::UCS2>::compare(const char_type * s,
                     const char_type * s2,
                     size_t n)
{
  for (size_t i = 0; i < n; ++i)
    {
      if (eq(s[i], s2[i])) continue;
      if (lt(s[i], s2[i])) return -1;
      else return 1;
    }
  return 0;
}

size_t
std::char_traits<Babylon::UCS2>::length(const char_type * s)
{
  size_t i = 0;
  while (!(eq(s[i], Babylon::UCS2(0)))) ++i;
  return i;
}

const std::char_traits<Babylon::UCS2>::char_type *
std::char_traits<Babylon::UCS2>::find(const char_type * s,
                      size_t n,
                      const char_type& c)
{
  size_t i = 0;
  while (!(eq(s[i], c))) ++i;
  
  return s + i;
}

std::char_traits<Babylon::UCS2>::int_type
std::char_traits<Babylon::UCS2>::eof() { return(Babylon::UC_NULL); }

std::char_traits<Babylon::UCS2>::int_type
std::char_traits<Babylon::UCS2>::not_eof(const int_type & i)
{
  if (eof() == i)
    return(Babylon::UCS2(Babylon::UC_NOT_A_CHAR));
  return(i);
}



void
std::char_traits<Babylon::UCS4>::assign(char_type & c1,
                    const char_type & c2)
{ c1 = c2; }

std::char_traits<Babylon::UCS4>::char_type
std::char_traits<Babylon::UCS4>::to_char_type(const int_type& i) { return(i); }
  
std::char_traits<Babylon::UCS4>::int_type
std::char_traits<Babylon::UCS4>::to_int_type(const char_type& c) { return(c); }

bool
std::char_traits<Babylon::UCS4>::eq_int_type(const int_type& i1,
                         const int_type& i2)
{
  return(i1 == i2);
}

bool
std::char_traits<Babylon::UCS4>::eq(const char_type& c1,
                    const char_type& c2) { return(c1 == c2); }

bool
std::char_traits<Babylon::UCS4>::lt(const char_type& c1,
                    const char_type& c2) { return(c1 < c2); }

std::char_traits<Babylon::UCS4>::char_type *
std::char_traits<Babylon::UCS4>::move(char_type * s,
                      const char_type * s2,
                      size_t n)
{
  return static_cast<char_type *>
    (std::memmove(s, s2, n * sizeof(char_type)));
}

std::char_traits<Babylon::UCS4>::char_type *
std::char_traits<Babylon::UCS4>::copy(char_type * s,
                      const char_type * s2,
                      size_t n)
{
  return static_cast<char_type *>
    (std::memcpy(s, s2, n * sizeof(char_type)));
}

std::char_traits<Babylon::UCS4>::char_type *
std::char_traits<Babylon::UCS4>::assign(char_type * s,
                    size_t n,
                    char_type a)
{
  for (size_t i = 0; i < n; ++i)
    assign(s[i], a);
  return s; 
}

int
std::char_traits<Babylon::UCS4>::compare(const char_type * s,
                     const char_type * s2,
                     size_t n)
{
  for (size_t i = 0; i < n; ++i)
    {
      if (eq(s[i], s2[i])) continue;
      if (lt(s[i], s2[i])) return -1;
      else return 1;
    }
  return 0;
}

size_t
std::char_traits<Babylon::UCS4>::length(const char_type * s)
{
  size_t i = 0;
  while (!(eq(s[i], Babylon::UCS2(0)))) ++i;
  return i;
}

const std::char_traits<Babylon::UCS4>::char_type *
std::char_traits<Babylon::UCS4>::find(const char_type * s,
                      size_t n,
                      const char_type& c)
{
  size_t i = 0;
  while (!(eq(s[i], c))) ++i;
  
  return s + i;
}

std::char_traits<Babylon::UCS4>::int_type
std::char_traits<Babylon::UCS4>::eof() { return(Babylon::UC_NULL); }

std::char_traits<Babylon::UCS4>::int_type
std::char_traits<Babylon::UCS4>::not_eof(const int_type & i)
{
  if (eof() == i)
    return(Babylon::UCS4(Babylon::UC_NOT_A_CHAR));
  return(i);
}

}; // namespace std

#endif // __GNUC__ >= 3
