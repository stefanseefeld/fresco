/*$Id: UnicodePluginGenerator.pl,v 1.7 2003/08/01 16:47:16 tobias Exp 3300-33FF.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 05 Aug 2003 17:09:49 +0200.
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
    class CJK_Compatibility3300 : public Babylon::Block
    {
      public:
        void clean() { };

        CJK_Compatibility3300() :
	    my_first_letter(0x3300),
	    my_last_letter(0x33FF)
	    // my_version="4.0" // Not yet supported!
        {
        }

        ~CJK_Compatibility3300() { }

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
	    return "CJK Compatibility";
	}

        bool is_defined(const UCS4 uc) const
        {
            return 1;
        }

        UCS4 uppercase(const UCS4 uc) const
        {
            return uc;
        }

        UCS4 lowercase(const UCS4 uc) const
        {
            return uc;
        }

        UCS4 titlecase(const UCS4 uc) const
        {
            return uc;
        }

        int dec_digit_value(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Decimal_Digit(const UCS4 uc) const
        {
            return 0;
        }

        int digit_value(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Digit(const UCS4 uc) const
        {
            return 0;
        }

        float numeric_value(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Numeric(const UCS4 uc) const
        {
            return 0;
        }

        Gen_Cat category(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CAT_MAX;
            return Babylon::Gen_Cat(CAT_So);
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
            return CJK_Compatibility3300::my_bidir[uc - my_first_letter];
        }

        Char_Decomp decomp_type(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return DECOMP_MAX;
            return Babylon::Char_Decomp(CJK_Compatibility3300::my_decomp[uc - my_first_letter]);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            Babylon::UTF32_string us;
            us.resize(2);
            us[0] = CJK_Compatibility3300::my_decompStr[uc - my_first_letter][0];
            us[1] = CJK_Compatibility3300::my_decompStr[uc - my_first_letter][1];

            switch (uc)
            {

            case 0x3300:
                us.resize(4);
                us[2u] = 0x30FCu;
                us[3u] = 0x30C8u;
                break;

            case 0x3301:
                us.resize(4);
                us[2u] = 0x30D5u;
                us[3u] = 0x30A1u;
                break;

            case 0x3302:
                us.resize(4);
                us[2u] = 0x30DAu;
                us[3u] = 0x30A2u;
                break;

            case 0x3303:
                us.resize(3);
                us[2u] = 0x30EBu;
                break;

            case 0x3304:
                us.resize(4);
                us[2u] = 0x30F3u;
                us[3u] = 0x30B0u;
                break;

            case 0x3305:
                us.resize(3);
                us[2u] = 0x30C1u;
                break;

            case 0x3306:
                us.resize(3);
                us[2u] = 0x30F3u;
                break;

            case 0x3307:
                us.resize(5);
                us[2u] = 0x30AFu;
                us[3u] = 0x30FCu;
                us[4u] = 0x30C9u;
                break;

            case 0x3308:
                us.resize(4);
                us[2u] = 0x30ABu;
                us[3u] = 0x30FCu;
                break;

            case 0x3309:
                us.resize(3);
                us[2u] = 0x30B9u;
                break;

            case 0x330A:
                us.resize(3);
                us[2u] = 0x30E0u;
                break;

            case 0x330B:
                us.resize(3);
                us[2u] = 0x30EAu;
                break;

            case 0x330C:
                us.resize(4);
                us[2u] = 0x30C3u;
                us[3u] = 0x30C8u;
                break;

            case 0x330D:
                us.resize(4);
                us[2u] = 0x30EAu;
                us[3u] = 0x30FCu;
                break;

            case 0x330E:
                us.resize(3);
                us[2u] = 0x30F3u;
                break;

            case 0x330F:
                us.resize(3);
                us[2u] = 0x30DEu;
                break;

            case 0x3311:
                us.resize(3);
                us[2u] = 0x30FCu;
                break;

            case 0x3312:
                us.resize(4);
                us[2u] = 0x30EAu;
                us[3u] = 0x30FCu;
                break;

            case 0x3313:
                us.resize(4);
                us[2u] = 0x30C0u;
                us[3u] = 0x30FCu;
                break;

            case 0x3315:
                us.resize(5);
                us[2u] = 0x30B0u;
                us[3u] = 0x30E9u;
                us[4u] = 0x30E0u;
                break;

            case 0x3316:
                us.resize(6);
                us[2u] = 0x30E1u;
                us[3u] = 0x30FCu;
                us[4u] = 0x30C8u;
                us[5u] = 0x30EBu;
                break;

            case 0x3317:
                us.resize(5);
                us[2u] = 0x30EFu;
                us[3u] = 0x30C3u;
                us[4u] = 0x30C8u;
                break;

            case 0x3318:
                us.resize(3);
                us[2u] = 0x30E0u;
                break;

            case 0x3319:
                us.resize(5);
                us[2u] = 0x30E0u;
                us[3u] = 0x30C8u;
                us[4u] = 0x30F3u;
                break;

            case 0x331A:
                us.resize(5);
                us[2u] = 0x30BCu;
                us[3u] = 0x30A4u;
                us[4u] = 0x30EDu;
                break;

            case 0x331B:
                us.resize(4);
                us[2u] = 0x30FCu;
                us[3u] = 0x30CDu;
                break;

            case 0x331C:
                us.resize(3);
                us[2u] = 0x30B9u;
                break;

            case 0x331D:
                us.resize(3);
                us[2u] = 0x30CAu;
                break;

            case 0x331E:
                us.resize(3);
                us[2u] = 0x30DDu;
                break;

            case 0x331F:
                us.resize(4);
                us[2u] = 0x30AFu;
                us[3u] = 0x30EBu;
                break;

            case 0x3320:
                us.resize(5);
                us[2u] = 0x30C1u;
                us[3u] = 0x30FCu;
                us[4u] = 0x30E0u;
                break;

            case 0x3321:
                us.resize(4);
                us[2u] = 0x30F3u;
                us[3u] = 0x30B0u;
                break;

            case 0x3322:
                us.resize(3);
                us[2u] = 0x30C1u;
                break;

            case 0x3323:
                us.resize(3);
                us[2u] = 0x30C8u;
                break;

            case 0x3324:
                us.resize(3);
                us[2u] = 0x30B9u;
                break;

            case 0x3329:
                us.resize(3);
                us[2u] = 0x30C8u;
                break;

            case 0x332A:
                us.resize(3);
                us[2u] = 0x30C4u;
                break;

            case 0x332B:
                us.resize(5);
                us[2u] = 0x30BBu;
                us[3u] = 0x30F3u;
                us[4u] = 0x30C8u;
                break;

            case 0x332C:
                us.resize(3);
                us[2u] = 0x30C4u;
                break;

            case 0x332D:
                us.resize(4);
                us[2u] = 0x30ECu;
                us[3u] = 0x30EBu;
                break;

            case 0x332E:
                us.resize(5);
                us[2u] = 0x30B9u;
                us[3u] = 0x30C8u;
                us[4u] = 0x30EBu;
                break;

            case 0x332F:
                us.resize(3);
                us[2u] = 0x30EBu;
                break;

            case 0x3332:
                us.resize(5);
                us[2u] = 0x30E9u;
                us[3u] = 0x30C3u;
                us[4u] = 0x30C9u;
                break;

            case 0x3333:
                us.resize(4);
                us[2u] = 0x30FCu;
                us[3u] = 0x30C8u;
                break;

            case 0x3334:
                us.resize(5);
                us[2u] = 0x30B7u;
                us[3u] = 0x30A7u;
                us[4u] = 0x30EBu;
                break;

            case 0x3335:
                us.resize(3);
                us[2u] = 0x30F3u;
                break;

            case 0x3336:
                us.resize(5);
                us[2u] = 0x30BFu;
                us[3u] = 0x30FCu;
                us[4u] = 0x30EBu;
                break;

            case 0x3338:
                us.resize(3);
                us[2u] = 0x30D2u;
                break;

            case 0x3339:
                us.resize(3);
                us[2u] = 0x30C4u;
                break;

            case 0x333A:
                us.resize(3);
                us[2u] = 0x30B9u;
                break;

            case 0x333B:
                us.resize(3);
                us[2u] = 0x30B8u;
                break;

            case 0x333C:
                us.resize(3);
                us[2u] = 0x30BFu;
                break;

            case 0x333D:
                us.resize(4);
                us[2u] = 0x30F3u;
                us[3u] = 0x30C8u;
                break;

            case 0x333E:
                us.resize(3);
                us[2u] = 0x30C8u;
                break;

            case 0x3340:
                us.resize(3);
                us[2u] = 0x30C9u;
                break;

            case 0x3341:
                us.resize(3);
                us[2u] = 0x30EBu;
                break;

            case 0x3342:
                us.resize(3);
                us[2u] = 0x30F3u;
                break;

            case 0x3343:
                us.resize(4);
                us[2u] = 0x30AFu;
                us[3u] = 0x30EDu;
                break;

            case 0x3344:
                us.resize(3);
                us[2u] = 0x30EBu;
                break;

            case 0x3345:
                us.resize(3);
                us[2u] = 0x30CFu;
                break;

            case 0x3346:
                us.resize(3);
                us[2u] = 0x30AFu;
                break;

            case 0x3347:
                us.resize(5);
                us[2u] = 0x30B7u;
                us[3u] = 0x30E7u;
                us[4u] = 0x30F3u;
                break;

            case 0x3348:
                us.resize(4);
                us[2u] = 0x30EDu;
                us[3u] = 0x30F3u;
                break;

            case 0x334A:
                us.resize(5);
                us[2u] = 0x30D0u;
                us[3u] = 0x30FCu;
                us[4u] = 0x30EBu;
                break;

            case 0x334C:
                us.resize(4);
                us[2u] = 0x30C8u;
                us[3u] = 0x30F3u;
                break;

            case 0x334D:
                us.resize(4);
                us[2u] = 0x30C8u;
                us[3u] = 0x30EBu;
                break;

            case 0x334E:
                us.resize(3);
                us[2u] = 0x30C9u;
                break;

            case 0x334F:
                us.resize(3);
                us[2u] = 0x30EBu;
                break;

            case 0x3350:
                us.resize(3);
                us[2u] = 0x30F3u;
                break;

            case 0x3351:
                us.resize(4);
                us[2u] = 0x30C8u;
                us[3u] = 0x30EBu;
                break;

            case 0x3353:
                us.resize(3);
                us[2u] = 0x30FCu;
                break;

            case 0x3354:
                us.resize(4);
                us[2u] = 0x30D6u;
                us[3u] = 0x30EBu;
                break;

            case 0x3356:
                us.resize(5);
                us[2u] = 0x30C8u;
                us[3u] = 0x30B2u;
                us[4u] = 0x30F3u;
                break;

            case 0x3357:
                us.resize(3);
                us[2u] = 0x30C8u;
                break;

            case 0x3362:
                us.resize(3);
                us[2u] = 0x70B9u;
                break;

            case 0x3363:
                us.resize(3);
                us[2u] = 0x70B9u;
                break;

            case 0x3364:
                us.resize(3);
                us[2u] = 0x70B9u;
                break;

            case 0x3365:
                us.resize(3);
                us[2u] = 0x70B9u;
                break;

            case 0x3366:
                us.resize(3);
                us[2u] = 0x70B9u;
                break;

            case 0x3367:
                us.resize(3);
                us[2u] = 0x70B9u;
                break;

            case 0x3368:
                us.resize(3);
                us[2u] = 0x70B9u;
                break;

            case 0x3369:
                us.resize(3);
                us[2u] = 0x70B9u;
                break;

            case 0x336A:
                us.resize(3);
                us[2u] = 0x70B9u;
                break;

            case 0x336B:
                us.resize(3);
                us[2u] = 0x70B9u;
                break;

            case 0x336C:
                us.resize(3);
                us[2u] = 0x70B9u;
                break;

            case 0x336D:
                us.resize(3);
                us[2u] = 0x70B9u;
                break;

            case 0x336E:
                us.resize(3);
                us[2u] = 0x70B9u;
                break;

            case 0x336F:
                us.resize(3);
                us[2u] = 0x70B9u;
                break;

            case 0x3370:
                us.resize(3);
                us[2u] = 0x70B9u;
                break;

            case 0x3371:
                us.resize(3);
                us[2u] = 0x0061u;
                break;

            case 0x3374:
                us.resize(3);
                us[2u] = 0x0072u;
                break;

            case 0x3378:
                us.resize(3);
                us[2u] = 0x00B2u;
                break;

            case 0x3379:
                us.resize(3);
                us[2u] = 0x00B3u;
                break;

            case 0x337F:
                us.resize(4);
                us[2u] = 0x4F1Au;
                us[3u] = 0x793Eu;
                break;

            case 0x3388:
                us.resize(3);
                us[2u] = 0x006Cu;
                break;

            case 0x3389:
                us.resize(4);
                us[2u] = 0x0061u;
                us[3u] = 0x006Cu;
                break;

            case 0x3391:
                us.resize(3);
                us[2u] = 0x007Au;
                break;

            case 0x3392:
                us.resize(3);
                us[2u] = 0x007Au;
                break;

            case 0x3393:
                us.resize(3);
                us[2u] = 0x007Au;
                break;

            case 0x3394:
                us.resize(3);
                us[2u] = 0x007Au;
                break;

            case 0x339F:
                us.resize(3);
                us[2u] = 0x00B2u;
                break;

            case 0x33A0:
                us.resize(3);
                us[2u] = 0x00B2u;
                break;

            case 0x33A2:
                us.resize(3);
                us[2u] = 0x00B2u;
                break;

            case 0x33A3:
                us.resize(3);
                us[2u] = 0x00B3u;
                break;

            case 0x33A4:
                us.resize(3);
                us[2u] = 0x00B3u;
                break;

            case 0x33A6:
                us.resize(3);
                us[2u] = 0x00B3u;
                break;

            case 0x33A7:
                us.resize(3);
                us[2u] = 0x0073u;
                break;

            case 0x33A8:
                us.resize(4);
                us[2u] = 0x0073u;
                us[3u] = 0x00B2u;
                break;

            case 0x33AA:
                us.resize(3);
                us[2u] = 0x0061u;
                break;

            case 0x33AB:
                us.resize(3);
                us[2u] = 0x0061u;
                break;

            case 0x33AC:
                us.resize(3);
                us[2u] = 0x0061u;
                break;

            case 0x33AD:
                us.resize(3);
                us[2u] = 0x0064u;
                break;

            case 0x33AE:
                us.resize(5);
                us[2u] = 0x0064u;
                us[3u] = 0x2215u;
                us[4u] = 0x0073u;
                break;

            case 0x33AF:
                us.resize(6);
                us[2u] = 0x0064u;
                us[3u] = 0x2215u;
                us[4u] = 0x0073u;
                us[5u] = 0x00B2u;
                break;

            case 0x33C2:
                us.resize(4);
                us[2u] = 0x006Du;
                us[3u] = 0x002Eu;
                break;

            case 0x33C6:
                us.resize(4);
                us[2u] = 0x006Bu;
                us[3u] = 0x0067u;
                break;

            case 0x33C7:
                us.resize(3);
                us[2u] = 0x002Eu;
                break;

            case 0x33D2:
                us.resize(3);
                us[2u] = 0x0067u;
                break;

            case 0x33D5:
                us.resize(3);
                us[2u] = 0x006Cu;
                break;

            case 0x33D6:
                us.resize(3);
                us[2u] = 0x006Cu;
                break;

            case 0x33D8:
                us.resize(4);
                us[2u] = 0x006Du;
                us[3u] = 0x002Eu;
                break;

            case 0x33D9:
                us.resize(3);
                us[2u] = 0x004Du;
                break;

            case 0x33DE:
                us.resize(3);
                us[2u] = 0x006Du;
                break;

            case 0x33DF:
                us.resize(3);
                us[2u] = 0x006Du;
                break;

            case 0x33E9:
                us.resize(3);
                us[2u] = 0x65E5u;
                break;

            case 0x33EA:
                us.resize(3);
                us[2u] = 0x65E5u;
                break;

            case 0x33EB:
                us.resize(3);
                us[2u] = 0x65E5u;
                break;

            case 0x33EC:
                us.resize(3);
                us[2u] = 0x65E5u;
                break;

            case 0x33ED:
                us.resize(3);
                us[2u] = 0x65E5u;
                break;

            case 0x33EE:
                us.resize(3);
                us[2u] = 0x65E5u;
                break;

            case 0x33EF:
                us.resize(3);
                us[2u] = 0x65E5u;
                break;

            case 0x33F0:
                us.resize(3);
                us[2u] = 0x65E5u;
                break;

            case 0x33F1:
                us.resize(3);
                us[2u] = 0x65E5u;
                break;

            case 0x33F2:
                us.resize(3);
                us[2u] = 0x65E5u;
                break;

            case 0x33F3:
                us.resize(3);
                us[2u] = 0x65E5u;
                break;

            case 0x33F4:
                us.resize(3);
                us[2u] = 0x65E5u;
                break;

            case 0x33F5:
                us.resize(3);
                us[2u] = 0x65E5u;
                break;

            case 0x33F6:
                us.resize(3);
                us[2u] = 0x65E5u;
                break;

            case 0x33F7:
                us.resize(3);
                us[2u] = 0x65E5u;
                break;

            case 0x33F8:
                us.resize(3);
                us[2u] = 0x65E5u;
                break;

            case 0x33F9:
                us.resize(3);
                us[2u] = 0x65E5u;
                break;

            case 0x33FA:
                us.resize(3);
                us[2u] = 0x65E5u;
                break;

            case 0x33FB:
                us.resize(3);
                us[2u] = 0x65E5u;
                break;

            case 0x33FC:
                us.resize(3);
                us[2u] = 0x65E5u;
                break;

            case 0x33FD:
                us.resize(3);
                us[2u] = 0x65E5u;
                break;

            case 0x33FE:
                us.resize(3);
                us[2u] = 0x65E5u;
                break;

            case 0x33FF:
                us.resize(3);
                us[2u] = 0x006Cu;
                break;
            }
            if (0x0000u == us[1])
                us.resize(1);
            return us;
        }

        bool must_mirror(const UCS4 uc) const
        {
            return 0;
        }

        Line_Break linebreak(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return LB_MAX;
            return Babylon::Line_Break(LB_ID);
    }

        EA_Width EA_width(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return EA_WIDTH_MAX;
            return Babylon::EA_Width(EA_WIDTH_W);
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
            return 0;
        }

        bool is_Hyphen(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Quotation_Mark(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Terminal_Punctuation(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Other_Math(const UCS4 uc) const
        {
            return 0;
        }

        bool is_Hex_Digit(const UCS4 uc) const
        {
            return 0;
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
            return 0;
        }

        bool is_Extender(const UCS4 uc) const
        {
            return 0;
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
            return 0;
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

        bool is_XID_Start_Closure(const UCS4 uc) const
        {
            return 0;
        }

        bool is_XID_Continue_Closure(const UCS4 uc) const
        {
            return 0;
        }

      private:
        // functions
        CJK_Compatibility3300(const CJK_Compatibility3300 &) ; // no implementaion!

	// members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const Babylon::Bidir_Props my_bidir[256];
        static const unsigned char my_decomp[256];
        static const UCS4 my_decompStr[256][2];
    }; // class CJK_Compatibility3300

    const Babylon::Bidir_Props CJK_Compatibility3300::my_bidir[] =
    {
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
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_ON, 
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_L, 
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
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_ON, BIDIR_ON, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_L, 
        BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_ON
    };

    const unsigned char CJK_Compatibility3300::my_decomp[] = {
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, DECOMP_SQUARE, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, 
        DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_COMPAT, DECOMP_SQUARE
    };

    const UCS4 CJK_Compatibility3300::my_decompStr[][2] =
    {
        { 0x000030A2u, 0x000030D1u }, { 0x000030A2u, 0x000030EBu },  // 00003300
        { 0x000030A2u, 0x000030F3u }, { 0x000030A2u, 0x000030FCu },  // 00003302
        { 0x000030A4u, 0x000030CBu }, { 0x000030A4u, 0x000030F3u },  // 00003304
        { 0x000030A6u, 0x000030A9u }, { 0x000030A8u, 0x000030B9u },  // 00003306
        { 0x000030A8u, 0x000030FCu }, { 0x000030AAu, 0x000030F3u },  // 00003308
        { 0x000030AAu, 0x000030FCu }, { 0x000030ABu, 0x000030A4u },  // 0000330A
        { 0x000030ABu, 0x000030E9u }, { 0x000030ABu, 0x000030EDu },  // 0000330C
        { 0x000030ACu, 0x000030EDu }, { 0x000030ACu, 0x000030F3u },  // 0000330E
        { 0x000030AEu, 0x000030ACu }, { 0x000030AEu, 0x000030CBu },  // 00003310
        { 0x000030ADu, 0x000030E5u }, { 0x000030AEu, 0x000030EBu },  // 00003312
        { 0x000030ADu, 0x000030EDu }, { 0x000030ADu, 0x000030EDu },  // 00003314
        { 0x000030ADu, 0x000030EDu }, { 0x000030ADu, 0x000030EDu },  // 00003316
        { 0x000030B0u, 0x000030E9u }, { 0x000030B0u, 0x000030E9u },  // 00003318
        { 0x000030AFu, 0x000030EBu }, { 0x000030AFu, 0x000030EDu },  // 0000331A
        { 0x000030B1u, 0x000030FCu }, { 0x000030B3u, 0x000030EBu },  // 0000331C
        { 0x000030B3u, 0x000030FCu }, { 0x000030B5u, 0x000030A4u },  // 0000331E
        { 0x000030B5u, 0x000030F3u }, { 0x000030B7u, 0x000030EAu },  // 00003320
        { 0x000030BBu, 0x000030F3u }, { 0x000030BBu, 0x000030F3u },  // 00003322
        { 0x000030C0u, 0x000030FCu }, { 0x000030C7u, 0x000030B7u },  // 00003324
        { 0x000030C9u, 0x000030EBu }, { 0x000030C8u, 0x000030F3u },  // 00003326
        { 0x000030CAu, 0x000030CEu }, { 0x000030CEu, 0x000030C3u },  // 00003328
        { 0x000030CFu, 0x000030A4u }, { 0x000030D1u, 0x000030FCu },  // 0000332A
        { 0x000030D1u, 0x000030FCu }, { 0x000030D0u, 0x000030FCu },  // 0000332C
        { 0x000030D4u, 0x000030A2u }, { 0x000030D4u, 0x000030AFu },  // 0000332E
        { 0x000030D4u, 0x000030B3u }, { 0x000030D3u, 0x000030EBu },  // 00003330
        { 0x000030D5u, 0x000030A1u }, { 0x000030D5u, 0x000030A3u },  // 00003332
        { 0x000030D6u, 0x000030C3u }, { 0x000030D5u, 0x000030E9u },  // 00003334
        { 0x000030D8u, 0x000030AFu }, { 0x000030DAu, 0x000030BDu },  // 00003336
        { 0x000030DAu, 0x000030CBu }, { 0x000030D8u, 0x000030EBu },  // 00003338
        { 0x000030DAu, 0x000030F3u }, { 0x000030DAu, 0x000030FCu },  // 0000333A
        { 0x000030D9u, 0x000030FCu }, { 0x000030DDu, 0x000030A4u },  // 0000333C
        { 0x000030DCu, 0x000030EBu }, { 0x000030DBu, 0x000030F3u },  // 0000333E
        { 0x000030DDu, 0x000030F3u }, { 0x000030DBu, 0x000030FCu },  // 00003340
        { 0x000030DBu, 0x000030FCu }, { 0x000030DEu, 0x000030A4u },  // 00003342
        { 0x000030DEu, 0x000030A4u }, { 0x000030DEu, 0x000030C3u },  // 00003344
        { 0x000030DEu, 0x000030EBu }, { 0x000030DEu, 0x000030F3u },  // 00003346
        { 0x000030DFu, 0x000030AFu }, { 0x000030DFu, 0x000030EAu },  // 00003348
        { 0x000030DFu, 0x000030EAu }, { 0x000030E1u, 0x000030ACu },  // 0000334A
        { 0x000030E1u, 0x000030ACu }, { 0x000030E1u, 0x000030FCu },  // 0000334C
        { 0x000030E4u, 0x000030FCu }, { 0x000030E4u, 0x000030FCu },  // 0000334E
        { 0x000030E6u, 0x000030A2u }, { 0x000030EAu, 0x000030C3u },  // 00003350
        { 0x000030EAu, 0x000030E9u }, { 0x000030EBu, 0x000030D4u },  // 00003352
        { 0x000030EBu, 0x000030FCu }, { 0x000030ECu, 0x000030E0u },  // 00003354
        { 0x000030ECu, 0x000030F3u }, { 0x000030EFu, 0x000030C3u },  // 00003356
        { 0x00000030u, 0x000070B9u }, { 0x00000031u, 0x000070B9u },  // 00003358
        { 0x00000032u, 0x000070B9u }, { 0x00000033u, 0x000070B9u },  // 0000335A
        { 0x00000034u, 0x000070B9u }, { 0x00000035u, 0x000070B9u },  // 0000335C
        { 0x00000036u, 0x000070B9u }, { 0x00000037u, 0x000070B9u },  // 0000335E
        { 0x00000038u, 0x000070B9u }, { 0x00000039u, 0x000070B9u },  // 00003360
        { 0x00000031u, 0x00000030u }, { 0x00000031u, 0x00000031u },  // 00003362
        { 0x00000031u, 0x00000032u }, { 0x00000031u, 0x00000033u },  // 00003364
        { 0x00000031u, 0x00000034u }, { 0x00000031u, 0x00000035u },  // 00003366
        { 0x00000031u, 0x00000036u }, { 0x00000031u, 0x00000037u },  // 00003368
        { 0x00000031u, 0x00000038u }, { 0x00000031u, 0x00000039u },  // 0000336A
        { 0x00000032u, 0x00000030u }, { 0x00000032u, 0x00000031u },  // 0000336C
        { 0x00000032u, 0x00000032u }, { 0x00000032u, 0x00000033u },  // 0000336E
        { 0x00000032u, 0x00000034u }, { 0x00000068u, 0x00000050u },  // 00003370
        { 0x00000064u, 0x00000061u }, { 0x00000041u, 0x00000055u },  // 00003372
        { 0x00000062u, 0x00000061u }, { 0x0000006Fu, 0x00000056u },  // 00003374
        { 0x00000070u, 0x00000063u }, { 0x00000064u, 0x0000006Du },  // 00003376
        { 0x00000064u, 0x0000006Du }, { 0x00000064u, 0x0000006Du },  // 00003378
        { 0x00000049u, 0x00000055u }, { 0x00005E73u, 0x00006210u },  // 0000337A
        { 0x0000662Du, 0x0000548Cu }, { 0x00005927u, 0x00006B63u },  // 0000337C
        { 0x0000660Eu, 0x00006CBBu }, { 0x0000682Au, 0x00005F0Fu },  // 0000337E
        { 0x00000070u, 0x00000041u }, { 0x0000006Eu, 0x00000041u },  // 00003380
        { 0x000003BCu, 0x00000041u }, { 0x0000006Du, 0x00000041u },  // 00003382
        { 0x0000006Bu, 0x00000041u }, { 0x0000004Bu, 0x00000042u },  // 00003384
        { 0x0000004Du, 0x00000042u }, { 0x00000047u, 0x00000042u },  // 00003386
        { 0x00000063u, 0x00000061u }, { 0x0000006Bu, 0x00000063u },  // 00003388
        { 0x00000070u, 0x00000046u }, { 0x0000006Eu, 0x00000046u },  // 0000338A
        { 0x000003BCu, 0x00000046u }, { 0x000003BCu, 0x00000067u },  // 0000338C
        { 0x0000006Du, 0x00000067u }, { 0x0000006Bu, 0x00000067u },  // 0000338E
        { 0x00000048u, 0x0000007Au }, { 0x0000006Bu, 0x00000048u },  // 00003390
        { 0x0000004Du, 0x00000048u }, { 0x00000047u, 0x00000048u },  // 00003392
        { 0x00000054u, 0x00000048u }, { 0x000003BCu, 0x00002113u },  // 00003394
        { 0x0000006Du, 0x00002113u }, { 0x00000064u, 0x00002113u },  // 00003396
        { 0x0000006Bu, 0x00002113u }, { 0x00000066u, 0x0000006Du },  // 00003398
        { 0x0000006Eu, 0x0000006Du }, { 0x000003BCu, 0x0000006Du },  // 0000339A
        { 0x0000006Du, 0x0000006Du }, { 0x00000063u, 0x0000006Du },  // 0000339C
        { 0x0000006Bu, 0x0000006Du }, { 0x0000006Du, 0x0000006Du },  // 0000339E
        { 0x00000063u, 0x0000006Du }, { 0x0000006Du, 0x000000B2u },  // 000033A0
        { 0x0000006Bu, 0x0000006Du }, { 0x0000006Du, 0x0000006Du },  // 000033A2
        { 0x00000063u, 0x0000006Du }, { 0x0000006Du, 0x000000B3u },  // 000033A4
        { 0x0000006Bu, 0x0000006Du }, { 0x0000006Du, 0x00002215u },  // 000033A6
        { 0x0000006Du, 0x00002215u }, { 0x00000050u, 0x00000061u },  // 000033A8
        { 0x0000006Bu, 0x00000050u }, { 0x0000004Du, 0x00000050u },  // 000033AA
        { 0x00000047u, 0x00000050u }, { 0x00000072u, 0x00000061u },  // 000033AC
        { 0x00000072u, 0x00000061u }, { 0x00000072u, 0x00000061u },  // 000033AE
        { 0x00000070u, 0x00000073u }, { 0x0000006Eu, 0x00000073u },  // 000033B0
        { 0x000003BCu, 0x00000073u }, { 0x0000006Du, 0x00000073u },  // 000033B2
        { 0x00000070u, 0x00000056u }, { 0x0000006Eu, 0x00000056u },  // 000033B4
        { 0x000003BCu, 0x00000056u }, { 0x0000006Du, 0x00000056u },  // 000033B6
        { 0x0000006Bu, 0x00000056u }, { 0x0000004Du, 0x00000056u },  // 000033B8
        { 0x00000070u, 0x00000057u }, { 0x0000006Eu, 0x00000057u },  // 000033BA
        { 0x000003BCu, 0x00000057u }, { 0x0000006Du, 0x00000057u },  // 000033BC
        { 0x0000006Bu, 0x00000057u }, { 0x0000004Du, 0x00000057u },  // 000033BE
        { 0x0000006Bu, 0x000003A9u }, { 0x0000004Du, 0x000003A9u },  // 000033C0
        { 0x00000061u, 0x0000002Eu }, { 0x00000042u, 0x00000071u },  // 000033C2
        { 0x00000063u, 0x00000063u }, { 0x00000063u, 0x00000064u },  // 000033C4
        { 0x00000043u, 0x00002215u }, { 0x00000043u, 0x0000006Fu },  // 000033C6
        { 0x00000064u, 0x00000042u }, { 0x00000047u, 0x00000079u },  // 000033C8
        { 0x00000068u, 0x00000061u }, { 0x00000048u, 0x00000050u },  // 000033CA
        { 0x00000069u, 0x0000006Eu }, { 0x0000004Bu, 0x0000004Bu },  // 000033CC
        { 0x0000004Bu, 0x0000004Du }, { 0x0000006Bu, 0x00000074u },  // 000033CE
        { 0x0000006Cu, 0x0000006Du }, { 0x0000006Cu, 0x0000006Eu },  // 000033D0
        { 0x0000006Cu, 0x0000006Fu }, { 0x0000006Cu, 0x00000078u },  // 000033D2
        { 0x0000006Du, 0x00000062u }, { 0x0000006Du, 0x00000069u },  // 000033D4
        { 0x0000006Du, 0x0000006Fu }, { 0x00000050u, 0x00000048u },  // 000033D6
        { 0x00000070u, 0x0000002Eu }, { 0x00000050u, 0x00000050u },  // 000033D8
        { 0x00000050u, 0x00000052u }, { 0x00000073u, 0x00000072u },  // 000033DA
        { 0x00000053u, 0x00000076u }, { 0x00000057u, 0x00000062u },  // 000033DC
        { 0x00000056u, 0x00002215u }, { 0x00000041u, 0x00002215u },  // 000033DE
        { 0x00000031u, 0x000065E5u }, { 0x00000032u, 0x000065E5u },  // 000033E0
        { 0x00000033u, 0x000065E5u }, { 0x00000034u, 0x000065E5u },  // 000033E2
        { 0x00000035u, 0x000065E5u }, { 0x00000036u, 0x000065E5u },  // 000033E4
        { 0x00000037u, 0x000065E5u }, { 0x00000038u, 0x000065E5u },  // 000033E6
        { 0x00000039u, 0x000065E5u }, { 0x00000031u, 0x00000030u },  // 000033E8
        { 0x00000031u, 0x00000031u }, { 0x00000031u, 0x00000032u },  // 000033EA
        { 0x00000031u, 0x00000033u }, { 0x00000031u, 0x00000034u },  // 000033EC
        { 0x00000031u, 0x00000035u }, { 0x00000031u, 0x00000036u },  // 000033EE
        { 0x00000031u, 0x00000037u }, { 0x00000031u, 0x00000038u },  // 000033F0
        { 0x00000031u, 0x00000039u }, { 0x00000032u, 0x00000030u },  // 000033F2
        { 0x00000032u, 0x00000031u }, { 0x00000032u, 0x00000032u },  // 000033F4
        { 0x00000032u, 0x00000033u }, { 0x00000032u, 0x00000034u },  // 000033F6
        { 0x00000032u, 0x00000035u }, { 0x00000032u, 0x00000036u },  // 000033F8
        { 0x00000032u, 0x00000037u }, { 0x00000032u, 0x00000038u },  // 000033FA
        { 0x00000032u, 0x00000039u }, { 0x00000033u, 0x00000030u },  // 000033FC
        { 0x00000033u, 0x00000031u }, { 0x00000067u, 0x00000061u }
    };

  }; // namespace
}; // namespace

dload(Babylon::Module::CJK_Compatibility3300);
