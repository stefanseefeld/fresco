/*$Id: UnicodePluginGenerator.pl,v 1.11 2004/01/28 12:39:04 tobias Exp 2F800-2FA1F.cc
 *
 * This source file is a part of the Fresco Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Wed, 28 Jan 2004 20:50:29 +0100.
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
    class CJK_Compatibility_Ideographs_Supplement2F800 : public Babylon::Block
    {
      public:
        void clean() { };

        CJK_Compatibility_Ideographs_Supplement2F800() :
        my_first_letter(0x2F800),
        my_last_letter(0x2FA1F)
        // my_version="4.0" // Not yet supported!
        {
        }

        ~CJK_Compatibility_Ideographs_Supplement2F800() { }

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
        return "CJK Compatibility Ideographs Supplement";
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
            us[0] = CJK_Compatibility_Ideographs_Supplement2F800::my_decompStr[uc - my_first_letter];
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
        CJK_Compatibility_Ideographs_Supplement2F800(const CJK_Compatibility_Ideographs_Supplement2F800 &) ; // no implementaion!

    // members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const std::bitset<544> my_is_defined;
        static const UCS4 my_decompStr[544];
        static const std::bitset<544> my_Ideographic;
    }; // class CJK_Compatibility_Ideographs_Supplement2F800

    const std::bitset<544> CJK_Compatibility_Ideographs_Supplement2F800::my_is_defined(std::string("0011111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"));

    const UCS4 CJK_Compatibility_Ideographs_Supplement2F800::my_decompStr[] =
    {
        0x00004E3Du, 0x00004E38u, 0x00004E41u, 0x00020122u,  // 0002F800
        0x00004F60u, 0x00004FAEu, 0x00004FBBu, 0x00005002u,  // 0002F804
        0x0000507Au, 0x00005099u, 0x000050E7u, 0x000050CFu,  // 0002F808
        0x0000349Eu, 0x0002063Au, 0x0000514Du, 0x00005154u,  // 0002F80C
        0x00005164u, 0x00005177u, 0x0002051Cu, 0x000034B9u,  // 0002F810
        0x00005167u, 0x0000518Du, 0x0002054Bu, 0x00005197u,  // 0002F814
        0x000051A4u, 0x00004ECCu, 0x000051ACu, 0x000051B5u,  // 0002F818
        0x000291DFu, 0x000051F5u, 0x00005203u, 0x000034DFu,  // 0002F81C
        0x0000523Bu, 0x00005246u, 0x00005272u, 0x00005277u,  // 0002F820
        0x00003515u, 0x000052C7u, 0x000052C9u, 0x000052E4u,  // 0002F824
        0x000052FAu, 0x00005305u, 0x00005306u, 0x00005317u,  // 0002F828
        0x00005349u, 0x00005351u, 0x0000535Au, 0x00005373u,  // 0002F82C
        0x0000537Du, 0x0000537Fu, 0x0000537Fu, 0x0000537Fu,  // 0002F830
        0x00020A2Cu, 0x00007070u, 0x000053CAu, 0x000053DFu,  // 0002F834
        0x00020B63u, 0x000053EBu, 0x000053F1u, 0x00005406u,  // 0002F838
        0x0000549Eu, 0x00005438u, 0x00005448u, 0x00005468u,  // 0002F83C
        0x000054A2u, 0x000054F6u, 0x00005510u, 0x00005553u,  // 0002F840
        0x00005563u, 0x00005584u, 0x00005584u, 0x00005599u,  // 0002F844
        0x000055ABu, 0x000055B3u, 0x000055C2u, 0x00005716u,  // 0002F848
        0x00005606u, 0x00005717u, 0x00005651u, 0x00005674u,  // 0002F84C
        0x00005207u, 0x000058EEu, 0x000057CEu, 0x000057F4u,  // 0002F850
        0x0000580Du, 0x0000578Bu, 0x00005832u, 0x00005831u,  // 0002F854
        0x000058ACu, 0x000214E4u, 0x000058F2u, 0x000058F7u,  // 0002F858
        0x00005906u, 0x0000591Au, 0x00005922u, 0x00005962u,  // 0002F85C
        0x000216A8u, 0x000216EAu, 0x000059ECu, 0x00005A1Bu,  // 0002F860
        0x00005A27u, 0x000059D8u, 0x00005A66u, 0x000036EEu,  // 0002F864
        0x000036FCu, 0x00005B08u, 0x00005B3Eu, 0x00005B3Eu,  // 0002F868
        0x000219C8u, 0x00005BC3u, 0x00005BD8u, 0x00005BE7u,  // 0002F86C
        0x00005BF3u, 0x00021B18u, 0x00005BFFu, 0x00005C06u,  // 0002F870
        0x00005F53u, 0x00005C22u, 0x00003781u, 0x00005C60u,  // 0002F874
        0x00005C6Eu, 0x00005CC0u, 0x00005C8Du, 0x00021DE4u,  // 0002F878
        0x00005D43u, 0x00021DE6u, 0x00005D6Eu, 0x00005D6Bu,  // 0002F87C
        0x00005D7Cu, 0x00005DE1u, 0x00005DE2u, 0x0000382Fu,  // 0002F880
        0x00005DFDu, 0x00005E28u, 0x00005E3Du, 0x00005E69u,  // 0002F884
        0x00003862u, 0x00022183u, 0x0000387Cu, 0x00005EB0u,  // 0002F888
        0x00005EB3u, 0x00005EB6u, 0x00005ECAu, 0x0002A392u,  // 0002F88C
        0x00005EFEu, 0x00022331u, 0x00022331u, 0x00008201u,  // 0002F890
        0x00005F22u, 0x00005F22u, 0x000038C7u, 0x000232B8u,  // 0002F894
        0x000261DAu, 0x00005F62u, 0x00005F6Bu, 0x000038E3u,  // 0002F898
        0x00005F9Au, 0x00005FCDu, 0x00005FD7u, 0x00005FF9u,  // 0002F89C
        0x00006081u, 0x0000393Au, 0x0000391Cu, 0x00006094u,  // 0002F8A0
        0x000226D4u, 0x000060C7u, 0x00006148u, 0x0000614Cu,  // 0002F8A4
        0x0000614Eu, 0x0000614Cu, 0x0000617Au, 0x0000618Eu,  // 0002F8A8
        0x000061B2u, 0x000061A4u, 0x000061AFu, 0x000061DEu,  // 0002F8AC
        0x000061F2u, 0x000061F6u, 0x00006210u, 0x0000621Bu,  // 0002F8B0
        0x0000625Du, 0x000062B1u, 0x000062D4u, 0x00006350u,  // 0002F8B4
        0x00022B0Cu, 0x0000633Du, 0x000062FCu, 0x00006368u,  // 0002F8B8
        0x00006383u, 0x000063E4u, 0x00022BF1u, 0x00006422u,  // 0002F8BC
        0x000063C5u, 0x000063A9u, 0x00003A2Eu, 0x00006469u,  // 0002F8C0
        0x0000647Eu, 0x0000649Du, 0x00006477u, 0x00003A6Cu,  // 0002F8C4
        0x0000654Fu, 0x0000656Cu, 0x0002300Au, 0x000065E3u,  // 0002F8C8
        0x000066F8u, 0x00006649u, 0x00003B19u, 0x00006691u,  // 0002F8CC
        0x00003B08u, 0x00003AE4u, 0x00005192u, 0x00005195u,  // 0002F8D0
        0x00006700u, 0x0000669Cu, 0x000080ADu, 0x000043D9u,  // 0002F8D4
        0x00006717u, 0x0000671Bu, 0x00006721u, 0x0000675Eu,  // 0002F8D8
        0x00006753u, 0x000233C3u, 0x00003B49u, 0x000067FAu,  // 0002F8DC
        0x00006785u, 0x00006852u, 0x00006885u, 0x0002346Du,  // 0002F8E0
        0x0000688Eu, 0x0000681Fu, 0x00006914u, 0x00003B9Du,  // 0002F8E4
        0x00006942u, 0x000069A3u, 0x000069EAu, 0x00006AA8u,  // 0002F8E8
        0x000236A3u, 0x00006ADBu, 0x00003C18u, 0x00006B21u,  // 0002F8EC
        0x000238A7u, 0x00006B54u, 0x00003C4Eu, 0x00006B72u,  // 0002F8F0
        0x00006B9Fu, 0x00006BBAu, 0x00006BBBu, 0x00023A8Du,  // 0002F8F4
        0x00021D0Bu, 0x00023AFAu, 0x00006C4Eu, 0x00023CBCu,  // 0002F8F8
        0x00006CBFu, 0x00006CCDu, 0x00006C67u, 0x00006D16u,  // 0002F8FC
        0x00006D3Eu, 0x00006D77u, 0x00006D41u, 0x00006D69u,  // 0002F900
        0x00006D78u, 0x00006D85u, 0x00023D1Eu, 0x00006D34u,  // 0002F904
        0x00006E2Fu, 0x00006E6Eu, 0x00003D33u, 0x00006ECBu,  // 0002F908
        0x00006EC7u, 0x00023ED1u, 0x00006DF9u, 0x00006F6Eu,  // 0002F90C
        0x00023F5Eu, 0x00023F8Eu, 0x00006FC6u, 0x00007039u,  // 0002F910
        0x0000701Eu, 0x0000701Bu, 0x00003D96u, 0x0000704Au,  // 0002F914
        0x0000707Du, 0x00007077u, 0x000070ADu, 0x00020525u,  // 0002F918
        0x00007145u, 0x00024263u, 0x0000719Cu, 0x000243ABu,  // 0002F91C
        0x00007228u, 0x00007235u, 0x00007250u, 0x00024608u,  // 0002F920
        0x00007280u, 0x00007295u, 0x00024735u, 0x00024814u,  // 0002F924
        0x0000737Au, 0x0000738Bu, 0x00003EACu, 0x000073A5u,  // 0002F928
        0x00003EB8u, 0x00003EB8u, 0x00007447u, 0x0000745Cu,  // 0002F92C
        0x00007471u, 0x00007485u, 0x000074CAu, 0x00003F1Bu,  // 0002F930
        0x00007524u, 0x00024C36u, 0x0000753Eu, 0x00024C92u,  // 0002F934
        0x00007570u, 0x0002219Fu, 0x00007610u, 0x00024FA1u,  // 0002F938
        0x00024FB8u, 0x00025044u, 0x00003FFCu, 0x00004008u,  // 0002F93C
        0x000076F4u, 0x000250F3u, 0x000250F2u, 0x00025119u,  // 0002F940
        0x00025133u, 0x0000771Eu, 0x0000771Fu, 0x0000771Fu,  // 0002F944
        0x0000774Au, 0x00004039u, 0x0000778Bu, 0x00004046u,  // 0002F948
        0x00004096u, 0x0002541Du, 0x0000784Eu, 0x0000788Cu,  // 0002F94C
        0x000078CCu, 0x000040E3u, 0x00025626u, 0x00007956u,  // 0002F950
        0x0002569Au, 0x000256C5u, 0x0000798Fu, 0x000079EBu,  // 0002F954
        0x0000412Fu, 0x00007A40u, 0x00007A4Au, 0x00007A4Fu,  // 0002F958
        0x0002597Cu, 0x00025AA7u, 0x00025AA7u, 0x00007AEEu,  // 0002F95C
        0x00004202u, 0x00025BABu, 0x00007BC6u, 0x00007BC9u,  // 0002F960
        0x00004227u, 0x00025C80u, 0x00007CD2u, 0x000042A0u,  // 0002F964
        0x00007CE8u, 0x00007CE3u, 0x00007D00u, 0x00025F86u,  // 0002F968
        0x00007D63u, 0x00004301u, 0x00007DC7u, 0x00007E02u,  // 0002F96C
        0x00007E45u, 0x00004334u, 0x00026228u, 0x00026247u,  // 0002F970
        0x00004359u, 0x000262D9u, 0x00007F7Au, 0x0002633Eu,  // 0002F974
        0x00007F95u, 0x00007FFAu, 0x00008005u, 0x000264DAu,  // 0002F978
        0x00026523u, 0x00008060u, 0x000265A8u, 0x00008070u,  // 0002F97C
        0x0002335Fu, 0x000043D5u, 0x000080B2u, 0x00008103u,  // 0002F980
        0x0000440Bu, 0x0000813Eu, 0x00005AB5u, 0x000267A7u,  // 0002F984
        0x000267B5u, 0x00023393u, 0x0002339Cu, 0x00008201u,  // 0002F988
        0x00008204u, 0x00008F9Eu, 0x0000446Bu, 0x00008291u,  // 0002F98C
        0x0000828Bu, 0x0000829Du, 0x000052B3u, 0x000082B1u,  // 0002F990
        0x000082B3u, 0x000082BDu, 0x000082E6u, 0x00026B3Cu,  // 0002F994
        0x000082E5u, 0x0000831Du, 0x00008363u, 0x000083ADu,  // 0002F998
        0x00008323u, 0x000083BDu, 0x000083E7u, 0x00008457u,  // 0002F99C
        0x00008353u, 0x000083CAu, 0x000083CCu, 0x000083DCu,  // 0002F9A0
        0x00026C36u, 0x00026D6Bu, 0x00026CD5u, 0x0000452Bu,  // 0002F9A4
        0x000084F1u, 0x000084F3u, 0x00008516u, 0x000273CAu,  // 0002F9A8
        0x00008564u, 0x00026F2Cu, 0x0000455Du, 0x00004561u,  // 0002F9AC
        0x00026FB1u, 0x000270D2u, 0x0000456Bu, 0x00008650u,  // 0002F9B0
        0x0000865Cu, 0x00008667u, 0x00008669u, 0x000086A9u,  // 0002F9B4
        0x00008688u, 0x0000870Eu, 0x000086E2u, 0x00008779u,  // 0002F9B8
        0x00008728u, 0x0000876Bu, 0x00008786u, 0x000045D7u,  // 0002F9BC
        0x000087E1u, 0x00008801u, 0x000045F9u, 0x00008860u,  // 0002F9C0
        0x00008863u, 0x00027667u, 0x000088D7u, 0x000088DEu,  // 0002F9C4
        0x00004635u, 0x000088FAu, 0x000034BBu, 0x000278AEu,  // 0002F9C8
        0x00027966u, 0x000046BEu, 0x000046C7u, 0x00008AA0u,  // 0002F9CC
        0x00008AEDu, 0x00008B8Au, 0x00008C55u, 0x00027CA8u,  // 0002F9D0
        0x00008CABu, 0x00008CC1u, 0x00008D1Bu, 0x00008D77u,  // 0002F9D4
        0x00027F2Fu, 0x00020804u, 0x00008DCBu, 0x00008DBCu,  // 0002F9D8
        0x00008DF0u, 0x000208DEu, 0x00008ED4u, 0x00008F38u,  // 0002F9DC
        0x000285D2u, 0x000285EDu, 0x00009094u, 0x000090F1u,  // 0002F9E0
        0x00009111u, 0x0002872Eu, 0x0000911Bu, 0x00009238u,  // 0002F9E4
        0x000092D7u, 0x000092D8u, 0x0000927Cu, 0x000093F9u,  // 0002F9E8
        0x00009415u, 0x00028BFAu, 0x0000958Bu, 0x00004995u,  // 0002F9EC
        0x000095B7u, 0x00028D77u, 0x000049E6u, 0x000096C3u,  // 0002F9F0
        0x00005DB2u, 0x00009723u, 0x00029145u, 0x0002921Au,  // 0002F9F4
        0x00004A6Eu, 0x00004A76u, 0x000097E0u, 0x0002940Au,  // 0002F9F8
        0x00004AB2u, 0x00029496u, 0x0000980Bu, 0x0000980Bu,  // 0002F9FC
        0x00009829u, 0x000295B6u, 0x000098E2u, 0x00004B33u,  // 0002FA00
        0x00009929u, 0x000099A7u, 0x000099C2u, 0x000099FEu,  // 0002FA04
        0x00004BCEu, 0x00029B30u, 0x00009B12u, 0x00009C40u,  // 0002FA08
        0x00009CFDu, 0x00004CCEu, 0x00004CEDu, 0x00009D67u,  // 0002FA0C
        0x0002A0CEu, 0x00004CF8u, 0x0002A105u, 0x0002A20Eu,  // 0002FA10
        0x0002A291u, 0x00009EBBu, 0x00004D56u, 0x00009EF9u,  // 0002FA14
        0x00009EFEu, 0x00009F05u, 0x00009F0Fu, 0x00009F16u,  // 0002FA18
        0x00009F3Bu, 0x0002A600u, 0x0002FA1Eu, 0x0002FA1Fu
    };

    const std::bitset<544> CJK_Compatibility_Ideographs_Supplement2F800::my_Ideographic(std::string("0011111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"));

  }; // namespace
}; // namespace

dload(Babylon::Module::CJK_Compatibility_Ideographs_Supplement2F800);
