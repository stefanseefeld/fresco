/*$Id: UnicodePluginGenerator.pl,v 1.7 2003/08/01 16:47:16 tobias Exp 0-7F.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999-2003 Tobias Hunger <tobias@fresco.org>
 * http://www.fresco.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 05 Aug 2003 17:09:38 +0200.
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

#include <map>

namespace Babylon
{
  namespace Module
  {
    class Basic_Latin0 : public Babylon::Block
    {
      public:
        void clean() { };

        Basic_Latin0() :
	    my_first_letter(0x0),
	    my_last_letter(0x7F)
	    // my_version="4.0" // Not yet supported!
        {
            {
                my_composeMap[std::make_pair(0x0000003C, 0x00000338)] = 0x226E;
                my_composeMap[std::make_pair(0x0000003D, 0x00000338)] = 0x2260;
                my_composeMap[std::make_pair(0x0000003E, 0x00000338)] = 0x226F;
                my_composeMap[std::make_pair(0x00000041, 0x00000300)] = 0x00C0;
                my_composeMap[std::make_pair(0x00000041, 0x00000301)] = 0x00C1;
                my_composeMap[std::make_pair(0x00000041, 0x00000302)] = 0x00C2;
                my_composeMap[std::make_pair(0x00000041, 0x00000303)] = 0x00C3;
                my_composeMap[std::make_pair(0x00000041, 0x00000304)] = 0x0100;
                my_composeMap[std::make_pair(0x00000041, 0x00000306)] = 0x0102;
                my_composeMap[std::make_pair(0x00000041, 0x00000307)] = 0x0226;
                my_composeMap[std::make_pair(0x00000041, 0x00000308)] = 0x00C4;
                my_composeMap[std::make_pair(0x00000041, 0x00000309)] = 0x1EA2;
                my_composeMap[std::make_pair(0x00000041, 0x0000030A)] = 0x00C5;
                my_composeMap[std::make_pair(0x00000041, 0x0000030C)] = 0x01CD;
                my_composeMap[std::make_pair(0x00000041, 0x0000030F)] = 0x0200;
                my_composeMap[std::make_pair(0x00000041, 0x00000311)] = 0x0202;
                my_composeMap[std::make_pair(0x00000041, 0x00000323)] = 0x1EA0;
                my_composeMap[std::make_pair(0x00000041, 0x00000325)] = 0x1E00;
                my_composeMap[std::make_pair(0x00000041, 0x00000328)] = 0x0104;
                my_composeMap[std::make_pair(0x00000042, 0x00000307)] = 0x1E02;
                my_composeMap[std::make_pair(0x00000042, 0x00000323)] = 0x1E04;
                my_composeMap[std::make_pair(0x00000042, 0x00000331)] = 0x1E06;
                my_composeMap[std::make_pair(0x00000043, 0x00000301)] = 0x0106;
                my_composeMap[std::make_pair(0x00000043, 0x00000302)] = 0x0108;
                my_composeMap[std::make_pair(0x00000043, 0x00000307)] = 0x010A;
                my_composeMap[std::make_pair(0x00000043, 0x0000030C)] = 0x010C;
                my_composeMap[std::make_pair(0x00000043, 0x00000327)] = 0x00C7;
                my_composeMap[std::make_pair(0x00000044, 0x00000307)] = 0x1E0A;
                my_composeMap[std::make_pair(0x00000044, 0x0000030C)] = 0x010E;
                my_composeMap[std::make_pair(0x00000044, 0x00000323)] = 0x1E0C;
                my_composeMap[std::make_pair(0x00000044, 0x00000327)] = 0x1E10;
                my_composeMap[std::make_pair(0x00000044, 0x0000032D)] = 0x1E12;
                my_composeMap[std::make_pair(0x00000044, 0x00000331)] = 0x1E0E;
                my_composeMap[std::make_pair(0x00000045, 0x00000300)] = 0x00C8;
                my_composeMap[std::make_pair(0x00000045, 0x00000301)] = 0x00C9;
                my_composeMap[std::make_pair(0x00000045, 0x00000302)] = 0x00CA;
                my_composeMap[std::make_pair(0x00000045, 0x00000303)] = 0x1EBC;
                my_composeMap[std::make_pair(0x00000045, 0x00000304)] = 0x0112;
                my_composeMap[std::make_pair(0x00000045, 0x00000306)] = 0x0114;
                my_composeMap[std::make_pair(0x00000045, 0x00000307)] = 0x0116;
                my_composeMap[std::make_pair(0x00000045, 0x00000308)] = 0x00CB;
                my_composeMap[std::make_pair(0x00000045, 0x00000309)] = 0x1EBA;
                my_composeMap[std::make_pair(0x00000045, 0x0000030C)] = 0x011A;
                my_composeMap[std::make_pair(0x00000045, 0x0000030F)] = 0x0204;
                my_composeMap[std::make_pair(0x00000045, 0x00000311)] = 0x0206;
                my_composeMap[std::make_pair(0x00000045, 0x00000323)] = 0x1EB8;
                my_composeMap[std::make_pair(0x00000045, 0x00000327)] = 0x0228;
                my_composeMap[std::make_pair(0x00000045, 0x00000328)] = 0x0118;
                my_composeMap[std::make_pair(0x00000045, 0x0000032D)] = 0x1E18;
                my_composeMap[std::make_pair(0x00000045, 0x00000330)] = 0x1E1A;
                my_composeMap[std::make_pair(0x00000046, 0x00000307)] = 0x1E1E;
                my_composeMap[std::make_pair(0x00000047, 0x00000301)] = 0x01F4;
                my_composeMap[std::make_pair(0x00000047, 0x00000302)] = 0x011C;
                my_composeMap[std::make_pair(0x00000047, 0x00000304)] = 0x1E20;
                my_composeMap[std::make_pair(0x00000047, 0x00000306)] = 0x011E;
                my_composeMap[std::make_pair(0x00000047, 0x00000307)] = 0x0120;
                my_composeMap[std::make_pair(0x00000047, 0x0000030C)] = 0x01E6;
                my_composeMap[std::make_pair(0x00000047, 0x00000327)] = 0x0122;
                my_composeMap[std::make_pair(0x00000048, 0x00000302)] = 0x0124;
                my_composeMap[std::make_pair(0x00000048, 0x00000307)] = 0x1E22;
                my_composeMap[std::make_pair(0x00000048, 0x00000308)] = 0x1E26;
                my_composeMap[std::make_pair(0x00000048, 0x0000030C)] = 0x021E;
                my_composeMap[std::make_pair(0x00000048, 0x00000323)] = 0x1E24;
                my_composeMap[std::make_pair(0x00000048, 0x00000327)] = 0x1E28;
                my_composeMap[std::make_pair(0x00000048, 0x0000032E)] = 0x1E2A;
                my_composeMap[std::make_pair(0x00000049, 0x00000300)] = 0x00CC;
                my_composeMap[std::make_pair(0x00000049, 0x00000301)] = 0x00CD;
                my_composeMap[std::make_pair(0x00000049, 0x00000302)] = 0x00CE;
                my_composeMap[std::make_pair(0x00000049, 0x00000303)] = 0x0128;
                my_composeMap[std::make_pair(0x00000049, 0x00000304)] = 0x012A;
                my_composeMap[std::make_pair(0x00000049, 0x00000306)] = 0x012C;
                my_composeMap[std::make_pair(0x00000049, 0x00000307)] = 0x0130;
                my_composeMap[std::make_pair(0x00000049, 0x00000308)] = 0x00CF;
                my_composeMap[std::make_pair(0x00000049, 0x00000309)] = 0x1EC8;
                my_composeMap[std::make_pair(0x00000049, 0x0000030C)] = 0x01CF;
                my_composeMap[std::make_pair(0x00000049, 0x0000030F)] = 0x0208;
                my_composeMap[std::make_pair(0x00000049, 0x00000311)] = 0x020A;
                my_composeMap[std::make_pair(0x00000049, 0x00000323)] = 0x1ECA;
                my_composeMap[std::make_pair(0x00000049, 0x00000328)] = 0x012E;
                my_composeMap[std::make_pair(0x00000049, 0x00000330)] = 0x1E2C;
                my_composeMap[std::make_pair(0x0000004A, 0x00000302)] = 0x0134;
                my_composeMap[std::make_pair(0x0000004B, 0x00000301)] = 0x1E30;
                my_composeMap[std::make_pair(0x0000004B, 0x0000030C)] = 0x01E8;
                my_composeMap[std::make_pair(0x0000004B, 0x00000323)] = 0x1E32;
                my_composeMap[std::make_pair(0x0000004B, 0x00000327)] = 0x0136;
                my_composeMap[std::make_pair(0x0000004B, 0x00000331)] = 0x1E34;
                my_composeMap[std::make_pair(0x0000004C, 0x00000301)] = 0x0139;
                my_composeMap[std::make_pair(0x0000004C, 0x0000030C)] = 0x013D;
                my_composeMap[std::make_pair(0x0000004C, 0x00000323)] = 0x1E36;
                my_composeMap[std::make_pair(0x0000004C, 0x00000327)] = 0x013B;
                my_composeMap[std::make_pair(0x0000004C, 0x0000032D)] = 0x1E3C;
                my_composeMap[std::make_pair(0x0000004C, 0x00000331)] = 0x1E3A;
                my_composeMap[std::make_pair(0x0000004D, 0x00000301)] = 0x1E3E;
                my_composeMap[std::make_pair(0x0000004D, 0x00000307)] = 0x1E40;
                my_composeMap[std::make_pair(0x0000004D, 0x00000323)] = 0x1E42;
                my_composeMap[std::make_pair(0x0000004E, 0x00000300)] = 0x01F8;
                my_composeMap[std::make_pair(0x0000004E, 0x00000301)] = 0x0143;
                my_composeMap[std::make_pair(0x0000004E, 0x00000303)] = 0x00D1;
                my_composeMap[std::make_pair(0x0000004E, 0x00000307)] = 0x1E44;
                my_composeMap[std::make_pair(0x0000004E, 0x0000030C)] = 0x0147;
                my_composeMap[std::make_pair(0x0000004E, 0x00000323)] = 0x1E46;
                my_composeMap[std::make_pair(0x0000004E, 0x00000327)] = 0x0145;
                my_composeMap[std::make_pair(0x0000004E, 0x0000032D)] = 0x1E4A;
                my_composeMap[std::make_pair(0x0000004E, 0x00000331)] = 0x1E48;
                my_composeMap[std::make_pair(0x0000004F, 0x00000300)] = 0x00D2;
                my_composeMap[std::make_pair(0x0000004F, 0x00000301)] = 0x00D3;
                my_composeMap[std::make_pair(0x0000004F, 0x00000302)] = 0x00D4;
                my_composeMap[std::make_pair(0x0000004F, 0x00000303)] = 0x00D5;
                my_composeMap[std::make_pair(0x0000004F, 0x00000304)] = 0x014C;
                my_composeMap[std::make_pair(0x0000004F, 0x00000306)] = 0x014E;
                my_composeMap[std::make_pair(0x0000004F, 0x00000307)] = 0x022E;
                my_composeMap[std::make_pair(0x0000004F, 0x00000308)] = 0x00D6;
                my_composeMap[std::make_pair(0x0000004F, 0x00000309)] = 0x1ECE;
                my_composeMap[std::make_pair(0x0000004F, 0x0000030B)] = 0x0150;
                my_composeMap[std::make_pair(0x0000004F, 0x0000030C)] = 0x01D1;
                my_composeMap[std::make_pair(0x0000004F, 0x0000030F)] = 0x020C;
                my_composeMap[std::make_pair(0x0000004F, 0x00000311)] = 0x020E;
                my_composeMap[std::make_pair(0x0000004F, 0x0000031B)] = 0x01A0;
                my_composeMap[std::make_pair(0x0000004F, 0x00000323)] = 0x1ECC;
                my_composeMap[std::make_pair(0x0000004F, 0x00000328)] = 0x01EA;
                my_composeMap[std::make_pair(0x00000050, 0x00000301)] = 0x1E54;
                my_composeMap[std::make_pair(0x00000050, 0x00000307)] = 0x1E56;
                my_composeMap[std::make_pair(0x00000052, 0x00000301)] = 0x0154;
                my_composeMap[std::make_pair(0x00000052, 0x00000307)] = 0x1E58;
                my_composeMap[std::make_pair(0x00000052, 0x0000030C)] = 0x0158;
                my_composeMap[std::make_pair(0x00000052, 0x0000030F)] = 0x0210;
                my_composeMap[std::make_pair(0x00000052, 0x00000311)] = 0x0212;
                my_composeMap[std::make_pair(0x00000052, 0x00000323)] = 0x1E5A;
                my_composeMap[std::make_pair(0x00000052, 0x00000327)] = 0x0156;
                my_composeMap[std::make_pair(0x00000052, 0x00000331)] = 0x1E5E;
                my_composeMap[std::make_pair(0x00000053, 0x00000301)] = 0x015A;
                my_composeMap[std::make_pair(0x00000053, 0x00000302)] = 0x015C;
                my_composeMap[std::make_pair(0x00000053, 0x00000307)] = 0x1E60;
                my_composeMap[std::make_pair(0x00000053, 0x0000030C)] = 0x0160;
                my_composeMap[std::make_pair(0x00000053, 0x00000323)] = 0x1E62;
                my_composeMap[std::make_pair(0x00000053, 0x00000326)] = 0x0218;
                my_composeMap[std::make_pair(0x00000053, 0x00000327)] = 0x015E;
                my_composeMap[std::make_pair(0x00000054, 0x00000307)] = 0x1E6A;
                my_composeMap[std::make_pair(0x00000054, 0x0000030C)] = 0x0164;
                my_composeMap[std::make_pair(0x00000054, 0x00000323)] = 0x1E6C;
                my_composeMap[std::make_pair(0x00000054, 0x00000326)] = 0x021A;
                my_composeMap[std::make_pair(0x00000054, 0x00000327)] = 0x0162;
                my_composeMap[std::make_pair(0x00000054, 0x0000032D)] = 0x1E70;
                my_composeMap[std::make_pair(0x00000054, 0x00000331)] = 0x1E6E;
                my_composeMap[std::make_pair(0x00000055, 0x00000300)] = 0x00D9;
                my_composeMap[std::make_pair(0x00000055, 0x00000301)] = 0x00DA;
                my_composeMap[std::make_pair(0x00000055, 0x00000302)] = 0x00DB;
                my_composeMap[std::make_pair(0x00000055, 0x00000303)] = 0x0168;
                my_composeMap[std::make_pair(0x00000055, 0x00000304)] = 0x016A;
                my_composeMap[std::make_pair(0x00000055, 0x00000306)] = 0x016C;
                my_composeMap[std::make_pair(0x00000055, 0x00000308)] = 0x00DC;
                my_composeMap[std::make_pair(0x00000055, 0x00000309)] = 0x1EE6;
                my_composeMap[std::make_pair(0x00000055, 0x0000030A)] = 0x016E;
                my_composeMap[std::make_pair(0x00000055, 0x0000030B)] = 0x0170;
                my_composeMap[std::make_pair(0x00000055, 0x0000030C)] = 0x01D3;
                my_composeMap[std::make_pair(0x00000055, 0x0000030F)] = 0x0214;
                my_composeMap[std::make_pair(0x00000055, 0x00000311)] = 0x0216;
                my_composeMap[std::make_pair(0x00000055, 0x0000031B)] = 0x01AF;
                my_composeMap[std::make_pair(0x00000055, 0x00000323)] = 0x1EE4;
                my_composeMap[std::make_pair(0x00000055, 0x00000324)] = 0x1E72;
                my_composeMap[std::make_pair(0x00000055, 0x00000328)] = 0x0172;
                my_composeMap[std::make_pair(0x00000055, 0x0000032D)] = 0x1E76;
                my_composeMap[std::make_pair(0x00000055, 0x00000330)] = 0x1E74;
                my_composeMap[std::make_pair(0x00000056, 0x00000303)] = 0x1E7C;
                my_composeMap[std::make_pair(0x00000056, 0x00000323)] = 0x1E7E;
                my_composeMap[std::make_pair(0x00000057, 0x00000300)] = 0x1E80;
                my_composeMap[std::make_pair(0x00000057, 0x00000301)] = 0x1E82;
                my_composeMap[std::make_pair(0x00000057, 0x00000302)] = 0x0174;
                my_composeMap[std::make_pair(0x00000057, 0x00000307)] = 0x1E86;
                my_composeMap[std::make_pair(0x00000057, 0x00000308)] = 0x1E84;
                my_composeMap[std::make_pair(0x00000057, 0x00000323)] = 0x1E88;
                my_composeMap[std::make_pair(0x00000058, 0x00000307)] = 0x1E8A;
                my_composeMap[std::make_pair(0x00000058, 0x00000308)] = 0x1E8C;
                my_composeMap[std::make_pair(0x00000059, 0x00000300)] = 0x1EF2;
                my_composeMap[std::make_pair(0x00000059, 0x00000301)] = 0x00DD;
                my_composeMap[std::make_pair(0x00000059, 0x00000302)] = 0x0176;
                my_composeMap[std::make_pair(0x00000059, 0x00000303)] = 0x1EF8;
                my_composeMap[std::make_pair(0x00000059, 0x00000304)] = 0x0232;
                my_composeMap[std::make_pair(0x00000059, 0x00000307)] = 0x1E8E;
                my_composeMap[std::make_pair(0x00000059, 0x00000308)] = 0x0178;
                my_composeMap[std::make_pair(0x00000059, 0x00000309)] = 0x1EF6;
                my_composeMap[std::make_pair(0x00000059, 0x00000323)] = 0x1EF4;
                my_composeMap[std::make_pair(0x0000005A, 0x00000301)] = 0x0179;
                my_composeMap[std::make_pair(0x0000005A, 0x00000302)] = 0x1E90;
                my_composeMap[std::make_pair(0x0000005A, 0x00000307)] = 0x017B;
                my_composeMap[std::make_pair(0x0000005A, 0x0000030C)] = 0x017D;
                my_composeMap[std::make_pair(0x0000005A, 0x00000323)] = 0x1E92;
                my_composeMap[std::make_pair(0x0000005A, 0x00000331)] = 0x1E94;
                my_composeMap[std::make_pair(0x00000061, 0x00000300)] = 0x00E0;
                my_composeMap[std::make_pair(0x00000061, 0x00000301)] = 0x00E1;
                my_composeMap[std::make_pair(0x00000061, 0x00000302)] = 0x00E2;
                my_composeMap[std::make_pair(0x00000061, 0x00000303)] = 0x00E3;
                my_composeMap[std::make_pair(0x00000061, 0x00000304)] = 0x0101;
                my_composeMap[std::make_pair(0x00000061, 0x00000306)] = 0x0103;
                my_composeMap[std::make_pair(0x00000061, 0x00000307)] = 0x0227;
                my_composeMap[std::make_pair(0x00000061, 0x00000308)] = 0x00E4;
                my_composeMap[std::make_pair(0x00000061, 0x00000309)] = 0x1EA3;
                my_composeMap[std::make_pair(0x00000061, 0x0000030A)] = 0x00E5;
                my_composeMap[std::make_pair(0x00000061, 0x0000030C)] = 0x01CE;
                my_composeMap[std::make_pair(0x00000061, 0x0000030F)] = 0x0201;
                my_composeMap[std::make_pair(0x00000061, 0x00000311)] = 0x0203;
                my_composeMap[std::make_pair(0x00000061, 0x00000323)] = 0x1EA1;
                my_composeMap[std::make_pair(0x00000061, 0x00000325)] = 0x1E01;
                my_composeMap[std::make_pair(0x00000061, 0x00000328)] = 0x0105;
                my_composeMap[std::make_pair(0x00000062, 0x00000307)] = 0x1E03;
                my_composeMap[std::make_pair(0x00000062, 0x00000323)] = 0x1E05;
                my_composeMap[std::make_pair(0x00000062, 0x00000331)] = 0x1E07;
                my_composeMap[std::make_pair(0x00000063, 0x00000301)] = 0x0107;
                my_composeMap[std::make_pair(0x00000063, 0x00000302)] = 0x0109;
                my_composeMap[std::make_pair(0x00000063, 0x00000307)] = 0x010B;
                my_composeMap[std::make_pair(0x00000063, 0x0000030C)] = 0x010D;
                my_composeMap[std::make_pair(0x00000063, 0x00000327)] = 0x00E7;
                my_composeMap[std::make_pair(0x00000064, 0x00000307)] = 0x1E0B;
                my_composeMap[std::make_pair(0x00000064, 0x0000030C)] = 0x010F;
                my_composeMap[std::make_pair(0x00000064, 0x00000323)] = 0x1E0D;
                my_composeMap[std::make_pair(0x00000064, 0x00000327)] = 0x1E11;
                my_composeMap[std::make_pair(0x00000064, 0x0000032D)] = 0x1E13;
                my_composeMap[std::make_pair(0x00000064, 0x00000331)] = 0x1E0F;
                my_composeMap[std::make_pair(0x00000065, 0x00000300)] = 0x00E8;
                my_composeMap[std::make_pair(0x00000065, 0x00000301)] = 0x00E9;
                my_composeMap[std::make_pair(0x00000065, 0x00000302)] = 0x00EA;
                my_composeMap[std::make_pair(0x00000065, 0x00000303)] = 0x1EBD;
                my_composeMap[std::make_pair(0x00000065, 0x00000304)] = 0x0113;
                my_composeMap[std::make_pair(0x00000065, 0x00000306)] = 0x0115;
                my_composeMap[std::make_pair(0x00000065, 0x00000307)] = 0x0117;
                my_composeMap[std::make_pair(0x00000065, 0x00000308)] = 0x00EB;
                my_composeMap[std::make_pair(0x00000065, 0x00000309)] = 0x1EBB;
                my_composeMap[std::make_pair(0x00000065, 0x0000030C)] = 0x011B;
                my_composeMap[std::make_pair(0x00000065, 0x0000030F)] = 0x0205;
                my_composeMap[std::make_pair(0x00000065, 0x00000311)] = 0x0207;
                my_composeMap[std::make_pair(0x00000065, 0x00000323)] = 0x1EB9;
                my_composeMap[std::make_pair(0x00000065, 0x00000327)] = 0x0229;
                my_composeMap[std::make_pair(0x00000065, 0x00000328)] = 0x0119;
                my_composeMap[std::make_pair(0x00000065, 0x0000032D)] = 0x1E19;
                my_composeMap[std::make_pair(0x00000065, 0x00000330)] = 0x1E1B;
                my_composeMap[std::make_pair(0x00000066, 0x00000307)] = 0x1E1F;
                my_composeMap[std::make_pair(0x00000067, 0x00000301)] = 0x01F5;
                my_composeMap[std::make_pair(0x00000067, 0x00000302)] = 0x011D;
                my_composeMap[std::make_pair(0x00000067, 0x00000304)] = 0x1E21;
                my_composeMap[std::make_pair(0x00000067, 0x00000306)] = 0x011F;
                my_composeMap[std::make_pair(0x00000067, 0x00000307)] = 0x0121;
                my_composeMap[std::make_pair(0x00000067, 0x0000030C)] = 0x01E7;
                my_composeMap[std::make_pair(0x00000067, 0x00000327)] = 0x0123;
                my_composeMap[std::make_pair(0x00000068, 0x00000302)] = 0x0125;
                my_composeMap[std::make_pair(0x00000068, 0x00000307)] = 0x1E23;
                my_composeMap[std::make_pair(0x00000068, 0x00000308)] = 0x1E27;
                my_composeMap[std::make_pair(0x00000068, 0x0000030C)] = 0x021F;
                my_composeMap[std::make_pair(0x00000068, 0x00000323)] = 0x1E25;
                my_composeMap[std::make_pair(0x00000068, 0x00000327)] = 0x1E29;
                my_composeMap[std::make_pair(0x00000068, 0x0000032E)] = 0x1E2B;
                my_composeMap[std::make_pair(0x00000068, 0x00000331)] = 0x1E96;
                my_composeMap[std::make_pair(0x00000069, 0x00000300)] = 0x00EC;
                my_composeMap[std::make_pair(0x00000069, 0x00000301)] = 0x00ED;
                my_composeMap[std::make_pair(0x00000069, 0x00000302)] = 0x00EE;
                my_composeMap[std::make_pair(0x00000069, 0x00000303)] = 0x0129;
                my_composeMap[std::make_pair(0x00000069, 0x00000304)] = 0x012B;
                my_composeMap[std::make_pair(0x00000069, 0x00000306)] = 0x012D;
                my_composeMap[std::make_pair(0x00000069, 0x00000308)] = 0x00EF;
                my_composeMap[std::make_pair(0x00000069, 0x00000309)] = 0x1EC9;
                my_composeMap[std::make_pair(0x00000069, 0x0000030C)] = 0x01D0;
                my_composeMap[std::make_pair(0x00000069, 0x0000030F)] = 0x0209;
                my_composeMap[std::make_pair(0x00000069, 0x00000311)] = 0x020B;
                my_composeMap[std::make_pair(0x00000069, 0x00000323)] = 0x1ECB;
                my_composeMap[std::make_pair(0x00000069, 0x00000328)] = 0x012F;
                my_composeMap[std::make_pair(0x00000069, 0x00000330)] = 0x1E2D;
                my_composeMap[std::make_pair(0x0000006A, 0x00000302)] = 0x0135;
                my_composeMap[std::make_pair(0x0000006A, 0x0000030C)] = 0x01F0;
                my_composeMap[std::make_pair(0x0000006B, 0x00000301)] = 0x1E31;
                my_composeMap[std::make_pair(0x0000006B, 0x0000030C)] = 0x01E9;
                my_composeMap[std::make_pair(0x0000006B, 0x00000323)] = 0x1E33;
                my_composeMap[std::make_pair(0x0000006B, 0x00000327)] = 0x0137;
                my_composeMap[std::make_pair(0x0000006B, 0x00000331)] = 0x1E35;
                my_composeMap[std::make_pair(0x0000006C, 0x00000301)] = 0x013A;
                my_composeMap[std::make_pair(0x0000006C, 0x0000030C)] = 0x013E;
                my_composeMap[std::make_pair(0x0000006C, 0x00000323)] = 0x1E37;
                my_composeMap[std::make_pair(0x0000006C, 0x00000327)] = 0x013C;
                my_composeMap[std::make_pair(0x0000006C, 0x0000032D)] = 0x1E3D;
                my_composeMap[std::make_pair(0x0000006C, 0x00000331)] = 0x1E3B;
                my_composeMap[std::make_pair(0x0000006D, 0x00000301)] = 0x1E3F;
                my_composeMap[std::make_pair(0x0000006D, 0x00000307)] = 0x1E41;
                my_composeMap[std::make_pair(0x0000006D, 0x00000323)] = 0x1E43;
                my_composeMap[std::make_pair(0x0000006E, 0x00000300)] = 0x01F9;
                my_composeMap[std::make_pair(0x0000006E, 0x00000301)] = 0x0144;
                my_composeMap[std::make_pair(0x0000006E, 0x00000303)] = 0x00F1;
                my_composeMap[std::make_pair(0x0000006E, 0x00000307)] = 0x1E45;
                my_composeMap[std::make_pair(0x0000006E, 0x0000030C)] = 0x0148;
                my_composeMap[std::make_pair(0x0000006E, 0x00000323)] = 0x1E47;
                my_composeMap[std::make_pair(0x0000006E, 0x00000327)] = 0x0146;
                my_composeMap[std::make_pair(0x0000006E, 0x0000032D)] = 0x1E4B;
                my_composeMap[std::make_pair(0x0000006E, 0x00000331)] = 0x1E49;
                my_composeMap[std::make_pair(0x0000006F, 0x00000300)] = 0x00F2;
                my_composeMap[std::make_pair(0x0000006F, 0x00000301)] = 0x00F3;
                my_composeMap[std::make_pair(0x0000006F, 0x00000302)] = 0x00F4;
                my_composeMap[std::make_pair(0x0000006F, 0x00000303)] = 0x00F5;
                my_composeMap[std::make_pair(0x0000006F, 0x00000304)] = 0x014D;
                my_composeMap[std::make_pair(0x0000006F, 0x00000306)] = 0x014F;
                my_composeMap[std::make_pair(0x0000006F, 0x00000307)] = 0x022F;
                my_composeMap[std::make_pair(0x0000006F, 0x00000308)] = 0x00F6;
                my_composeMap[std::make_pair(0x0000006F, 0x00000309)] = 0x1ECF;
                my_composeMap[std::make_pair(0x0000006F, 0x0000030B)] = 0x0151;
                my_composeMap[std::make_pair(0x0000006F, 0x0000030C)] = 0x01D2;
                my_composeMap[std::make_pair(0x0000006F, 0x0000030F)] = 0x020D;
                my_composeMap[std::make_pair(0x0000006F, 0x00000311)] = 0x020F;
                my_composeMap[std::make_pair(0x0000006F, 0x0000031B)] = 0x01A1;
                my_composeMap[std::make_pair(0x0000006F, 0x00000323)] = 0x1ECD;
                my_composeMap[std::make_pair(0x0000006F, 0x00000328)] = 0x01EB;
                my_composeMap[std::make_pair(0x00000070, 0x00000301)] = 0x1E55;
                my_composeMap[std::make_pair(0x00000070, 0x00000307)] = 0x1E57;
                my_composeMap[std::make_pair(0x00000072, 0x00000301)] = 0x0155;
                my_composeMap[std::make_pair(0x00000072, 0x00000307)] = 0x1E59;
                my_composeMap[std::make_pair(0x00000072, 0x0000030C)] = 0x0159;
                my_composeMap[std::make_pair(0x00000072, 0x0000030F)] = 0x0211;
                my_composeMap[std::make_pair(0x00000072, 0x00000311)] = 0x0213;
                my_composeMap[std::make_pair(0x00000072, 0x00000323)] = 0x1E5B;
                my_composeMap[std::make_pair(0x00000072, 0x00000327)] = 0x0157;
                my_composeMap[std::make_pair(0x00000072, 0x00000331)] = 0x1E5F;
                my_composeMap[std::make_pair(0x00000073, 0x00000301)] = 0x015B;
                my_composeMap[std::make_pair(0x00000073, 0x00000302)] = 0x015D;
                my_composeMap[std::make_pair(0x00000073, 0x00000307)] = 0x1E61;
                my_composeMap[std::make_pair(0x00000073, 0x0000030C)] = 0x0161;
                my_composeMap[std::make_pair(0x00000073, 0x00000323)] = 0x1E63;
                my_composeMap[std::make_pair(0x00000073, 0x00000326)] = 0x0219;
                my_composeMap[std::make_pair(0x00000073, 0x00000327)] = 0x015F;
                my_composeMap[std::make_pair(0x00000074, 0x00000307)] = 0x1E6B;
                my_composeMap[std::make_pair(0x00000074, 0x00000308)] = 0x1E97;
                my_composeMap[std::make_pair(0x00000074, 0x0000030C)] = 0x0165;
                my_composeMap[std::make_pair(0x00000074, 0x00000323)] = 0x1E6D;
                my_composeMap[std::make_pair(0x00000074, 0x00000326)] = 0x021B;
                my_composeMap[std::make_pair(0x00000074, 0x00000327)] = 0x0163;
                my_composeMap[std::make_pair(0x00000074, 0x0000032D)] = 0x1E71;
                my_composeMap[std::make_pair(0x00000074, 0x00000331)] = 0x1E6F;
                my_composeMap[std::make_pair(0x00000075, 0x00000300)] = 0x00F9;
                my_composeMap[std::make_pair(0x00000075, 0x00000301)] = 0x00FA;
                my_composeMap[std::make_pair(0x00000075, 0x00000302)] = 0x00FB;
                my_composeMap[std::make_pair(0x00000075, 0x00000303)] = 0x0169;
                my_composeMap[std::make_pair(0x00000075, 0x00000304)] = 0x016B;
                my_composeMap[std::make_pair(0x00000075, 0x00000306)] = 0x016D;
                my_composeMap[std::make_pair(0x00000075, 0x00000308)] = 0x00FC;
                my_composeMap[std::make_pair(0x00000075, 0x00000309)] = 0x1EE7;
                my_composeMap[std::make_pair(0x00000075, 0x0000030A)] = 0x016F;
                my_composeMap[std::make_pair(0x00000075, 0x0000030B)] = 0x0171;
                my_composeMap[std::make_pair(0x00000075, 0x0000030C)] = 0x01D4;
                my_composeMap[std::make_pair(0x00000075, 0x0000030F)] = 0x0215;
                my_composeMap[std::make_pair(0x00000075, 0x00000311)] = 0x0217;
                my_composeMap[std::make_pair(0x00000075, 0x0000031B)] = 0x01B0;
                my_composeMap[std::make_pair(0x00000075, 0x00000323)] = 0x1EE5;
                my_composeMap[std::make_pair(0x00000075, 0x00000324)] = 0x1E73;
                my_composeMap[std::make_pair(0x00000075, 0x00000328)] = 0x0173;
                my_composeMap[std::make_pair(0x00000075, 0x0000032D)] = 0x1E77;
                my_composeMap[std::make_pair(0x00000075, 0x00000330)] = 0x1E75;
                my_composeMap[std::make_pair(0x00000076, 0x00000303)] = 0x1E7D;
                my_composeMap[std::make_pair(0x00000076, 0x00000323)] = 0x1E7F;
                my_composeMap[std::make_pair(0x00000077, 0x00000300)] = 0x1E81;
                my_composeMap[std::make_pair(0x00000077, 0x00000301)] = 0x1E83;
                my_composeMap[std::make_pair(0x00000077, 0x00000302)] = 0x0175;
                my_composeMap[std::make_pair(0x00000077, 0x00000307)] = 0x1E87;
                my_composeMap[std::make_pair(0x00000077, 0x00000308)] = 0x1E85;
                my_composeMap[std::make_pair(0x00000077, 0x0000030A)] = 0x1E98;
                my_composeMap[std::make_pair(0x00000077, 0x00000323)] = 0x1E89;
                my_composeMap[std::make_pair(0x00000078, 0x00000307)] = 0x1E8B;
                my_composeMap[std::make_pair(0x00000078, 0x00000308)] = 0x1E8D;
                my_composeMap[std::make_pair(0x00000079, 0x00000300)] = 0x1EF3;
                my_composeMap[std::make_pair(0x00000079, 0x00000301)] = 0x00FD;
                my_composeMap[std::make_pair(0x00000079, 0x00000302)] = 0x0177;
                my_composeMap[std::make_pair(0x00000079, 0x00000303)] = 0x1EF9;
                my_composeMap[std::make_pair(0x00000079, 0x00000304)] = 0x0233;
                my_composeMap[std::make_pair(0x00000079, 0x00000307)] = 0x1E8F;
                my_composeMap[std::make_pair(0x00000079, 0x00000308)] = 0x00FF;
                my_composeMap[std::make_pair(0x00000079, 0x00000309)] = 0x1EF7;
                my_composeMap[std::make_pair(0x00000079, 0x0000030A)] = 0x1E99;
                my_composeMap[std::make_pair(0x00000079, 0x00000323)] = 0x1EF5;
                my_composeMap[std::make_pair(0x0000007A, 0x00000301)] = 0x017A;
                my_composeMap[std::make_pair(0x0000007A, 0x00000302)] = 0x1E91;
                my_composeMap[std::make_pair(0x0000007A, 0x00000307)] = 0x017C;
                my_composeMap[std::make_pair(0x0000007A, 0x0000030C)] = 0x017E;
                my_composeMap[std::make_pair(0x0000007A, 0x00000323)] = 0x1E93;
                my_composeMap[std::make_pair(0x0000007A, 0x00000331)] = 0x1E95;
            }
        }

        ~Basic_Latin0() { }

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
	    return "Basic Latin";
	}

        bool is_defined(const UCS4 uc) const
        {
            return 1;
        }

        UCS4 uppercase(const UCS4 uc) const
        {
            return Basic_Latin0::my_upper[uc - my_first_letter];
        }

        UCS4 lowercase(const UCS4 uc) const
        {
            return Basic_Latin0::my_lower[uc - my_first_letter];
        }

        UCS4 titlecase(const UCS4 uc) const
        {
            return Basic_Latin0::my_title[uc - my_first_letter];
        }

        int dec_digit_value(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return 0;
            switch(uc)
            {
            case 0x0030u:
                return 0;
            case 0x0031u:
                return 1;
            case 0x0032u:
                return 2;
            case 0x0033u:
                return 3;
            case 0x0034u:
                return 4;
            case 0x0035u:
                return 5;
            case 0x0036u:
                return 6;
            case 0x0037u:
                return 7;
            case 0x0038u:
                return 8;
            case 0x0039u:
                return 9;
            default:
                return 0;
            }
        }

        bool is_Decimal_Digit(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x0030u:
            case 0x0031u:
            case 0x0032u:
            case 0x0033u:
            case 0x0034u:
            case 0x0035u:
            case 0x0036u:
            case 0x0037u:
            case 0x0038u:
            case 0x0039u:
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
            case 0x0030u:
                return 0;
            case 0x0031u:
                return 1;
            case 0x0032u:
                return 2;
            case 0x0033u:
                return 3;
            case 0x0034u:
                return 4;
            case 0x0035u:
                return 5;
            case 0x0036u:
                return 6;
            case 0x0037u:
                return 7;
            case 0x0038u:
                return 8;
            case 0x0039u:
                return 9;
            default:
                return 0;
            }
        }

        bool is_Digit(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x0030u:
            case 0x0031u:
            case 0x0032u:
            case 0x0033u:
            case 0x0034u:
            case 0x0035u:
            case 0x0036u:
            case 0x0037u:
            case 0x0038u:
            case 0x0039u:
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
            case 0x0030u:
                return 0.000000;
            case 0x0031u:
                return 1.000000;
            case 0x0032u:
                return 2.000000;
            case 0x0033u:
                return 3.000000;
            case 0x0034u:
                return 4.000000;
            case 0x0035u:
                return 5.000000;
            case 0x0036u:
                return 6.000000;
            case 0x0037u:
                return 7.000000;
            case 0x0038u:
                return 8.000000;
            case 0x0039u:
                return 9.000000;
            default:
                return 0;
            }
        }

        bool is_Numeric(const UCS4 uc) const
        {
            switch(uc)
            {
            case 0x0030u:
            case 0x0031u:
            case 0x0032u:
            case 0x0033u:
            case 0x0034u:
            case 0x0035u:
            case 0x0036u:
            case 0x0037u:
            case 0x0038u:
            case 0x0039u:
                return 1;
            default:
                return 0;
            }
        }

        Gen_Cat category(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return CAT_MAX;
            return Babylon::Gen_Cat(Basic_Latin0::my_cat[uc - my_first_letter]);
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
            return Basic_Latin0::my_bidir[uc - my_first_letter];
        }

        Char_Decomp decomp_type(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return DECOMP_MAX;
            return Babylon::Char_Decomp(DECOMP_CANONICAL);
        }

        UTF32_string decompose(const UCS4 uc) const
        {
            UTF32_string us;
            us.resize(1); us[0] = uc;
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
            return Babylon::Line_Break(Basic_Latin0::my_lb[uc - my_first_letter]);
        }

        EA_Width EA_width(const UCS4 uc) const
        {
            if (!is_defined(uc))
                return EA_WIDTH_MAX;
            return Babylon::EA_Width(Basic_Latin0::my_ea[uc - my_first_letter]);
        }

        UCS4 compose(const UCS4 starter, const UCS4 last)
        {
            return my_composeMap[std::make_pair(starter, last)];
        }

        bool exclude_from_composition(const UCS4 uc) const
        {
            return 0;
        }

        bool is_White_Space(const UCS4 uc) const
        {
            return my_White_Space.test(uc - my_first_letter);
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
            return my_ASCII_Hex_Digit.test(uc - my_first_letter);
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
            return my_Soft_Dotted.test(uc - my_first_letter);
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
        Basic_Latin0(const Basic_Latin0 &) ; // no implementaion!

	// members
        Babylon::UCS4 my_first_letter;
        Babylon::UCS4 my_last_letter;
        // Babylon::UCS4_string my_version;
        static const UCS4 my_upper[128];
        static const UCS4 my_lower[128];
        static const UCS4 my_title[128];
        static const unsigned char my_cat[128];
        static const Babylon::Bidir_Props my_bidir[128];
        static const std::bitset<128> my_mirror;
        static const unsigned char my_lb[128];
        static const unsigned char my_ea[128];
        std::map<std::pair<UCS4, UCS4>, UCS4> my_composeMap;
        static const std::bitset<128> my_White_Space;
        static const std::bitset<128> my_Dash;
        static const std::bitset<128> my_Hyphen;
        static const std::bitset<128> my_Quotation_Mark;
        static const std::bitset<128> my_Terminal_Punctuation;
        static const std::bitset<128> my_Other_Math;
        static const std::bitset<128> my_Hex_Digit;
        static const std::bitset<128> my_ASCII_Hex_Digit;
        static const std::bitset<128> my_Diacritic;
        static const std::bitset<128> my_Soft_Dotted;
    }; // class Basic_Latin0

    const UCS4 Basic_Latin0::my_upper[] =
    {
        0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 
        0x0008, 0x0009, 0x000A, 0x000B, 0x000C, 0x000D, 0x000E, 0x000F, 
        0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017, 
        0x0018, 0x0019, 0x001A, 0x001B, 0x001C, 0x001D, 0x001E, 0x001F, 
        0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027, 
        0x0028, 0x0029, 0x002A, 0x002B, 0x002C, 0x002D, 0x002E, 0x002F, 
        0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 
        0x0038, 0x0039, 0x003A, 0x003B, 0x003C, 0x003D, 0x003E, 0x003F, 
        0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047, 
        0x0048, 0x0049, 0x004A, 0x004B, 0x004C, 0x004D, 0x004E, 0x004F, 
        0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057, 
        0x0058, 0x0059, 0x005A, 0x005B, 0x005C, 0x005D, 0x005E, 0x005F, 
        0x0060, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047, 
        0x0048, 0x0049, 0x004A, 0x004B, 0x004C, 0x004D, 0x004E, 0x004F, 
        0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057, 
        0x0058, 0x0059, 0x005A, 0x007B, 0x007C, 0x007D, 0x007E, 0x007F
    };

    const UCS4 Basic_Latin0::my_lower[] =
    {
        0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 
        0x0008, 0x0009, 0x000A, 0x000B, 0x000C, 0x000D, 0x000E, 0x000F, 
        0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017, 
        0x0018, 0x0019, 0x001A, 0x001B, 0x001C, 0x001D, 0x001E, 0x001F, 
        0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027, 
        0x0028, 0x0029, 0x002A, 0x002B, 0x002C, 0x002D, 0x002E, 0x002F, 
        0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 
        0x0038, 0x0039, 0x003A, 0x003B, 0x003C, 0x003D, 0x003E, 0x003F, 
        0x0040, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067, 
        0x0068, 0x0069, 0x006A, 0x006B, 0x006C, 0x006D, 0x006E, 0x006F, 
        0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077, 
        0x0078, 0x0079, 0x007A, 0x005B, 0x005C, 0x005D, 0x005E, 0x005F, 
        0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067, 
        0x0068, 0x0069, 0x006A, 0x006B, 0x006C, 0x006D, 0x006E, 0x006F, 
        0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077, 
        0x0078, 0x0079, 0x007A, 0x007B, 0x007C, 0x007D, 0x007E, 0x007F
    };

    const UCS4 Basic_Latin0::my_title[] =
    {
        0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 
        0x0008, 0x0009, 0x000A, 0x000B, 0x000C, 0x000D, 0x000E, 0x000F, 
        0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017, 
        0x0018, 0x0019, 0x001A, 0x001B, 0x001C, 0x001D, 0x001E, 0x001F, 
        0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027, 
        0x0028, 0x0029, 0x002A, 0x002B, 0x002C, 0x002D, 0x002E, 0x002F, 
        0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 
        0x0038, 0x0039, 0x003A, 0x003B, 0x003C, 0x003D, 0x003E, 0x003F, 
        0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047, 
        0x0048, 0x0049, 0x004A, 0x004B, 0x004C, 0x004D, 0x004E, 0x004F, 
        0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057, 
        0x0058, 0x0059, 0x005A, 0x005B, 0x005C, 0x005D, 0x005E, 0x005F, 
        0x0060, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047, 
        0x0048, 0x0049, 0x004A, 0x004B, 0x004C, 0x004D, 0x004E, 0x004F, 
        0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057, 
        0x0058, 0x0059, 0x005A, 0x007B, 0x007C, 0x007D, 0x007E, 0x007F
    };

    const unsigned char Basic_Latin0::my_cat[] =
    {
        CAT_Cc, CAT_Cc, CAT_Cc, CAT_Cc, CAT_Cc, CAT_Cc, CAT_Cc, CAT_Cc, 
        CAT_Cc, CAT_Cc, CAT_Cc, CAT_Cc, CAT_Cc, CAT_Cc, CAT_Cc, CAT_Cc, 
        CAT_Cc, CAT_Cc, CAT_Cc, CAT_Cc, CAT_Cc, CAT_Cc, CAT_Cc, CAT_Cc, 
        CAT_Cc, CAT_Cc, CAT_Cc, CAT_Cc, CAT_Cc, CAT_Cc, CAT_Cc, CAT_Cc, 
        CAT_Zs, CAT_Po, CAT_Po, CAT_Po, CAT_Sc, CAT_Po, CAT_Po, CAT_Po, 
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
        CAT_Ll, CAT_Ll, CAT_Ll, CAT_Ps, CAT_Sm, CAT_Pe, CAT_Sm, CAT_Cc
    };

    const Babylon::Bidir_Props Basic_Latin0::my_bidir[] =
    {
        BIDIR_BN, BIDIR_BN, BIDIR_BN, BIDIR_BN, 
        BIDIR_BN, BIDIR_BN, BIDIR_BN, BIDIR_BN, 
        BIDIR_BN, BIDIR_S, BIDIR_B, BIDIR_S, 
        BIDIR_WS, BIDIR_B, BIDIR_BN, BIDIR_BN, 
        BIDIR_BN, BIDIR_BN, BIDIR_BN, BIDIR_BN, 
        BIDIR_BN, BIDIR_BN, BIDIR_BN, BIDIR_BN, 
        BIDIR_BN, BIDIR_BN, BIDIR_BN, BIDIR_BN, 
        BIDIR_B, BIDIR_B, BIDIR_B, BIDIR_S, 
        BIDIR_WS, BIDIR_ON, BIDIR_ON, BIDIR_ET, 
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
        BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_BN
    };

    const std::bitset<128> Basic_Latin0::my_mirror(std::string("00101000000000000000000000000000001010000000000000000000000000000101000000000000000000110000000000000000000000000000000000000000"));

    const unsigned char Basic_Latin0::my_lb[] =
    {
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_BA, LB_LF, LB_CM, LB_BK, LB_CR, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, LB_CM, 
        LB_SP, LB_EX, LB_QU, LB_AL, LB_PR, LB_PO, LB_AL, LB_QU, 
        LB_OP, LB_CL, LB_AL, LB_PR, LB_IS, LB_HY, LB_IS, LB_SY, 
        LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, LB_NU, 
        LB_NU, LB_NU, LB_IS, LB_IS, LB_AL, LB_AL, LB_AL, LB_EX, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_OP, LB_PR, LB_CL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, LB_AL, 
        LB_AL, LB_AL, LB_AL, LB_OP, LB_BA, LB_CL, LB_AL, LB_CM
    };

    const unsigned char Basic_Latin0::my_ea[] =
    {
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
        EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, 
        EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, 
        EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, 
        EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, 
        EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, 
        EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, 
        EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, 
        EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, 
        EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, 
        EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, 
        EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, 
        EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, 
        EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, 
        EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, 
        EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, 
        EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, 
        EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, 
        EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, 
        EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, 
        EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, 
        EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, 
        EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, 
        EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, 
        EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_N
    };

    const std::bitset<128> Basic_Latin0::my_White_Space(std::string("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000100000000000000000011111000000000"));

    const std::bitset<128> Basic_Latin0::my_Dash(std::string("00000000000000000000000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000"));

    const std::bitset<128> Basic_Latin0::my_Hyphen(std::string("00000000000000000000000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000"));

    const std::bitset<128> Basic_Latin0::my_Quotation_Mark(std::string("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000001000010000000000000000000000000000000000"));

    const std::bitset<128> Basic_Latin0::my_Terminal_Punctuation(std::string("00000000000000000000000000000000000000000000000000000000000000001000110000000000010100000000001000000000000000000000000000000000"));

    const std::bitset<128> Basic_Latin0::my_Other_Math(std::string("00101000000000000000000000000000011110000000000000000000000000000000000000000000101001110000000000000000000000000000000000000000"));

    const std::bitset<128> Basic_Latin0::my_Hex_Digit(std::string("00000000000000000000000001111110000000000000000000000000011111100000001111111111000000000000000000000000000000000000000000000000"));

    const std::bitset<128> Basic_Latin0::my_ASCII_Hex_Digit(std::string("00000000000000000000000001111110000000000000000000000000011111100000001111111111000000000000000000000000000000000000000000000000"));

    const std::bitset<128> Basic_Latin0::my_Diacritic(std::string("00000000000000000000000000000001010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));

    const std::bitset<128> Basic_Latin0::my_Soft_Dotted(std::string("00000000000000000000011000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));

  }; // namespace
}; // namespace

dload(Babylon::Module::Basic_Latin0);
