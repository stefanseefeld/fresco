/*$Id:
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 2003 Tobias Hunger <Tobias@fresco.org>
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

#include <Babylon/Char.hh>
#include <Prague/Sys/Path.hh>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace Babylon;

class Property
{
  public:
    virtual std::string property() = 0;
    virtual bool get(Char) = 0;
};

// Properties
class White_Space : public Property
{
  public:
    std::string property() { return std::string("White_Space"); }
    bool get(Char a) { return a.is_White_Space(); }
};

class Bidi_Control : public Property
{
  public:
    std::string property() { return std::string("Bidi_Control"); }
    bool get(Char a) { return a.is_Bidi_Control(); }
};

class Join_Control : public Property
{
  public:
    std::string property() { return std::string("Join_Control"); }
    bool get(Char a) { return a.is_Join_Control(); }
};

class Dash : public Property
{
  public:
    std::string property() { return std::string("Dash"); }
    bool get(Char a) { return a.is_Dash(); }
};

class Hyphen : public Property
{
  public:
    std::string property() { return std::string("Hyphen"); }
    bool get(Char a) { return a.is_Hyphen(); }
};

class Quotation_Mark : public Property
{
  public:
    std::string property() { return std::string("Quotation_Mark"); }
    bool get(Char a) { return a.is_Quotation_Mark(); }
};

class Terminal_Punctuation : public Property
{
  public:
    std::string property() { return std::string("Terminal_Punctuation"); }
    bool get(Char a) { return a.is_Terminal_Punctuation(); }
};

class Other_Math : public Property
{
  public:
    std::string property() { return std::string("Other_Math"); }
    bool get(Char a) { return a.is_Other_Math(); }
};

class Hex_Digit : public Property
{
  public:
    std::string property() { return std::string("Hex_Digit"); }
    bool get(Char a) { return a.is_Hex_Digit(); }
};

class ASCII_Hex_Digit : public Property
{
  public:
    std::string property() { return std::string("ASCII_Hex_Digit"); }
    bool get(Char a) { return a.is_ASCII_Hex_Digit(); }
};

class Other_Alphabetic : public Property
{
  public:
    std::string property() { return std::string("Other_Alphabetic"); }
    bool get(Char a) { return a.is_Other_Alphabetic(); }
};

class Ideographic : public Property
{
  public:
    std::string property() { return std::string("Ideographic"); }
    bool get(Char a) { return a.is_Ideographic(); }
};

class Diacritic : public Property
{
  public:
    std::string property() { return std::string("Diacritic"); }
    bool get(Char a) { return a.is_Diacritic(); }
};

class Extender : public Property
{
  public:
    std::string property() { return std::string("Extender"); }
    bool get(Char a) { return a.is_Extender(); }
};

class Other_Lowercase : public Property
{
  public:
    std::string property() { return std::string("Other_Lowercase"); }
    bool get(Char a) { return a.is_Other_Lowercase(); }
};

class Other_Uppercase : public Property
{
  public:
    std::string property() { return std::string("Other_Uppercase"); }
    bool get(Char a) { return a.is_Other_Uppercase(); }
};

class Noncharacter_Code_Point : public Property
{
  public:
    std::string property() { return std::string("Noncharacter_Code_Point"); }
    bool get(Char a) { return a.is_Noncharacter_Code_Point(); }
};

class Other_Grapheme_Extend : public Property
{
  public:
    std::string property() { return std::string("Other_Grapheme_Extend"); }
    bool get(Char a) { return a.is_Other_Grapheme_Extend(); }
};

class Grapheme_Link : public Property
{
  public:
    std::string property() { return std::string("Grapheme_Link"); }
    bool get(Char a) { return a.is_Grapheme_Link(); }
};

class IDS_Binary_Operator : public Property
{
  public:
    std::string property() { return std::string("IDS_Binary_Operator"); }
    bool get(Char a) { return a.is_IDS_Binary_Operator(); }
};

class IDS_Trinary_Operator : public Property
{
  public:
    std::string property() { return std::string("IDS_Trinary_Operator"); }
    bool get(Char a) { return a.is_IDS_Trinary_Operator(); }
};

class Radical : public Property
{
  public:
    std::string property() { return std::string("Radical"); }
    bool get(Char a) { return a.is_Radical(); }
};

class Unified_Ideograph : public Property
{
  public:
    std::string property() { return std::string("Unified_Ideograph"); }
    bool get(Char a) { return a.is_Unified_Ideograph(); }
};

class Other_Default_Ignorable_Code_Point : public Property
{
  public:
    std::string property() { return std::string("Other_Default_Ignorable_Code_Point"); }
    bool get(Char a) { return a.is_Other_Default_Ignorable_Code_Point(); }
};

class Deprecated : public Property
{
  public:
    std::string property() { return std::string("Deprecated"); }
    bool get(Char a) { return a.is_Deprecated(); }
};

class Soft_Dotted : public Property
{
  public:
    std::string property() { return std::string("Soft_Dotted"); }
    bool get(Char a) { return a.is_Soft_Dotted(); }
};

class Logical_Order_Exception : public Property
{
  public:
    std::string property() { return std::string("Logical_Order_Exception"); }
    bool get(Char a) { return a.is_Logical_Order_Exception(); }
};

class Other_ID_Start : public Property
{
  public:
    std::string property() { return std::string("Other_ID_Start"); }
    bool get(Char a) { return a.is_Other_ID_Start(); }
};

// Derived Properties
class Math : public Property
{
  public:
    std::string property() { return std::string("Math"); }
    bool get(Char a) { return a.is_Math(); }
};

class Alphabetic : public Property
{
  public:
    std::string property() { return std::string("Alphabetic"); }
    bool get(Char a) { return a.is_Alphabetic(); }
};

class Lowercase : public Property
{
  public:
    std::string property() { return std::string("Lowercase"); }
    bool get(Char a) { return a.is_Lowercase(); }
};

class Uppercase : public Property
{
  public:
    std::string property() { return std::string("Uppercase"); }
    bool get(Char a) { return a.is_Uppercase(); }
};

class ID_Start : public Property
{
  public:
    std::string property() { return std::string("ID_Start"); }
    bool get(Char a) { return a.is_ID_Start(); }
};

class ID_Continue : public Property
{
  public:
    std::string property() { return std::string("ID_Continue"); }
    bool get(Char a) { return a.is_ID_Continue(); }
};

class XID_Start : public Property
{
  public:
    std::string property() { return std::string("XID_Start"); }
    bool get(Char a) { return a.is_XID_Start(); }
};

class XID_Continue : public Property
{
  public:
    std::string property() { return std::string("XID_Continue"); }
    bool get(Char a) { return a.is_XID_Continue(); }
};

class Default_Ignorable_Code_Point : public Property
{
  public:
    std::string property() { return std::string("Default_Ignorable_Code_Point"); }
    bool get(Char a) { return a.is_Default_Ignorable_Code_Point(); }
};

class Grapheme_Extend : public Property
{
  public:
    std::string property() { return std::string("Grapheme_Extend"); }
    bool get(Char a) { return a.is_Grapheme_Extend(); }
};

class Grapheme_Base : public Property
{
  public:
    std::string property() { return std::string("Grapheme_Base"); }
    bool get(Char a) { return a.is_Grapheme_Base(); }
};

class FC_NFKC_Closure : public Property
{
  public:
    std::string property() { return std::string("FC_NFKC_Closure"); }
    bool get(Char a) { return a.is_FC_NFKC_Closure(); }
};

class Full_Composition_Exclusion : public Property
{
  public:
    std::string property() { return std::string("Full_Composition_Exclusion"); }
    bool get(Char a) { return a.is_Full_Composition_Exclusion(); }
};

class NFD_QuickCheck : public Property
{
  public:
    std::string property() { return std::string("NFD_QuickCheck"); }
    bool get(Char a) { return a.is_NFD_QuickCheck(); }
};

class NFC_QuickCheck : public Property
{
  public:
    std::string property() { return std::string("NFC_QuickCheck"); }
    bool get(Char a) { return a.is_NFC_QuickCheck(); }
};

class NFKD_QuickCheck : public Property
{
  public:
    std::string property() { return std::string("NFKD_QuickCheck"); }
    bool get(Char a) { return a.is_NFKD_QuickCheck(); }
};

class NFKC_QuickCheck : public Property
{
  public:
    std::string property() { return std::string("NFKC_QuickCheck"); }
    bool get(Char a) { return a.is_NFKC_QuickCheck(); }
};

class Expands_On_NFD : public Property
{
  public:
    std::string property() { return std::string("Expands_On_NFD"); }
    bool get(Char a) { return a.is_Expands_On_NFD(); }
};

class Expands_On_NFC : public Property
{
  public:
    std::string property() { return std::string("Expands_On_NFC"); }
    bool get(Char a) { return a.is_Expands_On_NFC(); }
};

class Expands_On_NFKD : public Property
{
  public:
    std::string property() { return std::string("Expands_On_NFKD"); }
    bool get(Char a) { return a.is_Expands_On_NFKD(); }
};

class Expands_On_NFKC : public Property
{
  public:
    std::string property() { return std::string("Expands_On_NFKC"); }
    bool get(Char a) { return a.is_Expands_On_NFKC(); }
};

// Further Properties
class Space : public Property
{
  public:
    std::string property() { return std::string("Space"); }
    bool get(Char a) { return a.is_Space(); }
};

class Punctuation : public Property
{
  public:
    std::string property() { return std::string("Punctuation"); }
    bool get(Char a) { return a.is_Punctuation(); }
};

class Line_Separator : public Property
{
  public:
    std::string property() { return std::string("Line_Separator"); }
    bool get(Char a) { return a.is_Line_Separator(); }
};

class Paragraph_Separator : public Property
{
  public:
    std::string property() { return std::string("Paragraph_Separator"); }
    bool get(Char a) { return a.is_Paragraph_Separator(); }
};

class Currency_Symbol : public Property
{
  public:
    std::string property() { return std::string("Currency_Symbol"); }
    bool get(Char a) { return a.is_Currency_Symbol(); }
};

class Bidi_Left_to_Right : public Property
{
  public:
    std::string property() { return std::string("Bidi_Left_to_Right"); }
    bool get(Char a) { return a.is_Bidi_Left_to_Right(); }
};

class Bidi_European_Digit : public Property
{
  public:
    std::string property() { return std::string("Bidi_European_Digit"); }
    bool get(Char a) { return a.is_Bidi_European_Digit(); }
};

class Bidi_Eur_Num_Separator : public Property
{
  public:
    std::string property() { return std::string("Bidi_Eur_Num_Separator"); }
    bool get(Char a) { return a.is_Bidi_Eur_Num_Separator(); }
};

class Bidi_Eur_Num_Terminator : public Property
{
  public:
    std::string property() { return std::string("Bidi_Eur_Num_Terminator"); }
    bool get(Char a) { return a.is_Bidi_Eur_Num_Terminator(); }
};

class Bidi_Arabic_Digit : public Property
{
  public:
    std::string property() { return std::string("Bidi_Arabic_Digit"); }
    bool get(Char a) { return a.is_Bidi_Arabic_Digit(); }
};

class Bidi_Common_Separator : public Property
{
  public:
    std::string property() { return std::string("Bidi_Common_Separator"); }
    bool get(Char a) { return a.is_Bidi_Common_Separator(); }
};

class Bidi_Block_Separator : public Property
{
  public:
    std::string property() { return std::string("Bidi_Block_Separator"); }
    bool get(Char a) { return a.is_Bidi_Block_Separator(); }
};

class Bidi_Segment_Separator : public Property
{
  public:
    std::string property() { return std::string("Bidi_Segment_Separator"); }
    bool get(Char a) { return a.is_Bidi_Segment_Separator(); }
};

class Bidi_Whitespace : public Property
{
  public:
    std::string property() { return std::string("Bidi_Whitespace"); }
    bool get(Char a) { return a.is_Bidi_Whitespace(); }
};

class Bidi_Non_spacing_Mark : public Property
{
  public:
    std::string property() { return std::string("Bidi_Non_spacing_Mark"); }
    bool get(Char a) { return a.is_Bidi_Non_spacing_Mark(); }
};

class Bidi_Boundary_Neutral : public Property
{
  public:
    std::string property() { return std::string("Bidi_Boundary_Neutral"); }
    bool get(Char a) { return a.is_Bidi_Boundary_Neutral(); }
};

class Bidi_PDF : public Property
{
  public:
    std::string property() { return std::string("Bidi_PDF"); }
    bool get(Char a) { return a.is_Bidi_PDF(); }
};

class Bidi_Embedding_or_Override : public Property
{
  public:
    std::string property() { return std::string("Bidi_Embedding_or_Override"); }
    bool get(Char a) { return a.is_Bidi_Embedding_or_Override(); }
};

class Bidi_Other_Neutral : public Property
{
  public:
    std::string property() { return std::string("Bidi_Other_Neutral"); }
    bool get(Char a) { return a.is_Bidi_Other_Neutral(); }
};

class Virama : public Property
{
  public:
    std::string property() { return std::string("Virama"); }
    bool get(Char a) { return a.is_Virama(); }
};

class Printable : public Property
{
  public:
    std::string property() { return std::string("Printable"); }
    bool get(Char a) { return a.is_Printable(); }
};

class Titlecase : public Property
{
  public:
    std::string property() { return std::string("Titlecase"); }
    bool get(Char a) { return a.is_Titlecase(); }
};

class Private_Use : public Property
{
  public:
    std::string property() { return std::string("Private_Use"); }
    bool get(Char a) { return a.is_Private_Use(); }
};

Property * get_property(const std::string & p)
{
    // Properties
    if (p == "White_Space") return new White_Space();
    if (p == "Bidi_Control") return new Bidi_Control();
    if (p == "Join_Control") return new Join_Control();
    if (p == "Dash") return new Dash();
    if (p == "Hyphen") return new Hyphen();
    if (p == "Quotation_Mark") return new Quotation_Mark();
    if (p == "Terminal_Punctuation") return new Terminal_Punctuation();
    if (p == "Other_Math") return new Other_Math();
    if (p == "Hex_Digit") return new Hex_Digit();
    if (p == "ASCII_Hex_Digit") return new ASCII_Hex_Digit();
    if (p == "Other_Alphabetic") return new Other_Alphabetic();
    if (p == "Ideographic") return new Ideographic();
    if (p == "Diacritic") return new Diacritic();
    if (p == "Extender") return new Extender();
    if (p == "Other_Lowercase") return new Other_Lowercase();
    if (p == "Other_Uppercase") return new Other_Uppercase();
    if (p == "Noncharacter_Code_Point") return new Noncharacter_Code_Point();
    if (p == "Other_Grapheme_Extend") return new Other_Grapheme_Extend();
    if (p == "Grapheme_Link") return new Grapheme_Link();
    if (p == "IDS_Binary_Operator") return new IDS_Binary_Operator();
    if (p == "IDS_Trinary_Operator") return new IDS_Trinary_Operator();
    if (p == "Radical") return new Radical();
    if (p == "Unified_Ideograph") return new Unified_Ideograph();
    if (p == "Other_Default_Ignorable_Code_Point") return new Other_Default_Ignorable_Code_Point();
    if (p == "Deprecated") return new Deprecated();
    if (p == "Soft_Dotted") return new Soft_Dotted();
    if (p == "Logical_Order_Exception") return new Logical_Order_Exception();
    if (p == "Other_ID_Start") return new Other_ID_Start();
    // Derived Properties
    if (p == "Math") return new Math();
    if (p == "Alphabetic") return new Alphabetic();
    if (p == "Lowercase") return new Lowercase();
    if (p == "Uppercase") return new Uppercase();
    if (p == "ID_Start") return new ID_Start();
    if (p == "ID_Continue") return new ID_Continue();
    if (p == "XID_Start") return new XID_Start();
    if (p == "XID_Continue") return new XID_Continue();
    if (p == "Default_Ignorable_Code_Point") return new Default_Ignorable_Code_Point();
    if (p == "Grapheme_Extend") return new Grapheme_Extend();
    if (p == "Grapheme_Base") return new Grapheme_Base();
    if (p == "FC_NFKC_Closure") return new FC_NFKC_Closure();
    if (p == "Full_Composition_Exclusion") return new Full_Composition_Exclusion();
    if (p == "NFD_QuickCheck") return new NFD_QuickCheck();
    if (p == "NFC_QuickCheck") return new NFC_QuickCheck();
    if (p == "NFKD_QuickCheck") return new NFKD_QuickCheck();
    if (p == "NFKC_QuickCheck") return new NFKC_QuickCheck();
    if (p == "Expands_On_NFD") return new Expands_On_NFD();
    if (p == "Expands_On_NFC") return new Expands_On_NFC();
    if (p == "Expands_On_NFKD") return new Expands_On_NFKD();
    if (p == "Expands_On_NFKC") return new Expands_On_NFKC();
    // Further Properties
    if (p == "Space") return new Space();
    if (p == "Punctuation") return new Punctuation();
    if (p == "Line_Separator") return new Line_Separator();
    if (p == "Paragraph_Separator") return new Paragraph_Separator();
    if (p == "Currency_Symbol") return new Currency_Symbol();
    if (p == "Bidi_Left_to_Right") return new Bidi_Left_to_Right();
    if (p == "Bidi_European_Digit") return new Bidi_European_Digit();
    if (p == "Bidi_Eur_Num_Separator") return new Bidi_Eur_Num_Separator();
    if (p == "Bidi_Eur_Num_Terminator") return new Bidi_Eur_Num_Terminator();
    if (p == "Bidi_Arabic_Digit") return new Bidi_Arabic_Digit();
    if (p == "Bidi_Common_Separator") return new Bidi_Common_Separator();
    if (p == "Bidi_Block_Separator") return new Bidi_Block_Separator();
    if (p == "Bidi_Segment_Separator") return new Bidi_Segment_Separator();
    if (p == "Bidi_Whitespace") return new Bidi_Whitespace();
    if (p == "Bidi_Non_spacing_Mark") return new Bidi_Non_spacing_Mark();
    if (p == "Bidi_Boundary_Neutral") return new Bidi_Boundary_Neutral();
    if (p == "Bidi_PDF") return new Bidi_PDF();
    if (p == "Bidi_Embedding_or_Override") return new Bidi_Embedding_or_Override();
    if (p == "Bidi_Other_Neutral") return new Bidi_Other_Neutral();
    if (p == "Virama") return new Virama();
    if (p == "Printable") return new Printable();
    if (p == "Titlecase") return new Titlecase();
    if (p == "Private_Use") return new Private_Use();
    return 0;
}

void output_char(std::ostream & out, const Char s)
{
    out.setf(std::ios::uppercase);
    out << std::hex << std::setfill('0');
    if (s.value() <= 0xFFFF)
        out << std::setw(4) << s.value();
    else if (s.value() <= 0xFFFFF)
        out << std::setw(5) << s.value();
    else if (s.value() <= 0xFFFFFF)
        out << std::setw(6) << s.value();
    else if (s.value() <= 0xFFFFFFF)
        out << std::setw(7) << s.value();
    else
        out << std::setw(8) << s.value();
}

int main(int argc, char** argv)
{
    try
    {
	std::string property_str;
	if (argc == 3)
	{
	    Babylon::override_path(std::string(argv[1]));
	    property_str = argv[2];
	}
	else if (argc == 2)
	    property_str = argv[1];
	else
	{
	    std::cerr << "Usage: " << argv[0]
		      << " [module_path] property" << std::endl;
	    exit(1);
	}
	Property * p = get_property(property_str);
	if (!p)
	{
	    std::cout << "Unknown Property!" << std::endl;
	    exit(2);
	}

	Char start(UC_NULL);
	for (Char A(UC_NULL); A.value() < 0x110000; ++A)
	    if (p->get(A))
	    {
		output_char(std::cout, A);
		std::cout << std::endl;
	    }
    }
    catch(std::runtime_error &e)
    {
	std::cout << "Caught an runtime exception: " << e.what()
		  << std::endl;
    }
    catch(std::exception &e)
    {
	std::cout << "Caught an exception: " << e.what()
		  << std::endl;
    }
    catch(...)
    {
	std::cout << "Some exception happened!" << std::endl;
    }
}
