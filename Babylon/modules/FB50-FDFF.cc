/*$Id: UnicodePluginGenerator.pl,v 1.11 2004/01/28 12:39:04 tobias Exp FB50-FDFF.cc
 *
 * This source file is a part of the Fresco Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Wed, 28 Jan 2004 20:49:49 +0100.
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
    class Arabic_Presentation_FormsAFB50 : public Babylon::Block
    {
      public:
        void clean() { };

        Arabic_Presentation_FormsAFB50() :
        my_first_letter(0xFB50),
        my_last_letter(0xFDFF)
        // my_version="4.0" // Not yet supported!
        {
        }

        ~Arabic_Presentation_FormsAFB50() { }

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
        return "Arabic Presentation Forms-A";
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
            return Babylon::Gen_Cat(Arabic_Presentation_FormsAFB50::my_cat[uc - my_first_letter]);
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
            return Arabic_Presentation_FormsAFB50::my_bidir[uc - my_first_letter];
        }

        Char_Decomp decomp_type(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return DECOMP_MAX;
            return Babylon::Char_Decomp(Arabic_Presentation_FormsAFB50::my_decomp[uc - my_first_letter]);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            Babylon::UTF32_string us;
            us.resize(2);
            us[0] = Arabic_Presentation_FormsAFB50::my_decompStr[uc - my_first_letter][0];
            us[1] = Arabic_Presentation_FormsAFB50::my_decompStr[uc - my_first_letter][1];

            switch (uc)
            {

            case 0xFC5E:
                us.resize(3);
                us[2u] = 0x0651u;
                break;

            case 0xFC5F:
                us.resize(3);
                us[2u] = 0x0651u;
                break;

            case 0xFC60:
                us.resize(3);
                us[2u] = 0x0651u;
                break;

            case 0xFC61:
                us.resize(3);
                us[2u] = 0x0651u;
                break;

            case 0xFC62:
                us.resize(3);
                us[2u] = 0x0651u;
                break;

            case 0xFC63:
                us.resize(3);
                us[2u] = 0x0670u;
                break;

            case 0xFCF2:
                us.resize(3);
                us[2u] = 0x0651u;
                break;

            case 0xFCF3:
                us.resize(3);
                us[2u] = 0x0651u;
                break;

            case 0xFCF4:
                us.resize(3);
                us[2u] = 0x0651u;
                break;

            case 0xFD50:
                us.resize(3);
                us[2u] = 0x0645u;
                break;

            case 0xFD51:
                us.resize(3);
                us[2u] = 0x062Cu;
                break;

            case 0xFD52:
                us.resize(3);
                us[2u] = 0x062Cu;
                break;

            case 0xFD53:
                us.resize(3);
                us[2u] = 0x0645u;
                break;

            case 0xFD54:
                us.resize(3);
                us[2u] = 0x0645u;
                break;

            case 0xFD55:
                us.resize(3);
                us[2u] = 0x062Cu;
                break;

            case 0xFD56:
                us.resize(3);
                us[2u] = 0x062Du;
                break;

            case 0xFD57:
                us.resize(3);
                us[2u] = 0x062Eu;
                break;

            case 0xFD58:
                us.resize(3);
                us[2u] = 0x062Du;
                break;

            case 0xFD59:
                us.resize(3);
                us[2u] = 0x062Du;
                break;

            case 0xFD5A:
                us.resize(3);
                us[2u] = 0x064Au;
                break;

            case 0xFD5B:
                us.resize(3);
                us[2u] = 0x0649u;
                break;

            case 0xFD5C:
                us.resize(3);
                us[2u] = 0x062Cu;
                break;

            case 0xFD5D:
                us.resize(3);
                us[2u] = 0x062Du;
                break;

            case 0xFD5E:
                us.resize(3);
                us[2u] = 0x0649u;
                break;

            case 0xFD5F:
                us.resize(3);
                us[2u] = 0x062Du;
                break;

            case 0xFD60:
                us.resize(3);
                us[2u] = 0x062Du;
                break;

            case 0xFD61:
                us.resize(3);
                us[2u] = 0x062Cu;
                break;

            case 0xFD62:
                us.resize(3);
                us[2u] = 0x0645u;
                break;

            case 0xFD63:
                us.resize(3);
                us[2u] = 0x0645u;
                break;

            case 0xFD64:
                us.resize(3);
                us[2u] = 0x062Du;
                break;

            case 0xFD65:
                us.resize(3);
                us[2u] = 0x062Du;
                break;

            case 0xFD66:
                us.resize(3);
                us[2u] = 0x0645u;
                break;

            case 0xFD67:
                us.resize(3);
                us[2u] = 0x0645u;
                break;

            case 0xFD68:
                us.resize(3);
                us[2u] = 0x0645u;
                break;

            case 0xFD69:
                us.resize(3);
                us[2u] = 0x064Au;
                break;

            case 0xFD6A:
                us.resize(3);
                us[2u] = 0x062Eu;
                break;

            case 0xFD6B:
                us.resize(3);
                us[2u] = 0x062Eu;
                break;

            case 0xFD6C:
                us.resize(3);
                us[2u] = 0x0645u;
                break;

            case 0xFD6D:
                us.resize(3);
                us[2u] = 0x0645u;
                break;

            case 0xFD6E:
                us.resize(3);
                us[2u] = 0x0649u;
                break;

            case 0xFD6F:
                us.resize(3);
                us[2u] = 0x0645u;
                break;

            case 0xFD70:
                us.resize(3);
                us[2u] = 0x0645u;
                break;

            case 0xFD71:
                us.resize(3);
                us[2u] = 0x062Du;
                break;

            case 0xFD72:
                us.resize(3);
                us[2u] = 0x062Du;
                break;

            case 0xFD73:
                us.resize(3);
                us[2u] = 0x0645u;
                break;

            case 0xFD74:
                us.resize(3);
                us[2u] = 0x064Au;
                break;

            case 0xFD75:
                us.resize(3);
                us[2u] = 0x0645u;
                break;

            case 0xFD76:
                us.resize(3);
                us[2u] = 0x0645u;
                break;

            case 0xFD77:
                us.resize(3);
                us[2u] = 0x0645u;
                break;

            case 0xFD78:
                us.resize(3);
                us[2u] = 0x0649u;
                break;

            case 0xFD79:
                us.resize(3);
                us[2u] = 0x0645u;
                break;

            case 0xFD7A:
                us.resize(3);
                us[2u] = 0x064Au;
                break;

            case 0xFD7B:
                us.resize(3);
                us[2u] = 0x0649u;
                break;

            case 0xFD7C:
                us.resize(3);
                us[2u] = 0x0645u;
                break;

            case 0xFD7D:
                us.resize(3);
                us[2u] = 0x0645u;
                break;

            case 0xFD7E:
                us.resize(3);
                us[2u] = 0x062Du;
                break;

            case 0xFD7F:
                us.resize(3);
                us[2u] = 0x0645u;
                break;

            case 0xFD80:
                us.resize(3);
                us[2u] = 0x0645u;
                break;

            case 0xFD81:
                us.resize(3);
                us[2u] = 0x064Au;
                break;

            case 0xFD82:
                us.resize(3);
                us[2u] = 0x0649u;
                break;

            case 0xFD83:
                us.resize(3);
                us[2u] = 0x062Cu;
                break;

            case 0xFD84:
                us.resize(3);
                us[2u] = 0x062Cu;
                break;

            case 0xFD85:
                us.resize(3);
                us[2u] = 0x0645u;
                break;

            case 0xFD86:
                us.resize(3);
                us[2u] = 0x0645u;
                break;

            case 0xFD87:
                us.resize(3);
                us[2u] = 0x062Du;
                break;

            case 0xFD88:
                us.resize(3);
                us[2u] = 0x062Du;
                break;

            case 0xFD89:
                us.resize(3);
                us[2u] = 0x062Cu;
                break;

            case 0xFD8A:
                us.resize(3);
                us[2u] = 0x0645u;
                break;

            case 0xFD8B:
                us.resize(3);
                us[2u] = 0x064Au;
                break;

            case 0xFD8C:
                us.resize(3);
                us[2u] = 0x062Du;
                break;

            case 0xFD8D:
                us.resize(3);
                us[2u] = 0x0645u;
                break;

            case 0xFD8E:
                us.resize(3);
                us[2u] = 0x062Cu;
                break;

            case 0xFD8F:
                us.resize(3);
                us[2u] = 0x0645u;
                break;

            case 0xFD92:
                us.resize(3);
                us[2u] = 0x062Eu;
                break;

            case 0xFD93:
                us.resize(3);
                us[2u] = 0x062Cu;
                break;

            case 0xFD94:
                us.resize(3);
                us[2u] = 0x0645u;
                break;

            case 0xFD95:
                us.resize(3);
                us[2u] = 0x0645u;
                break;

            case 0xFD96:
                us.resize(3);
                us[2u] = 0x0649u;
                break;

            case 0xFD97:
                us.resize(3);
                us[2u] = 0x0645u;
                break;

            case 0xFD98:
                us.resize(3);
                us[2u] = 0x0645u;
                break;

            case 0xFD99:
                us.resize(3);
                us[2u] = 0x0649u;
                break;

            case 0xFD9A:
                us.resize(3);
                us[2u] = 0x064Au;
                break;

            case 0xFD9B:
                us.resize(3);
                us[2u] = 0x0649u;
                break;

            case 0xFD9C:
                us.resize(3);
                us[2u] = 0x0645u;
                break;

            case 0xFD9D:
                us.resize(3);
                us[2u] = 0x0645u;
                break;

            case 0xFD9E:
                us.resize(3);
                us[2u] = 0x064Au;
                break;

            case 0xFD9F:
                us.resize(3);
                us[2u] = 0x064Au;
                break;

            case 0xFDA0:
                us.resize(3);
                us[2u] = 0x0649u;
                break;

            case 0xFDA1:
                us.resize(3);
                us[2u] = 0x064Au;
                break;

            case 0xFDA2:
                us.resize(3);
                us[2u] = 0x0649u;
                break;

            case 0xFDA3:
                us.resize(3);
                us[2u] = 0x064Au;
                break;

            case 0xFDA4:
                us.resize(3);
                us[2u] = 0x0649u;
                break;

            case 0xFDA5:
                us.resize(3);
                us[2u] = 0x064Au;
                break;

            case 0xFDA6:
                us.resize(3);
                us[2u] = 0x0649u;
                break;

            case 0xFDA7:
                us.resize(3);
                us[2u] = 0x0649u;
                break;

            case 0xFDA8:
                us.resize(3);
                us[2u] = 0x0649u;
                break;

            case 0xFDA9:
                us.resize(3);
                us[2u] = 0x064Au;
                break;

            case 0xFDAA:
                us.resize(3);
                us[2u] = 0x064Au;
                break;

            case 0xFDAB:
                us.resize(3);
                us[2u] = 0x064Au;
                break;

            case 0xFDAC:
                us.resize(3);
                us[2u] = 0x064Au;
                break;

            case 0xFDAD:
                us.resize(3);
                us[2u] = 0x064Au;
                break;

            case 0xFDAE:
                us.resize(3);
                us[2u] = 0x064Au;
                break;

            case 0xFDAF:
                us.resize(3);
                us[2u] = 0x064Au;
                break;

            case 0xFDB0:
                us.resize(3);
                us[2u] = 0x064Au;
                break;

            case 0xFDB1:
                us.resize(3);
                us[2u] = 0x064Au;
                break;

            case 0xFDB2:
                us.resize(3);
                us[2u] = 0x064Au;
                break;

            case 0xFDB3:
                us.resize(3);
                us[2u] = 0x064Au;
                break;

            case 0xFDB4:
                us.resize(3);
                us[2u] = 0x062Du;
                break;

            case 0xFDB5:
                us.resize(3);
                us[2u] = 0x0645u;
                break;

            case 0xFDB6:
                us.resize(3);
                us[2u] = 0x064Au;
                break;

            case 0xFDB7:
                us.resize(3);
                us[2u] = 0x064Au;
                break;

            case 0xFDB8:
                us.resize(3);
                us[2u] = 0x062Du;
                break;

            case 0xFDB9:
                us.resize(3);
                us[2u] = 0x064Au;
                break;

            case 0xFDBA:
                us.resize(3);
                us[2u] = 0x0645u;
                break;

            case 0xFDBB:
                us.resize(3);
                us[2u] = 0x0645u;
                break;

            case 0xFDBC:
                us.resize(3);
                us[2u] = 0x0645u;
                break;

            case 0xFDBD:
                us.resize(3);
                us[2u] = 0x062Du;
                break;

            case 0xFDBE:
                us.resize(3);
                us[2u] = 0x064Au;
                break;

            case 0xFDBF:
                us.resize(3);
                us[2u] = 0x064Au;
                break;

            case 0xFDC0:
                us.resize(3);
                us[2u] = 0x064Au;
                break;

            case 0xFDC1:
                us.resize(3);
                us[2u] = 0x064Au;
                break;

            case 0xFDC2:
                us.resize(3);
                us[2u] = 0x064Au;
                break;

            case 0xFDC3:
                us.resize(3);
                us[2u] = 0x0645u;
                break;

            case 0xFDC4:
                us.resize(3);
                us[2u] = 0x0645u;
                break;

            case 0xFDC5:
                us.resize(3);
                us[2u] = 0x0645u;
                break;

            case 0xFDC6:
                us.resize(3);
                us[2u] = 0x064Au;
                break;

            case 0xFDC7:
                us.resize(3);
                us[2u] = 0x064Au;
                break;

            case 0xFDF0:
                us.resize(3);
                us[2u] = 0x06D2u;
                break;

            case 0xFDF1:
                us.resize(3);
                us[2u] = 0x06D2u;
                break;

            case 0xFDF2:
                us.resize(4);
                us[2u] = 0x0644u;
                us[3u] = 0x0647u;
                break;

            case 0xFDF3:
                us.resize(4);
                us[2u] = 0x0628u;
                us[3u] = 0x0631u;
                break;

            case 0xFDF4:
                us.resize(4);
                us[2u] = 0x0645u;
                us[3u] = 0x062Fu;
                break;

            case 0xFDF5:
                us.resize(4);
                us[2u] = 0x0639u;
                us[3u] = 0x0645u;
                break;

            case 0xFDF6:
                us.resize(4);
                us[2u] = 0x0648u;
                us[3u] = 0x0644u;
                break;

            case 0xFDF7:
                us.resize(4);
                us[2u] = 0x064Au;
                us[3u] = 0x0647u;
                break;

            case 0xFDF8:
                us.resize(4);
                us[2u] = 0x0644u;
                us[3u] = 0x0645u;
                break;

            case 0xFDF9:
                us.resize(3);
                us[2u] = 0x0649u;
                break;

            case 0xFDFA:
                us.resize(18);
                us[2u] = 0x0649u;
                us[3u] = 0x0020u;
                us[4u] = 0x0627u;
                us[5u] = 0x0644u;
                us[6u] = 0x0644u;
                us[7u] = 0x0647u;
                us[8u] = 0x0020u;
                us[9u] = 0x0639u;
                us[10u] = 0x0644u;
                us[11u] = 0x064Au;
                us[12u] = 0x0647u;
                us[13u] = 0x0020u;
                us[14u] = 0x0648u;
                us[15u] = 0x0633u;
                us[16u] = 0x0644u;
                us[17u] = 0x0645u;
                break;

            case 0xFDFB:
                us.resize(8);
                us[2u] = 0x0020u;
                us[3u] = 0x062Cu;
                us[4u] = 0x0644u;
                us[5u] = 0x0627u;
                us[6u] = 0x0644u;
                us[7u] = 0x0647u;
                break;

            case 0xFDFC:
                us.resize(4);
                us[2u] = 0x0627u;
                us[3u] = 0x0644u;
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
            return Babylon::Line_Break(Arabic_Presentation_FormsAFB50::my_lb[uc - my_first_letter]);
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
            return my_Noncharacter_Code_Point.test(uc - my_first_letter);
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
            return my_XID_Start_Closure.test(uc - my_first_letter);
        }

        bool is_XID_Continue_Closure(const UCS4 uc) const
        {
            return my_XID_Continue_Closure.test(uc - my_first_letter);
        }

      private:
        // functions
        Arabic_Presentation_FormsAFB50(const Arabic_Presentation_FormsAFB50 &) ; // no implementaion!

    // members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const std::bitset<688> my_is_defined;
        static const unsigned char my_cat[688];
        static const Babylon::Bidir_Props my_bidir[688];
        static const unsigned char my_decomp[688];
        static const UCS4 my_decompStr[688][2];
        static const unsigned char my_lb[688];
        static const std::bitset<688> my_Noncharacter_Code_Point;
        static const std::bitset<688> my_XID_Start_Closure;
        static const std::bitset<688> my_XID_Continue_Closure;
    }; // class Arabic_Presentation_FormsAFB50

    const std::bitset<688> Arabic_Presentation_FormsAFB50::my_is_defined(std::string("0011111111111111000000000000000000000000000000000000000011111111111111111111111111111111111111111111111111111100111111111111111111111111111111111111111111111111111111111111111100000000000000001111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111100000000000000000000000000000000011111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"));

    const unsigned char Arabic_Presentation_FormsAFB50::my_cat[] =
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
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Ps, CAT_Pe, 
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
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
        CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Sc, CAT_So, CAT_Lo, CAT_Lo
    };

    const Babylon::Bidir_Props Arabic_Presentation_FormsAFB50::my_bidir[] =
    {
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_ON, BIDIR_ON, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
        BIDIR_AL, BIDIR_ON, BIDIR_AL, BIDIR_AL
    };

    const unsigned char Arabic_Presentation_FormsAFB50::my_decomp[] = {
        DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, 
        DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, 
        DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, 
        DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, 
        DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, 
        DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, 
        DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, 
        DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, 
        DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, 
        DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, 
        DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, 
        DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, 
        DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, 
        DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, 
        DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, 
        DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, 
        DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, 
        DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, 
        DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, 
        DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, 
        DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_MEDIAL, 
        DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, 
        DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, 
        DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, 
        DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_ISOLATED, 
        DECOMP_FINAL, DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, 
        DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, 
        DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_FINAL, 
        DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, 
        DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_MEDIAL, 
        DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, 
        DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, 
        DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, 
        DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, 
        DECOMP_INITIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, 
        DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_MEDIAL, 
        DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
        DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
        DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
        DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
        DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
        DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
        DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
        DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
        DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
        DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
        DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
        DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
        DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
        DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
        DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
        DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
        DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
        DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
        DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
        DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
        DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
        DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
        DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
        DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
        DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
        DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, 
        DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, 
        DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, 
        DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, 
        DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, 
        DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, 
        DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, 
        DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, 
        DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, 
        DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, 
        DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, 
        DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, 
        DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_INITIAL, 
        DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, 
        DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, 
        DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, 
        DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, 
        DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, 
        DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, 
        DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, 
        DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, 
        DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, 
        DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, 
        DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, 
        DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, 
        DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, 
        DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, 
        DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, 
        DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, 
        DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, 
        DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_MEDIAL, 
        DECOMP_MEDIAL, DECOMP_MEDIAL, DECOMP_MEDIAL, DECOMP_MEDIAL, 
        DECOMP_MEDIAL, DECOMP_MEDIAL, DECOMP_MEDIAL, DECOMP_MEDIAL, 
        DECOMP_MEDIAL, DECOMP_MEDIAL, DECOMP_MEDIAL, DECOMP_MEDIAL, 
        DECOMP_MEDIAL, DECOMP_MEDIAL, DECOMP_MEDIAL, DECOMP_MEDIAL, 
        DECOMP_MEDIAL, DECOMP_MEDIAL, DECOMP_MEDIAL, DECOMP_MEDIAL, 
        DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
        DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
        DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
        DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
        DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
        DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
        DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
        DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, 
        DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, 
        DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, 
        DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, 
        DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, 
        DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, 
        DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, 
        DECOMP_FINAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, 
        DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, 
        DECOMP_MEDIAL, DECOMP_MEDIAL, DECOMP_MEDIAL, DECOMP_MEDIAL, 
        DECOMP_MEDIAL, DECOMP_MEDIAL, DECOMP_MEDIAL, DECOMP_MEDIAL, 
        DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_INITIAL, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_INITIAL, 
        DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, 
        DECOMP_FINAL, DECOMP_INITIAL, DECOMP_FINAL, DECOMP_FINAL, 
        DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_FINAL, DECOMP_FINAL, 
        DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_FINAL, DECOMP_INITIAL, 
        DECOMP_FINAL, DECOMP_INITIAL, DECOMP_FINAL, DECOMP_FINAL, 
        DECOMP_INITIAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_INITIAL, 
        DECOMP_FINAL, DECOMP_INITIAL, DECOMP_FINAL, DECOMP_FINAL, 
        DECOMP_INITIAL, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_INITIAL, 
        DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_INITIAL, 
        DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, 
        DECOMP_FINAL, DECOMP_INITIAL, DECOMP_FINAL, DECOMP_FINAL, 
        DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_INITIAL, 
        DECOMP_FINAL, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_FINAL, 
        DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_FINAL, 
        DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_INITIAL, DECOMP_INITIAL, 
        DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_FINAL, DECOMP_FINAL, 
        DECOMP_INITIAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, 
        DECOMP_FINAL, DECOMP_INITIAL, DECOMP_FINAL, DECOMP_FINAL, 
        DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, 
        DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, 
        DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, 
        DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, 
        DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, 
        DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_FINAL, DECOMP_FINAL, 
        DECOMP_INITIAL, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_FINAL, 
        DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, 
        DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_INITIAL, 
        DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_FINAL, DECOMP_FINAL, 
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
        DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
        DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
        DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
        DECOMP_ISOLATED, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL
    };

    const UCS4 Arabic_Presentation_FormsAFB50::my_decompStr[][2] =
    {
        { 0x00000671u, 0x00000000u }, { 0x00000671u, 0x00000000u },  // 0000FB50
        { 0x0000067Bu, 0x00000000u }, { 0x0000067Bu, 0x00000000u },  // 0000FB52
        { 0x0000067Bu, 0x00000000u }, { 0x0000067Bu, 0x00000000u },  // 0000FB54
        { 0x0000067Eu, 0x00000000u }, { 0x0000067Eu, 0x00000000u },  // 0000FB56
        { 0x0000067Eu, 0x00000000u }, { 0x0000067Eu, 0x00000000u },  // 0000FB58
        { 0x00000680u, 0x00000000u }, { 0x00000680u, 0x00000000u },  // 0000FB5A
        { 0x00000680u, 0x00000000u }, { 0x00000680u, 0x00000000u },  // 0000FB5C
        { 0x0000067Au, 0x00000000u }, { 0x0000067Au, 0x00000000u },  // 0000FB5E
        { 0x0000067Au, 0x00000000u }, { 0x0000067Au, 0x00000000u },  // 0000FB60
        { 0x0000067Fu, 0x00000000u }, { 0x0000067Fu, 0x00000000u },  // 0000FB62
        { 0x0000067Fu, 0x00000000u }, { 0x0000067Fu, 0x00000000u },  // 0000FB64
        { 0x00000679u, 0x00000000u }, { 0x00000679u, 0x00000000u },  // 0000FB66
        { 0x00000679u, 0x00000000u }, { 0x00000679u, 0x00000000u },  // 0000FB68
        { 0x000006A4u, 0x00000000u }, { 0x000006A4u, 0x00000000u },  // 0000FB6A
        { 0x000006A4u, 0x00000000u }, { 0x000006A4u, 0x00000000u },  // 0000FB6C
        { 0x000006A6u, 0x00000000u }, { 0x000006A6u, 0x00000000u },  // 0000FB6E
        { 0x000006A6u, 0x00000000u }, { 0x000006A6u, 0x00000000u },  // 0000FB70
        { 0x00000684u, 0x00000000u }, { 0x00000684u, 0x00000000u },  // 0000FB72
        { 0x00000684u, 0x00000000u }, { 0x00000684u, 0x00000000u },  // 0000FB74
        { 0x00000683u, 0x00000000u }, { 0x00000683u, 0x00000000u },  // 0000FB76
        { 0x00000683u, 0x00000000u }, { 0x00000683u, 0x00000000u },  // 0000FB78
        { 0x00000686u, 0x00000000u }, { 0x00000686u, 0x00000000u },  // 0000FB7A
        { 0x00000686u, 0x00000000u }, { 0x00000686u, 0x00000000u },  // 0000FB7C
        { 0x00000687u, 0x00000000u }, { 0x00000687u, 0x00000000u },  // 0000FB7E
        { 0x00000687u, 0x00000000u }, { 0x00000687u, 0x00000000u },  // 0000FB80
        { 0x0000068Du, 0x00000000u }, { 0x0000068Du, 0x00000000u },  // 0000FB82
        { 0x0000068Cu, 0x00000000u }, { 0x0000068Cu, 0x00000000u },  // 0000FB84
        { 0x0000068Eu, 0x00000000u }, { 0x0000068Eu, 0x00000000u },  // 0000FB86
        { 0x00000688u, 0x00000000u }, { 0x00000688u, 0x00000000u },  // 0000FB88
        { 0x00000698u, 0x00000000u }, { 0x00000698u, 0x00000000u },  // 0000FB8A
        { 0x00000691u, 0x00000000u }, { 0x00000691u, 0x00000000u },  // 0000FB8C
        { 0x000006A9u, 0x00000000u }, { 0x000006A9u, 0x00000000u },  // 0000FB8E
        { 0x000006A9u, 0x00000000u }, { 0x000006A9u, 0x00000000u },  // 0000FB90
        { 0x000006AFu, 0x00000000u }, { 0x000006AFu, 0x00000000u },  // 0000FB92
        { 0x000006AFu, 0x00000000u }, { 0x000006AFu, 0x00000000u },  // 0000FB94
        { 0x000006B3u, 0x00000000u }, { 0x000006B3u, 0x00000000u },  // 0000FB96
        { 0x000006B3u, 0x00000000u }, { 0x000006B3u, 0x00000000u },  // 0000FB98
        { 0x000006B1u, 0x00000000u }, { 0x000006B1u, 0x00000000u },  // 0000FB9A
        { 0x000006B1u, 0x00000000u }, { 0x000006B1u, 0x00000000u },  // 0000FB9C
        { 0x000006BAu, 0x00000000u }, { 0x000006BAu, 0x00000000u },  // 0000FB9E
        { 0x000006BBu, 0x00000000u }, { 0x000006BBu, 0x00000000u },  // 0000FBA0
        { 0x000006BBu, 0x00000000u }, { 0x000006BBu, 0x00000000u },  // 0000FBA2
        { 0x000006C0u, 0x00000000u }, { 0x000006C0u, 0x00000000u },  // 0000FBA4
        { 0x000006C1u, 0x00000000u }, { 0x000006C1u, 0x00000000u },  // 0000FBA6
        { 0x000006C1u, 0x00000000u }, { 0x000006C1u, 0x00000000u },  // 0000FBA8
        { 0x000006BEu, 0x00000000u }, { 0x000006BEu, 0x00000000u },  // 0000FBAA
        { 0x000006BEu, 0x00000000u }, { 0x000006BEu, 0x00000000u },  // 0000FBAC
        { 0x000006D2u, 0x00000000u }, { 0x000006D2u, 0x00000000u },  // 0000FBAE
        { 0x000006D3u, 0x00000000u }, { 0x000006D3u, 0x00000000u },  // 0000FBB0
        { 0x0000FBB2u, 0x00000000u }, { 0x0000FBB3u, 0x00000000u },  // 0000FBB2
        { 0x0000FBB4u, 0x00000000u }, { 0x0000FBB5u, 0x00000000u },  // 0000FBB4
        { 0x0000FBB6u, 0x00000000u }, { 0x0000FBB7u, 0x00000000u },  // 0000FBB6
        { 0x0000FBB8u, 0x00000000u }, { 0x0000FBB9u, 0x00000000u },  // 0000FBB8
        { 0x0000FBBAu, 0x00000000u }, { 0x0000FBBBu, 0x00000000u },  // 0000FBBA
        { 0x0000FBBCu, 0x00000000u }, { 0x0000FBBDu, 0x00000000u },  // 0000FBBC
        { 0x0000FBBEu, 0x00000000u }, { 0x0000FBBFu, 0x00000000u },  // 0000FBBE
        { 0x0000FBC0u, 0x00000000u }, { 0x0000FBC1u, 0x00000000u },  // 0000FBC0
        { 0x0000FBC2u, 0x00000000u }, { 0x0000FBC3u, 0x00000000u },  // 0000FBC2
        { 0x0000FBC4u, 0x00000000u }, { 0x0000FBC5u, 0x00000000u },  // 0000FBC4
        { 0x0000FBC6u, 0x00000000u }, { 0x0000FBC7u, 0x00000000u },  // 0000FBC6
        { 0x0000FBC8u, 0x00000000u }, { 0x0000FBC9u, 0x00000000u },  // 0000FBC8
        { 0x0000FBCAu, 0x00000000u }, { 0x0000FBCBu, 0x00000000u },  // 0000FBCA
        { 0x0000FBCCu, 0x00000000u }, { 0x0000FBCDu, 0x00000000u },  // 0000FBCC
        { 0x0000FBCEu, 0x00000000u }, { 0x0000FBCFu, 0x00000000u },  // 0000FBCE
        { 0x0000FBD0u, 0x00000000u }, { 0x0000FBD1u, 0x00000000u },  // 0000FBD0
        { 0x0000FBD2u, 0x00000000u }, { 0x000006ADu, 0x00000000u },  // 0000FBD2
        { 0x000006ADu, 0x00000000u }, { 0x000006ADu, 0x00000000u },  // 0000FBD4
        { 0x000006ADu, 0x00000000u }, { 0x000006C7u, 0x00000000u },  // 0000FBD6
        { 0x000006C7u, 0x00000000u }, { 0x000006C6u, 0x00000000u },  // 0000FBD8
        { 0x000006C6u, 0x00000000u }, { 0x000006C8u, 0x00000000u },  // 0000FBDA
        { 0x000006C8u, 0x00000000u }, { 0x00000677u, 0x00000000u },  // 0000FBDC
        { 0x000006CBu, 0x00000000u }, { 0x000006CBu, 0x00000000u },  // 0000FBDE
        { 0x000006C5u, 0x00000000u }, { 0x000006C5u, 0x00000000u },  // 0000FBE0
        { 0x000006C9u, 0x00000000u }, { 0x000006C9u, 0x00000000u },  // 0000FBE2
        { 0x000006D0u, 0x00000000u }, { 0x000006D0u, 0x00000000u },  // 0000FBE4
        { 0x000006D0u, 0x00000000u }, { 0x000006D0u, 0x00000000u },  // 0000FBE6
        { 0x00000649u, 0x00000000u }, { 0x00000649u, 0x00000000u },  // 0000FBE8
        { 0x00000626u, 0x00000627u }, { 0x00000626u, 0x00000627u },  // 0000FBEA
        { 0x00000626u, 0x000006D5u }, { 0x00000626u, 0x000006D5u },  // 0000FBEC
        { 0x00000626u, 0x00000648u }, { 0x00000626u, 0x00000648u },  // 0000FBEE
        { 0x00000626u, 0x000006C7u }, { 0x00000626u, 0x000006C7u },  // 0000FBF0
        { 0x00000626u, 0x000006C6u }, { 0x00000626u, 0x000006C6u },  // 0000FBF2
        { 0x00000626u, 0x000006C8u }, { 0x00000626u, 0x000006C8u },  // 0000FBF4
        { 0x00000626u, 0x000006D0u }, { 0x00000626u, 0x000006D0u },  // 0000FBF6
        { 0x00000626u, 0x000006D0u }, { 0x00000626u, 0x00000649u },  // 0000FBF8
        { 0x00000626u, 0x00000649u }, { 0x00000626u, 0x00000649u },  // 0000FBFA
        { 0x000006CCu, 0x00000000u }, { 0x000006CCu, 0x00000000u },  // 0000FBFC
        { 0x000006CCu, 0x00000000u }, { 0x000006CCu, 0x00000000u },  // 0000FBFE
        { 0x00000626u, 0x0000062Cu }, { 0x00000626u, 0x0000062Du },  // 0000FC00
        { 0x00000626u, 0x00000645u }, { 0x00000626u, 0x00000649u },  // 0000FC02
        { 0x00000626u, 0x0000064Au }, { 0x00000628u, 0x0000062Cu },  // 0000FC04
        { 0x00000628u, 0x0000062Du }, { 0x00000628u, 0x0000062Eu },  // 0000FC06
        { 0x00000628u, 0x00000645u }, { 0x00000628u, 0x00000649u },  // 0000FC08
        { 0x00000628u, 0x0000064Au }, { 0x0000062Au, 0x0000062Cu },  // 0000FC0A
        { 0x0000062Au, 0x0000062Du }, { 0x0000062Au, 0x0000062Eu },  // 0000FC0C
        { 0x0000062Au, 0x00000645u }, { 0x0000062Au, 0x00000649u },  // 0000FC0E
        { 0x0000062Au, 0x0000064Au }, { 0x0000062Bu, 0x0000062Cu },  // 0000FC10
        { 0x0000062Bu, 0x00000645u }, { 0x0000062Bu, 0x00000649u },  // 0000FC12
        { 0x0000062Bu, 0x0000064Au }, { 0x0000062Cu, 0x0000062Du },  // 0000FC14
        { 0x0000062Cu, 0x00000645u }, { 0x0000062Du, 0x0000062Cu },  // 0000FC16
        { 0x0000062Du, 0x00000645u }, { 0x0000062Eu, 0x0000062Cu },  // 0000FC18
        { 0x0000062Eu, 0x0000062Du }, { 0x0000062Eu, 0x00000645u },  // 0000FC1A
        { 0x00000633u, 0x0000062Cu }, { 0x00000633u, 0x0000062Du },  // 0000FC1C
        { 0x00000633u, 0x0000062Eu }, { 0x00000633u, 0x00000645u },  // 0000FC1E
        { 0x00000635u, 0x0000062Du }, { 0x00000635u, 0x00000645u },  // 0000FC20
        { 0x00000636u, 0x0000062Cu }, { 0x00000636u, 0x0000062Du },  // 0000FC22
        { 0x00000636u, 0x0000062Eu }, { 0x00000636u, 0x00000645u },  // 0000FC24
        { 0x00000637u, 0x0000062Du }, { 0x00000637u, 0x00000645u },  // 0000FC26
        { 0x00000638u, 0x00000645u }, { 0x00000639u, 0x0000062Cu },  // 0000FC28
        { 0x00000639u, 0x00000645u }, { 0x0000063Au, 0x0000062Cu },  // 0000FC2A
        { 0x0000063Au, 0x00000645u }, { 0x00000641u, 0x0000062Cu },  // 0000FC2C
        { 0x00000641u, 0x0000062Du }, { 0x00000641u, 0x0000062Eu },  // 0000FC2E
        { 0x00000641u, 0x00000645u }, { 0x00000641u, 0x00000649u },  // 0000FC30
        { 0x00000641u, 0x0000064Au }, { 0x00000642u, 0x0000062Du },  // 0000FC32
        { 0x00000642u, 0x00000645u }, { 0x00000642u, 0x00000649u },  // 0000FC34
        { 0x00000642u, 0x0000064Au }, { 0x00000643u, 0x00000627u },  // 0000FC36
        { 0x00000643u, 0x0000062Cu }, { 0x00000643u, 0x0000062Du },  // 0000FC38
        { 0x00000643u, 0x0000062Eu }, { 0x00000643u, 0x00000644u },  // 0000FC3A
        { 0x00000643u, 0x00000645u }, { 0x00000643u, 0x00000649u },  // 0000FC3C
        { 0x00000643u, 0x0000064Au }, { 0x00000644u, 0x0000062Cu },  // 0000FC3E
        { 0x00000644u, 0x0000062Du }, { 0x00000644u, 0x0000062Eu },  // 0000FC40
        { 0x00000644u, 0x00000645u }, { 0x00000644u, 0x00000649u },  // 0000FC42
        { 0x00000644u, 0x0000064Au }, { 0x00000645u, 0x0000062Cu },  // 0000FC44
        { 0x00000645u, 0x0000062Du }, { 0x00000645u, 0x0000062Eu },  // 0000FC46
        { 0x00000645u, 0x00000645u }, { 0x00000645u, 0x00000649u },  // 0000FC48
        { 0x00000645u, 0x0000064Au }, { 0x00000646u, 0x0000062Cu },  // 0000FC4A
        { 0x00000646u, 0x0000062Du }, { 0x00000646u, 0x0000062Eu },  // 0000FC4C
        { 0x00000646u, 0x00000645u }, { 0x00000646u, 0x00000649u },  // 0000FC4E
        { 0x00000646u, 0x0000064Au }, { 0x00000647u, 0x0000062Cu },  // 0000FC50
        { 0x00000647u, 0x00000645u }, { 0x00000647u, 0x00000649u },  // 0000FC52
        { 0x00000647u, 0x0000064Au }, { 0x0000064Au, 0x0000062Cu },  // 0000FC54
        { 0x0000064Au, 0x0000062Du }, { 0x0000064Au, 0x0000062Eu },  // 0000FC56
        { 0x0000064Au, 0x00000645u }, { 0x0000064Au, 0x00000649u },  // 0000FC58
        { 0x0000064Au, 0x0000064Au }, { 0x00000630u, 0x00000670u },  // 0000FC5A
        { 0x00000631u, 0x00000670u }, { 0x00000649u, 0x00000670u },  // 0000FC5C
        { 0x00000020u, 0x0000064Cu }, { 0x00000020u, 0x0000064Du },  // 0000FC5E
        { 0x00000020u, 0x0000064Eu }, { 0x00000020u, 0x0000064Fu },  // 0000FC60
        { 0x00000020u, 0x00000650u }, { 0x00000020u, 0x00000651u },  // 0000FC62
        { 0x00000626u, 0x00000631u }, { 0x00000626u, 0x00000632u },  // 0000FC64
        { 0x00000626u, 0x00000645u }, { 0x00000626u, 0x00000646u },  // 0000FC66
        { 0x00000626u, 0x00000649u }, { 0x00000626u, 0x0000064Au },  // 0000FC68
        { 0x00000628u, 0x00000631u }, { 0x00000628u, 0x00000632u },  // 0000FC6A
        { 0x00000628u, 0x00000645u }, { 0x00000628u, 0x00000646u },  // 0000FC6C
        { 0x00000628u, 0x00000649u }, { 0x00000628u, 0x0000064Au },  // 0000FC6E
        { 0x0000062Au, 0x00000631u }, { 0x0000062Au, 0x00000632u },  // 0000FC70
        { 0x0000062Au, 0x00000645u }, { 0x0000062Au, 0x00000646u },  // 0000FC72
        { 0x0000062Au, 0x00000649u }, { 0x0000062Au, 0x0000064Au },  // 0000FC74
        { 0x0000062Bu, 0x00000631u }, { 0x0000062Bu, 0x00000632u },  // 0000FC76
        { 0x0000062Bu, 0x00000645u }, { 0x0000062Bu, 0x00000646u },  // 0000FC78
        { 0x0000062Bu, 0x00000649u }, { 0x0000062Bu, 0x0000064Au },  // 0000FC7A
        { 0x00000641u, 0x00000649u }, { 0x00000641u, 0x0000064Au },  // 0000FC7C
        { 0x00000642u, 0x00000649u }, { 0x00000642u, 0x0000064Au },  // 0000FC7E
        { 0x00000643u, 0x00000627u }, { 0x00000643u, 0x00000644u },  // 0000FC80
        { 0x00000643u, 0x00000645u }, { 0x00000643u, 0x00000649u },  // 0000FC82
        { 0x00000643u, 0x0000064Au }, { 0x00000644u, 0x00000645u },  // 0000FC84
        { 0x00000644u, 0x00000649u }, { 0x00000644u, 0x0000064Au },  // 0000FC86
        { 0x00000645u, 0x00000627u }, { 0x00000645u, 0x00000645u },  // 0000FC88
        { 0x00000646u, 0x00000631u }, { 0x00000646u, 0x00000632u },  // 0000FC8A
        { 0x00000646u, 0x00000645u }, { 0x00000646u, 0x00000646u },  // 0000FC8C
        { 0x00000646u, 0x00000649u }, { 0x00000646u, 0x0000064Au },  // 0000FC8E
        { 0x00000649u, 0x00000670u }, { 0x0000064Au, 0x00000631u },  // 0000FC90
        { 0x0000064Au, 0x00000632u }, { 0x0000064Au, 0x00000645u },  // 0000FC92
        { 0x0000064Au, 0x00000646u }, { 0x0000064Au, 0x00000649u },  // 0000FC94
        { 0x0000064Au, 0x0000064Au }, { 0x00000626u, 0x0000062Cu },  // 0000FC96
        { 0x00000626u, 0x0000062Du }, { 0x00000626u, 0x0000062Eu },  // 0000FC98
        { 0x00000626u, 0x00000645u }, { 0x00000626u, 0x00000647u },  // 0000FC9A
        { 0x00000628u, 0x0000062Cu }, { 0x00000628u, 0x0000062Du },  // 0000FC9C
        { 0x00000628u, 0x0000062Eu }, { 0x00000628u, 0x00000645u },  // 0000FC9E
        { 0x00000628u, 0x00000647u }, { 0x0000062Au, 0x0000062Cu },  // 0000FCA0
        { 0x0000062Au, 0x0000062Du }, { 0x0000062Au, 0x0000062Eu },  // 0000FCA2
        { 0x0000062Au, 0x00000645u }, { 0x0000062Au, 0x00000647u },  // 0000FCA4
        { 0x0000062Bu, 0x00000645u }, { 0x0000062Cu, 0x0000062Du },  // 0000FCA6
        { 0x0000062Cu, 0x00000645u }, { 0x0000062Du, 0x0000062Cu },  // 0000FCA8
        { 0x0000062Du, 0x00000645u }, { 0x0000062Eu, 0x0000062Cu },  // 0000FCAA
        { 0x0000062Eu, 0x00000645u }, { 0x00000633u, 0x0000062Cu },  // 0000FCAC
        { 0x00000633u, 0x0000062Du }, { 0x00000633u, 0x0000062Eu },  // 0000FCAE
        { 0x00000633u, 0x00000645u }, { 0x00000635u, 0x0000062Du },  // 0000FCB0
        { 0x00000635u, 0x0000062Eu }, { 0x00000635u, 0x00000645u },  // 0000FCB2
        { 0x00000636u, 0x0000062Cu }, { 0x00000636u, 0x0000062Du },  // 0000FCB4
        { 0x00000636u, 0x0000062Eu }, { 0x00000636u, 0x00000645u },  // 0000FCB6
        { 0x00000637u, 0x0000062Du }, { 0x00000638u, 0x00000645u },  // 0000FCB8
        { 0x00000639u, 0x0000062Cu }, { 0x00000639u, 0x00000645u },  // 0000FCBA
        { 0x0000063Au, 0x0000062Cu }, { 0x0000063Au, 0x00000645u },  // 0000FCBC
        { 0x00000641u, 0x0000062Cu }, { 0x00000641u, 0x0000062Du },  // 0000FCBE
        { 0x00000641u, 0x0000062Eu }, { 0x00000641u, 0x00000645u },  // 0000FCC0
        { 0x00000642u, 0x0000062Du }, { 0x00000642u, 0x00000645u },  // 0000FCC2
        { 0x00000643u, 0x0000062Cu }, { 0x00000643u, 0x0000062Du },  // 0000FCC4
        { 0x00000643u, 0x0000062Eu }, { 0x00000643u, 0x00000644u },  // 0000FCC6
        { 0x00000643u, 0x00000645u }, { 0x00000644u, 0x0000062Cu },  // 0000FCC8
        { 0x00000644u, 0x0000062Du }, { 0x00000644u, 0x0000062Eu },  // 0000FCCA
        { 0x00000644u, 0x00000645u }, { 0x00000644u, 0x00000647u },  // 0000FCCC
        { 0x00000645u, 0x0000062Cu }, { 0x00000645u, 0x0000062Du },  // 0000FCCE
        { 0x00000645u, 0x0000062Eu }, { 0x00000645u, 0x00000645u },  // 0000FCD0
        { 0x00000646u, 0x0000062Cu }, { 0x00000646u, 0x0000062Du },  // 0000FCD2
        { 0x00000646u, 0x0000062Eu }, { 0x00000646u, 0x00000645u },  // 0000FCD4
        { 0x00000646u, 0x00000647u }, { 0x00000647u, 0x0000062Cu },  // 0000FCD6
        { 0x00000647u, 0x00000645u }, { 0x00000647u, 0x00000670u },  // 0000FCD8
        { 0x0000064Au, 0x0000062Cu }, { 0x0000064Au, 0x0000062Du },  // 0000FCDA
        { 0x0000064Au, 0x0000062Eu }, { 0x0000064Au, 0x00000645u },  // 0000FCDC
        { 0x0000064Au, 0x00000647u }, { 0x00000626u, 0x00000645u },  // 0000FCDE
        { 0x00000626u, 0x00000647u }, { 0x00000628u, 0x00000645u },  // 0000FCE0
        { 0x00000628u, 0x00000647u }, { 0x0000062Au, 0x00000645u },  // 0000FCE2
        { 0x0000062Au, 0x00000647u }, { 0x0000062Bu, 0x00000645u },  // 0000FCE4
        { 0x0000062Bu, 0x00000647u }, { 0x00000633u, 0x00000645u },  // 0000FCE6
        { 0x00000633u, 0x00000647u }, { 0x00000634u, 0x00000645u },  // 0000FCE8
        { 0x00000634u, 0x00000647u }, { 0x00000643u, 0x00000644u },  // 0000FCEA
        { 0x00000643u, 0x00000645u }, { 0x00000644u, 0x00000645u },  // 0000FCEC
        { 0x00000646u, 0x00000645u }, { 0x00000646u, 0x00000647u },  // 0000FCEE
        { 0x0000064Au, 0x00000645u }, { 0x0000064Au, 0x00000647u },  // 0000FCF0
        { 0x00000640u, 0x0000064Eu }, { 0x00000640u, 0x0000064Fu },  // 0000FCF2
        { 0x00000640u, 0x00000650u }, { 0x00000637u, 0x00000649u },  // 0000FCF4
        { 0x00000637u, 0x0000064Au }, { 0x00000639u, 0x00000649u },  // 0000FCF6
        { 0x00000639u, 0x0000064Au }, { 0x0000063Au, 0x00000649u },  // 0000FCF8
        { 0x0000063Au, 0x0000064Au }, { 0x00000633u, 0x00000649u },  // 0000FCFA
        { 0x00000633u, 0x0000064Au }, { 0x00000634u, 0x00000649u },  // 0000FCFC
        { 0x00000634u, 0x0000064Au }, { 0x0000062Du, 0x00000649u },  // 0000FCFE
        { 0x0000062Du, 0x0000064Au }, { 0x0000062Cu, 0x00000649u },  // 0000FD00
        { 0x0000062Cu, 0x0000064Au }, { 0x0000062Eu, 0x00000649u },  // 0000FD02
        { 0x0000062Eu, 0x0000064Au }, { 0x00000635u, 0x00000649u },  // 0000FD04
        { 0x00000635u, 0x0000064Au }, { 0x00000636u, 0x00000649u },  // 0000FD06
        { 0x00000636u, 0x0000064Au }, { 0x00000634u, 0x0000062Cu },  // 0000FD08
        { 0x00000634u, 0x0000062Du }, { 0x00000634u, 0x0000062Eu },  // 0000FD0A
        { 0x00000634u, 0x00000645u }, { 0x00000634u, 0x00000631u },  // 0000FD0C
        { 0x00000633u, 0x00000631u }, { 0x00000635u, 0x00000631u },  // 0000FD0E
        { 0x00000636u, 0x00000631u }, { 0x00000637u, 0x00000649u },  // 0000FD10
        { 0x00000637u, 0x0000064Au }, { 0x00000639u, 0x00000649u },  // 0000FD12
        { 0x00000639u, 0x0000064Au }, { 0x0000063Au, 0x00000649u },  // 0000FD14
        { 0x0000063Au, 0x0000064Au }, { 0x00000633u, 0x00000649u },  // 0000FD16
        { 0x00000633u, 0x0000064Au }, { 0x00000634u, 0x00000649u },  // 0000FD18
        { 0x00000634u, 0x0000064Au }, { 0x0000062Du, 0x00000649u },  // 0000FD1A
        { 0x0000062Du, 0x0000064Au }, { 0x0000062Cu, 0x00000649u },  // 0000FD1C
        { 0x0000062Cu, 0x0000064Au }, { 0x0000062Eu, 0x00000649u },  // 0000FD1E
        { 0x0000062Eu, 0x0000064Au }, { 0x00000635u, 0x00000649u },  // 0000FD20
        { 0x00000635u, 0x0000064Au }, { 0x00000636u, 0x00000649u },  // 0000FD22
        { 0x00000636u, 0x0000064Au }, { 0x00000634u, 0x0000062Cu },  // 0000FD24
        { 0x00000634u, 0x0000062Du }, { 0x00000634u, 0x0000062Eu },  // 0000FD26
        { 0x00000634u, 0x00000645u }, { 0x00000634u, 0x00000631u },  // 0000FD28
        { 0x00000633u, 0x00000631u }, { 0x00000635u, 0x00000631u },  // 0000FD2A
        { 0x00000636u, 0x00000631u }, { 0x00000634u, 0x0000062Cu },  // 0000FD2C
        { 0x00000634u, 0x0000062Du }, { 0x00000634u, 0x0000062Eu },  // 0000FD2E
        { 0x00000634u, 0x00000645u }, { 0x00000633u, 0x00000647u },  // 0000FD30
        { 0x00000634u, 0x00000647u }, { 0x00000637u, 0x00000645u },  // 0000FD32
        { 0x00000633u, 0x0000062Cu }, { 0x00000633u, 0x0000062Du },  // 0000FD34
        { 0x00000633u, 0x0000062Eu }, { 0x00000634u, 0x0000062Cu },  // 0000FD36
        { 0x00000634u, 0x0000062Du }, { 0x00000634u, 0x0000062Eu },  // 0000FD38
        { 0x00000637u, 0x00000645u }, { 0x00000638u, 0x00000645u },  // 0000FD3A
        { 0x00000627u, 0x0000064Bu }, { 0x00000627u, 0x0000064Bu },  // 0000FD3C
        { 0x0000FD3Eu, 0x00000000u }, { 0x0000FD3Fu, 0x00000000u },  // 0000FD3E
        { 0x0000FD40u, 0x00000000u }, { 0x0000FD41u, 0x00000000u },  // 0000FD40
        { 0x0000FD42u, 0x00000000u }, { 0x0000FD43u, 0x00000000u },  // 0000FD42
        { 0x0000FD44u, 0x00000000u }, { 0x0000FD45u, 0x00000000u },  // 0000FD44
        { 0x0000FD46u, 0x00000000u }, { 0x0000FD47u, 0x00000000u },  // 0000FD46
        { 0x0000FD48u, 0x00000000u }, { 0x0000FD49u, 0x00000000u },  // 0000FD48
        { 0x0000FD4Au, 0x00000000u }, { 0x0000FD4Bu, 0x00000000u },  // 0000FD4A
        { 0x0000FD4Cu, 0x00000000u }, { 0x0000FD4Du, 0x00000000u },  // 0000FD4C
        { 0x0000FD4Eu, 0x00000000u }, { 0x0000FD4Fu, 0x00000000u },  // 0000FD4E
        { 0x0000062Au, 0x0000062Cu }, { 0x0000062Au, 0x0000062Du },  // 0000FD50
        { 0x0000062Au, 0x0000062Du }, { 0x0000062Au, 0x0000062Du },  // 0000FD52
        { 0x0000062Au, 0x0000062Eu }, { 0x0000062Au, 0x00000645u },  // 0000FD54
        { 0x0000062Au, 0x00000645u }, { 0x0000062Au, 0x00000645u },  // 0000FD56
        { 0x0000062Cu, 0x00000645u }, { 0x0000062Cu, 0x00000645u },  // 0000FD58
        { 0x0000062Du, 0x00000645u }, { 0x0000062Du, 0x00000645u },  // 0000FD5A
        { 0x00000633u, 0x0000062Du }, { 0x00000633u, 0x0000062Cu },  // 0000FD5C
        { 0x00000633u, 0x0000062Cu }, { 0x00000633u, 0x00000645u },  // 0000FD5E
        { 0x00000633u, 0x00000645u }, { 0x00000633u, 0x00000645u },  // 0000FD60
        { 0x00000633u, 0x00000645u }, { 0x00000633u, 0x00000645u },  // 0000FD62
        { 0x00000635u, 0x0000062Du }, { 0x00000635u, 0x0000062Du },  // 0000FD64
        { 0x00000635u, 0x00000645u }, { 0x00000634u, 0x0000062Du },  // 0000FD66
        { 0x00000634u, 0x0000062Du }, { 0x00000634u, 0x0000062Cu },  // 0000FD68
        { 0x00000634u, 0x00000645u }, { 0x00000634u, 0x00000645u },  // 0000FD6A
        { 0x00000634u, 0x00000645u }, { 0x00000634u, 0x00000645u },  // 0000FD6C
        { 0x00000636u, 0x0000062Du }, { 0x00000636u, 0x0000062Eu },  // 0000FD6E
        { 0x00000636u, 0x0000062Eu }, { 0x00000637u, 0x00000645u },  // 0000FD70
        { 0x00000637u, 0x00000645u }, { 0x00000637u, 0x00000645u },  // 0000FD72
        { 0x00000637u, 0x00000645u }, { 0x00000639u, 0x0000062Cu },  // 0000FD74
        { 0x00000639u, 0x00000645u }, { 0x00000639u, 0x00000645u },  // 0000FD76
        { 0x00000639u, 0x00000645u }, { 0x0000063Au, 0x00000645u },  // 0000FD78
        { 0x0000063Au, 0x00000645u }, { 0x0000063Au, 0x00000645u },  // 0000FD7A
        { 0x00000641u, 0x0000062Eu }, { 0x00000641u, 0x0000062Eu },  // 0000FD7C
        { 0x00000642u, 0x00000645u }, { 0x00000642u, 0x00000645u },  // 0000FD7E
        { 0x00000644u, 0x0000062Du }, { 0x00000644u, 0x0000062Du },  // 0000FD80
        { 0x00000644u, 0x0000062Du }, { 0x00000644u, 0x0000062Cu },  // 0000FD82
        { 0x00000644u, 0x0000062Cu }, { 0x00000644u, 0x0000062Eu },  // 0000FD84
        { 0x00000644u, 0x0000062Eu }, { 0x00000644u, 0x00000645u },  // 0000FD86
        { 0x00000644u, 0x00000645u }, { 0x00000645u, 0x0000062Du },  // 0000FD88
        { 0x00000645u, 0x0000062Du }, { 0x00000645u, 0x0000062Du },  // 0000FD8A
        { 0x00000645u, 0x0000062Cu }, { 0x00000645u, 0x0000062Cu },  // 0000FD8C
        { 0x00000645u, 0x0000062Eu }, { 0x00000645u, 0x0000062Eu },  // 0000FD8E
        { 0x0000FD90u, 0x00000000u }, { 0x0000FD91u, 0x00000000u },  // 0000FD90
        { 0x00000645u, 0x0000062Cu }, { 0x00000647u, 0x00000645u },  // 0000FD92
        { 0x00000647u, 0x00000645u }, { 0x00000646u, 0x0000062Du },  // 0000FD94
        { 0x00000646u, 0x0000062Du }, { 0x00000646u, 0x0000062Cu },  // 0000FD96
        { 0x00000646u, 0x0000062Cu }, { 0x00000646u, 0x0000062Cu },  // 0000FD98
        { 0x00000646u, 0x00000645u }, { 0x00000646u, 0x00000645u },  // 0000FD9A
        { 0x0000064Au, 0x00000645u }, { 0x0000064Au, 0x00000645u },  // 0000FD9C
        { 0x00000628u, 0x0000062Eu }, { 0x0000062Au, 0x0000062Cu },  // 0000FD9E
        { 0x0000062Au, 0x0000062Cu }, { 0x0000062Au, 0x0000062Eu },  // 0000FDA0
        { 0x0000062Au, 0x0000062Eu }, { 0x0000062Au, 0x00000645u },  // 0000FDA2
        { 0x0000062Au, 0x00000645u }, { 0x0000062Cu, 0x00000645u },  // 0000FDA4
        { 0x0000062Cu, 0x0000062Du }, { 0x0000062Cu, 0x00000645u },  // 0000FDA6
        { 0x00000633u, 0x0000062Eu }, { 0x00000635u, 0x0000062Du },  // 0000FDA8
        { 0x00000634u, 0x0000062Du }, { 0x00000636u, 0x0000062Du },  // 0000FDAA
        { 0x00000644u, 0x0000062Cu }, { 0x00000644u, 0x00000645u },  // 0000FDAC
        { 0x0000064Au, 0x0000062Du }, { 0x0000064Au, 0x0000062Cu },  // 0000FDAE
        { 0x0000064Au, 0x00000645u }, { 0x00000645u, 0x00000645u },  // 0000FDB0
        { 0x00000642u, 0x00000645u }, { 0x00000646u, 0x0000062Du },  // 0000FDB2
        { 0x00000642u, 0x00000645u }, { 0x00000644u, 0x0000062Du },  // 0000FDB4
        { 0x00000639u, 0x00000645u }, { 0x00000643u, 0x00000645u },  // 0000FDB6
        { 0x00000646u, 0x0000062Cu }, { 0x00000645u, 0x0000062Eu },  // 0000FDB8
        { 0x00000644u, 0x0000062Cu }, { 0x00000643u, 0x00000645u },  // 0000FDBA
        { 0x00000644u, 0x0000062Cu }, { 0x00000646u, 0x0000062Cu },  // 0000FDBC
        { 0x0000062Cu, 0x0000062Du }, { 0x0000062Du, 0x0000062Cu },  // 0000FDBE
        { 0x00000645u, 0x0000062Cu }, { 0x00000641u, 0x00000645u },  // 0000FDC0
        { 0x00000628u, 0x0000062Du }, { 0x00000643u, 0x00000645u },  // 0000FDC2
        { 0x00000639u, 0x0000062Cu }, { 0x00000635u, 0x00000645u },  // 0000FDC4
        { 0x00000633u, 0x0000062Eu }, { 0x00000646u, 0x0000062Cu },  // 0000FDC6
        { 0x0000FDC8u, 0x00000000u }, { 0x0000FDC9u, 0x00000000u },  // 0000FDC8
        { 0x0000FDCAu, 0x00000000u }, { 0x0000FDCBu, 0x00000000u },  // 0000FDCA
        { 0x0000FDCCu, 0x00000000u }, { 0x0000FDCDu, 0x00000000u },  // 0000FDCC
        { 0x0000FDCEu, 0x00000000u }, { 0x0000FDCFu, 0x00000000u },  // 0000FDCE
        { 0x0000FDD0u, 0x00000000u }, { 0x0000FDD1u, 0x00000000u },  // 0000FDD0
        { 0x0000FDD2u, 0x00000000u }, { 0x0000FDD3u, 0x00000000u },  // 0000FDD2
        { 0x0000FDD4u, 0x00000000u }, { 0x0000FDD5u, 0x00000000u },  // 0000FDD4
        { 0x0000FDD6u, 0x00000000u }, { 0x0000FDD7u, 0x00000000u },  // 0000FDD6
        { 0x0000FDD8u, 0x00000000u }, { 0x0000FDD9u, 0x00000000u },  // 0000FDD8
        { 0x0000FDDAu, 0x00000000u }, { 0x0000FDDBu, 0x00000000u },  // 0000FDDA
        { 0x0000FDDCu, 0x00000000u }, { 0x0000FDDDu, 0x00000000u },  // 0000FDDC
        { 0x0000FDDEu, 0x00000000u }, { 0x0000FDDFu, 0x00000000u },  // 0000FDDE
        { 0x0000FDE0u, 0x00000000u }, { 0x0000FDE1u, 0x00000000u },  // 0000FDE0
        { 0x0000FDE2u, 0x00000000u }, { 0x0000FDE3u, 0x00000000u },  // 0000FDE2
        { 0x0000FDE4u, 0x00000000u }, { 0x0000FDE5u, 0x00000000u },  // 0000FDE4
        { 0x0000FDE6u, 0x00000000u }, { 0x0000FDE7u, 0x00000000u },  // 0000FDE6
        { 0x0000FDE8u, 0x00000000u }, { 0x0000FDE9u, 0x00000000u },  // 0000FDE8
        { 0x0000FDEAu, 0x00000000u }, { 0x0000FDEBu, 0x00000000u },  // 0000FDEA
        { 0x0000FDECu, 0x00000000u }, { 0x0000FDEDu, 0x00000000u },  // 0000FDEC
        { 0x0000FDEEu, 0x00000000u }, { 0x0000FDEFu, 0x00000000u },  // 0000FDEE
        { 0x00000635u, 0x00000644u }, { 0x00000642u, 0x00000644u },  // 0000FDF0
        { 0x00000627u, 0x00000644u }, { 0x00000627u, 0x00000643u },  // 0000FDF2
        { 0x00000645u, 0x0000062Du }, { 0x00000635u, 0x00000644u },  // 0000FDF4
        { 0x00000631u, 0x00000633u }, { 0x00000639u, 0x00000644u },  // 0000FDF6
        { 0x00000648u, 0x00000633u }, { 0x00000635u, 0x00000644u },  // 0000FDF8
        { 0x00000635u, 0x00000644u }, { 0x0000062Cu, 0x00000644u },  // 0000FDFA
        { 0x00000631u, 0x000006CCu }, { 0x0000FDFDu, 0x00000000u },  // 0000FDFC
        { 0x0000FDFEu, 0x00000000u }, { 0x0000FDFFu, 0x00000000u }
    };

    const unsigned char Arabic_Presentation_FormsAFB50::my_lb[] =
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
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_OP, LB_CL, 
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
        LB_AL, LB_AL, LB_AL, LB_AL, LB_PO, LB_AL, LB_AL, LB_AL
    };

    const std::bitset<688> Arabic_Presentation_FormsAFB50::my_Noncharacter_Code_Point(std::string("0000000000000000111111111111111111111111111111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<688> Arabic_Presentation_FormsAFB50::my_XID_Start_Closure(std::string("0000110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000111111000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<688> Arabic_Presentation_FormsAFB50::my_XID_Continue_Closure(std::string("0000110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000111111000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));

  }; // namespace
}; // namespace

dload(Babylon::Module::Arabic_Presentation_FormsAFB50);
