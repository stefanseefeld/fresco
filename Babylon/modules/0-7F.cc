/*$Id: 0-7F.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Wed,  6 Dec 2000 23:21:34 +0100.
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

  class Basic_Latin0 : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    Basic_Latin0() {
      _first_letter = 0x0;
      _last_letter  = 0x7F;
      // _version="3.0.1" // Not yet supported!
      _composeMap[0x003C0338] = 0x226E;
      _composeMap[0x003D0338] = 0x2260;
      _composeMap[0x003E0338] = 0x226F;
      _composeMap[0x00410300] = 0x00C0;
      _composeMap[0x00410301] = 0x00C1;
      _composeMap[0x00410302] = 0x00C2;
      _composeMap[0x00410303] = 0x00C3;
      _composeMap[0x00410304] = 0x0100;
      _composeMap[0x00410306] = 0x0102;
      _composeMap[0x00410307] = 0x0226;
      _composeMap[0x00410308] = 0x00C4;
      _composeMap[0x00410309] = 0x1EA2;
      _composeMap[0x0041030A] = 0x00C5;
      _composeMap[0x0041030C] = 0x01CD;
      _composeMap[0x0041030F] = 0x0200;
      _composeMap[0x00410311] = 0x0202;
      _composeMap[0x00410323] = 0x1EA0;
      _composeMap[0x00410325] = 0x1E00;
      _composeMap[0x00410328] = 0x0104;
      _composeMap[0x00420307] = 0x1E02;
      _composeMap[0x00420323] = 0x1E04;
      _composeMap[0x00420331] = 0x1E06;
      _composeMap[0x00430301] = 0x0106;
      _composeMap[0x00430302] = 0x0108;
      _composeMap[0x00430307] = 0x010A;
      _composeMap[0x0043030C] = 0x010C;
      _composeMap[0x00430327] = 0x00C7;
      _composeMap[0x00440307] = 0x1E0A;
      _composeMap[0x0044030C] = 0x010E;
      _composeMap[0x00440323] = 0x1E0C;
      _composeMap[0x00440327] = 0x1E10;
      _composeMap[0x0044032D] = 0x1E12;
      _composeMap[0x00440331] = 0x1E0E;
      _composeMap[0x00450300] = 0x00C8;
      _composeMap[0x00450301] = 0x00C9;
      _composeMap[0x00450302] = 0x00CA;
      _composeMap[0x00450303] = 0x1EBC;
      _composeMap[0x00450304] = 0x0112;
      _composeMap[0x00450306] = 0x0114;
      _composeMap[0x00450307] = 0x0116;
      _composeMap[0x00450308] = 0x00CB;
      _composeMap[0x00450309] = 0x1EBA;
      _composeMap[0x0045030C] = 0x011A;
      _composeMap[0x0045030F] = 0x0204;
      _composeMap[0x00450311] = 0x0206;
      _composeMap[0x00450323] = 0x1EB8;
      _composeMap[0x00450327] = 0x0228;
      _composeMap[0x00450328] = 0x0118;
      _composeMap[0x0045032D] = 0x1E18;
      _composeMap[0x00450330] = 0x1E1A;
      _composeMap[0x00460307] = 0x1E1E;
      _composeMap[0x00470301] = 0x01F4;
      _composeMap[0x00470302] = 0x011C;
      _composeMap[0x00470304] = 0x1E20;
      _composeMap[0x00470306] = 0x011E;
      _composeMap[0x00470307] = 0x0120;
      _composeMap[0x0047030C] = 0x01E6;
      _composeMap[0x00470327] = 0x0122;
      _composeMap[0x00480302] = 0x0124;
      _composeMap[0x00480307] = 0x1E22;
      _composeMap[0x00480308] = 0x1E26;
      _composeMap[0x0048030C] = 0x021E;
      _composeMap[0x00480323] = 0x1E24;
      _composeMap[0x00480327] = 0x1E28;
      _composeMap[0x0048032E] = 0x1E2A;
      _composeMap[0x00490300] = 0x00CC;
      _composeMap[0x00490301] = 0x00CD;
      _composeMap[0x00490302] = 0x00CE;
      _composeMap[0x00490303] = 0x0128;
      _composeMap[0x00490304] = 0x012A;
      _composeMap[0x00490306] = 0x012C;
      _composeMap[0x00490307] = 0x0130;
      _composeMap[0x00490308] = 0x00CF;
      _composeMap[0x00490309] = 0x1EC8;
      _composeMap[0x0049030C] = 0x01CF;
      _composeMap[0x0049030F] = 0x0208;
      _composeMap[0x00490311] = 0x020A;
      _composeMap[0x00490323] = 0x1ECA;
      _composeMap[0x00490328] = 0x012E;
      _composeMap[0x00490330] = 0x1E2C;
      _composeMap[0x004A0302] = 0x0134;
      _composeMap[0x004B0301] = 0x1E30;
      _composeMap[0x004B030C] = 0x01E8;
      _composeMap[0x004B0323] = 0x1E32;
      _composeMap[0x004B0327] = 0x0136;
      _composeMap[0x004B0331] = 0x1E34;
      _composeMap[0x004C0301] = 0x0139;
      _composeMap[0x004C030C] = 0x013D;
      _composeMap[0x004C0323] = 0x1E36;
      _composeMap[0x004C0327] = 0x013B;
      _composeMap[0x004C032D] = 0x1E3C;
      _composeMap[0x004C0331] = 0x1E3A;
      _composeMap[0x004D0301] = 0x1E3E;
      _composeMap[0x004D0307] = 0x1E40;
      _composeMap[0x004D0323] = 0x1E42;
      _composeMap[0x004E0300] = 0x01F8;
      _composeMap[0x004E0301] = 0x0143;
      _composeMap[0x004E0303] = 0x00D1;
      _composeMap[0x004E0307] = 0x1E44;
      _composeMap[0x004E030C] = 0x0147;
      _composeMap[0x004E0323] = 0x1E46;
      _composeMap[0x004E0327] = 0x0145;
      _composeMap[0x004E032D] = 0x1E4A;
      _composeMap[0x004E0331] = 0x1E48;
      _composeMap[0x004F0300] = 0x00D2;
      _composeMap[0x004F0301] = 0x00D3;
      _composeMap[0x004F0302] = 0x00D4;
      _composeMap[0x004F0303] = 0x00D5;
      _composeMap[0x004F0304] = 0x014C;
      _composeMap[0x004F0306] = 0x014E;
      _composeMap[0x004F0307] = 0x022E;
      _composeMap[0x004F0308] = 0x00D6;
      _composeMap[0x004F0309] = 0x1ECE;
      _composeMap[0x004F030B] = 0x0150;
      _composeMap[0x004F030C] = 0x01D1;
      _composeMap[0x004F030F] = 0x020C;
      _composeMap[0x004F0311] = 0x020E;
      _composeMap[0x004F031B] = 0x01A0;
      _composeMap[0x004F0323] = 0x1ECC;
      _composeMap[0x004F0328] = 0x01EA;
      _composeMap[0x00500301] = 0x1E54;
      _composeMap[0x00500307] = 0x1E56;
      _composeMap[0x00520301] = 0x0154;
      _composeMap[0x00520307] = 0x1E58;
      _composeMap[0x0052030C] = 0x0158;
      _composeMap[0x0052030F] = 0x0210;
      _composeMap[0x00520311] = 0x0212;
      _composeMap[0x00520323] = 0x1E5A;
      _composeMap[0x00520327] = 0x0156;
      _composeMap[0x00520331] = 0x1E5E;
      _composeMap[0x00530301] = 0x015A;
      _composeMap[0x00530302] = 0x015C;
      _composeMap[0x00530307] = 0x1E60;
      _composeMap[0x0053030C] = 0x0160;
      _composeMap[0x00530323] = 0x1E62;
      _composeMap[0x00530326] = 0x0218;
      _composeMap[0x00530327] = 0x015E;
      _composeMap[0x00540307] = 0x1E6A;
      _composeMap[0x0054030C] = 0x0164;
      _composeMap[0x00540323] = 0x1E6C;
      _composeMap[0x00540326] = 0x021A;
      _composeMap[0x00540327] = 0x0162;
      _composeMap[0x0054032D] = 0x1E70;
      _composeMap[0x00540331] = 0x1E6E;
      _composeMap[0x00550300] = 0x00D9;
      _composeMap[0x00550301] = 0x00DA;
      _composeMap[0x00550302] = 0x00DB;
      _composeMap[0x00550303] = 0x0168;
      _composeMap[0x00550304] = 0x016A;
      _composeMap[0x00550306] = 0x016C;
      _composeMap[0x00550308] = 0x00DC;
      _composeMap[0x00550309] = 0x1EE6;
      _composeMap[0x0055030A] = 0x016E;
      _composeMap[0x0055030B] = 0x0170;
      _composeMap[0x0055030C] = 0x01D3;
      _composeMap[0x0055030F] = 0x0214;
      _composeMap[0x00550311] = 0x0216;
      _composeMap[0x0055031B] = 0x01AF;
      _composeMap[0x00550323] = 0x1EE4;
      _composeMap[0x00550324] = 0x1E72;
      _composeMap[0x00550328] = 0x0172;
      _composeMap[0x0055032D] = 0x1E76;
      _composeMap[0x00550330] = 0x1E74;
      _composeMap[0x00560303] = 0x1E7C;
      _composeMap[0x00560323] = 0x1E7E;
      _composeMap[0x00570300] = 0x1E80;
      _composeMap[0x00570301] = 0x1E82;
      _composeMap[0x00570302] = 0x0174;
      _composeMap[0x00570307] = 0x1E86;
      _composeMap[0x00570308] = 0x1E84;
      _composeMap[0x00570323] = 0x1E88;
      _composeMap[0x00580307] = 0x1E8A;
      _composeMap[0x00580308] = 0x1E8C;
      _composeMap[0x00590300] = 0x1EF2;
      _composeMap[0x00590301] = 0x00DD;
      _composeMap[0x00590302] = 0x0176;
      _composeMap[0x00590303] = 0x1EF8;
      _composeMap[0x00590304] = 0x0232;
      _composeMap[0x00590307] = 0x1E8E;
      _composeMap[0x00590308] = 0x0178;
      _composeMap[0x00590309] = 0x1EF6;
      _composeMap[0x00590323] = 0x1EF4;
      _composeMap[0x005A0301] = 0x0179;
      _composeMap[0x005A0302] = 0x1E90;
      _composeMap[0x005A0307] = 0x017B;
      _composeMap[0x005A030C] = 0x017D;
      _composeMap[0x005A0323] = 0x1E92;
      _composeMap[0x005A0331] = 0x1E94;
      _composeMap[0x00610300] = 0x00E0;
      _composeMap[0x00610301] = 0x00E1;
      _composeMap[0x00610302] = 0x00E2;
      _composeMap[0x00610303] = 0x00E3;
      _composeMap[0x00610304] = 0x0101;
      _composeMap[0x00610306] = 0x0103;
      _composeMap[0x00610307] = 0x0227;
      _composeMap[0x00610308] = 0x00E4;
      _composeMap[0x00610309] = 0x1EA3;
      _composeMap[0x0061030A] = 0x00E5;
      _composeMap[0x0061030C] = 0x01CE;
      _composeMap[0x0061030F] = 0x0201;
      _composeMap[0x00610311] = 0x0203;
      _composeMap[0x00610323] = 0x1EA1;
      _composeMap[0x00610325] = 0x1E01;
      _composeMap[0x00610328] = 0x0105;
      _composeMap[0x00620307] = 0x1E03;
      _composeMap[0x00620323] = 0x1E05;
      _composeMap[0x00620331] = 0x1E07;
      _composeMap[0x00630301] = 0x0107;
      _composeMap[0x00630302] = 0x0109;
      _composeMap[0x00630307] = 0x010B;
      _composeMap[0x0063030C] = 0x010D;
      _composeMap[0x00630327] = 0x00E7;
      _composeMap[0x00640307] = 0x1E0B;
      _composeMap[0x0064030C] = 0x010F;
      _composeMap[0x00640323] = 0x1E0D;
      _composeMap[0x00640327] = 0x1E11;
      _composeMap[0x0064032D] = 0x1E13;
      _composeMap[0x00640331] = 0x1E0F;
      _composeMap[0x00650300] = 0x00E8;
      _composeMap[0x00650301] = 0x00E9;
      _composeMap[0x00650302] = 0x00EA;
      _composeMap[0x00650303] = 0x1EBD;
      _composeMap[0x00650304] = 0x0113;
      _composeMap[0x00650306] = 0x0115;
      _composeMap[0x00650307] = 0x0117;
      _composeMap[0x00650308] = 0x00EB;
      _composeMap[0x00650309] = 0x1EBB;
      _composeMap[0x0065030C] = 0x011B;
      _composeMap[0x0065030F] = 0x0205;
      _composeMap[0x00650311] = 0x0207;
      _composeMap[0x00650323] = 0x1EB9;
      _composeMap[0x00650327] = 0x0229;
      _composeMap[0x00650328] = 0x0119;
      _composeMap[0x0065032D] = 0x1E19;
      _composeMap[0x00650330] = 0x1E1B;
      _composeMap[0x00660307] = 0x1E1F;
      _composeMap[0x00670301] = 0x01F5;
      _composeMap[0x00670302] = 0x011D;
      _composeMap[0x00670304] = 0x1E21;
      _composeMap[0x00670306] = 0x011F;
      _composeMap[0x00670307] = 0x0121;
      _composeMap[0x0067030C] = 0x01E7;
      _composeMap[0x00670327] = 0x0123;
      _composeMap[0x00680302] = 0x0125;
      _composeMap[0x00680307] = 0x1E23;
      _composeMap[0x00680308] = 0x1E27;
      _composeMap[0x0068030C] = 0x021F;
      _composeMap[0x00680323] = 0x1E25;
      _composeMap[0x00680327] = 0x1E29;
      _composeMap[0x0068032E] = 0x1E2B;
      _composeMap[0x00680331] = 0x1E96;
      _composeMap[0x00690300] = 0x00EC;
      _composeMap[0x00690301] = 0x00ED;
      _composeMap[0x00690302] = 0x00EE;
      _composeMap[0x00690303] = 0x0129;
      _composeMap[0x00690304] = 0x012B;
      _composeMap[0x00690306] = 0x012D;
      _composeMap[0x00690308] = 0x00EF;
      _composeMap[0x00690309] = 0x1EC9;
      _composeMap[0x0069030C] = 0x01D0;
      _composeMap[0x0069030F] = 0x0209;
      _composeMap[0x00690311] = 0x020B;
      _composeMap[0x00690323] = 0x1ECB;
      _composeMap[0x00690328] = 0x012F;
      _composeMap[0x00690330] = 0x1E2D;
      _composeMap[0x006A0302] = 0x0135;
      _composeMap[0x006A030C] = 0x01F0;
      _composeMap[0x006B0301] = 0x1E31;
      _composeMap[0x006B030C] = 0x01E9;
      _composeMap[0x006B0323] = 0x1E33;
      _composeMap[0x006B0327] = 0x0137;
      _composeMap[0x006B0331] = 0x1E35;
      _composeMap[0x006C0301] = 0x013A;
      _composeMap[0x006C030C] = 0x013E;
      _composeMap[0x006C0323] = 0x1E37;
      _composeMap[0x006C0327] = 0x013C;
      _composeMap[0x006C032D] = 0x1E3D;
      _composeMap[0x006C0331] = 0x1E3B;
      _composeMap[0x006D0301] = 0x1E3F;
      _composeMap[0x006D0307] = 0x1E41;
      _composeMap[0x006D0323] = 0x1E43;
      _composeMap[0x006E0300] = 0x01F9;
      _composeMap[0x006E0301] = 0x0144;
      _composeMap[0x006E0303] = 0x00F1;
      _composeMap[0x006E0307] = 0x1E45;
      _composeMap[0x006E030C] = 0x0148;
      _composeMap[0x006E0323] = 0x1E47;
      _composeMap[0x006E0327] = 0x0146;
      _composeMap[0x006E032D] = 0x1E4B;
      _composeMap[0x006E0331] = 0x1E49;
      _composeMap[0x006F0300] = 0x00F2;
      _composeMap[0x006F0301] = 0x00F3;
      _composeMap[0x006F0302] = 0x00F4;
      _composeMap[0x006F0303] = 0x00F5;
      _composeMap[0x006F0304] = 0x014D;
      _composeMap[0x006F0306] = 0x014F;
      _composeMap[0x006F0307] = 0x022F;
      _composeMap[0x006F0308] = 0x00F6;
      _composeMap[0x006F0309] = 0x1ECF;
      _composeMap[0x006F030B] = 0x0151;
      _composeMap[0x006F030C] = 0x01D2;
      _composeMap[0x006F030F] = 0x020D;
      _composeMap[0x006F0311] = 0x020F;
      _composeMap[0x006F031B] = 0x01A1;
      _composeMap[0x006F0323] = 0x1ECD;
      _composeMap[0x006F0328] = 0x01EB;
      _composeMap[0x00700301] = 0x1E55;
      _composeMap[0x00700307] = 0x1E57;
      _composeMap[0x00720301] = 0x0155;
      _composeMap[0x00720307] = 0x1E59;
      _composeMap[0x0072030C] = 0x0159;
      _composeMap[0x0072030F] = 0x0211;
      _composeMap[0x00720311] = 0x0213;
      _composeMap[0x00720323] = 0x1E5B;
      _composeMap[0x00720327] = 0x0157;
      _composeMap[0x00720331] = 0x1E5F;
      _composeMap[0x00730301] = 0x015B;
      _composeMap[0x00730302] = 0x015D;
      _composeMap[0x00730307] = 0x1E61;
      _composeMap[0x0073030C] = 0x0161;
      _composeMap[0x00730323] = 0x1E63;
      _composeMap[0x00730326] = 0x0219;
      _composeMap[0x00730327] = 0x015F;
      _composeMap[0x00740307] = 0x1E6B;
      _composeMap[0x00740308] = 0x1E97;
      _composeMap[0x0074030C] = 0x0165;
      _composeMap[0x00740323] = 0x1E6D;
      _composeMap[0x00740326] = 0x021B;
      _composeMap[0x00740327] = 0x0163;
      _composeMap[0x0074032D] = 0x1E71;
      _composeMap[0x00740331] = 0x1E6F;
      _composeMap[0x00750300] = 0x00F9;
      _composeMap[0x00750301] = 0x00FA;
      _composeMap[0x00750302] = 0x00FB;
      _composeMap[0x00750303] = 0x0169;
      _composeMap[0x00750304] = 0x016B;
      _composeMap[0x00750306] = 0x016D;
      _composeMap[0x00750308] = 0x00FC;
      _composeMap[0x00750309] = 0x1EE7;
      _composeMap[0x0075030A] = 0x016F;
      _composeMap[0x0075030B] = 0x0171;
      _composeMap[0x0075030C] = 0x01D4;
      _composeMap[0x0075030F] = 0x0215;
      _composeMap[0x00750311] = 0x0217;
      _composeMap[0x0075031B] = 0x01B0;
      _composeMap[0x00750323] = 0x1EE5;
      _composeMap[0x00750324] = 0x1E73;
      _composeMap[0x00750328] = 0x0173;
      _composeMap[0x0075032D] = 0x1E77;
      _composeMap[0x00750330] = 0x1E75;
      _composeMap[0x00760303] = 0x1E7D;
      _composeMap[0x00760323] = 0x1E7F;
      _composeMap[0x00770300] = 0x1E81;
      _composeMap[0x00770301] = 0x1E83;
      _composeMap[0x00770302] = 0x0175;
      _composeMap[0x00770307] = 0x1E87;
      _composeMap[0x00770308] = 0x1E85;
      _composeMap[0x0077030A] = 0x1E98;
      _composeMap[0x00770323] = 0x1E89;
      _composeMap[0x00780307] = 0x1E8B;
      _composeMap[0x00780308] = 0x1E8D;
      _composeMap[0x00790300] = 0x1EF3;
      _composeMap[0x00790301] = 0x00FD;
      _composeMap[0x00790302] = 0x0177;
      _composeMap[0x00790303] = 0x1EF9;
      _composeMap[0x00790304] = 0x0233;
      _composeMap[0x00790307] = 0x1E8F;
      _composeMap[0x00790308] = 0x00FF;
      _composeMap[0x00790309] = 0x1EF7;
      _composeMap[0x0079030A] = 0x1E99;
      _composeMap[0x00790323] = 0x1EF5;
      _composeMap[0x007A0301] = 0x017A;
      _composeMap[0x007A0302] = 0x1E91;
      _composeMap[0x007A0307] = 0x017C;
      _composeMap[0x007A030C] = 0x017E;
      _composeMap[0x007A0323] = 0x1E93;
      _composeMap[0x007A0331] = 0x1E95;

    }


    ~Basic_Latin0() {
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
      return "Basic Latin";
    }

    bool is_defined(const UCS4 uc) const {
      return 1;
    }

    UCS4 uppercase(const UCS4 uc) const {
      return Basic_Latin0::_upper[uc - _first_letter];
    }

    bool is_Uppercase(const UCS4 uc) const {
      return category(uc) == CAT_Lu;
    }

    UCS4 lowercase(const UCS4 uc) const {
      return Basic_Latin0::_lower[uc - _first_letter];
    }

    bool is_Lowercase(const UCS4 uc) const {
      return category(uc) == CAT_Ll;
    }

    UCS4 titlecase(const UCS4 uc) const {
      return Basic_Latin0::_title[uc - _first_letter];
    }

    bool is_Titlecase(const UCS4 uc) const {
      return category(uc) == CAT_Lt;
    }

    int dec_digit_value(const UCS4 uc) const {
      if (!is_defined(uc))
        return 0;
      switch(uc) {
      case 0x0030:
        return 0;
        break;
      case 0x0031:
        return 1;
        break;
      case 0x0032:
        return 2;
        break;
      case 0x0033:
        return 3;
        break;
      case 0x0034:
        return 4;
        break;
      case 0x0035:
        return 5;
        break;
      case 0x0036:
        return 6;
        break;
      case 0x0037:
        return 7;
        break;
      case 0x0038:
        return 8;
        break;
      case 0x0039:
        return 9;
        break;
      default:
        return 0;
      }
    }

    bool is_Decimal_Digit(const UCS4 uc) const {
      switch(uc) {
      case 0x0030:
      case 0x0031:
      case 0x0032:
      case 0x0033:
      case 0x0034:
      case 0x0035:
      case 0x0036:
      case 0x0037:
      case 0x0038:
      case 0x0039:
        return 1;
      default:
        return 0;
      }
    }

    int digit_value(const UCS4 uc) const {
      if (!is_defined(uc))
        return 0;
      switch(uc) {
      case 0x0030:
        return 0;
        break;
      case 0x0031:
        return 1;
        break;
      case 0x0032:
        return 2;
        break;
      case 0x0033:
        return 3;
        break;
      case 0x0034:
        return 4;
        break;
      case 0x0035:
        return 5;
        break;
      case 0x0036:
        return 6;
        break;
      case 0x0037:
        return 7;
        break;
      case 0x0038:
        return 8;
        break;
      case 0x0039:
        return 9;
        break;
      default:
        return 0;
      }
    }

    bool is_Digit(const UCS4 uc) const {
      switch(uc) {
      case 0x0030:
      case 0x0031:
      case 0x0032:
      case 0x0033:
      case 0x0034:
      case 0x0035:
      case 0x0036:
      case 0x0037:
      case 0x0038:
      case 0x0039:
        return 1;
      default:
        return 0;
      }
    }

    float numeric_value(const UCS4 uc) const {
      if (!is_defined(uc))
        return 0;
      switch(uc) {
      case 0x0030:
        return 0.000000;
        break;
      case 0x0031:
        return 1.000000;
        break;
      case 0x0032:
        return 2.000000;
        break;
      case 0x0033:
        return 3.000000;
        break;
      case 0x0034:
        return 4.000000;
        break;
      case 0x0035:
        return 5.000000;
        break;
      case 0x0036:
        return 6.000000;
        break;
      case 0x0037:
        return 7.000000;
        break;
      case 0x0038:
        return 8.000000;
        break;
      case 0x0039:
        return 9.000000;
        break;
      default:
        return 0;
      }
    }

    bool is_Numeric(const UCS4 uc) const {
      switch(uc) {
      case 0x0030:
      case 0x0031:
      case 0x0032:
      case 0x0033:
      case 0x0034:
      case 0x0035:
      case 0x0036:
      case 0x0037:
      case 0x0038:
      case 0x0039:
        return 1;
      default:
        return 0;
      }
    }

    Gen_Cat category(const UCS4 uc) const {
      if (!is_defined(uc))
        return CAT_MAX;
      return Babylon::Gen_Cat(Basic_Latin0::_cat[uc - _first_letter]);
    }

    Can_Comb_Class comb_class(const UCS4 uc) const {
      if (!is_defined(uc))
        return CC_MAX;
      return Babylon::Can_Comb_Class(0);
    }

    Bidir_Props bidir_props(const UCS4 uc) const {
      if (!is_defined(uc))
        return BIDIR_MAX;
      return Babylon::Bidir_Props(Basic_Latin0::_bidir[uc - _first_letter]);
    }

    Char_Decomp decomp_type(const UCS4 uc) const {
      if (!is_defined(uc))
        return DECOMP_MAX;
      return Babylon::Char_Decomp(DECOMP_NO_DECOMP);
    }

    UTF32_string decompose(const UCS4 uc) const {
      UTF32_string us;
      us.resize(1); us[0]=uc;
      return us;
    }

    bool must_mirror(const UCS4 uc) const {
      return Basic_Latin0::_mirror[uc - _first_letter];
    }

    Line_Break linebreak(const UCS4 uc) const {
      if (!is_defined(uc))
        return LB_MAX;
      return Babylon::Line_Break(Basic_Latin0::_lb[uc - _first_letter]);
    }

    EA_Width EA_width(const UCS4 uc) const {
      if (!is_defined(uc))
        return EA_WIDTH_MAX;
      return Babylon::EA_Width(Basic_Latin0::_ea[uc - _first_letter]);
    }

    UCS4 compose (const UCS4 starter, const UCS4 last) {
      return _composeMap[starter << 16 | last];
    }

    bool is_Zero_width(const UCS4 uc) const {
      return 0;
    }

    bool is_White_space(const UCS4 uc) const {
      return Basic_Latin0::_White_space[uc - _first_letter];
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
      return Basic_Latin0::_Dash[uc - _first_letter];
    }

    bool is_Hyphen(const UCS4 uc) const {
      return Basic_Latin0::_Hyphen[uc - _first_letter];
    }

    bool is_Quotation_Mark(const UCS4 uc) const {
      return Basic_Latin0::_Quotation_Mark[uc - _first_letter];
    }

    bool is_Terminal_Punctuation(const UCS4 uc) const {
      return Basic_Latin0::_Terminal_Punctuation[uc - _first_letter];
    }

    bool is_Math(const UCS4 uc) const {
      return Basic_Latin0::_Math[uc - _first_letter];
    }

    bool is_Paired_Punctuation(const UCS4 uc) const {
      return Basic_Latin0::_Paired_Punctuation[uc - _first_letter];
    }

    bool is_Left_of_Pair(const UCS4 uc) const {
      return Basic_Latin0::_Left_of_Pair[uc - _first_letter];
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
      return Basic_Latin0::_Hex_Digit[uc - _first_letter];
    }

    bool is_Alphabetic(const UCS4 uc) const {
      return Basic_Latin0::_Alphabetic[uc - _first_letter];
    }

    bool is_Diacritic(const UCS4 uc) const {
      return Basic_Latin0::_Diacritic[uc - _first_letter];
    }

    bool is_Extender(const UCS4 uc) const {
      return 0;
    }

    bool is_Identifier_Part(const UCS4 uc) const {
      return Basic_Latin0::_Identifier_Part[uc - _first_letter];
    }

    bool is_Ignorable_Control(const UCS4 uc) const {
      return Basic_Latin0::_Ignorable_Control[uc - _first_letter];
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
    Basic_Latin0(const Basic_Latin0 &) {}

    Babylon::UCS4 _first_letter;
    Babylon::UCS4 _last_letter;
    static const UCS4 _upper[128];
    static const UCS4 _lower[128];
    static const UCS4 _title[128];
    static const unsigned char _cat[128];
    static const unsigned char _bidir[128];
    static const bool _mirror[128];
    static const unsigned char _lb[128];
    static const unsigned char _ea[128];
    map<UCS4, UCS4> _composeMap;
    static const bool _White_space[128];
    static const bool _Dash[128];
    static const bool _Hyphen[128];
    static const bool _Quotation_Mark[128];
    static const bool _Terminal_Punctuation[128];
    static const bool _Math[128];
    static const bool _Paired_Punctuation[128];
    static const bool _Left_of_Pair[128];
    static const bool _Hex_Digit[128];
    static const bool _Alphabetic[128];
    static const bool _Diacritic[128];
    static const bool _Identifier_Part[128];
    static const bool _Ignorable_Control[128];

  }; // class Basic_Latin0

  const UCS4 Basic_Latin0::_upper[] = {
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

  const UCS4 Basic_Latin0::_lower[] = {
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

  const UCS4 Basic_Latin0::_title[] = {
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

  const unsigned char Basic_Latin0::_cat[] = {
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

  const unsigned char Basic_Latin0::_bidir[] = {
    BIDIR_BN, BIDIR_BN, BIDIR_BN, BIDIR_BN, BIDIR_BN, BIDIR_BN, BIDIR_BN, BIDIR_BN, 
    BIDIR_BN, BIDIR_S, BIDIR_B, BIDIR_S, BIDIR_WS, BIDIR_B, BIDIR_BN, BIDIR_BN, 
    BIDIR_BN, BIDIR_BN, BIDIR_BN, BIDIR_BN, BIDIR_BN, BIDIR_BN, BIDIR_BN, BIDIR_BN, 
    BIDIR_BN, BIDIR_BN, BIDIR_BN, BIDIR_BN, BIDIR_B, BIDIR_B, BIDIR_B, BIDIR_S, 
    BIDIR_WS, BIDIR_ON, BIDIR_ON, BIDIR_ET, BIDIR_ET, BIDIR_ET, BIDIR_ON, BIDIR_ON, 
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
    BIDIR_L, BIDIR_L, BIDIR_L, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_ON, BIDIR_BN
  };

  const bool Basic_Latin0::_mirror[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    1, 1, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 1, 0, 1, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 1, 0, 1, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 1, 0, 1, 0, 0
  };

  const unsigned char Basic_Latin0::_lb[] = {
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

  const unsigned char Basic_Latin0::_ea[] = {
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, EA_WIDTH_N, 
    EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, 
    EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, 
    EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, 
    EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, 
    EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, 
    EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, 
    EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, 
    EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, 
    EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, 
    EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, 
    EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, 
    EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_Na, EA_WIDTH_N
  };

    const bool Basic_Latin0::_White_space[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 1, 1, 1, 1, 1, 0, 0, 
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
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Basic_Latin0::_Dash[] = {
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
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Basic_Latin0::_Hyphen[] = {
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
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Basic_Latin0::_Quotation_Mark[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
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
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Basic_Latin0::_Terminal_Punctuation[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
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
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Basic_Latin0::_Math[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
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
        0, 0, 0, 1, 1, 1, 1, 0
    };

    const bool Basic_Latin0::_Paired_Punctuation[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
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
        0, 0, 0, 1, 0, 1, 0, 0
    };

    const bool Basic_Latin0::_Left_of_Pair[] = {
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
        0, 0, 0, 1, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 1, 0, 0, 0, 0
    };

    const bool Basic_Latin0::_Hex_Digit[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
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
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Basic_Latin0::_Alphabetic[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
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
        1, 1, 1, 0, 0, 0, 0, 0
    };

    const bool Basic_Latin0::_Diacritic[] = {
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
        1, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Basic_Latin0::_Identifier_Part[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
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
        1, 1, 1, 0, 0, 0, 0, 0
    };

    const bool Basic_Latin0::_Ignorable_Control[] = {
        0, 1, 1, 1, 1, 1, 1, 1, 
        1, 0, 0, 0, 0, 0, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 0, 0, 0, 0, 
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
        0, 0, 0, 0, 0, 0, 0, 1
    };

}; // namespace Babylon

dload(Babylon::Basic_Latin0);
