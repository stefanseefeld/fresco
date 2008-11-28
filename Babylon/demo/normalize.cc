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

#include <Babylon/String.hh>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>

using namespace Babylon;

void output_char(std::ostream & out, Char a)
{
    out.setf(std::ios::uppercase);
    out << std::hex << std::setfill('0');
    if (a.value() <= 0xFFFF)
        out << std::setw(4) << a.value();
    else if (a.value() <= 0xFFFFF)
        out << std::setw(5) << a.value();
    else if (a.value() <= 0xFFFFFF)
        out << std::setw(6) << a.value();
    else if (a.value() <= 0xFFFFFFF)
        out << std::setw(7) << a.value();
    else
        out << std::setw(8) << a.value();
}

void dump_norms(const String & s)
{
    for (String::const_iterator i = s.begin(); i != s.end(); ++i)
    if (! i->is_defined())
    {
            std::cout << "UNDEFINED CHARACTER" << std::endl;
        return;
    }        

    for (String::const_iterator i = s.begin(); i != s.end(); ++i)
    {
    if (i != s.begin()) std::cout << " ";
    output_char(std::cout, *i);
    }
    std::cout << ";";

    String t;

    t = s.get_normalized(NORM_C);
    for (String::const_iterator i = t.begin(); i != t.end(); ++i)
    {
    if (i != t.begin()) std::cout << " ";
    output_char(std::cout, *i);
    }
    std::cout << ";";

    t = s.get_normalized(NORM_D);
    for (String::const_iterator i = t.begin(); i != t.end(); ++i)
    {
    if (i != t.begin()) std::cout << " ";
    output_char(std::cout, *i);
    }
    std::cout << ";";

    t = s.get_normalized(NORM_KC);
    for (String::const_iterator i = t.begin(); i != t.end(); ++i)
    {
    if (i != t.begin()) std::cout << " ";
    output_char(std::cout, *i);
    }
    std::cout << ";";

    t = s.get_normalized(NORM_KD);

    for (String::const_iterator i = t.begin(); i != t.end(); ++i)
    {
    if (i != t.begin()) std::cout << " ";
    output_char(std::cout, *i);
    }
    std::cout << ";" << std::endl << std::flush;
}

int main(int argc, char** argv)
{
    std::string in;
    {
    if (argc == 1)
    {
        std::cout << "usage : " << argv[0]
              << " norm-string-in-hex [override path]" << std::endl;
        std::cout << "- or -: " << argv[0]
              << " interactive [override-path]" << std::endl;
        return 0;
    }
    if (argc >= 2)
        in = argv[1];
    if (argc == 3)
        Babylon::override_path(std::string(argv[2]));
    }

    if ("interactive" == in)
    {
    while ("quit" != in)
    {
        if ("interactive" != in)
        {
        String s;
        Norm n;
        if (('A' >= in[0] && 'F' <= in[0]) ||
            ('0' >= in[0] && '9' <= in[0]))
            n = NORM_NONE;
        else if ('n' == in [0])
        {
            n = NORM_NONE;
            in.erase(0, 1);
        }
        else if ('k' == in[0])
        {
            n = Norm(n | NORM_MASK_K);
            in.erase(0, 1);
        }
        if ('c' == in[0])
        {
            n = Norm(n | NORM_MASK_C);
            in.erase(0, 1);
        }
        else if ('d' == in[0])
            in.erase(0, 1);

        std::istringstream stream(in);
        UCS4 c;
        
        while (stream >> std::hex >> c) s.push_back(Char(c));
        s.override_norm(n);

        dump_norms(s);
        }
        char chars[1024];
        std::cin.getline(chars, sizeof(chars));
        chars[1023] = '\0';
        in.assign(chars);
    }
    }
    else
    {
    String s;
    std::istringstream stream(in);
    UCS4 c;
    
    while (stream >> std::hex >> c) s.push_back(Char(c));

    dump_norms(s);
    }

    return 0;
}
