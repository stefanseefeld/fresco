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

#ifndef _Babylon_String_hh
#define _Babylon_String_hh

/* String class
 * This class stores and manipulates strings of characters defined 
 * according to ISO10646. 
 */

#include <Babylon/Char.hh>

namespace Babylon
{

  class Bidir;

  class String
  {
      // Do not inherit from std::basic_string. It's not meant to be derived
      // from:-(

    public:
      typedef std::basic_string<Babylon::Char> string_type;
      typedef Babylon::Char char_type;
      // import types from string_type:
      typedef string_type::traits_type traits_type;
      typedef string_type::value_type value_type;
      typedef string_type::size_type size_type;
      typedef string_type::difference_type difference_type;
      typedef string_type::reference reference;
      typedef string_type::const_reference const_reference;
      typedef string_type::pointer pointer;
      typedef string_type::const_pointer const_pointer;
      typedef string_type::iterator iterator;
      typedef string_type::const_iterator const_iterator;
      typedef string_type::reverse_iterator reverse_iterator;
      typedef string_type::const_reverse_iterator const_reverse_iterator;

      static const size_type npos = string_type::npos;

      // Constructors:
      String();
      String(const String &,
         const size_type = 0, const size_type = npos);
      String(const char_type *, const Norm = NORM_NONE);
      String(const char_type *, const size_type, const Norm = NORM_NONE);
      String(const size_type, const Char, const Norm = NORM_NONE);
      template<class InputIterator>
      String(InputIterator, InputIterator, const Norm = NORM_NONE);
      // additional constructors:
      String(const string_type &);
      
      // Destructor:
      ~String();
      
      // Size Operations:

      size_type size() const { return my_data.size(); }
      size_type length() const { return my_data.length(); }
      bool empty() const { return my_data.empty(); }
      size_type max_size() const { return my_data.max_size(); }
      
      // Capacity Operations:
      
      size_type capacity() const { return my_data.capacity(); }
      void reserve() { my_data.reserve(); }
      void reserve(const size_type l) { my_data.reserve(l); }
      
      // Comparisons:
      int compare(const String & s) const { return compare(0, npos, s); }
      int compare(const size_type, const size_type,
          const String &) const;
      int compare(const size_type, const size_type, const String &,
          const size_type, const size_type) const;
      int compare(const char_type *) const;
      int compare(const size_type, const size_type, const char_type *) const;
      int compare(const size_type, const size_type,
          const char_type *, const size_type) const;
      
      // Character Access
      char_type & operator[](const size_type p);
      char_type operator[](const size_type p) const { return my_data[p]; }
      char_type & at(const size_type p);
      char_type at(const size_type p) const { return my_data.at(p); }
      
      // Generating C-Strings and Character Arrays
      
      // Modify Operations:
      String & assign(const String & s)
      { return assign(s, 0, npos); }
      String & assign(const String &,
               const size_type, const size_type);
      String & assign(const char_type *, const Norm = NORM_NONE);
      String & assign(const char_type *, const size_type,
               const Norm = NORM_NONE);
      String & assign(const size_type, const char_type);
      
      String & operator=(const String s) { return assign(s); }
      String & operator=(const char_type * c) { return assign(c); }
      String & operator=(char_type c) { return assign(1, c); }
      
      void swap(String &) throw ();
      
      String & append(const String & s)
      { return append(s, 0, npos); }
      String & append(const String &,
               const size_type, const size_type);
      String & append(const char_type *, const size_type,
               const Norm = NORM_NONE);
      String & append(const char_type *, const Norm = NORM_NONE);
      String & append(const size_type, const char_type);
      template<class InputIterator>
      String & append(InputIterator, InputIterator);
      
      void push_back(char_type c) { append(1, c); }
      
      String & operator+=(const String & s) { return append(s); }
      String & operator+=(const char_type * c) { return append(c); }
      String & operator+=(const char_type c) { return append(1, c); }
      
      String & insert(const size_type p, const String & s)
      { return insert(p, s, 0, npos); }
      String & insert(const size_type, const String &,
               const size_type, const size_type);
      String & insert(const size_type,
               const char_type *, const size_type);
      String & insert(const size_type, const char_type *);
      String & insert(const size_type, const size_type, const char_type);
      void insert(iterator, const size_type, const char_type);
      iterator insert(iterator, const char_type);
      void insert(iterator, iterator, iterator);
      
      void clear();
      String & erase();
      String & erase(const size_type);
      String & erase(const size_type, const size_type);
      String & erase(iterator, iterator);
      
