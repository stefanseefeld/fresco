/*$Id: UnicodePluginGenerator.pl,v 1.6 2002/05/31 23:42:14 tobias Exp 2000-206F.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Mon, 26 May 2003 15:56:00 +0200.
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
    class General_Punctuation2000 : public Babylon::Block
    {
      public:
        void clean() { };

        General_Punctuation2000() :
	    my_first_letter(0x2000),
	    my_last_letter(0x206F)
	    // my_version="4.0" // Not yet supported!
        {
        }

        ~General_Punctuation2000() { }

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
	    return "General Punctuation";
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
            return Babylon::Gen_Cat(General_Punctuation2000::my_cat[uc - my_first_letter]);
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
            return General_Punctuation2000::my_bidir[uc - my_first_letter];
        }

        Char_Decomp decomp_type(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return DECOMP_MAX;
            return Babylon::Char_Decomp(General_Punctuation2000::my_decomp[uc - my_first_letter]);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            Babylon::UTF32_string us;
            us.resize(2);
            us[0] = General_Punctuation2000::my_decompStr[uc - my_first_letter][0];
            us[1] = General_Punctuation2000::my_decompStr[uc - my_first_letter][1];

            switch (uc)
            {

            case 0x2026:
                us.resize(3);
                us[2u] = 0x002Eu;
                break;

            case 0x2034:
                us.resize(3);
                us[2u] = 0x2032u;
                break;

            case 0x2037:
                us.resize(3);
                us[2u] = 0x2035u;
                break;

            case 0x2057:
                us.resize(4);
                us[2u] = 0x2032u;
                us[3u] = 0x2032u;
                break;
            }
            if (0x0000u == us[1])
                us.resize(1);
            return us;
        }

        bool must_mirror(const UCS4 uc) const
        {
            return my_mirror.test(uc - my_first_letter);
        }

        Line_Break linebreak(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return LB_MAX;
            return Babylon::Line_Break(General_Punctuation2000::my_lb[uc - my_first_letter]);
        }

        EA_Width EA_width(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return EA_WIDTH_MAX;
            return Babylon::EA_Width(General_Punctuation2000::my_ea[uc - my_first_letter]);
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
            return my_White_Space.test(uc - my_first_letter);
        }

        bool is_Bidi_Control(const UCS4 uc) const
        {
            return my_Bidi_Control.test(uc - my_first_letter);
        }

        bool is_Join_Control(const UCS4 uc) const
        {
            return my_Join_Control.test(uc - my_first_letter);
        }

        bool is_Dash(const UCS4 uc) const
        {
            return my_Dash.test(uc - my_first_letter);
        }

        bool is_Hyphen(const UCS4 uc) const
        {
            return my_Hyphen.test(uc - my_first_letter);
        }

        bool is_Quotation_Mark(const UCS4 uc) const
        {
            return my_Quotation_Mark.test(uc - my_first_letter);
        }

        bool is_Terminal_Punctuation(const UCS4 uc) const
        {
            return my_Terminal_Punctuation.test(uc - my_first_letter);
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
            return my_Other_Default_Ignorable_Code_Point.test(uc - my_first_letter);
        }

        bool is_Deprecated(const UCS4 uc) const
        {
            return my_Deprecated.test(uc - my_first_letter);
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

      private:
        // functions
        General_Punctuation2000(const General_Punctuation2000 &) ; // no implementaion!

	// members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const std::bitset<112> my_is_defined;
        static const unsigned char my_cat[112];
        static const Babylon::Bidir_Props my_bidir[112];
        static const unsigned char my_decomp[112];
        static const UCS2 my_decompStr[112][2];
        static const std::bitset<112> my_mirror;
        static const unsigned char my_lb[112];
        static const unsigned char my_ea[112];
        static const std::bitset<112> my_White_Space;
        static const std::bitset<112> my_Bidi_Control;
        static const std::bitset<112> my_Join_Control;
        static const std::bitset<112> my_Dash;
        static const std::bitset<112> my_Hyphen;
        static const std::bitset<112> my_Quotation_Mark;
        static const std::bitset<112> my_Terminal_Punctuation;
        static const std::bitset<112> my_Other_Math;
        static const std::bitset<112> my_Other_Default_Ignorable_Code_Point;
        static const std::bitset<112> my_Deprecated;
    }; // class General_Punctuation2000

    const std::bitset<112> General_Punctuation2000::my_is_defined(std::string("1111110000001111100000001001111111111111111111111111111111111111111111111111111111111111111111111111111111111111"));

    const unsigned char General_Punctuation2000::my_cat[] =
    {
        CAT_Zs, CAT_Zs, CAT_Zs, CAT_Zs, CAT_Zs, CAT_Zs, CAT_Zs, CAT_Zs, 
        CAT_Zs, CAT_Zs, CAT_Zs, CAT_Zs, CAT_Cf, CAT_Cf, CAT_Cf, CAT_Cf, 
        CAT_Pd, CAT_Pd, CAT_Pd, CAT_Pd, CAT_Pd, CAT_Pd, CAT_Po, CAT_Po, 
        CAT_Pi, CAT_Pf, CAT_Ps, CAT_Pi, CAT_Pi, CAT_Pf, CAT_Ps, CAT_Pi, 
        CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, 
        CAT_Zl, CAT_Zp, CAT_Cf, CAT_Cf, CAT_Cf, CAT_Cf, CAT_Cf, CAT_Zs, 
        CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, 
        CAT_Po, CAT_Pi, CAT_Pf, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Pc, 
        CAT_Pc, CAT_Po, CAT_Po, CAT_Po, CAT_Sm, CAT_Ps, CAT_Pe, CAT_Po, 
        CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, 
        CAT_Po, CAT_Po, CAT_Sm, CAT_Po, CAT_Pc, CAT_Zs, CAT_Zs, CAT_Po, 
        CAT_Zs, CAT_Zs, CAT_Zs, CAT_Zs, CAT_Zs, CAT_Zs, CAT_Zs, CAT_Zs, 
        CAT_Cf, CAT_Cf, CAT_Cf, CAT_Cf, CAT_Zs, CAT_Zs, CAT_Zs, CAT_Zs, 
        CAT_Zs, CAT_Zs, CAT_Cf, CAT_Cf, CAT_Cf, CAT_Cf, CAT_Cf, CAT_Cf
    };

    const Babylon::Bidir_Props General_Punctuation2000::my_bidir[] =
    {
        BIDIR_WS, BIDIR_WS, BIDIR_WS, BIDIR_WS, 
        BIDIR_WS, BIDIR_WS, BIDIR_WS, BIDIR_WS, 
        BIDIR_WS, BIDIR_WS, BIDIR_WS, BIDIR_BN, 
        BIDIR_BN, BIDIR_BN, BIDIR_L, BIDIR_R, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_WS, BIDIR_B, BIDIR_LRE, BIDIR_RLE, 
        BIDIR_PDF, BIDIR_LRO, BIDIR_RLO, BIDIR_WS, 
        BIDIR_ET, BIDIR_ET, BIDIR_ET, BIDIR_ET, 
        BIDIR_ET, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_WS, BIDIR_WS, BIDIR_ON, 
        BIDIR_WS, BIDIR_WS, BIDIR_WS, BIDIR_WS, 
        BIDIR_WS, BIDIR_WS, BIDIR_WS, BIDIR_WS, 
        BIDIR_BN, BIDIR_BN, BIDIR_BN, BIDIR_BN, 
        BIDIR_WS, BIDIR_WS, BIDIR_WS, BIDIR_WS, 
        BIDIR_WS, BIDIR_WS, BIDIR_BN, BIDIR_BN, 
        BIDIR_BN, BIDIR_BN, BIDIR_BN, BIDIR_BN
    };

    const unsigned char General_Punctuation2000::my_decomp[] = {
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_NOBREAK, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_NOBREAK, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_COMPAT, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_NOBREAK, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_CANONICAL, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_COMPAT, DECOMP_CANONICAL, DECOMP_COMPAT, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_COMPAT, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_COMPAT, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL
    };

    const UCS2 General_Punctuation2000::my_decompStr[][2] =
    {
        { 0x00002002u, 0x00000000u }, { 0x00002003u, 0x00000000u },  // 00002000
        { 0x00000020u, 0x00000000u }, { 0x00000020u, 0x00000000u },  // 00002002
        { 0x00000020u, 0x00000000u }, { 0x00000020u, 0x00000000u },  // 00002004
        { 0x00000020u, 0x00000000u }, { 0x00000020u, 0x00000000u },  // 00002006
        { 0x00000020u, 0x00000000u }, { 0x00000020u, 0x00000000u },  // 00002008
        { 0x00000020u, 0x00000000u }, { 0x0000200Bu, 0x00000000u },  // 0000200A
        { 0x0000200Cu, 0x00000000u }, { 0x0000200Du, 0x00000000u },  // 0000200C
        { 0x0000200Eu, 0x00000000u }, { 0x0000200Fu, 0x00000000u },  // 0000200E
        { 0x00002010u, 0x00000000u }, { 0x00002010u, 0x00000000u },  // 00002010
        { 0x00002012u, 0x00000000u }, { 0x00002013u, 0x00000000u },  // 00002012
        { 0x00002014u, 0x00000000u }, { 0x00002015u, 0x00000000u },  // 00002014
        { 0x00002016u, 0x00000000u }, { 0x00000020u, 0x00000333u },  // 00002016
        { 0x00002018u, 0x00000000u }, { 0x00002019u, 0x00000000u },  // 00002018
        { 0x0000201Au, 0x00000000u }, { 0x0000201Bu, 0x00000000u },  // 0000201A
        { 0x0000201Cu, 0x00000000u }, { 0x0000201Du, 0x00000000u },  // 0000201C
        { 0x0000201Eu, 0x00000000u }, { 0x0000201Fu, 0x00000000u },  // 0000201E
        { 0x00002020u, 0x00000000u }, { 0x00002021u, 0x00000000u },  // 00002020
        { 0x00002022u, 0x00000000u }, { 0x00002023u, 0x00000000u },  // 00002022
        { 0x0000002Eu, 0x00000000u }, { 0x0000002Eu, 0x0000002Eu },  // 00002024
        { 0x0000002Eu, 0x0000002Eu }, { 0x00002027u, 0x00000000u },  // 00002026
        { 0x00002028u, 0x00000000u }, { 0x00002029u, 0x00000000u },  // 00002028
        { 0x0000202Au, 0x00000000u }, { 0x0000202Bu, 0x00000000u },  // 0000202A
        { 0x0000202Cu, 0x00000000u }, { 0x0000202Du, 0x00000000u },  // 0000202C
        { 0x0000202Eu, 0x00000000u }, { 0x00000020u, 0x00000000u },  // 0000202E
        { 0x00002030u, 0x00000000u }, { 0x00002031u, 0x00000000u },  // 00002030
        { 0x00002032u, 0x00000000u }, { 0x00002032u, 0x00002032u },  // 00002032
        { 0x00002032u, 0x00002032u }, { 0x00002035u, 0x00000000u },  // 00002034
        { 0x00002035u, 0x00002035u }, { 0x00002035u, 0x00002035u },  // 00002036
        { 0x00002038u, 0x00000000u }, { 0x00002039u, 0x00000000u },  // 00002038
        { 0x0000203Au, 0x00000000u }, { 0x0000203Bu, 0x00000000u },  // 0000203A
        { 0x00000021u, 0x00000021u }, { 0x0000203Du, 0x00000000u },  // 0000203C
        { 0x00000020u, 0x00000305u }, { 0x0000203Fu, 0x00000000u },  // 0000203E
        { 0x00002040u, 0x00000000u }, { 0x00002041u, 0x00000000u },  // 00002040
        { 0x00002042u, 0x00000000u }, { 0x00002043u, 0x00000000u },  // 00002042
        { 0x00002044u, 0x00000000u }, { 0x00002045u, 0x00000000u },  // 00002044
        { 0x00002046u, 0x00000000u }, { 0x0000003Fu, 0x0000003Fu },  // 00002046
        { 0x0000003Fu, 0x00000021u }, { 0x00000021u, 0x0000003Fu },  // 00002048
        { 0x0000204Au, 0x00000000u }, { 0x0000204Bu, 0x00000000u },  // 0000204A
        { 0x0000204Cu, 0x00000000u }, { 0x0000204Du, 0x00000000u },  // 0000204C
        { 0x0000204Eu, 0x00000000u }, { 0x0000204Fu, 0x00000000u },  // 0000204E
        { 0x00002050u, 0x00000000u }, { 0x00002051u, 0x00000000u },  // 00002050
        { 0x00002052u, 0x00000000u }, { 0x00002053u, 0x00000000u },  // 00002052
        { 0x00002054u, 0x00000000u }, { 0x00002055u, 0x00000000u },  // 00002054
        { 0x00002056u, 0x00000000u }, { 0x00002032u, 0x00002032u },  // 00002056
        { 0x00002058u, 0x00000000u }, { 0x00002059u, 0x00000000u },  // 00002058
        { 0x0000205Au, 0x00000000u }, { 0x0000205Bu, 0x00000000u },  // 0000205A
        { 0x0000205Cu, 0x00000000u }, { 0x0000205Du, 0x00000000u },  // 0000205C
        { 0x0000205Eu, 0x00000000u }, { 0x00000020u, 0x00000000u },  // 0000205E
        { 0x00002060u, 0x00000000u }, { 0x00002061u, 0x00000000u },  // 00002060
        { 0x00002062u, 0x00000000u }, { 0x00002063u, 0x00000000u },  // 00002062
        { 0x00002064u, 0x00000000u }, { 0x00002065u, 0x00000000u },  // 00002064
        { 0x00002066u, 0x00000000u }, { 0x00002067u, 0x00000000u },  // 00002066
        { 0x00002068u, 0x00000000u }, { 0x00002069u, 0x00000000u },  // 00002068
        { 0x0000206Au, 0x00000000u }, { 0x0000206Bu, 0x00000000u },  // 0000206A
        { 0x0000206Cu, 0x00000000u }, { 0x0000206Du, 0x00000000u },  // 0000206C
        { 0x0000206Eu, 0x00000000u }, { 0x0000206Fu, 0x00000000u }
    };

    const std::bitset<112> General_Punctuation2000::my_mirror(std::string("0000000000000000000000000000000000000000011000000000011000000000000000000000000000000000000000000000000000000000"));

    const unsigned char General_Punctuation2000::my_lb[] =
    {
        LB_BA, LB_BA, LB_BA, LB_BA, LB_BA, LB_BA, LB_BA, LB_GL, 
        LB_BA, LB_BA, LB_BA, LB_ZW, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_BA, LB_GL, LB_BA, LB_BA, LB_B2, LB_AI, LB_AI, LB_AL, 
        LB_QU, LB_QU, LB_OP, LB_QU, LB_QU, LB_QU, LB_OP, LB_QU, 
        LB_AI, LB_AI, LB_AL, LB_AL, LB_IN, LB_IN, LB_IN, LB_BA, 
        LB_BK, LB_BK, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_GL, 
        LB_PO, LB_PO, LB_PO, LB_PO, LB_PO, LB_PO, LB_PO, LB_PO, 
        LB_AL, LB_QU, LB_QU, LB_AI, LB_NS, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_IS, LB_OP, LB_CL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_BA, LB_BA, LB_AL, 
        LB_BA, LB_BA, LB_BA, LB_BA, LB_BA, LB_BA, LB_BA, LB_BA, 
        LB_WJ, LB_AL, LB_AL, LB_AL, LB_BA, LB_BA, LB_BA, LB_BA, 
        LB_BA, LB_BA, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM
    };

    const unsigned char General_Punctuation2000::my_ea[] =
    {
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_N, 
        EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_A, 
        EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N
    };

    const std::bitset<112> General_Punctuation2000::my_White_Space(std::string("0000000000000000100000000000000000000000000000000000000000000000100000110000000000000000000000000000011111111111"));

    const std::bitset<112> General_Punctuation2000::my_Bidi_Control(std::string("0000000000000000000000000000000000000000000000000000000000000000011111000000000000000000000000001100000000000000"));

    const std::bitset<112> General_Punctuation2000::my_Join_Control(std::string("0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000011000000000000"));

    const std::bitset<112> General_Punctuation2000::my_Dash(std::string("0000000000000000000000000000100000000000000000000000000000000000000000000000000000000000001111110000000000000000"));

    const std::bitset<112> General_Punctuation2000::my_Hyphen(std::string("0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000110000000000000000"));

    const std::bitset<112> General_Punctuation2000::my_Quotation_Mark(std::string("0000000000000000000000000000000000000000000000000000011000000000000000000000000011111111000000000000000000000000"));

    const std::bitset<112> General_Punctuation2000::my_Terminal_Punctuation(std::string("0000000000000000000000000000000000000011100000000011000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<112> General_Punctuation2000::my_Other_Math(std::string("0000000000000000000000000000000000000000000000000000000000011100000000000000000000000000010000000000000000000000"));

    const std::bitset<112> General_Punctuation2000::my_Other_Default_Ignorable_Code_Point(std::string("0000001111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000100000000000"));

    const std::bitset<112> General_Punctuation2000::my_Deprecated(std::string("1111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));

  }; // namespace
}; // namespace

dload(Babylon::Module::General_Punctuation2000);
