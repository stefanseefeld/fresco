/*$Id: UnicodePluginGenerator.pl,v 1.7 2003/08/01 16:47:16 tobias Exp 1D400-1D7FF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 05 Aug 2003 17:10:28 +0200.
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


namespace Babylon
{
  namespace Module
  {
    class Mathematical_Alphanumeric_Symbols1D400 : public Babylon::Block
    {
      public:
        void clean() { };

        Mathematical_Alphanumeric_Symbols1D400() :
        my_first_letter(0x1D400),
        my_last_letter(0x1D7FF)
        // my_version="4.0" // Not yet supported!
        {
        }

        ~Mathematical_Alphanumeric_Symbols1D400() { }

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
        return "Mathematical Alphanumeric Symbols";
    }

        bool is_defined(const UCS4 uc) const
        {
            return (my_is_defined.test(uc - my_first_letter));
        }

        UCS4 uppercase(const UCS4 uc) const
        {
            return uc;
        }

        UCS4 lowercase(const UCS4 uc) const
        {
            return uc;
        }

        UCS4 titlecase(const UCS4 uc) const
        {
            return uc;
        }

        int dec_digit_value(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return 0;
            switch(uc)
            {
            case 0x1D7CEu:
                return 0;
            case 0x1D7CFu:
                return 1;
            case 0x1D7D0u:
                return 2;
            case 0x1D7D1u:
                return 3;
            case 0x1D7D2u:
                return 4;
            case 0x1D7D3u:
                return 5;
            case 0x1D7D4u:
                return 6;
            case 0x1D7D5u:
                return 7;
            case 0x1D7D6u:
                return 8;
            case 0x1D7D7u:
                return 9;
            case 0x1D7D8u:
                return 0;
            case 0x1D7D9u:
                return 1;
            case 0x1D7DAu:
                return 2;
            case 0x1D7DBu:
                return 3;
            case 0x1D7DCu:
                return 4;
            case 0x1D7DDu:
                return 5;
            case 0x1D7DEu:
                return 6;
            case 0x1D7DFu:
                return 7;
            case 0x1D7E0u:
                return 8;
            case 0x1D7E1u:
                return 9;
            case 0x1D7E2u:
                return 0;
            case 0x1D7E3u:
                return 1;
            case 0x1D7E4u:
                return 2;
            case 0x1D7E5u:
                return 3;
            case 0x1D7E6u:
                return 4;
            case 0x1D7E7u:
                return 5;
            case 0x1D7E8u:
                return 6;
            case 0x1D7E9u:
                return 7;
            case 0x1D7EAu:
                return 8;
            case 0x1D7EBu:
                return 9;
            case 0x1D7ECu:
                return 0;
            case 0x1D7EDu:
                return 1;
            case 0x1D7EEu:
                return 2;
            case 0x1D7EFu:
                return 3;
            case 0x1D7F0u:
                return 4;
            case 0x1D7F1u:
                return 5;
            case 0x1D7F2u:
                return 6;
            case 0x1D7F3u:
                return 7;
            case 0x1D7F4u:
                return 8;
            case 0x1D7F5u:
                return 9;
            case 0x1D7F6u:
                return 0;
            case 0x1D7F7u:
                return 1;
            case 0x1D7F8u:
                return 2;
            case 0x1D7F9u:
                return 3;
            case 0x1D7FAu:
                return 4;
            case 0x1D7FBu:
                return 5;
            case 0x1D7FCu:
                return 6;
            case 0x1D7FDu:
                return 7;
            case 0x1D7FEu:
                return 8;
            case 0x1D7FFu:
                return 9;
            default:
                return 0;
            }
        }

        bool is_Decimal_Digit(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x1D7CEu:
            case 0x1D7CFu:
            case 0x1D7D0u:
            case 0x1D7D1u:
            case 0x1D7D2u:
            case 0x1D7D3u:
            case 0x1D7D4u:
            case 0x1D7D5u:
            case 0x1D7D6u:
            case 0x1D7D7u:
            case 0x1D7D8u:
            case 0x1D7D9u:
            case 0x1D7DAu:
            case 0x1D7DBu:
            case 0x1D7DCu:
            case 0x1D7DDu:
            case 0x1D7DEu:
            case 0x1D7DFu:
            case 0x1D7E0u:
            case 0x1D7E1u:
            case 0x1D7E2u:
            case 0x1D7E3u:
            case 0x1D7E4u:
            case 0x1D7E5u:
            case 0x1D7E6u:
            case 0x1D7E7u:
            case 0x1D7E8u:
            case 0x1D7E9u:
            case 0x1D7EAu:
            case 0x1D7EBu:
            case 0x1D7ECu:
            case 0x1D7EDu:
            case 0x1D7EEu:
            case 0x1D7EFu:
            case 0x1D7F0u:
            case 0x1D7F1u:
            case 0x1D7F2u:
            case 0x1D7F3u:
            case 0x1D7F4u:
            case 0x1D7F5u:
            case 0x1D7F6u:
            case 0x1D7F7u:
            case 0x1D7F8u:
            case 0x1D7F9u:
            case 0x1D7FAu:
            case 0x1D7FBu:
            case 0x1D7FCu:
            case 0x1D7FDu:
            case 0x1D7FEu:
            case 0x1D7FFu:
                return 1;
            default:
                return 0;
            }
        }

        int digit_value(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return 0;
            switch(uc)
            {
            case 0x1D7CEu:
                return 0;
            case 0x1D7CFu:
                return 1;
            case 0x1D7D0u:
                return 2;
            case 0x1D7D1u:
                return 3;
            case 0x1D7D2u:
                return 4;
            case 0x1D7D3u:
                return 5;
            case 0x1D7D4u:
                return 6;
            case 0x1D7D5u:
                return 7;
            case 0x1D7D6u:
                return 8;
            case 0x1D7D7u:
                return 9;
            case 0x1D7D8u:
                return 0;
            case 0x1D7D9u:
                return 1;
            case 0x1D7DAu:
                return 2;
            case 0x1D7DBu:
                return 3;
            case 0x1D7DCu:
                return 4;
            case 0x1D7DDu:
                return 5;
            case 0x1D7DEu:
                return 6;
            case 0x1D7DFu:
                return 7;
            case 0x1D7E0u:
                return 8;
            case 0x1D7E1u:
                return 9;
            case 0x1D7E2u:
                return 0;
            case 0x1D7E3u:
                return 1;
            case 0x1D7E4u:
                return 2;
            case 0x1D7E5u:
                return 3;
            case 0x1D7E6u:
                return 4;
            case 0x1D7E7u:
                return 5;
            case 0x1D7E8u:
                return 6;
            case 0x1D7E9u:
                return 7;
            case 0x1D7EAu:
                return 8;
            case 0x1D7EBu:
                return 9;
            case 0x1D7ECu:
                return 0;
            case 0x1D7EDu:
                return 1;
            case 0x1D7EEu:
                return 2;
            case 0x1D7EFu:
                return 3;
            case 0x1D7F0u:
                return 4;
            case 0x1D7F1u:
                return 5;
            case 0x1D7F2u:
                return 6;
            case 0x1D7F3u:
                return 7;
            case 0x1D7F4u:
                return 8;
            case 0x1D7F5u:
                return 9;
            case 0x1D7F6u:
                return 0;
            case 0x1D7F7u:
                return 1;
            case 0x1D7F8u:
                return 2;
            case 0x1D7F9u:
                return 3;
            case 0x1D7FAu:
                return 4;
            case 0x1D7FBu:
                return 5;
            case 0x1D7FCu:
                return 6;
            case 0x1D7FDu:
                return 7;
            case 0x1D7FEu:
                return 8;
            case 0x1D7FFu:
                return 9;
            default:
                return 0;
            }
        }

        bool is_Digit(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x1D7CEu:
            case 0x1D7CFu:
            case 0x1D7D0u:
            case 0x1D7D1u:
            case 0x1D7D2u:
            case 0x1D7D3u:
            case 0x1D7D4u:
            case 0x1D7D5u:
            case 0x1D7D6u:
            case 0x1D7D7u:
            case 0x1D7D8u:
            case 0x1D7D9u:
            case 0x1D7DAu:
            case 0x1D7DBu:
            case 0x1D7DCu:
            case 0x1D7DDu:
            case 0x1D7DEu:
            case 0x1D7DFu:
            case 0x1D7E0u:
            case 0x1D7E1u:
            case 0x1D7E2u:
            case 0x1D7E3u:
            case 0x1D7E4u:
            case 0x1D7E5u:
            case 0x1D7E6u:
            case 0x1D7E7u:
            case 0x1D7E8u:
            case 0x1D7E9u:
            case 0x1D7EAu:
            case 0x1D7EBu:
            case 0x1D7ECu:
            case 0x1D7EDu:
            case 0x1D7EEu:
            case 0x1D7EFu:
            case 0x1D7F0u:
            case 0x1D7F1u:
            case 0x1D7F2u:
            case 0x1D7F3u:
            case 0x1D7F4u:
            case 0x1D7F5u:
            case 0x1D7F6u:
            case 0x1D7F7u:
            case 0x1D7F8u:
            case 0x1D7F9u:
            case 0x1D7FAu:
            case 0x1D7FBu:
            case 0x1D7FCu:
            case 0x1D7FDu:
            case 0x1D7FEu:
            case 0x1D7FFu:
                return 1;
            default:
                return 0;
            }
        }

        float numeric_value(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return 0;
            switch(uc)
            {
            case 0x1D7CEu:
                return 0.000000;
            case 0x1D7CFu:
                return 1.000000;
            case 0x1D7D0u:
                return 2.000000;
            case 0x1D7D1u:
                return 3.000000;
            case 0x1D7D2u:
                return 4.000000;
            case 0x1D7D3u:
                return 5.000000;
            case 0x1D7D4u:
                return 6.000000;
            case 0x1D7D5u:
                return 7.000000;
            case 0x1D7D6u:
                return 8.000000;
            case 0x1D7D7u:
                return 9.000000;
            case 0x1D7D8u:
                return 0.000000;
            case 0x1D7D9u:
                return 1.000000;
            case 0x1D7DAu:
                return 2.000000;
            case 0x1D7DBu:
                return 3.000000;
            case 0x1D7DCu:
                return 4.000000;
            case 0x1D7DDu:
                return 5.000000;
            case 0x1D7DEu:
                return 6.000000;
            case 0x1D7DFu:
                return 7.000000;
            case 0x1D7E0u:
                return 8.000000;
            case 0x1D7E1u:
                return 9.000000;
            case 0x1D7E2u:
                return 0.000000;
            case 0x1D7E3u:
                return 1.000000;
            case 0x1D7E4u:
                return 2.000000;
            case 0x1D7E5u:
                return 3.000000;
            case 0x1D7E6u:
                return 4.000000;
            case 0x1D7E7u:
                return 5.000000;
            case 0x1D7E8u:
                return 6.000000;
            case 0x1D7E9u:
                return 7.000000;
            case 0x1D7EAu:
                return 8.000000;
            case 0x1D7EBu:
                return 9.000000;
            case 0x1D7ECu:
                return 0.000000;
            case 0x1D7EDu:
                return 1.000000;
            case 0x1D7EEu:
                return 2.000000;
            case 0x1D7EFu:
                return 3.000000;
            case 0x1D7F0u:
                return 4.000000;
            case 0x1D7F1u:
                return 5.000000;
            case 0x1D7F2u:
                return 6.000000;
            case 0x1D7F3u:
                return 7.000000;
            case 0x1D7F4u:
                return 8.000000;
            case 0x1D7F5u:
                return 9.000000;
            case 0x1D7F6u:
                return 0.000000;
            case 0x1D7F7u:
                return 1.000000;
            case 0x1D7F8u:
                return 2.000000;
            case 0x1D7F9u:
                return 3.000000;
            case 0x1D7FAu:
                return 4.000000;
            case 0x1D7FBu:
                return 5.000000;
            case 0x1D7FCu:
                return 6.000000;
            case 0x1D7FDu:
                return 7.000000;
            case 0x1D7FEu:
                return 8.000000;
            case 0x1D7FFu:
                return 9.000000;
            default:
                return 0;
            }
        }

        bool is_Numeric(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x1D7CEu:
            case 0x1D7CFu:
            case 0x1D7D0u:
            case 0x1D7D1u:
            case 0x1D7D2u:
            case 0x1D7D3u:
            case 0x1D7D4u:
            case 0x1D7D5u:
            case 0x1D7D6u:
            case 0x1D7D7u:
            case 0x1D7D8u:
            case 0x1D7D9u:
            case 0x1D7DAu:
            case 0x1D7DBu:
            case 0x1D7DCu:
            case 0x1D7DDu:
            case 0x1D7DEu:
            case 0x1D7DFu:
            case 0x1D7E0u:
            case 0x1D7E1u:
            case 0x1D7E2u:
            case 0x1D7E3u:
            case 0x1D7E4u:
            case 0x1D7E5u:
            case 0x1D7E6u:
            case 0x1D7E7u:
            case 0x1D7E8u:
            case 0x1D7E9u:
            case 0x1D7EAu:
            case 0x1D7EBu:
            case 0x1D7ECu:
            case 0x1D7EDu:
            case 0x1D7EEu:
            case 0x1D7EFu:
            case 0x1D7F0u:
            case 0x1D7F1u:
            case 0x1D7F2u:
            case 0x1D7F3u:
            case 0x1D7F4u:
            case 0x1D7F5u:
            case 0x1D7F6u:
            case 0x1D7F7u:
            case 0x1D7F8u:
            case 0x1D7F9u:
            case 0x1D7FAu:
            case 0x1D7FBu:
            case 0x1D7FCu:
            case 0x1D7FDu:
            case 0x1D7FEu:
            case 0x1D7FFu:
                return 1;
            default:
                return 0;
            }
        }

        Gen_Cat category(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CAT_MAX;
            return Babylon::Gen_Cat(Mathematical_Alphanumeric_Symbols1D400::my_cat[uc - my_first_letter]);
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
            return Mathematical_Alphanumeric_Symbols1D400::my_bidir[uc - my_first_letter];
        }

        Char_Decomp decomp_type(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return DECOMP_MAX;
            return Babylon::Char_Decomp(Mathematical_Alphanumeric_Symbols1D400::my_decomp[uc - my_first_letter]);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            Babylon::UTF32_string us;
            us.resize(1);
            us[0] = Mathematical_Alphanumeric_Symbols1D400::my_decompStr[uc - my_first_letter];
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
            return Babylon::Line_Break(Mathematical_Alphanumeric_Symbols1D400::my_lb[uc - my_first_letter]);
        }

        EA_Width EA_width(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return EA_WIDTH_MAX;
            return Babylon::EA_Width(EA_WIDTH_N);
        }

        UCS4 compose(const UCS4 starter, const UCS4 last)
        {
            return 0;
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
            return my_Other_Math.test(uc - my_first_letter);
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
            return 0;
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
        Mathematical_Alphanumeric_Symbols1D400(const Mathematical_Alphanumeric_Symbols1D400 &) ; // no implementaion!

    // members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const std::bitset<1024> my_is_defined;
        static const unsigned char my_cat[1024];
        static const Babylon::Bidir_Props my_bidir[1024];
        static const unsigned char my_decomp[1024];
        static const UCS4 my_decompStr[1024];
        static const unsigned char my_lb[1024];
        static const std::bitset<1024> my_Other_Math;
    }; // class Mathematical_Alphanumeric_Symbols1D400

    const std::bitset<1024> Mathematical_Alphanumeric_Symbols1D400::my_is_defined(std::string("1111111111111111111111111111111111111111111111111100001111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111100001111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111101111111000101111101111011111111111111111111111111110111111101111111100111101111111111111111111111111111111111111111111111111111111111111111101111111010111111111111011110011001001101111111111111111111111111111111111111111111111111111111111111111111111101111111111111111111111111111111111111111111111111111111111111111111111111111111111111"));

    const unsigned char Mathematical_Alphanumeric_Symbols1D400::my_cat[] =
    {
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Sm, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Sm, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Sm, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Sm, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Sm, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Sm, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Sm, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Sm, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Sm, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Sm, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Nd, CAT_Nd, 
        CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, 
        CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, 
        CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, 
        CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, 
        CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, 
        CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd
    };

    const Babylon::Bidir_Props Mathematical_Alphanumeric_Symbols1D400::my_bidir[] =
    {
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_EN, BIDIR_EN, 
        BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
        BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
        BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
        BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
        BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
        BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
        BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
        BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
        BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
        BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
        BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
        BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN
    };

    const unsigned char Mathematical_Alphanumeric_Symbols1D400::my_decomp[] = {
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_CANONICAL, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_CANONICAL, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_FONT, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_FONT, DECOMP_FONT, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_CANONICAL, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_CANONICAL, DECOMP_FONT, 
        DECOMP_CANONICAL, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_CANONICAL, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_CANONICAL, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_CANONICAL, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_CANONICAL, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_CANONICAL, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_CANONICAL, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_CANONICAL, DECOMP_FONT, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_CANONICAL, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, 
        DECOMP_FONT, DECOMP_FONT, DECOMP_FONT, DECOMP_FONT
    };

    const UCS4 Mathematical_Alphanumeric_Symbols1D400::my_decompStr[] =
    {
        0x00000041u, 0x00000042u, 0x00000043u, 0x00000044u,  // 0001D400
        0x00000045u, 0x00000046u, 0x00000047u, 0x00000048u,  // 0001D404
        0x00000049u, 0x0000004Au, 0x0000004Bu, 0x0000004Cu,  // 0001D408
        0x0000004Du, 0x0000004Eu, 0x0000004Fu, 0x00000050u,  // 0001D40C
        0x00000051u, 0x00000052u, 0x00000053u, 0x00000054u,  // 0001D410
        0x00000055u, 0x00000056u, 0x00000057u, 0x00000058u,  // 0001D414
        0x00000059u, 0x0000005Au, 0x00000061u, 0x00000062u,  // 0001D418
        0x00000063u, 0x00000064u, 0x00000065u, 0x00000066u,  // 0001D41C
        0x00000067u, 0x00000068u, 0x00000069u, 0x0000006Au,  // 0001D420
        0x0000006Bu, 0x0000006Cu, 0x0000006Du, 0x0000006Eu,  // 0001D424
        0x0000006Fu, 0x00000070u, 0x00000071u, 0x00000072u,  // 0001D428
        0x00000073u, 0x00000074u, 0x00000075u, 0x00000076u,  // 0001D42C
        0x00000077u, 0x00000078u, 0x00000079u, 0x0000007Au,  // 0001D430
        0x00000041u, 0x00000042u, 0x00000043u, 0x00000044u,  // 0001D434
        0x00000045u, 0x00000046u, 0x00000047u, 0x00000048u,  // 0001D438
        0x00000049u, 0x0000004Au, 0x0000004Bu, 0x0000004Cu,  // 0001D43C
        0x0000004Du, 0x0000004Eu, 0x0000004Fu, 0x00000050u,  // 0001D440
        0x00000051u, 0x00000052u, 0x00000053u, 0x00000054u,  // 0001D444
        0x00000055u, 0x00000056u, 0x00000057u, 0x00000058u,  // 0001D448
        0x00000059u, 0x0000005Au, 0x00000061u, 0x00000062u,  // 0001D44C
        0x00000063u, 0x00000064u, 0x00000065u, 0x00000066u,  // 0001D450
        0x00000067u, 0x0001D455u, 0x00000069u, 0x0000006Au,  // 0001D454
        0x0000006Bu, 0x0000006Cu, 0x0000006Du, 0x0000006Eu,  // 0001D458
        0x0000006Fu, 0x00000070u, 0x00000071u, 0x00000072u,  // 0001D45C
        0x00000073u, 0x00000074u, 0x00000075u, 0x00000076u,  // 0001D460
        0x00000077u, 0x00000078u, 0x00000079u, 0x0000007Au,  // 0001D464
        0x00000041u, 0x00000042u, 0x00000043u, 0x00000044u,  // 0001D468
        0x00000045u, 0x00000046u, 0x00000047u, 0x00000048u,  // 0001D46C
        0x00000049u, 0x0000004Au, 0x0000004Bu, 0x0000004Cu,  // 0001D470
        0x0000004Du, 0x0000004Eu, 0x0000004Fu, 0x00000050u,  // 0001D474
        0x00000051u, 0x00000052u, 0x00000053u, 0x00000054u,  // 0001D478
        0x00000055u, 0x00000056u, 0x00000057u, 0x00000058u,  // 0001D47C
        0x00000059u, 0x0000005Au, 0x00000061u, 0x00000062u,  // 0001D480
        0x00000063u, 0x00000064u, 0x00000065u, 0x00000066u,  // 0001D484
        0x00000067u, 0x00000068u, 0x00000069u, 0x0000006Au,  // 0001D488
        0x0000006Bu, 0x0000006Cu, 0x0000006Du, 0x0000006Eu,  // 0001D48C
        0x0000006Fu, 0x00000070u, 0x00000071u, 0x00000072u,  // 0001D490
        0x00000073u, 0x00000074u, 0x00000075u, 0x00000076u,  // 0001D494
        0x00000077u, 0x00000078u, 0x00000079u, 0x0000007Au,  // 0001D498
        0x00000041u, 0x0001D49Du, 0x00000043u, 0x00000044u,  // 0001D49C
        0x0001D4A0u, 0x0001D4A1u, 0x00000047u, 0x0001D4A3u,  // 0001D4A0
        0x0001D4A4u, 0x0000004Au, 0x0000004Bu, 0x0001D4A7u,  // 0001D4A4
        0x0001D4A8u, 0x0000004Eu, 0x0000004Fu, 0x00000050u,  // 0001D4A8
        0x00000051u, 0x0001D4ADu, 0x00000053u, 0x00000054u,  // 0001D4AC
        0x00000055u, 0x00000056u, 0x00000057u, 0x00000058u,  // 0001D4B0
        0x00000059u, 0x0000005Au, 0x00000061u, 0x00000062u,  // 0001D4B4
        0x00000063u, 0x00000064u, 0x0001D4BAu, 0x00000066u,  // 0001D4B8
        0x0001D4BCu, 0x00000068u, 0x00000069u, 0x0000006Au,  // 0001D4BC
        0x0000006Bu, 0x0000006Cu, 0x0000006Du, 0x0000006Eu,  // 0001D4C0
        0x0001D4C4u, 0x00000070u, 0x00000071u, 0x00000072u,  // 0001D4C4
        0x00000073u, 0x00000074u, 0x00000075u, 0x00000076u,  // 0001D4C8
        0x00000077u, 0x00000078u, 0x00000079u, 0x0000007Au,  // 0001D4CC
        0x00000041u, 0x00000042u, 0x00000043u, 0x00000044u,  // 0001D4D0
        0x00000045u, 0x00000046u, 0x00000047u, 0x00000048u,  // 0001D4D4
        0x00000049u, 0x0000004Au, 0x0000004Bu, 0x0000004Cu,  // 0001D4D8
        0x0000004Du, 0x0000004Eu, 0x0000004Fu, 0x00000050u,  // 0001D4DC
        0x00000051u, 0x00000052u, 0x00000053u, 0x00000054u,  // 0001D4E0
        0x00000055u, 0x00000056u, 0x00000057u, 0x00000058u,  // 0001D4E4
        0x00000059u, 0x0000005Au, 0x00000061u, 0x00000062u,  // 0001D4E8
        0x00000063u, 0x00000064u, 0x00000065u, 0x00000066u,  // 0001D4EC
        0x00000067u, 0x00000068u, 0x00000069u, 0x0000006Au,  // 0001D4F0
        0x0000006Bu, 0x0000006Cu, 0x0000006Du, 0x0000006Eu,  // 0001D4F4
        0x0000006Fu, 0x00000070u, 0x00000071u, 0x00000072u,  // 0001D4F8
        0x00000073u, 0x00000074u, 0x00000075u, 0x00000076u,  // 0001D4FC
        0x00000077u, 0x00000078u, 0x00000079u, 0x0000007Au,  // 0001D500
        0x00000041u, 0x00000042u, 0x0001D506u, 0x00000044u,  // 0001D504
        0x00000045u, 0x00000046u, 0x00000047u, 0x0001D50Bu,  // 0001D508
        0x0001D50Cu, 0x0000004Au, 0x0000004Bu, 0x0000004Cu,  // 0001D50C
        0x0000004Du, 0x0000004Eu, 0x0000004Fu, 0x00000050u,  // 0001D510
        0x00000051u, 0x0001D515u, 0x00000053u, 0x00000054u,  // 0001D514
        0x00000055u, 0x00000056u, 0x00000057u, 0x00000058u,  // 0001D518
        0x00000059u, 0x0001D51Du, 0x00000061u, 0x00000062u,  // 0001D51C
        0x00000063u, 0x00000064u, 0x00000065u, 0x00000066u,  // 0001D520
        0x00000067u, 0x00000068u, 0x00000069u, 0x0000006Au,  // 0001D524
        0x0000006Bu, 0x0000006Cu, 0x0000006Du, 0x0000006Eu,  // 0001D528
        0x0000006Fu, 0x00000070u, 0x00000071u, 0x00000072u,  // 0001D52C
        0x00000073u, 0x00000074u, 0x00000075u, 0x00000076u,  // 0001D530
        0x00000077u, 0x00000078u, 0x00000079u, 0x0000007Au,  // 0001D534
        0x00000041u, 0x00000042u, 0x0001D53Au, 0x00000044u,  // 0001D538
        0x00000045u, 0x00000046u, 0x00000047u, 0x0001D53Fu,  // 0001D53C
        0x00000049u, 0x0000004Au, 0x0000004Bu, 0x0000004Cu,  // 0001D540
        0x0000004Du, 0x0001D545u, 0x0000004Fu, 0x0001D547u,  // 0001D544
        0x0001D548u, 0x0001D549u, 0x00000053u, 0x00000054u,  // 0001D548
        0x00000055u, 0x00000056u, 0x00000057u, 0x00000058u,  // 0001D54C
        0x00000059u, 0x0001D551u, 0x00000061u, 0x00000062u,  // 0001D550
        0x00000063u, 0x00000064u, 0x00000065u, 0x00000066u,  // 0001D554
        0x00000067u, 0x00000068u, 0x00000069u, 0x0000006Au,  // 0001D558
        0x0000006Bu, 0x0000006Cu, 0x0000006Du, 0x0000006Eu,  // 0001D55C
        0x0000006Fu, 0x00000070u, 0x00000071u, 0x00000072u,  // 0001D560
        0x00000073u, 0x00000074u, 0x00000075u, 0x00000076u,  // 0001D564
        0x00000077u, 0x00000078u, 0x00000079u, 0x0000007Au,  // 0001D568
        0x00000041u, 0x00000042u, 0x00000043u, 0x00000044u,  // 0001D56C
        0x00000045u, 0x00000046u, 0x00000047u, 0x00000048u,  // 0001D570
        0x00000049u, 0x0000004Au, 0x0000004Bu, 0x0000004Cu,  // 0001D574
        0x0000004Du, 0x0000004Eu, 0x0000004Fu, 0x00000050u,  // 0001D578
        0x00000051u, 0x00000052u, 0x00000053u, 0x00000054u,  // 0001D57C
        0x00000055u, 0x00000056u, 0x00000057u, 0x00000058u,  // 0001D580
        0x00000059u, 0x0000005Au, 0x00000061u, 0x00000062u,  // 0001D584
        0x00000063u, 0x00000064u, 0x00000065u, 0x00000066u,  // 0001D588
        0x00000067u, 0x00000068u, 0x00000069u, 0x0000006Au,  // 0001D58C
        0x0000006Bu, 0x0000006Cu, 0x0000006Du, 0x0000006Eu,  // 0001D590
        0x0000006Fu, 0x00000070u, 0x00000071u, 0x00000072u,  // 0001D594
        0x00000073u, 0x00000074u, 0x00000075u, 0x00000076u,  // 0001D598
        0x00000077u, 0x00000078u, 0x00000079u, 0x0000007Au,  // 0001D59C
        0x00000041u, 0x00000042u, 0x00000043u, 0x00000044u,  // 0001D5A0
        0x00000045u, 0x00000046u, 0x00000047u, 0x00000048u,  // 0001D5A4
        0x00000049u, 0x0000004Au, 0x0000004Bu, 0x0000004Cu,  // 0001D5A8
        0x0000004Du, 0x0000004Eu, 0x0000004Fu, 0x00000050u,  // 0001D5AC
        0x00000051u, 0x00000052u, 0x00000053u, 0x00000054u,  // 0001D5B0
        0x00000055u, 0x00000056u, 0x00000057u, 0x00000058u,  // 0001D5B4
        0x00000059u, 0x0000005Au, 0x00000061u, 0x00000062u,  // 0001D5B8
        0x00000063u, 0x00000064u, 0x00000065u, 0x00000066u,  // 0001D5BC
        0x00000067u, 0x00000068u, 0x00000069u, 0x0000006Au,  // 0001D5C0
        0x0000006Bu, 0x0000006Cu, 0x0000006Du, 0x0000006Eu,  // 0001D5C4
        0x0000006Fu, 0x00000070u, 0x00000071u, 0x00000072u,  // 0001D5C8
        0x00000073u, 0x00000074u, 0x00000075u, 0x00000076u,  // 0001D5CC
        0x00000077u, 0x00000078u, 0x00000079u, 0x0000007Au,  // 0001D5D0
        0x00000041u, 0x00000042u, 0x00000043u, 0x00000044u,  // 0001D5D4
        0x00000045u, 0x00000046u, 0x00000047u, 0x00000048u,  // 0001D5D8
        0x00000049u, 0x0000004Au, 0x0000004Bu, 0x0000004Cu,  // 0001D5DC
        0x0000004Du, 0x0000004Eu, 0x0000004Fu, 0x00000050u,  // 0001D5E0
        0x00000051u, 0x00000052u, 0x00000053u, 0x00000054u,  // 0001D5E4
        0x00000055u, 0x00000056u, 0x00000057u, 0x00000058u,  // 0001D5E8
        0x00000059u, 0x0000005Au, 0x00000061u, 0x00000062u,  // 0001D5EC
        0x00000063u, 0x00000064u, 0x00000065u, 0x00000066u,  // 0001D5F0
        0x00000067u, 0x00000068u, 0x00000069u, 0x0000006Au,  // 0001D5F4
        0x0000006Bu, 0x0000006Cu, 0x0000006Du, 0x0000006Eu,  // 0001D5F8
        0x0000006Fu, 0x00000070u, 0x00000071u, 0x00000072u,  // 0001D5FC
        0x00000073u, 0x00000074u, 0x00000075u, 0x00000076u,  // 0001D600
        0x00000077u, 0x00000078u, 0x00000079u, 0x0000007Au,  // 0001D604
        0x00000041u, 0x00000042u, 0x00000043u, 0x00000044u,  // 0001D608
        0x00000045u, 0x00000046u, 0x00000047u, 0x00000048u,  // 0001D60C
        0x00000049u, 0x0000004Au, 0x0000004Bu, 0x0000004Cu,  // 0001D610
        0x0000004Du, 0x0000004Eu, 0x0000004Fu, 0x00000050u,  // 0001D614
        0x00000051u, 0x00000052u, 0x00000053u, 0x00000054u,  // 0001D618
        0x00000055u, 0x00000056u, 0x00000057u, 0x00000058u,  // 0001D61C
        0x00000059u, 0x0000005Au, 0x00000061u, 0x00000062u,  // 0001D620
        0x00000063u, 0x00000064u, 0x00000065u, 0x00000066u,  // 0001D624
        0x00000067u, 0x00000068u, 0x00000069u, 0x0000006Au,  // 0001D628
        0x0000006Bu, 0x0000006Cu, 0x0000006Du, 0x0000006Eu,  // 0001D62C
        0x0000006Fu, 0x00000070u, 0x00000071u, 0x00000072u,  // 0001D630
        0x00000073u, 0x00000074u, 0x00000075u, 0x00000076u,  // 0001D634
        0x00000077u, 0x00000078u, 0x00000079u, 0x0000007Au,  // 0001D638
        0x00000041u, 0x00000042u, 0x00000043u, 0x00000044u,  // 0001D63C
        0x00000045u, 0x00000046u, 0x00000047u, 0x00000048u,  // 0001D640
        0x00000049u, 0x0000004Au, 0x0000004Bu, 0x0000004Cu,  // 0001D644
        0x0000004Du, 0x0000004Eu, 0x0000004Fu, 0x00000050u,  // 0001D648
        0x00000051u, 0x00000052u, 0x00000053u, 0x00000054u,  // 0001D64C
        0x00000055u, 0x00000056u, 0x00000057u, 0x00000058u,  // 0001D650
        0x00000059u, 0x0000005Au, 0x00000061u, 0x00000062u,  // 0001D654
        0x00000063u, 0x00000064u, 0x00000065u, 0x00000066u,  // 0001D658
        0x00000067u, 0x00000068u, 0x00000069u, 0x0000006Au,  // 0001D65C
        0x0000006Bu, 0x0000006Cu, 0x0000006Du, 0x0000006Eu,  // 0001D660
        0x0000006Fu, 0x00000070u, 0x00000071u, 0x00000072u,  // 0001D664
        0x00000073u, 0x00000074u, 0x00000075u, 0x00000076u,  // 0001D668
        0x00000077u, 0x00000078u, 0x00000079u, 0x0000007Au,  // 0001D66C
        0x00000041u, 0x00000042u, 0x00000043u, 0x00000044u,  // 0001D670
        0x00000045u, 0x00000046u, 0x00000047u, 0x00000048u,  // 0001D674
        0x00000049u, 0x0000004Au, 0x0000004Bu, 0x0000004Cu,  // 0001D678
        0x0000004Du, 0x0000004Eu, 0x0000004Fu, 0x00000050u,  // 0001D67C
        0x00000051u, 0x00000052u, 0x00000053u, 0x00000054u,  // 0001D680
        0x00000055u, 0x00000056u, 0x00000057u, 0x00000058u,  // 0001D684
        0x00000059u, 0x0000005Au, 0x00000061u, 0x00000062u,  // 0001D688
        0x00000063u, 0x00000064u, 0x00000065u, 0x00000066u,  // 0001D68C
        0x00000067u, 0x00000068u, 0x00000069u, 0x0000006Au,  // 0001D690
        0x0000006Bu, 0x0000006Cu, 0x0000006Du, 0x0000006Eu,  // 0001D694
        0x0000006Fu, 0x00000070u, 0x00000071u, 0x00000072u,  // 0001D698
        0x00000073u, 0x00000074u, 0x00000075u, 0x00000076u,  // 0001D69C
        0x00000077u, 0x00000078u, 0x00000079u, 0x0000007Au,  // 0001D6A0
        0x0001D6A4u, 0x0001D6A5u, 0x0001D6A6u, 0x0001D6A7u,  // 0001D6A4
        0x00000391u, 0x00000392u, 0x00000393u, 0x00000394u,  // 0001D6A8
        0x00000395u, 0x00000396u, 0x00000397u, 0x00000398u,  // 0001D6AC
        0x00000399u, 0x0000039Au, 0x0000039Bu, 0x0000039Cu,  // 0001D6B0
        0x0000039Du, 0x0000039Eu, 0x0000039Fu, 0x000003A0u,  // 0001D6B4
        0x000003A1u, 0x000003F4u, 0x000003A3u, 0x000003A4u,  // 0001D6B8
        0x000003A5u, 0x000003A6u, 0x000003A7u, 0x000003A8u,  // 0001D6BC
        0x000003A9u, 0x00002207u, 0x000003B1u, 0x000003B2u,  // 0001D6C0
        0x000003B3u, 0x000003B4u, 0x000003B5u, 0x000003B6u,  // 0001D6C4
        0x000003B7u, 0x000003B8u, 0x000003B9u, 0x000003BAu,  // 0001D6C8
        0x000003BBu, 0x000003BCu, 0x000003BDu, 0x000003BEu,  // 0001D6CC
        0x000003BFu, 0x000003C0u, 0x000003C1u, 0x000003C2u,  // 0001D6D0
        0x000003C3u, 0x000003C4u, 0x000003C5u, 0x000003C6u,  // 0001D6D4
        0x000003C7u, 0x000003C8u, 0x000003C9u, 0x00002202u,  // 0001D6D8
        0x000003F5u, 0x000003D1u, 0x000003F0u, 0x000003D5u,  // 0001D6DC
        0x000003F1u, 0x000003D6u, 0x00000391u, 0x00000392u,  // 0001D6E0
        0x00000393u, 0x00000394u, 0x00000395u, 0x00000396u,  // 0001D6E4
        0x00000397u, 0x00000398u, 0x00000399u, 0x0000039Au,  // 0001D6E8
        0x0000039Bu, 0x0000039Cu, 0x0000039Du, 0x0000039Eu,  // 0001D6EC
        0x0000039Fu, 0x000003A0u, 0x000003A1u, 0x000003F4u,  // 0001D6F0
        0x000003A3u, 0x000003A4u, 0x000003A5u, 0x000003A6u,  // 0001D6F4
        0x000003A7u, 0x000003A8u, 0x000003A9u, 0x00002207u,  // 0001D6F8
        0x000003B1u, 0x000003B2u, 0x000003B3u, 0x000003B4u,  // 0001D6FC
        0x000003B5u, 0x000003B6u, 0x000003B7u, 0x000003B8u,  // 0001D700
        0x000003B9u, 0x000003BAu, 0x000003BBu, 0x000003BCu,  // 0001D704
        0x000003BDu, 0x000003BEu, 0x000003BFu, 0x000003C0u,  // 0001D708
        0x000003C1u, 0x000003C2u, 0x000003C3u, 0x000003C4u,  // 0001D70C
        0x000003C5u, 0x000003C6u, 0x000003C7u, 0x000003C8u,  // 0001D710
        0x000003C9u, 0x00002202u, 0x000003F5u, 0x000003D1u,  // 0001D714
        0x000003F0u, 0x000003D5u, 0x000003F1u, 0x000003D6u,  // 0001D718
        0x00000391u, 0x00000392u, 0x00000393u, 0x00000394u,  // 0001D71C
        0x00000395u, 0x00000396u, 0x00000397u, 0x00000398u,  // 0001D720
        0x00000399u, 0x0000039Au, 0x0000039Bu, 0x0000039Cu,  // 0001D724
        0x0000039Du, 0x0000039Eu, 0x0000039Fu, 0x000003A0u,  // 0001D728
        0x000003A1u, 0x000003F4u, 0x000003A3u, 0x000003A4u,  // 0001D72C
        0x000003A5u, 0x000003A6u, 0x000003A7u, 0x000003A8u,  // 0001D730
        0x000003A9u, 0x00002207u, 0x000003B1u, 0x000003B2u,  // 0001D734
        0x000003B3u, 0x000003B4u, 0x000003B5u, 0x000003B6u,  // 0001D738
        0x000003B7u, 0x000003B8u, 0x000003B9u, 0x000003BAu,  // 0001D73C
        0x000003BBu, 0x000003BCu, 0x000003BDu, 0x000003BEu,  // 0001D740
        0x000003BFu, 0x000003C0u, 0x000003C1u, 0x000003C2u,  // 0001D744
        0x000003C3u, 0x000003C4u, 0x000003C5u, 0x000003C6u,  // 0001D748
        0x000003C7u, 0x000003C8u, 0x000003C9u, 0x00002202u,  // 0001D74C
        0x000003F5u, 0x000003D1u, 0x000003F0u, 0x000003D5u,  // 0001D750
        0x000003F1u, 0x000003D6u, 0x00000391u, 0x00000392u,  // 0001D754
        0x00000393u, 0x00000394u, 0x00000395u, 0x00000396u,  // 0001D758
        0x00000397u, 0x00000398u, 0x00000399u, 0x0000039Au,  // 0001D75C
        0x0000039Bu, 0x0000039Cu, 0x0000039Du, 0x0000039Eu,  // 0001D760
        0x0000039Fu, 0x000003A0u, 0x000003A1u, 0x000003F4u,  // 0001D764
        0x000003A3u, 0x000003A4u, 0x000003A5u, 0x000003A6u,  // 0001D768
        0x000003A7u, 0x000003A8u, 0x000003A9u, 0x00002207u,  // 0001D76C
        0x000003B1u, 0x000003B2u, 0x000003B3u, 0x000003B4u,  // 0001D770
        0x000003B5u, 0x000003B6u, 0x000003B7u, 0x000003B8u,  // 0001D774
        0x000003B9u, 0x000003BAu, 0x000003BBu, 0x000003BCu,  // 0001D778
        0x000003BDu, 0x000003BEu, 0x000003BFu, 0x000003C0u,  // 0001D77C
        0x000003C1u, 0x000003C2u, 0x000003C3u, 0x000003C4u,  // 0001D780
        0x000003C5u, 0x000003C6u, 0x000003C7u, 0x000003C8u,  // 0001D784
        0x000003C9u, 0x00002202u, 0x000003F5u, 0x000003D1u,  // 0001D788
        0x000003F0u, 0x000003D5u, 0x000003F1u, 0x000003D6u,  // 0001D78C
        0x00000391u, 0x00000392u, 0x00000393u, 0x00000394u,  // 0001D790
        0x00000395u, 0x00000396u, 0x00000397u, 0x00000398u,  // 0001D794
        0x00000399u, 0x0000039Au, 0x0000039Bu, 0x0000039Cu,  // 0001D798
        0x0000039Du, 0x0000039Eu, 0x0000039Fu, 0x000003A0u,  // 0001D79C
        0x000003A1u, 0x000003F4u, 0x000003A3u, 0x000003A4u,  // 0001D7A0
        0x000003A5u, 0x000003A6u, 0x000003A7u, 0x000003A8u,  // 0001D7A4
        0x000003A9u, 0x00002207u, 0x000003B1u, 0x000003B2u,  // 0001D7A8
        0x000003B3u, 0x000003B4u, 0x000003B5u, 0x000003B6u,  // 0001D7AC
        0x000003B7u, 0x000003B8u, 0x000003B9u, 0x000003BAu,  // 0001D7B0
        0x000003BBu, 0x000003BCu, 0x000003BDu, 0x000003BEu,  // 0001D7B4
        0x000003BFu, 0x000003C0u, 0x000003C1u, 0x000003C2u,  // 0001D7B8
        0x000003C3u, 0x000003C4u, 0x000003C5u, 0x000003C6u,  // 0001D7BC
        0x000003C7u, 0x000003C8u, 0x000003C9u, 0x00002202u,  // 0001D7C0
        0x000003F5u, 0x000003D1u, 0x000003F0u, 0x000003D5u,  // 0001D7C4
        0x000003F1u, 0x000003D6u, 0x0001D7CAu, 0x0001D7CBu,  // 0001D7C8
        0x0001D7CCu, 0x0001D7CDu, 0x00000030u, 0x00000031u,  // 0001D7CC
        0x00000032u, 0x00000033u, 0x00000034u, 0x00000035u,  // 0001D7D0
        0x00000036u, 0x00000037u, 0x00000038u, 0x00000039u,  // 0001D7D4
        0x00000030u, 0x00000031u, 0x00000032u, 0x00000033u,  // 0001D7D8
        0x00000034u, 0x00000035u, 0x00000036u, 0x00000037u,  // 0001D7DC
        0x00000038u, 0x00000039u, 0x00000030u, 0x00000031u,  // 0001D7E0
        0x00000032u, 0x00000033u, 0x00000034u, 0x00000035u,  // 0001D7E4
        0x00000036u, 0x00000037u, 0x00000038u, 0x00000039u,  // 0001D7E8
        0x00000030u, 0x00000031u, 0x00000032u, 0x00000033u,  // 0001D7EC
        0x00000034u, 0x00000035u, 0x00000036u, 0x00000037u,  // 0001D7F0
        0x00000038u, 0x00000039u, 0x00000030u, 0x00000031u,  // 0001D7F4
        0x00000032u, 0x00000033u, 0x00000034u, 0x00000035u,  // 0001D7F8
        0x00000036u, 0x00000037u, 0x00000038u, 0x00000039u
    };

    const unsigned char Mathematical_Alphanumeric_Symbols1D400::my_lb[] =
    {
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_NU, LB_NU, 
        LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, 
        LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, 
        LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, 
        LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, 
        LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, 
        LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU
    };

    const std::bitset<1024> Mathematical_Alphanumeric_Symbols1D400::my_Other_Math(std::string("1111111111111111111111111111111111111111111111111100001111110111111111111111111111111101111111111111111111111111111111011111111111111111111111110111111111111111111111111111111101111111111111111111111111011111111111111111111111111111110111111111111111111111111101111111111111111111111111111111011111111111111111111111110111111111111111111111111100001111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111101111111000101111101111011111111111111111111111111110111111101111111100111101111111111111111111111111111111111111111111111111111111111111111101111111010111111111111011110011001001101111111111111111111111111111111111111111111111111111111111111111111111101111111111111111111111111111111111111111111111111111111111111111111111111111111111111"));

  }; // namespace
}; // namespace

dload(Babylon::Module::Mathematical_Alphanumeric_Symbols1D400);