      void resize(const size_type);
      void resize(const size_type, char_type);
      
      String & replace(const size_type p1, const size_type p2,
                const String & s)
      { return replace(p1, p2, s, 0, npos); }
      String & replace(iterator, iterator, const String &);
      String & replace(const size_type, const size_type,
                const String &,
                const size_type, const size_type);
      String & replace(const size_type, const size_type,
                const char_type *, const size_type);
      String & replace(iterator, iterator,
                       const char_type *, const size_type);
      String & replace(const size_type, const size_type,
                const char_type *);
      String & replace(iterator, iterator, const char_type *);
      String & replace(const size_type, const size_type,
                const size_type, char_type);
      String & replace(iterator, iterator,
                       const size_type, char_type);
      template<class InputIterator>
      String & replace(iterator, iterator,
                       InputIterator, InputIterator);
      
      size_type find(const char_type c) const { return my_data.find(c); }
      size_type find(const char_type c, const size_type i)
      { return my_data.find(c, i); }
      size_type rfind(const char_type c) const { return my_data.rfind(c); }
      size_type rfind(const char_type c, const size_type i)
      { return my_data.rfind(c, i); }
      
      size_type find(const String & s) const
      { return my_data.find(s.my_data); }
      size_type find(const String & s, const size_type i)
      { return my_data.find(s.my_data, i); }
      size_type rfind(const String & s) const
      { return my_data.rfind(s.my_data); }
      size_type rfind(const String & s, const size_type i)
      { return my_data.rfind(s.my_data, i); }
      
      size_type find(const char_type * c) const { return my_data.find(c); }
      size_type find(const char_type * c, const size_type i)
      { return my_data.find(c, i); }
      size_type rfind(const char_type * c) const { return my_data.rfind(c); }
      size_type rfind(const char_type * c, const size_type i)
      { return my_data.rfind(c, i); }
      
      size_type find(const char_type * c,
             const size_type i, const size_type l) const
      { return my_data.find(c, i, l); }
      size_type rfind(const char_type * c,
              const size_type i, const size_type l)
      { return my_data.rfind(c, i, l); }
      
      size_type find_first_of(const String & s) const
      { return my_data.find_first_of(s.my_data); }
      size_type find_first_of(const String & s, const size_type i)
      { return my_data.find_first_of(s.my_data, i); }
      size_type find_first_not_of(const String & s) const
      { return my_data.find_first_not_of(s.my_data); }
      size_type find_first_not_of(const String & s, const size_type i)
      { return my_data.find_first_not_of(s.my_data, i); }
      
      size_type find_first_of(const char_type * c) const
      { return my_data.find_first_of(c); }
      size_type find_first_of(const char_type * c, const size_type i)
      { return my_data.find_first_of(c, i); }
      size_type find_first_not_of(const char_type * c) const
      { return my_data.find_first_not_of(c); }
      size_type find_first_not_of(const char_type * c, const size_type i)
      { return my_data.find_first_not_of(c, i); }
      
      size_type find_first_of(const char_type * c, const size_type i,
                  const size_type l) const
      { return my_data.find_first_of(c, i, l); }
      size_type find_first_not_of(const char_type * c, const size_type i,
                  const size_type l) const
      { return my_data.find_first_not_of(c, i, l); }
      
      size_type find_first_of(const char_type c) const
      { return my_data.find_first_of(c); }
      size_type find_first_of(const char_type c, const size_type i)
      { return my_data.find_first_of(c, i); }
      size_type find_first_not_of(const char_type c) const
      { return my_data.find_first_not_of(c); }
      size_type find_first_not_of(const char_type c, const size_type i)
      { return my_data.find_first_not_of(c, i); }
      
      size_type find_last_of(const String & s) const
      { return my_data.find_last_of(s.my_data); }
      size_type find_last_of(const String & s, const size_type i)
      { return my_data.find_last_of(s.my_data, i); }
      size_type find_flast_not_of(const String & s) const
      { return my_data.find_last_not_of(s.my_data); }
      size_type find_last_not_of(const String & s, const size_type i)
      { return my_data.find_last_not_of(s.my_data, i); }
      
      size_type find_last_of(const char_type * c) const
      { return my_data.find_last_of(c); }
      size_type find_last_of(const char_type * c, const size_type i)
      { return my_data.find_last_of(c, i); }
      size_type find_last_not_of(const char_type * c) const
      { return my_data.find_last_not_of(c); }
      size_type find_last_not_of(const char_type * c, const size_type i)
      { return my_data.find_last_not_of(c, i); }
      
