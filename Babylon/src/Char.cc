/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999,2000 Tobias Hunger <Tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
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

#include <Babylon/String.hh>
#include <Babylon/Char.hh>

// QUERIES:

Babylon::Char Babylon::Char::uppercase() const
throw (UndefinedProperty, BlockError) {
  return Babylon::Dictionary::instance()->uppercase(my_unicode);
} // uppercase

Babylon::Char Babylon::Char::lowercase() const
throw (UndefinedProperty, BlockError) {
  return Babylon::Dictionary::instance()->lowercase(my_unicode);
} // lowercase

Babylon::Char Babylon::Char::titlecase() const
throw (UndefinedProperty, BlockError) {
  return Babylon::Dictionary::instance()->titlecase(my_unicode);
} // titlecase

float Babylon::Char::numericValue() const
throw (UndefinedProperty, BlockError) {
  return Babylon::Dictionary::instance()->numericValue(my_unicode);
} // numericValue

int Babylon::Char::digitValue() const
throw (UndefinedProperty, BlockError) {
  return Babylon::Dictionary::instance()->digitValue(my_unicode);
} // digitValue

int Babylon::Char::decDigitValue() const
throw (UndefinedProperty, BlockError) {
  return Babylon::Dictionary::instance()->decDigitValue(my_unicode);
} // declDigitValue

string Babylon::Char::blockname() const
throw (BlockError) {
  return Babylon::Dictionary::instance()->blockname(my_unicode);
} // blockname

Babylon::Gen_Cat Babylon::Char::category() const
throw (UndefinedProperty, BlockError) {
  return Babylon::Dictionary::instance()->category(my_unicode);
} // category

Babylon::Bidir_Props Babylon::Char::direction() const
throw (UndefinedProperty, BlockError) {
  return Babylon::Dictionary::instance()->bidirProps(my_unicode);
} // direction

Babylon::Can_Comb_Class Babylon::Char::combClass() const
throw (UndefinedProperty, BlockError) {
  return Babylon::Dictionary::instance()->combClass(my_unicode);
} // CombClass

Babylon::Char_Decomp Babylon::Char::decompType() const
throw (UndefinedProperty, BlockError) {
  return Babylon::Dictionary::instance()->decompType(my_unicode);
} // decompType

Babylon::String Babylon::Char::decompose() const
throw (UndefinedProperty, BlockError) {
  return String(Babylon::Dictionary::instance()->
    decompose(my_unicode));
} // decompose

bool Babylon::Char::mustMirror() const
throw (UndefinedProperty, BlockError) {
  return Babylon::Dictionary::instance()->mustMirror(my_unicode);
} // MustMirror

Babylon::EA_Width Babylon::Char::EAWidth() const
throw (UndefinedProperty, BlockError) {
  return Babylon::Dictionary::instance()->EAWidth(my_unicode);
} // EAWidth

Babylon::Line_Break Babylon::Char::linebreak() const
throw (UndefinedProperty, BlockError) {
  return Babylon::Dictionary::instance()->linebreak(my_unicode);
} // LineBreak

// TESTS:

bool Babylon::Char::is_lowercase() const
throw (UndefinedProperty, BlockError) {
  return (this->category() == Babylon::CAT_Ll);
} // is_lowercase

bool Babylon::Char::is_uppercase() const
throw (UndefinedProperty, BlockError) {
  return (this->category() == Babylon::CAT_Lu);
} // is_uppercase

bool Babylon::Char::is_titlecase() const
throw (UndefinedProperty, BlockError) {
  return (this->category() == Babylon::CAT_Lt);
} // is_titlecase

bool Babylon::Char::is_digit() const
throw (UndefinedProperty, BlockError) {
  return (this->category() == Babylon::CAT_Nd);
} // is_digit

bool Babylon::Char::is_defined() const
throw (BlockError) {
  return Babylon::Dictionary::instance()->isDefined(my_unicode);
} // is_defined

bool Babylon::Char::is_alpha() const
throw (UndefinedProperty, BlockError) {
  Gen_Cat tmp = this->category();
  return ( (tmp >= Babylon::CAT_Lu &&
	    tmp <= Babylon::CAT_Lt) ||
	   tmp == Babylon::CAT_Lm  ||
	   tmp == Babylon::CAT_Lo );
} // is_alpha

bool Babylon::Char::is_space() const
throw (UndefinedProperty, BlockError) {
  Gen_Cat tmp = this->category();
  return (tmp >= Babylon::CAT_Zs &&
	  tmp <= Babylon::CAT_Zp);
} // is_space

bool Babylon::Char::is_control() const
throw (UndefinedProperty, BlockError) {
  Gen_Cat tmp = this->category();
  return (tmp == Babylon::CAT_Cc ||
	  tmp == Babylon::CAT_Cf ||
	  tmp == Babylon::CAT_Zl ||
	  tmp == Babylon::CAT_Zp);
} // is_control

bool Babylon::Char::is_printable() const
throw (UndefinedProperty, BlockError) {
  Gen_Cat tmp = this->category();
  return ( ! (tmp >= Babylon::CAT_Cc &&
	      tmp <= Babylon::CAT_Cn) );
} // is_print

bool Babylon::Char::is_ascii() const
throw (UndefinedProperty, BlockError) {
  return ( my_unicode < 128 );
} // is_ascii

bool Babylon::Char::is_mark() const
throw (UndefinedProperty, BlockError) {
  Gen_Cat tmp = this->category();
  return ( tmp >= Babylon::CAT_Mn &&
	   tmp <= Babylon::CAT_Me );
} // is_mark

bool Babylon::Char::is_base() const
throw (UndefinedProperty, BlockError) {
  return ( this->is_alpha() || this->is_number() || this->is_mark() );
} // is_base

bool Babylon::Char::is_punctuation() const
throw (UndefinedProperty, BlockError) {
  Gen_Cat tmp = this->category();
  return ( tmp >= Babylon::CAT_Pc &&
	   tmp <= Babylon::CAT_Po );
} // is_punctuation

bool Babylon::Char::is_number() const
throw (UndefinedProperty, BlockError) {
  Gen_Cat tmp = this->category();
  return ( tmp >= Babylon::CAT_Nd &&
	   tmp <= Babylon::CAT_Nl );
} // is_number

// TRANSFORMATIONS:
void Babylon::Char::to_lower()
throw (UndefinedProperty, BlockError) {
  *this = this->lowercase();
} // to_lowercase

void Babylon::Char::to_upper()
throw (UndefinedProperty, BlockError) {
  *this = this->uppercase();
} // to_uppercase

void Babylon::Char::to_title()
throw (UndefinedProperty, BlockError) {
  *this = this->titlecase();
} // to_titlecase

// UTILITIES
ostream & Babylon::Char::_write(ostream & out) const {
  if (my_unicode <= 0x007F)
    out << char(my_unicode);
  else {
    ios::fmtflags outflags = out.setf(ios::uppercase);
    out << "U+"
	<< hex << setfill('0') << setw(4)
	<< my_unicode;
    out.setf(outflags);
  }
  return out;
} // _write
