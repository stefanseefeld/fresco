/*$Id: UnicodePluginGenerator.pl,v 1.7 2003/08/01 16:47:16 tobias Exp F900-FAFF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 05 Aug 2003 17:10:25 +0200.
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
    class CJK_Compatibility_IdeographsF900 : public Babylon::Block
    {
      public:
        void clean() { };

        CJK_Compatibility_IdeographsF900() :
	    my_first_letter(0xF900),
	    my_last_letter(0xFAFF)
	    // my_version="4.0" // Not yet supported!
        {
        }

        ~CJK_Compatibility_IdeographsF900() { }

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
	    return "CJK Compatibility Ideographs";
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
            return Babylon::Gen_Cat(CAT_Lo);
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
            return Babylon::Char_Decomp(DECOMP_CANONICAL);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            Babylon::UTF32_string us;
            us.resize(1);
            us[0] = CJK_Compatibility_IdeographsF900::my_decompStr[uc - my_first_letter];
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
            return my_Ideographic.test(uc - my_first_letter);
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
            return my_Unified_Ideograph.test(uc - my_first_letter);
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
        CJK_Compatibility_IdeographsF900(const CJK_Compatibility_IdeographsF900 &) ; // no implementaion!

	// members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const std::bitset<512> my_is_defined;
        static const UCS4 my_decompStr[512];
        static const std::bitset<512> my_Ideographic;
        static const std::bitset<512> my_Unified_Ideograph;
    }; // class CJK_Compatibility_IdeographsF900

    const std::bitset<512> CJK_Compatibility_IdeographsF900::my_is_defined(std::string("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000111111111111111111111111111111111111111111111111111111111110011111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"));

    const UCS4 CJK_Compatibility_IdeographsF900::my_decompStr[] =
    {
        0x00008C48u, 0x000066F4u, 0x00008ECAu, 0x00008CC8u,  // 0000F900
        0x00006ED1u, 0x00004E32u, 0x000053E5u, 0x00009F9Cu,  // 0000F904
        0x00009F9Cu, 0x00005951u, 0x000091D1u, 0x00005587u,  // 0000F908
        0x00005948u, 0x000061F6u, 0x00007669u, 0x00007F85u,  // 0000F90C
        0x0000863Fu, 0x000087BAu, 0x000088F8u, 0x0000908Fu,  // 0000F910
        0x00006A02u, 0x00006D1Bu, 0x000070D9u, 0x000073DEu,  // 0000F914
        0x0000843Du, 0x0000916Au, 0x000099F1u, 0x00004E82u,  // 0000F918
        0x00005375u, 0x00006B04u, 0x0000721Bu, 0x0000862Du,  // 0000F91C
        0x00009E1Eu, 0x00005D50u, 0x00006FEBu, 0x000085CDu,  // 0000F920
        0x00008964u, 0x000062C9u, 0x000081D8u, 0x0000881Fu,  // 0000F924
        0x00005ECAu, 0x00006717u, 0x00006D6Au, 0x000072FCu,  // 0000F928
        0x000090CEu, 0x00004F86u, 0x000051B7u, 0x000052DEu,  // 0000F92C
        0x000064C4u, 0x00006AD3u, 0x00007210u, 0x000076E7u,  // 0000F930
        0x00008001u, 0x00008606u, 0x0000865Cu, 0x00008DEFu,  // 0000F934
        0x00009732u, 0x00009B6Fu, 0x00009DFAu, 0x0000788Cu,  // 0000F938
        0x0000797Fu, 0x00007DA0u, 0x000083C9u, 0x00009304u,  // 0000F93C
        0x00009E7Fu, 0x00008AD6u, 0x000058DFu, 0x00005F04u,  // 0000F940
        0x00007C60u, 0x0000807Eu, 0x00007262u, 0x000078CAu,  // 0000F944
        0x00008CC2u, 0x000096F7u, 0x000058D8u, 0x00005C62u,  // 0000F948
        0x00006A13u, 0x00006DDAu, 0x00006F0Fu, 0x00007D2Fu,  // 0000F94C
        0x00007E37u, 0x0000964Bu, 0x000052D2u, 0x0000808Bu,  // 0000F950
        0x000051DCu, 0x000051CCu, 0x00007A1Cu, 0x00007DBEu,  // 0000F954
        0x000083F1u, 0x00009675u, 0x00008B80u, 0x000062CFu,  // 0000F958
        0x00006A02u, 0x00008AFEu, 0x00004E39u, 0x00005BE7u,  // 0000F95C
        0x00006012u, 0x00007387u, 0x00007570u, 0x00005317u,  // 0000F960
        0x000078FBu, 0x00004FBFu, 0x00005FA9u, 0x00004E0Du,  // 0000F964
        0x00006CCCu, 0x00006578u, 0x00007D22u, 0x000053C3u,  // 0000F968
        0x0000585Eu, 0x00007701u, 0x00008449u, 0x00008AAAu,  // 0000F96C
        0x00006BBAu, 0x00008FB0u, 0x00006C88u, 0x000062FEu,  // 0000F970
        0x000082E5u, 0x000063A0u, 0x00007565u, 0x00004EAEu,  // 0000F974
        0x00005169u, 0x000051C9u, 0x00006881u, 0x00007CE7u,  // 0000F978
        0x0000826Fu, 0x00008AD2u, 0x000091CFu, 0x000052F5u,  // 0000F97C
        0x00005442u, 0x00005973u, 0x00005EECu, 0x000065C5u,  // 0000F980
        0x00006FFEu, 0x0000792Au, 0x000095ADu, 0x00009A6Au,  // 0000F984
        0x00009E97u, 0x00009ECEu, 0x0000529Bu, 0x000066C6u,  // 0000F988
        0x00006B77u, 0x00008F62u, 0x00005E74u, 0x00006190u,  // 0000F98C
        0x00006200u, 0x0000649Au, 0x00006F23u, 0x00007149u,  // 0000F990
        0x00007489u, 0x000079CAu, 0x00007DF4u, 0x0000806Fu,  // 0000F994
        0x00008F26u, 0x000084EEu, 0x00009023u, 0x0000934Au,  // 0000F998
        0x00005217u, 0x000052A3u, 0x000054BDu, 0x000070C8u,  // 0000F99C
        0x000088C2u, 0x00008AAAu, 0x00005EC9u, 0x00005FF5u,  // 0000F9A0
        0x0000637Bu, 0x00006BAEu, 0x00007C3Eu, 0x00007375u,  // 0000F9A4
        0x00004EE4u, 0x000056F9u, 0x00005BE7u, 0x00005DBAu,  // 0000F9A8
        0x0000601Cu, 0x000073B2u, 0x00007469u, 0x00007F9Au,  // 0000F9AC
        0x00008046u, 0x00009234u, 0x000096F6u, 0x00009748u,  // 0000F9B0
        0x00009818u, 0x00004F8Bu, 0x000079AEu, 0x000091B4u,  // 0000F9B4
        0x000096B8u, 0x000060E1u, 0x00004E86u, 0x000050DAu,  // 0000F9B8
        0x00005BEEu, 0x00005C3Fu, 0x00006599u, 0x00006A02u,  // 0000F9BC
        0x000071CEu, 0x00007642u, 0x000084FCu, 0x0000907Cu,  // 0000F9C0
        0x00009F8Du, 0x00006688u, 0x0000962Eu, 0x00005289u,  // 0000F9C4
        0x0000677Bu, 0x000067F3u, 0x00006D41u, 0x00006E9Cu,  // 0000F9C8
        0x00007409u, 0x00007559u, 0x0000786Bu, 0x00007D10u,  // 0000F9CC
        0x0000985Eu, 0x0000516Du, 0x0000622Eu, 0x00009678u,  // 0000F9D0
        0x0000502Bu, 0x00005D19u, 0x00006DEAu, 0x00008F2Au,  // 0000F9D4
        0x00005F8Bu, 0x00006144u, 0x00006817u, 0x00007387u,  // 0000F9D8
        0x00009686u, 0x00005229u, 0x0000540Fu, 0x00005C65u,  // 0000F9DC
        0x00006613u, 0x0000674Eu, 0x000068A8u, 0x00006CE5u,  // 0000F9E0
        0x00007406u, 0x000075E2u, 0x00007F79u, 0x000088CFu,  // 0000F9E4
        0x000088E1u, 0x000091CCu, 0x000096E2u, 0x0000533Fu,  // 0000F9E8
        0x00006EBAu, 0x0000541Du, 0x000071D0u, 0x00007498u,  // 0000F9EC
        0x000085FAu, 0x000096A3u, 0x00009C57u, 0x00009E9Fu,  // 0000F9F0
        0x00006797u, 0x00006DCBu, 0x000081E8u, 0x00007ACBu,  // 0000F9F4
        0x00007B20u, 0x00007C92u, 0x000072C0u, 0x00007099u,  // 0000F9F8
        0x00008B58u, 0x00004EC0u, 0x00008336u, 0x0000523Au,  // 0000F9FC
        0x00005207u, 0x00005EA6u, 0x000062D3u, 0x00007CD6u,  // 0000FA00
        0x00005B85u, 0x00006D1Eu, 0x000066B4u, 0x00008F3Bu,  // 0000FA04
        0x0000884Cu, 0x0000964Du, 0x0000898Bu, 0x00005ED3u,  // 0000FA08
        0x00005140u, 0x000055C0u, 0x0000FA0Eu, 0x0000FA0Fu,  // 0000FA0C
        0x0000585Au, 0x0000FA11u, 0x00006674u, 0x0000FA13u,  // 0000FA10
        0x0000FA14u, 0x000051DEu, 0x0000732Au, 0x000076CAu,  // 0000FA14
        0x0000793Cu, 0x0000795Eu, 0x00007965u, 0x0000798Fu,  // 0000FA18
        0x00009756u, 0x00007CBEu, 0x00007FBDu, 0x0000FA1Fu,  // 0000FA1C
        0x00008612u, 0x0000FA21u, 0x00008AF8u, 0x0000FA23u,  // 0000FA20
        0x0000FA24u, 0x00009038u, 0x000090FDu, 0x0000FA27u,  // 0000FA24
        0x0000FA28u, 0x0000FA29u, 0x000098EFu, 0x000098FCu,  // 0000FA28
        0x00009928u, 0x00009DB4u, 0x0000FA2Eu, 0x0000FA2Fu,  // 0000FA2C
        0x00004FAEu, 0x000050E7u, 0x0000514Du, 0x000052C9u,  // 0000FA30
        0x000052E4u, 0x00005351u, 0x0000559Du, 0x00005606u,  // 0000FA34
        0x00005668u, 0x00005840u, 0x000058A8u, 0x00005C64u,  // 0000FA38
        0x00005C6Eu, 0x00006094u, 0x00006168u, 0x0000618Eu,  // 0000FA3C
        0x000061F2u, 0x0000654Fu, 0x000065E2u, 0x00006691u,  // 0000FA40
        0x00006885u, 0x00006D77u, 0x00006E1Au, 0x00006F22u,  // 0000FA44
        0x0000716Eu, 0x0000722Bu, 0x00007422u, 0x00007891u,  // 0000FA48
        0x0000793Eu, 0x00007949u, 0x00007948u, 0x00007950u,  // 0000FA4C
        0x00007956u, 0x0000795Du, 0x0000798Du, 0x0000798Eu,  // 0000FA50
        0x00007A40u, 0x00007A81u, 0x00007BC0u, 0x00007DF4u,  // 0000FA54
        0x00007E09u, 0x00007E41u, 0x00007F72u, 0x00008005u,  // 0000FA58
        0x000081EDu, 0x00008279u, 0x00008279u, 0x00008457u,  // 0000FA5C
        0x00008910u, 0x00008996u, 0x00008B01u, 0x00008B39u,  // 0000FA60
        0x00008CD3u, 0x00008D08u, 0x00008FB6u, 0x00009038u,  // 0000FA64
        0x000096E3u, 0x000097FFu, 0x0000983Bu, 0x0000FA6Bu,  // 0000FA68
        0x0000FA6Cu, 0x0000FA6Du, 0x0000FA6Eu, 0x0000FA6Fu,  // 0000FA6C
        0x0000FA70u, 0x0000FA71u, 0x0000FA72u, 0x0000FA73u,  // 0000FA70
        0x0000FA74u, 0x0000FA75u, 0x0000FA76u, 0x0000FA77u,  // 0000FA74
        0x0000FA78u, 0x0000FA79u, 0x0000FA7Au, 0x0000FA7Bu,  // 0000FA78
        0x0000FA7Cu, 0x0000FA7Du, 0x0000FA7Eu, 0x0000FA7Fu,  // 0000FA7C
        0x0000FA80u, 0x0000FA81u, 0x0000FA82u, 0x0000FA83u,  // 0000FA80
        0x0000FA84u, 0x0000FA85u, 0x0000FA86u, 0x0000FA87u,  // 0000FA84
        0x0000FA88u, 0x0000FA89u, 0x0000FA8Au, 0x0000FA8Bu,  // 0000FA88
        0x0000FA8Cu, 0x0000FA8Du, 0x0000FA8Eu, 0x0000FA8Fu,  // 0000FA8C
        0x0000FA90u, 0x0000FA91u, 0x0000FA92u, 0x0000FA93u,  // 0000FA90
        0x0000FA94u, 0x0000FA95u, 0x0000FA96u, 0x0000FA97u,  // 0000FA94
        0x0000FA98u, 0x0000FA99u, 0x0000FA9Au, 0x0000FA9Bu,  // 0000FA98
        0x0000FA9Cu, 0x0000FA9Du, 0x0000FA9Eu, 0x0000FA9Fu,  // 0000FA9C
        0x0000FAA0u, 0x0000FAA1u, 0x0000FAA2u, 0x0000FAA3u,  // 0000FAA0
        0x0000FAA4u, 0x0000FAA5u, 0x0000FAA6u, 0x0000FAA7u,  // 0000FAA4
        0x0000FAA8u, 0x0000FAA9u, 0x0000FAAAu, 0x0000FAABu,  // 0000FAA8
        0x0000FAACu, 0x0000FAADu, 0x0000FAAEu, 0x0000FAAFu,  // 0000FAAC
        0x0000FAB0u, 0x0000FAB1u, 0x0000FAB2u, 0x0000FAB3u,  // 0000FAB0
        0x0000FAB4u, 0x0000FAB5u, 0x0000FAB6u, 0x0000FAB7u,  // 0000FAB4
        0x0000FAB8u, 0x0000FAB9u, 0x0000FABAu, 0x0000FABBu,  // 0000FAB8
        0x0000FABCu, 0x0000FABDu, 0x0000FABEu, 0x0000FABFu,  // 0000FABC
        0x0000FAC0u, 0x0000FAC1u, 0x0000FAC2u, 0x0000FAC3u,  // 0000FAC0
        0x0000FAC4u, 0x0000FAC5u, 0x0000FAC6u, 0x0000FAC7u,  // 0000FAC4
        0x0000FAC8u, 0x0000FAC9u, 0x0000FACAu, 0x0000FACBu,  // 0000FAC8
        0x0000FACCu, 0x0000FACDu, 0x0000FACEu, 0x0000FACFu,  // 0000FACC
        0x0000FAD0u, 0x0000FAD1u, 0x0000FAD2u, 0x0000FAD3u,  // 0000FAD0
        0x0000FAD4u, 0x0000FAD5u, 0x0000FAD6u, 0x0000FAD7u,  // 0000FAD4
        0x0000FAD8u, 0x0000FAD9u, 0x0000FADAu, 0x0000FADBu,  // 0000FAD8
        0x0000FADCu, 0x0000FADDu, 0x0000FADEu, 0x0000FADFu,  // 0000FADC
        0x0000FAE0u, 0x0000FAE1u, 0x0000FAE2u, 0x0000FAE3u,  // 0000FAE0
        0x0000FAE4u, 0x0000FAE5u, 0x0000FAE6u, 0x0000FAE7u,  // 0000FAE4
        0x0000FAE8u, 0x0000FAE9u, 0x0000FAEAu, 0x0000FAEBu,  // 0000FAE8
        0x0000FAECu, 0x0000FAEDu, 0x0000FAEEu, 0x0000FAEFu,  // 0000FAEC
        0x0000FAF0u, 0x0000FAF1u, 0x0000FAF2u, 0x0000FAF3u,  // 0000FAF0
        0x0000FAF4u, 0x0000FAF5u, 0x0000FAF6u, 0x0000FAF7u,  // 0000FAF4
        0x0000FAF8u, 0x0000FAF9u, 0x0000FAFAu, 0x0000FAFBu,  // 0000FAF8
        0x0000FAFCu, 0x0000FAFDu, 0x0000FAFEu, 0x0000FAFFu
    };

    const std::bitset<512> CJK_Compatibility_IdeographsF900::my_Ideographic(std::string("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000011111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"));

    const std::bitset<512> CJK_Compatibility_IdeographsF900::my_Unified_Ideograph(std::string("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001110011010100000000001101011000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));

  }; // namespace
}; // namespace

dload(Babylon::Module::CJK_Compatibility_IdeographsF900);