      size_type find_last_of(const char_type * c, const size_type i,
                 const size_type l) const
      { return my_data.find_last_of(c, i, l); }
      size_type find_last_not_of(const char_type * c, const size_type i,
                 const size_type l) const
      { return my_data.find_last_not_of(c, i, l); }
      
      size_type find_last_of(const char_type c) const
      { return my_data.find_last_of(c); }
      size_type find_last_of(const char_type c, const size_type i)
      { return my_data.find_last_of(c, i); }
      size_type find_last_not_of(const char_type c) const
      { return my_data.find_last_not_of(c); }
      size_type find_last_not_of(const char_type c, const size_type i)
      { return my_data.find_last_not_of(c, i); }
      
      // Substrings and String Concatenation:
      
      String substr() const { return String(my_data.substr()); }
      String substr(const size_type i) const
      { return String(my_data.substr(i)); }
      String substr(const size_type i, const size_type l) const
      { return String(my_data.substr(i, l)); }
      
      // Generating Iterators:

      iterator begin() { return my_data.begin(); }
      const_iterator begin() const { return my_data.begin(); }
      iterator end() { return my_data.end(); }
      const_iterator end() const { return my_data.end(); }
      reverse_iterator rbegin() { return my_data.rbegin(); }
      const_reverse_iterator rbegin() const { return my_data.rbegin(); }
      reverse_iterator rend() { return my_data.rend(); }
      const_reverse_iterator rend() const { return my_data.rend(); }

      // ------------------------------------------------------------
      // methods *NOT* in basic_string:
      // ------------------------------------------------------------

      // Constructors:
      String(const std::string &, const size_t pos = 0,
         const std::string format = Babylon::UTF8_format,
         const Babylon::Norm norm = NORM_NONE);
      String(const char *,
         const std::string format = Babylon::UTF8_format,
         const Babylon::Norm norm = NORM_NONE);
      String(const char *, const size_t len,
         const std::string format = Babylon::UTF8_format,
         const Babylon::Norm norm = NORM_NONE);
         

      // Conversion:

      std::string
      convert(const std::string & format = Babylon::UTF8_format) const
          throw (Transfer_Error);
      
      size_t convert(const std::string &,
             const size_t = 0,
             const std::string& = Babylon::UTF8_format,
             const Babylon::Norm norm = NORM_NONE)
          throw (Transfer_Error, std::length_error);
      
      //. returns the norm the string is in
      Norm norm() const { return my_norm; }
      //. normalizes the string to the given norm.
      void norm(const Norm);
      //. sets the norm the String is in. Does NOT change the
      //. string itself, so USE WITH CARE!
      void override_norm(const Norm n) { my_norm = n; }
      //. returns the normalized form of a string without changing it.
      String get_normalized(const Norm) const;

      void debug_dump() const;

    protected:
    private:
      Babylon::Norm my_norm;
      string_type my_data;
  }; // class String
  
  inline bool operator==(const String & s1, const String & s2)
  { return 0 == s1.compare(s2); }
  inline bool operator!=(const String & s1, const String & s2)
  { return 0 != s1.compare(s2); }
  inline bool operator<(const String & s1, const String & s2)
  { return 0 > s1.compare(s2); }
  inline bool operator>(const String & s1, const String & s2)
  { return 0 < s1.compare(s2); }
  inline bool operator<=(const String & s1, const String & s2)
  { return 0 >= s1.compare(s2); }
  inline bool operator>=(const String & s1, const String & s2)
  { return 0 <=s1.compare(s2); }

  inline String operator+(const String & s1, const String & s2)
  {
      String r(s1);
      return r.append(s2);
  }
  inline String operator+(const String & s1, String::char_type * c)
  {
      String r(s1);
      return r.append(c);
  }
  inline String operator+(String::char_type * c, const String & s1)
  {
      String r(c);
      return r.append(s1);
  }
  inline String operator+(const String & s1, String::char_type c)
  {
      String r(s1);
      r.push_back(c);
      return r;
  }
  inline String operator+(String::char_type c, const String & s1)
  {
      String r(1, c);
      return r.append(s1);
  }
  
}; // namespace Babylon

namespace std
{

  template<>
  inline void swap(Babylon::String & a, Babylon::String & b)
  {
      a.swap(b);
  }
    
}; // namespace std

#endif // _Babylon_String_hh
