/*$Id: UnicodePluginGenerator.pl,v 1.11 2004/01/28 12:39:04 tobias Exp 100-17F.cc
 *
 * This source file is a part of the Fresco Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Wed, 28 Jan 2004 20:49:02 +0100.
 *
 * This plugin to libBabylon is free software; you can redistribute it
 * and/or  modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 675 Mass Ave, Cambridge,
 * MA 02139, USA
 */

#include <Babylon/defs.hh>
#include <Babylon/internal/Blocks.hh>
#include <bitset>
#include <utility>

#include <map>

namespace Babylon
{
  namespace Module
  {
    class Latin_ExtendedA100 : public Babylon::Block
    {
      public:
        void clean() { };

        Latin_ExtendedA100() :
        my_first_letter(0x100),
        my_last_letter(0x17F)
        // my_version="4.0" // Not yet supported!
        {
            {
                my_composeMap[std::make_pair(0x00000102, 0x00000300)] = 0x1EB0;
                my_composeMap[std::make_pair(0x00000102, 0x00000301)] = 0x1EAE;
                my_composeMap[std::make_pair(0x00000102, 0x00000303)] = 0x1EB4;
                my_composeMap[std::make_pair(0x00000102, 0x00000309)] = 0x1EB2;
                my_composeMap[std::make_pair(0x00000103, 0x00000300)] = 0x1EB1;
                my_composeMap[std::make_pair(0x00000103, 0x00000301)] = 0x1EAF;
                my_composeMap[std::make_pair(0x00000103, 0x00000303)] = 0x1EB5;
                my_composeMap[std::make_pair(0x00000103, 0x00000309)] = 0x1EB3;
                my_composeMap[std::make_pair(0x00000112, 0x00000300)] = 0x1E14;
                my_composeMap[std::make_pair(0x00000112, 0x00000301)] = 0x1E16;
                my_composeMap[std::make_pair(0x00000113, 0x00000300)] = 0x1E15;
                my_composeMap[std::make_pair(0x00000113, 0x00000301)] = 0x1E17;
                my_composeMap[std::make_pair(0x0000014C, 0x00000300)] = 0x1E50;
                my_composeMap[std::make_pair(0x0000014C, 0x00000301)] = 0x1E52;
                my_composeMap[std::make_pair(0x0000014D, 0x00000300)] = 0x1E51;
                my_composeMap[std::make_pair(0x0000014D, 0x00000301)] = 0x1E53;
                my_composeMap[std::make_pair(0x0000015A, 0x00000307)] = 0x1E64;
                my_composeMap[std::make_pair(0x0000015B, 0x00000307)] = 0x1E65;
                my_composeMap[std::make_pair(0x00000160, 0x00000307)] = 0x1E66;
                my_composeMap[std::make_pair(0x00000161, 0x00000307)] = 0x1E67;
                my_composeMap[std::make_pair(0x00000168, 0x00000301)] = 0x1E78;
                my_composeMap[std::make_pair(0x00000169, 0x00000301)] = 0x1E79;
                my_composeMap[std::make_pair(0x0000016A, 0x00000308)] = 0x1E7A;
                my_composeMap[std::make_pair(0x0000016B, 0x00000308)] = 0x1E7B;
                my_composeMap[std::make_pair(0x0000017F, 0x00000307)] = 0x1E9B;
            }
        }

        ~Latin_ExtendedA100() { }

        UCS4 first_letter() const
        {
        return my_first_letter;
    }  

    UCS4 last_letter() const
    {
        return my_last_letter;
    }

    bool is_undef_block() const
    {
        return 0;
    }

    // query functions:
    std::string blockname(const UCS4 uc) const
    {
        return "Latin Extended-A";
    }

        bool is_defined(const UCS4 uc) const
        {
            return 1;
        }

        UCS4 uppercase(const UCS4 uc) const
        {
            return Latin_ExtendedA100::my_upper[uc - my_first_letter];
        }

        UCS4 lowercase(const UCS4 uc) const
        {
            return Latin_ExtendedA100::my_lower[uc - my_first_letter];
        }

        UCS4 titlecase(const UCS4 uc) const
        {
            return Latin_ExtendedA100::my_title[uc - my_first_letter];
        }

