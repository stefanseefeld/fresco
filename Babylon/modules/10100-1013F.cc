/*$Id: UnicodePluginGenerator.pl,v 1.7 2003/08/01 16:47:16 tobias Exp 10100-1013F.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 05 Aug 2003 17:10:27 +0200.
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
    class Aegean_Numbers10100 : public Babylon::Block
    {
      public:
        void clean() { };

        Aegean_Numbers10100() :
        my_first_letter(0x10100),
        my_last_letter(0x1013F)
        // my_version="4.0" // Not yet supported!
        {
        }

        ~Aegean_Numbers10100() { }

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
        return "Aegean Numbers";
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
            if (!is_defined(uc))
                return 0;
            switch(uc)
            {
            case 0x10107u:
                return 1.000000;
            case 0x10108u:
                return 2.000000;
            case 0x10109u:
                return 3.000000;
            case 0x1010Au:
                return 4.000000;
            case 0x1010Bu:
                return 5.000000;
            case 0x1010Cu:
                return 6.000000;
            case 0x1010Du:
                return 7.000000;
            case 0x1010Eu:
                return 8.000000;
            case 0x1010Fu:
                return 9.000000;
            case 0x10110u:
                return 10.000000;
            case 0x10111u:
                return 20.000000;
            case 0x10112u:
                return 30.000000;
            case 0x10113u:
                return 40.000000;
            case 0x10114u:
                return 50.000000;
            case 0x10115u:
                return 60.000000;
            case 0x10116u:
                return 70.000000;
            case 0x10117u:
                return 80.000000;
            case 0x10118u:
                return 90.000000;
            case 0x10119u:
                return 100.000000;
            case 0x1011Au:
                return 200.000000;
            case 0x1011Bu:
                return 300.000000;
            case 0x1011Cu:
                return 400.000000;
            case 0x1011Du:
                return 500.000000;
            case 0x1011Eu:
                return 600.000000;
            case 0x1011Fu:
                return 700.000000;
            case 0x10120u:
                return 800.000000;
            case 0x10121u:
                return 900.000000;
            case 0x10122u:
                return 1000.000000;
            case 0x10123u:
                return 2000.000000;
            case 0x10124u:
                return 3000.000000;
            case 0x10125u:
                return 4000.000000;
            case 0x10126u:
                return 5000.000000;
            case 0x10127u:
                return 6000.000000;
            case 0x10128u:
                return 7000.000000;
            case 0x10129u:
                return 8000.000000;
            case 0x1012Au:
                return 9000.000000;
            case 0x1012Bu:
                return 10000.000000;
            case 0x1012Cu:
                return 20000.000000;
            case 0x1012Du:
                return 30000.000000;
            case 0x1012Eu:
                return 40000.000000;
            case 0x1012Fu:
                return 50000.000000;
            case 0x10130u:
                return 60000.000000;
            case 0x10131u:
                return 70000.000000;
            case 0x10132u:
                return 80000.000000;
            case 0x10133u:
                return 90000.000000;
            default:
                return 0;
            }
        }

        bool is_Numeric(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x10107u:
            case 0x10108u:
            case 0x10109u:
            case 0x1010Au:
            case 0x1010Bu:
            case 0x1010Cu:
            case 0x1010Du:
            case 0x1010Eu:
            case 0x1010Fu:
            case 0x10110u:
            case 0x10111u:
            case 0x10112u:
            case 0x10113u:
            case 0x10114u:
            case 0x10115u:
            case 0x10116u:
            case 0x10117u:
            case 0x10118u:
            case 0x10119u:
            case 0x1011Au:
            case 0x1011Bu:
            case 0x1011Cu:
            case 0x1011Du:
            case 0x1011Eu:
            case 0x1011Fu:
            case 0x10120u:
            case 0x10121u:
            case 0x10122u:
            case 0x10123u:
            case 0x10124u:
            case 0x10125u:
            case 0x10126u:
            case 0x10127u:
            case 0x10128u:
            case 0x10129u:
            case 0x1012Au:
            case 0x1012Bu:
            case 0x1012Cu:
            case 0x1012Du:
            case 0x1012Eu:
            case 0x1012Fu:
            case 0x10130u:
            case 0x10131u:
            case 0x10132u:
            case 0x10133u:
                return 1;
            default:
                return 0;
            }
        }

        Gen_Cat category(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CAT_MAX;
            return Babylon::Gen_Cat(Aegean_Numbers10100::my_cat[uc - my_first_letter]);
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
            return Aegean_Numbers10100::my_bidir[uc - my_first_letter];
        }

        Char_Decomp decomp_type(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return DECOMP_MAX;
            return Babylon::Char_Decomp(DECOMP_CANONICAL);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            UTF32_string us;
            us.resize(1); us[0] = uc;
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
            return Babylon::Line_Break(Aegean_Numbers10100::my_lb[uc - my_first_letter]);
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
        Aegean_Numbers10100(const Aegean_Numbers10100 &) ; // no implementaion!

    // members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const std::bitset<64> my_is_defined;
        static const unsigned char my_cat[64];
        static const Babylon::Bidir_Props my_bidir[64];
        static const unsigned char my_lb[64];
    }; // class Aegean_Numbers10100

    const std::bitset<64> Aegean_Numbers10100::my_is_defined(std::string("1111111110001111111111111111111111111111111111111111111110000111"));

    const unsigned char Aegean_Numbers10100::my_cat[] =
    {
        CAT_Po, CAT_Po, CAT_So, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_No, 
        CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
        CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
        CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
        CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
        CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
        CAT_No, CAT_No, CAT_No, CAT_No, CAT_Po, CAT_Po, CAT_Po, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So
    };

    const Babylon::Bidir_Props Aegean_Numbers10100::my_bidir[] =
    {
        BIDIR_L, BIDIR_ON, BIDIR_L, BIDIR_L, 
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
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L
    };

    const unsigned char Aegean_Numbers10100::my_lb[] =
    {
        LB_BA, LB_BA, LB_BA, LB_BA, LB_BA, LB_BA, LB_BA, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_BA, LB_BA, LB_BA, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL
    };

  }; // namespace
}; // namespace

dload(Babylon::Module::Aegean_Numbers10100);
