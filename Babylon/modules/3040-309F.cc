/*$Id: UnicodePluginGenerator.pl,v 1.6 2002/05/31 23:42:14 tobias Exp 3040-309F.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Mon, 26 May 2003 15:56:03 +0200.
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
    class Hiragana3040 : public Babylon::Block
    {
      public:
        void clean() { };

        Hiragana3040() :
	    my_first_letter(0x3040),
	    my_last_letter(0x309F)
	    // my_version="4.0" // Not yet supported!
        {
            {
                my_composeMap[std::make_pair(0x00003046, 0x00003099)] = 0x3094;
                my_composeMap[std::make_pair(0x0000304B, 0x00003099)] = 0x304C;
                my_composeMap[std::make_pair(0x0000304D, 0x00003099)] = 0x304E;
                my_composeMap[std::make_pair(0x0000304F, 0x00003099)] = 0x3050;
                my_composeMap[std::make_pair(0x00003051, 0x00003099)] = 0x3052;
                my_composeMap[std::make_pair(0x00003053, 0x00003099)] = 0x3054;
                my_composeMap[std::make_pair(0x00003055, 0x00003099)] = 0x3056;
                my_composeMap[std::make_pair(0x00003057, 0x00003099)] = 0x3058;
                my_composeMap[std::make_pair(0x00003059, 0x00003099)] = 0x305A;
                my_composeMap[std::make_pair(0x0000305B, 0x00003099)] = 0x305C;
                my_composeMap[std::make_pair(0x0000305D, 0x00003099)] = 0x305E;
                my_composeMap[std::make_pair(0x0000305F, 0x00003099)] = 0x3060;
                my_composeMap[std::make_pair(0x00003061, 0x00003099)] = 0x3062;
                my_composeMap[std::make_pair(0x00003064, 0x00003099)] = 0x3065;
                my_composeMap[std::make_pair(0x00003066, 0x00003099)] = 0x3067;
                my_composeMap[std::make_pair(0x00003068, 0x00003099)] = 0x3069;
                my_composeMap[std::make_pair(0x0000306F, 0x00003099)] = 0x3070;
                my_composeMap[std::make_pair(0x0000306F, 0x0000309A)] = 0x3071;
                my_composeMap[std::make_pair(0x00003072, 0x00003099)] = 0x3073;
                my_composeMap[std::make_pair(0x00003072, 0x0000309A)] = 0x3074;
                my_composeMap[std::make_pair(0x00003075, 0x00003099)] = 0x3076;
                my_composeMap[std::make_pair(0x00003075, 0x0000309A)] = 0x3077;
                my_composeMap[std::make_pair(0x00003078, 0x00003099)] = 0x3079;
                my_composeMap[std::make_pair(0x00003078, 0x0000309A)] = 0x307A;
                my_composeMap[std::make_pair(0x0000307B, 0x00003099)] = 0x307C;
                my_composeMap[std::make_pair(0x0000307B, 0x0000309A)] = 0x307D;
                my_composeMap[std::make_pair(0x0000309D, 0x00003099)] = 0x309E;
            }
        }

        ~Hiragana3040() { }

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
	    return "Hiragana";
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
            return Babylon::Gen_Cat(Hiragana3040::my_cat[uc - my_first_letter]);
        }

        Can_Comb_Class comb_class(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CC_MAX;
            return Can_Comb_Class(Hiragana3040::my_comb_cl[uc - my_first_letter]);
        }

        Bidir_Props bidir_props(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return BIDIR_INVALID;
            return Hiragana3040::my_bidir[uc - my_first_letter];
        }

        Char_Decomp decomp_type(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return DECOMP_MAX;
            return Babylon::Char_Decomp(Hiragana3040::my_decomp[uc - my_first_letter]);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            Babylon::UTF32_string us;
            us.resize(2);
            us[0] = Hiragana3040::my_decompStr[uc - my_first_letter][0];
            us[1] = Hiragana3040::my_decompStr[uc - my_first_letter][1];
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
            return Babylon::Line_Break(Hiragana3040::my_lb[uc - my_first_letter]);
        }

        EA_Width EA_width(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return EA_WIDTH_MAX;
            return Babylon::EA_Width(EA_WIDTH_W);
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
            return my_Diacritic.test(uc - my_first_letter);
        }

        bool is_Extender(const UCS4 uc) const
        {
            return my_Extender.test(uc - my_first_letter);
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
            return my_Other_ID_Start.test(uc - my_first_letter);
        }

      private:
        // functions
        Hiragana3040(const Hiragana3040 &) ; // no implementaion!

	// members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const std::bitset<96> my_is_defined;
        static const unsigned char my_cat[96];
        static const unsigned char my_comb_cl[96];
        static const Babylon::Bidir_Props my_bidir[96];
        static const unsigned char my_decomp[96];
        static const UCS4 my_decompStr[96][2];
        static const unsigned char my_lb[96];
        std::map<std::pair<UCS4, UCS4>, UCS4> my_composeMap;
        static const std::bitset<96> my_Diacritic;
        static const std::bitset<96> my_Extender;
        static const std::bitset<96> my_Other_ID_Start;
    }; // class Hiragana3040

    const std::bitset<96> Hiragana3040::my_is_defined(std::string("111111100111111111111111111111111111111111111111111111111111111111111111111111111111111111111110"));

    const unsigned char Hiragana3040::my_cat[] =
    {
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Mn, CAT_Mn, CAT_Sk, CAT_Sk, CAT_Lm, CAT_Lm, CAT_Lo
    };

    const unsigned char Hiragana3040::my_comb_cl[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 8, 8, 0, 0, 0, 0, 0
    };

    const Babylon::Bidir_Props Hiragana3040::my_bidir[] =
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
        BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_ON, 
        BIDIR_ON, BIDIR_L, BIDIR_L, BIDIR_L
    };

    const unsigned char Hiragana3040::my_decomp[] = {
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
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_VERTICAL
    };

    const UCS4 Hiragana3040::my_decompStr[][2] =
    {
        { 0x00003040u, 0x00000000u }, { 0x00003041u, 0x00000000u },  // 00003040
        { 0x00003042u, 0x00000000u }, { 0x00003043u, 0x00000000u },  // 00003042
        { 0x00003044u, 0x00000000u }, { 0x00003045u, 0x00000000u },  // 00003044
        { 0x00003046u, 0x00000000u }, { 0x00003047u, 0x00000000u },  // 00003046
        { 0x00003048u, 0x00000000u }, { 0x00003049u, 0x00000000u },  // 00003048
        { 0x0000304Au, 0x00000000u }, { 0x0000304Bu, 0x00000000u },  // 0000304A
        { 0x0000304Bu, 0x00003099u }, { 0x0000304Du, 0x00000000u },  // 0000304C
        { 0x0000304Du, 0x00003099u }, { 0x0000304Fu, 0x00000000u },  // 0000304E
        { 0x0000304Fu, 0x00003099u }, { 0x00003051u, 0x00000000u },  // 00003050
        { 0x00003051u, 0x00003099u }, { 0x00003053u, 0x00000000u },  // 00003052
        { 0x00003053u, 0x00003099u }, { 0x00003055u, 0x00000000u },  // 00003054
        { 0x00003055u, 0x00003099u }, { 0x00003057u, 0x00000000u },  // 00003056
        { 0x00003057u, 0x00003099u }, { 0x00003059u, 0x00000000u },  // 00003058
        { 0x00003059u, 0x00003099u }, { 0x0000305Bu, 0x00000000u },  // 0000305A
        { 0x0000305Bu, 0x00003099u }, { 0x0000305Du, 0x00000000u },  // 0000305C
        { 0x0000305Du, 0x00003099u }, { 0x0000305Fu, 0x00000000u },  // 0000305E
        { 0x0000305Fu, 0x00003099u }, { 0x00003061u, 0x00000000u },  // 00003060
        { 0x00003061u, 0x00003099u }, { 0x00003063u, 0x00000000u },  // 00003062
        { 0x00003064u, 0x00000000u }, { 0x00003064u, 0x00003099u },  // 00003064
        { 0x00003066u, 0x00000000u }, { 0x00003066u, 0x00003099u },  // 00003066
        { 0x00003068u, 0x00000000u }, { 0x00003068u, 0x00003099u },  // 00003068
        { 0x0000306Au, 0x00000000u }, { 0x0000306Bu, 0x00000000u },  // 0000306A
        { 0x0000306Cu, 0x00000000u }, { 0x0000306Du, 0x00000000u },  // 0000306C
        { 0x0000306Eu, 0x00000000u }, { 0x0000306Fu, 0x00000000u },  // 0000306E
        { 0x0000306Fu, 0x00003099u }, { 0x0000306Fu, 0x0000309Au },  // 00003070
        { 0x00003072u, 0x00000000u }, { 0x00003072u, 0x00003099u },  // 00003072
        { 0x00003072u, 0x0000309Au }, { 0x00003075u, 0x00000000u },  // 00003074
        { 0x00003075u, 0x00003099u }, { 0x00003075u, 0x0000309Au },  // 00003076
        { 0x00003078u, 0x00000000u }, { 0x00003078u, 0x00003099u },  // 00003078
        { 0x00003078u, 0x0000309Au }, { 0x0000307Bu, 0x00000000u },  // 0000307A
        { 0x0000307Bu, 0x00003099u }, { 0x0000307Bu, 0x0000309Au },  // 0000307C
        { 0x0000307Eu, 0x00000000u }, { 0x0000307Fu, 0x00000000u },  // 0000307E
        { 0x00003080u, 0x00000000u }, { 0x00003081u, 0x00000000u },  // 00003080
        { 0x00003082u, 0x00000000u }, { 0x00003083u, 0x00000000u },  // 00003082
        { 0x00003084u, 0x00000000u }, { 0x00003085u, 0x00000000u },  // 00003084
        { 0x00003086u, 0x00000000u }, { 0x00003087u, 0x00000000u },  // 00003086
        { 0x00003088u, 0x00000000u }, { 0x00003089u, 0x00000000u },  // 00003088
        { 0x0000308Au, 0x00000000u }, { 0x0000308Bu, 0x00000000u },  // 0000308A
        { 0x0000308Cu, 0x00000000u }, { 0x0000308Du, 0x00000000u },  // 0000308C
        { 0x0000308Eu, 0x00000000u }, { 0x0000308Fu, 0x00000000u },  // 0000308E
        { 0x00003090u, 0x00000000u }, { 0x00003091u, 0x00000000u },  // 00003090
        { 0x00003092u, 0x00000000u }, { 0x00003093u, 0x00000000u },  // 00003092
        { 0x00003046u, 0x00003099u }, { 0x00003095u, 0x00000000u },  // 00003094
        { 0x00003096u, 0x00000000u }, { 0x00003097u, 0x00000000u },  // 00003096
        { 0x00003098u, 0x00000000u }, { 0x00003099u, 0x00000000u },  // 00003098
        { 0x0000309Au, 0x00000000u }, { 0x00000020u, 0x00003099u },  // 0000309A
        { 0x00000020u, 0x0000309Au }, { 0x0000309Du, 0x00000000u },  // 0000309C
        { 0x0000309Du, 0x00003099u }, { 0x00003088u, 0x0000308Au }
    };

    const unsigned char Hiragana3040::my_lb[] =
    {
        LB_NS, LB_NS, LB_ID, LB_NS, LB_ID, LB_NS, LB_ID, LB_NS, 
        LB_ID, LB_NS, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, 
        LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, 
        LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, 
        LB_ID, LB_ID, LB_ID, LB_NS, LB_ID, LB_ID, LB_ID, LB_ID, 
        LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, 
        LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, 
        LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, 
        LB_ID, LB_ID, LB_ID, LB_NS, LB_ID, LB_NS, LB_ID, LB_NS, 
        LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_NS, LB_ID, 
        LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_NS, LB_NS, LB_NS, 
        LB_NS, LB_CM, LB_CM, LB_NS, LB_NS, LB_NS, LB_NS, LB_ID
    };

    const std::bitset<96> Hiragana3040::my_Diacritic(std::string("000111100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<96> Hiragana3040::my_Extender(std::string("011000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<96> Hiragana3040::my_Other_ID_Start(std::string("000110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));

  }; // namespace
}; // namespace

dload(Babylon::Module::Hiragana3040);
