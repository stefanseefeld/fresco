/*$Id: FE70-FEFE.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Wed,  6 Dec 2000 23:40:05 +0100.
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

  class Arabic_Presentation_FormsBFE70 : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    Arabic_Presentation_FormsBFE70() {
      _first_letter = 0xFE70;
      _last_letter  = 0xFEFE;
      // _version="3.0.1" // Not yet supported!

    }


    ~Arabic_Presentation_FormsBFE70() {
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
      return "Arabic Presentation Forms-B";
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
      return Babylon::Bidir_Props(BIDIR_AL);
    }

    Char_Decomp decomp_type(const UCS4 uc) const {
      if (!is_defined(uc))
        return DECOMP_MAX;
      return Babylon::Char_Decomp(Arabic_Presentation_FormsBFE70::_decomp[uc - _first_letter]);
    }

    UTF32_string decompose(const UCS4 uc) const {
      Babylon::UTF32_string us;
      us.resize(2);
      us[0] = Arabic_Presentation_FormsBFE70::_decompStr[uc - _first_letter][0];
      us[1] = Arabic_Presentation_FormsBFE70::_decompStr[uc - _first_letter][1];
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
      return Babylon::Line_Break(LB_AL);
    }

    EA_Width EA_width(const UCS4 uc) const {
      if (!is_defined(uc))
        return EA_WIDTH_MAX;
      return Babylon::EA_Width(EA_WIDTH_N);
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
      return Arabic_Presentation_FormsBFE70::_Composite[uc - _first_letter];
    }

    bool is_Hex_Digit(const UCS4 uc) const {
      return 0;
    }

    bool is_Alphabetic(const UCS4 uc) const {
      return Arabic_Presentation_FormsBFE70::_Alphabetic[uc - _first_letter];
    }

    bool is_Diacritic(const UCS4 uc) const {
      return 0;
    }

    bool is_Extender(const UCS4 uc) const {
      return 0;
    }

    bool is_Identifier_Part(const UCS4 uc) const {
      return Arabic_Presentation_FormsBFE70::_Identifier_Part[uc - _first_letter];
    }

    bool is_Ignorable_Control(const UCS4 uc) const {
      return 0;
    }

    bool is_Bidi_Hebrew_Right_to_Left(const UCS4 uc) const {
      return 0;
    }

    bool is_Bidi_Arabic_Right_to_Left(const UCS4 uc) const {
      return Arabic_Presentation_FormsBFE70::_Bidi_Arabic_Right_to_Left[uc - _first_letter];
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
    Arabic_Presentation_FormsBFE70(const Arabic_Presentation_FormsBFE70 &) {}

    Babylon::UCS4 _first_letter;
    Babylon::UCS4 _last_letter;
    static const bool _is_defined[143];
    static const unsigned char _decomp[143];
    static const UCS2 _decompStr[143][2];
    static const bool _Composite[143];
    static const bool _Alphabetic[143];
    static const bool _Identifier_Part[143];
    static const bool _Bidi_Arabic_Right_to_Left[143];

  }; // class Arabic_Presentation_FormsBFE70

  const bool Arabic_Presentation_FormsBFE70::_is_defined[] = {
    1, 1, 1, 0, 1, 0, 1, 1, 
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
    1, 1, 1, 1, 1, 0, 0
  };

  const unsigned char Arabic_Presentation_FormsBFE70::_decomp[] = {
    DECOMP_ISOLATED, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_NO_DECOMP, DECOMP_ISOLATED, DECOMP_NO_DECOMP, DECOMP_ISOLATED, DECOMP_MEDIAL, 
    DECOMP_ISOLATED, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_MEDIAL, 
    DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, 
    DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, 
    DECOMP_FINAL, DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, 
    DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, 
    DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, 
    DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, 
    DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, 
    DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, 
    DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, 
    DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, 
    DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, 
    DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, 
    DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, 
    DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, 
    DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, 
    DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP
  };

  const UCS2 Arabic_Presentation_FormsBFE70::_decompStr[][2] = {
    { 0x0020, 0x064B }, { 0x0640, 0x064B }, { 0x0020, 0x064C }, { 0xFE73, 0x0000 }, 
    { 0x0020, 0x064D }, { 0xFE75, 0x0000 }, { 0x0020, 0x064E }, { 0x0640, 0x064E }, 
    { 0x0020, 0x064F }, { 0x0640, 0x064F }, { 0x0020, 0x0650 }, { 0x0640, 0x0650 }, 
    { 0x0020, 0x0651 }, { 0x0640, 0x0651 }, { 0x0020, 0x0652 }, { 0x0640, 0x0652 }, 
    { 0x0621, 0x0000 }, { 0x0622, 0x0000 }, { 0x0622, 0x0000 }, { 0x0623, 0x0000 }, 
    { 0x0623, 0x0000 }, { 0x0624, 0x0000 }, { 0x0624, 0x0000 }, { 0x0625, 0x0000 }, 
    { 0x0625, 0x0000 }, { 0x0626, 0x0000 }, { 0x0626, 0x0000 }, { 0x0626, 0x0000 }, 
    { 0x0626, 0x0000 }, { 0x0627, 0x0000 }, { 0x0627, 0x0000 }, { 0x0628, 0x0000 }, 
    { 0x0628, 0x0000 }, { 0x0628, 0x0000 }, { 0x0628, 0x0000 }, { 0x0629, 0x0000 }, 
    { 0x0629, 0x0000 }, { 0x062A, 0x0000 }, { 0x062A, 0x0000 }, { 0x062A, 0x0000 }, 
    { 0x062A, 0x0000 }, { 0x062B, 0x0000 }, { 0x062B, 0x0000 }, { 0x062B, 0x0000 }, 
    { 0x062B, 0x0000 }, { 0x062C, 0x0000 }, { 0x062C, 0x0000 }, { 0x062C, 0x0000 }, 
    { 0x062C, 0x0000 }, { 0x062D, 0x0000 }, { 0x062D, 0x0000 }, { 0x062D, 0x0000 }, 
    { 0x062D, 0x0000 }, { 0x062E, 0x0000 }, { 0x062E, 0x0000 }, { 0x062E, 0x0000 }, 
    { 0x062E, 0x0000 }, { 0x062F, 0x0000 }, { 0x062F, 0x0000 }, { 0x0630, 0x0000 }, 
    { 0x0630, 0x0000 }, { 0x0631, 0x0000 }, { 0x0631, 0x0000 }, { 0x0632, 0x0000 }, 
    { 0x0632, 0x0000 }, { 0x0633, 0x0000 }, { 0x0633, 0x0000 }, { 0x0633, 0x0000 }, 
    { 0x0633, 0x0000 }, { 0x0634, 0x0000 }, { 0x0634, 0x0000 }, { 0x0634, 0x0000 }, 
    { 0x0634, 0x0000 }, { 0x0635, 0x0000 }, { 0x0635, 0x0000 }, { 0x0635, 0x0000 }, 
    { 0x0635, 0x0000 }, { 0x0636, 0x0000 }, { 0x0636, 0x0000 }, { 0x0636, 0x0000 }, 
    { 0x0636, 0x0000 }, { 0x0637, 0x0000 }, { 0x0637, 0x0000 }, { 0x0637, 0x0000 }, 
    { 0x0637, 0x0000 }, { 0x0638, 0x0000 }, { 0x0638, 0x0000 }, { 0x0638, 0x0000 }, 
    { 0x0638, 0x0000 }, { 0x0639, 0x0000 }, { 0x0639, 0x0000 }, { 0x0639, 0x0000 }, 
    { 0x0639, 0x0000 }, { 0x063A, 0x0000 }, { 0x063A, 0x0000 }, { 0x063A, 0x0000 }, 
    { 0x063A, 0x0000 }, { 0x0641, 0x0000 }, { 0x0641, 0x0000 }, { 0x0641, 0x0000 }, 
    { 0x0641, 0x0000 }, { 0x0642, 0x0000 }, { 0x0642, 0x0000 }, { 0x0642, 0x0000 }, 
    { 0x0642, 0x0000 }, { 0x0643, 0x0000 }, { 0x0643, 0x0000 }, { 0x0643, 0x0000 }, 
    { 0x0643, 0x0000 }, { 0x0644, 0x0000 }, { 0x0644, 0x0000 }, { 0x0644, 0x0000 }, 
    { 0x0644, 0x0000 }, { 0x0645, 0x0000 }, { 0x0645, 0x0000 }, { 0x0645, 0x0000 }, 
    { 0x0645, 0x0000 }, { 0x0646, 0x0000 }, { 0x0646, 0x0000 }, { 0x0646, 0x0000 }, 
    { 0x0646, 0x0000 }, { 0x0647, 0x0000 }, { 0x0647, 0x0000 }, { 0x0647, 0x0000 }, 
    { 0x0647, 0x0000 }, { 0x0648, 0x0000 }, { 0x0648, 0x0000 }, { 0x0649, 0x0000 }, 
    { 0x0649, 0x0000 }, { 0x064A, 0x0000 }, { 0x064A, 0x0000 }, { 0x064A, 0x0000 }, 
    { 0x064A, 0x0000 }, { 0x0644, 0x0622 }, { 0x0644, 0x0622 }, { 0x0644, 0x0623 }, 
    { 0x0644, 0x0623 }, { 0x0644, 0x0625 }, { 0x0644, 0x0625 }, { 0x0644, 0x0627 }, 
    { 0x0644, 0x0627 }, { 0xFEFD, 0x0000 }, { 0xFEFE, 0x0000 }
  };

    const bool Arabic_Presentation_FormsBFE70::_Composite[] = {
        1, 1, 1, 0, 1, 0, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
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
        0, 0, 0, 0, 0, 0, 0
    };

    const bool Arabic_Presentation_FormsBFE70::_Alphabetic[] = {
        1, 1, 1, 0, 1, 0, 1, 1, 
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
        1, 1, 1, 1, 1, 0, 0
    };

    const bool Arabic_Presentation_FormsBFE70::_Identifier_Part[] = {
        1, 1, 1, 0, 1, 0, 1, 1, 
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
        1, 1, 1, 1, 1, 0, 0
    };

    const bool Arabic_Presentation_FormsBFE70::_Bidi_Arabic_Right_to_Left[] = {
        1, 1, 1, 0, 1, 0, 1, 1, 
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
        1, 1, 1, 1, 1, 0, 0
    };

}; // namespace Babylon

dload(Babylon::Arabic_Presentation_FormsBFE70);
