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
#ifndef _Berlin_GapBuffer_hh
#define _Berlin_GapBuffer_hh

#include <vector>

namespace Berlin
{

  /*
   * the design of a gap buffer should follow the typical behavior
   * when editing text. Editing text has two parts: modifying it
   * and simply browsing it. The text contains a 'cursor', which indicates
   * the actual position. When in editing mode, we have to take care to
   * use smart memory management. For this purpose we introduce a little
   * memory gap into the string where new characters can be inserted,
   * so not on every insert() all the following characters have to be moved
   *
   * a gap buffer is layed out like this:
   *   
   *   |***********************..........**********|
   *   ^                      ^         ^          ^
   *  begin()                gbegin()  gend()     end()
   *
   * the following (in)equalities should always hold:
   * 
   * gend() > gbegin()
   * gend() - gbegin() <= gmaxsize()
   * end() >= gend()
   * 
   */
  template <class T, short gapsize>
  class GapBuffer : private std::vector<T>
  {
      typedef std::vector<T> rep_type;
      typedef typename rep_type::value_type value_type;
      typedef typename rep_type::iterator iterator;
      typedef unsigned int size_type;
      iterator gbegin() { return this->begin() + my_gapbegin;}
      iterator gend() { return this->begin() + my_gapend;}
      iterator cursor() { return this->begin() + my_cursor;}
      void newgap()
      {
      rep_type::insert(gbegin(), gapsize, value_type(0));
      my_gapend += gapsize;
      }
      void movegap(int d)
      {
      if (d > 0)
      {
          if (gend() + d > this->end())
          rep_type::insert(this->end(), size_type(gend() + d - this->end()),
                   value_type(0));
          copy(gend(), gend() + d, gbegin());
      }
      else
          copy(typename rep_type::reverse_iterator(gbegin()),
               typename rep_type::reverse_iterator(gbegin() + d),
               typename rep_type::reverse_iterator(gend()));
      my_gapbegin += d, my_gapend += d;
      }
      size_type gap() { return my_gapend - my_gapbegin; }
      void editing()
      { size_type d = my_cursor - my_gapbegin; if (d != 0) movegap(d); }
      void compact()
      { size_type d = this->end() - gend(); if (d > 0) movegap(d); }
    public:
      GapBuffer() : my_cursor(0), my_gapbegin(0), my_gapend(0) {}
      size_type size() { compact(); return gbegin() - this->begin(); }
      void forward()
      {
      if (my_cursor == my_gapbegin && gend() != this->end())
          my_cursor += gap();
      else if (cursor() < this->end()) my_cursor++;
      }
      void backward()
      {
      if (my_cursor == my_gapend)
	      if (gap())
		      my_cursor -= gap();
	      else
		      my_cursor--;
      else if (cursor() > this->begin()) my_cursor--;
      }
      void shift(size_type d)
      {
      size_type tmp = my_cursor + d;
      if ((my_cursor > my_gapend && tmp > my_gapend) ||
          (my_cursor <= my_gapbegin && tmp <= my_gapbegin))
          my_cursor = tmp;
      else if (d < 0) my_cursor += d - gap();
      else my_cursor += d + gap();
      }
      size_type position()
      { return my_cursor > my_gapend ? my_cursor - gap() : my_cursor;}
      void position(size_type p) { shift(p - my_cursor);}
      void insert(value_type u)
      {
      editing();
      if (!gap()) newgap();
      *cursor() = u;
      my_cursor++, my_gapbegin++;
      }
      void insert(value_type *u, size_type n)
      {
      editing();
      rep_type::insert(cursor(), u, u + n);
      my_cursor += n, my_gapbegin += n, my_gapend += n;
      }
      void remove_backward(size_type n)
      {
      if (my_cursor <= my_gapbegin)
      {
          if (my_cursor < n) n = my_cursor;
          erase(cursor() - n, cursor());
          my_cursor -= n, my_gapbegin -= n, my_gapend -= n;
      }
      else if (my_cursor - my_gapend > n)
      {
          erase(cursor() - n, cursor());
          my_cursor -= n;
      }
      else
      {
          size_type d = my_cursor - my_gapend;
          erase(gbegin() - (n - d), gbegin());
          erase(cursor() - d, cursor());
          my_gapbegin -= n - d, my_gapend -= n - d;
          my_cursor -= n;
      }
      }
      void remove_forward(size_type n)
      {
      if (my_cursor >= my_gapend)
      {
          if (size_type(this->end() - cursor()) < n) n = this->end() - cursor();
          erase(cursor(), cursor() + n);
      }
      else if (my_gapbegin - my_cursor > n)
      {
          erase(cursor(), cursor() + n);
          my_gapbegin -= n, my_gapend -= n;
      }
      else
      {
          size_type d = my_gapbegin - my_cursor;
          erase(gend(), gend() + (n - d));
          erase(cursor(), cursor() + d);
          my_gapbegin -= d, my_gapend -= d;
      }
      }
      const value_type *get() { compact(); return &*this->begin(); }
      void clear_buffer()
      {
      position(0);
      remove_forward(size());
      }
    private:
      size_type my_cursor;
      size_type my_gapbegin;
      size_type my_gapend;
  };

} // namespace

#endif
