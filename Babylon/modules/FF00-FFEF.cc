/*$Id: UnicodePluginGenerator.pl,v 1.6 2002/05/31 23:42:14 tobias Exp FF00-FFEF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Mon, 26 May 2003 15:56:44 +0200.
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
#include <Babylon/internal/Blocks.hh>
#include <bitset>
#include <utility>


namespace Babylon
{
  namespace Module
  {
    class Halfwidth_and_Fullwidth_FormsFF00 : public Babylon::Block
    {
      public:
        void clean() { };

        Halfwidth_and_Fullwidth_FormsFF00() :
	    my_first_letter(0xFF00),
	    my_last_letter(0xFFEF)
	    // my_version="4.0" // Not yet supported!
        {
        }

        ~Halfwidth_and_Fullwidth_FormsFF00() { }

        UCS4 first_letter() const
        {
	    return my_first_letter;
	}  

	UCS4 last_letter() const
	{
	    return my_last_letter;
	}

	bool is_undef_block() const
	{
	    return 0;
	}

	// query functions:
	std::string blockname(const UCS4 uc) const
	{
	    return "Halfwidth and Fullwidth Forms";
	}

        bool is_defined(const UCS4 uc) const
        {
            return (my_is_defined.test(uc - my_first_letter));
        }

        UCS4 uppercase(const UCS4 uc) const
        {
            return Halfwidth_and_Fullwidth_FormsFF00::my_upper[uc - my_first_letter];
        }

        UCS4 lowercase(const UCS4 uc) const
        {
            return Halfwidth_and_Fullwidth_FormsFF00::my_lower[uc - my_first_letter];
        }

        UCS4 titlecase(const UCS4 uc) const
        {
            return Halfwidth_and_Fullwidth_FormsFF00::my_title[uc - my_first_letter];
        }

        int dec_digit_value(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return 0;
            switch(uc)
            {
            case 0xFF10u:
                return 0;
            case 0xFF11u:
                return 1;
            case 0xFF12u:
                return 2;
            case 0xFF13u:
                return 3;
            case 0xFF14u:
                return 4;
            case 0xFF15u:
                return 5;
            case 0xFF16u:
                return 6;
            case 0xFF17u:
                return 7;
            case 0xFF18u:
                return 8;
            case 0xFF19u:
                return 9;
            default:
                return 0;
            }
        }

        bool is_Decimal_Digit(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0xFF10u:
            case 0xFF11u:
            case 0xFF12u:
            case 0xFF13u:
            case 0xFF14u:
            case 0xFF15u:
            case 0xFF16u:
            case 0xFF17u:
            case 0xFF18u:
            case 0xFF19u:
                return 1;
            default:
                return 0;
            }
        }

        int digit_value(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return 0;
            switch(uc)
            {
            case 0xFF10u:
                return 0;
            case 0xFF11u:
                return 1;
            case 0xFF12u:
                return 2;
            case 0xFF13u:
                return 3;
            case 0xFF14u:
                return 4;
            case 0xFF15u:
                return 5;
            case 0xFF16u:
                return 6;
            case 0xFF17u:
                return 7;
            case 0xFF18u:
                return 8;
            case 0xFF19u:
                return 9;
            default:
                return 0;
            }
        }

        bool is_Digit(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0xFF10u:
            case 0xFF11u:
            case 0xFF12u:
            case 0xFF13u:
            case 0xFF14u:
            case 0xFF15u:
            case 0xFF16u:
            case 0xFF17u:
            case 0xFF18u:
            case 0xFF19u:
                return 1;
            default:
                return 0;
            }
        }

        float numeric_value(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return 0;
            switch(uc)
            {
            case 0xFF10u:
                return 0.000000;
            case 0xFF11u:
                return 1.000000;
            case 0xFF12u:
                return 2.000000;
            case 0xFF13u:
                return 3.000000;
            case 0xFF14u:
                return 4.000000;
            case 0xFF15u:
                return 5.000000;
            case 0xFF16u:
                return 6.000000;
            case 0xFF17u:
                return 7.000000;
            case 0xFF18u:
                return 8.000000;
            case 0xFF19u:
                return 9.000000;
            default:
                return 0;
            }
        }

        bool is_Numeric(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0xFF10u:
            case 0xFF11u:
            case 0xFF12u:
            case 0xFF13u:
            case 0xFF14u:
            case 0xFF15u:
            case 0xFF16u:
            case 0xFF17u:
            case 0xFF18u:
            case 0xFF19u:
                return 1;
            default:
                return 0;
            }
        }

        Gen_Cat category(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CAT_MAX;
            return Babylon::Gen_Cat(Halfwidth_and_Fullwidth_FormsFF00::my_cat[uc - my_first_letter]);
        }

        Can_Comb_Class comb_class(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CC_MAX;
            return Babylon::Can_Comb_Class(0);
        }

        Bidir_Props bidir_props(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return BIDIR_INVALID;
            return Halfwidth_and_Fullwidth_FormsFF00::my_bidir[uc - my_first_letter];
        }

        Char_Decomp decomp_type(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return DECOMP_MAX;
            return Babylon::Char_Decomp(Halfwidth_and_Fullwidth_FormsFF00::my_decomp[uc - my_first_letter]);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            Babylon::UTF32_string us;
            us.resize(1);
            us[0] = Halfwidth_and_Fullwidth_FormsFF00::my_decompStr[uc - my_first_letter];
            return us;
        }

        bool must_mirror(const UCS4 uc) const
        {
            return my_mirror.test(uc - my_first_letter);
        }

        Line_Break linebreak(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return LB_MAX;
            return Babylon::Line_Break(Halfwidth_and_Fullwidth_FormsFF00::my_lb[uc - my_first_letter]);
        }

        EA_Width EA_width(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return EA_WIDTH_MAX;
            return Babylon::EA_Width(Halfwidth_and_Fullwidth_FormsFF00::my_ea[uc - my_first_letter]);
        }

        UCS4 compose(const UCS4 starter, const UCS4 last)
        {
            return 0;
        }

        bool exclude_from_composition(const UCS4 uc) const
        {
            return 0;
        }

        bool is_White_Space(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Bidi_Control(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Join_Control(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Dash(const UCS4 uc) const
        {
            return my_Dash.test(uc - my_first_letter);
        }

        bool is_Hyphen(const UCS4 uc) const
        {
            return my_Hyphen.test(uc - my_first_letter);
        }

        bool is_Quotation_Mark(const UCS4 uc) const
        {
            return my_Quotation_Mark.test(uc - my_first_letter);
        }

        bool is_Terminal_Punctuation(const UCS4 uc) const
        {
            return my_Terminal_Punctuation.test(uc - my_first_letter);
        }

        bool is_Other_Math(const UCS4 uc) const
        {
            return my_Other_Math.test(uc - my_first_letter);
        }

        bool is_Hex_Digit(const UCS4 uc) const
        {
            return my_Hex_Digit.test(uc - my_first_letter);
        }

        bool is_ASCII_Hex_Digit(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Other_Alphabetic(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Ideographic(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Diacritic(const UCS4 uc) const
        {
            return my_Diacritic.test(uc - my_first_letter);
        }

        bool is_Extender(const UCS4 uc) const
        {
            return my_Extender.test(uc - my_first_letter);
        }

        bool is_Other_Lowercase(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Other_Uppercase(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Noncharacter_Code_Point(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Other_Grapheme_Extend(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Grapheme_Link(const UCS4 uc) const
        {
            return 0;
        }

        bool is_IDS_Binary_Operator(const UCS4 uc) const
        {
            return 0;
        }

        bool is_IDS_Trinary_Operator(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Radical(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Unified_Ideograph(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Other_Default_Ignorable_Code_Point(const UCS4 uc) const
        {
            return my_Other_Default_Ignorable_Code_Point.test(uc - my_first_letter);
        }

        bool is_Deprecated(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Soft_Dotted(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Logical_Order_Exception(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Other_ID_Start(const UCS4 uc) const
        {
            return 0;
        }

      private:
        // functions
        Halfwidth_and_Fullwidth_FormsFF00(const Halfwidth_and_Fullwidth_FormsFF00 &) ; // no implementaion!

	// members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const std::bitset<240> my_is_defined;
        static const UCS4 my_upper[240];
        static const UCS4 my_lower[240];
        static const UCS4 my_title[240];
        static const unsigned char my_cat[240];
        static const Babylon::Bidir_Props my_bidir[240];
        static const unsigned char my_decomp[240];
        static const UCS4 my_decompStr[240];
        static const std::bitset<240> my_mirror;
        static const unsigned char my_lb[240];
        static const unsigned char my_ea[240];
        static const std::bitset<240> my_Dash;
        static const std::bitset<240> my_Hyphen;
        static const std::bitset<240> my_Quotation_Mark;
        static const std::bitset<240> my_Terminal_Punctuation;
        static const std::bitset<240> my_Other_Math;
        static const std::bitset<240> my_Hex_Digit;
        static const std::bitset<240> my_Diacritic;
        static const std::bitset<240> my_Extender;
        static const std::bitset<240> my_Other_Default_Ignorable_Code_Point;
    }; // class Halfwidth_and_Fullwidth_FormsFF00

    const std::bitset<240> Halfwidth_and_Fullwidth_FormsFF00::my_is_defined(std::string("011111110111111100011100111111001111110011111100011111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111110"));

    const UCS4 Halfwidth_and_Fullwidth_FormsFF00::my_upper[] =
    {
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

    const UCS4 Halfwidth_and_Fullwidth_FormsFF00::my_lower[] =
    {
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

    const UCS4 Halfwidth_and_Fullwidth_FormsFF00::my_title[] =
    {
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

    const unsigned char Halfwidth_and_Fullwidth_FormsFF00::my_cat[] =
    {
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
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ps, CAT_Sm, CAT_Pe, CAT_Sm, CAT_Ps, 
        CAT_Pe, CAT_Po, CAT_Ps, CAT_Pe, CAT_Po, CAT_Pc, CAT_Lo, CAT_Lo, 
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

    const Babylon::Bidir_Props Halfwidth_and_Fullwidth_FormsFF00::my_bidir[] =
    {
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ET, 
        BIDIR_ET, BIDIR_ET, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ET, 
        BIDIR_CS, BIDIR_ET, BIDIR_CS, BIDIR_ES, 
        BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
        BIDIR_EN, BIDIR_EN, BIDIR_EN, BIDIR_EN, 
        BIDIR_EN, BIDIR_EN, BIDIR_CS, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_ON, BIDIR_ON, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_ON, BIDIR_ON, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_ON, BIDIR_ON, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ET, BIDIR_ET, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ET, BIDIR_ET, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON
    };

    const unsigned char Halfwidth_and_Fullwidth_FormsFF00::my_decomp[] = {
        DECOMP_CANONICAL, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, 
        DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, 
        DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, 
        DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, 
        DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, 
        DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, 
        DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, 
        DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, 
        DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, 
        DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, 
        DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, 
        DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, 
        DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, 
        DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, 
        DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, 
        DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, 
        DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, 
        DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, 
        DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, 
        DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, 
        DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, 
        DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, 
        DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, 
        DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, 
        DECOMP_WIDE, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
        DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
        DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
        DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
        DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
        DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
        DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
        DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
        DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
        DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
        DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
        DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
        DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
        DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
        DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
        DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
        DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
        DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
        DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
        DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
        DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
        DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
        DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
        DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_CANONICAL, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_NARROW, DECOMP_NARROW, 
        DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_NARROW, DECOMP_NARROW, 
        DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_NARROW, DECOMP_NARROW, 
        DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
        DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_NARROW, DECOMP_NARROW, 
        DECOMP_NARROW, DECOMP_CANONICAL, DECOMP_CANONICAL, DECOMP_CANONICAL, 
        DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, 
        DECOMP_WIDE, DECOMP_WIDE, DECOMP_WIDE, DECOMP_CANONICAL, 
        DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, 
        DECOMP_NARROW, DECOMP_NARROW, DECOMP_NARROW, DECOMP_CANONICAL
    };

    const UCS4 Halfwidth_and_Fullwidth_FormsFF00::my_decompStr[] =
    {
        0x0000FF00u, 0x00000021u, 0x00000022u, 0x00000023u,  // 0000FF00
        0x00000024u, 0x00000025u, 0x00000026u, 0x00000027u,  // 0000FF04
        0x00000028u, 0x00000029u, 0x0000002Au, 0x0000002Bu,  // 0000FF08
        0x0000002Cu, 0x0000002Du, 0x0000002Eu, 0x0000002Fu,  // 0000FF0C
        0x00000030u, 0x00000031u, 0x00000032u, 0x00000033u,  // 0000FF10
        0x00000034u, 0x00000035u, 0x00000036u, 0x00000037u,  // 0000FF14
        0x00000038u, 0x00000039u, 0x0000003Au, 0x0000003Bu,  // 0000FF18
        0x0000003Cu, 0x0000003Du, 0x0000003Eu, 0x0000003Fu,  // 0000FF1C
        0x00000040u, 0x00000041u, 0x00000042u, 0x00000043u,  // 0000FF20
        0x00000044u, 0x00000045u, 0x00000046u, 0x00000047u,  // 0000FF24
        0x00000048u, 0x00000049u, 0x0000004Au, 0x0000004Bu,  // 0000FF28
        0x0000004Cu, 0x0000004Du, 0x0000004Eu, 0x0000004Fu,  // 0000FF2C
        0x00000050u, 0x00000051u, 0x00000052u, 0x00000053u,  // 0000FF30
        0x00000054u, 0x00000055u, 0x00000056u, 0x00000057u,  // 0000FF34
        0x00000058u, 0x00000059u, 0x0000005Au, 0x0000005Bu,  // 0000FF38
        0x0000005Cu, 0x0000005Du, 0x0000005Eu, 0x0000005Fu,  // 0000FF3C
        0x00000060u, 0x00000061u, 0x00000062u, 0x00000063u,  // 0000FF40
        0x00000064u, 0x00000065u, 0x00000066u, 0x00000067u,  // 0000FF44
        0x00000068u, 0x00000069u, 0x0000006Au, 0x0000006Bu,  // 0000FF48
        0x0000006Cu, 0x0000006Du, 0x0000006Eu, 0x0000006Fu,  // 0000FF4C
        0x00000070u, 0x00000071u, 0x00000072u, 0x00000073u,  // 0000FF50
        0x00000074u, 0x00000075u, 0x00000076u, 0x00000077u,  // 0000FF54
        0x00000078u, 0x00000079u, 0x0000007Au, 0x0000007Bu,  // 0000FF58
        0x0000007Cu, 0x0000007Du, 0x0000007Eu, 0x00002985u,  // 0000FF5C
        0x00002986u, 0x00003002u, 0x0000300Cu, 0x0000300Du,  // 0000FF60
        0x00003001u, 0x000030FBu, 0x000030F2u, 0x000030A1u,  // 0000FF64
        0x000030A3u, 0x000030A5u, 0x000030A7u, 0x000030A9u,  // 0000FF68
        0x000030E3u, 0x000030E5u, 0x000030E7u, 0x000030C3u,  // 0000FF6C
        0x000030FCu, 0x000030A2u, 0x000030A4u, 0x000030A6u,  // 0000FF70
        0x000030A8u, 0x000030AAu, 0x000030ABu, 0x000030ADu,  // 0000FF74
        0x000030AFu, 0x000030B1u, 0x000030B3u, 0x000030B5u,  // 0000FF78
        0x000030B7u, 0x000030B9u, 0x000030BBu, 0x000030BDu,  // 0000FF7C
        0x000030BFu, 0x000030C1u, 0x000030C4u, 0x000030C6u,  // 0000FF80
        0x000030C8u, 0x000030CAu, 0x000030CBu, 0x000030CCu,  // 0000FF84
        0x000030CDu, 0x000030CEu, 0x000030CFu, 0x000030D2u,  // 0000FF88
        0x000030D5u, 0x000030D8u, 0x000030DBu, 0x000030DEu,  // 0000FF8C
        0x000030DFu, 0x000030E0u, 0x000030E1u, 0x000030E2u,  // 0000FF90
        0x000030E4u, 0x000030E6u, 0x000030E8u, 0x000030E9u,  // 0000FF94
        0x000030EAu, 0x000030EBu, 0x000030ECu, 0x000030EDu,  // 0000FF98
        0x000030EFu, 0x000030F3u, 0x00003099u, 0x0000309Au,  // 0000FF9C
        0x00003164u, 0x00003131u, 0x00003132u, 0x00003133u,  // 0000FFA0
        0x00003134u, 0x00003135u, 0x00003136u, 0x00003137u,  // 0000FFA4
        0x00003138u, 0x00003139u, 0x0000313Au, 0x0000313Bu,  // 0000FFA8
        0x0000313Cu, 0x0000313Du, 0x0000313Eu, 0x0000313Fu,  // 0000FFAC
        0x00003140u, 0x00003141u, 0x00003142u, 0x00003143u,  // 0000FFB0
        0x00003144u, 0x00003145u, 0x00003146u, 0x00003147u,  // 0000FFB4
        0x00003148u, 0x00003149u, 0x0000314Au, 0x0000314Bu,  // 0000FFB8
        0x0000314Cu, 0x0000314Du, 0x0000314Eu, 0x0000FFBFu,  // 0000FFBC
        0x0000FFC0u, 0x0000FFC1u, 0x0000314Fu, 0x00003150u,  // 0000FFC0
        0x00003151u, 0x00003152u, 0x00003153u, 0x00003154u,  // 0000FFC4
        0x0000FFC8u, 0x0000FFC9u, 0x00003155u, 0x00003156u,  // 0000FFC8
        0x00003157u, 0x00003158u, 0x00003159u, 0x0000315Au,  // 0000FFCC
        0x0000FFD0u, 0x0000FFD1u, 0x0000315Bu, 0x0000315Cu,  // 0000FFD0
        0x0000315Du, 0x0000315Eu, 0x0000315Fu, 0x00003160u,  // 0000FFD4
        0x0000FFD8u, 0x0000FFD9u, 0x00003161u, 0x00003162u,  // 0000FFD8
        0x00003163u, 0x0000FFDDu, 0x0000FFDEu, 0x0000FFDFu,  // 0000FFDC
        0x000000A2u, 0x000000A3u, 0x000000ACu, 0x000000AFu,  // 0000FFE0
        0x000000A6u, 0x000000A5u, 0x000020A9u, 0x0000FFE7u,  // 0000FFE4
        0x00002502u, 0x00002190u, 0x00002191u, 0x00002192u,  // 0000FFE8
        0x00002193u, 0x000025A0u, 0x000025CBu, 0x0000FFEFu
    };

    const std::bitset<240> Halfwidth_and_Fullwidth_FormsFF00::my_mirror(std::string("000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001101101010000000000000000000000000000010100000000000000000000000000001010000000000000000001100000000"));

    const unsigned char Halfwidth_and_Fullwidth_FormsFF00::my_lb[] =
    {
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
        LB_ID, LB_ID, LB_ID, LB_OP, LB_ID, LB_CL, LB_ID, LB_OP, 
        LB_CL, LB_CL, LB_OP, LB_CL, LB_CL, LB_NS, LB_AL, LB_NS, 
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

    const unsigned char Halfwidth_and_Fullwidth_FormsFF00::my_ea[] =
    {
        EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
        EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
        EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
        EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
        EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
        EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
        EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
        EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
        EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
        EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
        EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
        EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
        EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
        EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
        EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
        EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
        EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
        EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
        EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
        EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
        EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
        EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
        EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
        EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
        EA_WIDTH_F, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
        EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
        EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
        EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
        EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
        EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
        EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
        EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
        EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
        EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
        EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
        EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
        EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
        EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
        EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
        EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
        EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
        EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
        EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
        EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
        EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
        EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
        EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
        EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_F, 
        EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_H, EA_WIDTH_H, 
        EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
        EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_H, EA_WIDTH_H, 
        EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
        EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_H, EA_WIDTH_H, 
        EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
        EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_H, EA_WIDTH_H, 
        EA_WIDTH_H, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
        EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
        EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, EA_WIDTH_F, 
        EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, 
        EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_H, EA_WIDTH_F
    };

    const std::bitset<240> Halfwidth_and_Fullwidth_FormsFF00::my_Dash(std::string("000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010000000000000"));

    const std::bitset<240> Halfwidth_and_Fullwidth_FormsFF00::my_Hyphen(std::string("000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000100000000000000000000000000000000000000000000000000000000000000000000000000000000000000010000000000000"));

    const std::bitset<240> Halfwidth_and_Fullwidth_FormsFF00::my_Quotation_Mark(std::string("000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010000100"));

    const std::bitset<240> Halfwidth_and_Fullwidth_FormsFF00::my_Terminal_Punctuation(std::string("000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010010000000000000000000000000000000000000000000000000000000000000000010001100000000000101000000000010"));

    const std::bitset<240> Halfwidth_and_Fullwidth_FormsFF00::my_Other_Math(std::string("000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001010000000000000000000000000000111100000000000000000000000000000000000000000001010011100000000"));

    const std::bitset<240> Halfwidth_and_Fullwidth_FormsFF00::my_Hex_Digit(std::string("000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000011111100000000000000000000000000111111000000011111111110000000000000000"));

    const std::bitset<240> Halfwidth_and_Fullwidth_FormsFF00::my_Diacritic(std::string("000000000000100000000000000000000000000000000000000000000000000000000000000000001100000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000010100000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<240> Halfwidth_and_Fullwidth_FormsFF00::my_Extender(std::string("000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<240> Halfwidth_and_Fullwidth_FormsFF00::my_Other_Default_Ignorable_Code_Point(std::string("000000000000000000000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));

  }; // namespace
}; // namespace

dload(Babylon::Module::Halfwidth_and_Fullwidth_FormsFF00);
