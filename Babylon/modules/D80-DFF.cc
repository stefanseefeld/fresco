/*$Id: D80-DFF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 21 Nov 2000 21:11:30 +0100.
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
      my_first_letter = 0xD80;
      my_last_letter  = 0xDFF;
      // my_version="3.0.1" // Not yet supported!
      composeMap[0x0DD90DCA] = 0x0DDA;
      composeMap[0x0DD90DCF] = 0x0DDC;
      composeMap[0x0DD90DDF] = 0x0DDE;
      composeMap[0x0DDC0DCA] = 0x0DDD;

    }


    ~SinhalaD80() {
    }

    UCS4 firstLetter() {
      return my_first_letter;
    }
 
    UCS4 lastLetter() {
      return my_last_letter;
    }
 
    // query functions:

    string blockname(const UCS4 & _uc) const {
      return "Sinhala";
    }

    bool isDefined(const UCS4 & _uc) const {
      return (isdefined[_uc - my_first_letter]);
    }

    UCS4 uppercase(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return _uc;
    }

    UCS4 lowercase(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return _uc;
    }

    UCS4 titlecase(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return _uc;
    }

    int decDigitValue(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      throw UndefinedProperty(_uc, PROP_DEC_DIGIT_VALUE);
    }

    int digitValue(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      throw UndefinedProperty(_uc, PROP_DIGIT_VALUE);
    }

    float numericValue(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      throw UndefinedProperty(_uc, PROP_NUMERIC_VALUE);
    }

    Gen_Cat category(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Gen_Cat(SinhalaD80::cat[_uc - my_first_letter]);
    }

    Can_Comb_Class combClass(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Can_Comb_Class(SinhalaD80::combCl[_uc - my_first_letter]);
    }

    Bidir_Props bidirProps(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Bidir_Props(SinhalaD80::bidir[_uc - my_first_letter]);
    }

    Char_Decomp decompType(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Char_Decomp(DECOMP_NO_DECOMP);
    }

    UTF32String decompose(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      Babylon::UTF32String us;
      us.resize(2);
      us[0] = SinhalaD80::decompStr[_uc - my_first_letter][0];
      us[1] = SinhalaD80::decompStr[_uc - my_first_letter][1];
      if (us[1] == 0x0000) {
        us.resize(1);
      }

      return us;
    }

    bool mustMirror(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return 0;
    }

    Line_Break linebreak(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Line_Break(SinhalaD80::lb[_uc - my_first_letter]);
    }

    EA_Width EAWidth(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::EA_Width(EA_WIDTH_N);
    }

    UCS4 compose (const UCS4 & starter, const UCS4 & last) {
      return composeMap[starter << 16 | last];
    }

    bool is_Zero_width(const UCS4 & _uc) const {
      return 0;
    }

    bool is_White_space(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Non_break(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Bidi_Control(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Join_Control(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Format_Control(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Dash(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Hyphen(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Quotation_Mark(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Terminal_Punctuation(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Math(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Paired_Punctuation(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Left_of_Pair(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Combining(const UCS4 & _uc) const {
      return SinhalaD80::Combining[_uc - my_first_letter];
    }

    bool is_Non_spacing(const UCS4 & _uc) const {
      return SinhalaD80::Non_spacing[_uc - my_first_letter];
    }

    bool is_Hex_Digit(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Alphabetic(const UCS4 & _uc) const {
      return SinhalaD80::Alphabetic[_uc - my_first_letter];
    }

    bool is_Diacritic(const UCS4 & _uc) const {
      return SinhalaD80::Diacritic[_uc - my_first_letter];
    }

    bool is_Extender(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Identifier_Part(const UCS4 & _uc) const {
      return SinhalaD80::Identifier_Part[_uc - my_first_letter];
    }

    bool is_Ignorable_Control(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Bidi_Hebrew_Right_to_Left(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Bidi_Arabic_Right_to_Left(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Bidi_Embedding_or_Override(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Uppercase(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Lowercase(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Space(const UCS4 & _uc) const {
      return (isDefined(_uc) && category(_uc) == CAT_Zs);
    }

    bool is_ISO_Control(const UCS4 & _uc) const {
      return (isDefined(_uc) && category(_uc) == CAT_Cc);
    }

    bool is_Punctuation(const UCS4 & _uc) const {
      return (isDefined(_uc) && (category(_uc) == CAT_Pc ||
                                 category(_uc) == CAT_Pd ||
                                 category(_uc) == CAT_Ps ||
                                 category(_uc) == CAT_Pe ||
                                 category(_uc) == CAT_Pi ||
                                 category(_uc) == CAT_Pf ||
                                 category(_uc) == CAT_Po)
             );
    }

    bool is_Line_Separator(const UCS4 & _uc) const {
      return (isDefined(_uc) && category(_uc) == CAT_Zl);
    }

    bool is_Paragraph_Separator(const UCS4 & _uc) const {
      return (isDefined(_uc) && category(_uc) == CAT_Zp);
    }

    bool is_Currency_Symbol(const UCS4 & _uc) const {
      return (isDefined(_uc) && category(_uc) == CAT_Sc);
    }

    bool is_Titlecase(const UCS4 & _uc) const {
      return (isDefined(_uc) && category(_uc) == CAT_Lt);
    }


  private:
    // functions
    SinhalaD80(const SinhalaD80 &) {}
 
    Babylon::UCS4 my_first_letter;
    Babylon::UCS4 my_last_letter;
    static const bool isdefined[128];
    static const unsigned char cat[128];
    static const unsigned char combCl[128];
    static const unsigned char bidir[128];
    static const UCS2 decompStr[128][2];
    static const unsigned char lb[128];
    map<UCS4, UCS4> composeMap;
    static const bool Combining[128];
    static const bool Non_spacing[128];
    static const bool Alphabetic[128];
    static const bool Diacritic[128];
    static const bool Identifier_Part[128];

  }; // class SinhalaD80

  const bool SinhalaD80::isdefined[] = {
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

  const unsigned char SinhalaD80::cat[] = {
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

  const unsigned char SinhalaD80::combCl[] = {
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

  const unsigned char SinhalaD80::bidir[] = {
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

  const UCS2 SinhalaD80::decompStr[][2] = {
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

  const unsigned char SinhalaD80::lb[] = {
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

    const bool SinhalaD80::Combining[] = {
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

    const bool SinhalaD80::Non_spacing[] = {
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

    const bool SinhalaD80::Alphabetic[] = {
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

    const bool SinhalaD80::Diacritic[] = {
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

    const bool SinhalaD80::Identifier_Part[] = {
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
