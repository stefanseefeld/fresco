/*$Id: UnicodePluginGenerator.pl,v 1.7 2003/08/01 16:47:16 tobias Exp 1E00-1EFF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 05 Aug 2003 17:09:44 +0200.
 *
 * This plugin to libPrague is free software; you can redistribute it
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
    class Latin_Extended_Additional1E00 : public Babylon::Block
    {
      public:
        void clean() { };

        Latin_Extended_Additional1E00() :
	    my_first_letter(0x1E00),
	    my_last_letter(0x1EFF)
	    // my_version="4.0" // Not yet supported!
        {
            {
                my_composeMap[std::make_pair(0x00001E36, 0x00000304)] = 0x1E38;
                my_composeMap[std::make_pair(0x00001E37, 0x00000304)] = 0x1E39;
                my_composeMap[std::make_pair(0x00001E5A, 0x00000304)] = 0x1E5C;
                my_composeMap[std::make_pair(0x00001E5B, 0x00000304)] = 0x1E5D;
                my_composeMap[std::make_pair(0x00001E62, 0x00000307)] = 0x1E68;
                my_composeMap[std::make_pair(0x00001E63, 0x00000307)] = 0x1E69;
                my_composeMap[std::make_pair(0x00001EA0, 0x00000302)] = 0x1EAC;
                my_composeMap[std::make_pair(0x00001EA0, 0x00000306)] = 0x1EB6;
                my_composeMap[std::make_pair(0x00001EA1, 0x00000302)] = 0x1EAD;
                my_composeMap[std::make_pair(0x00001EA1, 0x00000306)] = 0x1EB7;
                my_composeMap[std::make_pair(0x00001EB8, 0x00000302)] = 0x1EC6;
                my_composeMap[std::make_pair(0x00001EB9, 0x00000302)] = 0x1EC7;
                my_composeMap[std::make_pair(0x00001ECC, 0x00000302)] = 0x1ED8;
                my_composeMap[std::make_pair(0x00001ECD, 0x00000302)] = 0x1ED9;
            }
        }

        ~Latin_Extended_Additional1E00() { }

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
	    return "Latin Extended Additional";
	}

        bool is_defined(const UCS4 uc) const
        {
            return (my_is_defined.test(uc - my_first_letter));
        }

        UCS4 uppercase(const UCS4 uc) const
        {
            return Latin_Extended_Additional1E00::my_upper[uc - my_first_letter];
        }

        UCS4 lowercase(const UCS4 uc) const
        {
            return Latin_Extended_Additional1E00::my_lower[uc - my_first_letter];
        }

        UCS4 titlecase(const UCS4 uc) const
        {
            return Latin_Extended_Additional1E00::my_title[uc - my_first_letter];
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
            return Babylon::Gen_Cat(Latin_Extended_Additional1E00::my_cat[uc - my_first_letter]);
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
            return Babylon::Char_Decomp(Latin_Extended_Additional1E00::my_decomp[uc - my_first_letter]);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            Babylon::UTF32_string us;
            us.resize(2);
            us[0] = Latin_Extended_Additional1E00::my_decompStr[uc - my_first_letter][0];
            us[1] = Latin_Extended_Additional1E00::my_decompStr[uc - my_first_letter][1];
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
            return Babylon::Line_Break(LB_AL);
    }

        EA_Width EA_width(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return EA_WIDTH_MAX;
            return Babylon::EA_Width(EA_WIDTH_N);
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
        Latin_Extended_Additional1E00(const Latin_Extended_Additional1E00 &) ; // no implementaion!

	// members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const std::bitset<256> my_is_defined;
        static const UCS4 my_upper[256];
        static const UCS4 my_lower[256];
        static const UCS4 my_title[256];
        static const unsigned char my_cat[256];
        static const unsigned char my_decomp[256];
        static const UCS2 my_decompStr[256][2];
        std::map<std::pair<UCS4, UCS4>, UCS4> my_composeMap;
        static const std::bitset<256> my_Soft_Dotted;
    }; // class Latin_Extended_Additional1E00

    const std::bitset<256> Latin_Extended_Additional1E00::my_is_defined(std::string("0000001111111111111111111111111111111111111111111111111111111111111111111111111111111111111111110000111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"));

    const UCS4 Latin_Extended_Additional1E00::my_upper[] =
    {
        0x1E00, 0x1E00, 0x1E02, 0x1E02, 0x1E04, 0x1E04, 0x1E06, 0x1E06, 
        0x1E08, 0x1E08, 0x1E0A, 0x1E0A, 0x1E0C, 0x1E0C, 0x1E0E, 0x1E0E, 
        0x1E10, 0x1E10, 0x1E12, 0x1E12, 0x1E14, 0x1E14, 0x1E16, 0x1E16, 
        0x1E18, 0x1E18, 0x1E1A, 0x1E1A, 0x1E1C, 0x1E1C, 0x1E1E, 0x1E1E, 
        0x1E20, 0x1E20, 0x1E22, 0x1E22, 0x1E24, 0x1E24, 0x1E26, 0x1E26, 
        0x1E28, 0x1E28, 0x1E2A, 0x1E2A, 0x1E2C, 0x1E2C, 0x1E2E, 0x1E2E, 
        0x1E30, 0x1E30, 0x1E32, 0x1E32, 0x1E34, 0x1E34, 0x1E36, 0x1E36, 
        0x1E38, 0x1E38, 0x1E3A, 0x1E3A, 0x1E3C, 0x1E3C, 0x1E3E, 0x1E3E, 
        0x1E40, 0x1E40, 0x1E42, 0x1E42, 0x1E44, 0x1E44, 0x1E46, 0x1E46, 
        0x1E48, 0x1E48, 0x1E4A, 0x1E4A, 0x1E4C, 0x1E4C, 0x1E4E, 0x1E4E, 
        0x1E50, 0x1E50, 0x1E52, 0x1E52, 0x1E54, 0x1E54, 0x1E56, 0x1E56, 
        0x1E58, 0x1E58, 0x1E5A, 0x1E5A, 0x1E5C, 0x1E5C, 0x1E5E, 0x1E5E, 
        0x1E60, 0x1E60, 0x1E62, 0x1E62, 0x1E64, 0x1E64, 0x1E66, 0x1E66, 
        0x1E68, 0x1E68, 0x1E6A, 0x1E6A, 0x1E6C, 0x1E6C, 0x1E6E, 0x1E6E, 
        0x1E70, 0x1E70, 0x1E72, 0x1E72, 0x1E74, 0x1E74, 0x1E76, 0x1E76, 
        0x1E78, 0x1E78, 0x1E7A, 0x1E7A, 0x1E7C, 0x1E7C, 0x1E7E, 0x1E7E, 
        0x1E80, 0x1E80, 0x1E82, 0x1E82, 0x1E84, 0x1E84, 0x1E86, 0x1E86, 
        0x1E88, 0x1E88, 0x1E8A, 0x1E8A, 0x1E8C, 0x1E8C, 0x1E8E, 0x1E8E, 
        0x1E90, 0x1E90, 0x1E92, 0x1E92, 0x1E94, 0x1E94, 0x1E96, 0x1E97, 
        0x1E98, 0x1E99, 0x1E9A, 0x1E60, 0x1E9C, 0x1E9D, 0x1E9E, 0x1E9F, 
        0x1EA0, 0x1EA0, 0x1EA2, 0x1EA2, 0x1EA4, 0x1EA4, 0x1EA6, 0x1EA6, 
        0x1EA8, 0x1EA8, 0x1EAA, 0x1EAA, 0x1EAC, 0x1EAC, 0x1EAE, 0x1EAE, 
        0x1EB0, 0x1EB0, 0x1EB2, 0x1EB2, 0x1EB4, 0x1EB4, 0x1EB6, 0x1EB6, 
        0x1EB8, 0x1EB8, 0x1EBA, 0x1EBA, 0x1EBC, 0x1EBC, 0x1EBE, 0x1EBE, 
        0x1EC0, 0x1EC0, 0x1EC2, 0x1EC2, 0x1EC4, 0x1EC4, 0x1EC6, 0x1EC6, 
        0x1EC8, 0x1EC8, 0x1ECA, 0x1ECA, 0x1ECC, 0x1ECC, 0x1ECE, 0x1ECE, 
        0x1ED0, 0x1ED0, 0x1ED2, 0x1ED2, 0x1ED4, 0x1ED4, 0x1ED6, 0x1ED6, 
        0x1ED8, 0x1ED8, 0x1EDA, 0x1EDA, 0x1EDC, 0x1EDC, 0x1EDE, 0x1EDE, 
        0x1EE0, 0x1EE0, 0x1EE2, 0x1EE2, 0x1EE4, 0x1EE4, 0x1EE6, 0x1EE6, 
        0x1EE8, 0x1EE8, 0x1EEA, 0x1EEA, 0x1EEC, 0x1EEC, 0x1EEE, 0x1EEE, 
        0x1EF0, 0x1EF0, 0x1EF2, 0x1EF2, 0x1EF4, 0x1EF4, 0x1EF6, 0x1EF6, 
        0x1EF8, 0x1EF8, 0x1EFA, 0x1EFB, 0x1EFC, 0x1EFD, 0x1EFE, 0x1EFF
    };

    const UCS4 Latin_Extended_Additional1E00::my_lower[] =
    {
        0x1E01, 0x1E01, 0x1E03, 0x1E03, 0x1E05, 0x1E05, 0x1E07, 0x1E07, 
        0x1E09, 0x1E09, 0x1E0B, 0x1E0B, 0x1E0D, 0x1E0D, 0x1E0F, 0x1E0F, 
        0x1E11, 0x1E11, 0x1E13, 0x1E13, 0x1E15, 0x1E15, 0x1E17, 0x1E17, 
        0x1E19, 0x1E19, 0x1E1B, 0x1E1B, 0x1E1D, 0x1E1D, 0x1E1F, 0x1E1F, 
        0x1E21, 0x1E21, 0x1E23, 0x1E23, 0x1E25, 0x1E25, 0x1E27, 0x1E27, 
        0x1E29, 0x1E29, 0x1E2B, 0x1E2B, 0x1E2D, 0x1E2D, 0x1E2F, 0x1E2F, 
        0x1E31, 0x1E31, 0x1E33, 0x1E33, 0x1E35, 0x1E35, 0x1E37, 0x1E37, 
        0x1E39, 0x1E39, 0x1E3B, 0x1E3B, 0x1E3D, 0x1E3D, 0x1E3F, 0x1E3F, 
        0x1E41, 0x1E41, 0x1E43, 0x1E43, 0x1E45, 0x1E45, 0x1E47, 0x1E47, 
        0x1E49, 0x1E49, 0x1E4B, 0x1E4B, 0x1E4D, 0x1E4D, 0x1E4F, 0x1E4F, 
        0x1E51, 0x1E51, 0x1E53, 0x1E53, 0x1E55, 0x1E55, 0x1E57, 0x1E57, 
        0x1E59, 0x1E59, 0x1E5B, 0x1E5B, 0x1E5D, 0x1E5D, 0x1E5F, 0x1E5F, 
        0x1E61, 0x1E61, 0x1E63, 0x1E63, 0x1E65, 0x1E65, 0x1E67, 0x1E67, 
        0x1E69, 0x1E69, 0x1E6B, 0x1E6B, 0x1E6D, 0x1E6D, 0x1E6F, 0x1E6F, 
        0x1E71, 0x1E71, 0x1E73, 0x1E73, 0x1E75, 0x1E75, 0x1E77, 0x1E77, 
        0x1E79, 0x1E79, 0x1E7B, 0x1E7B, 0x1E7D, 0x1E7D, 0x1E7F, 0x1E7F, 
        0x1E81, 0x1E81, 0x1E83, 0x1E83, 0x1E85, 0x1E85, 0x1E87, 0x1E87, 
        0x1E89, 0x1E89, 0x1E8B, 0x1E8B, 0x1E8D, 0x1E8D, 0x1E8F, 0x1E8F, 
        0x1E91, 0x1E91, 0x1E93, 0x1E93, 0x1E95, 0x1E95, 0x1E96, 0x1E97, 
        0x1E98, 0x1E99, 0x1E9A, 0x1E9B, 0x1E9C, 0x1E9D, 0x1E9E, 0x1E9F, 
        0x1EA1, 0x1EA1, 0x1EA3, 0x1EA3, 0x1EA5, 0x1EA5, 0x1EA7, 0x1EA7, 
        0x1EA9, 0x1EA9, 0x1EAB, 0x1EAB, 0x1EAD, 0x1EAD, 0x1EAF, 0x1EAF, 
        0x1EB1, 0x1EB1, 0x1EB3, 0x1EB3, 0x1EB5, 0x1EB5, 0x1EB7, 0x1EB7, 
        0x1EB9, 0x1EB9, 0x1EBB, 0x1EBB, 0x1EBD, 0x1EBD, 0x1EBF, 0x1EBF, 
        0x1EC1, 0x1EC1, 0x1EC3, 0x1EC3, 0x1EC5, 0x1EC5, 0x1EC7, 0x1EC7, 
        0x1EC9, 0x1EC9, 0x1ECB, 0x1ECB, 0x1ECD, 0x1ECD, 0x1ECF, 0x1ECF, 
        0x1ED1, 0x1ED1, 0x1ED3, 0x1ED3, 0x1ED5, 0x1ED5, 0x1ED7, 0x1ED7, 
        0x1ED9, 0x1ED9, 0x1EDB, 0x1EDB, 0x1EDD, 0x1EDD, 0x1EDF, 0x1EDF, 
        0x1EE1, 0x1EE1, 0x1EE3, 0x1EE3, 0x1EE5, 0x1EE5, 0x1EE7, 0x1EE7, 
        0x1EE9, 0x1EE9, 0x1EEB, 0x1EEB, 0x1EED, 0x1EED, 0x1EEF, 0x1EEF, 
        0x1EF1, 0x1EF1, 0x1EF3, 0x1EF3, 0x1EF5, 0x1EF5, 0x1EF7, 0x1EF7, 
        0x1EF9, 0x1EF9, 0x1EFA, 0x1EFB, 0x1EFC, 0x1EFD, 0x1EFE, 0x1EFF
    };

    const UCS4 Latin_Extended_Additional1E00::my_title[] =
    {
        0x1E00, 0x1E00, 0x1E02, 0x1E02, 0x1E04, 0x1E04, 0x1E06, 0x1E06, 
        0x1E08, 0x1E08, 0x1E0A, 0x1E0A, 0x1E0C, 0x1E0C, 0x1E0E, 0x1E0E, 
        0x1E10, 0x1E10, 0x1E12, 0x1E12, 0x1E14, 0x1E14, 0x1E16, 0x1E16, 
        0x1E18, 0x1E18, 0x1E1A, 0x1E1A, 0x1E1C, 0x1E1C, 0x1E1E, 0x1E1E, 
        0x1E20, 0x1E20, 0x1E22, 0x1E22, 0x1E24, 0x1E24, 0x1E26, 0x1E26, 
        0x1E28, 0x1E28, 0x1E2A, 0x1E2A, 0x1E2C, 0x1E2C, 0x1E2E, 0x1E2E, 
        0x1E30, 0x1E30, 0x1E32, 0x1E32, 0x1E34, 0x1E34, 0x1E36, 0x1E36, 
        0x1E38, 0x1E38, 0x1E3A, 0x1E3A, 0x1E3C, 0x1E3C, 0x1E3E, 0x1E3E, 
        0x1E40, 0x1E40, 0x1E42, 0x1E42, 0x1E44, 0x1E44, 0x1E46, 0x1E46, 
        0x1E48, 0x1E48, 0x1E4A, 0x1E4A, 0x1E4C, 0x1E4C, 0x1E4E, 0x1E4E, 
        0x1E50, 0x1E50, 0x1E52, 0x1E52, 0x1E54, 0x1E54, 0x1E56, 0x1E56, 
        0x1E58, 0x1E58, 0x1E5A, 0x1E5A, 0x1E5C, 0x1E5C, 0x1E5E, 0x1E5E, 
        0x1E60, 0x1E60, 0x1E62, 0x1E62, 0x1E64, 0x1E64, 0x1E66, 0x1E66, 
        0x1E68, 0x1E68, 0x1E6A, 0x1E6A, 0x1E6C, 0x1E6C, 0x1E6E, 0x1E6E, 
        0x1E70, 0x1E70, 0x1E72, 0x1E72, 0x1E74, 0x1E74, 0x1E76, 0x1E76, 
        0x1E78, 0x1E78, 0x1E7A, 0x1E7A, 0x1E7C, 0x1E7C, 0x1E7E, 0x1E7E, 
        0x1E80, 0x1E80, 0x1E82, 0x1E82, 0x1E84, 0x1E84, 0x1E86, 0x1E86, 
        0x1E88, 0x1E88, 0x1E8A, 0x1E8A, 0x1E8C, 0x1E8C, 0x1E8E, 0x1E8E, 
        0x1E90, 0x1E90, 0x1E92, 0x1E92, 0x1E94, 0x1E94, 0x1E96, 0x1E97, 
        0x1E98, 0x1E99, 0x1E9A, 0x1E60, 0x1E9C, 0x1E9D, 0x1E9E, 0x1E9F, 
        0x1EA0, 0x1EA0, 0x1EA2, 0x1EA2, 0x1EA4, 0x1EA4, 0x1EA6, 0x1EA6, 
        0x1EA8, 0x1EA8, 0x1EAA, 0x1EAA, 0x1EAC, 0x1EAC, 0x1EAE, 0x1EAE, 
        0x1EB0, 0x1EB0, 0x1EB2, 0x1EB2, 0x1EB4, 0x1EB4, 0x1EB6, 0x1EB6, 
        0x1EB8, 0x1EB8, 0x1EBA, 0x1EBA, 0x1EBC, 0x1EBC, 0x1EBE, 0x1EBE, 
        0x1EC0, 0x1EC0, 0x1EC2, 0x1EC2, 0x1EC4, 0x1EC4, 0x1EC6, 0x1EC6, 
        0x1EC8, 0x1EC8, 0x1ECA, 0x1ECA, 0x1ECC, 0x1ECC, 0x1ECE, 0x1ECE, 
        0x1ED0, 0x1ED0, 0x1ED2, 0x1ED2, 0x1ED4, 0x1ED4, 0x1ED6, 0x1ED6, 
        0x1ED8, 0x1ED8, 0x1EDA, 0x1EDA, 0x1EDC, 0x1EDC, 0x1EDE, 0x1EDE, 
        0x1EE0, 0x1EE0, 0x1EE2, 0x1EE2, 0x1EE4, 0x1EE4, 0x1EE6, 0x1EE6, 
        0x1EE8, 0x1EE8, 0x1EEA, 0x1EEA, 0x1EEC, 0x1EEC, 0x1EEE, 0x1EEE, 
        0x1EF0, 0x1EF0, 0x1EF2, 0x1EF2, 0x1EF4, 0x1EF4, 0x1EF6, 0x1EF6, 
        0x1EF8, 0x1EF8, 0x1EFA, 0x1EFB, 0x1EFC, 0x1EFD, 0x1EFE, 0x1EFF
    };

    const unsigned char Latin_Extended_Additional1E00::my_cat[] =
    {
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu
    };

    const unsigned char Latin_Extended_Additional1E00::my_decomp[] = {
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
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_COMPAT, DECOMP_CANONICAL, 
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
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL
    };

    const UCS2 Latin_Extended_Additional1E00::my_decompStr[][2] =
    {
        { 0x00000041u, 0x00000325u }, { 0x00000061u, 0x00000325u },  // 00001E00
        { 0x00000042u, 0x00000307u }, { 0x00000062u, 0x00000307u },  // 00001E02
        { 0x00000042u, 0x00000323u }, { 0x00000062u, 0x00000323u },  // 00001E04
        { 0x00000042u, 0x00000331u }, { 0x00000062u, 0x00000331u },  // 00001E06
        { 0x000000C7u, 0x00000301u }, { 0x000000E7u, 0x00000301u },  // 00001E08
        { 0x00000044u, 0x00000307u }, { 0x00000064u, 0x00000307u },  // 00001E0A
        { 0x00000044u, 0x00000323u }, { 0x00000064u, 0x00000323u },  // 00001E0C
        { 0x00000044u, 0x00000331u }, { 0x00000064u, 0x00000331u },  // 00001E0E
        { 0x00000044u, 0x00000327u }, { 0x00000064u, 0x00000327u },  // 00001E10
        { 0x00000044u, 0x0000032Du }, { 0x00000064u, 0x0000032Du },  // 00001E12
        { 0x00000112u, 0x00000300u }, { 0x00000113u, 0x00000300u },  // 00001E14
        { 0x00000112u, 0x00000301u }, { 0x00000113u, 0x00000301u },  // 00001E16
        { 0x00000045u, 0x0000032Du }, { 0x00000065u, 0x0000032Du },  // 00001E18
        { 0x00000045u, 0x00000330u }, { 0x00000065u, 0x00000330u },  // 00001E1A
        { 0x00000228u, 0x00000306u }, { 0x00000229u, 0x00000306u },  // 00001E1C
        { 0x00000046u, 0x00000307u }, { 0x00000066u, 0x00000307u },  // 00001E1E
        { 0x00000047u, 0x00000304u }, { 0x00000067u, 0x00000304u },  // 00001E20
        { 0x00000048u, 0x00000307u }, { 0x00000068u, 0x00000307u },  // 00001E22
        { 0x00000048u, 0x00000323u }, { 0x00000068u, 0x00000323u },  // 00001E24
        { 0x00000048u, 0x00000308u }, { 0x00000068u, 0x00000308u },  // 00001E26
        { 0x00000048u, 0x00000327u }, { 0x00000068u, 0x00000327u },  // 00001E28
        { 0x00000048u, 0x0000032Eu }, { 0x00000068u, 0x0000032Eu },  // 00001E2A
        { 0x00000049u, 0x00000330u }, { 0x00000069u, 0x00000330u },  // 00001E2C
        { 0x000000CFu, 0x00000301u }, { 0x000000EFu, 0x00000301u },  // 00001E2E
        { 0x0000004Bu, 0x00000301u }, { 0x0000006Bu, 0x00000301u },  // 00001E30
        { 0x0000004Bu, 0x00000323u }, { 0x0000006Bu, 0x00000323u },  // 00001E32
        { 0x0000004Bu, 0x00000331u }, { 0x0000006Bu, 0x00000331u },  // 00001E34
        { 0x0000004Cu, 0x00000323u }, { 0x0000006Cu, 0x00000323u },  // 00001E36
        { 0x00001E36u, 0x00000304u }, { 0x00001E37u, 0x00000304u },  // 00001E38
        { 0x0000004Cu, 0x00000331u }, { 0x0000006Cu, 0x00000331u },  // 00001E3A
        { 0x0000004Cu, 0x0000032Du }, { 0x0000006Cu, 0x0000032Du },  // 00001E3C
        { 0x0000004Du, 0x00000301u }, { 0x0000006Du, 0x00000301u },  // 00001E3E
        { 0x0000004Du, 0x00000307u }, { 0x0000006Du, 0x00000307u },  // 00001E40
        { 0x0000004Du, 0x00000323u }, { 0x0000006Du, 0x00000323u },  // 00001E42
        { 0x0000004Eu, 0x00000307u }, { 0x0000006Eu, 0x00000307u },  // 00001E44
        { 0x0000004Eu, 0x00000323u }, { 0x0000006Eu, 0x00000323u },  // 00001E46
        { 0x0000004Eu, 0x00000331u }, { 0x0000006Eu, 0x00000331u },  // 00001E48
        { 0x0000004Eu, 0x0000032Du }, { 0x0000006Eu, 0x0000032Du },  // 00001E4A
        { 0x000000D5u, 0x00000301u }, { 0x000000F5u, 0x00000301u },  // 00001E4C
        { 0x000000D5u, 0x00000308u }, { 0x000000F5u, 0x00000308u },  // 00001E4E
        { 0x0000014Cu, 0x00000300u }, { 0x0000014Du, 0x00000300u },  // 00001E50
        { 0x0000014Cu, 0x00000301u }, { 0x0000014Du, 0x00000301u },  // 00001E52
        { 0x00000050u, 0x00000301u }, { 0x00000070u, 0x00000301u },  // 00001E54
        { 0x00000050u, 0x00000307u }, { 0x00000070u, 0x00000307u },  // 00001E56
        { 0x00000052u, 0x00000307u }, { 0x00000072u, 0x00000307u },  // 00001E58
        { 0x00000052u, 0x00000323u }, { 0x00000072u, 0x00000323u },  // 00001E5A
        { 0x00001E5Au, 0x00000304u }, { 0x00001E5Bu, 0x00000304u },  // 00001E5C
        { 0x00000052u, 0x00000331u }, { 0x00000072u, 0x00000331u },  // 00001E5E
        { 0x00000053u, 0x00000307u }, { 0x00000073u, 0x00000307u },  // 00001E60
        { 0x00000053u, 0x00000323u }, { 0x00000073u, 0x00000323u },  // 00001E62
        { 0x0000015Au, 0x00000307u }, { 0x0000015Bu, 0x00000307u },  // 00001E64
        { 0x00000160u, 0x00000307u }, { 0x00000161u, 0x00000307u },  // 00001E66
        { 0x00001E62u, 0x00000307u }, { 0x00001E63u, 0x00000307u },  // 00001E68
        { 0x00000054u, 0x00000307u }, { 0x00000074u, 0x00000307u },  // 00001E6A
        { 0x00000054u, 0x00000323u }, { 0x00000074u, 0x00000323u },  // 00001E6C
        { 0x00000054u, 0x00000331u }, { 0x00000074u, 0x00000331u },  // 00001E6E
        { 0x00000054u, 0x0000032Du }, { 0x00000074u, 0x0000032Du },  // 00001E70
        { 0x00000055u, 0x00000324u }, { 0x00000075u, 0x00000324u },  // 00001E72
        { 0x00000055u, 0x00000330u }, { 0x00000075u, 0x00000330u },  // 00001E74
        { 0x00000055u, 0x0000032Du }, { 0x00000075u, 0x0000032Du },  // 00001E76
        { 0x00000168u, 0x00000301u }, { 0x00000169u, 0x00000301u },  // 00001E78
        { 0x0000016Au, 0x00000308u }, { 0x0000016Bu, 0x00000308u },  // 00001E7A
        { 0x00000056u, 0x00000303u }, { 0x00000076u, 0x00000303u },  // 00001E7C
        { 0x00000056u, 0x00000323u }, { 0x00000076u, 0x00000323u },  // 00001E7E
        { 0x00000057u, 0x00000300u }, { 0x00000077u, 0x00000300u },  // 00001E80
        { 0x00000057u, 0x00000301u }, { 0x00000077u, 0x00000301u },  // 00001E82
        { 0x00000057u, 0x00000308u }, { 0x00000077u, 0x00000308u },  // 00001E84
        { 0x00000057u, 0x00000307u }, { 0x00000077u, 0x00000307u },  // 00001E86
        { 0x00000057u, 0x00000323u }, { 0x00000077u, 0x00000323u },  // 00001E88
        { 0x00000058u, 0x00000307u }, { 0x00000078u, 0x00000307u },  // 00001E8A
        { 0x00000058u, 0x00000308u }, { 0x00000078u, 0x00000308u },  // 00001E8C
        { 0x00000059u, 0x00000307u }, { 0x00000079u, 0x00000307u },  // 00001E8E
        { 0x0000005Au, 0x00000302u }, { 0x0000007Au, 0x00000302u },  // 00001E90
        { 0x0000005Au, 0x00000323u }, { 0x0000007Au, 0x00000323u },  // 00001E92
        { 0x0000005Au, 0x00000331u }, { 0x0000007Au, 0x00000331u },  // 00001E94
        { 0x00000068u, 0x00000331u }, { 0x00000074u, 0x00000308u },  // 00001E96
        { 0x00000077u, 0x0000030Au }, { 0x00000079u, 0x0000030Au },  // 00001E98
        { 0x00000061u, 0x000002BEu }, { 0x0000017Fu, 0x00000307u },  // 00001E9A
        { 0x00001E9Cu, 0x00000000u }, { 0x00001E9Du, 0x00000000u },  // 00001E9C
        { 0x00001E9Eu, 0x00000000u }, { 0x00001E9Fu, 0x00000000u },  // 00001E9E
        { 0x00000041u, 0x00000323u }, { 0x00000061u, 0x00000323u },  // 00001EA0
        { 0x00000041u, 0x00000309u }, { 0x00000061u, 0x00000309u },  // 00001EA2
        { 0x000000C2u, 0x00000301u }, { 0x000000E2u, 0x00000301u },  // 00001EA4
        { 0x000000C2u, 0x00000300u }, { 0x000000E2u, 0x00000300u },  // 00001EA6
        { 0x000000C2u, 0x00000309u }, { 0x000000E2u, 0x00000309u },  // 00001EA8
        { 0x000000C2u, 0x00000303u }, { 0x000000E2u, 0x00000303u },  // 00001EAA
        { 0x00001EA0u, 0x00000302u }, { 0x00001EA1u, 0x00000302u },  // 00001EAC
        { 0x00000102u, 0x00000301u }, { 0x00000103u, 0x00000301u },  // 00001EAE
        { 0x00000102u, 0x00000300u }, { 0x00000103u, 0x00000300u },  // 00001EB0
        { 0x00000102u, 0x00000309u }, { 0x00000103u, 0x00000309u },  // 00001EB2
        { 0x00000102u, 0x00000303u }, { 0x00000103u, 0x00000303u },  // 00001EB4
        { 0x00001EA0u, 0x00000306u }, { 0x00001EA1u, 0x00000306u },  // 00001EB6
        { 0x00000045u, 0x00000323u }, { 0x00000065u, 0x00000323u },  // 00001EB8
        { 0x00000045u, 0x00000309u }, { 0x00000065u, 0x00000309u },  // 00001EBA
        { 0x00000045u, 0x00000303u }, { 0x00000065u, 0x00000303u },  // 00001EBC
        { 0x000000CAu, 0x00000301u }, { 0x000000EAu, 0x00000301u },  // 00001EBE
        { 0x000000CAu, 0x00000300u }, { 0x000000EAu, 0x00000300u },  // 00001EC0
        { 0x000000CAu, 0x00000309u }, { 0x000000EAu, 0x00000309u },  // 00001EC2
        { 0x000000CAu, 0x00000303u }, { 0x000000EAu, 0x00000303u },  // 00001EC4
        { 0x00001EB8u, 0x00000302u }, { 0x00001EB9u, 0x00000302u },  // 00001EC6
        { 0x00000049u, 0x00000309u }, { 0x00000069u, 0x00000309u },  // 00001EC8
        { 0x00000049u, 0x00000323u }, { 0x00000069u, 0x00000323u },  // 00001ECA
        { 0x0000004Fu, 0x00000323u }, { 0x0000006Fu, 0x00000323u },  // 00001ECC
        { 0x0000004Fu, 0x00000309u }, { 0x0000006Fu, 0x00000309u },  // 00001ECE
        { 0x000000D4u, 0x00000301u }, { 0x000000F4u, 0x00000301u },  // 00001ED0
        { 0x000000D4u, 0x00000300u }, { 0x000000F4u, 0x00000300u },  // 00001ED2
        { 0x000000D4u, 0x00000309u }, { 0x000000F4u, 0x00000309u },  // 00001ED4
        { 0x000000D4u, 0x00000303u }, { 0x000000F4u, 0x00000303u },  // 00001ED6
        { 0x00001ECCu, 0x00000302u }, { 0x00001ECDu, 0x00000302u },  // 00001ED8
        { 0x000001A0u, 0x00000301u }, { 0x000001A1u, 0x00000301u },  // 00001EDA
        { 0x000001A0u, 0x00000300u }, { 0x000001A1u, 0x00000300u },  // 00001EDC
        { 0x000001A0u, 0x00000309u }, { 0x000001A1u, 0x00000309u },  // 00001EDE
        { 0x000001A0u, 0x00000303u }, { 0x000001A1u, 0x00000303u },  // 00001EE0
        { 0x000001A0u, 0x00000323u }, { 0x000001A1u, 0x00000323u },  // 00001EE2
        { 0x00000055u, 0x00000323u }, { 0x00000075u, 0x00000323u },  // 00001EE4
        { 0x00000055u, 0x00000309u }, { 0x00000075u, 0x00000309u },  // 00001EE6
        { 0x000001AFu, 0x00000301u }, { 0x000001B0u, 0x00000301u },  // 00001EE8
        { 0x000001AFu, 0x00000300u }, { 0x000001B0u, 0x00000300u },  // 00001EEA
        { 0x000001AFu, 0x00000309u }, { 0x000001B0u, 0x00000309u },  // 00001EEC
        { 0x000001AFu, 0x00000303u }, { 0x000001B0u, 0x00000303u },  // 00001EEE
        { 0x000001AFu, 0x00000323u }, { 0x000001B0u, 0x00000323u },  // 00001EF0
        { 0x00000059u, 0x00000300u }, { 0x00000079u, 0x00000300u },  // 00001EF2
        { 0x00000059u, 0x00000323u }, { 0x00000079u, 0x00000323u },  // 00001EF4
        { 0x00000059u, 0x00000309u }, { 0x00000079u, 0x00000309u },  // 00001EF6
        { 0x00000059u, 0x00000303u }, { 0x00000079u, 0x00000303u },  // 00001EF8
        { 0x00001EFAu, 0x00000000u }, { 0x00001EFBu, 0x00000000u },  // 00001EFA
        { 0x00001EFCu, 0x00000000u }, { 0x00001EFDu, 0x00000000u },  // 00001EFC
        { 0x00001EFEu, 0x00000000u }, { 0x00001EFFu, 0x00000000u }
    };

    const std::bitset<256> Latin_Extended_Additional1E00::my_Soft_Dotted(std::string("0000000000000000000000000000000000000000000000000000100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000"));

  }; // namespace
}; // namespace

dload(Babylon::Module::Latin_Extended_Additional1E00);
