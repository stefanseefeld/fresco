/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999-2003 Tobias Hunger <Tobias@fresco.org>
 * http://www.fresco.org
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 675 Mass Ave, Cambridge,
 * MA 02139, USA.
 */

#include <Babylon/internal/Dictionary.hh>
#include <Babylon/internal/Blocks.hh>

#include <Prague/Sys/Directory.hh>
#include <Prague/Sys/Tracer.hh>

using namespace Prague;
using namespace Babylon;

// static variables:
Dictionary             *Dictionary::my_dictionary = 0;
Dictionary::Dict_Guard  Dictionary::my_guard;
Mutex                   Dictionary::my_singleton_mutex;

namespace Babylon
{

#ifdef RC_MODULEPATH
  const std::string default_module_path=RC_MODULEPATH;
#else
  const std::string default_module_path="/usr/share/Babylon"
#endif

  std::string override_module_path("");

  void override_path(std::string p) throw (std::runtime_error)
  {
      override_module_path = p;
  }

}; // namespace

bool Dictionary::is_defined(const UCS4 uc) const throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::is_defined(...)");
    Prague::Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->is_defined(uc);
}

UCS4 Dictionary::uppercase(const UCS4 uc) const throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::uppercase(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->uppercase(uc);
}

UCS4 Dictionary::lowercase(const UCS4 uc) const throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::lowercase(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->lowercase(uc);
}

UCS4 Dictionary::titlecase(const UCS4 uc) const throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::titlecase(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->titlecase(uc);
}

bool Dictionary::is_Decimal_Digit(const UCS4 uc) const throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::is_Decimal_Digit(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->is_Decimal_Digit(uc);
}

bool Dictionary::is_Digit(const UCS4 uc) const throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::is_Digit(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->is_Digit(uc);
}

bool Dictionary::is_Numeric(const UCS4 uc) const throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::is_Numeric(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->is_Numeric(uc);
}

