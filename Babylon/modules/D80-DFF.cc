/*$Id: D80-DFF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Wed,  6 Dec 2000 23:23:20 +0100.
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

  class SinhalaD80 : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    SinhalaD80() {
      _first_letter = 0xD80;
      _last_letter  = 0xDFF;
      // _version="3.0.1" // Not yet supported!
      _composeMap[0x0DD90DCA] = 0x0DDA;
      _composeMap[0x0DD90DCF] = 0x0DDC;
      _composeMap[0x0DD90DDF] = 0x0DDE;
      _composeMap[0x0DDC0DCA] = 0x0DDD;

    }


    ~SinhalaD80() {
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
      return "Sinhala";
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
      return Babylon::Gen_Cat(SinhalaD80::_cat[uc - _first_letter]);
    }

    Can_Comb_Class comb_class(const UCS4 uc) const {
      if (!is_defined(uc))
        return CC_MAX;
      return Can_Comb_Class(SinhalaD80::_comb_cl[uc - _first_letter]);
    }

    Bidir_Props bidir_props(const UCS4 uc) const {
      if (!is_defined(uc))
        return BIDIR_MAX;
      return Babylon::Bidir_Props(SinhalaD80::_bidir[uc - _first_letter]);
    }

    Char_Decomp decomp_type(const UCS4 uc) const {
      if (!is_defined(uc))
        return DECOMP_MAX;
      return Babylon::Char_Decomp(DECOMP_NO_DECOMP);
    }

    UTF32_string decompose(const UCS4 uc) const {
      Babylon::UTF32_string us;
      us.resize(2);
      us[0] = SinhalaD80::_decompStr[uc - _first_letter][0];
      us[1] = SinhalaD80::_decompStr[uc - _first_letter][1];
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
      return Babylon::Line_Break(SinhalaD80::_lb[uc - _first_letter]);
    }

    EA_Width EA_width(const UCS4 uc) const {
      if (!is_defined(uc))
        return EA_WIDTH_MAX;
      return Babylon::EA_Width(EA_WIDTH_N);
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
      return SinhalaD80::_Combining[uc - _first_letter];
    }

    bool is_Non_spacing(const UCS4 uc) const {
      return SinhalaD80::_Non_spacing[uc - _first_letter];
    }

    bool is_Composite(const UCS4 uc) const {
      return SinhalaD80::_Composite[uc - _first_letter];
    }

    bool is_Hex_Digit(const UCS4 uc) const {
      return 0;
    }

    bool is_Alphabetic(const UCS4 uc) const {
      return SinhalaD80::_Alphabetic[uc - _first_letter];
    }

    bool is_Diacritic(const UCS4 uc) const {
      return SinhalaD80::_Diacritic[uc - _first_letter];
    }

    bool is_Extender(const UCS4 uc) const {
      return 0;
    }

    bool is_Identifier_Part(const UCS4 uc) const {
      return SinhalaD80::_Identifier_Part[uc - _first_letter];
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
    SinhalaD80(const SinhalaD80 &) {}

    Babylon::UCS4 _first_letter;
    Babylon::UCS4 _last_letter;
    static const bool _is_defined[128];
    static const unsigned char _cat[128];
    static const unsigned char _comb_cl[128];
    static const unsigned char _bidir[128];
    static const UCS2 _decompStr[128][2];
    static const unsigned char _lb[128];
    map<UCS4, UCS4> _composeMap;
    static const bool _Combining[128];
    static const bool _Non_spacing[128];
    static const bool _Composite[128];
    static const bool _Alphabetic[128];
    static const bool _Diacritic[128];
    static const bool _Identifier_Part[128];

  }; // class SinhalaD80

  const bool SinhalaD80::_is_defined[] = {
    0, 0, 1, 1, 0, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 0, 
    0, 0, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 0, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 0, 1, 0, 0, 
    1, 1, 1, 1, 1, 1, 1, 0, 
    0, 0, 1, 0, 0, 0, 0, 1, 
    1, 1, 1, 1, 1, 0, 1, 0, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 1, 1, 1, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0
  };

  const unsigned char SinhalaD80::_cat[] = {
    CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Mc, 
    CAT_Mc, CAT_Mc, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Mc, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Mc, CAT_Lo, CAT_Mc, CAT_Mc, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Mc, 
    CAT_Mc, CAT_Mc, CAT_Mn, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, 
    CAT_Mc, CAT_Mc, CAT_Mn, CAT_Mn, CAT_Mn, CAT_Mc, CAT_Mn, CAT_Mc, 
    CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, 
    CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, 
    CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, 
    CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Po, CAT_Mc, CAT_Mc, CAT_Mc, 
    CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc
  };

  const unsigned char SinhalaD80::_comb_cl[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 9, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0
  };

  const unsigned char SinhalaD80::_bidir[] = {
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_NSM, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L
  };

  const UCS2 SinhalaD80::_decompStr[][2] = {
    { 0x0D80, 0x0000 }, { 0x0D81, 0x0000 }, { 0x0D82, 0x0000 }, { 0x0D83, 0x0000 }, 
    { 0x0D84, 0x0000 }, { 0x0D85, 0x0000 }, { 0x0D86, 0x0000 }, { 0x0D87, 0x0000 }, 
    { 0x0D88, 0x0000 }, { 0x0D89, 0x0000 }, { 0x0D8A, 0x0000 }, { 0x0D8B, 0x0000 }, 
    { 0x0D8C, 0x0000 }, { 0x0D8D, 0x0000 }, { 0x0D8E, 0x0000 }, { 0x0D8F, 0x0000 }, 
    { 0x0D90, 0x0000 }, { 0x0D91, 0x0000 }, { 0x0D92, 0x0000 }, { 0x0D93, 0x0000 }, 
    { 0x0D94, 0x0000 }, { 0x0D95, 0x0000 }, { 0x0D96, 0x0000 }, { 0x0D97, 0x0000 }, 
    { 0x0D98, 0x0000 }, { 0x0D99, 0x0000 }, { 0x0D9A, 0x0000 }, { 0x0D9B, 0x0000 }, 
    { 0x0D9C, 0x0000 }, { 0x0D9D, 0x0000 }, { 0x0D9E, 0x0000 }, { 0x0D9F, 0x0000 }, 
    { 0x0DA0, 0x0000 }, { 0x0DA1, 0x0000 }, { 0x0DA2, 0x0000 }, { 0x0DA3, 0x0000 }, 
    { 0x0DA4, 0x0000 }, { 0x0DA5, 0x0000 }, { 0x0DA6, 0x0000 }, { 0x0DA7, 0x0000 }, 
    { 0x0DA8, 0x0000 }, { 0x0DA9, 0x0000 }, { 0x0DAA, 0x0000 }, { 0x0DAB, 0x0000 }, 
    { 0x0DAC, 0x0000 }, { 0x0DAD, 0x0000 }, { 0x0DAE, 0x0000 }, { 0x0DAF, 0x0000 }, 
    { 0x0DB0, 0x0000 }, { 0x0DB1, 0x0000 }, { 0x0DB2, 0x0000 }, { 0x0DB3, 0x0000 }, 
    { 0x0DB4, 0x0000 }, { 0x0DB5, 0x0000 }, { 0x0DB6, 0x0000 }, { 0x0DB7, 0x0000 }, 
    { 0x0DB8, 0x0000 }, { 0x0DB9, 0x0000 }, { 0x0DBA, 0x0000 }, { 0x0DBB, 0x0000 }, 
    { 0x0DBC, 0x0000 }, { 0x0DBD, 0x0000 }, { 0x0DBE, 0x0000 }, { 0x0DBF, 0x0000 }, 
    { 0x0DC0, 0x0000 }, { 0x0DC1, 0x0000 }, { 0x0DC2, 0x0000 }, { 0x0DC3, 0x0000 }, 
    { 0x0DC4, 0x0000 }, { 0x0DC5, 0x0000 }, { 0x0DC6, 0x0000 }, { 0x0DC7, 0x0000 }, 
    { 0x0DC8, 0x0000 }, { 0x0DC9, 0x0000 }, { 0x0DCA, 0x0000 }, { 0x0DCB, 0x0000 }, 
    { 0x0DCC, 0x0000 }, { 0x0DCD, 0x0000 }, { 0x0DCE, 0x0000 }, { 0x0DCF, 0x0000 }, 
    { 0x0DD0, 0x0000 }, { 0x0DD1, 0x0000 }, { 0x0DD2, 0x0000 }, { 0x0DD3, 0x0000 }, 
    { 0x0DD4, 0x0000 }, { 0x0DD5, 0x0000 }, { 0x0DD6, 0x0000 }, { 0x0DD7, 0x0000 }, 
    { 0x0DD8, 0x0000 }, { 0x0DD9, 0x0000 }, { 0x0DD9, 0x0DCA }, { 0x0DDB, 0x0000 }, 
    { 0x0DD9, 0x0DCF }, { 0x0DDC, 0x0DCA }, { 0x0DD9, 0x0DDF }, { 0x0DDF, 0x0000 }, 
    { 0x0DE0, 0x0000 }, { 0x0DE1, 0x0000 }, { 0x0DE2, 0x0000 }, { 0x0DE3, 0x0000 }, 
    { 0x0DE4, 0x0000 }, { 0x0DE5, 0x0000 }, { 0x0DE6, 0x0000 }, { 0x0DE7, 0x0000 }, 
    { 0x0DE8, 0x0000 }, { 0x0DE9, 0x0000 }, { 0x0DEA, 0x0000 }, { 0x0DEB, 0x0000 }, 
    { 0x0DEC, 0x0000 }, { 0x0DED, 0x0000 }, { 0x0DEE, 0x0000 }, { 0x0DEF, 0x0000 }, 
    { 0x0DF0, 0x0000 }, { 0x0DF1, 0x0000 }, { 0x0DF2, 0x0000 }, { 0x0DF3, 0x0000 }, 
    { 0x0DF4, 0x0000 }, { 0x0DF5, 0x0000 }, { 0x0DF6, 0x0000 }, { 0x0DF7, 0x0000 }, 
    { 0x0DF8, 0x0000 }, { 0x0DF9, 0x0000 }, { 0x0DFA, 0x0000 }, { 0x0DFB, 0x0000 }, 
    { 0x0DFC, 0x0000 }, { 0x0DFD, 0x0000 }, { 0x0DFE, 0x0000 }, { 0x0DFF, 0x0000 }
  };

  const unsigned char SinhalaD80::_lb[] = {
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_CM, 
    LB_CM, LB_CM, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_CM, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_CM, LB_AL, LB_CM, LB_CM, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_CM, 
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_CM, LB_CM, LB_CM, LB_CM, LB_AL, LB_CM, LB_CM, LB_CM, 
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM
  };

    const bool SinhalaD80::_Combining[] = {
        0, 0, 1, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 0, 0, 0, 0, 1, 
        1, 1, 1, 1, 1, 0, 1, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool SinhalaD80::_Non_spacing[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 1, 0, 1, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool SinhalaD80::_Composite[] = {
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
        0, 0, 1, 0, 1, 1, 1, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool SinhalaD80::_Alphabetic[] = {
        0, 0, 1, 1, 0, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 0, 
        0, 0, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 0, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 0, 1, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 0, 
        0, 0, 0, 0, 0, 0, 0, 1, 
        1, 1, 1, 1, 1, 0, 1, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool SinhalaD80::_Diacritic[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool SinhalaD80::_Identifier_Part[] = {
        0, 0, 1, 1, 0, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 0, 
        0, 0, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 0, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 0, 1, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 0, 
        0, 0, 1, 0, 0, 0, 0, 1, 
        1, 1, 1, 1, 1, 0, 1, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

}; // namespace Babylon

dload(Babylon::SinhalaD80);
