/*$Id: FF00-FFEF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Wed,  6 Dec 2000 23:40:10 +0100.
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

  class Halfwidth_and_Fullwidth_FormsFF00 : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    Halfwidth_and_Fullwidth_FormsFF00() {
      _first_letter = 0xFF00;
      _last_letter  = 0xFFEF;
      // _version="3.0.1" // Not yet supported!

    }


    ~Halfwidth_and_Fullwidth_FormsFF00() {
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
      return "Halfwidth and Fullwidth Forms";
    }

    bool is_defined(const UCS4 uc) const {
      return (_is_defined[uc - _first_letter]);
    }

    UCS4 uppercase(const UCS4 uc) const {
      return Halfwidth_and_Fullwidth_FormsFF00::_upper[uc - _first_letter];
    }

    bool is_Uppercase(const UCS4 uc) const {
      return category(uc) == CAT_Lu;
    }

    UCS4 lowercase(const UCS4 uc) const {
      return Halfwidth_and_Fullwidth_FormsFF00::_lower[uc - _first_letter];
    }

    bool is_Lowercase(const UCS4 uc) const {
      return category(uc) == CAT_Ll;
    }

    UCS4 titlecase(const UCS4 uc) const {
      return Halfwidth_and_Fullwidth_FormsFF00::_title[uc - _first_letter];
    }

    bool is_Titlecase(const UCS4 uc) const {
      return category(uc) == CAT_Lt;
    }

    int dec_digit_value(const UCS4 uc) const {
      if (!is_defined(uc))
        return 0;
      switch(uc) {
      case 0xFF10:
        return 0;
        break;
      case 0xFF11:
        return 1;
        break;
      case 0xFF12:
        return 2;
        break;
      case 0xFF13:
        return 3;
        break;
      case 0xFF14:
        return 4;
        break;
      case 0xFF15:
        return 5;
        break;
      case 0xFF16:
        return 6;
        break;
      case 0xFF17:
        return 7;
        break;
      case 0xFF18:
        return 8;
        break;
      case 0xFF19:
        return 9;
        break;
      default:
        return 0;
      }
    }

    bool is_Decimal_Digit(const UCS4 uc) const {
      switch(uc) {
      case 0xFF10:
      case 0xFF11:
      case 0xFF12:
      case 0xFF13:
      case 0xFF14:
      case 0xFF15:
      case 0xFF16:
      case 0xFF17:
      case 0xFF18:
      case 0xFF19:
        return 1;
      default:
        return 0;
      }
    }

    int digit_value(const UCS4 uc) const {
      if (!is_defined(uc))
        return 0;
      switch(uc) {
      case 0xFF10:
        return 0;
        break;
      case 0xFF11:
        return 1;
        break;
      case 0xFF12:
        return 2;
        break;
      case 0xFF13:
        return 3;
        break;
      case 0xFF14:
        return 4;
        break;
      case 0xFF15:
        return 5;
        break;
      case 0xFF16:
        return 6;
        break;
      case 0xFF17:
        return 7;
        break;
      case 0xFF18:
        return 8;
        break;
      case 0xFF19:
        return 9;
        break;
      default:
        return 0;
      }
    }

    bool is_Digit(const UCS4 uc) const {
      switch(uc) {
      case 0xFF10:
      case 0xFF11:
      case 0xFF12:
      case 0xFF13:
      case 0xFF14:
      case 0xFF15:
      case 0xFF16:
      case 0xFF17:
      case 0xFF18:
      case 0xFF19:
        return 1;
      default:
        return 0;
      }
    }

    float numeric_value(const UCS4 uc) const {
      if (!is_defined(uc))
        return 0;
      switch(uc) {
      case 0xFF10:
        return 0.000000;
        break;
      case 0xFF11:
        return 1.000000;
        break;
      case 0xFF12:
        return 2.000000;
        break;
      case 0xFF13:
        return 3.000000;
        break;
      case 0xFF14:
        return 4.000000;
        break;
      case 0xFF15:
        return 5.000000;
        break;
      case 0xFF16:
        return 6.000000;
        break;
      case 0xFF17:
        return 7.000000;
        break;
      case 0xFF18:
        return 8.000000;
        break;
      case 0xFF19:
        return 9.000000;
        break;
      default:
        return 0;
      }
    }

    bool is_Numeric(const UCS4 uc) const {
      switch(uc) {
      case 0xFF10:
      case 0xFF11:
      case 0xFF12:
      case 0xFF13:
      case 0xFF14:
      case 0xFF15:
      case 0xFF16:
      case 0xFF17:
      case 0xFF18:
      case 0xFF19:
        return 1;
      default:
        return 0;
      }
    }

    Gen_Cat category(const UCS4 uc) const {
      if (!is_defined(uc))
        return CAT_MAX;
      return Babylon::Gen_Cat(Halfwidth_and_Fullwidth_FormsFF00::_cat[uc - _first_letter]);
    }

    Can_Comb_Class comb_class(const UCS4 uc) const {
      if (!is_defined(uc))
        return CC_MAX;
      return Babylon::Can_Comb_Class(0);
    }

    Bidir_Props bidir_props(const UCS4 uc) const {
      if (!is_defined(uc))
        return BIDIR_MAX;
      return Babylon::Bidir_Props(Halfwidth_and_Fullwidth_FormsFF00::_bidir[uc - _first_letter]);
    }

    Char_Decomp decomp_type(const UCS4 uc) const {
      if (!is_defined(uc))
        return DECOMP_MAX;
      return Babylon::Char_Decomp(Halfwidth_and_Fullwidth_FormsFF00::_decomp[uc - _first_letter]);
    }

    UTF32_string decompose(const UCS4 uc) const {
      Babylon::UTF32_string us;
      us.resize(2);
      us[0] = Halfwidth_and_Fullwidth_FormsFF00::_decompStr[uc - _first_letter][0];
      us[1] = Halfwidth_and_Fullwidth_FormsFF00::_decompStr[uc - _first_letter][1];
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
      return Babylon::Line_Break(Halfwidth_and_Fullwidth_FormsFF00::_lb[uc - _first_letter]);
    }

    EA_Width EA_width(const UCS4 uc) const {
      if (!is_defined(uc))
        return EA_WIDTH_MAX;
      return Babylon::EA_Width(Halfwidth_and_Fullwidth_FormsFF00::_ea[uc - _first_letter]);
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
      return Halfwidth_and_Fullwidth_FormsFF00::_Dash[uc - _first_letter];
    }

    bool is_Hyphen(const UCS4 uc) const {
      return Halfwidth_and_Fullwidth_FormsFF00::_Hyphen[uc - _first_letter];
    }

    bool is_Quotation_Mark(const UCS4 uc) const {
      return Halfwidth_and_Fullwidth_FormsFF00::_Quotation_Mark[uc - _first_letter];
    }

    bool is_Terminal_Punctuation(const UCS4 uc) const {
      return Halfwidth_and_Fullwidth_FormsFF00::_Terminal_Punctuation[uc - _first_letter];
    }

    bool is_Math(const UCS4 uc) const {
      return Halfwidth_and_Fullwidth_FormsFF00::_Math[uc - _first_letter];
    }

    bool is_Paired_Punctuation(const UCS4 uc) const {
      return Halfwidth_and_Fullwidth_FormsFF00::_Paired_Punctuation[uc - _first_letter];
    }

    bool is_Left_of_Pair(const UCS4 uc) const {
      return Halfwidth_and_Fullwidth_FormsFF00::_Left_of_Pair[uc - _first_letter];
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
      return Halfwidth_and_Fullwidth_FormsFF00::_Hex_Digit[uc - _first_letter];
    }

    bool is_Alphabetic(const UCS4 uc) const {
      return Halfwidth_and_Fullwidth_FormsFF00::_Alphabetic[uc - _first_letter];
    }

    bool is_Diacritic(const UCS4 uc) const {
      return Halfwidth_and_Fullwidth_FormsFF00::_Diacritic[uc - _first_letter];
    }

    bool is_Extender(const UCS4 uc) const {
      return Halfwidth_and_Fullwidth_FormsFF00::_Extender[uc - _first_letter];
    }

    bool is_Identifier_Part(const UCS4 uc) const {
      return Halfwidth_and_Fullwidth_FormsFF00::_Identifier_Part[uc - _first_letter];
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
    Halfwidth_and_Fullwidth_FormsFF00(const Halfwidth_and_Fullwidth_FormsFF00 &) {}

    Babylon::UCS4 _first_letter;
    Babylon::UCS4 _last_letter;
    static const bool _is_defined[240];
    static const UCS4 _upper[240];
    static const UCS4 _lower[240];
    static const UCS4 _title[240];
    static const unsigned char _cat[240];
    static const unsigned char _bidir[240];
    static const unsigned char _decomp[240];
    static const UCS2 _decompStr[240][2];
    static const unsigned char _lb[240];
    static const unsigned char _ea[240];
    static const bool _Dash[240];
    static const bool _Hyphen[240];
    static const bool _Quotation_Mark[240];
    static const bool _Terminal_Punctuation[240];
    static const bool _Math[240];
    static const bool _Paired_Punctuation[240];
    static const bool _Left_of_Pair[240];
    static const bool _Hex_Digit[240];
    static const bool _Alphabetic[240];
    static const bool _Diacritic[240];
    static const bool _Extender[240];
    static const bool _Identifier_Part[240];

  }; // class Halfwidth_and_Fullwidth_FormsFF00

  const bool Halfwidth_and_Fullwidth_FormsFF00::_is_defined[] = {
    0, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 0, 
    0, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 0, 
    0, 0, 1, 1, 1, 1, 1, 1, 
    0, 0, 1, 1, 1, 1, 1, 1, 
    0, 0, 1, 1, 1, 1, 1, 1, 
    0, 0, 1, 1, 1, 0, 0, 0, 
    1, 1, 1, 1, 1, 1, 1, 0, 
    1, 1, 1, 1, 1, 1, 1, 0
  };

  const UCS4 Halfwidth_and_Fullwidth_FormsFF00::_upper[] = {
    0xFF00, 0xFF01, 0xFF02, 0xFF03, 0xFF04, 0xFF05, 0xFF06, 0xFF07, 
    0xFF08, 0xFF09, 0xFF0A, 0xFF0B, 0xFF0C, 0xFF0D, 0xFF0E, 0xFF0F, 
    0xFF10, 0xFF11, 0xFF12, 0xFF13, 0xFF14, 0xFF15, 0xFF16, 0xFF17, 
    0xFF18, 0xFF19, 0xFF1A, 0xFF1B, 0xFF1C, 0xFF1D, 0xFF1E, 0xFF1F, 
    0xFF20, 0xFF21, 0xFF22, 0xFF23, 0xFF24, 0xFF25, 0xFF26, 0xFF27, 
    0xFF28, 0xFF29, 0xFF2A, 0xFF2B, 0xFF2C, 0xFF2D, 0xFF2E, 0xFF2F, 
    0xFF30, 0xFF31, 0xFF32, 0xFF33, 0xFF34, 0xFF35, 0xFF36, 0xFF37, 
    0xFF38, 0xFF39, 0xFF3A, 0xFF3B, 0xFF3C, 0xFF3D, 0xFF3E, 0xFF3F, 
    0xFF40, 0xFF21, 0xFF22, 0xFF23, 0xFF24, 0xFF25, 0xFF26, 0xFF27, 
    0xFF28, 0xFF29, 0xFF2A, 0xFF2B, 0xFF2C, 0xFF2D, 0xFF2E, 0xFF2F, 
    0xFF30, 0xFF31, 0xFF32, 0xFF33, 0xFF34, 0xFF35, 0xFF36, 0xFF37, 
    0xFF38, 0xFF39, 0xFF3A, 0xFF5B, 0xFF5C, 0xFF5D, 0xFF5E, 0xFF5F, 
    0xFF60, 0xFF61, 0xFF62, 0xFF63, 0xFF64, 0xFF65, 0xFF66, 0xFF67, 
    0xFF68, 0xFF69, 0xFF6A, 0xFF6B, 0xFF6C, 0xFF6D, 0xFF6E, 0xFF6F, 
    0xFF70, 0xFF71, 0xFF72, 0xFF73, 0xFF74, 0xFF75, 0xFF76, 0xFF77, 
    0xFF78, 0xFF79, 0xFF7A, 0xFF7B, 0xFF7C, 0xFF7D, 0xFF7E, 0xFF7F, 
    0xFF80, 0xFF81, 0xFF82, 0xFF83, 0xFF84, 0xFF85, 0xFF86, 0xFF87, 
    0xFF88, 0xFF89, 0xFF8A, 0xFF8B, 0xFF8C, 0xFF8D, 0xFF8E, 0xFF8F, 
    0xFF90, 0xFF91, 0xFF92, 0xFF93, 0xFF94, 0xFF95, 0xFF96, 0xFF97, 
    0xFF98, 0xFF99, 0xFF9A, 0xFF9B, 0xFF9C, 0xFF9D, 0xFF9E, 0xFF9F, 
    0xFFA0, 0xFFA1, 0xFFA2, 0xFFA3, 0xFFA4, 0xFFA5, 0xFFA6, 0xFFA7, 
    0xFFA8, 0xFFA9, 0xFFAA, 0xFFAB, 0xFFAC, 0xFFAD, 0xFFAE, 0xFFAF, 
    0xFFB0, 0xFFB1, 0xFFB2, 0xFFB3, 0xFFB4, 0xFFB5, 0xFFB6, 0xFFB7, 
    0xFFB8, 0xFFB9, 0xFFBA, 0xFFBB, 0xFFBC, 0xFFBD, 0xFFBE, 0xFFBF, 
    0xFFC0, 0xFFC1, 0xFFC2, 0xFFC3, 0xFFC4, 0xFFC5, 0xFFC6, 0xFFC7, 
    0xFFC8, 0xFFC9, 0xFFCA, 0xFFCB, 0xFFCC, 0xFFCD, 0xFFCE, 0xFFCF, 
    0xFFD0, 0xFFD1, 0xFFD2, 0xFFD3, 0xFFD4, 0xFFD5, 0xFFD6, 0xFFD7, 
    0xFFD8, 0xFFD9, 0xFFDA, 0xFFDB, 0xFFDC, 0xFFDD, 0xFFDE, 0xFFDF, 
    0xFFE0, 0xFFE1, 0xFFE2, 0xFFE3, 0xFFE4, 0xFFE5, 0xFFE6, 0xFFE7, 
    0xFFE8, 0xFFE9, 0xFFEA, 0xFFEB, 0xFFEC, 0xFFED, 0xFFEE, 0xFFEF
  };

  const UCS4 Halfwidth_and_Fullwidth_FormsFF00::_lower[] = {
    0xFF00, 0xFF01, 0xFF02, 0xFF03, 0xFF04, 0xFF05, 0xFF06, 0xFF07, 
    0xFF08, 0xFF09, 0xFF0A, 0xFF0B, 0xFF0C, 0xFF0D, 0xFF0E, 0xFF0F, 
    0xFF10, 0xFF11, 0xFF12, 0xFF13, 0xFF14, 0xFF15, 0xFF16, 0xFF17, 
    0xFF18, 0xFF19, 0xFF1A, 0xFF1B, 0xFF1C, 0xFF1D, 0xFF1E, 0xFF1F, 
    0xFF20, 0xFF41, 0xFF42, 0xFF43, 0xFF44, 0xFF45, 0xFF46, 0xFF47, 
    0xFF48, 0xFF49, 0xFF4A, 0xFF4B, 0xFF4C, 0xFF4D, 0xFF4E, 0xFF4F, 
    0xFF50, 0xFF51, 0xFF52, 0xFF53, 0xFF54, 0xFF55, 0xFF56, 0xFF57, 
    0xFF58, 0xFF59, 0xFF5A, 0xFF3B, 0xFF3C, 0xFF3D, 0xFF3E, 0xFF3F, 
    0xFF40, 0xFF41, 0xFF42, 0xFF43, 0xFF44, 0xFF45, 0xFF46, 0xFF47, 
    0xFF48, 0xFF49, 0xFF4A, 0xFF4B, 0xFF4C, 0xFF4D, 0xFF4E, 0xFF4F, 
    0xFF50, 0xFF51, 0xFF52, 0xFF53, 0xFF54, 0xFF55, 0xFF56, 0xFF57, 
    0xFF58, 0xFF59, 0xFF5A, 0xFF5B, 0xFF5C, 0xFF5D, 0xFF5E, 0xFF5F, 
    0xFF60, 0xFF61, 0xFF62, 0xFF63, 0xFF64, 0xFF65, 0xFF66, 0xFF67, 
    0xFF68, 0xFF69, 0xFF6A, 0xFF6B, 0xFF6C, 0xFF6D, 0xFF6E, 0xFF6F, 
    0xFF70, 0xFF71, 0xFF72, 0xFF73, 0xFF74, 0xFF75, 0xFF76, 0xFF77, 
    0xFF78, 0xFF79, 0xFF7A, 0xFF7B, 0xFF7C, 0xFF7D, 0xFF7E, 0xFF7F, 
    0xFF80, 0xFF81, 0xFF82, 0xFF83, 0xFF84, 0xFF85, 0xFF86, 0xFF87, 
    0xFF88, 0xFF89, 0xFF8A, 0xFF8B, 0xFF8C, 0xFF8D, 0xFF8E, 0xFF8F, 
    0xFF90, 0xFF91, 0xFF92, 0xFF93, 0xFF94, 0xFF95, 0xFF96, 0xFF97, 
    0xFF98, 0xFF99, 0xFF9A, 0xFF9B, 0xFF9C, 0xFF9D, 0xFF9E, 0xFF9F, 
    0xFFA0, 0xFFA1, 0xFFA2, 0xFFA3, 0xFFA4, 0xFFA5, 0xFFA6, 0xFFA7, 
    0xFFA8, 0xFFA9, 0xFFAA, 0xFFAB, 0xFFAC, 0xFFAD, 0xFFAE, 0xFFAF, 
    0xFFB0, 0xFFB1, 0xFFB2, 0xFFB3, 0xFFB4, 0xFFB5, 0xFFB6, 0xFFB7, 
    0xFFB8, 0xFFB9, 0xFFBA, 0xFFBB, 0xFFBC, 0xFFBD, 0xFFBE, 0xFFBF, 
    0xFFC0, 0xFFC1, 0xFFC2, 0xFFC3, 0xFFC4, 0xFFC5, 0xFFC6, 0xFFC7, 
    0xFFC8, 0xFFC9, 0xFFCA, 0xFFCB, 0xFFCC, 0xFFCD, 0xFFCE, 0xFFCF, 
    0xFFD0, 0xFFD1, 0xFFD2, 0xFFD3, 0xFFD4, 0xFFD5, 0xFFD6, 0xFFD7, 
    0xFFD8, 0xFFD9, 0xFFDA, 0xFFDB, 0xFFDC, 0xFFDD, 0xFFDE, 0xFFDF, 
    0xFFE0, 0xFFE1, 0xFFE2, 0xFFE3, 0xFFE4, 0xFFE5, 0xFFE6, 0xFFE7, 
    0xFFE8, 0xFFE9, 0xFFEA, 0xFFEB, 0xFFEC, 0xFFED, 0xFFEE, 0xFFEF
  };

  const UCS4 Halfwidth_and_Fullwidth_FormsFF00::_title[] = {
    0xFF00, 0xFF01, 0xFF02, 0xFF03, 0xFF04, 0xFF05, 0xFF06, 0xFF07, 
    0xFF08, 0xFF09, 0xFF0A, 0xFF0B, 0xFF0C, 0xFF0D, 0xFF0E, 0xFF0F, 
    0xFF10, 0xFF11, 0xFF12, 0xFF13, 0xFF14, 0xFF15, 0xFF16, 0xFF17, 
    0xFF18, 0xFF19, 0xFF1A, 0xFF1B, 0xFF1C, 0xFF1D, 0xFF1E, 0xFF1F, 
    0xFF20, 0xFF21, 0xFF22, 0xFF23, 0xFF24, 0xFF25, 0xFF26, 0xFF27, 
    0xFF28, 0xFF29, 0xFF2A, 0xFF2B, 0xFF2C, 0xFF2D, 0xFF2E, 0xFF2F, 
    0xFF30, 0xFF31, 0xFF32, 0xFF33, 0xFF34, 0xFF35, 0xFF36, 0xFF37, 
    0xFF38, 0xFF39, 0xFF3A, 0xFF3B, 0xFF3C, 0xFF3D, 0xFF3E, 0xFF3F, 
    0xFF40, 0xFF21, 0xFF22, 0xFF23, 0xFF24, 0xFF25, 0xFF26, 0xFF27, 
    0xFF28, 0xFF29, 0xFF2A, 0xFF2B, 0xFF2C, 0xFF2D, 0xFF2E, 0xFF2F, 
    0xFF30, 0xFF31, 0xFF32, 0xFF33, 0xFF34, 0xFF35, 0xFF36, 0xFF37, 
    0xFF38, 0xFF39, 0xFF3A, 0xFF5B, 0xFF5C, 0xFF5D, 0xFF5E, 0xFF5F, 
    0xFF60, 0xFF61, 0xFF62, 0xFF63, 0xFF64, 0xFF65, 0xFF66, 0xFF67, 
    0xFF68, 0xFF69, 0xFF6A, 0xFF6B, 0xFF6C, 0xFF6D, 0xFF6E, 0xFF6F, 
    0xFF70, 0xFF71, 0xFF72, 0xFF73, 0xFF74, 0xFF75, 0xFF76, 0xFF77, 
    0xFF78, 0xFF79, 0xFF7A, 0xFF7B, 0xFF7C, 0xFF7D, 0xFF7E, 0xFF7F, 
    0xFF80, 0xFF81, 0xFF82, 0xFF83, 0xFF84, 0xFF85, 0xFF86, 0xFF87, 
    0xFF88, 0xFF89, 0xFF8A, 0xFF8B, 0xFF8C, 0xFF8D, 0xFF8E, 0xFF8F, 
    0xFF90, 0xFF91, 0xFF92, 0xFF93, 0xFF94, 0xFF95, 0xFF96, 0xFF97, 
    0xFF98, 0xFF99, 0xFF9A, 0xFF9B, 0xFF9C, 0xFF9D, 0xFF9E, 0xFF9F, 
    0xFFA0, 0xFFA1, 0xFFA2, 0xFFA3, 0xFFA4, 0xFFA5, 0xFFA6, 0xFFA7, 
    0xFFA8, 0xFFA9, 0xFFAA, 0xFFAB, 0xFFAC, 0xFFAD, 0xFFAE, 0xFFAF, 
    0xFFB0, 0xFFB1, 0xFFB2, 0xFFB3, 0xFFB4, 0xFFB5, 0xFFB6, 0xFFB7, 
    0xFFB8, 0xFFB9, 0xFFBA, 0xFFBB, 0xFFBC, 0xFFBD, 0xFFBE, 0xFFBF, 
    0xFFC0, 0xFFC1, 0xFFC2, 0xFFC3, 0xFFC4, 0xFFC5, 0xFFC6, 0xFFC7, 
    0xFFC8, 0xFFC9, 0xFFCA, 0xFFCB, 0xFFCC, 0xFFCD, 0xFFCE, 0xFFCF, 
    0xFFD0, 0xFFD1, 0xFFD2, 0xFFD3, 0xFFD4, 0xFFD5, 0xFFD6, 0xFFD7, 
    0xFFD8, 0xFFD9, 0xFFDA, 0xFFDB, 0xFFDC, 0xFFDD, 0xFFDE, 0xFFDF, 
    0xFFE0, 0xFFE1, 0xFFE2, 0xFFE3, 0xFFE4, 0xFFE5, 0xFFE6, 0xFFE7, 
    0xFFE8, 0xFFE9, 0xFFEA, 0xFFEB, 0xFFEC, 0xFFED, 0xFFEE, 0xFFEF
  };

  const unsigned char Halfwidth_and_Fullwidth_FormsFF00::_cat[] = {
    CAT_Po, CAT_Po, CAT_Po, CAT_Po, CAT_Sc, CAT_Po, CAT_Po, CAT_Po, 
    CAT_Ps, CAT_Pe, CAT_Po, CAT_Sm, CAT_Po, CAT_Pd, CAT_Po, CAT_Po, 
    CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, CAT_Nd, 
    CAT_Nd, CAT_Nd, CAT_Po, CAT_Po, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Po, 
    CAT_Po, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
    CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
    CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, CAT_Lu, 
    CAT_Lu, CAT_Lu, CAT_Lu, CAT_Ps, CAT_Po, CAT_Pe, CAT_Sk, CAT_Pc, 
    CAT_Sk, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
    CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
    CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ll, 
    CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ps, CAT_Sm, CAT_Pe, CAT_Sm, CAT_Po, 
    CAT_Po, CAT_Po, CAT_Ps, CAT_Pe, CAT_Po, CAT_Pc, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lm, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lm, CAT_Lm, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Po, 
    CAT_Po, CAT_Po, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Po, CAT_Po, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Po, CAT_Po, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Lo, 
    CAT_Po, CAT_Po, CAT_Lo, CAT_Lo, CAT_Lo, CAT_Po, CAT_Po, CAT_Po, 
    CAT_Sc, CAT_Sc, CAT_Sm, CAT_Sk, CAT_So, CAT_Sc, CAT_Sc, CAT_Po, 
    CAT_So, CAT_Sm, CAT_Sm, CAT_Sm, CAT_Sm, CAT_So, CAT_So, CAT_Po
  };

  const unsigned char Halfwidth_and_Fullwidth_FormsFF00::_bidir[] = {
    BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ET, BIDIR_ET, BIDIR_ET, BIDIR_ON, BIDIR_ON, 
    BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ET, BIDIR_CS, BIDIR_ET, BIDIR_CS, BIDIR_ES, 
    BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
    BIDIR_EN, BIDIR_EN, BIDIR_CS, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
    BIDIR_ON, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
    BIDIR_ON, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
    BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_ON, 
    BIDIR_ON, BIDIR_ON, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_ON, BIDIR_ON, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_ON, BIDIR_ON, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
    BIDIR_ON, BIDIR_ON, BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
    BIDIR_ET, BIDIR_ET, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ET, BIDIR_ET, BIDIR_ON, 
    BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON
  };

  const unsigned char Halfwidth_and_Fullwidth_FormsFF00::_decomp[] = {
    DECOMP_NO_DECOMP, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, 
    DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, 
    DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, 
    DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, 
    DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, 
    DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, 
    DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, 
    DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, 
    DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, 
    DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, 
    DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, 
    DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
    DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
    DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
    DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
    DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
    DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
    DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
    DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
    DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
    DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
    DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
    DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NO_DECOMP, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
    DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, DECOMP_NO_DECOMP, 
    DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_NO_DECOMP, 
    DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NO_DECOMP
  };

  const UCS2 Halfwidth_and_Fullwidth_FormsFF00::_decompStr[][2] = {
    { 0xFF00, 0x0000 }, { 0x0021, 0x0000 }, { 0x0022, 0x0000 }, { 0x0023, 0x0000 }, 
    { 0x0024, 0x0000 }, { 0x0025, 0x0000 }, { 0x0026, 0x0000 }, { 0x0027, 0x0000 }, 
    { 0x0028, 0x0000 }, { 0x0029, 0x0000 }, { 0x002A, 0x0000 }, { 0x002B, 0x0000 }, 
    { 0x002C, 0x0000 }, { 0x002D, 0x0000 }, { 0x002E, 0x0000 }, { 0x002F, 0x0000 }, 
    { 0x0030, 0x0000 }, { 0x0031, 0x0000 }, { 0x0032, 0x0000 }, { 0x0033, 0x0000 }, 
    { 0x0034, 0x0000 }, { 0x0035, 0x0000 }, { 0x0036, 0x0000 }, { 0x0037, 0x0000 }, 
    { 0x0038, 0x0000 }, { 0x0039, 0x0000 }, { 0x003A, 0x0000 }, { 0x003B, 0x0000 }, 
    { 0x003C, 0x0000 }, { 0x003D, 0x0000 }, { 0x003E, 0x0000 }, { 0x003F, 0x0000 }, 
    { 0x0040, 0x0000 }, { 0x0041, 0x0000 }, { 0x0042, 0x0000 }, { 0x0043, 0x0000 }, 
    { 0x0044, 0x0000 }, { 0x0045, 0x0000 }, { 0x0046, 0x0000 }, { 0x0047, 0x0000 }, 
    { 0x0048, 0x0000 }, { 0x0049, 0x0000 }, { 0x004A, 0x0000 }, { 0x004B, 0x0000 }, 
    { 0x004C, 0x0000 }, { 0x004D, 0x0000 }, { 0x004E, 0x0000 }, { 0x004F, 0x0000 }, 
    { 0x0050, 0x0000 }, { 0x0051, 0x0000 }, { 0x0052, 0x0000 }, { 0x0053, 0x0000 }, 
    { 0x0054, 0x0000 }, { 0x0055, 0x0000 }, { 0x0056, 0x0000 }, { 0x0057, 0x0000 }, 
    { 0x0058, 0x0000 }, { 0x0059, 0x0000 }, { 0x005A, 0x0000 }, { 0x005B, 0x0000 }, 
    { 0x005C, 0x0000 }, { 0x005D, 0x0000 }, { 0x005E, 0x0000 }, { 0x005F, 0x0000 }, 
    { 0x0060, 0x0000 }, { 0x0061, 0x0000 }, { 0x0062, 0x0000 }, { 0x0063, 0x0000 }, 
    { 0x0064, 0x0000 }, { 0x0065, 0x0000 }, { 0x0066, 0x0000 }, { 0x0067, 0x0000 }, 
    { 0x0068, 0x0000 }, { 0x0069, 0x0000 }, { 0x006A, 0x0000 }, { 0x006B, 0x0000 }, 
    { 0x006C, 0x0000 }, { 0x006D, 0x0000 }, { 0x006E, 0x0000 }, { 0x006F, 0x0000 }, 
    { 0x0070, 0x0000 }, { 0x0071, 0x0000 }, { 0x0072, 0x0000 }, { 0x0073, 0x0000 }, 
    { 0x0074, 0x0000 }, { 0x0075, 0x0000 }, { 0x0076, 0x0000 }, { 0x0077, 0x0000 }, 
    { 0x0078, 0x0000 }, { 0x0079, 0x0000 }, { 0x007A, 0x0000 }, { 0x007B, 0x0000 }, 
    { 0x007C, 0x0000 }, { 0x007D, 0x0000 }, { 0x007E, 0x0000 }, { 0xFF5F, 0x0000 }, 
    { 0xFF60, 0x0000 }, { 0x3002, 0x0000 }, { 0x300C, 0x0000 }, { 0x300D, 0x0000 }, 
    { 0x3001, 0x0000 }, { 0x30FB, 0x0000 }, { 0x30F2, 0x0000 }, { 0x30A1, 0x0000 }, 
    { 0x30A3, 0x0000 }, { 0x30A5, 0x0000 }, { 0x30A7, 0x0000 }, { 0x30A9, 0x0000 }, 
    { 0x30E3, 0x0000 }, { 0x30E5, 0x0000 }, { 0x30E7, 0x0000 }, { 0x30C3, 0x0000 }, 
    { 0x30FC, 0x0000 }, { 0x30A2, 0x0000 }, { 0x30A4, 0x0000 }, { 0x30A6, 0x0000 }, 
    { 0x30A8, 0x0000 }, { 0x30AA, 0x0000 }, { 0x30AB, 0x0000 }, { 0x30AD, 0x0000 }, 
    { 0x30AF, 0x0000 }, { 0x30B1, 0x0000 }, { 0x30B3, 0x0000 }, { 0x30B5, 0x0000 }, 
    { 0x30B7, 0x0000 }, { 0x30B9, 0x0000 }, { 0x30BB, 0x0000 }, { 0x30BD, 0x0000 }, 
    { 0x30BF, 0x0000 }, { 0x30C1, 0x0000 }, { 0x30C4, 0x0000 }, { 0x30C6, 0x0000 }, 
    { 0x30C8, 0x0000 }, { 0x30CA, 0x0000 }, { 0x30CB, 0x0000 }, { 0x30CC, 0x0000 }, 
    { 0x30CD, 0x0000 }, { 0x30CE, 0x0000 }, { 0x30CF, 0x0000 }, { 0x30D2, 0x0000 }, 
    { 0x30D5, 0x0000 }, { 0x30D8, 0x0000 }, { 0x30DB, 0x0000 }, { 0x30DE, 0x0000 }, 
    { 0x30DF, 0x0000 }, { 0x30E0, 0x0000 }, { 0x30E1, 0x0000 }, { 0x30E2, 0x0000 }, 
    { 0x30E4, 0x0000 }, { 0x30E6, 0x0000 }, { 0x30E8, 0x0000 }, { 0x30E9, 0x0000 }, 
    { 0x30EA, 0x0000 }, { 0x30EB, 0x0000 }, { 0x30EC, 0x0000 }, { 0x30ED, 0x0000 }, 
    { 0x30EF, 0x0000 }, { 0x30F3, 0x0000 }, { 0x3099, 0x0000 }, { 0x309A, 0x0000 }, 
    { 0x3164, 0x0000 }, { 0x3131, 0x0000 }, { 0x3132, 0x0000 }, { 0x3133, 0x0000 }, 
    { 0x3134, 0x0000 }, { 0x3135, 0x0000 }, { 0x3136, 0x0000 }, { 0x3137, 0x0000 }, 
    { 0x3138, 0x0000 }, { 0x3139, 0x0000 }, { 0x313A, 0x0000 }, { 0x313B, 0x0000 }, 
    { 0x313C, 0x0000 }, { 0x313D, 0x0000 }, { 0x313E, 0x0000 }, { 0x313F, 0x0000 }, 
    { 0x3140, 0x0000 }, { 0x3141, 0x0000 }, { 0x3142, 0x0000 }, { 0x3143, 0x0000 }, 
    { 0x3144, 0x0000 }, { 0x3145, 0x0000 }, { 0x3146, 0x0000 }, { 0x3147, 0x0000 }, 
    { 0x3148, 0x0000 }, { 0x3149, 0x0000 }, { 0x314A, 0x0000 }, { 0x314B, 0x0000 }, 
    { 0x314C, 0x0000 }, { 0x314D, 0x0000 }, { 0x314E, 0x0000 }, { 0xFFBF, 0x0000 }, 
    { 0xFFC0, 0x0000 }, { 0xFFC1, 0x0000 }, { 0x314F, 0x0000 }, { 0x3150, 0x0000 }, 
    { 0x3151, 0x0000 }, { 0x3152, 0x0000 }, { 0x3153, 0x0000 }, { 0x3154, 0x0000 }, 
    { 0xFFC8, 0x0000 }, { 0xFFC9, 0x0000 }, { 0x3155, 0x0000 }, { 0x3156, 0x0000 }, 
    { 0x3157, 0x0000 }, { 0x3158, 0x0000 }, { 0x3159, 0x0000 }, { 0x315A, 0x0000 }, 
    { 0xFFD0, 0x0000 }, { 0xFFD1, 0x0000 }, { 0x315B, 0x0000 }, { 0x315C, 0x0000 }, 
    { 0x315D, 0x0000 }, { 0x315E, 0x0000 }, { 0x315F, 0x0000 }, { 0x3160, 0x0000 }, 
    { 0xFFD8, 0x0000 }, { 0xFFD9, 0x0000 }, { 0x3161, 0x0000 }, { 0x3162, 0x0000 }, 
    { 0x3163, 0x0000 }, { 0xFFDD, 0x0000 }, { 0xFFDE, 0x0000 }, { 0xFFDF, 0x0000 }, 
    { 0x00A2, 0x0000 }, { 0x00A3, 0x0000 }, { 0x00AC, 0x0000 }, { 0x00AF, 0x0000 }, 
    { 0x00A6, 0x0000 }, { 0x00A5, 0x0000 }, { 0x20A9, 0x0000 }, { 0xFFE7, 0x0000 }, 
    { 0x2502, 0x0000 }, { 0x2190, 0x0000 }, { 0x2191, 0x0000 }, { 0x2192, 0x0000 }, 
    { 0x2193, 0x0000 }, { 0x25A0, 0x0000 }, { 0x25CB, 0x0000 }, { 0xFFEF, 0x0000 }
  };

  const unsigned char Halfwidth_and_Fullwidth_FormsFF00::_lb[] = {
    LB_EX, LB_EX, LB_ID, LB_ID, LB_PR, LB_PO, LB_ID, LB_ID, 
    LB_OP, LB_CL, LB_ID, LB_ID, LB_CL, LB_ID, LB_CL, LB_ID, 
    LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, 
    LB_ID, LB_ID, LB_NS, LB_NS, LB_ID, LB_ID, LB_ID, LB_EX, 
    LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, 
    LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, 
    LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, 
    LB_ID, LB_ID, LB_ID, LB_OP, LB_ID, LB_CL, LB_ID, LB_ID, 
    LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, 
    LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, 
    LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, LB_ID, 
    LB_ID, LB_ID, LB_ID, LB_OP, LB_ID, LB_CL, LB_ID, LB_EX, 
    LB_EX, LB_CL, LB_OP, LB_CL, LB_CL, LB_NS, LB_AL, LB_NS, 
    LB_NS, LB_NS, LB_NS, LB_NS, LB_NS, LB_NS, LB_NS, LB_NS, 
    LB_NS, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_NS, LB_NS, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_EX, 
    LB_EX, LB_EX, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_EX, LB_EX, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_EX, LB_EX, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
    LB_EX, LB_EX, LB_AL, LB_AL, LB_AL, LB_EX, LB_EX, LB_EX, 
    LB_PO, LB_PR, LB_ID, LB_ID, LB_ID, LB_PR, LB_PR, LB_EX, 
    LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_EX
  };

  const unsigned char Halfwidth_and_Fullwidth_FormsFF00::_ea[] = {
    EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
    EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
    EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
    EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
    EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
    EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
    EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
    EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
    EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
    EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
    EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
    EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
    EA_WIDTH_F, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
    EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
    EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
    EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
    EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
    EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
    EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
    EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
    EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
    EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
    EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
    EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_F, 
    EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
    EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
    EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
    EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
    EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
    EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_F
  };

    const bool Halfwidth_and_Fullwidth_FormsFF00::_Dash[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 1, 0, 0, 
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
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Halfwidth_and_Fullwidth_FormsFF00::_Hyphen[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 1, 0, 0, 
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
        0, 0, 0, 0, 0, 1, 0, 0, 
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

    const bool Halfwidth_and_Fullwidth_FormsFF00::_Quotation_Mark[] = {
        0, 0, 1, 0, 0, 0, 0, 1, 
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
        0, 0, 1, 1, 0, 0, 0, 0, 
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

    const bool Halfwidth_and_Fullwidth_FormsFF00::_Terminal_Punctuation[] = {
        0, 1, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 1, 0, 1, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 1, 1, 0, 0, 0, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 1, 0, 0, 1, 0, 0, 0, 
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

    const bool Halfwidth_and_Fullwidth_FormsFF00::_Math[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 0, 1, 0, 1, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 1, 1, 1, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 1, 1, 1, 1, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 1, 1, 1, 1, 0, 
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
        0, 0, 1, 0, 0, 0, 0, 0, 
        0, 1, 1, 1, 1, 0, 0, 0
    };

    const bool Halfwidth_and_Fullwidth_FormsFF00::_Paired_Punctuation[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 1, 0, 1, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 1, 0, 1, 0, 0, 
        0, 0, 1, 1, 0, 0, 0, 0, 
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

    const bool Halfwidth_and_Fullwidth_FormsFF00::_Left_of_Pair[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 1, 0, 0, 0, 0, 
        0, 0, 1, 0, 0, 0, 0, 0, 
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

    const bool Halfwidth_and_Fullwidth_FormsFF00::_Hex_Digit[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 0, 0, 0, 0, 0, 0, 
        0, 1, 1, 1, 1, 1, 1, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 1, 1, 1, 1, 1, 1, 0, 
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

    const bool Halfwidth_and_Fullwidth_FormsFF00::_Alphabetic[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 0, 0, 0, 0, 0, 
        0, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        0, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 0, 
        0, 0, 1, 1, 1, 1, 1, 1, 
        0, 0, 1, 1, 1, 1, 1, 1, 
        0, 0, 1, 1, 1, 1, 1, 1, 
        0, 0, 1, 1, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Halfwidth_and_Fullwidth_FormsFF00::_Diacritic[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 1, 0, 
        1, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 0, 0, 0, 0, 0, 0, 0, 
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
        0, 0, 0, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Halfwidth_and_Fullwidth_FormsFF00::_Extender[] = {
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
        1, 0, 0, 0, 0, 0, 0, 0, 
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

    const bool Halfwidth_and_Fullwidth_FormsFF00::_Identifier_Part[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 0, 0, 0, 0, 0, 0, 
        0, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 0, 0, 0, 0, 1, 
        0, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 0, 
        0, 0, 1, 1, 1, 1, 1, 1, 
        0, 0, 1, 1, 1, 1, 1, 1, 
        0, 0, 1, 1, 1, 1, 1, 1, 
        0, 0, 1, 1, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

}; // namespace Babylon

dload(Babylon::Halfwidth_and_Fullwidth_FormsFF00);
