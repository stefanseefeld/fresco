/*$Id: UnicodePluginGenerator.pl,v 1.5 2001/05/06 12:18:46 tobias Exp 2A00-2AFF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Thu, 30 May 2002 20:48:12 +0200.
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
#include <bitset>
#include <utility>

namespace Babylon {

  class Supplemental_Mathematical_Operators2A00 : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    Supplemental_Mathematical_Operators2A00() {
      m_first_letter = 0x2A00;
      m_last_letter  = 0x2AFF;
      // m_version="3.1" // Not yet supported!
    }

    ~Supplemental_Mathematical_Operators2A00() {
    }

    UCS4 first_letter() const {
      return m_first_letter;
    }

    UCS4 last_letter() const {
      return m_last_letter;
    }

    bool is_undef_block() const {
      return 0;
    }

    // query functions:
    std::string blockname(const UCS4 uc) const {
      return "Supplemental Mathematical Operators";
    }

    bool is_defined(const UCS4 uc) const {
      return 1;
    }

    UCS4 uppercase(const UCS4 uc) const {
      return uc;
    }

    UCS4 lowercase(const UCS4 uc) const {
      return uc;
    }

    UCS4 titlecase(const UCS4 uc) const {
      return uc;
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
      return Babylon::Gen_Cat(CAT_Sm);
    }

    Can_Comb_Class comb_class(const UCS4 uc) const {
      if (!is_defined(uc))
        return CC_MAX;
      return Babylon::Can_Comb_Class(0);
    }

    Bidir_Props bidir_props(const UCS4 uc) const {
      if (!is_defined(uc))
        return BIDIR_INVALID;
      return BIDIR_ON;
    }

    Char_Decomp decomp_type(const UCS4 uc) const {
      if (!is_defined(uc))
        return DECOMP_MAX;
      return Babylon::Char_Decomp(Supplemental_Mathematical_Operators2A00::_decomp[uc - m_first_letter]);
    }

    UTF32_string decompose(const UCS4 uc) const {
      Babylon::UTF32_string us;
      us.resize(2);
      us[0] = Supplemental_Mathematical_Operators2A00::m_decompStr[uc - m_first_letter][0];
      us[1] = Supplemental_Mathematical_Operators2A00::m_decompStr[uc - m_first_letter][1];

      switch (uc) {

      case 0x2A0C:
        us.resize(4);
        us[2u] = 0x222Bu;
        us[3u] = 0x222Bu;
        break;

      case 0x2A74:
        us.resize(3);
        us[2u] = 0x003Du;
        break;

      case 0x2A76:
        us.resize(3);
        us[2u] = 0x003Du;
        break;
      }
      if (us[1] == 0x0000u) {
        us.resize(1);
      }

      return us;
    }

    bool must_mirror(const UCS4 uc) const {
      return m_mirror.test(uc - m_first_letter);
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

    UCS4 compose (const UCS4 start, const UCS4 last) {
      return 0;
    }

    bool is_White_Space(const UCS4 uc) const {
      return 0;
    }

    bool is_Bidi_Control(const UCS4 uc) const {
      return 0;
    }

    bool is_Join_Control(const UCS4 uc) const {
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

    bool is_Other_Math(const UCS4 uc) const {
      return 0;
    }

    bool is_Hex_Digit(const UCS4 uc) const {
      return 0;
    }

    bool is_ASCII_Hex_Digit(const UCS4 uc) const {
      return 0;
    }

    bool is_Other_Alphabetic(const UCS4 uc) const {
      return 0;
    }

    bool is_Ideographic(const UCS4 uc) const {
      return 0;
    }

    bool is_Diacritic(const UCS4 uc) const {
      return 0;
    }

    bool is_Extender(const UCS4 uc) const {
      return 0;
    }

    bool is_Other_Lowercase(const UCS4 uc) const {
      return 0;
    }

    bool is_Other_Uppercase(const UCS4 uc) const {
      return 0;
    }

    bool is_Noncharacter_Code_Point(const UCS4 uc) const {
      return 0;
    }

    bool is_Other_Grapheme_Extend(const UCS4 uc) const {
      return 0;
    }

    bool is_Grapheme_Link(const UCS4 uc) const {
      return 0;
    }

    bool is_IDS_Binary_Operator(const UCS4 uc) const {
      return 0;
    }

    bool is_IDS_Trinary_Operator(const UCS4 uc) const {
      return 0;
    }

    bool is_Radical(const UCS4 uc) const {
      return 0;
    }

    bool is_Unified_Ideograph(const UCS4 uc) const {
      return 0;
    }

    bool is_Other_Default_Ignorable_Code_Point(const UCS4 uc) const {
      return 0;
    }

    bool is_Deprecated(const UCS4 uc) const {
      return 0;
    }

    bool is_Soft_Dotted(const UCS4 uc) const {
      return 0;
    }

    bool is_Logical_Order_Exception(const UCS4 uc) const {
      return 0;
    }

  private:
    // functions
    Supplemental_Mathematical_Operators2A00(const Supplemental_Mathematical_Operators2A00 &) {}

    Babylon::UCS4 m_first_letter;
    Babylon::UCS4 m_last_letter;
    // Babylon::UCS4_string m_version;
    static const unsigned char _decomp[256];
    static const UCS4 m_decompStr[256][2];
    static const std::bitset<256> m_mirror;
  }; // class Supplemental_Mathematical_Operators2A00

  const unsigned char Supplemental_Mathematical_Operators2A00::_decomp[] = {
    DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
    DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_COMPAT, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
    DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
    DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
    DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
    DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
    DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
    DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
    DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
    DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
    DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
    DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
    DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
    DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
    DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_CANONICAL, 
    DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
    DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
    DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
    DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
    DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
    DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
    DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
    DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
    DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
    DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
    DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
    DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
    DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
    DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
    DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
    DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
    DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL
  };

  const UCS4 Supplemental_Mathematical_Operators2A00::m_decompStr[][2] = {
    { 0x2A00u, 0x0000u }, { 0x2A01u, 0x0000u }, { 0x2A02u, 0x0000u }, { 0x2A03u, 0x0000u }, 
    { 0x2A04u, 0x0000u }, { 0x2A05u, 0x0000u }, { 0x2A06u, 0x0000u }, { 0x2A07u, 0x0000u }, 
    { 0x2A08u, 0x0000u }, { 0x2A09u, 0x0000u }, { 0x2A0Au, 0x0000u }, { 0x2A0Bu, 0x0000u }, 
    { 0x222Bu, 0x222Bu }, { 0x2A0Du, 0x0000u }, { 0x2A0Eu, 0x0000u }, { 0x2A0Fu, 0x0000u }, 
    { 0x2A10u, 0x0000u }, { 0x2A11u, 0x0000u }, { 0x2A12u, 0x0000u }, { 0x2A13u, 0x0000u }, 
    { 0x2A14u, 0x0000u }, { 0x2A15u, 0x0000u }, { 0x2A16u, 0x0000u }, { 0x2A17u, 0x0000u }, 
    { 0x2A18u, 0x0000u }, { 0x2A19u, 0x0000u }, { 0x2A1Au, 0x0000u }, { 0x2A1Bu, 0x0000u }, 
    { 0x2A1Cu, 0x0000u }, { 0x2A1Du, 0x0000u }, { 0x2A1Eu, 0x0000u }, { 0x2A1Fu, 0x0000u }, 
    { 0x2A20u, 0x0000u }, { 0x2A21u, 0x0000u }, { 0x2A22u, 0x0000u }, { 0x2A23u, 0x0000u }, 
    { 0x2A24u, 0x0000u }, { 0x2A25u, 0x0000u }, { 0x2A26u, 0x0000u }, { 0x2A27u, 0x0000u }, 
    { 0x2A28u, 0x0000u }, { 0x2A29u, 0x0000u }, { 0x2A2Au, 0x0000u }, { 0x2A2Bu, 0x0000u }, 
    { 0x2A2Cu, 0x0000u }, { 0x2A2Du, 0x0000u }, { 0x2A2Eu, 0x0000u }, { 0x2A2Fu, 0x0000u }, 
    { 0x2A30u, 0x0000u }, { 0x2A31u, 0x0000u }, { 0x2A32u, 0x0000u }, { 0x2A33u, 0x0000u }, 
    { 0x2A34u, 0x0000u }, { 0x2A35u, 0x0000u }, { 0x2A36u, 0x0000u }, { 0x2A37u, 0x0000u }, 
    { 0x2A38u, 0x0000u }, { 0x2A39u, 0x0000u }, { 0x2A3Au, 0x0000u }, { 0x2A3Bu, 0x0000u }, 
    { 0x2A3Cu, 0x0000u }, { 0x2A3Du, 0x0000u }, { 0x2A3Eu, 0x0000u }, { 0x2A3Fu, 0x0000u }, 
    { 0x2A40u, 0x0000u }, { 0x2A41u, 0x0000u }, { 0x2A42u, 0x0000u }, { 0x2A43u, 0x0000u }, 
    { 0x2A44u, 0x0000u }, { 0x2A45u, 0x0000u }, { 0x2A46u, 0x0000u }, { 0x2A47u, 0x0000u }, 
    { 0x2A48u, 0x0000u }, { 0x2A49u, 0x0000u }, { 0x2A4Au, 0x0000u }, { 0x2A4Bu, 0x0000u }, 
    { 0x2A4Cu, 0x0000u }, { 0x2A4Du, 0x0000u }, { 0x2A4Eu, 0x0000u }, { 0x2A4Fu, 0x0000u }, 
    { 0x2A50u, 0x0000u }, { 0x2A51u, 0x0000u }, { 0x2A52u, 0x0000u }, { 0x2A53u, 0x0000u }, 
    { 0x2A54u, 0x0000u }, { 0x2A55u, 0x0000u }, { 0x2A56u, 0x0000u }, { 0x2A57u, 0x0000u }, 
    { 0x2A58u, 0x0000u }, { 0x2A59u, 0x0000u }, { 0x2A5Au, 0x0000u }, { 0x2A5Bu, 0x0000u }, 
    { 0x2A5Cu, 0x0000u }, { 0x2A5Du, 0x0000u }, { 0x2A5Eu, 0x0000u }, { 0x2A5Fu, 0x0000u }, 
    { 0x2A60u, 0x0000u }, { 0x2A61u, 0x0000u }, { 0x2A62u, 0x0000u }, { 0x2A63u, 0x0000u }, 
    { 0x2A64u, 0x0000u }, { 0x2A65u, 0x0000u }, { 0x2A66u, 0x0000u }, { 0x2A67u, 0x0000u }, 
    { 0x2A68u, 0x0000u }, { 0x2A69u, 0x0000u }, { 0x2A6Au, 0x0000u }, { 0x2A6Bu, 0x0000u }, 
    { 0x2A6Cu, 0x0000u }, { 0x2A6Du, 0x0000u }, { 0x2A6Eu, 0x0000u }, { 0x2A6Fu, 0x0000u }, 
    { 0x2A70u, 0x0000u }, { 0x2A71u, 0x0000u }, { 0x2A72u, 0x0000u }, { 0x2A73u, 0x0000u }, 
    { 0x003Au, 0x003Au }, { 0x003Du, 0x003Du }, { 0x003Du, 0x003Du }, { 0x2A77u, 0x0000u }, 
    { 0x2A78u, 0x0000u }, { 0x2A79u, 0x0000u }, { 0x2A7Au, 0x0000u }, { 0x2A7Bu, 0x0000u }, 
    { 0x2A7Cu, 0x0000u }, { 0x2A7Du, 0x0000u }, { 0x2A7Eu, 0x0000u }, { 0x2A7Fu, 0x0000u }, 
    { 0x2A80u, 0x0000u }, { 0x2A81u, 0x0000u }, { 0x2A82u, 0x0000u }, { 0x2A83u, 0x0000u }, 
    { 0x2A84u, 0x0000u }, { 0x2A85u, 0x0000u }, { 0x2A86u, 0x0000u }, { 0x2A87u, 0x0000u }, 
    { 0x2A88u, 0x0000u }, { 0x2A89u, 0x0000u }, { 0x2A8Au, 0x0000u }, { 0x2A8Bu, 0x0000u }, 
    { 0x2A8Cu, 0x0000u }, { 0x2A8Du, 0x0000u }, { 0x2A8Eu, 0x0000u }, { 0x2A8Fu, 0x0000u }, 
    { 0x2A90u, 0x0000u }, { 0x2A91u, 0x0000u }, { 0x2A92u, 0x0000u }, { 0x2A93u, 0x0000u }, 
    { 0x2A94u, 0x0000u }, { 0x2A95u, 0x0000u }, { 0x2A96u, 0x0000u }, { 0x2A97u, 0x0000u }, 
    { 0x2A98u, 0x0000u }, { 0x2A99u, 0x0000u }, { 0x2A9Au, 0x0000u }, { 0x2A9Bu, 0x0000u }, 
    { 0x2A9Cu, 0x0000u }, { 0x2A9Du, 0x0000u }, { 0x2A9Eu, 0x0000u }, { 0x2A9Fu, 0x0000u }, 
    { 0x2AA0u, 0x0000u }, { 0x2AA1u, 0x0000u }, { 0x2AA2u, 0x0000u }, { 0x2AA3u, 0x0000u }, 
    { 0x2AA4u, 0x0000u }, { 0x2AA5u, 0x0000u }, { 0x2AA6u, 0x0000u }, { 0x2AA7u, 0x0000u }, 
    { 0x2AA8u, 0x0000u }, { 0x2AA9u, 0x0000u }, { 0x2AAAu, 0x0000u }, { 0x2AABu, 0x0000u }, 
    { 0x2AACu, 0x0000u }, { 0x2AADu, 0x0000u }, { 0x2AAEu, 0x0000u }, { 0x2AAFu, 0x0000u }, 
    { 0x2AB0u, 0x0000u }, { 0x2AB1u, 0x0000u }, { 0x2AB2u, 0x0000u }, { 0x2AB3u, 0x0000u }, 
    { 0x2AB4u, 0x0000u }, { 0x2AB5u, 0x0000u }, { 0x2AB6u, 0x0000u }, { 0x2AB7u, 0x0000u }, 
    { 0x2AB8u, 0x0000u }, { 0x2AB9u, 0x0000u }, { 0x2ABAu, 0x0000u }, { 0x2ABBu, 0x0000u }, 
    { 0x2ABCu, 0x0000u }, { 0x2ABDu, 0x0000u }, { 0x2ABEu, 0x0000u }, { 0x2ABFu, 0x0000u }, 
    { 0x2AC0u, 0x0000u }, { 0x2AC1u, 0x0000u }, { 0x2AC2u, 0x0000u }, { 0x2AC3u, 0x0000u }, 
    { 0x2AC4u, 0x0000u }, { 0x2AC5u, 0x0000u }, { 0x2AC6u, 0x0000u }, { 0x2AC7u, 0x0000u }, 
    { 0x2AC8u, 0x0000u }, { 0x2AC9u, 0x0000u }, { 0x2ACAu, 0x0000u }, { 0x2ACBu, 0x0000u }, 
    { 0x2ACCu, 0x0000u }, { 0x2ACDu, 0x0000u }, { 0x2ACEu, 0x0000u }, { 0x2ACFu, 0x0000u }, 
    { 0x2AD0u, 0x0000u }, { 0x2AD1u, 0x0000u }, { 0x2AD2u, 0x0000u }, { 0x2AD3u, 0x0000u }, 
    { 0x2AD4u, 0x0000u }, { 0x2AD5u, 0x0000u }, { 0x2AD6u, 0x0000u }, { 0x2AD7u, 0x0000u }, 
    { 0x2AD8u, 0x0000u }, { 0x2AD9u, 0x0000u }, { 0x2ADAu, 0x0000u }, { 0x2ADBu, 0x0000u }, 
    { 0x2ADDu, 0x0338u }, { 0x2ADDu, 0x0000u }, { 0x2ADEu, 0x0000u }, { 0x2ADFu, 0x0000u }, 
    { 0x2AE0u, 0x0000u }, { 0x2AE1u, 0x0000u }, { 0x2AE2u, 0x0000u }, { 0x2AE3u, 0x0000u }, 
    { 0x2AE4u, 0x0000u }, { 0x2AE5u, 0x0000u }, { 0x2AE6u, 0x0000u }, { 0x2AE7u, 0x0000u }, 
    { 0x2AE8u, 0x0000u }, { 0x2AE9u, 0x0000u }, { 0x2AEAu, 0x0000u }, { 0x2AEBu, 0x0000u }, 
    { 0x2AECu, 0x0000u }, { 0x2AEDu, 0x0000u }, { 0x2AEEu, 0x0000u }, { 0x2AEFu, 0x0000u }, 
    { 0x2AF0u, 0x0000u }, { 0x2AF1u, 0x0000u }, { 0x2AF2u, 0x0000u }, { 0x2AF3u, 0x0000u }, 
    { 0x2AF4u, 0x0000u }, { 0x2AF5u, 0x0000u }, { 0x2AF6u, 0x0000u }, { 0x2AF7u, 0x0000u }, 
    { 0x2AF8u, 0x0000u }, { 0x2AF9u, 0x0000u }, { 0x2AFAu, 0x0000u }, { 0x2AFBu, 0x0000u }, 
    { 0x2AFCu, 0x0000u }, { 0x2AFDu, 0x0000u }, { 0x2AFEu, 0x0000u }, { 0x2AFFu, 0x0000u }
  };

  const std::bitset<256> Supplemental_Mathematical_Operators2A00::m_mirror(std::string("0010111110001000011100000111110001010000011111111111111111111111111111111111111110111111110011111111111111111111111111111111111111111110000110011011110000110000000000011000000000000000000000000111000000110000011110100101001111011111111111111111110000000000"));

}; // namespace Babylon

dload(Babylon::Supplemental_Mathematical_Operators2A00);