        int dec_digit_value(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Decimal_Digit(const UCS4 uc) const
        {
            return 0;
        }

        int digit_value(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Digit(const UCS4 uc) const
        {
            return 0;
        }

        float numeric_value(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Numeric(const UCS4 uc) const
        {
            return 0;
        }

        Gen_Cat category(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CAT_MAX;
            return Babylon::Gen_Cat(Latin_ExtendedA100::my_cat[uc - my_first_letter]);
        }

        Can_Comb_Class comb_class(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CC_MAX;
            return Babylon::Can_Comb_Class(0);
        }

        Bidir_Props bidir_props(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return BIDIR_INVALID;
            return BIDIR_L;
        }

        Char_Decomp decomp_type(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return DECOMP_MAX;
            return Babylon::Char_Decomp(Latin_ExtendedA100::my_decomp[uc - my_first_letter]);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            Babylon::UTF32_string us;
            us.resize(2);
            us[0] = Latin_ExtendedA100::my_decompStr[uc - my_first_letter][0];
            us[1] = Latin_ExtendedA100::my_decompStr[uc - my_first_letter][1];
            if (0x0000u == us[1])
                us.resize(1);
            return us;
        }

        bool must_mirror(const UCS4 uc) const
        {
            return 0;
        }

        Line_Break linebreak(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return LB_MAX;
            return Babylon::Line_Break(Latin_ExtendedA100::my_lb[uc - my_first_letter]);
        }

        EA_Width EA_width(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return EA_WIDTH_MAX;
            return Babylon::EA_Width(Latin_ExtendedA100::my_ea[uc - my_first_letter]);
        }

        UCS4 compose(const UCS4 starter, const UCS4 last)
        {
            return my_composeMap[std::make_pair(starter, last)];
        }

        bool exclude_from_composition(const UCS4 uc) const
        {
            return 0;
        }

        bool is_White_Space(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Bidi_Control(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Join_Control(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Dash(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Hyphen(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Quotation_Mark(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Terminal_Punctuation(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Other_Math(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Hex_Digit(const UCS4 uc) const
        {
            return 0;
        }

        bool is_ASCII_Hex_Digit(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Other_Alphabetic(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Ideographic(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Diacritic(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Extender(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Other_Lowercase(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Other_Uppercase(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Noncharacter_Code_Point(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Other_Grapheme_Extend(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Grapheme_Link(const UCS4 uc) const
        {
            return 0;
        }

        bool is_IDS_Binary_Operator(const UCS4 uc) const
        {
            return 0;
        }

        bool is_IDS_Trinary_Operator(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Radical(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Unified_Ideograph(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Other_Default_Ignorable_Code_Point(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Deprecated(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Soft_Dotted(const UCS4 uc) const
        {
            return my_Soft_Dotted.test(uc - my_first_letter);
        }

        bool is_Logical_Order_Exception(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Other_ID_Start(const UCS4 uc) const
        {
            return 0;
        }

        bool is_XID_Start_Closure(const UCS4 uc) const
        {
            return 0;
        }

        bool is_XID_Continue_Closure(const UCS4 uc) const
        {
            return 0;
        }

      private:
        // functions
        Latin_ExtendedA100(const Latin_ExtendedA100 &) ; // no implementaion!

    // members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const UCS4 my_upper[128];
        static const UCS4 my_lower[128];
        static const UCS4 my_title[128];
        static const unsigned char my_cat[128];
        static const unsigned char my_decomp[128];
        static const UCS2 my_decompStr[128][2];
        static const unsigned char my_lb[128];
        static const unsigned char my_ea[128];
        std::map<std::pair<UCS4, UCS4>, UCS4> my_composeMap;
        static const std::bitset<128> my_Soft_Dotted;
    }; // class Latin_ExtendedA100

    const UCS4 Latin_ExtendedA100::my_upper[] =
    {
        0x0100, 0x0100, 0x0102, 0x0102, 0x0104, 0x0104, 0x0106, 0x0106, 
        0x0108, 0x0108, 0x010A, 0x010A, 0x010C, 0x010C, 0x010E, 0x010E, 
        0x0110, 0x0110, 0x0112, 0x0112, 0x0114, 0x0114, 0x0116, 0x0116, 
        0x0118, 0x0118, 0x011A, 0x011A, 0x011C, 0x011C, 0x011E, 0x011E, 
        0x0120, 0x0120, 0x0122, 0x0122, 0x0124, 0x0124, 0x0126, 0x0126, 
        0x0128, 0x0128, 0x012A, 0x012A, 0x012C, 0x012C, 0x012E, 0x012E, 
        0x0130, 0x0049, 0x0132, 0x0132, 0x0134, 0x0134, 0x0136, 0x0136, 
        0x0138, 0x0139, 0x0139, 0x013B, 0x013B, 0x013D, 0x013D, 0x013F, 
        0x013F, 0x0141, 0x0141, 0x0143, 0x0143, 0x0145, 0x0145, 0x0147, 
        0x0147, 0x0149, 0x014A, 0x014A, 0x014C, 0x014C, 0x014E, 0x014E, 
        0x0150, 0x0150, 0x0152, 0x0152, 0x0154, 0x0154, 0x0156, 0x0156, 
        0x0158, 0x0158, 0x015A, 0x015A, 0x015C, 0x015C, 0x015E, 0x015E, 
        0x0160, 0x0160, 0x0162, 0x0162, 0x0164, 0x0164, 0x0166, 0x0166, 
        0x0168, 0x0168, 0x016A, 0x016A, 0x016C, 0x016C, 0x016E, 0x016E, 
        0x0170, 0x0170, 0x0172, 0x0172, 0x0174, 0x0174, 0x0176, 0x0176, 
        0x0178, 0x0179, 0x0179, 0x017B, 0x017B, 0x017D, 0x017D, 0x0053
    };

    const UCS4 Latin_ExtendedA100::my_lower[] =
    {
        0x0101, 0x0101, 0x0103, 0x0103, 0x0105, 0x0105, 0x0107, 0x0107, 
        0x0109, 0x0109, 0x010B, 0x010B, 0x010D, 0x010D, 0x010F, 0x010F, 
        0x0111, 0x0111, 0x0113, 0x0113, 0x0115, 0x0115, 0x0117, 0x0117, 
        0x0119, 0x0119, 0x011B, 0x011B, 0x011D, 0x011D, 0x011F, 0x011F, 
        0x0121, 0x0121, 0x0123, 0x0123, 0x0125, 0x0125, 0x0127, 0x0127, 
        0x0129, 0x0129, 0x012B, 0x012B, 0x012D, 0x012D, 0x012F, 0x012F, 
        0x0069, 0x0131, 0x0133, 0x0133, 0x0135, 0x0135, 0x0137, 0x0137, 
        0x0138, 0x013A, 0x013A, 0x013C, 0x013C, 0x013E, 0x013E, 0x0140, 
        0x0140, 0x0142, 0x0142, 0x0144, 0x0144, 0x0146, 0x0146, 0x0148, 
        0x0148, 0x0149, 0x014B, 0x014B, 0x014D, 0x014D, 0x014F, 0x014F, 
        0x0151, 0x0151, 0x0153, 0x0153, 0x0155, 0x0155, 0x0157, 0x0157, 
        0x0159, 0x0159, 0x015B, 0x015B, 0x015D, 0x015D, 0x015F, 0x015F, 
        0x0161, 0x0161, 0x0163, 0x0163, 0x0165, 0x0165, 0x0167, 0x0167, 
        0x0169, 0x0169, 0x016B, 0x016B, 0x016D, 0x016D, 0x016F, 0x016F, 
        0x0171, 0x0171, 0x0173, 0x0173, 0x0175, 0x0175, 0x0177, 0x0177, 
        0x00FF, 0x017A, 0x017A, 0x017C, 0x017C, 0x017E, 0x017E, 0x017F
    };

    const UCS4 Latin_ExtendedA100::my_title[] =
    {
        0x0100, 0x0100, 0x0102, 0x0102, 0x0104, 0x0104, 0x0106, 0x0106, 
        0x0108, 0x0108, 0x010A, 0x010A, 0x010C, 0x010C, 0x010E, 0x010E, 
        0x0110, 0x0110, 0x0112, 0x0112, 0x0114, 0x0114, 0x0116, 0x0116, 
        0x0118, 0x0118, 0x011A, 0x011A, 0x011C, 0x011C, 0x011E, 0x011E, 
        0x0120, 0x0120, 0x0122, 0x0122, 0x0124, 0x0124, 0x0126, 0x0126, 
        0x0128, 0x0128, 0x012A, 0x012A, 0x012C, 0x012C, 0x012E, 0x012E, 
        0x0130, 0x0049, 0x0132, 0x0132, 0x0134, 0x0134, 0x0136, 0x0136, 
        0x0138, 0x0139, 0x0139, 0x013B, 0x013B, 0x013D, 0x013D, 0x013F, 
        0x013F, 0x0141, 0x0141, 0x0143, 0x0143, 0x0145, 0x0145, 0x0147, 
        0x0147, 0x0149, 0x014A, 0x014A, 0x014C, 0x014C, 0x014E, 0x014E, 
        0x0150, 0x0150, 0x0152, 0x0152, 0x0154, 0x0154, 0x0156, 0x0156, 
        0x0158, 0x0158, 0x015A, 0x015A, 0x015C, 0x015C, 0x015E, 0x015E, 
        0x0160, 0x0160, 0x0162, 0x0162, 0x0164, 0x0164, 0x0166, 0x0166, 
        0x0168, 0x0168, 0x016A, 0x016A, 0x016C, 0x016C, 0x016E, 0x016E, 
        0x0170, 0x0170, 0x0172, 0x0172, 0x0174, 0x0174, 0x0176, 0x0176, 
        0x0178, 0x0179, 0x0179, 0x017B, 0x017B, 0x017D, 0x017D, 0x0053
    };

    const unsigned char Latin_ExtendedA100::my_cat[] =
    {
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, 
        CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, 
        CAT_Ll, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Ll
    };

    const unsigned char Latin_ExtendedA100::my_decomp[] = {
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_COMPAT, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_COMPAT
    };

    const UCS2 Latin_ExtendedA100::my_decompStr[][2] =
    {
        { 0x00000041u, 0x00000304u }, { 0x00000061u, 0x00000304u },  // 00000100
        { 0x00000041u, 0x00000306u }, { 0x00000061u, 0x00000306u },  // 00000102
        { 0x00000041u, 0x00000328u }, { 0x00000061u, 0x00000328u },  // 00000104
        { 0x00000043u, 0x00000301u }, { 0x00000063u, 0x00000301u },  // 00000106
        { 0x00000043u, 0x00000302u }, { 0x00000063u, 0x00000302u },  // 00000108
        { 0x00000043u, 0x00000307u }, { 0x00000063u, 0x00000307u },  // 0000010A
        { 0x00000043u, 0x0000030Cu }, { 0x00000063u, 0x0000030Cu },  // 0000010C
        { 0x00000044u, 0x0000030Cu }, { 0x00000064u, 0x0000030Cu },  // 0000010E
        { 0x00000110u, 0x00000000u }, { 0x00000111u, 0x00000000u },  // 00000110
        { 0x00000045u, 0x00000304u }, { 0x00000065u, 0x00000304u },  // 00000112
        { 0x00000045u, 0x00000306u }, { 0x00000065u, 0x00000306u },  // 00000114
        { 0x00000045u, 0x00000307u }, { 0x00000065u, 0x00000307u },  // 00000116
        { 0x00000045u, 0x00000328u }, { 0x00000065u, 0x00000328u },  // 00000118
        { 0x00000045u, 0x0000030Cu }, { 0x00000065u, 0x0000030Cu },  // 0000011A
        { 0x00000047u, 0x00000302u }, { 0x00000067u, 0x00000302u },  // 0000011C
        { 0x00000047u, 0x00000306u }, { 0x00000067u, 0x00000306u },  // 0000011E
        { 0x00000047u, 0x00000307u }, { 0x00000067u, 0x00000307u },  // 00000120
        { 0x00000047u, 0x00000327u }, { 0x00000067u, 0x00000327u },  // 00000122
        { 0x00000048u, 0x00000302u }, { 0x00000068u, 0x00000302u },  // 00000124
        { 0x00000126u, 0x00000000u }, { 0x00000127u, 0x00000000u },  // 00000126
        { 0x00000049u, 0x00000303u }, { 0x00000069u, 0x00000303u },  // 00000128
        { 0x00000049u, 0x00000304u }, { 0x00000069u, 0x00000304u },  // 0000012A
        { 0x00000049u, 0x00000306u }, { 0x00000069u, 0x00000306u },  // 0000012C
        { 0x00000049u, 0x00000328u }, { 0x00000069u, 0x00000328u },  // 0000012E
        { 0x00000049u, 0x00000307u }, { 0x00000131u, 0x00000000u },  // 00000130
        { 0x00000049u, 0x0000004Au }, { 0x00000069u, 0x0000006Au },  // 00000132
        { 0x0000004Au, 0x00000302u }, { 0x0000006Au, 0x00000302u },  // 00000134
        { 0x0000004Bu, 0x00000327u }, { 0x0000006Bu, 0x00000327u },  // 00000136
        { 0x00000138u, 0x00000000u }, { 0x0000004Cu, 0x00000301u },  // 00000138
        { 0x0000006Cu, 0x00000301u }, { 0x0000004Cu, 0x00000327u },  // 0000013A
        { 0x0000006Cu, 0x00000327u }, { 0x0000004Cu, 0x0000030Cu },  // 0000013C
        { 0x0000006Cu, 0x0000030Cu }, { 0x0000004Cu, 0x000000B7u },  // 0000013E
        { 0x0000006Cu, 0x000000B7u }, { 0x00000141u, 0x00000000u },  // 00000140
        { 0x00000142u, 0x00000000u }, { 0x0000004Eu, 0x00000301u },  // 00000142
        { 0x0000006Eu, 0x00000301u }, { 0x0000004Eu, 0x00000327u },  // 00000144
        { 0x0000006Eu, 0x00000327u }, { 0x0000004Eu, 0x0000030Cu },  // 00000146
        { 0x0000006Eu, 0x0000030Cu }, { 0x000002BCu, 0x0000006Eu },  // 00000148
        { 0x0000014Au, 0x00000000u }, { 0x0000014Bu, 0x00000000u },  // 0000014A
        { 0x0000004Fu, 0x00000304u }, { 0x0000006Fu, 0x00000304u },  // 0000014C
        { 0x0000004Fu, 0x00000306u }, { 0x0000006Fu, 0x00000306u },  // 0000014E
        { 0x0000004Fu, 0x0000030Bu }, { 0x0000006Fu, 0x0000030Bu },  // 00000150
        { 0x00000152u, 0x00000000u }, { 0x00000153u, 0x00000000u },  // 00000152
        { 0x00000052u, 0x00000301u }, { 0x00000072u, 0x00000301u },  // 00000154
        { 0x00000052u, 0x00000327u }, { 0x00000072u, 0x00000327u },  // 00000156
        { 0x00000052u, 0x0000030Cu }, { 0x00000072u, 0x0000030Cu },  // 00000158
        { 0x00000053u, 0x00000301u }, { 0x00000073u, 0x00000301u },  // 0000015A
        { 0x00000053u, 0x00000302u }, { 0x00000073u, 0x00000302u },  // 0000015C
        { 0x00000053u, 0x00000327u }, { 0x00000073u, 0x00000327u },  // 0000015E
        { 0x00000053u, 0x0000030Cu }, { 0x00000073u, 0x0000030Cu },  // 00000160
        { 0x00000054u, 0x00000327u }, { 0x00000074u, 0x00000327u },  // 00000162
        { 0x00000054u, 0x0000030Cu }, { 0x00000074u, 0x0000030Cu },  // 00000164
        { 0x00000166u, 0x00000000u }, { 0x00000167u, 0x00000000u },  // 00000166
        { 0x00000055u, 0x00000303u }, { 0x00000075u, 0x00000303u },  // 00000168
        { 0x00000055u, 0x00000304u }, { 0x00000075u, 0x00000304u },  // 0000016A
        { 0x00000055u, 0x00000306u }, { 0x00000075u, 0x00000306u },  // 0000016C
        { 0x00000055u, 0x0000030Au }, { 0x00000075u, 0x0000030Au },  // 0000016E
        { 0x00000055u, 0x0000030Bu }, { 0x00000075u, 0x0000030Bu },  // 00000170
        { 0x00000055u, 0x00000328u }, { 0x00000075u, 0x00000328u },  // 00000172
        { 0x00000057u, 0x00000302u }, { 0x00000077u, 0x00000302u },  // 00000174
        { 0x00000059u, 0x00000302u }, { 0x00000079u, 0x00000302u },  // 00000176
        { 0x00000059u, 0x00000308u }, { 0x0000005Au, 0x00000301u },  // 00000178
        { 0x0000007Au, 0x00000301u }, { 0x0000005Au, 0x00000307u },  // 0000017A
        { 0x0000007Au, 0x00000307u }, { 0x0000005Au, 0x0000030Cu },  // 0000017C
        { 0x0000007Au, 0x0000030Cu }, { 0x00000073u, 0x00000000u }
    };

    const unsigned char Latin_ExtendedA100::my_lb[] =
    {
        LB_AL, LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AI, LB_AL, LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AI, LB_AI, 
        LB_AL, LB_AL, LB_AL, LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AI, LB_AI, LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AI, 
        LB_AI, LB_AI, LB_AI, LB_AL, LB_AI, LB_AL, LB_AL, LB_AL, 
        LB_AI, LB_AI, LB_AI, LB_AL, LB_AL, LB_AI, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AI, LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AI, LB_AI, 
        LB_AL, LB_AL, LB_AL, LB_AI, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL
    };

    const unsigned char Latin_ExtendedA100::my_ea[] =
    {
        EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_A, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, 
        EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N
    };

    const std::bitset<128> Latin_ExtendedA100::my_Soft_Dotted(std::string("00000000000000000000000000000000000000000000000000000000000000000000000000000000100000000000000000000000000000000000000000000000"));

  }; // namespace
}; // namespace

dload(Babylon::Module::Latin_ExtendedA100);
