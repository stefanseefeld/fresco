/*$Id: 180-24F.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Wed,  6 Dec 2000 23:21:48 +0100.
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
#include <Babylon/Dictionary.hh>
#include <map>

namespace Babylon {

  class Latin_ExtendedB180 : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    Latin_ExtendedB180() {
      _first_letter = 0x180;
      _last_letter  = 0x24F;
      // _version="3.0.1" // Not yet supported!
      _composeMap[0x01A00300] = 0x1EDC;
      _composeMap[0x01A00301] = 0x1EDA;
      _composeMap[0x01A00303] = 0x1EE0;
      _composeMap[0x01A00309] = 0x1EDE;
      _composeMap[0x01A00323] = 0x1EE2;
      _composeMap[0x01A10300] = 0x1EDD;
      _composeMap[0x01A10301] = 0x1EDB;
      _composeMap[0x01A10303] = 0x1EE1;
      _composeMap[0x01A10309] = 0x1EDF;
      _composeMap[0x01A10323] = 0x1EE3;
      _composeMap[0x01AF0300] = 0x1EEA;
      _composeMap[0x01AF0301] = 0x1EE8;
      _composeMap[0x01AF0303] = 0x1EEE;
      _composeMap[0x01AF0309] = 0x1EEC;
      _composeMap[0x01AF0323] = 0x1EF0;
      _composeMap[0x01B00300] = 0x1EEB;
      _composeMap[0x01B00301] = 0x1EE9;
      _composeMap[0x01B00303] = 0x1EEF;
      _composeMap[0x01B00309] = 0x1EED;
      _composeMap[0x01B00323] = 0x1EF1;
      _composeMap[0x01B7030C] = 0x01EE;
      _composeMap[0x01EA0304] = 0x01EC;
      _composeMap[0x01EB0304] = 0x01ED;
      _composeMap[0x02260304] = 0x01E0;
      _composeMap[0x02270304] = 0x01E1;
      _composeMap[0x02280306] = 0x1E1C;
      _composeMap[0x02290306] = 0x1E1D;
      _composeMap[0x022E0304] = 0x0230;
      _composeMap[0x022F0304] = 0x0231;

    }


    ~Latin_ExtendedB180() {
    }

    UCS4 firstLetter() {
      return _first_letter;
    }

    UCS4 lastLetter() {
      return _last_letter;
    }

    bool is_undef_block() const {
      return 0;
    }

    // query functions:

    string blockname(const UCS4 uc) const {
      return "Latin Extended-B";
    }

    bool is_defined(const UCS4 uc) const {
      return (_is_defined[uc - _first_letter]);
    }

    UCS4 uppercase(const UCS4 uc) const {
      return Latin_ExtendedB180::_upper[uc - _first_letter];
    }

    bool is_Uppercase(const UCS4 uc) const {
      return category(uc) == CAT_Lu;
    }

    UCS4 lowercase(const UCS4 uc) const {
      return Latin_ExtendedB180::_lower[uc - _first_letter];
    }

    bool is_Lowercase(const UCS4 uc) const {
      return category(uc) == CAT_Ll;
    }

    UCS4 titlecase(const UCS4 uc) const {
      return Latin_ExtendedB180::_title[uc - _first_letter];
    }

    bool is_Titlecase(const UCS4 uc) const {
      return category(uc) == CAT_Lt;
    }

    int dec_digit_value(const UCS4 uc) const {
      return 0;
    }

    bool is_Decimal_Digit(const UCS4 uc) const {
      return 0;
    }

    int digit_value(const UCS4 uc) const {
      return 0;
    }

    bool is_Digit(const UCS4 uc) const {
      return 0;
    }

    float numeric_value(const UCS4 uc) const {
      return 0;
    }

    bool is_Numeric(const UCS4 uc) const {
      return 0;
    }

    Gen_Cat category(const UCS4 uc) const {
      if (!is_defined(uc))
        return CAT_MAX;
      return Babylon::Gen_Cat(Latin_ExtendedB180::_cat[uc - _first_letter]);
    }

    Can_Comb_Class comb_class(const UCS4 uc) const {
      if (!is_defined(uc))
        return CC_MAX;
      return Babylon::Can_Comb_Class(0);
    }

    Bidir_Props bidir_props(const UCS4 uc) const {
      if (!is_defined(uc))
        return BIDIR_MAX;
      return Babylon::Bidir_Props(BIDIR_L);
    }

    Char_Decomp decomp_type(const UCS4 uc) const {
      if (!is_defined(uc))
        return DECOMP_MAX;
      return Babylon::Char_Decomp(Latin_ExtendedB180::_decomp[uc - _first_letter]);
    }

    UTF32_string decompose(const UCS4 uc) const {
      Babylon::UTF32_string us;
      us.resize(2);
      us[0] = Latin_ExtendedB180::_decompStr[uc - _first_letter][0];
      us[1] = Latin_ExtendedB180::_decompStr[uc - _first_letter][1];
      if (us[1] == 0x0000) {
        us.resize(1);
      }

      return us;
    }

    bool must_mirror(const UCS4 uc) const {
      return 0;
    }

    Line_Break linebreak(const UCS4 uc) const {
      if (!is_defined(uc))
        return LB_MAX;
      return Babylon::Line_Break(Latin_ExtendedB180::_lb[uc - _first_letter]);
    }

    EA_Width EA_width(const UCS4 uc) const {
      if (!is_defined(uc))
        return EA_WIDTH_MAX;
      return Babylon::EA_Width(Latin_ExtendedB180::_ea[uc - _first_letter]);
    }

    UCS4 compose (const UCS4 starter, const UCS4 last) {
      return _composeMap[starter << 16 | last];
    }

    bool is_Zero_width(const UCS4 uc) const {
      return 0;
    }

    bool is_White_space(const UCS4 uc) const {
      return 0;
    }

    bool is_Non_break(const UCS4 uc) const {
      return 0;
    }

    bool is_Bidi_Control(const UCS4 uc) const {
      return 0;
    }

    bool is_Join_Control(const UCS4 uc) const {
      return 0;
    }

    bool is_Format_Control(const UCS4 uc) const {
      return 0;
    }

    bool is_Dash(const UCS4 uc) const {
      return 0;
    }

    bool is_Hyphen(const UCS4 uc) const {
      return 0;
    }

    bool is_Quotation_Mark(const UCS4 uc) const {
      return 0;
    }

    bool is_Terminal_Punctuation(const UCS4 uc) const {
      return 0;
    }

    bool is_Math(const UCS4 uc) const {
      return 0;
    }

    bool is_Paired_Punctuation(const UCS4 uc) const {
      return 0;
    }

    bool is_Left_of_Pair(const UCS4 uc) const {
      return 0;
    }

    bool is_Combining(const UCS4 uc) const {
      return 0;
    }

    bool is_Non_spacing(const UCS4 uc) const {
      return 0;
    }

    bool is_Composite(const UCS4 uc) const {
      return Latin_ExtendedB180::_Composite[uc - _first_letter];
    }

    bool is_Hex_Digit(const UCS4 uc) const {
      return 0;
    }

    bool is_Alphabetic(const UCS4 uc) const {
      return Latin_ExtendedB180::_Alphabetic[uc - _first_letter];
    }

    bool is_Diacritic(const UCS4 uc) const {
      return 0;
    }

    bool is_Extender(const UCS4 uc) const {
      return 0;
    }

    bool is_Identifier_Part(const UCS4 uc) const {
      return Latin_ExtendedB180::_Identifier_Part[uc - _first_letter];
    }

    bool is_Ignorable_Control(const UCS4 uc) const {
      return 0;
    }

    bool is_Bidi_Hebrew_Right_to_Left(const UCS4 uc) const {
      return 0;
    }

    bool is_Bidi_Arabic_Right_to_Left(const UCS4 uc) const {
      return 0;
    }

    bool is_Ideographic(const UCS4 uc) const {
      return 0;
    }

    bool is_Private_Use(const UCS4 uc) const {
      return 0;
    }

    bool is_Not_a_Character(const UCS4 uc) const {
      return ((uc & 0xFFFE) == 0xFFFE);
    }

    bool is_Private_Use_High_Surrogate(const UCS4 uc) const {
      return 0;
    }

    bool is_Low_Surrogate(const UCS4 uc) const {
      return 0;
    }

    bool is_High_Surrogate(const UCS4 uc) const {
      return 0;
    }

    bool is_Space(const UCS4 uc) const {
      return (is_defined(uc) && category(uc) == CAT_Zs);
    }

    bool is_ISO_Control(const UCS4 uc) const {
      return (is_defined(uc) && category(uc) == CAT_Cc);
    }

    bool is_Punctuation(const UCS4 uc) const {
      return (is_defined(uc) && (category(uc) == CAT_Pc ||
                                 category(uc) == CAT_Pd ||
                                 category(uc) == CAT_Ps ||
                                 category(uc) == CAT_Pe ||
                                 category(uc) == CAT_Pi ||
                                 category(uc) == CAT_Pf ||
                                 category(uc) == CAT_Po)
             );
    }

    bool is_Line_Separator(const UCS4 uc) const {
      return (is_defined(uc) && category(uc) == CAT_Zl);
    }

    bool is_Paragraph_Separator(const UCS4 uc) const {
      return (is_defined(uc) && category(uc) == CAT_Zp);
    }

    bool is_Currency_Symbol(const UCS4 uc) const {
      return (is_defined(uc) && category(uc) == CAT_Sc);
    }

    bool is_Bidi_Left_to_Right(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_L;
    }

    bool is_Bidi_European_Digit(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_EN;
    }

    bool is_Bidi_Eur_Num_Separator(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_ES;
    }

    bool is_Bidi_Eur_Num_Terminator(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_ET;
    }

    bool is_Bidi_Arabic_Digit(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_AN;
    }

    bool is_Bidi_Common_Separator(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_CS;
    }

    bool is_Bidi_Block_Separator(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_B;
    }

    bool is_Bidi_Segment_Separator(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_S;
    }

    bool is_Bidi_Whitespace(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_WS;
    }

    bool is_Bidi_Non_spacing_Mark(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_NSM;
    }

    bool is_Bidi_Boundary_Neutral(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_BN;
    }

    bool is_Bidi_PDF(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_PDF;
    }

    bool is_Bidi_Embedding_or_Override(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_LRE ||
             bidir_props(uc) == BIDIR_RLE ||
             bidir_props(uc) == BIDIR_LRO ||
             bidir_props(uc) == BIDIR_RLO;
    }

    bool is_Bidi_LRE(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_LRE;
    }

    bool is_Bidi_RLE(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_RLE;
    }

    bool is_Bidi_LRO(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_LRO;
    }

    bool is_Bidi_RLO(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_RLO;
    }

    bool is_Bidi_Other_Neutral(const UCS4 uc) const {
      return bidir_props(uc) == BIDIR_ON;
    }

    bool is_Unassigned_Code_Value(const UCS4 uc) const {
      return !is_defined(uc) && !is_Not_a_Character(uc);
    }


  private:
    // functions
    Latin_ExtendedB180(const Latin_ExtendedB180 &) {}

    Babylon::UCS4 _first_letter;
    Babylon::UCS4 _last_letter;
    static const bool _is_defined[208];
    static const UCS4 _upper[208];
    static const UCS4 _lower[208];
    static const UCS4 _title[208];
    static const unsigned char _cat[208];
    static const unsigned char _decomp[208];
    static const UCS2 _decompStr[208][2];
    static const unsigned char _lb[208];
    static const unsigned char _ea[208];
    map<UCS4, UCS4> _composeMap;
    static const bool _Composite[208];
    static const bool _Alphabetic[208];
    static const bool _Identifier_Part[208];

  }; // class Latin_ExtendedB180

  const bool Latin_ExtendedB180::_is_defined[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    0, 0, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0
  };

  const UCS4 Latin_ExtendedB180::_upper[] = {
    0x0180, 0x0181, 0x0182, 0x0182, 0x0184, 0x0184, 0x0186, 0x0187, 
    0x0187, 0x0189, 0x018A, 0x018B, 0x018B, 0x018D, 0x018E, 0x018F, 
    0x0190, 0x0191, 0x0191, 0x0193, 0x0194, 0x01F6, 0x0196, 0x0197, 
    0x0198, 0x0198, 0x019A, 0x019B, 0x019C, 0x019D, 0x019E, 0x019F, 
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

  const UCS4 Latin_ExtendedB180::_lower[] = {
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
    0x0220, 0x0221, 0x0223, 0x0223, 0x0225, 0x0225, 0x0227, 0x0227, 
    0x0229, 0x0229, 0x022B, 0x022B, 0x022D, 0x022D, 0x022F, 0x022F, 
    0x0231, 0x0231, 0x0233, 0x0233, 0x0234, 0x0235, 0x0236, 0x0237, 
    0x0238, 0x0239, 0x023A, 0x023B, 0x023C, 0x023D, 0x023E, 0x023F, 
    0x0240, 0x0241, 0x0242, 0x0243, 0x0244, 0x0245, 0x0246, 0x0247, 
    0x0248, 0x0249, 0x024A, 0x024B, 0x024C, 0x024D, 0x024E, 0x024F
  };

  const UCS4 Latin_ExtendedB180::_title[] = {
    0x0180, 0x0181, 0x0182, 0x0182, 0x0184, 0x0184, 0x0186, 0x0187, 
    0x0187, 0x0189, 0x018A, 0x018B, 0x018B, 0x018D, 0x018E, 0x018F, 
    0x0190, 0x0191, 0x0191, 0x0193, 0x0194, 0x01F6, 0x0196, 0x0197, 
    0x0198, 0x0198, 0x019A, 0x019B, 0x019C, 0x019D, 0x019E, 0x019F, 
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

  const unsigned char Latin_ExtendedB180::_cat[] = {
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
    CAT_Ll, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, 
    CAT_Lu, CAT_Ll, CAT_Lu, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
    CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
    CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
    CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll
  };

  const unsigned char Latin_ExtendedB180::_decomp[] = {
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
    DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP
  };

  const UCS2 Latin_ExtendedB180::_decompStr[][2] = {
    { 0x0180, 0x0000 }, { 0x0181, 0x0000 }, { 0x0182, 0x0000 }, { 0x0183, 0x0000 }, 
    { 0x0184, 0x0000 }, { 0x0185, 0x0000 }, { 0x0186, 0x0000 }, { 0x0187, 0x0000 }, 
    { 0x0188, 0x0000 }, { 0x0189, 0x0000 }, { 0x018A, 0x0000 }, { 0x018B, 0x0000 }, 
    { 0x018C, 0x0000 }, { 0x018D, 0x0000 }, { 0x018E, 0x0000 }, { 0x018F, 0x0000 }, 
    { 0x0190, 0x0000 }, { 0x0191, 0x0000 }, { 0x0192, 0x0000 }, { 0x0193, 0x0000 }, 
    { 0x0194, 0x0000 }, { 0x0195, 0x0000 }, { 0x0196, 0x0000 }, { 0x0197, 0x0000 }, 
    { 0x0198, 0x0000 }, { 0x0199, 0x0000 }, { 0x019A, 0x0000 }, { 0x019B, 0x0000 }, 
    { 0x019C, 0x0000 }, { 0x019D, 0x0000 }, { 0x019E, 0x0000 }, { 0x019F, 0x0000 }, 
    { 0x004F, 0x031B }, { 0x006F, 0x031B }, { 0x01A2, 0x0000 }, { 0x01A3, 0x0000 }, 
    { 0x01A4, 0x0000 }, { 0x01A5, 0x0000 }, { 0x01A6, 0x0000 }, { 0x01A7, 0x0000 }, 
    { 0x01A8, 0x0000 }, { 0x01A9, 0x0000 }, { 0x01AA, 0x0000 }, { 0x01AB, 0x0000 }, 
    { 0x01AC, 0x0000 }, { 0x01AD, 0x0000 }, { 0x01AE, 0x0000 }, { 0x0055, 0x031B }, 
    { 0x0075, 0x031B }, { 0x01B1, 0x0000 }, { 0x01B2, 0x0000 }, { 0x01B3, 0x0000 }, 
    { 0x01B4, 0x0000 }, { 0x01B5, 0x0000 }, { 0x01B6, 0x0000 }, { 0x01B7, 0x0000 }, 
    { 0x01B8, 0x0000 }, { 0x01B9, 0x0000 }, { 0x01BA, 0x0000 }, { 0x01BB, 0x0000 }, 
    { 0x01BC, 0x0000 }, { 0x01BD, 0x0000 }, { 0x01BE, 0x0000 }, { 0x01BF, 0x0000 }, 
    { 0x01C0, 0x0000 }, { 0x01C1, 0x0000 }, { 0x01C2, 0x0000 }, { 0x01C3, 0x0000 }, 
    { 0x0044, 0x017D }, { 0x0044, 0x017E }, { 0x0064, 0x017E }, { 0x004C, 0x004A }, 
    { 0x004C, 0x006A }, { 0x006C, 0x006A }, { 0x004E, 0x004A }, { 0x004E, 0x006A }, 
    { 0x006E, 0x006A }, { 0x0041, 0x030C }, { 0x0061, 0x030C }, { 0x0049, 0x030C }, 
    { 0x0069, 0x030C }, { 0x004F, 0x030C }, { 0x006F, 0x030C }, { 0x0055, 0x030C }, 
    { 0x0075, 0x030C }, { 0x00DC, 0x0304 }, { 0x00FC, 0x0304 }, { 0x00DC, 0x0301 }, 
    { 0x00FC, 0x0301 }, { 0x00DC, 0x030C }, { 0x00FC, 0x030C }, { 0x00DC, 0x0300 }, 
    { 0x00FC, 0x0300 }, { 0x01DD, 0x0000 }, { 0x00C4, 0x0304 }, { 0x00E4, 0x0304 }, 
    { 0x0226, 0x0304 }, { 0x0227, 0x0304 }, { 0x00C6, 0x0304 }, { 0x00E6, 0x0304 }, 
    { 0x01E4, 0x0000 }, { 0x01E5, 0x0000 }, { 0x0047, 0x030C }, { 0x0067, 0x030C }, 
    { 0x004B, 0x030C }, { 0x006B, 0x030C }, { 0x004F, 0x0328 }, { 0x006F, 0x0328 }, 
    { 0x01EA, 0x0304 }, { 0x01EB, 0x0304 }, { 0x01B7, 0x030C }, { 0x0292, 0x030C }, 
    { 0x006A, 0x030C }, { 0x0044, 0x005A }, { 0x0044, 0x007A }, { 0x0064, 0x007A }, 
    { 0x0047, 0x0301 }, { 0x0067, 0x0301 }, { 0x01F6, 0x0000 }, { 0x01F7, 0x0000 }, 
    { 0x004E, 0x0300 }, { 0x006E, 0x0300 }, { 0x00C5, 0x0301 }, { 0x00E5, 0x0301 }, 
    { 0x00C6, 0x0301 }, { 0x00E6, 0x0301 }, { 0x00D8, 0x0301 }, { 0x00F8, 0x0301 }, 
    { 0x0041, 0x030F }, { 0x0061, 0x030F }, { 0x0041, 0x0311 }, { 0x0061, 0x0311 }, 
    { 0x0045, 0x030F }, { 0x0065, 0x030F }, { 0x0045, 0x0311 }, { 0x0065, 0x0311 }, 
    { 0x0049, 0x030F }, { 0x0069, 0x030F }, { 0x0049, 0x0311 }, { 0x0069, 0x0311 }, 
    { 0x004F, 0x030F }, { 0x006F, 0x030F }, { 0x004F, 0x0311 }, { 0x006F, 0x0311 }, 
    { 0x0052, 0x030F }, { 0x0072, 0x030F }, { 0x0052, 0x0311 }, { 0x0072, 0x0311 }, 
    { 0x0055, 0x030F }, { 0x0075, 0x030F }, { 0x0055, 0x0311 }, { 0x0075, 0x0311 }, 
    { 0x0053, 0x0326 }, { 0x0073, 0x0326 }, { 0x0054, 0x0326 }, { 0x0074, 0x0326 }, 
    { 0x021C, 0x0000 }, { 0x021D, 0x0000 }, { 0x0048, 0x030C }, { 0x0068, 0x030C }, 
    { 0x0220, 0x0000 }, { 0x0221, 0x0000 }, { 0x0222, 0x0000 }, { 0x0223, 0x0000 }, 
    { 0x0224, 0x0000 }, { 0x0225, 0x0000 }, { 0x0041, 0x0307 }, { 0x0061, 0x0307 }, 
    { 0x0045, 0x0327 }, { 0x0065, 0x0327 }, { 0x00D6, 0x0304 }, { 0x00F6, 0x0304 }, 
    { 0x00D5, 0x0304 }, { 0x00F5, 0x0304 }, { 0x004F, 0x0307 }, { 0x006F, 0x0307 }, 
    { 0x022E, 0x0304 }, { 0x022F, 0x0304 }, { 0x0059, 0x0304 }, { 0x0079, 0x0304 }, 
    { 0x0234, 0x0000 }, { 0x0235, 0x0000 }, { 0x0236, 0x0000 }, { 0x0237, 0x0000 }, 
    { 0x0238, 0x0000 }, { 0x0239, 0x0000 }, { 0x023A, 0x0000 }, { 0x023B, 0x0000 }, 
    { 0x023C, 0x0000 }, { 0x023D, 0x0000 }, { 0x023E, 0x0000 }, { 0x023F, 0x0000 }, 
    { 0x0240, 0x0000 }, { 0x0241, 0x0000 }, { 0x0242, 0x0000 }, { 0x0243, 0x0000 }, 
    { 0x0244, 0x0000 }, { 0x0245, 0x0000 }, { 0x0246, 0x0000 }, { 0x0247, 0x0000 }, 
    { 0x0248, 0x0000 }, { 0x0249, 0x0000 }, { 0x024A, 0x0000 }, { 0x024B, 0x0000 }, 
    { 0x024C, 0x0000 }, { 0x024D, 0x0000 }, { 0x024E, 0x0000 }, { 0x024F, 0x0000 }
  };

  const unsigned char Latin_ExtendedB180::_lb[] = {
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

  const unsigned char Latin_ExtendedB180::_ea[] = {
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, 
    EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, 
    EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_A, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N
  };

    const bool Latin_ExtendedB180::_Composite[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 1, 
        1, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 0, 1, 1, 
        1, 1, 1, 1, 0, 0, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 0, 0, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 0, 0, 1, 1, 
        0, 0, 0, 0, 0, 0, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Latin_ExtendedB180::_Alphabetic[] = {
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        0, 0, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Latin_ExtendedB180::_Identifier_Part[] = {
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        0, 0, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

}; // namespace Babylon

dload(Babylon::Latin_ExtendedB180);
