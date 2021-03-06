/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@fresco.org>
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
#ifndef _Prague_GetOpt_hh
#define _Prague_GetOpt_hh

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <exception>

namespace Prague
{

  //. GetOpt manages a command line option data base. It deals with short and long options,
  //. and reorders the given option vector such that you can run different GetOpt instances over
  //. the argv vector one after another.
  class GetOpt
  {
    public:
      //. the option type, i.e. whether an argument is required or not.
      enum type { novalue, optional, mandatory };
      enum order { inorder, require, permute };

      class NoSuchOption : public std::exception
      {
        public:
          NoSuchOption() throw() : my_option("(unknown)") { }
          NoSuchOption(const char o) throw() :
            my_option(std::string("-") + o)
          { }
          NoSuchOption(const std::string option) throw() :
            my_option(std::string("--") + option)
          { }
          virtual ~NoSuchOption() throw() { }
          virtual const char* what() const throw()
          {
              return (std::string("no such option ") + my_option).c_str();
          }
          const std::string my_option;
      };
      class DuplicateOption : public std::exception
      {
        public:
          DuplicateOption(const char o) throw() :
            my_option(std::string("-") + o)
          { }
          virtual ~DuplicateOption() throw() { }
          virtual const char* what() const throw()
          {
              return (std::string("option already added: ") + my_option).c_str();
          }
        private:
          const std::string my_option;
      };
    private:
      struct cell
      {
          cell(char oo, const std::string &opt, type tt, const std::string &des) :
            set(false), o(oo), option(opt), t(tt), description(des)
          { }
          bool set;
          char o; //.< option char
          std::string option; //.< option name
          type t; //.< option type
          std::string description; //.< a description of option
          std::string value; //.< value of option (string)
      };
      typedef std::vector<cell> table_t; //.< option table
    public:
      GetOpt(const char *, const char * = 0);
      ~GetOpt();
      //. print out usage information. This function uses help data provided with each
      //. registered option, i.e. it is suitable to be used as a help message.
      void usage() const;
      //. parse the given argv
      int parse(int argc, char **argv);
      //. parse the given args
      int parse(char *args);
      //. register an option
      void add(char o, const std::string &option, type,
               const std::string & = "no description available") throw (DuplicateOption);
      //. return whether the option was issued
      bool is_set(char o) const throw (NoSuchOption);
      //. return whether the option was issued
      bool is_set(const std::string &option) const throw (NoSuchOption);
      //. return whether the option was issued and return a value (if any) in out parameter
      bool get(char o, std::string *) const throw (NoSuchOption);
      //. return whether the option was issued and return a value (if any) in out parameter
      bool get(const std::string &option, std::string *) const throw (NoSuchOption);
    private:
      table_t table;
      const char *p; // program basename
      const char *u; // usage message
      order ordering;
      //. try to extract a long option, return number of tokens consumed
      size_t getlongopt(int argc, char **argv);
      //. try to extract a short option, return number of tokens consumed
      size_t getopt(int argc, char **argv);
      //. return the cell with the given option
      table_t::iterator find(const std::string &option)
      { return find_if(table.begin(), table.end(), comp_string(option)); }
      //. return the cell with the given option
      table_t::const_iterator find(const std::string &option) const
      { return find_if(table.begin(), table.end(), comp_string(option)); }
      //. return the cell with the given option
      table_t::iterator find(char o)
      { return find_if(table.begin(), table.end(), comp_char(o)); }
      //. return the cell with the given option
      table_t::const_iterator find(char o) const
      { return find_if(table.begin(), table.end(), comp_char(o)); }
      //. reorder the argument vector to move the consumed tokens to the front
      void exchange(char **, size_t, char **);
      struct comp_string
      {
          comp_string(const std::string &n) : name(n) { }
          bool operator () (const cell &c) { return name == c.option; }
          std::string name;
      };
      struct comp_char
      {
          comp_char(char n) : name(n) { }
          bool operator () (const cell &c) { return name == c.o; }
          char name;
      };
  };

} // namespace

#endif
