/*$Id: UnicodePluginGenerator.pl,v 1.11 2004/01/28 12:39:04 tobias Exp 900-97F.cc
 *
 * This source file is a part of the Fresco Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Wed, 28 Jan 2004 20:49:04 +0100.
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
    class Devanagari900 : public Babylon::Block
    {
      public:
        void clean() { };

        Devanagari900() :
        my_first_letter(0x900),
        my_last_letter(0x97F)
        // my_version="4.0" // Not yet supported!
        {
            {
                my_composeMap[std::make_pair(0x00000915, 0x0000093C)] = 0x0958;
                my_composeMap[std::make_pair(0x00000916, 0x0000093C)] = 0x0959;
                my_composeMap[std::make_pair(0x00000917, 0x0000093C)] = 0x095A;
                my_composeMap[std::make_pair(0x0000091C, 0x0000093C)] = 0x095B;
                my_composeMap[std::make_pair(0x00000921, 0x0000093C)] = 0x095C;
                my_composeMap[std::make_pair(0x00000922, 0x0000093C)] = 0x095D;
                my_composeMap[std::make_pair(0x00000928, 0x0000093C)] = 0x0929;
                my_composeMap[std::make_pair(0x0000092B, 0x0000093C)] = 0x095E;
                my_composeMap[std::make_pair(0x0000092F, 0x0000093C)] = 0x095F;
                my_composeMap[std::make_pair(0x00000930, 0x0000093C)] = 0x0931;
                my_composeMap[std::make_pair(0x00000933, 0x0000093C)] = 0x0934;
            }
        }

        ~Devanagari900() { }

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
        return "Devanagari";
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
            case 0x0966u:
                return 0;
            case 0x0967u:
                return 1;
            case 0x0968u:
                return 2;
            case 0x0969u:
                return 3;
            case 0x096Au:
                return 4;
            case 0x096Bu:
                return 5;
            case 0x096Cu:
                return 6;
            case 0x096Du:
                return 7;
            case 0x096Eu:
                return 8;
            case 0x096Fu:
                return 9;
            default:
                return 0;
            }
        }

        bool is_Decimal_Digit(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x0966u:
            case 0x0967u:
            case 0x0968u:
            case 0x0969u:
            case 0x096Au:
            case 0x096Bu:
            case 0x096Cu:
            case 0x096Du:
            case 0x096Eu:
            case 0x096Fu:
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
            case 0x0966u:
                return 0;
            case 0x0967u:
                return 1;
            case 0x0968u:
                return 2;
            case 0x0969u:
                return 3;
            case 0x096Au:
                return 4;
            case 0x096Bu:
                return 5;
            case 0x096Cu:
                return 6;
            case 0x096Du:
                return 7;
            case 0x096Eu:
                return 8;
            case 0x096Fu:
                return 9;
            default:
                return 0;
            }
        }

        bool is_Digit(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x0966u:
            case 0x0967u:
            case 0x0968u:
            case 0x0969u:
            case 0x096Au:
            case 0x096Bu:
            case 0x096Cu:
            case 0x096Du:
            case 0x096Eu:
            case 0x096Fu:
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
            case 0x0966u:
                return 0.000000;
            case 0x0967u:
                return 1.000000;
            case 0x0968u:
                return 2.000000;
            case 0x0969u:
                return 3.000000;
            case 0x096Au:
                return 4.000000;
            case 0x096Bu:
                return 5.000000;
            case 0x096Cu:
                return 6.000000;
            case 0x096Du:
                return 7.000000;
            case 0x096Eu:
                return 8.000000;
            case 0x096Fu:
                return 9.000000;
            default:
                return 0;
            }
        }

        bool is_Numeric(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x0966u:
            case 0x0967u:
            case 0x0968u:
            case 0x0969u:
            case 0x096Au:
            case 0x096Bu:
            case 0x096Cu:
            case 0x096Du:
            case 0x096Eu:
            case 0x096Fu:
                return 1;
            default:
                return 0;
            }
        }

        Gen_Cat category(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CAT_MAX;
            return Babylon::Gen_Cat(Devanagari900::my_cat[uc - my_first_letter]);
        }

        Can_Comb_Class comb_class(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CC_MAX;
            return Can_Comb_Class(Devanagari900::my_comb_cl[uc - my_first_letter]);
        }

        Bidir_Props bidir_props(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return BIDIR_INVALID;
            return Devanagari900::my_bidir[uc - my_first_letter];
        }

        Char_Decomp decomp_type(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return DECOMP_MAX;
            return Babylon::Char_Decomp(DECOMP_CANONICAL);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            Babylon::UTF32_string us;
            us.resize(2);
            us[0] = Devanagari900::my_decompStr[uc - my_first_letter][0];
            us[1] = Devanagari900::my_decompStr[uc - my_first_letter][1];
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
            return Babylon::Line_Break(Devanagari900::my_lb[uc - my_first_letter]);
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
            if (my_comp_exclude.test(uc - my_first_letter)) return 1;
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
            return my_Terminal_Punctuation.test(uc - my_first_letter);
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
            return my_Other_Alphabetic.test(uc - my_first_letter);
        }

        bool is_Ideographic(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Diacritic(const UCS4 uc) const
        {
            return my_Diacritic.test(uc - my_first_letter);
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
            return my_Grapheme_Link.test(uc - my_first_letter);
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
        Devanagari900(const Devanagari900 &) ; // no implementaion!

    // members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const std::bitset<128> my_is_defined;
        static const unsigned char my_cat[128];
        static const unsigned char my_comb_cl[128];
        static const Babylon::Bidir_Props my_bidir[128];
        static const UCS2 my_decompStr[128][2];
        static const unsigned char my_lb[128];
        std::map<std::pair<UCS4, UCS4>, UCS4> my_composeMap;
        static const std::bitset<128> my_comp_exclude;
        static const std::bitset<128> my_Terminal_Punctuation;
        static const std::bitset<128> my_Other_Alphabetic;
        static const std::bitset<128> my_Diacritic;
        static const std::bitset<128> my_Grapheme_Link;
    }; // class Devanagari900

    const std::bitset<128> Devanagari900::my_is_defined(std::string("00000000000000011111111111111111111111110001111100111111111111111111001111111111111111111111111111111111111111111111111111111110"));

    const unsigned char Devanagari900::my_cat[] =
    {
        CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mc, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Lo, CAT_Mc, CAT_Mc, 
        CAT_Mc, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, 
        CAT_Mn, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mn, CAT_Mn, CAT_Mn, 
        CAT_Lo, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Mn, CAT_Mn, CAT_Po, CAT_Po, CAT_Nd, CAT_Nd, 
        CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, 
        CAT_Po, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, 
        CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mn
    };

    const unsigned char Devanagari900::my_comb_cl[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 7, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 9, 0, 0, 
        0, 230, 220, 230, 230, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const Babylon::Bidir_Props Devanagari900::my_bidir[] =
    {
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, 
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
        BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, 
        BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM
    };

    const UCS2 Devanagari900::my_decompStr[][2] =
    {
        { 0x00000900u, 0x00000000u }, { 0x00000901u, 0x00000000u },  // 00000900
        { 0x00000902u, 0x00000000u }, { 0x00000903u, 0x00000000u },  // 00000902
        { 0x00000904u, 0x00000000u }, { 0x00000905u, 0x00000000u },  // 00000904
        { 0x00000906u, 0x00000000u }, { 0x00000907u, 0x00000000u },  // 00000906
        { 0x00000908u, 0x00000000u }, { 0x00000909u, 0x00000000u },  // 00000908
        { 0x0000090Au, 0x00000000u }, { 0x0000090Bu, 0x00000000u },  // 0000090A
        { 0x0000090Cu, 0x00000000u }, { 0x0000090Du, 0x00000000u },  // 0000090C
        { 0x0000090Eu, 0x00000000u }, { 0x0000090Fu, 0x00000000u },  // 0000090E
        { 0x00000910u, 0x00000000u }, { 0x00000911u, 0x00000000u },  // 00000910
        { 0x00000912u, 0x00000000u }, { 0x00000913u, 0x00000000u },  // 00000912
        { 0x00000914u, 0x00000000u }, { 0x00000915u, 0x00000000u },  // 00000914
        { 0x00000916u, 0x00000000u }, { 0x00000917u, 0x00000000u },  // 00000916
        { 0x00000918u, 0x00000000u }, { 0x00000919u, 0x00000000u },  // 00000918
        { 0x0000091Au, 0x00000000u }, { 0x0000091Bu, 0x00000000u },  // 0000091A
        { 0x0000091Cu, 0x00000000u }, { 0x0000091Du, 0x00000000u },  // 0000091C
        { 0x0000091Eu, 0x00000000u }, { 0x0000091Fu, 0x00000000u },  // 0000091E
        { 0x00000920u, 0x00000000u }, { 0x00000921u, 0x00000000u },  // 00000920
        { 0x00000922u, 0x00000000u }, { 0x00000923u, 0x00000000u },  // 00000922
        { 0x00000924u, 0x00000000u }, { 0x00000925u, 0x00000000u },  // 00000924
        { 0x00000926u, 0x00000000u }, { 0x00000927u, 0x00000000u },  // 00000926
        { 0x00000928u, 0x00000000u }, { 0x00000928u, 0x0000093Cu },  // 00000928
        { 0x0000092Au, 0x00000000u }, { 0x0000092Bu, 0x00000000u },  // 0000092A
        { 0x0000092Cu, 0x00000000u }, { 0x0000092Du, 0x00000000u },  // 0000092C
        { 0x0000092Eu, 0x00000000u }, { 0x0000092Fu, 0x00000000u },  // 0000092E
        { 0x00000930u, 0x00000000u }, { 0x00000930u, 0x0000093Cu },  // 00000930
        { 0x00000932u, 0x00000000u }, { 0x00000933u, 0x00000000u },  // 00000932
        { 0x00000933u, 0x0000093Cu }, { 0x00000935u, 0x00000000u },  // 00000934
        { 0x00000936u, 0x00000000u }, { 0x00000937u, 0x00000000u },  // 00000936
        { 0x00000938u, 0x00000000u }, { 0x00000939u, 0x00000000u },  // 00000938
        { 0x0000093Au, 0x00000000u }, { 0x0000093Bu, 0x00000000u },  // 0000093A
        { 0x0000093Cu, 0x00000000u }, { 0x0000093Du, 0x00000000u },  // 0000093C
        { 0x0000093Eu, 0x00000000u }, { 0x0000093Fu, 0x00000000u },  // 0000093E
        { 0x00000940u, 0x00000000u }, { 0x00000941u, 0x00000000u },  // 00000940
        { 0x00000942u, 0x00000000u }, { 0x00000943u, 0x00000000u },  // 00000942
        { 0x00000944u, 0x00000000u }, { 0x00000945u, 0x00000000u },  // 00000944
        { 0x00000946u, 0x00000000u }, { 0x00000947u, 0x00000000u },  // 00000946
        { 0x00000948u, 0x00000000u }, { 0x00000949u, 0x00000000u },  // 00000948
        { 0x0000094Au, 0x00000000u }, { 0x0000094Bu, 0x00000000u },  // 0000094A
        { 0x0000094Cu, 0x00000000u }, { 0x0000094Du, 0x00000000u },  // 0000094C
        { 0x0000094Eu, 0x00000000u }, { 0x0000094Fu, 0x00000000u },  // 0000094E
        { 0x00000950u, 0x00000000u }, { 0x00000951u, 0x00000000u },  // 00000950
        { 0x00000952u, 0x00000000u }, { 0x00000953u, 0x00000000u },  // 00000952
        { 0x00000954u, 0x00000000u }, { 0x00000955u, 0x00000000u },  // 00000954
        { 0x00000956u, 0x00000000u }, { 0x00000957u, 0x00000000u },  // 00000956
        { 0x00000915u, 0x0000093Cu }, { 0x00000916u, 0x0000093Cu },  // 00000958
        { 0x00000917u, 0x0000093Cu }, { 0x0000091Cu, 0x0000093Cu },  // 0000095A
        { 0x00000921u, 0x0000093Cu }, { 0x00000922u, 0x0000093Cu },  // 0000095C
        { 0x0000092Bu, 0x0000093Cu }, { 0x0000092Fu, 0x0000093Cu },  // 0000095E
        { 0x00000960u, 0x00000000u }, { 0x00000961u, 0x00000000u },  // 00000960
        { 0x00000962u, 0x00000000u }, { 0x00000963u, 0x00000000u },  // 00000962
        { 0x00000964u, 0x00000000u }, { 0x00000965u, 0x00000000u },  // 00000964
        { 0x00000966u, 0x00000000u }, { 0x00000967u, 0x00000000u },  // 00000966
        { 0x00000968u, 0x00000000u }, { 0x00000969u, 0x00000000u },  // 00000968
        { 0x0000096Au, 0x00000000u }, { 0x0000096Bu, 0x00000000u },  // 0000096A
        { 0x0000096Cu, 0x00000000u }, { 0x0000096Du, 0x00000000u },  // 0000096C
        { 0x0000096Eu, 0x00000000u }, { 0x0000096Fu, 0x00000000u },  // 0000096E
        { 0x00000970u, 0x00000000u }, { 0x00000971u, 0x00000000u },  // 00000970
        { 0x00000972u, 0x00000000u }, { 0x00000973u, 0x00000000u },  // 00000972
        { 0x00000974u, 0x00000000u }, { 0x00000975u, 0x00000000u },  // 00000974
        { 0x00000976u, 0x00000000u }, { 0x00000977u, 0x00000000u },  // 00000976
        { 0x00000978u, 0x00000000u }, { 0x00000979u, 0x00000000u },  // 00000978
        { 0x0000097Au, 0x00000000u }, { 0x0000097Bu, 0x00000000u },  // 0000097A
        { 0x0000097Cu, 0x00000000u }, { 0x0000097Du, 0x00000000u },  // 0000097C
        { 0x0000097Eu, 0x00000000u }, { 0x0000097Fu, 0x00000000u }
    };

    const unsigned char Devanagari900::my_lb[] =
    {
        LB_CM, LB_CM, LB_CM, LB_CM, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, LB_AL, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_AL, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_CM, LB_CM, LB_AL, LB_AL, LB_NU, LB_NU, 
        LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, 
        LB_AL, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM
    };

    const std::bitset<128> Devanagari900::my_comp_exclude(std::string("00000000000000000000000000000000111111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<128> Devanagari900::my_Terminal_Punctuation(std::string("00000000000000000000000000110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<128> Devanagari900::my_Other_Alphabetic(std::string("00000000000000000000000000001100000000000000000000011111111111111100000000000000000000000000000000000000000000000000000000001110"));

    const std::bitset<128> Devanagari900::my_Diacritic(std::string("00000000000000000000000000000000000000000001111000100000000000000001000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<128> Devanagari900::my_Grapheme_Link(std::string("00000000000000000000000000000000000000000000000000100000000000000000000000000000000000000000000000000000000000000000000000000000"));

  }; // namespace
}; // namespace

dload(Babylon::Module::Devanagari900);
