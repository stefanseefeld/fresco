/*
 *$Id$
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

void output_range(std::ostream & out, Char s, Char e, Line_Break c)
{
    if (s == e) output_char(out, s);
    else
    {
	output_char(out, s);
	out << "..";
	output_char(out, e);
    }
    out << ";";
    switch (c)
    {
    case LB_BK:
	out << "BK";
	break;
    case LB_CR:
	out << "CR";
	break;
    case LB_LF:
	out << "LF";
	break;
    case LB_CM:
	out << "CM";
	break;
    case LB_SG:
	out << "SG";
	break;
    case LB_GL:
	out << "GL";
	break;
    case LB_CB:
	out << "CB";
	break;
    case LB_SP:
	out << "SP";
	break;
    case LB_ZW:
	out << "ZW";
	break;
    case LB_NL:
	out << "NL";
	break;
    case LB_WJ:
	out << "WJ";
	break;
    case LB_XX:
	out << "XX";
	break;
    case LB_OP:
	out << "OP";
	break;
    case LB_CL:
	out << "CL";
	break;
    case LB_QU:
	out << "QU";
	break;
    case LB_NS:
	out << "NS";
	break;
    case LB_EX:
	out << "EX";
	break;
    case LB_SY:
	out << "SY";
	break;
    case LB_IS:
	out << "IS";
	break;
    case LB_PR:
	out << "PR";
	break;
    case LB_PO:
	out << "PO";
	break;
    case LB_NU:
	out << "NU";
	break;
    case LB_AL:
	out << "AL";
	break;
    case LB_ID:
	out << "ID";
	break;
    case LB_IN:
	out << "IN";
	break;
    case LB_HY:
	out << "HY";
	break;
    case LB_BB:
	out << "BB";
	break;
    case LB_BA:
	out << "BA";
	break;
    case LB_SA:
	out << "SA";
	break;
    case LB_AI:
	out << "AI";
	break;
    case LB_B2:
	out << "B2";
	break;
    default:
	out << "UNKNOWN";
    }
    out << std::endl;
}

int main(int argc, char** argv)
{
    try
    {
	if (argc == 2) Babylon::override_path(std::string(argv[1]));
	
	for (Char A(UC_NULL); A.value() < 0x110000; ++A)
	{
	    if (!A.is_defined()) continue;
	    if (A.value() == 0x3400)
	    {
		output_range(std::cout, A, 0x4DB5, A.linebreak());
		A = 0x4DB5;
		continue;
	    }
	    if (A.value() == 0x4E00)
	    {
		output_range(std::cout, A, 0x9FA5, A.linebreak());
		A = 0x9FA5;
		continue;
	    }
	    if (A.value() == 0xAC00)
	    {
		output_range(std::cout, A, 0xD7A3, A.linebreak());
		A = 0xD7A3;
		continue;
	    }
	    if (A.value() == 0xD800)
	    {
		output_range(std::cout, A, 0xDB7F, A.linebreak());
		A = 0xDB7F;
		continue;
	    }
	    if (A.value() == 0xDB80)
	    {
		output_range(std::cout, A, 0xDBFF, A.linebreak());
		A = 0xDBFF;
		continue;
	    }
	    if (A.value() == 0xDC00)
	    {
		output_range(std::cout, A, 0xDFFF, A.linebreak());
		A = 0xDFFF;
		continue;
	    }
	    if (A.value() == 0xE000)
	    {
		output_range(std::cout, A, 0xF8FF, A.linebreak());
		A = 0xF8FF;
		continue;
	    }
	    if (A.value() == 0x20000)
	    {
		output_range(std::cout, A, 0x2A6D6, A.linebreak());
		A = 0x2A6D6;
		continue;
	    }
	    if (A.value() == 0xF0000)
	    {
		output_range(std::cout, A, 0xFFFFD, A.linebreak());
		A = 0xFFFFD;
		continue;
	    }
	    if (A.value() == 0x100000)
	    {
		output_range(std::cout, A, 0x10FFFD, A.linebreak());
		A = 0x10FFFD;
		continue;
	    }
	    output_range(std::cout, A, A, A.linebreak());
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
