/*$Id: F900-FAFF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Wed,  6 Dec 2000 23:39:31 +0100.
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

namespace Babylon {

  class CJK_Compatibility_IdeographsF900 : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    CJK_Compatibility_IdeographsF900() {
      _first_letter = 0xF900;
      _last_letter  = 0xFAFF;
      // _version="3.0.1" // Not yet supported!

    }


    ~CJK_Compatibility_IdeographsF900() {
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
      return "CJK Compatibility Ideographs";
    }

    bool is_defined(const UCS4 uc) const {
      return (_is_defined[uc - _first_letter]);
    }

    UCS4 uppercase(const UCS4 uc) const {
      return uc;
    }

    bool is_Uppercase(const UCS4 uc) const {
      return category(uc) == CAT_Lu;
    }

    UCS4 lowercase(const UCS4 uc) const {
      return uc;
    }

    bool is_Lowercase(const UCS4 uc) const {
      return category(uc) == CAT_Ll;
    }

    UCS4 titlecase(const UCS4 uc) const {
      return uc;
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
      return Babylon::Gen_Cat(CAT_Lo);
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
      return Babylon::Char_Decomp(DECOMP_NO_DECOMP);
    }

    UTF32_string decompose(const UCS4 uc) const {
      Babylon::UTF32_string us;
      us.resize(2);
      us[0] = CJK_Compatibility_IdeographsF900::_decompStr[uc - _first_letter][0];
      us[1] = CJK_Compatibility_IdeographsF900::_decompStr[uc - _first_letter][1];
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
      return Babylon::Line_Break(LB_ID);
    }

    EA_Width EA_width(const UCS4 uc) const {
      if (!is_defined(uc))
        return EA_WIDTH_MAX;
      return Babylon::EA_Width(EA_WIDTH_W);
    }

    UCS4 compose (const UCS4 starter, const UCS4 last) {
      return 0;
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
      return 0;
    }

    bool is_Hex_Digit(const UCS4 uc) const {
      return 0;
    }

    bool is_Alphabetic(const UCS4 uc) const {
      return 0;
    }

    bool is_Diacritic(const UCS4 uc) const {
      return 0;
    }

    bool is_Extender(const UCS4 uc) const {
      return 0;
    }

    bool is_Identifier_Part(const UCS4 uc) const {
      return CJK_Compatibility_IdeographsF900::_Identifier_Part[uc - _first_letter];
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
      return (uc >= 0xF900 && uc <= 0xFA2D);
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
    CJK_Compatibility_IdeographsF900(const CJK_Compatibility_IdeographsF900 &) {}

    Babylon::UCS4 _first_letter;
    Babylon::UCS4 _last_letter;
    static const bool _is_defined[512];
    static const UCS2 _decompStr[512][2];
    static const bool _Identifier_Part[512];

  }; // class CJK_Compatibility_IdeographsF900

  const bool CJK_Compatibility_IdeographsF900::_is_defined[] = {
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
    1, 1, 1, 1, 1, 1, 0, 0, 
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
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0
  };

  const UCS2 CJK_Compatibility_IdeographsF900::_decompStr[][2] = {
    { 0x8C48, 0x0000 }, { 0x66F4, 0x0000 }, { 0x8ECA, 0x0000 }, { 0x8CC8, 0x0000 }, 
    { 0x6ED1, 0x0000 }, { 0x4E32, 0x0000 }, { 0x53E5, 0x0000 }, { 0x9F9C, 0x0000 }, 
    { 0x9F9C, 0x0000 }, { 0x5951, 0x0000 }, { 0x91D1, 0x0000 }, { 0x5587, 0x0000 }, 
    { 0x5948, 0x0000 }, { 0x61F6, 0x0000 }, { 0x7669, 0x0000 }, { 0x7F85, 0x0000 }, 
    { 0x863F, 0x0000 }, { 0x87BA, 0x0000 }, { 0x88F8, 0x0000 }, { 0x908F, 0x0000 }, 
    { 0x6A02, 0x0000 }, { 0x6D1B, 0x0000 }, { 0x70D9, 0x0000 }, { 0x73DE, 0x0000 }, 
    { 0x843D, 0x0000 }, { 0x916A, 0x0000 }, { 0x99F1, 0x0000 }, { 0x4E82, 0x0000 }, 
    { 0x5375, 0x0000 }, { 0x6B04, 0x0000 }, { 0x721B, 0x0000 }, { 0x862D, 0x0000 }, 
    { 0x9E1E, 0x0000 }, { 0x5D50, 0x0000 }, { 0x6FEB, 0x0000 }, { 0x85CD, 0x0000 }, 
    { 0x8964, 0x0000 }, { 0x62C9, 0x0000 }, { 0x81D8, 0x0000 }, { 0x881F, 0x0000 }, 
    { 0x5ECA, 0x0000 }, { 0x6717, 0x0000 }, { 0x6D6A, 0x0000 }, { 0x72FC, 0x0000 }, 
    { 0x90CE, 0x0000 }, { 0x4F86, 0x0000 }, { 0x51B7, 0x0000 }, { 0x52DE, 0x0000 }, 
    { 0x64C4, 0x0000 }, { 0x6AD3, 0x0000 }, { 0x7210, 0x0000 }, { 0x76E7, 0x0000 }, 
    { 0x8001, 0x0000 }, { 0x8606, 0x0000 }, { 0x865C, 0x0000 }, { 0x8DEF, 0x0000 }, 
    { 0x9732, 0x0000 }, { 0x9B6F, 0x0000 }, { 0x9DFA, 0x0000 }, { 0x788C, 0x0000 }, 
    { 0x797F, 0x0000 }, { 0x7DA0, 0x0000 }, { 0x83C9, 0x0000 }, { 0x9304, 0x0000 }, 
    { 0x9E7F, 0x0000 }, { 0x8AD6, 0x0000 }, { 0x58DF, 0x0000 }, { 0x5F04, 0x0000 }, 
    { 0x7C60, 0x0000 }, { 0x807E, 0x0000 }, { 0x7262, 0x0000 }, { 0x78CA, 0x0000 }, 
    { 0x8CC2, 0x0000 }, { 0x96F7, 0x0000 }, { 0x58D8, 0x0000 }, { 0x5C62, 0x0000 }, 
    { 0x6A13, 0x0000 }, { 0x6DDA, 0x0000 }, { 0x6F0F, 0x0000 }, { 0x7D2F, 0x0000 }, 
    { 0x7E37, 0x0000 }, { 0x96FB, 0x0000 }, { 0x52D2, 0x0000 }, { 0x808B, 0x0000 }, 
    { 0x51DC, 0x0000 }, { 0x51CC, 0x0000 }, { 0x7A1C, 0x0000 }, { 0x7DBE, 0x0000 }, 
    { 0x83F1, 0x0000 }, { 0x9675, 0x0000 }, { 0x8B80, 0x0000 }, { 0x62CF, 0x0000 }, 
    { 0x6A02, 0x0000 }, { 0x8AFE, 0x0000 }, { 0x4E39, 0x0000 }, { 0x5BE7, 0x0000 }, 
    { 0x6012, 0x0000 }, { 0x7387, 0x0000 }, { 0x7570, 0x0000 }, { 0x5317, 0x0000 }, 
    { 0x78FB, 0x0000 }, { 0x4FBF, 0x0000 }, { 0x5FA9, 0x0000 }, { 0x4E0D, 0x0000 }, 
    { 0x6CCC, 0x0000 }, { 0x6578, 0x0000 }, { 0x7D22, 0x0000 }, { 0x53C3, 0x0000 }, 
    { 0x585E, 0x0000 }, { 0x7701, 0x0000 }, { 0x8449, 0x0000 }, { 0x8AAA, 0x0000 }, 
    { 0x6BBA, 0x0000 }, { 0x8FB0, 0x0000 }, { 0x6C88, 0x0000 }, { 0x62FE, 0x0000 }, 
    { 0x82E5, 0x0000 }, { 0x63A0, 0x0000 }, { 0x7565, 0x0000 }, { 0x4EAE, 0x0000 }, 
    { 0x5169, 0x0000 }, { 0x51C9, 0x0000 }, { 0x6881, 0x0000 }, { 0x7CE7, 0x0000 }, 
    { 0x826F, 0x0000 }, { 0x8AD2, 0x0000 }, { 0x91CF, 0x0000 }, { 0x52F5, 0x0000 }, 
    { 0x5442, 0x0000 }, { 0x5973, 0x0000 }, { 0x5EEC, 0x0000 }, { 0x65C5, 0x0000 }, 
    { 0x6FFE, 0x0000 }, { 0x792A, 0x0000 }, { 0x95AD, 0x0000 }, { 0x9A6A, 0x0000 }, 
    { 0x9E97, 0x0000 }, { 0x9ECE, 0x0000 }, { 0x529B, 0x0000 }, { 0x66C6, 0x0000 }, 
    { 0x6B77, 0x0000 }, { 0x8F62, 0x0000 }, { 0x5E74, 0x0000 }, { 0x6190, 0x0000 }, 
    { 0x6200, 0x0000 }, { 0x649A, 0x0000 }, { 0x6F23, 0x0000 }, { 0x7149, 0x0000 }, 
    { 0x7489, 0x0000 }, { 0x79CA, 0x0000 }, { 0x7DF4, 0x0000 }, { 0x806F, 0x0000 }, 
    { 0x8F26, 0x0000 }, { 0x84EE, 0x0000 }, { 0x9023, 0x0000 }, { 0x934A, 0x0000 }, 
    { 0x5217, 0x0000 }, { 0x52A3, 0x0000 }, { 0x54BD, 0x0000 }, { 0x70C8, 0x0000 }, 
    { 0x88C2, 0x0000 }, { 0x8AAA, 0x0000 }, { 0x5EC9, 0x0000 }, { 0x5FF5, 0x0000 }, 
    { 0x637B, 0x0000 }, { 0x6BAE, 0x0000 }, { 0x7C3E, 0x0000 }, { 0x7375, 0x0000 }, 
    { 0x4EE4, 0x0000 }, { 0x56F9, 0x0000 }, { 0x5BE7, 0x0000 }, { 0x5DBA, 0x0000 }, 
    { 0x601C, 0x0000 }, { 0x73B2, 0x0000 }, { 0x7469, 0x0000 }, { 0x7F9A, 0x0000 }, 
    { 0x8046, 0x0000 }, { 0x9234, 0x0000 }, { 0x96F6, 0x0000 }, { 0x9748, 0x0000 }, 
    { 0x9818, 0x0000 }, { 0x4F8B, 0x0000 }, { 0x79AE, 0x0000 }, { 0x91B4, 0x0000 }, 
    { 0x96B8, 0x0000 }, { 0x60E1, 0x0000 }, { 0x4E86, 0x0000 }, { 0x50DA, 0x0000 }, 
    { 0x5BEE, 0x0000 }, { 0x5C3F, 0x0000 }, { 0x6599, 0x0000 }, { 0x6A02, 0x0000 }, 
    { 0x71CE, 0x0000 }, { 0x7642, 0x0000 }, { 0x84FC, 0x0000 }, { 0x907C, 0x0000 }, 
    { 0x9F8D, 0x0000 }, { 0x6688, 0x0000 }, { 0x962E, 0x0000 }, { 0x5289, 0x0000 }, 
    { 0x677B, 0x0000 }, { 0x67F3, 0x0000 }, { 0x6D41, 0x0000 }, { 0x6E9C, 0x0000 }, 
    { 0x7409, 0x0000 }, { 0x7559, 0x0000 }, { 0x786B, 0x0000 }, { 0x7D10, 0x0000 }, 
    { 0x985E, 0x0000 }, { 0x516D, 0x0000 }, { 0x622E, 0x0000 }, { 0x9678, 0x0000 }, 
    { 0x502B, 0x0000 }, { 0x5D19, 0x0000 }, { 0x6DEA, 0x0000 }, { 0x8F2A, 0x0000 }, 
    { 0x5F8B, 0x0000 }, { 0x6144, 0x0000 }, { 0x6817, 0x0000 }, { 0x7387, 0x0000 }, 
    { 0x9686, 0x0000 }, { 0x5229, 0x0000 }, { 0x540F, 0x0000 }, { 0x5C65, 0x0000 }, 
    { 0x6613, 0x0000 }, { 0x674E, 0x0000 }, { 0x68A8, 0x0000 }, { 0x6CE5, 0x0000 }, 
    { 0x7406, 0x0000 }, { 0x75E2, 0x0000 }, { 0x7F79, 0x0000 }, { 0x88CF, 0x0000 }, 
    { 0x88E1, 0x0000 }, { 0x91CC, 0x0000 }, { 0x96E2, 0x0000 }, { 0x533F, 0x0000 }, 
    { 0x6EBA, 0x0000 }, { 0x541D, 0x0000 }, { 0x71D0, 0x0000 }, { 0x7498, 0x0000 }, 
    { 0x85FA, 0x0000 }, { 0x96A3, 0x0000 }, { 0x9C57, 0x0000 }, { 0x9E9F, 0x0000 }, 
    { 0x6797, 0x0000 }, { 0x6DCB, 0x0000 }, { 0x81E8, 0x0000 }, { 0x7ACB, 0x0000 }, 
    { 0x7B20, 0x0000 }, { 0x7C92, 0x0000 }, { 0x72C0, 0x0000 }, { 0x7099, 0x0000 }, 
    { 0x8B58, 0x0000 }, { 0x4EC0, 0x0000 }, { 0x8336, 0x0000 }, { 0x523A, 0x0000 }, 
    { 0x5207, 0x0000 }, { 0x5EA6, 0x0000 }, { 0x62D3, 0x0000 }, { 0x7CD6, 0x0000 }, 
    { 0x5B85, 0x0000 }, { 0x6D1E, 0x0000 }, { 0x66B4, 0x0000 }, { 0x8F3B, 0x0000 }, 
    { 0x884C, 0x0000 }, { 0x964D, 0x0000 }, { 0x898B, 0x0000 }, { 0x5ED3, 0x0000 }, 
    { 0x5140, 0x0000 }, { 0x55C0, 0x0000 }, { 0xFA0E, 0x0000 }, { 0xFA0F, 0x0000 }, 
    { 0x585A, 0x0000 }, { 0xFA11, 0x0000 }, { 0x6674, 0x0000 }, { 0xFA13, 0x0000 }, 
    { 0xFA14, 0x0000 }, { 0x51DE, 0x0000 }, { 0x732A, 0x0000 }, { 0x76CA, 0x0000 }, 
    { 0x793C, 0x0000 }, { 0x795E, 0x0000 }, { 0x7965, 0x0000 }, { 0x798F, 0x0000 }, 
    { 0x9756, 0x0000 }, { 0x7CBE, 0x0000 }, { 0x7FBD, 0x0000 }, { 0xFA1F, 0x0000 }, 
    { 0x8612, 0x0000 }, { 0xFA21, 0x0000 }, { 0x8AF8, 0x0000 }, { 0xFA23, 0x0000 }, 
    { 0xFA24, 0x0000 }, { 0x9038, 0x0000 }, { 0x90FD, 0x0000 }, { 0xFA27, 0x0000 }, 
    { 0xFA28, 0x0000 }, { 0xFA29, 0x0000 }, { 0x98EF, 0x0000 }, { 0x98FC, 0x0000 }, 
    { 0x9928, 0x0000 }, { 0x9DB4, 0x0000 }, { 0xFA2E, 0x0000 }, { 0xFA2F, 0x0000 }, 
    { 0xFA30, 0x0000 }, { 0xFA31, 0x0000 }, { 0xFA32, 0x0000 }, { 0xFA33, 0x0000 }, 
    { 0xFA34, 0x0000 }, { 0xFA35, 0x0000 }, { 0xFA36, 0x0000 }, { 0xFA37, 0x0000 }, 
    { 0xFA38, 0x0000 }, { 0xFA39, 0x0000 }, { 0xFA3A, 0x0000 }, { 0xFA3B, 0x0000 }, 
    { 0xFA3C, 0x0000 }, { 0xFA3D, 0x0000 }, { 0xFA3E, 0x0000 }, { 0xFA3F, 0x0000 }, 
    { 0xFA40, 0x0000 }, { 0xFA41, 0x0000 }, { 0xFA42, 0x0000 }, { 0xFA43, 0x0000 }, 
    { 0xFA44, 0x0000 }, { 0xFA45, 0x0000 }, { 0xFA46, 0x0000 }, { 0xFA47, 0x0000 }, 
    { 0xFA48, 0x0000 }, { 0xFA49, 0x0000 }, { 0xFA4A, 0x0000 }, { 0xFA4B, 0x0000 }, 
    { 0xFA4C, 0x0000 }, { 0xFA4D, 0x0000 }, { 0xFA4E, 0x0000 }, { 0xFA4F, 0x0000 }, 
    { 0xFA50, 0x0000 }, { 0xFA51, 0x0000 }, { 0xFA52, 0x0000 }, { 0xFA53, 0x0000 }, 
    { 0xFA54, 0x0000 }, { 0xFA55, 0x0000 }, { 0xFA56, 0x0000 }, { 0xFA57, 0x0000 }, 
    { 0xFA58, 0x0000 }, { 0xFA59, 0x0000 }, { 0xFA5A, 0x0000 }, { 0xFA5B, 0x0000 }, 
    { 0xFA5C, 0x0000 }, { 0xFA5D, 0x0000 }, { 0xFA5E, 0x0000 }, { 0xFA5F, 0x0000 }, 
    { 0xFA60, 0x0000 }, { 0xFA61, 0x0000 }, { 0xFA62, 0x0000 }, { 0xFA63, 0x0000 }, 
    { 0xFA64, 0x0000 }, { 0xFA65, 0x0000 }, { 0xFA66, 0x0000 }, { 0xFA67, 0x0000 }, 
    { 0xFA68, 0x0000 }, { 0xFA69, 0x0000 }, { 0xFA6A, 0x0000 }, { 0xFA6B, 0x0000 }, 
    { 0xFA6C, 0x0000 }, { 0xFA6D, 0x0000 }, { 0xFA6E, 0x0000 }, { 0xFA6F, 0x0000 }, 
    { 0xFA70, 0x0000 }, { 0xFA71, 0x0000 }, { 0xFA72, 0x0000 }, { 0xFA73, 0x0000 }, 
    { 0xFA74, 0x0000 }, { 0xFA75, 0x0000 }, { 0xFA76, 0x0000 }, { 0xFA77, 0x0000 }, 
    { 0xFA78, 0x0000 }, { 0xFA79, 0x0000 }, { 0xFA7A, 0x0000 }, { 0xFA7B, 0x0000 }, 
    { 0xFA7C, 0x0000 }, { 0xFA7D, 0x0000 }, { 0xFA7E, 0x0000 }, { 0xFA7F, 0x0000 }, 
    { 0xFA80, 0x0000 }, { 0xFA81, 0x0000 }, { 0xFA82, 0x0000 }, { 0xFA83, 0x0000 }, 
    { 0xFA84, 0x0000 }, { 0xFA85, 0x0000 }, { 0xFA86, 0x0000 }, { 0xFA87, 0x0000 }, 
    { 0xFA88, 0x0000 }, { 0xFA89, 0x0000 }, { 0xFA8A, 0x0000 }, { 0xFA8B, 0x0000 }, 
    { 0xFA8C, 0x0000 }, { 0xFA8D, 0x0000 }, { 0xFA8E, 0x0000 }, { 0xFA8F, 0x0000 }, 
    { 0xFA90, 0x0000 }, { 0xFA91, 0x0000 }, { 0xFA92, 0x0000 }, { 0xFA93, 0x0000 }, 
    { 0xFA94, 0x0000 }, { 0xFA95, 0x0000 }, { 0xFA96, 0x0000 }, { 0xFA97, 0x0000 }, 
    { 0xFA98, 0x0000 }, { 0xFA99, 0x0000 }, { 0xFA9A, 0x0000 }, { 0xFA9B, 0x0000 }, 
    { 0xFA9C, 0x0000 }, { 0xFA9D, 0x0000 }, { 0xFA9E, 0x0000 }, { 0xFA9F, 0x0000 }, 
    { 0xFAA0, 0x0000 }, { 0xFAA1, 0x0000 }, { 0xFAA2, 0x0000 }, { 0xFAA3, 0x0000 }, 
    { 0xFAA4, 0x0000 }, { 0xFAA5, 0x0000 }, { 0xFAA6, 0x0000 }, { 0xFAA7, 0x0000 }, 
    { 0xFAA8, 0x0000 }, { 0xFAA9, 0x0000 }, { 0xFAAA, 0x0000 }, { 0xFAAB, 0x0000 }, 
    { 0xFAAC, 0x0000 }, { 0xFAAD, 0x0000 }, { 0xFAAE, 0x0000 }, { 0xFAAF, 0x0000 }, 
    { 0xFAB0, 0x0000 }, { 0xFAB1, 0x0000 }, { 0xFAB2, 0x0000 }, { 0xFAB3, 0x0000 }, 
    { 0xFAB4, 0x0000 }, { 0xFAB5, 0x0000 }, { 0xFAB6, 0x0000 }, { 0xFAB7, 0x0000 }, 
    { 0xFAB8, 0x0000 }, { 0xFAB9, 0x0000 }, { 0xFABA, 0x0000 }, { 0xFABB, 0x0000 }, 
    { 0xFABC, 0x0000 }, { 0xFABD, 0x0000 }, { 0xFABE, 0x0000 }, { 0xFABF, 0x0000 }, 
    { 0xFAC0, 0x0000 }, { 0xFAC1, 0x0000 }, { 0xFAC2, 0x0000 }, { 0xFAC3, 0x0000 }, 
    { 0xFAC4, 0x0000 }, { 0xFAC5, 0x0000 }, { 0xFAC6, 0x0000 }, { 0xFAC7, 0x0000 }, 
    { 0xFAC8, 0x0000 }, { 0xFAC9, 0x0000 }, { 0xFACA, 0x0000 }, { 0xFACB, 0x0000 }, 
    { 0xFACC, 0x0000 }, { 0xFACD, 0x0000 }, { 0xFACE, 0x0000 }, { 0xFACF, 0x0000 }, 
    { 0xFAD0, 0x0000 }, { 0xFAD1, 0x0000 }, { 0xFAD2, 0x0000 }, { 0xFAD3, 0x0000 }, 
    { 0xFAD4, 0x0000 }, { 0xFAD5, 0x0000 }, { 0xFAD6, 0x0000 }, { 0xFAD7, 0x0000 }, 
    { 0xFAD8, 0x0000 }, { 0xFAD9, 0x0000 }, { 0xFADA, 0x0000 }, { 0xFADB, 0x0000 }, 
    { 0xFADC, 0x0000 }, { 0xFADD, 0x0000 }, { 0xFADE, 0x0000 }, { 0xFADF, 0x0000 }, 
    { 0xFAE0, 0x0000 }, { 0xFAE1, 0x0000 }, { 0xFAE2, 0x0000 }, { 0xFAE3, 0x0000 }, 
    { 0xFAE4, 0x0000 }, { 0xFAE5, 0x0000 }, { 0xFAE6, 0x0000 }, { 0xFAE7, 0x0000 }, 
    { 0xFAE8, 0x0000 }, { 0xFAE9, 0x0000 }, { 0xFAEA, 0x0000 }, { 0xFAEB, 0x0000 }, 
    { 0xFAEC, 0x0000 }, { 0xFAED, 0x0000 }, { 0xFAEE, 0x0000 }, { 0xFAEF, 0x0000 }, 
    { 0xFAF0, 0x0000 }, { 0xFAF1, 0x0000 }, { 0xFAF2, 0x0000 }, { 0xFAF3, 0x0000 }, 
    { 0xFAF4, 0x0000 }, { 0xFAF5, 0x0000 }, { 0xFAF6, 0x0000 }, { 0xFAF7, 0x0000 }, 
    { 0xFAF8, 0x0000 }, { 0xFAF9, 0x0000 }, { 0xFAFA, 0x0000 }, { 0xFAFB, 0x0000 }, 
    { 0xFAFC, 0x0000 }, { 0xFAFD, 0x0000 }, { 0xFAFE, 0x0000 }, { 0xFAFF, 0x0000 }
  };

    const bool CJK_Compatibility_IdeographsF900::_Identifier_Part[] = {
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
        1, 1, 1, 1, 1, 1, 0, 0, 
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
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

}; // namespace Babylon

dload(Babylon::CJK_Compatibility_IdeographsF900);
