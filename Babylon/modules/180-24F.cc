/*$Id: UnicodePluginGenerator.pl,v 1.11 2004/01/28 12:39:04 tobias Exp 180-24F.cc
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
    class Latin_ExtendedB180 : public Babylon::Block
    {
      public:
        void clean() { };

        Latin_ExtendedB180() :
        my_first_letter(0x180),
        my_last_letter(0x24F)
        // my_version="4.0" // Not yet supported!
        {
            {
                my_composeMap[std::make_pair(0x000001A0, 0x00000300)] = 0x1EDC;
                my_composeMap[std::make_pair(0x000001A0, 0x00000301)] = 0x1EDA;
                my_composeMap[std::make_pair(0x000001A0, 0x00000303)] = 0x1EE0;
                my_composeMap[std::make_pair(0x000001A0, 0x00000309)] = 0x1EDE;
                my_composeMap[std::make_pair(0x000001A0, 0x00000323)] = 0x1EE2;
                my_composeMap[std::make_pair(0x000001A1, 0x00000300)] = 0x1EDD;
                my_composeMap[std::make_pair(0x000001A1, 0x00000301)] = 0x1EDB;
                my_composeMap[std::make_pair(0x000001A1, 0x00000303)] = 0x1EE1;
                my_composeMap[std::make_pair(0x000001A1, 0x00000309)] = 0x1EDF;
                my_composeMap[std::make_pair(0x000001A1, 0x00000323)] = 0x1EE3;
                my_composeMap[std::make_pair(0x000001AF, 0x00000300)] = 0x1EEA;
                my_composeMap[std::make_pair(0x000001AF, 0x00000301)] = 0x1EE8;
                my_composeMap[std::make_pair(0x000001AF, 0x00000303)] = 0x1EEE;
                my_composeMap[std::make_pair(0x000001AF, 0x00000309)] = 0x1EEC;
                my_composeMap[std::make_pair(0x000001AF, 0x00000323)] = 0x1EF0;
                my_composeMap[std::make_pair(0x000001B0, 0x00000300)] = 0x1EEB;
                my_composeMap[std::make_pair(0x000001B0, 0x00000301)] = 0x1EE9;
                my_composeMap[std::make_pair(0x000001B0, 0x00000303)] = 0x1EEF;
                my_composeMap[std::make_pair(0x000001B0, 0x00000309)] = 0x1EED;
                my_composeMap[std::make_pair(0x000001B0, 0x00000323)] = 0x1EF1;
                my_composeMap[std::make_pair(0x000001B7, 0x0000030C)] = 0x01EE;
                my_composeMap[std::make_pair(0x000001EA, 0x00000304)] = 0x01EC;
                my_composeMap[std::make_pair(0x000001EB, 0x00000304)] = 0x01ED;
                my_composeMap[std::make_pair(0x00000226, 0x00000304)] = 0x01E0;
                my_composeMap[std::make_pair(0x00000227, 0x00000304)] = 0x01E1;
                my_composeMap[std::make_pair(0x00000228, 0x00000306)] = 0x1E1C;
                my_composeMap[std::make_pair(0x00000229, 0x00000306)] = 0x1E1D;
                my_composeMap[std::make_pair(0x0000022E, 0x00000304)] = 0x0230;
                my_composeMap[std::make_pair(0x0000022F, 0x00000304)] = 0x0231;
            }
        }

        ~Latin_ExtendedB180() { }

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
        return "Latin Extended-B";
    }

        bool is_defined(const UCS4 uc) const
        {
            return (my_is_defined.test(uc - my_first_letter));
        }

        UCS4 uppercase(const UCS4 uc) const
        {
            return Latin_ExtendedB180::my_upper[uc - my_first_letter];
        }

        UCS4 lowercase(const UCS4 uc) const
        {
            return Latin_ExtendedB180::my_lower[uc - my_first_letter];
        }

        UCS4 titlecase(const UCS4 uc) const
        {
            return Latin_ExtendedB180::my_title[uc - my_first_letter];
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
            return Babylon::Gen_Cat(Latin_ExtendedB180::my_cat[uc - my_first_letter]);
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
            return Babylon::Char_Decomp(Latin_ExtendedB180::my_decomp[uc - my_first_letter]);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            Babylon::UTF32_string us;
            us.resize(2);
            us[0] = Latin_ExtendedB180::my_decompStr[uc - my_first_letter][0];
            us[1] = Latin_ExtendedB180::my_decompStr[uc - my_first_letter][1];
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
            return Babylon::Line_Break(Latin_ExtendedB180::my_lb[uc - my_first_letter]);
        }

        EA_Width EA_width(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return EA_WIDTH_MAX;
            return Babylon::EA_Width(Latin_ExtendedB180::my_ea[uc - my_first_letter]);
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
        Latin_ExtendedB180(const Latin_ExtendedB180 &) ; // no implementaion!

    // members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const std::bitset<208> my_is_defined;
        static const UCS4 my_upper[208];
        static const UCS4 my_lower[208];
        static const UCS4 my_title[208];
        static const unsigned char my_cat[208];
        static const unsigned char my_decomp[208];
        static const UCS2 my_decompStr[208][2];
        static const unsigned char my_lb[208];
        static const unsigned char my_ea[208];
        std::map<std::pair<UCS4, UCS4>, UCS4> my_composeMap;
    }; // class Latin_ExtendedB180

    const std::bitset<208> Latin_ExtendedB180::my_is_defined(std::string("0000000000000000000000000111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"));

    const UCS4 Latin_ExtendedB180::my_upper[] =
    {
        0x0180, 0x0181, 0x0182, 0x0182, 0x0184, 0x0184, 0x0186, 0x0187, 
        0x0187, 0x0189, 0x018A, 0x018B, 0x018B, 0x018D, 0x018E, 0x018F, 
        0x0190, 0x0191, 0x0191, 0x0193, 0x0194, 0x01F6, 0x0196, 0x0197, 
        0x0198, 0x0198, 0x019A, 0x019B, 0x019C, 0x019D, 0x0220, 0x019F, 
        0x01A0, 0x01A0, 0x01A2, 0x01A2, 0x01A4, 0x01A4, 0x01A6, 0x01A7, 
        0x01A7, 0x01A9, 0x01AA, 0x01AB, 0x01AC, 0x01AC, 0x01AE, 0x01AF, 
        0x01AF, 0x01B1, 0x01B2, 0x01B3, 0x01B3, 0x01B5, 0x01B5, 0x01B7, 
        0x01B8, 0x01B8, 0x01BA, 0x01BB, 0x01BC, 0x01BC, 0x01BE, 0x01F7, 
        0x01C0, 0x01C1, 0x01C2, 0x01C3, 0x01C4, 0x01C4, 0x01C4, 0x01C7, 
        0x01C7, 0x01C7, 0x01CA, 0x01CA, 0x01CA, 0x01CD, 0x01CD, 0x01CF, 
        0x01CF, 0x01D1, 0x01D1, 0x01D3, 0x01D3, 0x01D5, 0x01D5, 0x01D7, 
        0x01D7, 0x01D9, 0x01D9, 0x01DB, 0x01DB, 0x018E, 0x01DE, 0x01DE, 
        0x01E0, 0x01E0, 0x01E2, 0x01E2, 0x01E4, 0x01E4, 0x01E6, 0x01E6, 
        0x01E8, 0x01E8, 0x01EA, 0x01EA, 0x01EC, 0x01EC, 0x01EE, 0x01EE, 
        0x01F0, 0x01F1, 0x01F1, 0x01F1, 0x01F4, 0x01F4, 0x01F6, 0x01F7, 
        0x01F8, 0x01F8, 0x01FA, 0x01FA, 0x01FC, 0x01FC, 0x01FE, 0x01FE, 
        0x0200, 0x0200, 0x0202, 0x0202, 0x0204, 0x0204, 0x0206, 0x0206, 
        0x0208, 0x0208, 0x020A, 0x020A, 0x020C, 0x020C, 0x020E, 0x020E, 
        0x0210, 0x0210, 0x0212, 0x0212, 0x0214, 0x0214, 0x0216, 0x0216, 
        0x0218, 0x0218, 0x021A, 0x021A, 0x021C, 0x021C, 0x021E, 0x021E, 
        0x0220, 0x0221, 0x0222, 0x0222, 0x0224, 0x0224, 0x0226, 0x0226, 
        0x0228, 0x0228, 0x022A, 0x022A, 0x022C, 0x022C, 0x022E, 0x022E, 
        0x0230, 0x0230, 0x0232, 0x0232, 0x0234, 0x0235, 0x0236, 0x0237, 
        0x0238, 0x0239, 0x023A, 0x023B, 0x023C, 0x023D, 0x023E, 0x023F, 
        0x0240, 0x0241, 0x0242, 0x0243, 0x0244, 0x0245, 0x0246, 0x0247, 
        0x0248, 0x0249, 0x024A, 0x024B, 0x024C, 0x024D, 0x024E, 0x024F
    };

    const UCS4 Latin_ExtendedB180::my_lower[] =
    {
        0x0180, 0x0253, 0x0183, 0x0183, 0x0185, 0x0185, 0x0254, 0x0188, 
        0x0188, 0x0256, 0x0257, 0x018C, 0x018C, 0x018D, 0x01DD, 0x0259, 
        0x025B, 0x0192, 0x0192, 0x0260, 0x0263, 0x0195, 0x0269, 0x0268, 
        0x0199, 0x0199, 0x019A, 0x019B, 0x026F, 0x0272, 0x019E, 0x0275, 
        0x01A1, 0x01A1, 0x01A3, 0x01A3, 0x01A5, 0x01A5, 0x0280, 0x01A8, 
        0x01A8, 0x0283, 0x01AA, 0x01AB, 0x01AD, 0x01AD, 0x0288, 0x01B0, 
        0x01B0, 0x028A, 0x028B, 0x01B4, 0x01B4, 0x01B6, 0x01B6, 0x0292, 
        0x01B9, 0x01B9, 0x01BA, 0x01BB, 0x01BD, 0x01BD, 0x01BE, 0x01BF, 
        0x01C0, 0x01C1, 0x01C2, 0x01C3, 0x01C6, 0x01C6, 0x01C6, 0x01C9, 
        0x01C9, 0x01C9, 0x01CC, 0x01CC, 0x01CC, 0x01CE, 0x01CE, 0x01D0, 
        0x01D0, 0x01D2, 0x01D2, 0x01D4, 0x01D4, 0x01D6, 0x01D6, 0x01D8, 
        0x01D8, 0x01DA, 0x01DA, 0x01DC, 0x01DC, 0x01DD, 0x01DF, 0x01DF, 
        0x01E1, 0x01E1, 0x01E3, 0x01E3, 0x01E5, 0x01E5, 0x01E7, 0x01E7, 
        0x01E9, 0x01E9, 0x01EB, 0x01EB, 0x01ED, 0x01ED, 0x01EF, 0x01EF, 
        0x01F0, 0x01F3, 0x01F3, 0x01F3, 0x01F5, 0x01F5, 0x0195, 0x01BF, 
        0x01F9, 0x01F9, 0x01FB, 0x01FB, 0x01FD, 0x01FD, 0x01FF, 0x01FF, 
        0x0201, 0x0201, 0x0203, 0x0203, 0x0205, 0x0205, 0x0207, 0x0207, 
        0x0209, 0x0209, 0x020B, 0x020B, 0x020D, 0x020D, 0x020F, 0x020F, 
        0x0211, 0x0211, 0x0213, 0x0213, 0x0215, 0x0215, 0x0217, 0x0217, 
        0x0219, 0x0219, 0x021B, 0x021B, 0x021D, 0x021D, 0x021F, 0x021F, 
        0x019E, 0x0221, 0x0223, 0x0223, 0x0225, 0x0225, 0x0227, 0x0227, 
        0x0229, 0x0229, 0x022B, 0x022B, 0x022D, 0x022D, 0x022F, 0x022F, 
        0x0231, 0x0231, 0x0233, 0x0233, 0x0234, 0x0235, 0x0236, 0x0237, 
        0x0238, 0x0239, 0x023A, 0x023B, 0x023C, 0x023D, 0x023E, 0x023F, 
        0x0240, 0x0241, 0x0242, 0x0243, 0x0244, 0x0245, 0x0246, 0x0247, 
        0x0248, 0x0249, 0x024A, 0x024B, 0x024C, 0x024D, 0x024E, 0x024F
    };

    const UCS4 Latin_ExtendedB180::my_title[] =
    {
        0x0180, 0x0181, 0x0182, 0x0182, 0x0184, 0x0184, 0x0186, 0x0187, 
        0x0187, 0x0189, 0x018A, 0x018B, 0x018B, 0x018D, 0x018E, 0x018F, 
        0x0190, 0x0191, 0x0191, 0x0193, 0x0194, 0x01F6, 0x0196, 0x0197, 
        0x0198, 0x0198, 0x019A, 0x019B, 0x019C, 0x019D, 0x0220, 0x019F, 
        0x01A0, 0x01A0, 0x01A2, 0x01A2, 0x01A4, 0x01A4, 0x01A6, 0x01A7, 
        0x01A7, 0x01A9, 0x01AA, 0x01AB, 0x01AC, 0x01AC, 0x01AE, 0x01AF, 
        0x01AF, 0x01B1, 0x01B2, 0x01B3, 0x01B3, 0x01B5, 0x01B5, 0x01B7, 
        0x01B8, 0x01B8, 0x01BA, 0x01BB, 0x01BC, 0x01BC, 0x01BE, 0x01F7, 
        0x01C0, 0x01C1, 0x01C2, 0x01C3, 0x01C5, 0x01C5, 0x01C5, 0x01C8, 
        0x01C8, 0x01C8, 0x01CB, 0x01CB, 0x01CB, 0x01CD, 0x01CD, 0x01CF, 
        0x01CF, 0x01D1, 0x01D1, 0x01D3, 0x01D3, 0x01D5, 0x01D5, 0x01D7, 
        0x01D7, 0x01D9, 0x01D9, 0x01DB, 0x01DB, 0x018E, 0x01DE, 0x01DE, 
        0x01E0, 0x01E0, 0x01E2, 0x01E2, 0x01E4, 0x01E4, 0x01E6, 0x01E6, 
        0x01E8, 0x01E8, 0x01EA, 0x01EA, 0x01EC, 0x01EC, 0x01EE, 0x01EE, 
        0x01F0, 0x01F2, 0x01F2, 0x01F2, 0x01F4, 0x01F4, 0x01F6, 0x01F7, 
        0x01F8, 0x01F8, 0x01FA, 0x01FA, 0x01FC, 0x01FC, 0x01FE, 0x01FE, 
        0x0200, 0x0200, 0x0202, 0x0202, 0x0204, 0x0204, 0x0206, 0x0206, 
        0x0208, 0x0208, 0x020A, 0x020A, 0x020C, 0x020C, 0x020E, 0x020E, 
        0x0210, 0x0210, 0x0212, 0x0212, 0x0214, 0x0214, 0x0216, 0x0216, 
        0x0218, 0x0218, 0x021A, 0x021A, 0x021C, 0x021C, 0x021E, 0x021E, 
        0x0220, 0x0221, 0x0222, 0x0222, 0x0224, 0x0224, 0x0226, 0x0226, 
        0x0228, 0x0228, 0x022A, 0x022A, 0x022C, 0x022C, 0x022E, 0x022E, 
        0x0230, 0x0230, 0x0232, 0x0232, 0x0234, 0x0235, 0x0236, 0x0237, 
        0x0238, 0x0239, 0x023A, 0x023B, 0x023C, 0x023D, 0x023E, 0x023F, 
        0x0240, 0x0241, 0x0242, 0x0243, 0x0244, 0x0245, 0x0246, 0x0247, 
        0x0248, 0x0249, 0x024A, 0x024B, 0x024C, 0x024D, 0x024E, 0x024F
    };

    const unsigned char Latin_ExtendedB180::my_cat[] =
    {
        CAT_Ll, CAT_Lu, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Lu, 
        CAT_Ll, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Ll, CAT_Ll, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Lu, CAT_Lu, CAT_Ll, CAT_Lu, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Lu, 
        CAT_Ll, CAT_Lu, CAT_Ll, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Lu, 
        CAT_Ll, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, 
        CAT_Lu, CAT_Ll, CAT_Ll, CAT_Lo, CAT_Lu, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lu, CAT_Lt, CAT_Ll, CAT_Lu, 
        CAT_Lt, CAT_Ll, CAT_Lu, CAT_Lt, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, 
        CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, 
        CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Ll, CAT_Lu, CAT_Lt, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Lu, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
        CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll
    };

    const unsigned char Latin_ExtendedB180::my_decomp[] = {
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
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
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

    const UCS2 Latin_ExtendedB180::my_decompStr[][2] =
    {
        { 0x00000180u, 0x00000000u }, { 0x00000181u, 0x00000000u },  // 00000180
        { 0x00000182u, 0x00000000u }, { 0x00000183u, 0x00000000u },  // 00000182
        { 0x00000184u, 0x00000000u }, { 0x00000185u, 0x00000000u },  // 00000184
        { 0x00000186u, 0x00000000u }, { 0x00000187u, 0x00000000u },  // 00000186
        { 0x00000188u, 0x00000000u }, { 0x00000189u, 0x00000000u },  // 00000188
        { 0x0000018Au, 0x00000000u }, { 0x0000018Bu, 0x00000000u },  // 0000018A
        { 0x0000018Cu, 0x00000000u }, { 0x0000018Du, 0x00000000u },  // 0000018C
        { 0x0000018Eu, 0x00000000u }, { 0x0000018Fu, 0x00000000u },  // 0000018E
        { 0x00000190u, 0x00000000u }, { 0x00000191u, 0x00000000u },  // 00000190
        { 0x00000192u, 0x00000000u }, { 0x00000193u, 0x00000000u },  // 00000192
        { 0x00000194u, 0x00000000u }, { 0x00000195u, 0x00000000u },  // 00000194
        { 0x00000196u, 0x00000000u }, { 0x00000197u, 0x00000000u },  // 00000196
        { 0x00000198u, 0x00000000u }, { 0x00000199u, 0x00000000u },  // 00000198
        { 0x0000019Au, 0x00000000u }, { 0x0000019Bu, 0x00000000u },  // 0000019A
        { 0x0000019Cu, 0x00000000u }, { 0x0000019Du, 0x00000000u },  // 0000019C
        { 0x0000019Eu, 0x00000000u }, { 0x0000019Fu, 0x00000000u },  // 0000019E
        { 0x0000004Fu, 0x0000031Bu }, { 0x0000006Fu, 0x0000031Bu },  // 000001A0
        { 0x000001A2u, 0x00000000u }, { 0x000001A3u, 0x00000000u },  // 000001A2
        { 0x000001A4u, 0x00000000u }, { 0x000001A5u, 0x00000000u },  // 000001A4
        { 0x000001A6u, 0x00000000u }, { 0x000001A7u, 0x00000000u },  // 000001A6
        { 0x000001A8u, 0x00000000u }, { 0x000001A9u, 0x00000000u },  // 000001A8
        { 0x000001AAu, 0x00000000u }, { 0x000001ABu, 0x00000000u },  // 000001AA
        { 0x000001ACu, 0x00000000u }, { 0x000001ADu, 0x00000000u },  // 000001AC
        { 0x000001AEu, 0x00000000u }, { 0x00000055u, 0x0000031Bu },  // 000001AE
        { 0x00000075u, 0x0000031Bu }, { 0x000001B1u, 0x00000000u },  // 000001B0
        { 0x000001B2u, 0x00000000u }, { 0x000001B3u, 0x00000000u },  // 000001B2
        { 0x000001B4u, 0x00000000u }, { 0x000001B5u, 0x00000000u },  // 000001B4
        { 0x000001B6u, 0x00000000u }, { 0x000001B7u, 0x00000000u },  // 000001B6
        { 0x000001B8u, 0x00000000u }, { 0x000001B9u, 0x00000000u },  // 000001B8
        { 0x000001BAu, 0x00000000u }, { 0x000001BBu, 0x00000000u },  // 000001BA
        { 0x000001BCu, 0x00000000u }, { 0x000001BDu, 0x00000000u },  // 000001BC
        { 0x000001BEu, 0x00000000u }, { 0x000001BFu, 0x00000000u },  // 000001BE
        { 0x000001C0u, 0x00000000u }, { 0x000001C1u, 0x00000000u },  // 000001C0
        { 0x000001C2u, 0x00000000u }, { 0x000001C3u, 0x00000000u },  // 000001C2
        { 0x00000044u, 0x0000017Du }, { 0x00000044u, 0x0000017Eu },  // 000001C4
        { 0x00000064u, 0x0000017Eu }, { 0x0000004Cu, 0x0000004Au },  // 000001C6
        { 0x0000004Cu, 0x0000006Au }, { 0x0000006Cu, 0x0000006Au },  // 000001C8
        { 0x0000004Eu, 0x0000004Au }, { 0x0000004Eu, 0x0000006Au },  // 000001CA
        { 0x0000006Eu, 0x0000006Au }, { 0x00000041u, 0x0000030Cu },  // 000001CC
        { 0x00000061u, 0x0000030Cu }, { 0x00000049u, 0x0000030Cu },  // 000001CE
        { 0x00000069u, 0x0000030Cu }, { 0x0000004Fu, 0x0000030Cu },  // 000001D0
        { 0x0000006Fu, 0x0000030Cu }, { 0x00000055u, 0x0000030Cu },  // 000001D2
        { 0x00000075u, 0x0000030Cu }, { 0x000000DCu, 0x00000304u },  // 000001D4
        { 0x000000FCu, 0x00000304u }, { 0x000000DCu, 0x00000301u },  // 000001D6
        { 0x000000FCu, 0x00000301u }, { 0x000000DCu, 0x0000030Cu },  // 000001D8
        { 0x000000FCu, 0x0000030Cu }, { 0x000000DCu, 0x00000300u },  // 000001DA
        { 0x000000FCu, 0x00000300u }, { 0x000001DDu, 0x00000000u },  // 000001DC
        { 0x000000C4u, 0x00000304u }, { 0x000000E4u, 0x00000304u },  // 000001DE
        { 0x00000226u, 0x00000304u }, { 0x00000227u, 0x00000304u },  // 000001E0
        { 0x000000C6u, 0x00000304u }, { 0x000000E6u, 0x00000304u },  // 000001E2
        { 0x000001E4u, 0x00000000u }, { 0x000001E5u, 0x00000000u },  // 000001E4
        { 0x00000047u, 0x0000030Cu }, { 0x00000067u, 0x0000030Cu },  // 000001E6
        { 0x0000004Bu, 0x0000030Cu }, { 0x0000006Bu, 0x0000030Cu },  // 000001E8
        { 0x0000004Fu, 0x00000328u }, { 0x0000006Fu, 0x00000328u },  // 000001EA
        { 0x000001EAu, 0x00000304u }, { 0x000001EBu, 0x00000304u },  // 000001EC
        { 0x000001B7u, 0x0000030Cu }, { 0x00000292u, 0x0000030Cu },  // 000001EE
        { 0x0000006Au, 0x0000030Cu }, { 0x00000044u, 0x0000005Au },  // 000001F0
        { 0x00000044u, 0x0000007Au }, { 0x00000064u, 0x0000007Au },  // 000001F2
        { 0x00000047u, 0x00000301u }, { 0x00000067u, 0x00000301u },  // 000001F4
        { 0x000001F6u, 0x00000000u }, { 0x000001F7u, 0x00000000u },  // 000001F6
        { 0x0000004Eu, 0x00000300u }, { 0x0000006Eu, 0x00000300u },  // 000001F8
        { 0x000000C5u, 0x00000301u }, { 0x000000E5u, 0x00000301u },  // 000001FA
        { 0x000000C6u, 0x00000301u }, { 0x000000E6u, 0x00000301u },  // 000001FC
        { 0x000000D8u, 0x00000301u }, { 0x000000F8u, 0x00000301u },  // 000001FE
        { 0x00000041u, 0x0000030Fu }, { 0x00000061u, 0x0000030Fu },  // 00000200
        { 0x00000041u, 0x00000311u }, { 0x00000061u, 0x00000311u },  // 00000202
        { 0x00000045u, 0x0000030Fu }, { 0x00000065u, 0x0000030Fu },  // 00000204
        { 0x00000045u, 0x00000311u }, { 0x00000065u, 0x00000311u },  // 00000206
        { 0x00000049u, 0x0000030Fu }, { 0x00000069u, 0x0000030Fu },  // 00000208
        { 0x00000049u, 0x00000311u }, { 0x00000069u, 0x00000311u },  // 0000020A
        { 0x0000004Fu, 0x0000030Fu }, { 0x0000006Fu, 0x0000030Fu },  // 0000020C
        { 0x0000004Fu, 0x00000311u }, { 0x0000006Fu, 0x00000311u },  // 0000020E
        { 0x00000052u, 0x0000030Fu }, { 0x00000072u, 0x0000030Fu },  // 00000210
        { 0x00000052u, 0x00000311u }, { 0x00000072u, 0x00000311u },  // 00000212
        { 0x00000055u, 0x0000030Fu }, { 0x00000075u, 0x0000030Fu },  // 00000214
        { 0x00000055u, 0x00000311u }, { 0x00000075u, 0x00000311u },  // 00000216
        { 0x00000053u, 0x00000326u }, { 0x00000073u, 0x00000326u },  // 00000218
        { 0x00000054u, 0x00000326u }, { 0x00000074u, 0x00000326u },  // 0000021A
        { 0x0000021Cu, 0x00000000u }, { 0x0000021Du, 0x00000000u },  // 0000021C
        { 0x00000048u, 0x0000030Cu }, { 0x00000068u, 0x0000030Cu },  // 0000021E
        { 0x00000220u, 0x00000000u }, { 0x00000221u, 0x00000000u },  // 00000220
        { 0x00000222u, 0x00000000u }, { 0x00000223u, 0x00000000u },  // 00000222
        { 0x00000224u, 0x00000000u }, { 0x00000225u, 0x00000000u },  // 00000224
        { 0x00000041u, 0x00000307u }, { 0x00000061u, 0x00000307u },  // 00000226
        { 0x00000045u, 0x00000327u }, { 0x00000065u, 0x00000327u },  // 00000228
        { 0x000000D6u, 0x00000304u }, { 0x000000F6u, 0x00000304u },  // 0000022A
        { 0x000000D5u, 0x00000304u }, { 0x000000F5u, 0x00000304u },  // 0000022C
        { 0x0000004Fu, 0x00000307u }, { 0x0000006Fu, 0x00000307u },  // 0000022E
        { 0x0000022Eu, 0x00000304u }, { 0x0000022Fu, 0x00000304u },  // 00000230
        { 0x00000059u, 0x00000304u }, { 0x00000079u, 0x00000304u },  // 00000232
        { 0x00000234u, 0x00000000u }, { 0x00000235u, 0x00000000u },  // 00000234
        { 0x00000236u, 0x00000000u }, { 0x00000237u, 0x00000000u },  // 00000236
        { 0x00000238u, 0x00000000u }, { 0x00000239u, 0x00000000u },  // 00000238
        { 0x0000023Au, 0x00000000u }, { 0x0000023Bu, 0x00000000u },  // 0000023A
        { 0x0000023Cu, 0x00000000u }, { 0x0000023Du, 0x00000000u },  // 0000023C
        { 0x0000023Eu, 0x00000000u }, { 0x0000023Fu, 0x00000000u },  // 0000023E
        { 0x00000240u, 0x00000000u }, { 0x00000241u, 0x00000000u },  // 00000240
        { 0x00000242u, 0x00000000u }, { 0x00000243u, 0x00000000u },  // 00000242
        { 0x00000244u, 0x00000000u }, { 0x00000245u, 0x00000000u },  // 00000244
        { 0x00000246u, 0x00000000u }, { 0x00000247u, 0x00000000u },  // 00000246
        { 0x00000248u, 0x00000000u }, { 0x00000249u, 0x00000000u },  // 00000248
        { 0x0000024Au, 0x00000000u }, { 0x0000024Bu, 0x00000000u },  // 0000024A
        { 0x0000024Cu, 0x00000000u }, { 0x0000024Du, 0x00000000u },  // 0000024C
        { 0x0000024Eu, 0x00000000u }, { 0x0000024Fu, 0x00000000u }
    };

    const unsigned char Latin_ExtendedB180::my_lb[] =
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
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AI, LB_AL, 
        LB_AI, LB_AL, LB_AI, LB_AL, LB_AI, LB_AL, LB_AI, LB_AL, 
        LB_AI, LB_AL, LB_AI, LB_AL, LB_AI, LB_AL, LB_AL, LB_AL, 
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
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL
    };

    const unsigned char Latin_ExtendedB180::my_ea[] =
    {
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
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, 
        EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, 
        EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, 
        EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, 
        EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
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
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N
    };

  }; // namespace
}; // namespace

dload(Babylon::Module::Latin_ExtendedB180);
