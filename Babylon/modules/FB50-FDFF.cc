/*$Id: FB50-FDFF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Wed,  6 Dec 2000 23:39:48 +0100.
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

  class Arabic_Presentation_FormsAFB50 : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    Arabic_Presentation_FormsAFB50() {
      _first_letter = 0xFB50;
      _last_letter  = 0xFDFF;
      // _version="3.0.1" // Not yet supported!

    }


    ~Arabic_Presentation_FormsAFB50() {
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
      return "Arabic Presentation Forms-A";
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
      return Babylon::Gen_Cat(Arabic_Presentation_FormsAFB50::_cat[uc - _first_letter]);
    }

    Can_Comb_Class comb_class(const UCS4 uc) const {
      if (!is_defined(uc))
        return CC_MAX;
      return Babylon::Can_Comb_Class(0);
    }

    Bidir_Props bidir_props(const UCS4 uc) const {
      if (!is_defined(uc))
        return BIDIR_MAX;
      return Babylon::Bidir_Props(Arabic_Presentation_FormsAFB50::_bidir[uc - _first_letter]);
    }

    Char_Decomp decomp_type(const UCS4 uc) const {
      if (!is_defined(uc))
        return DECOMP_MAX;
      return Babylon::Char_Decomp(Arabic_Presentation_FormsAFB50::_decomp[uc - _first_letter]);
    }

    UTF32_string decompose(const UCS4 uc) const {
      Babylon::UTF32_string us;
      us.resize(2);
      us[0] = Arabic_Presentation_FormsAFB50::_decompStr[uc - _first_letter][0];
      us[1] = Arabic_Presentation_FormsAFB50::_decompStr[uc - _first_letter][1];

      switch (uc) {

      case 0xFC5E:
        us.resize(3);
        us[2] = 0x0651;
        break;

      case 0xFC5F:
        us.resize(3);
        us[2] = 0x0651;
        break;

      case 0xFC60:
        us.resize(3);
        us[2] = 0x0651;
        break;

      case 0xFC61:
        us.resize(3);
        us[2] = 0x0651;
        break;

      case 0xFC62:
        us.resize(3);
        us[2] = 0x0651;
        break;

      case 0xFC63:
        us.resize(3);
        us[2] = 0x0670;
        break;

      case 0xFCF2:
        us.resize(3);
        us[2] = 0x0651;
        break;

      case 0xFCF3:
        us.resize(3);
        us[2] = 0x0651;
        break;

      case 0xFCF4:
        us.resize(3);
        us[2] = 0x0651;
        break;

      case 0xFD50:
        us.resize(3);
        us[2] = 0x0645;
        break;

      case 0xFD51:
        us.resize(3);
        us[2] = 0x062C;
        break;

      case 0xFD52:
        us.resize(3);
        us[2] = 0x062C;
        break;

      case 0xFD53:
        us.resize(3);
        us[2] = 0x0645;
        break;

      case 0xFD54:
        us.resize(3);
        us[2] = 0x0645;
        break;

      case 0xFD55:
        us.resize(3);
        us[2] = 0x062C;
        break;

      case 0xFD56:
        us.resize(3);
        us[2] = 0x062D;
        break;

      case 0xFD57:
        us.resize(3);
        us[2] = 0x062E;
        break;

      case 0xFD58:
        us.resize(3);
        us[2] = 0x062D;
        break;

      case 0xFD59:
        us.resize(3);
        us[2] = 0x062D;
        break;

      case 0xFD5A:
        us.resize(3);
        us[2] = 0x064A;
        break;

      case 0xFD5B:
        us.resize(3);
        us[2] = 0x0649;
        break;

      case 0xFD5C:
        us.resize(3);
        us[2] = 0x062C;
        break;

      case 0xFD5D:
        us.resize(3);
        us[2] = 0x062D;
        break;

      case 0xFD5E:
        us.resize(3);
        us[2] = 0x0649;
        break;

      case 0xFD5F:
        us.resize(3);
        us[2] = 0x062D;
        break;

      case 0xFD60:
        us.resize(3);
        us[2] = 0x062D;
        break;

      case 0xFD61:
        us.resize(3);
        us[2] = 0x062C;
        break;

      case 0xFD62:
        us.resize(3);
        us[2] = 0x0645;
        break;

      case 0xFD63:
        us.resize(3);
        us[2] = 0x0645;
        break;

      case 0xFD64:
        us.resize(3);
        us[2] = 0x062D;
        break;

      case 0xFD65:
        us.resize(3);
        us[2] = 0x062D;
        break;

      case 0xFD66:
        us.resize(3);
        us[2] = 0x0645;
        break;

      case 0xFD67:
        us.resize(3);
        us[2] = 0x0645;
        break;

      case 0xFD68:
        us.resize(3);
        us[2] = 0x0645;
        break;

      case 0xFD69:
        us.resize(3);
        us[2] = 0x064A;
        break;

      case 0xFD6A:
        us.resize(3);
        us[2] = 0x062E;
        break;

      case 0xFD6B:
        us.resize(3);
        us[2] = 0x062E;
        break;

      case 0xFD6C:
        us.resize(3);
        us[2] = 0x0645;
        break;

      case 0xFD6D:
        us.resize(3);
        us[2] = 0x0645;
        break;

      case 0xFD6E:
        us.resize(3);
        us[2] = 0x0649;
        break;

      case 0xFD6F:
        us.resize(3);
        us[2] = 0x0645;
        break;

      case 0xFD70:
        us.resize(3);
        us[2] = 0x0645;
        break;

      case 0xFD71:
        us.resize(3);
        us[2] = 0x062D;
        break;

      case 0xFD72:
        us.resize(3);
        us[2] = 0x062D;
        break;

      case 0xFD73:
        us.resize(3);
        us[2] = 0x0645;
        break;

      case 0xFD74:
        us.resize(3);
        us[2] = 0x064A;
        break;

      case 0xFD75:
        us.resize(3);
        us[2] = 0x0645;
        break;

      case 0xFD76:
        us.resize(3);
        us[2] = 0x0645;
        break;

      case 0xFD77:
        us.resize(3);
        us[2] = 0x0645;
        break;

      case 0xFD78:
        us.resize(3);
        us[2] = 0x0649;
        break;

      case 0xFD79:
        us.resize(3);
        us[2] = 0x0645;
        break;

      case 0xFD7A:
        us.resize(3);
        us[2] = 0x064A;
        break;

      case 0xFD7B:
        us.resize(3);
        us[2] = 0x0649;
        break;

      case 0xFD7C:
        us.resize(3);
        us[2] = 0x0645;
        break;

      case 0xFD7D:
        us.resize(3);
        us[2] = 0x0645;
        break;

      case 0xFD7E:
        us.resize(3);
        us[2] = 0x062D;
        break;

      case 0xFD7F:
        us.resize(3);
        us[2] = 0x0645;
        break;

      case 0xFD80:
        us.resize(3);
        us[2] = 0x0645;
        break;

      case 0xFD81:
        us.resize(3);
        us[2] = 0x064A;
        break;

      case 0xFD82:
        us.resize(3);
        us[2] = 0x0649;
        break;

      case 0xFD83:
        us.resize(3);
        us[2] = 0x062C;
        break;

      case 0xFD84:
        us.resize(3);
        us[2] = 0x062C;
        break;

      case 0xFD85:
        us.resize(3);
        us[2] = 0x0645;
        break;

      case 0xFD86:
        us.resize(3);
        us[2] = 0x0645;
        break;

      case 0xFD87:
        us.resize(3);
        us[2] = 0x062D;
        break;

      case 0xFD88:
        us.resize(3);
        us[2] = 0x062D;
        break;

      case 0xFD89:
        us.resize(3);
        us[2] = 0x062C;
        break;

      case 0xFD8A:
        us.resize(3);
        us[2] = 0x0645;
        break;

      case 0xFD8B:
        us.resize(3);
        us[2] = 0x064A;
        break;

      case 0xFD8C:
        us.resize(3);
        us[2] = 0x062D;
        break;

      case 0xFD8D:
        us.resize(3);
        us[2] = 0x0645;
        break;

      case 0xFD8E:
        us.resize(3);
        us[2] = 0x062C;
        break;

      case 0xFD8F:
        us.resize(3);
        us[2] = 0x0645;
        break;

      case 0xFD92:
        us.resize(3);
        us[2] = 0x062E;
        break;

      case 0xFD93:
        us.resize(3);
        us[2] = 0x062C;
        break;

      case 0xFD94:
        us.resize(3);
        us[2] = 0x0645;
        break;

      case 0xFD95:
        us.resize(3);
        us[2] = 0x0645;
        break;

      case 0xFD96:
        us.resize(3);
        us[2] = 0x0649;
        break;

      case 0xFD97:
        us.resize(3);
        us[2] = 0x0645;
        break;

      case 0xFD98:
        us.resize(3);
        us[2] = 0x0645;
        break;

      case 0xFD99:
        us.resize(3);
        us[2] = 0x0649;
        break;

      case 0xFD9A:
        us.resize(3);
        us[2] = 0x064A;
        break;

      case 0xFD9B:
        us.resize(3);
        us[2] = 0x0649;
        break;

      case 0xFD9C:
        us.resize(3);
        us[2] = 0x0645;
        break;

      case 0xFD9D:
        us.resize(3);
        us[2] = 0x0645;
        break;

      case 0xFD9E:
        us.resize(3);
        us[2] = 0x064A;
        break;

      case 0xFD9F:
        us.resize(3);
        us[2] = 0x064A;
        break;

      case 0xFDA0:
        us.resize(3);
        us[2] = 0x0649;
        break;

      case 0xFDA1:
        us.resize(3);
        us[2] = 0x064A;
        break;

      case 0xFDA2:
        us.resize(3);
        us[2] = 0x0649;
        break;

      case 0xFDA3:
        us.resize(3);
        us[2] = 0x064A;
        break;

      case 0xFDA4:
        us.resize(3);
        us[2] = 0x0649;
        break;

      case 0xFDA5:
        us.resize(3);
        us[2] = 0x064A;
        break;

      case 0xFDA6:
        us.resize(3);
        us[2] = 0x0649;
        break;

      case 0xFDA7:
        us.resize(3);
        us[2] = 0x0649;
        break;

      case 0xFDA8:
        us.resize(3);
        us[2] = 0x0649;
        break;

      case 0xFDA9:
        us.resize(3);
        us[2] = 0x064A;
        break;

      case 0xFDAA:
        us.resize(3);
        us[2] = 0x064A;
        break;

      case 0xFDAB:
        us.resize(3);
        us[2] = 0x064A;
        break;

      case 0xFDAC:
        us.resize(3);
        us[2] = 0x064A;
        break;

      case 0xFDAD:
        us.resize(3);
        us[2] = 0x064A;
        break;

      case 0xFDAE:
        us.resize(3);
        us[2] = 0x064A;
        break;

      case 0xFDAF:
        us.resize(3);
        us[2] = 0x064A;
        break;

      case 0xFDB0:
        us.resize(3);
        us[2] = 0x064A;
        break;

      case 0xFDB1:
        us.resize(3);
        us[2] = 0x064A;
        break;

      case 0xFDB2:
        us.resize(3);
        us[2] = 0x064A;
        break;

      case 0xFDB3:
        us.resize(3);
        us[2] = 0x064A;
        break;

      case 0xFDB4:
        us.resize(3);
        us[2] = 0x062D;
        break;

      case 0xFDB5:
        us.resize(3);
        us[2] = 0x0645;
        break;

      case 0xFDB6:
        us.resize(3);
        us[2] = 0x064A;
        break;

      case 0xFDB7:
        us.resize(3);
        us[2] = 0x064A;
        break;

      case 0xFDB8:
        us.resize(3);
        us[2] = 0x062D;
        break;

      case 0xFDB9:
        us.resize(3);
        us[2] = 0x064A;
        break;

      case 0xFDBA:
        us.resize(3);
        us[2] = 0x0645;
        break;

      case 0xFDBB:
        us.resize(3);
        us[2] = 0x0645;
        break;

      case 0xFDBC:
        us.resize(3);
        us[2] = 0x0645;
        break;

      case 0xFDBD:
        us.resize(3);
        us[2] = 0x062D;
        break;

      case 0xFDBE:
        us.resize(3);
        us[2] = 0x064A;
        break;

      case 0xFDBF:
        us.resize(3);
        us[2] = 0x064A;
        break;

      case 0xFDC0:
        us.resize(3);
        us[2] = 0x064A;
        break;

      case 0xFDC1:
        us.resize(3);
        us[2] = 0x064A;
        break;

      case 0xFDC2:
        us.resize(3);
        us[2] = 0x064A;
        break;

      case 0xFDC3:
        us.resize(3);
        us[2] = 0x0645;
        break;

      case 0xFDC4:
        us.resize(3);
        us[2] = 0x0645;
        break;

      case 0xFDC5:
        us.resize(3);
        us[2] = 0x0645;
        break;

      case 0xFDC6:
        us.resize(3);
        us[2] = 0x064A;
        break;

      case 0xFDC7:
        us.resize(3);
        us[2] = 0x064A;
        break;

      case 0xFDF0:
        us.resize(3);
        us[2] = 0x06D2;
        break;

      case 0xFDF1:
        us.resize(3);
        us[2] = 0x06D2;
        break;

      case 0xFDF2:
        us.resize(4);
        us[2] = 0x0644;
        us[3] = 0x0647;
        break;

      case 0xFDF3:
        us.resize(4);
        us[2] = 0x0628;
        us[3] = 0x0631;
        break;

      case 0xFDF4:
        us.resize(4);
        us[2] = 0x0645;
        us[3] = 0x062F;
        break;

      case 0xFDF5:
        us.resize(4);
        us[2] = 0x0639;
        us[3] = 0x0645;
        break;

      case 0xFDF6:
        us.resize(4);
        us[2] = 0x0648;
        us[3] = 0x0644;
        break;

      case 0xFDF7:
        us.resize(4);
        us[2] = 0x064A;
        us[3] = 0x0647;
        break;

      case 0xFDF8:
        us.resize(4);
        us[2] = 0x0644;
        us[3] = 0x0645;
        break;

      case 0xFDF9:
        us.resize(3);
        us[2] = 0x0649;
        break;

      case 0xFDFA:
        us.resize(18);
        us[2] = 0x0649;
        us[3] = 0x0020;
        us[4] = 0x0627;
        us[5] = 0x0644;
        us[6] = 0x0644;
        us[7] = 0x0647;
        us[8] = 0x0020;
        us[9] = 0x0639;
        us[10] = 0x0644;
        us[11] = 0x064A;
        us[12] = 0x0647;
        us[13] = 0x0020;
        us[14] = 0x0648;
        us[15] = 0x0633;
        us[16] = 0x0644;
        us[17] = 0x0645;
        break;

      case 0xFDFB:
        us.resize(8);
        us[2] = 0x0020;
        us[3] = 0x062C;
        us[4] = 0x0644;
        us[5] = 0x0627;
        us[6] = 0x0644;
        us[7] = 0x0647;
        break;
      }
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
      return Babylon::Line_Break(Arabic_Presentation_FormsAFB50::_lb[uc - _first_letter]);
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
      return Arabic_Presentation_FormsAFB50::_Paired_Punctuation[uc - _first_letter];
    }

    bool is_Left_of_Pair(const UCS4 uc) const {
      return Arabic_Presentation_FormsAFB50::_Left_of_Pair[uc - _first_letter];
    }

    bool is_Combining(const UCS4 uc) const {
      return 0;
    }

    bool is_Non_spacing(const UCS4 uc) const {
      return 0;
    }

    bool is_Composite(const UCS4 uc) const {
      return Arabic_Presentation_FormsAFB50::_Composite[uc - _first_letter];
    }

    bool is_Hex_Digit(const UCS4 uc) const {
      return 0;
    }

    bool is_Alphabetic(const UCS4 uc) const {
      return Arabic_Presentation_FormsAFB50::_Alphabetic[uc - _first_letter];
    }

    bool is_Diacritic(const UCS4 uc) const {
      return 0;
    }

    bool is_Extender(const UCS4 uc) const {
      return 0;
    }

    bool is_Identifier_Part(const UCS4 uc) const {
      return Arabic_Presentation_FormsAFB50::_Identifier_Part[uc - _first_letter];
    }

    bool is_Ignorable_Control(const UCS4 uc) const {
      return 0;
    }

    bool is_Bidi_Hebrew_Right_to_Left(const UCS4 uc) const {
      return 0;
    }

    bool is_Bidi_Arabic_Right_to_Left(const UCS4 uc) const {
      return Arabic_Presentation_FormsAFB50::_Bidi_Arabic_Right_to_Left[uc - _first_letter];
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
    Arabic_Presentation_FormsAFB50(const Arabic_Presentation_FormsAFB50 &) {}

    Babylon::UCS4 _first_letter;
    Babylon::UCS4 _last_letter;
    static const bool _is_defined[688];
    static const unsigned char _cat[688];
    static const unsigned char _bidir[688];
    static const unsigned char _decomp[688];
    static const UCS2 _decompStr[688][2];
    static const unsigned char _lb[688];
    static const bool _Paired_Punctuation[688];
    static const bool _Left_of_Pair[688];
    static const bool _Composite[688];
    static const bool _Alphabetic[688];
    static const bool _Identifier_Part[688];
    static const bool _Bidi_Arabic_Right_to_Left[688];

  }; // class Arabic_Presentation_FormsAFB50

  const bool Arabic_Presentation_FormsAFB50::_is_defined[] = {
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
    1, 1, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 1, 1, 1, 1, 1, 
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
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
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
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 0, 0, 0, 0
  };

  const unsigned char Arabic_Presentation_FormsAFB50::_cat[] = {
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Ps, CAT_Pe, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo
  };

  const unsigned char Arabic_Presentation_FormsAFB50::_bidir[] = {
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_ON, BIDIR_ON, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, 
    BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL, BIDIR_AL
  };

  const unsigned char Arabic_Presentation_FormsAFB50::_decomp[] = {
    DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, 
    DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, 
    DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, 
    DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, 
    DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, 
    DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, 
    DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, 
    DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, 
    DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, 
    DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, 
    DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, 
    DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, 
    DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, 
    DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_FINAL, 
    DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_MEDIAL, 
    DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, 
    DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_FINAL, 
    DECOMP_INITIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_MEDIAL, 
    DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
    DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
    DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
    DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
    DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
    DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
    DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
    DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
    DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
    DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
    DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
    DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
    DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, 
    DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, 
    DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, 
    DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, 
    DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, 
    DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, 
    DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_INITIAL, 
    DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, 
    DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, 
    DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, 
    DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, 
    DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, 
    DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, 
    DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, 
    DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, 
    DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_MEDIAL, 
    DECOMP_MEDIAL, DECOMP_MEDIAL, DECOMP_MEDIAL, DECOMP_MEDIAL, DECOMP_MEDIAL, DECOMP_MEDIAL, DECOMP_MEDIAL, DECOMP_MEDIAL, 
    DECOMP_MEDIAL, DECOMP_MEDIAL, DECOMP_MEDIAL, DECOMP_MEDIAL, DECOMP_MEDIAL, DECOMP_MEDIAL, DECOMP_MEDIAL, DECOMP_MEDIAL, 
    DECOMP_MEDIAL, DECOMP_MEDIAL, DECOMP_MEDIAL, DECOMP_MEDIAL, DECOMP_MEDIAL, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
    DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
    DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
    DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
    DECOMP_ISOLATED, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, 
    DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, 
    DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, 
    DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, 
    DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_MEDIAL, DECOMP_MEDIAL, DECOMP_MEDIAL, DECOMP_MEDIAL, 
    DECOMP_MEDIAL, DECOMP_MEDIAL, DECOMP_MEDIAL, DECOMP_MEDIAL, DECOMP_FINAL, DECOMP_ISOLATED, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_INITIAL, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, 
    DECOMP_FINAL, DECOMP_INITIAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_FINAL, DECOMP_FINAL, 
    DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_FINAL, DECOMP_FINAL, 
    DECOMP_INITIAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_FINAL, DECOMP_FINAL, 
    DECOMP_INITIAL, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_INITIAL, 
    DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_FINAL, DECOMP_FINAL, 
    DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_FINAL, 
    DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_FINAL, DECOMP_FINAL, 
    DECOMP_INITIAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_FINAL, DECOMP_FINAL, 
    DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, 
    DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, 
    DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_FINAL, DECOMP_FINAL, 
    DECOMP_INITIAL, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, 
    DECOMP_FINAL, DECOMP_FINAL, DECOMP_FINAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_INITIAL, DECOMP_FINAL, DECOMP_FINAL, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, 
    DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_ISOLATED, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP
  };

  const UCS2 Arabic_Presentation_FormsAFB50::_decompStr[][2] = {
    { 0x0671, 0x0000 }, { 0x0671, 0x0000 }, { 0x067B, 0x0000 }, { 0x067B, 0x0000 }, 
    { 0x067B, 0x0000 }, { 0x067B, 0x0000 }, { 0x067E, 0x0000 }, { 0x067E, 0x0000 }, 
    { 0x067E, 0x0000 }, { 0x067E, 0x0000 }, { 0x0680, 0x0000 }, { 0x0680, 0x0000 }, 
    { 0x0680, 0x0000 }, { 0x0680, 0x0000 }, { 0x067A, 0x0000 }, { 0x067A, 0x0000 }, 
    { 0x067A, 0x0000 }, { 0x067A, 0x0000 }, { 0x067F, 0x0000 }, { 0x067F, 0x0000 }, 
    { 0x067F, 0x0000 }, { 0x067F, 0x0000 }, { 0x0679, 0x0000 }, { 0x0679, 0x0000 }, 
    { 0x0679, 0x0000 }, { 0x0679, 0x0000 }, { 0x06A4, 0x0000 }, { 0x06A4, 0x0000 }, 
    { 0x06A4, 0x0000 }, { 0x06A4, 0x0000 }, { 0x06A6, 0x0000 }, { 0x06A6, 0x0000 }, 
    { 0x06A6, 0x0000 }, { 0x06A6, 0x0000 }, { 0x0684, 0x0000 }, { 0x0684, 0x0000 }, 
    { 0x0684, 0x0000 }, { 0x0684, 0x0000 }, { 0x0683, 0x0000 }, { 0x0683, 0x0000 }, 
    { 0x0683, 0x0000 }, { 0x0683, 0x0000 }, { 0x0686, 0x0000 }, { 0x0686, 0x0000 }, 
    { 0x0686, 0x0000 }, { 0x0686, 0x0000 }, { 0x0687, 0x0000 }, { 0x0687, 0x0000 }, 
    { 0x0687, 0x0000 }, { 0x0687, 0x0000 }, { 0x068D, 0x0000 }, { 0x068D, 0x0000 }, 
    { 0x068C, 0x0000 }, { 0x068C, 0x0000 }, { 0x068E, 0x0000 }, { 0x068E, 0x0000 }, 
    { 0x0688, 0x0000 }, { 0x0688, 0x0000 }, { 0x0698, 0x0000 }, { 0x0698, 0x0000 }, 
    { 0x0691, 0x0000 }, { 0x0691, 0x0000 }, { 0x06A9, 0x0000 }, { 0x06A9, 0x0000 }, 
    { 0x06A9, 0x0000 }, { 0x06A9, 0x0000 }, { 0x06AF, 0x0000 }, { 0x06AF, 0x0000 }, 
    { 0x06AF, 0x0000 }, { 0x06AF, 0x0000 }, { 0x06B3, 0x0000 }, { 0x06B3, 0x0000 }, 
    { 0x06B3, 0x0000 }, { 0x06B3, 0x0000 }, { 0x06B1, 0x0000 }, { 0x06B1, 0x0000 }, 
    { 0x06B1, 0x0000 }, { 0x06B1, 0x0000 }, { 0x06BA, 0x0000 }, { 0x06BA, 0x0000 }, 
    { 0x06BB, 0x0000 }, { 0x06BB, 0x0000 }, { 0x06BB, 0x0000 }, { 0x06BB, 0x0000 }, 
    { 0x06C0, 0x0000 }, { 0x06C0, 0x0000 }, { 0x06C1, 0x0000 }, { 0x06C1, 0x0000 }, 
    { 0x06C1, 0x0000 }, { 0x06C1, 0x0000 }, { 0x06BE, 0x0000 }, { 0x06BE, 0x0000 }, 
    { 0x06BE, 0x0000 }, { 0x06BE, 0x0000 }, { 0x06D2, 0x0000 }, { 0x06D2, 0x0000 }, 
    { 0x06D3, 0x0000 }, { 0x06D3, 0x0000 }, { 0xFBB2, 0x0000 }, { 0xFBB3, 0x0000 }, 
    { 0xFBB4, 0x0000 }, { 0xFBB5, 0x0000 }, { 0xFBB6, 0x0000 }, { 0xFBB7, 0x0000 }, 
    { 0xFBB8, 0x0000 }, { 0xFBB9, 0x0000 }, { 0xFBBA, 0x0000 }, { 0xFBBB, 0x0000 }, 
    { 0xFBBC, 0x0000 }, { 0xFBBD, 0x0000 }, { 0xFBBE, 0x0000 }, { 0xFBBF, 0x0000 }, 
    { 0xFBC0, 0x0000 }, { 0xFBC1, 0x0000 }, { 0xFBC2, 0x0000 }, { 0xFBC3, 0x0000 }, 
    { 0xFBC4, 0x0000 }, { 0xFBC5, 0x0000 }, { 0xFBC6, 0x0000 }, { 0xFBC7, 0x0000 }, 
    { 0xFBC8, 0x0000 }, { 0xFBC9, 0x0000 }, { 0xFBCA, 0x0000 }, { 0xFBCB, 0x0000 }, 
    { 0xFBCC, 0x0000 }, { 0xFBCD, 0x0000 }, { 0xFBCE, 0x0000 }, { 0xFBCF, 0x0000 }, 
    { 0xFBD0, 0x0000 }, { 0xFBD1, 0x0000 }, { 0xFBD2, 0x0000 }, { 0x06AD, 0x0000 }, 
    { 0x06AD, 0x0000 }, { 0x06AD, 0x0000 }, { 0x06AD, 0x0000 }, { 0x06C7, 0x0000 }, 
    { 0x06C7, 0x0000 }, { 0x06C6, 0x0000 }, { 0x06C6, 0x0000 }, { 0x06C8, 0x0000 }, 
    { 0x06C8, 0x0000 }, { 0x0677, 0x0000 }, { 0x06CB, 0x0000 }, { 0x06CB, 0x0000 }, 
    { 0x06C5, 0x0000 }, { 0x06C5, 0x0000 }, { 0x06C9, 0x0000 }, { 0x06C9, 0x0000 }, 
    { 0x06D0, 0x0000 }, { 0x06D0, 0x0000 }, { 0x06D0, 0x0000 }, { 0x06D0, 0x0000 }, 
    { 0x0649, 0x0000 }, { 0x0649, 0x0000 }, { 0x0626, 0x0627 }, { 0x0626, 0x0627 }, 
    { 0x0626, 0x06D5 }, { 0x0626, 0x06D5 }, { 0x0626, 0x0648 }, { 0x0626, 0x0648 }, 
    { 0x0626, 0x06C7 }, { 0x0626, 0x06C7 }, { 0x0626, 0x06C6 }, { 0x0626, 0x06C6 }, 
    { 0x0626, 0x06C8 }, { 0x0626, 0x06C8 }, { 0x0626, 0x06D0 }, { 0x0626, 0x06D0 }, 
    { 0x0626, 0x06D0 }, { 0x0626, 0x0649 }, { 0x0626, 0x0649 }, { 0x0626, 0x0649 }, 
    { 0x06CC, 0x0000 }, { 0x06CC, 0x0000 }, { 0x06CC, 0x0000 }, { 0x06CC, 0x0000 }, 
    { 0x0626, 0x062C }, { 0x0626, 0x062D }, { 0x0626, 0x0645 }, { 0x0626, 0x0649 }, 
    { 0x0626, 0x064A }, { 0x0628, 0x062C }, { 0x0628, 0x062D }, { 0x0628, 0x062E }, 
    { 0x0628, 0x0645 }, { 0x0628, 0x0649 }, { 0x0628, 0x064A }, { 0x062A, 0x062C }, 
    { 0x062A, 0x062D }, { 0x062A, 0x062E }, { 0x062A, 0x0645 }, { 0x062A, 0x0649 }, 
    { 0x062A, 0x064A }, { 0x062B, 0x062C }, { 0x062B, 0x0645 }, { 0x062B, 0x0649 }, 
    { 0x062B, 0x064A }, { 0x062C, 0x062D }, { 0x062C, 0x0645 }, { 0x062D, 0x062C }, 
    { 0x062D, 0x0645 }, { 0x062E, 0x062C }, { 0x062E, 0x062D }, { 0x062E, 0x0645 }, 
    { 0x0633, 0x062C }, { 0x0633, 0x062D }, { 0x0633, 0x062E }, { 0x0633, 0x0645 }, 
    { 0x0635, 0x062D }, { 0x0635, 0x0645 }, { 0x0636, 0x062C }, { 0x0636, 0x062D }, 
    { 0x0636, 0x062E }, { 0x0636, 0x0645 }, { 0x0637, 0x062D }, { 0x0637, 0x0645 }, 
    { 0x0638, 0x0645 }, { 0x0639, 0x062C }, { 0x0639, 0x0645 }, { 0x063A, 0x062C }, 
    { 0x063A, 0x0645 }, { 0x0641, 0x062C }, { 0x0641, 0x062D }, { 0x0641, 0x062E }, 
    { 0x0641, 0x0645 }, { 0x0641, 0x0649 }, { 0x0641, 0x064A }, { 0x0642, 0x062D }, 
    { 0x0642, 0x0645 }, { 0x0642, 0x0649 }, { 0x0642, 0x064A }, { 0x0643, 0x0627 }, 
    { 0x0643, 0x062C }, { 0x0643, 0x062D }, { 0x0643, 0x062E }, { 0x0643, 0x0644 }, 
    { 0x0643, 0x0645 }, { 0x0643, 0x0649 }, { 0x0643, 0x064A }, { 0x0644, 0x062C }, 
    { 0x0644, 0x062D }, { 0x0644, 0x062E }, { 0x0644, 0x0645 }, { 0x0644, 0x0649 }, 
    { 0x0644, 0x064A }, { 0x0645, 0x062C }, { 0x0645, 0x062D }, { 0x0645, 0x062E }, 
    { 0x0645, 0x0645 }, { 0x0645, 0x0649 }, { 0x0645, 0x064A }, { 0x0646, 0x062C }, 
    { 0x0646, 0x062D }, { 0x0646, 0x062E }, { 0x0646, 0x0645 }, { 0x0646, 0x0649 }, 
    { 0x0646, 0x064A }, { 0x0647, 0x062C }, { 0x0647, 0x0645 }, { 0x0647, 0x0649 }, 
    { 0x0647, 0x064A }, { 0x064A, 0x062C }, { 0x064A, 0x062D }, { 0x064A, 0x062E }, 
    { 0x064A, 0x0645 }, { 0x064A, 0x0649 }, { 0x064A, 0x064A }, { 0x0630, 0x0670 }, 
    { 0x0631, 0x0670 }, { 0x0649, 0x0670 }, { 0x0020, 0x064C }, { 0x0020, 0x064D }, 
    { 0x0020, 0x064E }, { 0x0020, 0x064F }, { 0x0020, 0x0650 }, { 0x0020, 0x0651 }, 
    { 0x0626, 0x0631 }, { 0x0626, 0x0632 }, { 0x0626, 0x0645 }, { 0x0626, 0x0646 }, 
    { 0x0626, 0x0649 }, { 0x0626, 0x064A }, { 0x0628, 0x0631 }, { 0x0628, 0x0632 }, 
    { 0x0628, 0x0645 }, { 0x0628, 0x0646 }, { 0x0628, 0x0649 }, { 0x0628, 0x064A }, 
    { 0x062A, 0x0631 }, { 0x062A, 0x0632 }, { 0x062A, 0x0645 }, { 0x062A, 0x0646 }, 
    { 0x062A, 0x0649 }, { 0x062A, 0x064A }, { 0x062B, 0x0631 }, { 0x062B, 0x0632 }, 
    { 0x062B, 0x0645 }, { 0x062B, 0x0646 }, { 0x062B, 0x0649 }, { 0x062B, 0x064A }, 
    { 0x0641, 0x0649 }, { 0x0641, 0x064A }, { 0x0642, 0x0649 }, { 0x0642, 0x064A }, 
    { 0x0643, 0x0627 }, { 0x0643, 0x0644 }, { 0x0643, 0x0645 }, { 0x0643, 0x0649 }, 
    { 0x0643, 0x064A }, { 0x0644, 0x0645 }, { 0x0644, 0x0649 }, { 0x0644, 0x064A }, 
    { 0x0645, 0x0627 }, { 0x0645, 0x0645 }, { 0x0646, 0x0631 }, { 0x0646, 0x0632 }, 
    { 0x0646, 0x0645 }, { 0x0646, 0x0646 }, { 0x0646, 0x0649 }, { 0x0646, 0x064A }, 
    { 0x0649, 0x0670 }, { 0x064A, 0x0631 }, { 0x064A, 0x0632 }, { 0x064A, 0x0645 }, 
    { 0x064A, 0x0646 }, { 0x064A, 0x0649 }, { 0x064A, 0x064A }, { 0x0626, 0x062C }, 
    { 0x0626, 0x062D }, { 0x0626, 0x062E }, { 0x0626, 0x0645 }, { 0x0626, 0x0647 }, 
    { 0x0628, 0x062C }, { 0x0628, 0x062D }, { 0x0628, 0x062E }, { 0x0628, 0x0645 }, 
    { 0x0628, 0x0647 }, { 0x062A, 0x062C }, { 0x062A, 0x062D }, { 0x062A, 0x062E }, 
    { 0x062A, 0x0645 }, { 0x062A, 0x0647 }, { 0x062B, 0x0645 }, { 0x062C, 0x062D }, 
    { 0x062C, 0x0645 }, { 0x062D, 0x062C }, { 0x062D, 0x0645 }, { 0x062E, 0x062C }, 
    { 0x062E, 0x0645 }, { 0x0633, 0x062C }, { 0x0633, 0x062D }, { 0x0633, 0x062E }, 
    { 0x0633, 0x0645 }, { 0x0635, 0x062D }, { 0x0635, 0x062E }, { 0x0635, 0x0645 }, 
    { 0x0636, 0x062C }, { 0x0636, 0x062D }, { 0x0636, 0x062E }, { 0x0636, 0x0645 }, 
    { 0x0637, 0x062D }, { 0x0638, 0x0645 }, { 0x0639, 0x062C }, { 0x0639, 0x0645 }, 
    { 0x063A, 0x062C }, { 0x063A, 0x0645 }, { 0x0641, 0x062C }, { 0x0641, 0x062D }, 
    { 0x0641, 0x062E }, { 0x0641, 0x0645 }, { 0x0642, 0x062D }, { 0x0642, 0x0645 }, 
    { 0x0643, 0x062C }, { 0x0643, 0x062D }, { 0x0643, 0x062E }, { 0x0643, 0x0644 }, 
    { 0x0643, 0x0645 }, { 0x0644, 0x062C }, { 0x0644, 0x062D }, { 0x0644, 0x062E }, 
    { 0x0644, 0x0645 }, { 0x0644, 0x0647 }, { 0x0645, 0x062C }, { 0x0645, 0x062D }, 
    { 0x0645, 0x062E }, { 0x0645, 0x0645 }, { 0x0646, 0x062C }, { 0x0646, 0x062D }, 
    { 0x0646, 0x062E }, { 0x0646, 0x0645 }, { 0x0646, 0x0647 }, { 0x0647, 0x062C }, 
    { 0x0647, 0x0645 }, { 0x0647, 0x0670 }, { 0x064A, 0x062C }, { 0x064A, 0x062D }, 
    { 0x064A, 0x062E }, { 0x064A, 0x0645 }, { 0x064A, 0x0647 }, { 0x0626, 0x0645 }, 
    { 0x0626, 0x0647 }, { 0x0628, 0x0645 }, { 0x0628, 0x0647 }, { 0x062A, 0x0645 }, 
    { 0x062A, 0x0647 }, { 0x062B, 0x0645 }, { 0x062B, 0x0647 }, { 0x0633, 0x0645 }, 
    { 0x0633, 0x0647 }, { 0x0634, 0x0645 }, { 0x0634, 0x0647 }, { 0x0643, 0x0644 }, 
    { 0x0643, 0x0645 }, { 0x0644, 0x0645 }, { 0x0646, 0x0645 }, { 0x0646, 0x0647 }, 
    { 0x064A, 0x0645 }, { 0x064A, 0x0647 }, { 0x0640, 0x064E }, { 0x0640, 0x064F }, 
    { 0x0640, 0x0650 }, { 0x0637, 0x0649 }, { 0x0637, 0x064A }, { 0x0639, 0x0649 }, 
    { 0x0639, 0x064A }, { 0x063A, 0x0649 }, { 0x063A, 0x064A }, { 0x0633, 0x0649 }, 
    { 0x0633, 0x064A }, { 0x0634, 0x0649 }, { 0x0634, 0x064A }, { 0x062D, 0x0649 }, 
    { 0x062D, 0x064A }, { 0x062C, 0x0649 }, { 0x062C, 0x064A }, { 0x062E, 0x0649 }, 
    { 0x062E, 0x064A }, { 0x0635, 0x0649 }, { 0x0635, 0x064A }, { 0x0636, 0x0649 }, 
    { 0x0636, 0x064A }, { 0x0634, 0x062C }, { 0x0634, 0x062D }, { 0x0634, 0x062E }, 
    { 0x0634, 0x0645 }, { 0x0634, 0x0631 }, { 0x0633, 0x0631 }, { 0x0635, 0x0631 }, 
    { 0x0636, 0x0631 }, { 0x0637, 0x0649 }, { 0x0637, 0x064A }, { 0x0639, 0x0649 }, 
    { 0x0639, 0x064A }, { 0x063A, 0x0649 }, { 0x063A, 0x064A }, { 0x0633, 0x0649 }, 
    { 0x0633, 0x064A }, { 0x0634, 0x0649 }, { 0x0634, 0x064A }, { 0x062D, 0x0649 }, 
    { 0x062D, 0x064A }, { 0x062C, 0x0649 }, { 0x062C, 0x064A }, { 0x062E, 0x0649 }, 
    { 0x062E, 0x064A }, { 0x0635, 0x0649 }, { 0x0635, 0x064A }, { 0x0636, 0x0649 }, 
    { 0x0636, 0x064A }, { 0x0634, 0x062C }, { 0x0634, 0x062D }, { 0x0634, 0x062E }, 
    { 0x0634, 0x0645 }, { 0x0634, 0x0631 }, { 0x0633, 0x0631 }, { 0x0635, 0x0631 }, 
    { 0x0636, 0x0631 }, { 0x0634, 0x062C }, { 0x0634, 0x062D }, { 0x0634, 0x062E }, 
    { 0x0634, 0x0645 }, { 0x0633, 0x0647 }, { 0x0634, 0x0647 }, { 0x0637, 0x0645 }, 
    { 0x0633, 0x062C }, { 0x0633, 0x062D }, { 0x0633, 0x062E }, { 0x0634, 0x062C }, 
    { 0x0634, 0x062D }, { 0x0634, 0x062E }, { 0x0637, 0x0645 }, { 0x0638, 0x0645 }, 
    { 0x0627, 0x064B }, { 0x0627, 0x064B }, { 0xFD3E, 0x0000 }, { 0xFD3F, 0x0000 }, 
    { 0xFD40, 0x0000 }, { 0xFD41, 0x0000 }, { 0xFD42, 0x0000 }, { 0xFD43, 0x0000 }, 
    { 0xFD44, 0x0000 }, { 0xFD45, 0x0000 }, { 0xFD46, 0x0000 }, { 0xFD47, 0x0000 }, 
    { 0xFD48, 0x0000 }, { 0xFD49, 0x0000 }, { 0xFD4A, 0x0000 }, { 0xFD4B, 0x0000 }, 
    { 0xFD4C, 0x0000 }, { 0xFD4D, 0x0000 }, { 0xFD4E, 0x0000 }, { 0xFD4F, 0x0000 }, 
    { 0x062A, 0x062C }, { 0x062A, 0x062D }, { 0x062A, 0x062D }, { 0x062A, 0x062D }, 
    { 0x062A, 0x062E }, { 0x062A, 0x0645 }, { 0x062A, 0x0645 }, { 0x062A, 0x0645 }, 
    { 0x062C, 0x0645 }, { 0x062C, 0x0645 }, { 0x062D, 0x0645 }, { 0x062D, 0x0645 }, 
    { 0x0633, 0x062D }, { 0x0633, 0x062C }, { 0x0633, 0x062C }, { 0x0633, 0x0645 }, 
    { 0x0633, 0x0645 }, { 0x0633, 0x0645 }, { 0x0633, 0x0645 }, { 0x0633, 0x0645 }, 
    { 0x0635, 0x062D }, { 0x0635, 0x062D }, { 0x0635, 0x0645 }, { 0x0634, 0x062D }, 
    { 0x0634, 0x062D }, { 0x0634, 0x062C }, { 0x0634, 0x0645 }, { 0x0634, 0x0645 }, 
    { 0x0634, 0x0645 }, { 0x0634, 0x0645 }, { 0x0636, 0x062D }, { 0x0636, 0x062E }, 
    { 0x0636, 0x062E }, { 0x0637, 0x0645 }, { 0x0637, 0x0645 }, { 0x0637, 0x0645 }, 
    { 0x0637, 0x0645 }, { 0x0639, 0x062C }, { 0x0639, 0x0645 }, { 0x0639, 0x0645 }, 
    { 0x0639, 0x0645 }, { 0x063A, 0x0645 }, { 0x063A, 0x0645 }, { 0x063A, 0x0645 }, 
    { 0x0641, 0x062E }, { 0x0641, 0x062E }, { 0x0642, 0x0645 }, { 0x0642, 0x0645 }, 
    { 0x0644, 0x062D }, { 0x0644, 0x062D }, { 0x0644, 0x062D }, { 0x0644, 0x062C }, 
    { 0x0644, 0x062C }, { 0x0644, 0x062E }, { 0x0644, 0x062E }, { 0x0644, 0x0645 }, 
    { 0x0644, 0x0645 }, { 0x0645, 0x062D }, { 0x0645, 0x062D }, { 0x0645, 0x062D }, 
    { 0x0645, 0x062C }, { 0x0645, 0x062C }, { 0x0645, 0x062E }, { 0x0645, 0x062E }, 
    { 0xFD90, 0x0000 }, { 0xFD91, 0x0000 }, { 0x0645, 0x062C }, { 0x0647, 0x0645 }, 
    { 0x0647, 0x0645 }, { 0x0646, 0x062D }, { 0x0646, 0x062D }, { 0x0646, 0x062C }, 
    { 0x0646, 0x062C }, { 0x0646, 0x062C }, { 0x0646, 0x0645 }, { 0x0646, 0x0645 }, 
    { 0x064A, 0x0645 }, { 0x064A, 0x0645 }, { 0x0628, 0x062E }, { 0x062A, 0x062C }, 
    { 0x062A, 0x062C }, { 0x062A, 0x062E }, { 0x062A, 0x062E }, { 0x062A, 0x0645 }, 
    { 0x062A, 0x0645 }, { 0x062C, 0x0645 }, { 0x062C, 0x062D }, { 0x062C, 0x0645 }, 
    { 0x0633, 0x062E }, { 0x0635, 0x062D }, { 0x0634, 0x062D }, { 0x0636, 0x062D }, 
    { 0x0644, 0x062C }, { 0x0644, 0x0645 }, { 0x064A, 0x062D }, { 0x064A, 0x062C }, 
    { 0x064A, 0x0645 }, { 0x0645, 0x0645 }, { 0x0642, 0x0645 }, { 0x0646, 0x062D }, 
    { 0x0642, 0x0645 }, { 0x0644, 0x062D }, { 0x0639, 0x0645 }, { 0x0643, 0x0645 }, 
    { 0x0646, 0x062C }, { 0x0645, 0x062E }, { 0x0644, 0x062C }, { 0x0643, 0x0645 }, 
    { 0x0644, 0x062C }, { 0x0646, 0x062C }, { 0x062C, 0x062D }, { 0x062D, 0x062C }, 
    { 0x0645, 0x062C }, { 0x0641, 0x0645 }, { 0x0628, 0x062D }, { 0x0643, 0x0645 }, 
    { 0x0639, 0x062C }, { 0x0635, 0x0645 }, { 0x0633, 0x062E }, { 0x0646, 0x062C }, 
    { 0xFDC8, 0x0000 }, { 0xFDC9, 0x0000 }, { 0xFDCA, 0x0000 }, { 0xFDCB, 0x0000 }, 
    { 0xFDCC, 0x0000 }, { 0xFDCD, 0x0000 }, { 0xFDCE, 0x0000 }, { 0xFDCF, 0x0000 }, 
    { 0xFDD0, 0x0000 }, { 0xFDD1, 0x0000 }, { 0xFDD2, 0x0000 }, { 0xFDD3, 0x0000 }, 
    { 0xFDD4, 0x0000 }, { 0xFDD5, 0x0000 }, { 0xFDD6, 0x0000 }, { 0xFDD7, 0x0000 }, 
    { 0xFDD8, 0x0000 }, { 0xFDD9, 0x0000 }, { 0xFDDA, 0x0000 }, { 0xFDDB, 0x0000 }, 
    { 0xFDDC, 0x0000 }, { 0xFDDD, 0x0000 }, { 0xFDDE, 0x0000 }, { 0xFDDF, 0x0000 }, 
    { 0xFDE0, 0x0000 }, { 0xFDE1, 0x0000 }, { 0xFDE2, 0x0000 }, { 0xFDE3, 0x0000 }, 
    { 0xFDE4, 0x0000 }, { 0xFDE5, 0x0000 }, { 0xFDE6, 0x0000 }, { 0xFDE7, 0x0000 }, 
    { 0xFDE8, 0x0000 }, { 0xFDE9, 0x0000 }, { 0xFDEA, 0x0000 }, { 0xFDEB, 0x0000 }, 
    { 0xFDEC, 0x0000 }, { 0xFDED, 0x0000 }, { 0xFDEE, 0x0000 }, { 0xFDEF, 0x0000 }, 
    { 0x0635, 0x0644 }, { 0x0642, 0x0644 }, { 0x0627, 0x0644 }, { 0x0627, 0x0643 }, 
    { 0x0645, 0x062D }, { 0x0635, 0x0644 }, { 0x0631, 0x0633 }, { 0x0639, 0x0644 }, 
    { 0x0648, 0x0633 }, { 0x0635, 0x0644 }, { 0x0635, 0x0644 }, { 0x062C, 0x0644 }, 
    { 0xFDFC, 0x0000 }, { 0xFDFD, 0x0000 }, { 0xFDFE, 0x0000 }, { 0xFDFF, 0x0000 }
  };

  const unsigned char Arabic_Presentation_FormsAFB50::_lb[] = {
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
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_OP, LB_CL, 
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

    const bool Arabic_Presentation_FormsAFB50::_Paired_Punctuation[] = {
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
        0, 0, 0, 0, 0, 0, 1, 1, 
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

    const bool Arabic_Presentation_FormsAFB50::_Left_of_Pair[] = {
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
        0, 0, 0, 0, 0, 0, 1, 0, 
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

    const bool Arabic_Presentation_FormsAFB50::_Composite[] = {
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
        0, 0, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 0, 0, 0, 0, 
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
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
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
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 0, 0, 0, 0
    };

    const bool Arabic_Presentation_FormsAFB50::_Alphabetic[] = {
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
        1, 1, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 1, 1, 1, 1, 1, 
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
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 0, 0, 0, 0
    };

    const bool Arabic_Presentation_FormsAFB50::_Identifier_Part[] = {
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
        1, 1, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 1, 1, 1, 1, 1, 
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
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 0, 0, 0, 0
    };

    const bool Arabic_Presentation_FormsAFB50::_Bidi_Arabic_Right_to_Left[] = {
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
        1, 1, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 1, 1, 1, 1, 1, 
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
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 0, 0, 0, 0
    };

}; // namespace Babylon

dload(Babylon::Arabic_Presentation_FormsAFB50);
