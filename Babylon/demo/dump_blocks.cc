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

#include <Babylon/Char.hh>
#include <Babylon/String.hh>
#include <Babylon/internal/Dictionary.hh>
#include <Prague/Sys/Path.hh>
#include <iostream>
#include <iomanip>

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

int main(int argc, char** argv)
{
    try
    {
	if (argc == 2) Babylon::override_path(std::string(argv[1]));
	
	for(Char A(UC_NULL);
	    A.value() != UC_MAX_DEFINED;
	    A = Dictionary::instance()->start_of_next_block(A.value()))
	{
	    output_char(std::cout,
			Char(Dictionary::instance()->
			     first_letter_of_block(A.value())));
	    std::cout << "..";
	    output_char(std::cout,
			Char(Dictionary::instance()->
			     last_letter_of_block(A.value())));
	    std::cout << "; "
		      << A.blockname() << std::endl;
	}
    }
    catch(std::runtime_error &e)
    {
	std::cout << "Caught an runtime exception: " << e.what()
		  << std::endl;
    }
    catch(std::exception &e)
    {
	std::cout << "Caught an exception: " << e.what()
		  << std::endl;
    }
    catch(...)
    {
	std::cout << "Some exception happened!" << std::endl;
    }
}