float Dictionary::numeric_value(const UCS4 uc) const
    throw (Undefined_Property, Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::numeric_value(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    if (!find_char(uc)->is_Numeric(uc))
    throw Undefined_Property(uc, PROP_NUMERIC_VALUE);
    return find_char(uc)->numeric_value(uc);
}

int Dictionary::dec_digit_value(const UCS4 uc) const
    throw (Undefined_Property, Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::dec_digit_value(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    if (!find_char(uc)->is_Decimal_Digit(uc))
    throw Undefined_Property(uc, PROP_DEC_DIGIT_VALUE);
    return find_char(uc)->dec_digit_value(uc);
}
    
int Dictionary::digit_value(const UCS4 uc) const
    throw (Undefined_Property, Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::digit_value(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    if (!(find_char(uc)->is_Digit(uc)))
    throw Undefined_Property(uc, PROP_DIGIT_VALUE);
    return find_char(uc)->digit_value(uc);
} 

std::string Dictionary::blockname(const UCS4 uc) const throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::blockname(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->blockname(uc);
}
    
Gen_Cat Dictionary::category(const UCS4 uc) const
    throw (Undefined_Property, Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::category(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->category(uc);
}

Can_Comb_Class Dictionary::comb_class(const UCS4 uc) const
    throw (Undefined_Property, Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::comb_class(...)");
    Can_Comb_Class result;
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    result = find_char(uc)->comb_class(uc);
    if (result == CC_MAX)
        throw Undefined_Property(uc, PROP_CHARACTER);
    return result;
}

Bidir_Props Dictionary::bidir_props(const UCS4 uc) const
    throw (Undefined_Property, Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::bidir_props(...)");
    Bidir_Props result;
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    result = find_char(uc)->bidir_props(uc);
    if (result == BIDIR_INVALID)
        throw Undefined_Property(uc, PROP_CHARACTER);
    return result;
}

Char_Decomp Dictionary::decomp_type(const UCS4 uc) const
    throw (Undefined_Property, Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::decomp_type(...)");
    Char_Decomp result;
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    result = find_char(uc)->decomp_type(uc);
    if (result == DECOMP_MAX)
        throw Undefined_Property(uc, PROP_CHARACTER);
    return result;
}

UTF32_string Dictionary::decompose(const UCS4 uc) const
    throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::decompose(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->decompose(uc);
}

bool Dictionary::exclude_from_composition(const UCS4 uc) const
    throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::exclude_from_composition(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->exclude_from_composition(uc);
}

UCS4 Dictionary::compose(const UCS4 starter, const UCS4 last) const
    throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::compose(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(starter)->compose(starter, last);
}
    
bool Dictionary::must_mirror(const UCS4 uc) const
    throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::must_mirror(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->must_mirror(uc);
}

EA_Width Dictionary::EA_width(const UCS4 uc) const
    throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::EA_width(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->EA_width(uc);
}

Line_Break Dictionary::linebreak(const UCS4 uc) const
    throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::linebreak(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->linebreak(uc);
}

// Properties:
bool Dictionary::is_White_Space(const UCS4 uc) const
    throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::is_White_space(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->is_White_Space(uc);
}

bool Dictionary::is_Bidi_Control(const UCS4 uc) const
    throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::is_Bidi_Control(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->is_Bidi_Control(uc);
}

bool Dictionary::is_Join_Control(const UCS4 uc) const
    throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::is_Join_Control(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->is_Join_Control(uc);
}

bool Dictionary::is_Dash(const UCS4 uc) const
    throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::is_Dash(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->is_Dash(uc);
}

bool Dictionary::is_Hyphen(const UCS4 uc) const
    throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::is_Hyphen(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->is_Hyphen(uc);
}

bool Dictionary::is_Quotation_Mark(const UCS4 uc) const
    throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::is_Quotation_Mark(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->is_Quotation_Mark(uc);
}

bool Dictionary::is_Terminal_Punctuation(const UCS4 uc) const
    throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::is_Terminal_Punctuation(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->is_Terminal_Punctuation(uc);
}

bool Dictionary::is_Other_Math(const UCS4 uc) const
    throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::is_Other_Math(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->is_Other_Math(uc);
}

bool Dictionary::is_Hex_Digit(const UCS4 uc) const
    throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::is_Hex_Digit(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->is_Hex_Digit(uc);
}

bool Dictionary::is_ASCII_Hex_Digit(const UCS4 uc) const
    throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::is_Hex_Digit(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->is_ASCII_Hex_Digit(uc);
}

bool Dictionary::is_Other_Alphabetic(const UCS4 uc) const
    throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::is_Other_Alphabetic(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->is_Other_Alphabetic(uc);
}

bool Dictionary::is_Ideographic(const UCS4 uc) const
    throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::is_Ideographic(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->is_Ideographic(uc);
}

bool Dictionary::is_Diacritic(const UCS4 uc) const
    throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::is_Diacritic(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->is_Diacritic(uc);
}

bool Dictionary::is_Extender(const UCS4 uc) const
    throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::is_Extender(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->is_Extender(uc);
}

bool Dictionary::is_Other_Lowercase(const UCS4 uc) const
    throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::is_Other_Lowercase(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->is_Other_Lowercase(uc);
}

bool Dictionary::is_Other_Uppercase(const UCS4 uc) const
    throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::is_Other_Uppercase(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->is_Other_Uppercase(uc);
}

bool Dictionary::is_Noncharacter_Code_Point(const UCS4 uc) const
    throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::is_Noncharacter_Code_Point(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->is_Noncharacter_Code_Point(uc);
}    

bool Dictionary::is_Other_Grapheme_Extend(const UCS4 uc) const
    throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::is_Other_Grapheme_Extend(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->is_Other_Grapheme_Extend(uc);
}

bool Dictionary::is_Grapheme_Link(const UCS4 uc) const
    throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::is_Grapheme_Link(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->is_Grapheme_Link(uc);
}

bool Dictionary::is_IDS_Binary_Operator(const UCS4 uc) const
    throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::is_IDS_Binary_Operator(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->is_IDS_Binary_Operator(uc);
}

bool Dictionary::is_IDS_Trinary_Operator(const UCS4 uc) const
    throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::is_IDS_Trinary_Operator(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->is_IDS_Trinary_Operator(uc);
}

bool Dictionary::is_Radical(const UCS4 uc) const
    throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::is_Radical(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->is_Radical(uc);
}

bool Dictionary::is_Unified_Ideograph(const UCS4 uc) const
    throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::is_Unified_Ideograph(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->is_Unified_Ideograph(uc);
}

bool Dictionary::is_Other_Default_Ignorable_Code_Point(const UCS4 uc) const
    throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::is_Other_Default_Ignorable_Code_Point(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->is_Other_Default_Ignorable_Code_Point(uc);
}

bool Dictionary::is_Deprecated(const UCS4 uc) const
    throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::is_Deprecated(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->is_Deprecated(uc);
}

bool Dictionary::is_Soft_Dotted(const UCS4 uc) const
    throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::is_Soft_Dotted(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->is_Soft_Dotted(uc);
}

bool Dictionary::is_Logical_Order_Exception(const UCS4 uc) const
    throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::is_Logical_Order_Exception(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->is_Logical_Order_Exception(uc);
}

bool Dictionary::is_Other_ID_Start(const UCS4 uc) const
    throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::is_Other_ID_Start(...)");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return find_char(uc)->is_Other_ID_Start(uc);
}

// Derived Properties:
bool Dictionary::is_Math(const UCS4 uc) const throw (Block_Error)
{
     return (category(uc) == CAT_Sm || is_Other_Math(uc));
}

bool Dictionary::is_Alphabetic(const UCS4 uc) const throw (Block_Error)
{
    Prague::Trace trace("Babylon::Char::is_Alphabetic()");
    Gen_Cat cat = category(uc);
    return (cat == CAT_Ll || cat == CAT_Lu || cat == CAT_Lt ||
            cat == CAT_Lm || cat == CAT_Lo || cat == CAT_Nl ||
            is_Other_Alphabetic(uc));
}

bool Dictionary::is_Lowercase(const UCS4 uc) const throw (Block_Error)
{
    return (category(uc) == CAT_Ll || is_Other_Lowercase(uc));
}

bool Dictionary::is_Uppercase(const UCS4 uc) const throw (Block_Error)
{
    return (category(uc) == CAT_Lu || is_Other_Uppercase(uc));
}

bool Dictionary::is_ID_Start(const UCS4 uc) const throw (Block_Error)
{
    Prague::Trace trace("Babylon::Char::is_ID_Start()");
    Gen_Cat cat = category(uc);
    return (cat == CAT_Lu || cat == CAT_Ll || cat == CAT_Lt ||
        cat == CAT_Lm || cat == CAT_Lo || cat == CAT_Nl ||
        is_Other_ID_Start(uc));
}

bool Dictionary::is_ID_Continue(const UCS4 uc) const throw (Block_Error)
{
    Prague::Trace trace("Babylon::Char::is_ID_Continue()");
    Gen_Cat cat = category(uc);
    return (cat != CAT_Cf && // filter out Cf characters.
        (is_ID_Start(uc) ||
         cat == CAT_Mn || cat == CAT_Mc || cat == CAT_Nd ||
         cat == CAT_Pc));
}

bool Dictionary::is_XID_Start(const UCS4 uc) const throw (Block_Error)
{
    Prague::Trace trace("Babylon::Char::is_XID_Start()");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return (is_ID_Start(uc) ^ find_char(uc)->is_XID_Start_Closure(uc));
}

bool Dictionary::is_XID_Continue(const UCS4 uc) const throw (Block_Error)
{
    Prague::Trace trace("Babylon::Char::is_XID_Continue()");
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    return (is_ID_Continue(uc) ^
        find_char(uc)->is_XID_Continue_Closure(uc));
}

bool Dictionary::is_Default_Ignorable_Code_Point(const UCS4 uc) const
    throw (Block_Error)
{
    Gen_Cat cat = category(uc);
    return ((is_Other_Default_Ignorable_Code_Point(uc) ||
         cat == CAT_Cf || cat == CAT_Cc || cat == CAT_Cs) &&
        !is_White_Space(uc));
}

bool Dictionary::is_Grapheme_Extend(const UCS4 uc) const throw (Block_Error)
{
    Gen_Cat cat = category(uc);
    return (cat == CAT_Me || cat == CAT_Mn || is_Other_Grapheme_Extend(uc));
}

bool Dictionary::is_Grapheme_Base(const UCS4 uc) const throw (Block_Error)
{
    Gen_Cat cat = category(uc);
   return ((0 <= uc && uc <= 0x10FFFF) &&
        !(cat == CAT_Cc || cat == CAT_Cf || cat == CAT_Cs ||
          cat == CAT_Co || cat == CAT_Cn || cat == CAT_Zl ||
          cat == CAT_Zp || is_Grapheme_Extend(uc)));
}

bool Dictionary::is_FC_NFKC_Closure(const UCS4 uc) const throw (Block_Error)
{
    // FIXME: Implement this!
}

bool Dictionary::is_Full_Composition_Exclusion(const UCS4 uc) const
    throw (Block_Error)
{
    if (exclude_from_composition(uc)) return 1;
    UTF32_string decomp = decompose(uc);
    if (decomp.length() == 1)
    {
    if (decomp[0] == uc) return 0; // no decomposition
    if (decomp_type(uc) == DECOMP_CANONICAL) return 1;
    return 0;
    }
    if (Dictionary::instance()->comb_class(decomp[0]) != CC_SPACING) return 1;
    return 0;
}

bool Dictionary::is_NFD_QuickCheck(const UCS4 uc) const throw (Block_Error)
{
    // FIXME: Implement this!
}

bool Dictionary::is_NFC_QuickCheck(const UCS4 uc) const throw (Block_Error)
{
    // FIXME: Implement this!
}

bool Dictionary::is_NFKD_QuickCheck(const UCS4 uc) const throw (Block_Error)
{
    // FIXME: Implement this!
}

bool Dictionary::is_NFKC_QuickCheck(const UCS4 uc) const throw (Block_Error)
{
    // FIXME: Implement this!
}

bool Dictionary::is_Expands_On_NFD(const UCS4 uc) const throw (Block_Error)
{
    // FIXME: Implement this!
}

bool Dictionary::is_Expands_On_NFC(const UCS4 uc) const throw (Block_Error)
{
    // FIXME: Implement this!
}

bool Dictionary::is_Expands_On_NFKD(const UCS4 uc) const throw (Block_Error)
{
    // FIXME: Implement this!
}

bool Dictionary::is_Expands_On_NFKC(const UCS4 uc) const throw (Block_Error)
{
    // FIXME: Implement this!
}

// Further Properties:
bool Dictionary::is_Space(const UCS4 uc) const throw (Block_Error)
{
    return category(uc) == CAT_Zs;
}

bool Dictionary::is_Punctuation(const UCS4 uc) const throw (Block_Error)
{
    Gen_Cat cat = category(uc);
    return (cat == CAT_Pc || cat == CAT_Pd || cat == CAT_Ps ||
        cat == CAT_Pe || cat == CAT_Pi || cat == CAT_Pf ||
        cat == CAT_Po);
}

bool Dictionary::is_Line_Separator(const UCS4 uc) const throw (Block_Error)
{
     return category(uc) == CAT_Zl;
}

bool Dictionary::is_Paragraph_Separator(const UCS4 uc) const
    throw (Block_Error)
{
    return category(uc) == CAT_Zp;
}

bool Dictionary::is_Currency_Symbol(const UCS4 uc) const throw (Block_Error)
{
    return category(uc) == CAT_Sc;
}

bool Dictionary::is_Bidi_Left_to_Right(const UCS4 uc) const
    throw (Block_Error)
{
    return bidir_props(uc) == BIDIR_L;
}

bool Dictionary::is_Bidi_European_Digit(const UCS4 uc) const
    throw (Block_Error)
{
    return bidir_props(uc) == BIDIR_EN;
}

bool Dictionary::is_Bidi_Eur_Num_Separator(const UCS4 uc) const
    throw (Block_Error)
{
    return bidir_props(uc) == BIDIR_ES;
}

bool Dictionary::is_Bidi_Eur_Num_Terminator(const UCS4 uc) const
    throw (Block_Error)
{
    return bidir_props(uc) == BIDIR_ET;
}

bool Dictionary::is_Bidi_Arabic_Digit(const UCS4 uc) const
    throw (Block_Error)
{
    return bidir_props(uc) == BIDIR_AN;
}

bool Dictionary::is_Bidi_Common_Separator(const UCS4 uc) const
    throw (Block_Error)
{
    return bidir_props(uc) == BIDIR_CS;
}

bool Dictionary::is_Bidi_Block_Separator(const UCS4 uc) const
    throw (Block_Error)
{
    return bidir_props(uc) == BIDIR_B;
}

bool Dictionary::is_Bidi_Segment_Separator(const UCS4 uc) const
    throw (Block_Error)
{
    return bidir_props(uc) == BIDIR_S;
}

bool Dictionary::is_Bidi_Whitespace(const UCS4 uc) const
    throw (Block_Error)
{
    return bidir_props(uc) == BIDIR_WS;
}

bool Dictionary::is_Bidi_Non_spacing_Mark(const UCS4 uc) const
    throw (Block_Error)
{
    return bidir_props(uc) == BIDIR_NSM;
}

bool Dictionary::is_Bidi_Boundary_Neutral(const UCS4 uc) const
    throw (Block_Error)
{
    return bidir_props(uc) == BIDIR_BN;
}

bool Dictionary::is_Bidi_PDF(const UCS4 uc) const throw (Block_Error)
{
    return bidir_props(uc) == BIDIR_PDF;
}

bool Dictionary::is_Bidi_Embedding_or_Override(const UCS4 uc) const
    throw (Block_Error)
{
    Bidir_Props bidi = bidir_props(uc);
    return (bidi == BIDIR_LRE || bidi == BIDIR_RLE || bidi == BIDIR_LRO ||
        bidi == BIDIR_RLO);
}

bool Dictionary::is_Bidi_Other_Neutral(const UCS4 uc) const
    throw (Block_Error)
{
    return bidir_props(uc) == BIDIR_ON;
}

bool Dictionary::is_Virama(const UCS4 uc) const throw (Block_Error)
{
    return comb_class(uc) == CC_VIRAMAS;
}

bool Dictionary::is_Printable(const UCS4 uc) const throw (Block_Error)
{
    return category(uc) != CAT_Cc;
}

bool Dictionary::is_Titlecase(const UCS4 uc) const throw (Block_Error)
{
    return category(uc) == CAT_Lt;
}

bool Dictionary::is_Private_Use(const UCS4 uc) const throw (Block_Error)
{
    return ((  0xDB80 <= uc && uc <=   0xDBFF) ||
            (  0xE000 <= uc && uc <=   0xF8FF) ||
            ( 0xF0000 <= uc && uc <=  0xFFFFF) ||
            (0x100000 <= uc && uc <= 0x10FFFF));
}

// Other functions:
UCS4 Dictionary::first_letter_of_block(const UCS4 uc) const throw ()
{
    Prague::Trace trace("Babylon::Dictionary::first_Letter_of_block(...)");
    UCS4 result = UC_MAX_DEFINED;
    if (uc >= UC_MAX_DEFINED)
    return result;

    std::vector<Data>::const_iterator b;
    Data tmp(uc, uc);
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    b = lower_bound(my_data.begin(), my_data.end(), tmp, DataLess());
    if (b->my_start <= uc && b->my_end >= uc)
    result = b->my_start;
    return result;
}

UCS4 Dictionary::last_letter_of_block(const UCS4 uc) const throw ()
{
    Prague::Trace trace("Babylon::Dictionary::last_letter_of_block(...)");
    UCS4 result = UC_MAX_DEFINED;
    if (uc >= UC_MAX_DEFINED)
    return result;

    std::vector<Data>::const_iterator b;
    Data tmp(uc, uc);
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    b = lower_bound(my_data.begin(), my_data.end(), tmp, DataLess());
    if (b->my_start <= uc && b->my_end >= uc)
    result = b->my_end;
    return result;
}

UCS4 Dictionary::start_of_next_block(const UCS4 uc) const throw ()
{
    Prague::Trace trace("Babylon::Dictionary::start_of_next_block(...)");
    UCS4 result = UC_MAX_DEFINED;
    if (uc >= UC_MAX_DEFINED)
    return result;

    std::vector<Data>::const_iterator b;
    Data tmp(uc, uc);
    Guard<RWLock, RLockTrait> guard(my_rw_lock);
    b = lower_bound(my_data.begin(), my_data.end(), tmp, DataLess()); 
    if (b != my_data.end()) {
    if (b->my_end >= uc)
        ++b;
    if (b != my_data.end())
        result = b->my_start;
    }
    return result;
}

Dictionary * Dictionary::instance()
{
    Prague::Trace trace("Babylon::Dictionary::instance()");
    // Create Dictionary just once
    Prague::Guard<Mutex> guard(my_singleton_mutex);
    if (!my_dictionary) my_dictionary = new Dictionary;
    return my_dictionary;
} // instance


UTF32_string
Dictionary::recursive_decompose(const bool compat, const UCS4 uc) const
    throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::recursive_decompose(...)");
    UTF32_string decomp(decompose(uc));

    if (uc == decomp[0] ||
    !(decomp_type(uc) == DECOMP_CANONICAL ||
      compat))
    return UTF32_string(1, uc);

    UTF32_string result;
    for (UTF32_string::const_iterator i = decomp.begin();
     i != decomp.end();
     ++i)
    result += recursive_decompose(compat, *i);

    return result;
}


Block * Dictionary::find_char(const UCS4 uc) const throw (Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::find_char(...)");
    // Gets only called after the dictionary is rlocked!

    // Binary search version:
    std::vector<Data>::iterator p = my_data.begin();
    
    // ASCII happens so often that this speeds things up a bit
    if (uc > p->my_end)
    {
    // binary search for non-ASCII characters
    ++p; // advance past ASCII
    Data tmp(uc, uc);
    p = lower_bound(p, my_data.end(), tmp, DataLess());
    }
    
    if (p == my_data.end() || p->my_start > uc) // uc belongs to no block
    return my_undef_block->get();
    
    if (p->my_block == 0) // need to dynamically load the script
    {
        try
        {
            p->my_block = new Prague::Plugin<Block>(p->my_file);
        }
        catch(const std::runtime_error &e)
    {
        // Failed to load the plugin for this block
        throw Block_Error(p->my_start, p->my_end, e.what());
    }
    }

    return p->my_block->get();
} // Dictionary::find_char


void Dictionary::update(const std::string & scanDir)
    throw (std::runtime_error, Block_Error)
{
    Prague::Trace trace("Babylon::Dictionary::update(...)");

    Guard<RWLock, WLockTrait> guard(my_rw_lock);
    clean();
    
    Prague::Directory dir(scanDir, 0);
    if (!dir.is(Prague::File::dir))
    {
    throw std::runtime_error("Babylon: \""+ dir.long_name() +
          "\" does not exist. I was looking for my modules there.");
    }

    // start scanning the directory:
    for (Prague::Directory::const_iterator dir_it = dir.begin();
     dir_it != dir.end();
     ++dir_it)
    {
    std::string name = (*dir_it)->long_name();
    
    if ( !((*dir_it)->is(Prague::Directory::reg)) )
        continue;
    
    Prague::Plugin<Block> * block;
    try
    {
        block = new Prague::Plugin<Block>(name);
    }
    catch(const std::runtime_error &e)
    {
        // block can't be loaded, so skip it
        continue;
    }
    
    UCS4 start = (*block)->first_letter();
    UCS4 end   = (*block)->last_letter();
    
    if ((*block)->is_undef_block())
    {
        if(my_undef_block == 0)
        {
        my_undef_block = block;
        // don't delete the block!
        }
        else
        delete block;
    }
    else
    {
        Data current(start, end);
        current.my_file = name;
        current.my_can_remove = 0;
        current.my_block = 0;
        
        my_data.push_back(current);
        delete block;
    }
    }
    
    std::vector<Data> (my_data).swap(my_data); // shrink vector
    sort(my_data.begin(), my_data.end(), DataLess()); // sort it

    // Sanity tests:
    if (my_undef_block == 0)
    {
    throw Block_Error(0, 0xFFFFFFFF, "No undef-block defined.");
    }

    if (my_data.size() == 0)
    {
    throw Block_Error(0, 0xFFFFFFFF, "No block defined.");
    }
} // update_dictionary


Dictionary::Dictionary()
{
    Prague::Trace trace("Babylon::Dictionary::Dictionary()");
    {
        Guard<RWLock, WLockTrait> guard(my_rw_lock);
        my_undef_block = 0;
    }
    
    if (override_module_path.size())
    update(override_module_path);
    else
        update(default_module_path);
} // Dictionary::Dictionary


Dictionary::~Dictionary()
{
    Prague::Trace trace("Babylon::Dictionary::~Dictionary()");
    Guard<RWLock, WLockTrait> guard(my_rw_lock);
    clean();
} // Dictionary::~Dictionary()


void Dictionary::clean()
{
    Prague::Trace trace("Babylon::Dictionary::clean()");
    // gets only called in writelocked functions!
    for (std::vector<Data>::const_iterator i = my_data.begin();
         i != my_data.end();
         ++i)
    if (i->my_block)
        delete i->my_block;
    
    my_data.clear();
    delete my_undef_block;
}
