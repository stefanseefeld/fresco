/*$Id: FE70-FEFE.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Wed, 15 Nov 2000 23:44:55 +0100.
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
 
  class Arabic_Presentation_FormsB : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    Arabic_Presentation_FormsB() {
      my_first_letter = 0xFE70;
      my_last_letter  = 0xFEFE;
      // my_version="3.0.1" // Not yet supported!

    }


    ~Arabic_Presentation_FormsB() {
    }

    _UCS4 firstLetter() {
      return my_first_letter;
    }
 
    _UCS4 lastLetter() {
      return my_last_letter;
    }
 
    // query functions:

    string blockname(const _UCS4 _uc) const {
      return "Arabic Presentation Forms-B";
    }

    bool isDefined(const _UCS4 _uc) const {
      return (isdefined[_uc - my_first_letter]);
    }

    _UCS4 uppercase(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return _uc;
    }

    _UCS4 lowercase(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return _uc;
    }

    _UCS4 titlecase(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return _uc;
    }

    int decDigitValue(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      throw UndefinedProperty(_uc, PROP_DEC_DIGIT_VALUE);
    }

    int digitValue(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      throw UndefinedProperty(_uc, PROP_DIGIT_VALUE);
    }

    float numericValue(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      throw UndefinedProperty(_uc, PROP_NUMERIC_VALUE);
    }

    Gen_Cat category(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Gen_Cat(CAT_Lo);
    }

    Can_Comb_Class combClass(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Can_Comb_Class(0);
    }

    Bidir_Props bidirProps(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Bidir_Props(BIDIR_AL);
    }

    Char_Decomp decompType(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Char_Decomp(Arabic_Presentation_FormsB::decomp[_uc - my_first_letter]);
    }

    _UTF32String decompose(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      Babylon::_UTF32String us;
      us.resize(2);
      us[0] = Arabic_Presentation_FormsB::decompStr[_uc - my_first_letter][0];
      us[1] = Arabic_Presentation_FormsB::decompStr[_uc - my_first_letter][1];
      if (us[1] == 0x0000) {
        us.resize(1);
      }

      return us;
    }

    bool mustMirror(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return 0;
    }

    Line_Break linebreak(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Line_Break(LB_AL);
    }

    EA_Width EAWidth(const _UCS4 _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::EA_Width(EA_WIDTH_N);
    }

    _UCS4 compose (const _UCS4 starter, const _UCS4 last) {
      return 0;
    }

    bool is_Zero_width(const _UCS4 _uc) const {
      return 0;
    }

    bool is_White_space(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Non_break(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Bidi_Control(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Join_Control(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Format_Control(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Dash(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Hyphen(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Quotation_Mark(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Terminal_Punctuation(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Math(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Paired_Punctuation(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Left_of_Pair(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Combining(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Non_spacing(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Hex_Digit(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Alphabetic(const _UCS4 _uc) const {
      return Arabic_Presentation_FormsB::Alphabetic[_uc - my_first_letter];
    }

    bool is_Diacritic(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Extender(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Identifier_Part(const _UCS4 _uc) const {
      return Arabic_Presentation_FormsB::Identifier_Part[_uc - my_first_letter];
    }

    bool is_Ignorable_Control(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Bidi_Hebrew_Right_to_Left(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Bidi_Arabic_Right_to_Left(const _UCS4 _uc) const {
      return Arabic_Presentation_FormsB::Bidi_Arabic_Right_to_Left[_uc - my_first_letter];
    }

    bool is_Bidi_Embedding_or_Override(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Uppercase(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Lowercase(const _UCS4 _uc) const {
      return 0;
    }

    bool is_Space(const _UCS4 _uc) const {
      return (isDefined(_uc) && category(_uc) == CAT_Zs);
    }

    bool is_ISO_Control(const _UCS4 _uc) const {
      return (isDefined(_uc) && category(_uc) == CAT_Cc);
    }

    bool is_Punctuation(const _UCS4 _uc) const {
      return (isDefined(_uc) && (category(_uc) == CAT_Pc ||
                                 category(_uc) == CAT_Pd ||
                                 category(_uc) == CAT_Ps ||
                                 category(_uc) == CAT_Pe ||
                                 category(_uc) == CAT_Pi ||
                                 category(_uc) == CAT_Pf ||
                                 category(_uc) == CAT_Po)
             );
    }

    bool is_Line_Separator(const _UCS4 _uc) const {
      return (isDefined(_uc) && category(_uc) == CAT_Zl);
    }

    bool is_Paragraph_Separator(const _UCS4 _uc) const {
      return (isDefined(_uc) && category(_uc) == CAT_Zp);
    }

    bool is_Currency_Symbol(const _UCS4 _uc) const {
      return (isDefined(_uc) && category(_uc) == CAT_Sc);
    }

    bool is_Titlecase(const _UCS4 _uc) const {
      return (isDefined(_uc) && category(_uc) == CAT_Lt);
    }


  private:
    // functions
    Arabic_Presentation_FormsB(const Arabic_Presentation_FormsB &) {}
 
    Babylon::_UCS4 my_first_letter;
    Babylon::_UCS4 my_last_letter;
    static const bool isdefined[143];
    static const unsigned char decomp[143];
    static const _UCS2 decompStr[143][2];
    static const bool Alphabetic[143];
    static const bool Identifier_Part[143];
    static const bool Bidi_Arabic_Right_to_Left[143];

  }; // class Arabic_Presentation_FormsB

  const bool Arabic_Presentation_FormsB::isdefined[] = {
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

  const unsigned char Arabic_Presentation_FormsB::decomp[] = {
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

  const _UCS2 Arabic_Presentation_FormsB::decompStr[][2] = {
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

    const bool Arabic_Presentation_FormsB::Alphabetic[] = {
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

    const bool Arabic_Presentation_FormsB::Identifier_Part[] = {
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

    const bool Arabic_Presentation_FormsB::Bidi_Arabic_Right_to_Left[] = {
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
 
dload(Babylon::Arabic_Presentation_FormsB);
