/*$Id: UnicodePluginGenerator.pl,v 1.6 2002/05/31 23:42:14 tobias Exp 2F00-2FDF.cc
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


namespace Babylon
{
  namespace Module
  {
    class Kangxi_Radicals2F00 : public Babylon::Block
    {
      public:
        void clean() { };

        Kangxi_Radicals2F00() :
	    my_first_letter(0x2F00),
	    my_last_letter(0x2FDF)
	    // my_version="4.0" // Not yet supported!
        {
        }

        ~Kangxi_Radicals2F00() { }

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
	    return "Kangxi Radicals";
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
            return Babylon::Gen_Cat(CAT_So);
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
            return BIDIR_ON;
        }

        Char_Decomp decomp_type(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return DECOMP_MAX;
            return Babylon::Char_Decomp(Kangxi_Radicals2F00::my_decomp[uc - my_first_letter]);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            Babylon::UTF32_string us;
            us.resize(1);
            us[0] = Kangxi_Radicals2F00::my_decompStr[uc - my_first_letter];
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
            return my_Radical.test(uc - my_first_letter);
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

      private:
        // functions
        Kangxi_Radicals2F00(const Kangxi_Radicals2F00 &) ; // no implementaion!

	// members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const std::bitset<224> my_is_defined;
        static const unsigned char my_decomp[224];
        static const UCS4 my_decompStr[224];
        static const std::bitset<224> my_Radical;
    }; // class Kangxi_Radicals2F00

    const std::bitset<224> Kangxi_Radicals2F00::my_is_defined(std::string("00000000001111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"));

    const unsigned char Kangxi_Radicals2F00::my_decomp[] = {
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL
    };

    const UCS4 Kangxi_Radicals2F00::my_decompStr[] =
    {
        0x00004E00u, 0x00004E28u, 0x00004E36u, 0x00004E3Fu,  // 00002F00
        0x00004E59u, 0x00004E85u, 0x00004E8Cu, 0x00004EA0u,  // 00002F04
        0x00004EBAu, 0x0000513Fu, 0x00005165u, 0x0000516Bu,  // 00002F08
        0x00005182u, 0x00005196u, 0x000051ABu, 0x000051E0u,  // 00002F0C
        0x000051F5u, 0x00005200u, 0x0000529Bu, 0x000052F9u,  // 00002F10
        0x00005315u, 0x0000531Au, 0x00005338u, 0x00005341u,  // 00002F14
        0x0000535Cu, 0x00005369u, 0x00005382u, 0x000053B6u,  // 00002F18
        0x000053C8u, 0x000053E3u, 0x000056D7u, 0x0000571Fu,  // 00002F1C
        0x000058EBu, 0x00005902u, 0x0000590Au, 0x00005915u,  // 00002F20
        0x00005927u, 0x00005973u, 0x00005B50u, 0x00005B80u,  // 00002F24
        0x00005BF8u, 0x00005C0Fu, 0x00005C22u, 0x00005C38u,  // 00002F28
        0x00005C6Eu, 0x00005C71u, 0x00005DDBu, 0x00005DE5u,  // 00002F2C
        0x00005DF1u, 0x00005DFEu, 0x00005E72u, 0x00005E7Au,  // 00002F30
        0x00005E7Fu, 0x00005EF4u, 0x00005EFEu, 0x00005F0Bu,  // 00002F34
        0x00005F13u, 0x00005F50u, 0x00005F61u, 0x00005F73u,  // 00002F38
        0x00005FC3u, 0x00006208u, 0x00006236u, 0x0000624Bu,  // 00002F3C
        0x0000652Fu, 0x00006534u, 0x00006587u, 0x00006597u,  // 00002F40
        0x000065A4u, 0x000065B9u, 0x000065E0u, 0x000065E5u,  // 00002F44
        0x000066F0u, 0x00006708u, 0x00006728u, 0x00006B20u,  // 00002F48
        0x00006B62u, 0x00006B79u, 0x00006BB3u, 0x00006BCBu,  // 00002F4C
        0x00006BD4u, 0x00006BDBu, 0x00006C0Fu, 0x00006C14u,  // 00002F50
        0x00006C34u, 0x0000706Bu, 0x0000722Au, 0x00007236u,  // 00002F54
        0x0000723Bu, 0x0000723Fu, 0x00007247u, 0x00007259u,  // 00002F58
        0x0000725Bu, 0x000072ACu, 0x00007384u, 0x00007389u,  // 00002F5C
        0x000074DCu, 0x000074E6u, 0x00007518u, 0x0000751Fu,  // 00002F60
        0x00007528u, 0x00007530u, 0x0000758Bu, 0x00007592u,  // 00002F64
        0x00007676u, 0x0000767Du, 0x000076AEu, 0x000076BFu,  // 00002F68
        0x000076EEu, 0x000077DBu, 0x000077E2u, 0x000077F3u,  // 00002F6C
        0x0000793Au, 0x000079B8u, 0x000079BEu, 0x00007A74u,  // 00002F70
        0x00007ACBu, 0x00007AF9u, 0x00007C73u, 0x00007CF8u,  // 00002F74
        0x00007F36u, 0x00007F51u, 0x00007F8Au, 0x00007FBDu,  // 00002F78
        0x00008001u, 0x0000800Cu, 0x00008012u, 0x00008033u,  // 00002F7C
        0x0000807Fu, 0x00008089u, 0x000081E3u, 0x000081EAu,  // 00002F80
        0x000081F3u, 0x000081FCu, 0x0000820Cu, 0x0000821Bu,  // 00002F84
        0x0000821Fu, 0x0000826Eu, 0x00008272u, 0x00008278u,  // 00002F88
        0x0000864Du, 0x0000866Bu, 0x00008840u, 0x0000884Cu,  // 00002F8C
        0x00008863u, 0x0000897Eu, 0x0000898Bu, 0x000089D2u,  // 00002F90
        0x00008A00u, 0x00008C37u, 0x00008C46u, 0x00008C55u,  // 00002F94
        0x00008C78u, 0x00008C9Du, 0x00008D64u, 0x00008D70u,  // 00002F98
        0x00008DB3u, 0x00008EABu, 0x00008ECAu, 0x00008F9Bu,  // 00002F9C
        0x00008FB0u, 0x00008FB5u, 0x00009091u, 0x00009149u,  // 00002FA0
        0x000091C6u, 0x000091CCu, 0x000091D1u, 0x00009577u,  // 00002FA4
        0x00009580u, 0x0000961Cu, 0x000096B6u, 0x000096B9u,  // 00002FA8
        0x000096E8u, 0x00009751u, 0x0000975Eu, 0x00009762u,  // 00002FAC
        0x00009769u, 0x000097CBu, 0x000097EDu, 0x000097F3u,  // 00002FB0
        0x00009801u, 0x000098A8u, 0x000098DBu, 0x000098DFu,  // 00002FB4
        0x00009996u, 0x00009999u, 0x000099ACu, 0x00009AA8u,  // 00002FB8
        0x00009AD8u, 0x00009ADFu, 0x00009B25u, 0x00009B2Fu,  // 00002FBC
        0x00009B32u, 0x00009B3Cu, 0x00009B5Au, 0x00009CE5u,  // 00002FC0
        0x00009E75u, 0x00009E7Fu, 0x00009EA5u, 0x00009EBBu,  // 00002FC4
        0x00009EC3u, 0x00009ECDu, 0x00009ED1u, 0x00009EF9u,  // 00002FC8
        0x00009EFDu, 0x00009F0Eu, 0x00009F13u, 0x00009F20u,  // 00002FCC
        0x00009F3Bu, 0x00009F4Au, 0x00009F52u, 0x00009F8Du,  // 00002FD0
        0x00009F9Cu, 0x00009FA0u, 0x00002FD6u, 0x00002FD7u,  // 00002FD4
        0x00002FD8u, 0x00002FD9u, 0x00002FDAu, 0x00002FDBu,  // 00002FD8
        0x00002FDCu, 0x00002FDDu, 0x00002FDEu, 0x00002FDFu
    };

    const std::bitset<224> Kangxi_Radicals2F00::my_Radical(std::string("00000000001111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"));

  }; // namespace
}; // namespace

dload(Babylon::Module::Kangxi_Radicals2F00);
