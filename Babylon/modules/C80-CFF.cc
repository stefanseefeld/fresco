/*$Id: C80-CFF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 21 Nov 2000 21:11:25 +0100.
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
 
  class KannadaC80 : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    KannadaC80() {
      my_first_letter = 0xC80;
      my_last_letter  = 0xCFF;
      // my_version="3.0.1" // Not yet supported!
      composeMap[0x0CBF0CD5] = 0x0CC0;
      composeMap[0x0CC60CC2] = 0x0CCA;
      composeMap[0x0CC60CD5] = 0x0CC7;
      composeMap[0x0CC60CD6] = 0x0CC8;
      composeMap[0x0CCA0CD5] = 0x0CCB;

    }


    ~KannadaC80() {
    }

    UCS4 firstLetter() {
      return my_first_letter;
    }
 
    UCS4 lastLetter() {
      return my_last_letter;
    }
 
    // query functions:

    string blockname(const UCS4 & _uc) const {
      return "Kannada";
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
      switch(_uc) {
      case 0x0CE6:
        return 0;
        break;
      case 0x0CE7:
        return 1;
        break;
      case 0x0CE8:
        return 2;
        break;
      case 0x0CE9:
        return 3;
        break;
      case 0x0CEA:
        return 4;
        break;
      case 0x0CEB:
        return 5;
        break;
      case 0x0CEC:
        return 6;
        break;
      case 0x0CED:
        return 7;
        break;
      case 0x0CEE:
        return 8;
        break;
      case 0x0CEF:
        return 9;
        break;
      default:
        throw UndefinedProperty(_uc, PROP_DEC_DIGIT_VALUE);
      }
    }

    int digitValue(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      switch(_uc) {
      case 0x0CE6:
        return 0;
        break;
      case 0x0CE7:
        return 1;
        break;
      case 0x0CE8:
        return 2;
        break;
      case 0x0CE9:
        return 3;
        break;
      case 0x0CEA:
        return 4;
        break;
      case 0x0CEB:
        return 5;
        break;
      case 0x0CEC:
        return 6;
        break;
      case 0x0CED:
        return 7;
        break;
      case 0x0CEE:
        return 8;
        break;
      case 0x0CEF:
        return 9;
        break;
      default:
        throw UndefinedProperty(_uc, PROP_DIGIT_VALUE);
      }
    }

    float numericValue(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      switch(_uc) {
      case 0x0CE6:
        return 0.000000;
        break;
      case 0x0CE7:
        return 1.000000;
        break;
      case 0x0CE8:
        return 2.000000;
        break;
      case 0x0CE9:
        return 3.000000;
        break;
      case 0x0CEA:
        return 4.000000;
        break;
      case 0x0CEB:
        return 5.000000;
        break;
      case 0x0CEC:
        return 6.000000;
        break;
      case 0x0CED:
        return 7.000000;
        break;
      case 0x0CEE:
        return 8.000000;
        break;
      case 0x0CEF:
        return 9.000000;
        break;
      default:
        throw UndefinedProperty(_uc, PROP_NUMERIC_VALUE);
      }
    }

    Gen_Cat category(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Gen_Cat(KannadaC80::cat[_uc - my_first_letter]);
    }

    Can_Comb_Class combClass(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Can_Comb_Class(KannadaC80::combCl[_uc - my_first_letter]);
    }

    Bidir_Props bidirProps(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Bidir_Props(KannadaC80::bidir[_uc - my_first_letter]);
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
      us[0] = KannadaC80::decompStr[_uc - my_first_letter][0];
      us[1] = KannadaC80::decompStr[_uc - my_first_letter][1];
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
      return Babylon::Line_Break(KannadaC80::lb[_uc - my_first_letter]);
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
      return KannadaC80::Combining[_uc - my_first_letter];
    }

    bool is_Non_spacing(const UCS4 & _uc) const {
      return KannadaC80::Non_spacing[_uc - my_first_letter];
    }

    bool is_Hex_Digit(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Alphabetic(const UCS4 & _uc) const {
      return KannadaC80::Alphabetic[_uc - my_first_letter];
    }

    bool is_Diacritic(const UCS4 & _uc) const {
      return KannadaC80::Diacritic[_uc - my_first_letter];
    }

    bool is_Extender(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Identifier_Part(const UCS4 & _uc) const {
      return KannadaC80::Identifier_Part[_uc - my_first_letter];
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
    KannadaC80(const KannadaC80 &) {}
 
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

  }; // class KannadaC80

  const bool KannadaC80::isdefined[] = {
    0, 0, 1, 1, 0, 1, 1, 1, 
    1, 1, 1, 1, 1, 0, 1, 1, 
    1, 0, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 0, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 0, 1, 1, 1, 
    1, 1, 0, 0, 0, 0, 1, 1, 
    1, 1, 1, 1, 1, 0, 1, 1, 
    1, 0, 1, 1, 1, 1, 0, 0, 
    0, 0, 0, 0, 0, 1, 1, 0, 
    0, 0, 0, 0, 0, 0, 1, 0, 
    1, 1, 0, 0, 0, 0, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0
  };

  const unsigned char KannadaC80::cat[] = {
    CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Mc, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Mc, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Mc, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Mc, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mn, 
    CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mn, CAT_Mc, 
    CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mn, CAT_Mn, CAT_Mc, CAT_Mc, 
    CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, 
    CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Lo, CAT_Mc, 
    CAT_Lo, CAT_Lo, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Nd, CAT_Nd, 
    CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, 
    CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, 
    CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc, CAT_Mc
  };

  const unsigned char KannadaC80::combCl[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 9, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0
  };

  const unsigned char KannadaC80::bidir[] = {
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_NSM, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_NSM, BIDIR_NSM, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L
  };

  const UCS2 KannadaC80::decompStr[][2] = {
    { 0x0C80, 0x0000 }, { 0x0C81, 0x0000 }, { 0x0C82, 0x0000 }, { 0x0C83, 0x0000 }, 
    { 0x0C84, 0x0000 }, { 0x0C85, 0x0000 }, { 0x0C86, 0x0000 }, { 0x0C87, 0x0000 }, 
    { 0x0C88, 0x0000 }, { 0x0C89, 0x0000 }, { 0x0C8A, 0x0000 }, { 0x0C8B, 0x0000 }, 
    { 0x0C8C, 0x0000 }, { 0x0C8D, 0x0000 }, { 0x0C8E, 0x0000 }, { 0x0C8F, 0x0000 }, 
    { 0x0C90, 0x0000 }, { 0x0C91, 0x0000 }, { 0x0C92, 0x0000 }, { 0x0C93, 0x0000 }, 
    { 0x0C94, 0x0000 }, { 0x0C95, 0x0000 }, { 0x0C96, 0x0000 }, { 0x0C97, 0x0000 }, 
    { 0x0C98, 0x0000 }, { 0x0C99, 0x0000 }, { 0x0C9A, 0x0000 }, { 0x0C9B, 0x0000 }, 
    { 0x0C9C, 0x0000 }, { 0x0C9D, 0x0000 }, { 0x0C9E, 0x0000 }, { 0x0C9F, 0x0000 }, 
    { 0x0CA0, 0x0000 }, { 0x0CA1, 0x0000 }, { 0x0CA2, 0x0000 }, { 0x0CA3, 0x0000 }, 
    { 0x0CA4, 0x0000 }, { 0x0CA5, 0x0000 }, { 0x0CA6, 0x0000 }, { 0x0CA7, 0x0000 }, 
    { 0x0CA8, 0x0000 }, { 0x0CA9, 0x0000 }, { 0x0CAA, 0x0000 }, { 0x0CAB, 0x0000 }, 
    { 0x0CAC, 0x0000 }, { 0x0CAD, 0x0000 }, { 0x0CAE, 0x0000 }, { 0x0CAF, 0x0000 }, 
    { 0x0CB0, 0x0000 }, { 0x0CB1, 0x0000 }, { 0x0CB2, 0x0000 }, { 0x0CB3, 0x0000 }, 
    { 0x0CB4, 0x0000 }, { 0x0CB5, 0x0000 }, { 0x0CB6, 0x0000 }, { 0x0CB7, 0x0000 }, 
    { 0x0CB8, 0x0000 }, { 0x0CB9, 0x0000 }, { 0x0CBA, 0x0000 }, { 0x0CBB, 0x0000 }, 
    { 0x0CBC, 0x0000 }, { 0x0CBD, 0x0000 }, { 0x0CBE, 0x0000 }, { 0x0CBF, 0x0000 }, 
    { 0x0CBF, 0x0CD5 }, { 0x0CC1, 0x0000 }, { 0x0CC2, 0x0000 }, { 0x0CC3, 0x0000 }, 
    { 0x0CC4, 0x0000 }, { 0x0CC5, 0x0000 }, { 0x0CC6, 0x0000 }, { 0x0CC6, 0x0CD5 }, 
    { 0x0CC6, 0x0CD6 }, { 0x0CC9, 0x0000 }, { 0x0CC6, 0x0CC2 }, { 0x0CCA, 0x0CD5 }, 
    { 0x0CCC, 0x0000 }, { 0x0CCD, 0x0000 }, { 0x0CCE, 0x0000 }, { 0x0CCF, 0x0000 }, 
    { 0x0CD0, 0x0000 }, { 0x0CD1, 0x0000 }, { 0x0CD2, 0x0000 }, { 0x0CD3, 0x0000 }, 
    { 0x0CD4, 0x0000 }, { 0x0CD5, 0x0000 }, { 0x0CD6, 0x0000 }, { 0x0CD7, 0x0000 }, 
    { 0x0CD8, 0x0000 }, { 0x0CD9, 0x0000 }, { 0x0CDA, 0x0000 }, { 0x0CDB, 0x0000 }, 
    { 0x0CDC, 0x0000 }, { 0x0CDD, 0x0000 }, { 0x0CDE, 0x0000 }, { 0x0CDF, 0x0000 }, 
    { 0x0CE0, 0x0000 }, { 0x0CE1, 0x0000 }, { 0x0CE2, 0x0000 }, { 0x0CE3, 0x0000 }, 
    { 0x0CE4, 0x0000 }, { 0x0CE5, 0x0000 }, { 0x0CE6, 0x0000 }, { 0x0CE7, 0x0000 }, 
    { 0x0CE8, 0x0000 }, { 0x0CE9, 0x0000 }, { 0x0CEA, 0x0000 }, { 0x0CEB, 0x0000 }, 
    { 0x0CEC, 0x0000 }, { 0x0CED, 0x0000 }, { 0x0CEE, 0x0000 }, { 0x0CEF, 0x0000 }, 
    { 0x0CF0, 0x0000 }, { 0x0CF1, 0x0000 }, { 0x0CF2, 0x0000 }, { 0x0CF3, 0x0000 }, 
    { 0x0CF4, 0x0000 }, { 0x0CF5, 0x0000 }, { 0x0CF6, 0x0000 }, { 0x0CF7, 0x0000 }, 
    { 0x0CF8, 0x0000 }, { 0x0CF9, 0x0000 }, { 0x0CFA, 0x0000 }, { 0x0CFB, 0x0000 }, 
    { 0x0CFC, 0x0000 }, { 0x0CFD, 0x0000 }, { 0x0CFE, 0x0000 }, { 0x0CFF, 0x0000 }
  };

  const unsigned char KannadaC80::lb[] = {
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_CM, LB_AL, LB_AL, 
    LB_AL, LB_CM, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_CM, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_CM, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_AL, LB_CM, 
    LB_AL, LB_AL, LB_CM, LB_CM, LB_CM, LB_CM, LB_NU, LB_NU, 
    LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, 
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
    LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM
  };

    const bool KannadaC80::Combining[] = {
        0, 0, 1, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 1, 1, 
        1, 1, 1, 1, 1, 0, 1, 1, 
        1, 0, 1, 1, 1, 1, 0, 0, 
        0, 0, 0, 0, 0, 1, 1, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool KannadaC80::Non_spacing[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 1, 
        0, 0, 0, 0, 0, 0, 1, 0, 
        0, 0, 0, 0, 1, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool KannadaC80::Alphabetic[] = {
        0, 0, 1, 1, 0, 1, 1, 1, 
        1, 1, 1, 1, 1, 0, 1, 1, 
        1, 0, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 0, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 0, 1, 1, 1, 
        1, 1, 0, 0, 0, 0, 1, 1, 
        1, 1, 1, 1, 1, 0, 1, 1, 
        1, 0, 1, 1, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 1, 1, 0, 
        0, 0, 0, 0, 0, 0, 1, 0, 
        1, 1, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool KannadaC80::Diacritic[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool KannadaC80::Identifier_Part[] = {
        0, 0, 1, 1, 0, 1, 1, 1, 
        1, 1, 1, 1, 1, 0, 1, 1, 
        1, 0, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 0, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 0, 1, 1, 1, 
        1, 1, 0, 0, 0, 0, 1, 1, 
        1, 1, 1, 1, 1, 0, 1, 1, 
        1, 0, 1, 1, 1, 1, 0, 0, 
        0, 0, 0, 0, 0, 1, 1, 0, 
        0, 0, 0, 0, 0, 0, 1, 0, 
        1, 1, 0, 0, 0, 0, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

}; // namespace Babylon
 
dload(Babylon::KannadaC80);
