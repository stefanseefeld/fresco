/*$Id: UnicodePluginGenerator.pl,v 1.7 2003/08/01 16:47:16 tobias Exp 3200-32FF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 05 Aug 2003 17:09:49 +0200.
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
    class Enclosed_CJK_Letters_and_Months3200 : public Babylon::Block
    {
      public:
        void clean() { };

        Enclosed_CJK_Letters_and_Months3200() :
        my_first_letter(0x3200),
        my_last_letter(0x32FF)
        // my_version="4.0" // Not yet supported!
        {
        }

        ~Enclosed_CJK_Letters_and_Months3200() { }

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
        return "Enclosed CJK Letters and Months";
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
            case 0x3220u:
                return 1.000000;
            case 0x3221u:
                return 2.000000;
            case 0x3222u:
                return 3.000000;
            case 0x3223u:
                return 4.000000;
            case 0x3224u:
                return 5.000000;
            case 0x3225u:
                return 6.000000;
            case 0x3226u:
                return 7.000000;
            case 0x3227u:
                return 8.000000;
            case 0x3228u:
                return 9.000000;
            case 0x3229u:
                return 10.000000;
            case 0x3251u:
                return 21.000000;
            case 0x3252u:
                return 22.000000;
            case 0x3253u:
                return 23.000000;
            case 0x3254u:
                return 24.000000;
            case 0x3255u:
                return 25.000000;
            case 0x3256u:
                return 26.000000;
            case 0x3257u:
                return 27.000000;
            case 0x3258u:
                return 28.000000;
            case 0x3259u:
                return 29.000000;
            case 0x325Au:
                return 30.000000;
            case 0x325Bu:
                return 31.000000;
            case 0x325Cu:
                return 32.000000;
            case 0x325Du:
                return 33.000000;
            case 0x325Eu:
                return 34.000000;
            case 0x325Fu:
                return 35.000000;
            case 0x3280u:
                return 1.000000;
            case 0x3281u:
                return 2.000000;
            case 0x3282u:
                return 3.000000;
            case 0x3283u:
                return 4.000000;
            case 0x3284u:
                return 5.000000;
            case 0x3285u:
                return 6.000000;
            case 0x3286u:
                return 7.000000;
            case 0x3287u:
                return 8.000000;
            case 0x3288u:
                return 9.000000;
            case 0x3289u:
                return 10.000000;
            case 0x32B1u:
                return 36.000000;
            case 0x32B2u:
                return 37.000000;
            case 0x32B3u:
                return 38.000000;
            case 0x32B4u:
                return 39.000000;
            case 0x32B5u:
                return 40.000000;
            case 0x32B6u:
                return 41.000000;
            case 0x32B7u:
                return 42.000000;
            case 0x32B8u:
                return 43.000000;
            case 0x32B9u:
                return 44.000000;
            case 0x32BAu:
                return 45.000000;
            case 0x32BBu:
                return 46.000000;
            case 0x32BCu:
                return 47.000000;
            case 0x32BDu:
                return 48.000000;
            case 0x32BEu:
                return 49.000000;
            case 0x32BFu:
                return 50.000000;
            default:
                return 0;
            }
        }

        bool is_Numeric(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x3220u:
            case 0x3221u:
            case 0x3222u:
            case 0x3223u:
            case 0x3224u:
            case 0x3225u:
            case 0x3226u:
            case 0x3227u:
            case 0x3228u:
            case 0x3229u:
            case 0x3251u:
            case 0x3252u:
            case 0x3253u:
            case 0x3254u:
            case 0x3255u:
            case 0x3256u:
            case 0x3257u:
            case 0x3258u:
            case 0x3259u:
            case 0x325Au:
            case 0x325Bu:
            case 0x325Cu:
            case 0x325Du:
            case 0x325Eu:
            case 0x325Fu:
            case 0x3280u:
            case 0x3281u:
            case 0x3282u:
            case 0x3283u:
            case 0x3284u:
            case 0x3285u:
            case 0x3286u:
            case 0x3287u:
            case 0x3288u:
            case 0x3289u:
            case 0x32B1u:
            case 0x32B2u:
            case 0x32B3u:
            case 0x32B4u:
            case 0x32B5u:
            case 0x32B6u:
            case 0x32B7u:
            case 0x32B8u:
            case 0x32B9u:
            case 0x32BAu:
            case 0x32BBu:
            case 0x32BCu:
            case 0x32BDu:
            case 0x32BEu:
            case 0x32BFu:
                return 1;
            default:
                return 0;
            }
        }

        Gen_Cat category(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CAT_MAX;
            return Babylon::Gen_Cat(Enclosed_CJK_Letters_and_Months3200::my_cat[uc - my_first_letter]);
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
            return Enclosed_CJK_Letters_and_Months3200::my_bidir[uc - my_first_letter];
        }

        Char_Decomp decomp_type(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return DECOMP_MAX;
            return Babylon::Char_Decomp(Enclosed_CJK_Letters_and_Months3200::my_decomp[uc - my_first_letter]);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            Babylon::UTF32_string us;
            us.resize(2);
            us[0] = Enclosed_CJK_Letters_and_Months3200::my_decompStr[uc - my_first_letter][0];
            us[1] = Enclosed_CJK_Letters_and_Months3200::my_decompStr[uc - my_first_letter][1];

            switch (uc)
            {

            case 0x3200:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x3201:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x3202:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x3203:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x3204:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x3205:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x3206:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x3207:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x3208:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x3209:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x320A:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x320B:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x320C:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x320D:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x320E:
                us.resize(4);
                us[2u] = 0x1161u;
                us[3u] = 0x0029u;
                break;

            case 0x320F:
                us.resize(4);
                us[2u] = 0x1161u;
                us[3u] = 0x0029u;
                break;

            case 0x3210:
                us.resize(4);
                us[2u] = 0x1161u;
                us[3u] = 0x0029u;
                break;

            case 0x3211:
                us.resize(4);
                us[2u] = 0x1161u;
                us[3u] = 0x0029u;
                break;

            case 0x3212:
                us.resize(4);
                us[2u] = 0x1161u;
                us[3u] = 0x0029u;
                break;

            case 0x3213:
                us.resize(4);
                us[2u] = 0x1161u;
                us[3u] = 0x0029u;
                break;

            case 0x3214:
                us.resize(4);
                us[2u] = 0x1161u;
                us[3u] = 0x0029u;
                break;

            case 0x3215:
                us.resize(4);
                us[2u] = 0x1161u;
                us[3u] = 0x0029u;
                break;

            case 0x3216:
                us.resize(4);
                us[2u] = 0x1161u;
                us[3u] = 0x0029u;
                break;

            case 0x3217:
                us.resize(4);
                us[2u] = 0x1161u;
                us[3u] = 0x0029u;
                break;

            case 0x3218:
                us.resize(4);
                us[2u] = 0x1161u;
                us[3u] = 0x0029u;
                break;

            case 0x3219:
                us.resize(4);
                us[2u] = 0x1161u;
                us[3u] = 0x0029u;
                break;

            case 0x321A:
                us.resize(4);
                us[2u] = 0x1161u;
                us[3u] = 0x0029u;
                break;

            case 0x321B:
                us.resize(4);
                us[2u] = 0x1161u;
                us[3u] = 0x0029u;
                break;

            case 0x321C:
                us.resize(4);
                us[2u] = 0x116Eu;
                us[3u] = 0x0029u;
                break;

            case 0x321D:
                us.resize(7);
                us[2u] = 0x1169u;
                us[3u] = 0x110Cu;
                us[4u] = 0x1165u;
                us[5u] = 0x11ABu;
                us[6u] = 0x0029u;
                break;

            case 0x321E:
                us.resize(6);
                us[2u] = 0x1169u;
                us[3u] = 0x1112u;
                us[4u] = 0x116Eu;
                us[5u] = 0x0029u;
                break;

            case 0x3220:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x3221:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x3222:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x3223:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x3224:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x3225:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x3226:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x3227:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x3228:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x3229:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x322A:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x322B:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x322C:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x322D:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x322E:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x322F:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x3230:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x3231:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x3232:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x3233:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x3234:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x3235:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x3236:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x3237:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x3238:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x3239:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x323A:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x323B:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x323C:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x323D:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x323E:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x323F:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x3240:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x3241:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x3242:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x3243:
                us.resize(3);
                us[2u] = 0x0029u;
                break;

            case 0x3250:
                us.resize(3);
                us[2u] = 0x0045u;
                break;

            case 0x327C:
                us.resize(5);
                us[2u] = 0x11B7u;
                us[3u] = 0x1100u;
                us[4u] = 0x1169u;
                break;

            case 0x327D:
                us.resize(4);
                us[2u] = 0x110Bu;
                us[3u] = 0x1174u;
                break;

            case 0x32C9:
                us.resize(3);
                us[2u] = 0x6708u;
                break;

            case 0x32CA:
                us.resize(3);
                us[2u] = 0x6708u;
                break;

            case 0x32CB:
                us.resize(3);
                us[2u] = 0x6708u;
                break;

            case 0x32CD:
                us.resize(3);
                us[2u] = 0x0067u;
                break;

            case 0x32CF:
                us.resize(3);
                us[2u] = 0x0044u;
                break;
            }
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
            return Babylon::Line_Break(LB_ID);
    }

        EA_Width EA_width(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return EA_WIDTH_MAX;
            return Babylon::EA_Width(EA_WIDTH_W);
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
        Enclosed_CJK_Letters_and_Months3200(const Enclosed_CJK_Letters_and_Months3200 &) ; // no implementaion!

    // members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const std::bitset<256> my_is_defined;
        static const unsigned char my_cat[256];
        static const Babylon::Bidir_Props my_bidir[256];
        static const unsigned char my_decomp[256];
        static const UCS4 my_decompStr[256][2];
    }; // class Enclosed_CJK_Letters_and_Months3200

    const std::bitset<256> Enclosed_CJK_Letters_and_Months3200::my_is_defined(std::string("0111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111110111111111111111111111111111111111111111111111100000000000011111111111111111111111111111111111101111111111111111111111111111111"));

    const unsigned char Enclosed_CJK_Letters_and_Months3200::my_cat[] =
    {
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
        CAT_No, CAT_No, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
        CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
        CAT_No, CAT_No, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
        CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, CAT_No, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, 
        CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So, CAT_So
    };

    const Babylon::Bidir_Props Enclosed_CJK_Letters_and_Months3200::my_bidir[] =
    {
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_ON, BIDIR_ON, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_ON, BIDIR_ON, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
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

    const unsigned char Enclosed_CJK_Letters_and_Months3200::my_decomp[] = {
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_CANONICAL, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_SQUARE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, 
        DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CIRCLE, DECOMP_CANONICAL
    };

    const UCS4 Enclosed_CJK_Letters_and_Months3200::my_decompStr[][2] =
    {
        { 0x00000028u, 0x00001100u }, { 0x00000028u, 0x00001102u },  // 00003200
        { 0x00000028u, 0x00001103u }, { 0x00000028u, 0x00001105u },  // 00003202
        { 0x00000028u, 0x00001106u }, { 0x00000028u, 0x00001107u },  // 00003204
        { 0x00000028u, 0x00001109u }, { 0x00000028u, 0x0000110Bu },  // 00003206
        { 0x00000028u, 0x0000110Cu }, { 0x00000028u, 0x0000110Eu },  // 00003208
        { 0x00000028u, 0x0000110Fu }, { 0x00000028u, 0x00001110u },  // 0000320A
        { 0x00000028u, 0x00001111u }, { 0x00000028u, 0x00001112u },  // 0000320C
        { 0x00000028u, 0x00001100u }, { 0x00000028u, 0x00001102u },  // 0000320E
        { 0x00000028u, 0x00001103u }, { 0x00000028u, 0x00001105u },  // 00003210
        { 0x00000028u, 0x00001106u }, { 0x00000028u, 0x00001107u },  // 00003212
        { 0x00000028u, 0x00001109u }, { 0x00000028u, 0x0000110Bu },  // 00003214
        { 0x00000028u, 0x0000110Cu }, { 0x00000028u, 0x0000110Eu },  // 00003216
        { 0x00000028u, 0x0000110Fu }, { 0x00000028u, 0x00001110u },  // 00003218
        { 0x00000028u, 0x00001111u }, { 0x00000028u, 0x00001112u },  // 0000321A
        { 0x00000028u, 0x0000110Cu }, { 0x00000028u, 0x0000110Bu },  // 0000321C
        { 0x00000028u, 0x0000110Bu }, { 0x0000321Fu, 0x00000000u },  // 0000321E
        { 0x00000028u, 0x00004E00u }, { 0x00000028u, 0x00004E8Cu },  // 00003220
        { 0x00000028u, 0x00004E09u }, { 0x00000028u, 0x000056DBu },  // 00003222
        { 0x00000028u, 0x00004E94u }, { 0x00000028u, 0x0000516Du },  // 00003224
        { 0x00000028u, 0x00004E03u }, { 0x00000028u, 0x0000516Bu },  // 00003226
        { 0x00000028u, 0x00004E5Du }, { 0x00000028u, 0x00005341u },  // 00003228
        { 0x00000028u, 0x00006708u }, { 0x00000028u, 0x0000706Bu },  // 0000322A
        { 0x00000028u, 0x00006C34u }, { 0x00000028u, 0x00006728u },  // 0000322C
        { 0x00000028u, 0x000091D1u }, { 0x00000028u, 0x0000571Fu },  // 0000322E
        { 0x00000028u, 0x000065E5u }, { 0x00000028u, 0x0000682Au },  // 00003230
        { 0x00000028u, 0x00006709u }, { 0x00000028u, 0x0000793Eu },  // 00003232
        { 0x00000028u, 0x0000540Du }, { 0x00000028u, 0x00007279u },  // 00003234
        { 0x00000028u, 0x00008CA1u }, { 0x00000028u, 0x0000795Du },  // 00003236
        { 0x00000028u, 0x000052B4u }, { 0x00000028u, 0x00004EE3u },  // 00003238
        { 0x00000028u, 0x0000547Cu }, { 0x00000028u, 0x00005B66u },  // 0000323A
        { 0x00000028u, 0x000076E3u }, { 0x00000028u, 0x00004F01u },  // 0000323C
        { 0x00000028u, 0x00008CC7u }, { 0x00000028u, 0x00005354u },  // 0000323E
        { 0x00000028u, 0x0000796Du }, { 0x00000028u, 0x00004F11u },  // 00003240
        { 0x00000028u, 0x000081EAu }, { 0x00000028u, 0x000081F3u },  // 00003242
        { 0x00003244u, 0x00000000u }, { 0x00003245u, 0x00000000u },  // 00003244
        { 0x00003246u, 0x00000000u }, { 0x00003247u, 0x00000000u },  // 00003246
        { 0x00003248u, 0x00000000u }, { 0x00003249u, 0x00000000u },  // 00003248
        { 0x0000324Au, 0x00000000u }, { 0x0000324Bu, 0x00000000u },  // 0000324A
        { 0x0000324Cu, 0x00000000u }, { 0x0000324Du, 0x00000000u },  // 0000324C
        { 0x0000324Eu, 0x00000000u }, { 0x0000324Fu, 0x00000000u },  // 0000324E
        { 0x00000050u, 0x00000054u }, { 0x00000032u, 0x00000031u },  // 00003250
        { 0x00000032u, 0x00000032u }, { 0x00000032u, 0x00000033u },  // 00003252
        { 0x00000032u, 0x00000034u }, { 0x00000032u, 0x00000035u },  // 00003254
        { 0x00000032u, 0x00000036u }, { 0x00000032u, 0x00000037u },  // 00003256
        { 0x00000032u, 0x00000038u }, { 0x00000032u, 0x00000039u },  // 00003258
        { 0x00000033u, 0x00000030u }, { 0x00000033u, 0x00000031u },  // 0000325A
        { 0x00000033u, 0x00000032u }, { 0x00000033u, 0x00000033u },  // 0000325C
        { 0x00000033u, 0x00000034u }, { 0x00000033u, 0x00000035u },  // 0000325E
        { 0x00001100u, 0x00000000u }, { 0x00001102u, 0x00000000u },  // 00003260
        { 0x00001103u, 0x00000000u }, { 0x00001105u, 0x00000000u },  // 00003262
        { 0x00001106u, 0x00000000u }, { 0x00001107u, 0x00000000u },  // 00003264
        { 0x00001109u, 0x00000000u }, { 0x0000110Bu, 0x00000000u },  // 00003266
        { 0x0000110Cu, 0x00000000u }, { 0x0000110Eu, 0x00000000u },  // 00003268
        { 0x0000110Fu, 0x00000000u }, { 0x00001110u, 0x00000000u },  // 0000326A
        { 0x00001111u, 0x00000000u }, { 0x00001112u, 0x00000000u },  // 0000326C
        { 0x00001100u, 0x00001161u }, { 0x00001102u, 0x00001161u },  // 0000326E
        { 0x00001103u, 0x00001161u }, { 0x00001105u, 0x00001161u },  // 00003270
        { 0x00001106u, 0x00001161u }, { 0x00001107u, 0x00001161u },  // 00003272
        { 0x00001109u, 0x00001161u }, { 0x0000110Bu, 0x00001161u },  // 00003274
        { 0x0000110Cu, 0x00001161u }, { 0x0000110Eu, 0x00001161u },  // 00003276
        { 0x0000110Fu, 0x00001161u }, { 0x00001110u, 0x00001161u },  // 00003278
        { 0x00001111u, 0x00001161u }, { 0x00001112u, 0x00001161u },  // 0000327A
        { 0x0000110Eu, 0x00001161u }, { 0x0000110Cu, 0x0000116Eu },  // 0000327C
        { 0x0000327Eu, 0x00000000u }, { 0x0000327Fu, 0x00000000u },  // 0000327E
        { 0x00004E00u, 0x00000000u }, { 0x00004E8Cu, 0x00000000u },  // 00003280
        { 0x00004E09u, 0x00000000u }, { 0x000056DBu, 0x00000000u },  // 00003282
        { 0x00004E94u, 0x00000000u }, { 0x0000516Du, 0x00000000u },  // 00003284
        { 0x00004E03u, 0x00000000u }, { 0x0000516Bu, 0x00000000u },  // 00003286
        { 0x00004E5Du, 0x00000000u }, { 0x00005341u, 0x00000000u },  // 00003288
        { 0x00006708u, 0x00000000u }, { 0x0000706Bu, 0x00000000u },  // 0000328A
        { 0x00006C34u, 0x00000000u }, { 0x00006728u, 0x00000000u },  // 0000328C
        { 0x000091D1u, 0x00000000u }, { 0x0000571Fu, 0x00000000u },  // 0000328E
        { 0x000065E5u, 0x00000000u }, { 0x0000682Au, 0x00000000u },  // 00003290
        { 0x00006709u, 0x00000000u }, { 0x0000793Eu, 0x00000000u },  // 00003292
        { 0x0000540Du, 0x00000000u }, { 0x00007279u, 0x00000000u },  // 00003294
        { 0x00008CA1u, 0x00000000u }, { 0x0000795Du, 0x00000000u },  // 00003296
        { 0x000052B4u, 0x00000000u }, { 0x000079D8u, 0x00000000u },  // 00003298
        { 0x00007537u, 0x00000000u }, { 0x00005973u, 0x00000000u },  // 0000329A
        { 0x00009069u, 0x00000000u }, { 0x0000512Au, 0x00000000u },  // 0000329C
        { 0x00005370u, 0x00000000u }, { 0x00006CE8u, 0x00000000u },  // 0000329E
        { 0x00009805u, 0x00000000u }, { 0x00004F11u, 0x00000000u },  // 000032A0
        { 0x00005199u, 0x00000000u }, { 0x00006B63u, 0x00000000u },  // 000032A2
        { 0x00004E0Au, 0x00000000u }, { 0x00004E2Du, 0x00000000u },  // 000032A4
        { 0x00004E0Bu, 0x00000000u }, { 0x00005DE6u, 0x00000000u },  // 000032A6
        { 0x000053F3u, 0x00000000u }, { 0x0000533Bu, 0x00000000u },  // 000032A8
        { 0x00005B97u, 0x00000000u }, { 0x00005B66u, 0x00000000u },  // 000032AA
        { 0x000076E3u, 0x00000000u }, { 0x00004F01u, 0x00000000u },  // 000032AC
        { 0x00008CC7u, 0x00000000u }, { 0x00005354u, 0x00000000u },  // 000032AE
        { 0x0000591Cu, 0x00000000u }, { 0x00000033u, 0x00000036u },  // 000032B0
        { 0x00000033u, 0x00000037u }, { 0x00000033u, 0x00000038u },  // 000032B2
        { 0x00000033u, 0x00000039u }, { 0x00000034u, 0x00000030u },  // 000032B4
        { 0x00000034u, 0x00000031u }, { 0x00000034u, 0x00000032u },  // 000032B6
        { 0x00000034u, 0x00000033u }, { 0x00000034u, 0x00000034u },  // 000032B8
        { 0x00000034u, 0x00000035u }, { 0x00000034u, 0x00000036u },  // 000032BA
        { 0x00000034u, 0x00000037u }, { 0x00000034u, 0x00000038u },  // 000032BC
        { 0x00000034u, 0x00000039u }, { 0x00000035u, 0x00000030u },  // 000032BE
        { 0x00000031u, 0x00006708u }, { 0x00000032u, 0x00006708u },  // 000032C0
        { 0x00000033u, 0x00006708u }, { 0x00000034u, 0x00006708u },  // 000032C2
        { 0x00000035u, 0x00006708u }, { 0x00000036u, 0x00006708u },  // 000032C4
        { 0x00000037u, 0x00006708u }, { 0x00000038u, 0x00006708u },  // 000032C6
        { 0x00000039u, 0x00006708u }, { 0x00000031u, 0x00000030u },  // 000032C8
        { 0x00000031u, 0x00000031u }, { 0x00000031u, 0x00000032u },  // 000032CA
        { 0x00000048u, 0x00000067u }, { 0x00000065u, 0x00000072u },  // 000032CC
        { 0x00000065u, 0x00000056u }, { 0x0000004Cu, 0x00000054u },  // 000032CE
        { 0x000030A2u, 0x00000000u }, { 0x000030A4u, 0x00000000u },  // 000032D0
        { 0x000030A6u, 0x00000000u }, { 0x000030A8u, 0x00000000u },  // 000032D2
        { 0x000030AAu, 0x00000000u }, { 0x000030ABu, 0x00000000u },  // 000032D4
        { 0x000030ADu, 0x00000000u }, { 0x000030AFu, 0x00000000u },  // 000032D6
        { 0x000030B1u, 0x00000000u }, { 0x000030B3u, 0x00000000u },  // 000032D8
        { 0x000030B5u, 0x00000000u }, { 0x000030B7u, 0x00000000u },  // 000032DA
        { 0x000030B9u, 0x00000000u }, { 0x000030BBu, 0x00000000u },  // 000032DC
        { 0x000030BDu, 0x00000000u }, { 0x000030BFu, 0x00000000u },  // 000032DE
        { 0x000030C1u, 0x00000000u }, { 0x000030C4u, 0x00000000u },  // 000032E0
        { 0x000030C6u, 0x00000000u }, { 0x000030C8u, 0x00000000u },  // 000032E2
        { 0x000030CAu, 0x00000000u }, { 0x000030CBu, 0x00000000u },  // 000032E4
        { 0x000030CCu, 0x00000000u }, { 0x000030CDu, 0x00000000u },  // 000032E6
        { 0x000030CEu, 0x00000000u }, { 0x000030CFu, 0x00000000u },  // 000032E8
        { 0x000030D2u, 0x00000000u }, { 0x000030D5u, 0x00000000u },  // 000032EA
        { 0x000030D8u, 0x00000000u }, { 0x000030DBu, 0x00000000u },  // 000032EC
        { 0x000030DEu, 0x00000000u }, { 0x000030DFu, 0x00000000u },  // 000032EE
        { 0x000030E0u, 0x00000000u }, { 0x000030E1u, 0x00000000u },  // 000032F0
        { 0x000030E2u, 0x00000000u }, { 0x000030E4u, 0x00000000u },  // 000032F2
        { 0x000030E6u, 0x00000000u }, { 0x000030E8u, 0x00000000u },  // 000032F4
        { 0x000030E9u, 0x00000000u }, { 0x000030EAu, 0x00000000u },  // 000032F6
        { 0x000030EBu, 0x00000000u }, { 0x000030ECu, 0x00000000u },  // 000032F8
        { 0x000030EDu, 0x00000000u }, { 0x000030EFu, 0x00000000u },  // 000032FA
        { 0x000030F0u, 0x00000000u }, { 0x000030F1u, 0x00000000u },  // 000032FC
        { 0x000030F2u, 0x00000000u }, { 0x000032FFu, 0x00000000u }
    };

  }; // namespace
}; // namespace

dload(Babylon::Module::Enclosed_CJK_Letters_and_Months3200);
