/*$Id: UnicodePluginGenerator.pl,v 1.11 2004/01/28 12:39:04 tobias Exp 530-58F.cc
 *
 * This source file is a part of the Fresco Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Wed, 28 Jan 2004 20:49:03 +0100.
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


namespace Babylon
{
  namespace Module
  {
    class Armenian530 : public Babylon::Block
    {
      public:
        void clean() { };

        Armenian530() :
        my_first_letter(0x530),
        my_last_letter(0x58F)
        // my_version="4.0" // Not yet supported!
        {
        }

        ~Armenian530() { }

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
        return "Armenian";
    }

        bool is_defined(const UCS4 uc) const
        {
            return (my_is_defined.test(uc - my_first_letter));
        }

        UCS4 uppercase(const UCS4 uc) const
        {
            return Armenian530::my_upper[uc - my_first_letter];
        }

        UCS4 lowercase(const UCS4 uc) const
        {
            return Armenian530::my_lower[uc - my_first_letter];
        }

        UCS4 titlecase(const UCS4 uc) const
        {
            return Armenian530::my_title[uc - my_first_letter];
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
            return Babylon::Gen_Cat(Armenian530::my_cat[uc - my_first_letter]);
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
            return Armenian530::my_bidir[uc - my_first_letter];
        }

        Char_Decomp decomp_type(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return DECOMP_MAX;
            return Babylon::Char_Decomp(Armenian530::my_decomp[uc - my_first_letter]);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            Babylon::UTF32_string us;
            us.resize(2);
            us[0] = Armenian530::my_decompStr[uc - my_first_letter][0];
            us[1] = Armenian530::my_decompStr[uc - my_first_letter][1];
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
            return Babylon::Line_Break(Armenian530::my_lb[uc - my_first_letter]);
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
            return my_Dash.test(uc - my_first_letter);
        }

        bool is_Hyphen(const UCS4 uc) const
        {
            return my_Hyphen.test(uc - my_first_letter);
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
        Armenian530(const Armenian530 &) ; // no implementaion!

    // members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const std::bitset<96> my_is_defined;
        static const UCS4 my_upper[96];
        static const UCS4 my_lower[96];
        static const UCS4 my_title[96];
        static const unsigned char my_cat[96];
        static const Babylon::Bidir_Props my_bidir[96];
        static const unsigned char my_decomp[96];
        static const UCS2 my_decompStr[96][2];
        static const unsigned char my_lb[96];
        static const std::bitset<96> my_Dash;
        static const std::bitset<96> my_Hyphen;
        static const std::bitset<96> my_Terminal_Punctuation;
        static const std::bitset<96> my_Diacritic;
    }; // class Armenian530

    const std::bitset<96> Armenian530::my_is_defined(std::string("000001101111111111111111111111111111111111111110111111100111111111111111111111111111111111111110"));

    const UCS4 Armenian530::my_upper[] =
    {
        0x0530, 0x0531, 0x0532, 0x0533, 0x0534, 0x0535, 0x0536, 0x0537, 
        0x0538, 0x0539, 0x053A, 0x053B, 0x053C, 0x053D, 0x053E, 0x053F, 
        0x0540, 0x0541, 0x0542, 0x0543, 0x0544, 0x0545, 0x0546, 0x0547, 
        0x0548, 0x0549, 0x054A, 0x054B, 0x054C, 0x054D, 0x054E, 0x054F, 
        0x0550, 0x0551, 0x0552, 0x0553, 0x0554, 0x0555, 0x0556, 0x0557, 
        0x0558, 0x0559, 0x055A, 0x055B, 0x055C, 0x055D, 0x055E, 0x055F, 
        0x0560, 0x0531, 0x0532, 0x0533, 0x0534, 0x0535, 0x0536, 0x0537, 
        0x0538, 0x0539, 0x053A, 0x053B, 0x053C, 0x053D, 0x053E, 0x053F, 
        0x0540, 0x0541, 0x0542, 0x0543, 0x0544, 0x0545, 0x0546, 0x0547, 
        0x0548, 0x0549, 0x054A, 0x054B, 0x054C, 0x054D, 0x054E, 0x054F, 
        0x0550, 0x0551, 0x0552, 0x0553, 0x0554, 0x0555, 0x0556, 0x0587, 
        0x0588, 0x0589, 0x058A, 0x058B, 0x058C, 0x058D, 0x058E, 0x058F
    };

    const UCS4 Armenian530::my_lower[] =
    {
        0x0530, 0x0561, 0x0562, 0x0563, 0x0564, 0x0565, 0x0566, 0x0567, 
        0x0568, 0x0569, 0x056A, 0x056B, 0x056C, 0x056D, 0x056E, 0x056F, 
        0x0570, 0x0571, 0x0572, 0x0573, 0x0574, 0x0575, 0x0576, 0x0577, 
        0x0578, 0x0579, 0x057A, 0x057B, 0x057C, 0x057D, 0x057E, 0x057F, 
        0x0580, 0x0581, 0x0582, 0x0583, 0x0584, 0x0585, 0x0586, 0x0557, 
        0x0558, 0x0559, 0x055A, 0x055B, 0x055C, 0x055D, 0x055E, 0x055F, 
        0x0560, 0x0561, 0x0562, 0x0563, 0x0564, 0x0565, 0x0566, 0x0567, 
        0x0568, 0x0569, 0x056A, 0x056B, 0x056C, 0x056D, 0x056E, 0x056F, 
        0x0570, 0x0571, 0x0572, 0x0573, 0x0574, 0x0575, 0x0576, 0x0577, 
        0x0578, 0x0579, 0x057A, 0x057B, 0x057C, 0x057D, 0x057E, 0x057F, 
        0x0580, 0x0581, 0x0582, 0x0583, 0x0584, 0x0585, 0x0586, 0x0587, 
        0x0588, 0x0589, 0x058A, 0x058B, 0x058C, 0x058D, 0x058E, 0x058F
    };

    const UCS4 Armenian530::my_title[] =
    {
        0x0530, 0x0531, 0x0532, 0x0533, 0x0534, 0x0535, 0x0536, 0x0537, 
        0x0538, 0x0539, 0x053A, 0x053B, 0x053C, 0x053D, 0x053E, 0x053F, 
        0x0540, 0x0541, 0x0542, 0x0543, 0x0544, 0x0545, 0x0546, 0x0547, 
        0x0548, 0x0549, 0x054A, 0x054B, 0x054C, 0x054D, 0x054E, 0x054F, 
        0x0550, 0x0551, 0x0552, 0x0553, 0x0554, 0x0555, 0x0556, 0x0557, 
        0x0558, 0x0559, 0x055A, 0x055B, 0x055C, 0x055D, 0x055E, 0x055F, 
        0x0560, 0x0531, 0x0532, 0x0533, 0x0534, 0x0535, 0x0536, 0x0537, 
        0x0538, 0x0539, 0x053A, 0x053B, 0x053C, 0x053D, 0x053E, 0x053F, 
        0x0540, 0x0541, 0x0542, 0x0543, 0x0544, 0x0545, 0x0546, 0x0547, 
        0x0548, 0x0549, 0x054A, 0x054B, 0x054C, 0x054D, 0x054E, 0x054F, 
        0x0550, 0x0551, 0x0552, 0x0553, 0x0554, 0x0555, 0x0556, 0x0587, 
        0x0588, 0x0589, 0x058A, 0x058B, 0x058C, 0x058D, 0x058E, 0x058F
    };

    const unsigned char Armenian530::my_cat[] =
    {
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lm, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Po, 
        CAT_Lu, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Lu, CAT_Po, CAT_Pd, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu
    };

    const Babylon::Bidir_Props Armenian530::my_bidir[] =
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
        BIDIR_L, BIDIR_L, BIDIR_ON, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L
    };

    const unsigned char Armenian530::my_decomp[] = {
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
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL
    };

    const UCS2 Armenian530::my_decompStr[][2] =
    {
        { 0x00000530u, 0x00000000u }, { 0x00000531u, 0x00000000u },  // 00000530
        { 0x00000532u, 0x00000000u }, { 0x00000533u, 0x00000000u },  // 00000532
        { 0x00000534u, 0x00000000u }, { 0x00000535u, 0x00000000u },  // 00000534
        { 0x00000536u, 0x00000000u }, { 0x00000537u, 0x00000000u },  // 00000536
        { 0x00000538u, 0x00000000u }, { 0x00000539u, 0x00000000u },  // 00000538
        { 0x0000053Au, 0x00000000u }, { 0x0000053Bu, 0x00000000u },  // 0000053A
        { 0x0000053Cu, 0x00000000u }, { 0x0000053Du, 0x00000000u },  // 0000053C
        { 0x0000053Eu, 0x00000000u }, { 0x0000053Fu, 0x00000000u },  // 0000053E
        { 0x00000540u, 0x00000000u }, { 0x00000541u, 0x00000000u },  // 00000540
        { 0x00000542u, 0x00000000u }, { 0x00000543u, 0x00000000u },  // 00000542
        { 0x00000544u, 0x00000000u }, { 0x00000545u, 0x00000000u },  // 00000544
        { 0x00000546u, 0x00000000u }, { 0x00000547u, 0x00000000u },  // 00000546
        { 0x00000548u, 0x00000000u }, { 0x00000549u, 0x00000000u },  // 00000548
        { 0x0000054Au, 0x00000000u }, { 0x0000054Bu, 0x00000000u },  // 0000054A
        { 0x0000054Cu, 0x00000000u }, { 0x0000054Du, 0x00000000u },  // 0000054C
        { 0x0000054Eu, 0x00000000u }, { 0x0000054Fu, 0x00000000u },  // 0000054E
        { 0x00000550u, 0x00000000u }, { 0x00000551u, 0x00000000u },  // 00000550
        { 0x00000552u, 0x00000000u }, { 0x00000553u, 0x00000000u },  // 00000552
        { 0x00000554u, 0x00000000u }, { 0x00000555u, 0x00000000u },  // 00000554
        { 0x00000556u, 0x00000000u }, { 0x00000557u, 0x00000000u },  // 00000556
        { 0x00000558u, 0x00000000u }, { 0x00000559u, 0x00000000u },  // 00000558
        { 0x0000055Au, 0x00000000u }, { 0x0000055Bu, 0x00000000u },  // 0000055A
        { 0x0000055Cu, 0x00000000u }, { 0x0000055Du, 0x00000000u },  // 0000055C
        { 0x0000055Eu, 0x00000000u }, { 0x0000055Fu, 0x00000000u },  // 0000055E
        { 0x00000560u, 0x00000000u }, { 0x00000561u, 0x00000000u },  // 00000560
        { 0x00000562u, 0x00000000u }, { 0x00000563u, 0x00000000u },  // 00000562
        { 0x00000564u, 0x00000000u }, { 0x00000565u, 0x00000000u },  // 00000564
        { 0x00000566u, 0x00000000u }, { 0x00000567u, 0x00000000u },  // 00000566
        { 0x00000568u, 0x00000000u }, { 0x00000569u, 0x00000000u },  // 00000568
        { 0x0000056Au, 0x00000000u }, { 0x0000056Bu, 0x00000000u },  // 0000056A
        { 0x0000056Cu, 0x00000000u }, { 0x0000056Du, 0x00000000u },  // 0000056C
        { 0x0000056Eu, 0x00000000u }, { 0x0000056Fu, 0x00000000u },  // 0000056E
        { 0x00000570u, 0x00000000u }, { 0x00000571u, 0x00000000u },  // 00000570
        { 0x00000572u, 0x00000000u }, { 0x00000573u, 0x00000000u },  // 00000572
        { 0x00000574u, 0x00000000u }, { 0x00000575u, 0x00000000u },  // 00000574
        { 0x00000576u, 0x00000000u }, { 0x00000577u, 0x00000000u },  // 00000576
        { 0x00000578u, 0x00000000u }, { 0x00000579u, 0x00000000u },  // 00000578
        { 0x0000057Au, 0x00000000u }, { 0x0000057Bu, 0x00000000u },  // 0000057A
        { 0x0000057Cu, 0x00000000u }, { 0x0000057Du, 0x00000000u },  // 0000057C
        { 0x0000057Eu, 0x00000000u }, { 0x0000057Fu, 0x00000000u },  // 0000057E
        { 0x00000580u, 0x00000000u }, { 0x00000581u, 0x00000000u },  // 00000580
        { 0x00000582u, 0x00000000u }, { 0x00000583u, 0x00000000u },  // 00000582
        { 0x00000584u, 0x00000000u }, { 0x00000585u, 0x00000000u },  // 00000584
        { 0x00000586u, 0x00000000u }, { 0x00000565u, 0x00000582u },  // 00000586
        { 0x00000588u, 0x00000000u }, { 0x00000589u, 0x00000000u },  // 00000588
        { 0x0000058Au, 0x00000000u }, { 0x0000058Bu, 0x00000000u },  // 0000058A
        { 0x0000058Cu, 0x00000000u }, { 0x0000058Du, 0x00000000u },  // 0000058C
        { 0x0000058Eu, 0x00000000u }, { 0x0000058Fu, 0x00000000u }
    };

    const unsigned char Armenian530::my_lb[] =
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
        LB_AL, LB_IS, LB_BA, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL
    };

    const std::bitset<96> Armenian530::my_Dash(std::string("000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<96> Armenian530::my_Hyphen(std::string("000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<96> Armenian530::my_Terminal_Punctuation(std::string("000000100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<96> Armenian530::my_Diacritic(std::string("000000000000000000000000000000000000000000000000000000100000000000000000000000000000000000000000"));

  }; // namespace
}; // namespace

dload(Babylon::Module::Armenian530);
