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

#include <Babylon/exceptions.hh>

#include <iomanip>
#include <sstream>

const char * Babylon::Undefined_Property::what() const throw()
{
    std::ostringstream res;
    res << std::setw(4) << std::setfill('0') << std::hex; 
    switch (my_error_prop)
    {
    case PROP_CHARACTER:
    res << "(" <<  my_error_uc << " Character is undefined";
    break;
    case PROP_UNICODE_VALUE:
    res << "(" << my_error_uc
        << ") Character has no unicode value.. how did this happen?";
    break;
    case PROP_GEN_CAT:
    res << "(" << my_error_uc
        << ") Character has no general category... how did this happen?";
    break;
    case PROP_CHAR_DECOMP:
    res << "(" << my_error_uc << ") Character has no decomposition";
    break;
    case PROP_COMB_CLASS :
    res << "(" << my_error_uc
        << ") Character has no canonical combining class.";
    break;
    case PROP_BIDIR_PROPS:
    res << "(" << my_error_uc << ") Character has no bidir property.";
    break;
    case PROP_DEC_DIGIT_VALUE:
    res << "(" << my_error_uc << ") Character has no decimal digit value.";
    break;
    case PROP_DIGIT_VALUE:
    res << "(" << my_error_uc << ") Character has no digit value.";
    break;
    case PROP_NUMERIC_VALUE:
    res << "(" << my_error_uc << ") Character has no numeric value.";
    break;
    case PROP_IS_MIRRORED:
    res << "(" << my_error_uc 
        << ") Mirroring property missing... how did this happen?";
    break;
    case PROP_UPPER_EQUIV:
    res << "(" << my_error_uc
        << ") Uppercase equivalent missing... how did this happen?";
    break;
    case PROP_LOWER_EQUIV:
    res << "(" << my_error_uc
        << ") Lowercase equivalent missing... how did this happen?";
    break;
    case PROP_TITLE_EQUIV:
    res << "(" << my_error_uc
        << ") Titlecase equivalent missing... how did this happen?";
    break;
    case PROP_SCRIPT:
    res << "(" << my_error_uc
        << ") Character belongs to no script... how did this happen?";
    break;
    case PROP_EA_WIDTH:
    res << "(" << my_error_uc
        << ") EA width property missing... how did this happen?";
    break;
    case PROP_LINE_BREAKING:
    res << "(" << my_error_uc
        << ") linebreak property missing... how did this happen?";
    break;
    case PROP_MAX:
    res << "(" << my_error_uc
        << ") PROP_MAX throw... how did this happen?";
    break;    
    }
    return res.str().c_str();
}


const char * Babylon::Transfer_Error::what() const throw()
{
    switch (my_error)
    {
    case TRANS_ICONV_FAILED:
    return("iconv failed to transform some characters.");
    case TRANS_CAN_NOT_ENCODE:
    return("Can not encode from Babylon to foreign format.");
    default:
    return("Can not decode from foreign format to Babylon.");
    }
}


const char * Babylon::Block_Error::what() const throw()
{
    std::ostringstream res;
    res << std::hex << std::setw(4) << std::setfill('0');
    res << "(" << my_block_start << "-" << my_block_end << "): "
    << my_error_message;
    return res.str().c_str();
}
