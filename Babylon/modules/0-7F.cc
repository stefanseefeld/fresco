/*$Id: 0-7F.cc
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on Tue, 21 Nov 2000 21:10:31 +0100.
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
      my_first_letter = 0x0;
      my_last_letter  = 0x7F;
      // my_version="3.0.1" // Not yet supported!
      composeMap[0x003C0338] = 0x226E;
      composeMap[0x003D0338] = 0x2260;
      composeMap[0x003E0338] = 0x226F;
      composeMap[0x00410300] = 0x00C0;
      composeMap[0x00410301] = 0x00C1;
      composeMap[0x00410302] = 0x00C2;
      composeMap[0x00410303] = 0x00C3;
      composeMap[0x00410304] = 0x0100;
      composeMap[0x00410306] = 0x0102;
      composeMap[0x00410307] = 0x0226;
      composeMap[0x00410308] = 0x00C4;
      composeMap[0x00410309] = 0x1EA2;
      composeMap[0x0041030A] = 0x00C5;
      composeMap[0x0041030C] = 0x01CD;
      composeMap[0x0041030F] = 0x0200;
      composeMap[0x00410311] = 0x0202;
      composeMap[0x00410323] = 0x1EA0;
      composeMap[0x00410325] = 0x1E00;
      composeMap[0x00410328] = 0x0104;
      composeMap[0x00420307] = 0x1E02;
      composeMap[0x00420323] = 0x1E04;
      composeMap[0x00420331] = 0x1E06;
      composeMap[0x00430301] = 0x0106;
      composeMap[0x00430302] = 0x0108;
      composeMap[0x00430307] = 0x010A;
      composeMap[0x0043030C] = 0x010C;
      composeMap[0x00430327] = 0x00C7;
      composeMap[0x00440307] = 0x1E0A;
      composeMap[0x0044030C] = 0x010E;
      composeMap[0x00440323] = 0x1E0C;
      composeMap[0x00440327] = 0x1E10;
      composeMap[0x0044032D] = 0x1E12;
      composeMap[0x00440331] = 0x1E0E;
      composeMap[0x00450300] = 0x00C8;
      composeMap[0x00450301] = 0x00C9;
      composeMap[0x00450302] = 0x00CA;
      composeMap[0x00450303] = 0x1EBC;
      composeMap[0x00450304] = 0x0112;
      composeMap[0x00450306] = 0x0114;
      composeMap[0x00450307] = 0x0116;
      composeMap[0x00450308] = 0x00CB;
      composeMap[0x00450309] = 0x1EBA;
      composeMap[0x0045030C] = 0x011A;
      composeMap[0x0045030F] = 0x0204;
      composeMap[0x00450311] = 0x0206;
      composeMap[0x00450323] = 0x1EB8;
      composeMap[0x00450327] = 0x0228;
      composeMap[0x00450328] = 0x0118;
      composeMap[0x0045032D] = 0x1E18;
      composeMap[0x00450330] = 0x1E1A;
      composeMap[0x00460307] = 0x1E1E;
      composeMap[0x00470301] = 0x01F4;
      composeMap[0x00470302] = 0x011C;
      composeMap[0x00470304] = 0x1E20;
      composeMap[0x00470306] = 0x011E;
      composeMap[0x00470307] = 0x0120;
      composeMap[0x0047030C] = 0x01E6;
      composeMap[0x00470327] = 0x0122;
      composeMap[0x00480302] = 0x0124;
      composeMap[0x00480307] = 0x1E22;
      composeMap[0x00480308] = 0x1E26;
      composeMap[0x0048030C] = 0x021E;
      composeMap[0x00480323] = 0x1E24;
      composeMap[0x00480327] = 0x1E28;
      composeMap[0x0048032E] = 0x1E2A;
      composeMap[0x00490300] = 0x00CC;
      composeMap[0x00490301] = 0x00CD;
      composeMap[0x00490302] = 0x00CE;
      composeMap[0x00490303] = 0x0128;
      composeMap[0x00490304] = 0x012A;
      composeMap[0x00490306] = 0x012C;
      composeMap[0x00490307] = 0x0130;
      composeMap[0x00490308] = 0x00CF;
      composeMap[0x00490309] = 0x1EC8;
      composeMap[0x0049030C] = 0x01CF;
      composeMap[0x0049030F] = 0x0208;
      composeMap[0x00490311] = 0x020A;
      composeMap[0x00490323] = 0x1ECA;
      composeMap[0x00490328] = 0x012E;
      composeMap[0x00490330] = 0x1E2C;
      composeMap[0x004A0302] = 0x0134;
      composeMap[0x004B0301] = 0x1E30;
      composeMap[0x004B030C] = 0x01E8;
      composeMap[0x004B0323] = 0x1E32;
      composeMap[0x004B0327] = 0x0136;
      composeMap[0x004B0331] = 0x1E34;
      composeMap[0x004C0301] = 0x0139;
      composeMap[0x004C030C] = 0x013D;
      composeMap[0x004C0323] = 0x1E36;
      composeMap[0x004C0327] = 0x013B;
      composeMap[0x004C032D] = 0x1E3C;
      composeMap[0x004C0331] = 0x1E3A;
      composeMap[0x004D0301] = 0x1E3E;
      composeMap[0x004D0307] = 0x1E40;
      composeMap[0x004D0323] = 0x1E42;
      composeMap[0x004E0300] = 0x01F8;
      composeMap[0x004E0301] = 0x0143;
      composeMap[0x004E0303] = 0x00D1;
      composeMap[0x004E0307] = 0x1E44;
      composeMap[0x004E030C] = 0x0147;
      composeMap[0x004E0323] = 0x1E46;
      composeMap[0x004E0327] = 0x0145;
      composeMap[0x004E032D] = 0x1E4A;
      composeMap[0x004E0331] = 0x1E48;
      composeMap[0x004F0300] = 0x00D2;
      composeMap[0x004F0301] = 0x00D3;
      composeMap[0x004F0302] = 0x00D4;
      composeMap[0x004F0303] = 0x00D5;
      composeMap[0x004F0304] = 0x014C;
      composeMap[0x004F0306] = 0x014E;
      composeMap[0x004F0307] = 0x022E;
      composeMap[0x004F0308] = 0x00D6;
      composeMap[0x004F0309] = 0x1ECE;
      composeMap[0x004F030B] = 0x0150;
      composeMap[0x004F030C] = 0x01D1;
      composeMap[0x004F030F] = 0x020C;
      composeMap[0x004F0311] = 0x020E;
      composeMap[0x004F031B] = 0x01A0;
      composeMap[0x004F0323] = 0x1ECC;
      composeMap[0x004F0328] = 0x01EA;
      composeMap[0x00500301] = 0x1E54;
      composeMap[0x00500307] = 0x1E56;
      composeMap[0x00520301] = 0x0154;
      composeMap[0x00520307] = 0x1E58;
      composeMap[0x0052030C] = 0x0158;
      composeMap[0x0052030F] = 0x0210;
      composeMap[0x00520311] = 0x0212;
      composeMap[0x00520323] = 0x1E5A;
      composeMap[0x00520327] = 0x0156;
      composeMap[0x00520331] = 0x1E5E;
      composeMap[0x00530301] = 0x015A;
      composeMap[0x00530302] = 0x015C;
      composeMap[0x00530307] = 0x1E60;
      composeMap[0x0053030C] = 0x0160;
      composeMap[0x00530323] = 0x1E62;
      composeMap[0x00530326] = 0x0218;
      composeMap[0x00530327] = 0x015E;
      composeMap[0x00540307] = 0x1E6A;
      composeMap[0x0054030C] = 0x0164;
      composeMap[0x00540323] = 0x1E6C;
      composeMap[0x00540326] = 0x021A;
      composeMap[0x00540327] = 0x0162;
      composeMap[0x0054032D] = 0x1E70;
      composeMap[0x00540331] = 0x1E6E;
      composeMap[0x00550300] = 0x00D9;
      composeMap[0x00550301] = 0x00DA;
      composeMap[0x00550302] = 0x00DB;
      composeMap[0x00550303] = 0x0168;
      composeMap[0x00550304] = 0x016A;
      composeMap[0x00550306] = 0x016C;
      composeMap[0x00550308] = 0x00DC;
      composeMap[0x00550309] = 0x1EE6;
      composeMap[0x0055030A] = 0x016E;
      composeMap[0x0055030B] = 0x0170;
      composeMap[0x0055030C] = 0x01D3;
      composeMap[0x0055030F] = 0x0214;
      composeMap[0x00550311] = 0x0216;
      composeMap[0x0055031B] = 0x01AF;
      composeMap[0x00550323] = 0x1EE4;
      composeMap[0x00550324] = 0x1E72;
      composeMap[0x00550328] = 0x0172;
      composeMap[0x0055032D] = 0x1E76;
      composeMap[0x00550330] = 0x1E74;
      composeMap[0x00560303] = 0x1E7C;
      composeMap[0x00560323] = 0x1E7E;
      composeMap[0x00570300] = 0x1E80;
      composeMap[0x00570301] = 0x1E82;
      composeMap[0x00570302] = 0x0174;
      composeMap[0x00570307] = 0x1E86;
      composeMap[0x00570308] = 0x1E84;
      composeMap[0x00570323] = 0x1E88;
      composeMap[0x00580307] = 0x1E8A;
      composeMap[0x00580308] = 0x1E8C;
      composeMap[0x00590300] = 0x1EF2;
      composeMap[0x00590301] = 0x00DD;
      composeMap[0x00590302] = 0x0176;
      composeMap[0x00590303] = 0x1EF8;
      composeMap[0x00590304] = 0x0232;
      composeMap[0x00590307] = 0x1E8E;
      composeMap[0x00590308] = 0x0178;
      composeMap[0x00590309] = 0x1EF6;
      composeMap[0x00590323] = 0x1EF4;
      composeMap[0x005A0301] = 0x0179;
      composeMap[0x005A0302] = 0x1E90;
      composeMap[0x005A0307] = 0x017B;
      composeMap[0x005A030C] = 0x017D;
      composeMap[0x005A0323] = 0x1E92;
      composeMap[0x005A0331] = 0x1E94;
      composeMap[0x00610300] = 0x00E0;
      composeMap[0x00610301] = 0x00E1;
      composeMap[0x00610302] = 0x00E2;
      composeMap[0x00610303] = 0x00E3;
      composeMap[0x00610304] = 0x0101;
      composeMap[0x00610306] = 0x0103;
      composeMap[0x00610307] = 0x0227;
      composeMap[0x00610308] = 0x00E4;
      composeMap[0x00610309] = 0x1EA3;
      composeMap[0x0061030A] = 0x00E5;
      composeMap[0x0061030C] = 0x01CE;
      composeMap[0x0061030F] = 0x0201;
      composeMap[0x00610311] = 0x0203;
      composeMap[0x00610323] = 0x1EA1;
      composeMap[0x00610325] = 0x1E01;
      composeMap[0x00610328] = 0x0105;
      composeMap[0x00620307] = 0x1E03;
      composeMap[0x00620323] = 0x1E05;
      composeMap[0x00620331] = 0x1E07;
      composeMap[0x00630301] = 0x0107;
      composeMap[0x00630302] = 0x0109;
      composeMap[0x00630307] = 0x010B;
      composeMap[0x0063030C] = 0x010D;
      composeMap[0x00630327] = 0x00E7;
      composeMap[0x00640307] = 0x1E0B;
      composeMap[0x0064030C] = 0x010F;
      composeMap[0x00640323] = 0x1E0D;
      composeMap[0x00640327] = 0x1E11;
      composeMap[0x0064032D] = 0x1E13;
      composeMap[0x00640331] = 0x1E0F;
      composeMap[0x00650300] = 0x00E8;
      composeMap[0x00650301] = 0x00E9;
      composeMap[0x00650302] = 0x00EA;
      composeMap[0x00650303] = 0x1EBD;
      composeMap[0x00650304] = 0x0113;
      composeMap[0x00650306] = 0x0115;
      composeMap[0x00650307] = 0x0117;
      composeMap[0x00650308] = 0x00EB;
      composeMap[0x00650309] = 0x1EBB;
      composeMap[0x0065030C] = 0x011B;
      composeMap[0x0065030F] = 0x0205;
      composeMap[0x00650311] = 0x0207;
      composeMap[0x00650323] = 0x1EB9;
      composeMap[0x00650327] = 0x0229;
      composeMap[0x00650328] = 0x0119;
      composeMap[0x0065032D] = 0x1E19;
      composeMap[0x00650330] = 0x1E1B;
      composeMap[0x00660307] = 0x1E1F;
      composeMap[0x00670301] = 0x01F5;
      composeMap[0x00670302] = 0x011D;
      composeMap[0x00670304] = 0x1E21;
      composeMap[0x00670306] = 0x011F;
      composeMap[0x00670307] = 0x0121;
      composeMap[0x0067030C] = 0x01E7;
      composeMap[0x00670327] = 0x0123;
      composeMap[0x00680302] = 0x0125;
      composeMap[0x00680307] = 0x1E23;
      composeMap[0x00680308] = 0x1E27;
      composeMap[0x0068030C] = 0x021F;
      composeMap[0x00680323] = 0x1E25;
      composeMap[0x00680327] = 0x1E29;
      composeMap[0x0068032E] = 0x1E2B;
      composeMap[0x00680331] = 0x1E96;
      composeMap[0x00690300] = 0x00EC;
      composeMap[0x00690301] = 0x00ED;
      composeMap[0x00690302] = 0x00EE;
      composeMap[0x00690303] = 0x0129;
      composeMap[0x00690304] = 0x012B;
      composeMap[0x00690306] = 0x012D;
      composeMap[0x00690308] = 0x00EF;
      composeMap[0x00690309] = 0x1EC9;
      composeMap[0x0069030C] = 0x01D0;
      composeMap[0x0069030F] = 0x0209;
      composeMap[0x00690311] = 0x020B;
      composeMap[0x00690323] = 0x1ECB;
      composeMap[0x00690328] = 0x012F;
      composeMap[0x00690330] = 0x1E2D;
      composeMap[0x006A0302] = 0x0135;
      composeMap[0x006A030C] = 0x01F0;
      composeMap[0x006B0301] = 0x1E31;
      composeMap[0x006B030C] = 0x01E9;
      composeMap[0x006B0323] = 0x1E33;
      composeMap[0x006B0327] = 0x0137;
      composeMap[0x006B0331] = 0x1E35;
      composeMap[0x006C0301] = 0x013A;
      composeMap[0x006C030C] = 0x013E;
      composeMap[0x006C0323] = 0x1E37;
      composeMap[0x006C0327] = 0x013C;
      composeMap[0x006C032D] = 0x1E3D;
      composeMap[0x006C0331] = 0x1E3B;
      composeMap[0x006D0301] = 0x1E3F;
      composeMap[0x006D0307] = 0x1E41;
      composeMap[0x006D0323] = 0x1E43;
      composeMap[0x006E0300] = 0x01F9;
      composeMap[0x006E0301] = 0x0144;
      composeMap[0x006E0303] = 0x00F1;
      composeMap[0x006E0307] = 0x1E45;
      composeMap[0x006E030C] = 0x0148;
      composeMap[0x006E0323] = 0x1E47;
      composeMap[0x006E0327] = 0x0146;
      composeMap[0x006E032D] = 0x1E4B;
      composeMap[0x006E0331] = 0x1E49;
      composeMap[0x006F0300] = 0x00F2;
      composeMap[0x006F0301] = 0x00F3;
      composeMap[0x006F0302] = 0x00F4;
      composeMap[0x006F0303] = 0x00F5;
      composeMap[0x006F0304] = 0x014D;
      composeMap[0x006F0306] = 0x014F;
      composeMap[0x006F0307] = 0x022F;
      composeMap[0x006F0308] = 0x00F6;
      composeMap[0x006F0309] = 0x1ECF;
      composeMap[0x006F030B] = 0x0151;
      composeMap[0x006F030C] = 0x01D2;
      composeMap[0x006F030F] = 0x020D;
      composeMap[0x006F0311] = 0x020F;
      composeMap[0x006F031B] = 0x01A1;
      composeMap[0x006F0323] = 0x1ECD;
      composeMap[0x006F0328] = 0x01EB;
      composeMap[0x00700301] = 0x1E55;
      composeMap[0x00700307] = 0x1E57;
      composeMap[0x00720301] = 0x0155;
      composeMap[0x00720307] = 0x1E59;
      composeMap[0x0072030C] = 0x0159;
      composeMap[0x0072030F] = 0x0211;
      composeMap[0x00720311] = 0x0213;
      composeMap[0x00720323] = 0x1E5B;
      composeMap[0x00720327] = 0x0157;
      composeMap[0x00720331] = 0x1E5F;
      composeMap[0x00730301] = 0x015B;
      composeMap[0x00730302] = 0x015D;
      composeMap[0x00730307] = 0x1E61;
      composeMap[0x0073030C] = 0x0161;
      composeMap[0x00730323] = 0x1E63;
      composeMap[0x00730326] = 0x0219;
      composeMap[0x00730327] = 0x015F;
      composeMap[0x00740307] = 0x1E6B;
      composeMap[0x00740308] = 0x1E97;
      composeMap[0x0074030C] = 0x0165;
      composeMap[0x00740323] = 0x1E6D;
      composeMap[0x00740326] = 0x021B;
      composeMap[0x00740327] = 0x0163;
      composeMap[0x0074032D] = 0x1E71;
      composeMap[0x00740331] = 0x1E6F;
      composeMap[0x00750300] = 0x00F9;
      composeMap[0x00750301] = 0x00FA;
      composeMap[0x00750302] = 0x00FB;
      composeMap[0x00750303] = 0x0169;
      composeMap[0x00750304] = 0x016B;
      composeMap[0x00750306] = 0x016D;
      composeMap[0x00750308] = 0x00FC;
      composeMap[0x00750309] = 0x1EE7;
      composeMap[0x0075030A] = 0x016F;
      composeMap[0x0075030B] = 0x0171;
      composeMap[0x0075030C] = 0x01D4;
      composeMap[0x0075030F] = 0x0215;
      composeMap[0x00750311] = 0x0217;
      composeMap[0x0075031B] = 0x01B0;
      composeMap[0x00750323] = 0x1EE5;
      composeMap[0x00750324] = 0x1E73;
      composeMap[0x00750328] = 0x0173;
      composeMap[0x0075032D] = 0x1E77;
      composeMap[0x00750330] = 0x1E75;
      composeMap[0x00760303] = 0x1E7D;
      composeMap[0x00760323] = 0x1E7F;
      composeMap[0x00770300] = 0x1E81;
      composeMap[0x00770301] = 0x1E83;
      composeMap[0x00770302] = 0x0175;
      composeMap[0x00770307] = 0x1E87;
      composeMap[0x00770308] = 0x1E85;
      composeMap[0x0077030A] = 0x1E98;
      composeMap[0x00770323] = 0x1E89;
      composeMap[0x00780307] = 0x1E8B;
      composeMap[0x00780308] = 0x1E8D;
      composeMap[0x00790300] = 0x1EF3;
      composeMap[0x00790301] = 0x00FD;
      composeMap[0x00790302] = 0x0177;
      composeMap[0x00790303] = 0x1EF9;
      composeMap[0x00790304] = 0x0233;
      composeMap[0x00790307] = 0x1E8F;
      composeMap[0x00790308] = 0x00FF;
      composeMap[0x00790309] = 0x1EF7;
      composeMap[0x0079030A] = 0x1E99;
      composeMap[0x00790323] = 0x1EF5;
      composeMap[0x007A0301] = 0x017A;
      composeMap[0x007A0302] = 0x1E91;
      composeMap[0x007A0307] = 0x017C;
      composeMap[0x007A030C] = 0x017E;
      composeMap[0x007A0323] = 0x1E93;
      composeMap[0x007A0331] = 0x1E95;

    }


    ~Basic_Latin0() {
    }

    UCS4 firstLetter() {
      return my_first_letter;
    }
 
    UCS4 lastLetter() {
      return my_last_letter;
    }
 
    // query functions:

    string blockname(const UCS4 & _uc) const {
      return "Basic Latin";
    }

    bool isDefined(const UCS4 & _uc) const {
      return 1;
    }

    UCS4 uppercase(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Basic_Latin0::upper[_uc - my_first_letter];
    }

    UCS4 lowercase(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Basic_Latin0::lower[_uc - my_first_letter];
    }

    UCS4 titlecase(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Basic_Latin0::title[_uc - my_first_letter];
    }

    int decDigitValue(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      switch(_uc) {
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
        throw UndefinedProperty(_uc, PROP_DEC_DIGIT_VALUE);
      }
    }

    int digitValue(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      switch(_uc) {
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
        throw UndefinedProperty(_uc, PROP_DIGIT_VALUE);
      }
    }

    float numericValue(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      switch(_uc) {
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
        throw UndefinedProperty(_uc, PROP_NUMERIC_VALUE);
      }
    }

    Gen_Cat category(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Gen_Cat(Basic_Latin0::cat[_uc - my_first_letter]);
    }

    Can_Comb_Class combClass(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Can_Comb_Class(0);
    }

    Bidir_Props bidirProps(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Bidir_Props(Basic_Latin0::bidir[_uc - my_first_letter]);
    }

    Char_Decomp decompType(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Char_Decomp(DECOMP_NO_DECOMP);
    }

    UTF32String decompose(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      UTF32String _us;
      _us.resize(1); _us[0]=_uc;
      return _us;
    }

    bool mustMirror(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Basic_Latin0::mirror[_uc - my_first_letter];
    }

    Line_Break linebreak(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::Line_Break(Basic_Latin0::lb[_uc - my_first_letter]);
    }

    EA_Width EAWidth(const UCS4 & _uc) const {
      if (!isDefined(_uc))
        throw UndefinedProperty(_uc, PROP_CHARACTER);
      return Babylon::EA_Width(Basic_Latin0::ea[_uc - my_first_letter]);
    }

    UCS4 compose (const UCS4 & starter, const UCS4 & last) {
      return composeMap[starter << 16 | last];
    }

    bool is_Zero_width(const UCS4 & _uc) const {
      return 0;
    }

    bool is_White_space(const UCS4 & _uc) const {
      return Basic_Latin0::White_space[_uc - my_first_letter];
    }

    bool is_Non_break(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Bidi_Control(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Join_Control(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Format_Control(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Dash(const UCS4 & _uc) const {
      return Basic_Latin0::Dash[_uc - my_first_letter];
    }

    bool is_Hyphen(const UCS4 & _uc) const {
      return Basic_Latin0::Hyphen[_uc - my_first_letter];
    }

    bool is_Quotation_Mark(const UCS4 & _uc) const {
      return Basic_Latin0::Quotation_Mark[_uc - my_first_letter];
    }

    bool is_Terminal_Punctuation(const UCS4 & _uc) const {
      return Basic_Latin0::Terminal_Punctuation[_uc - my_first_letter];
    }

    bool is_Math(const UCS4 & _uc) const {
      return Basic_Latin0::Math[_uc - my_first_letter];
    }

    bool is_Paired_Punctuation(const UCS4 & _uc) const {
      return Basic_Latin0::Paired_Punctuation[_uc - my_first_letter];
    }

    bool is_Left_of_Pair(const UCS4 & _uc) const {
      return Basic_Latin0::Left_of_Pair[_uc - my_first_letter];
    }

    bool is_Combining(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Non_spacing(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Hex_Digit(const UCS4 & _uc) const {
      return Basic_Latin0::Hex_Digit[_uc - my_first_letter];
    }

    bool is_Alphabetic(const UCS4 & _uc) const {
      return Basic_Latin0::Alphabetic[_uc - my_first_letter];
    }

    bool is_Diacritic(const UCS4 & _uc) const {
      return Basic_Latin0::Diacritic[_uc - my_first_letter];
    }

    bool is_Extender(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Identifier_Part(const UCS4 & _uc) const {
      return Basic_Latin0::Identifier_Part[_uc - my_first_letter];
    }

    bool is_Ignorable_Control(const UCS4 & _uc) const {
      return Basic_Latin0::Ignorable_Control[_uc - my_first_letter];
    }

    bool is_Bidi_Hebrew_Right_to_Left(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Bidi_Arabic_Right_to_Left(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Bidi_Embedding_or_Override(const UCS4 & _uc) const {
      return 0;
    }

    bool is_Uppercase(const UCS4 & _uc) const {
      return Basic_Latin0::Uppercase[_uc - my_first_letter];
    }

    bool is_Lowercase(const UCS4 & _uc) const {
      return Basic_Latin0::Lowercase[_uc - my_first_letter];
    }

    bool is_Space(const UCS4 & _uc) const {
      return (isDefined(_uc) && category(_uc) == CAT_Zs);
    }

    bool is_ISO_Control(const UCS4 & _uc) const {
      return (isDefined(_uc) && category(_uc) == CAT_Cc);
    }

    bool is_Punctuation(const UCS4 & _uc) const {
      return (isDefined(_uc) && (category(_uc) == CAT_Pc ||
                                 category(_uc) == CAT_Pd ||
                                 category(_uc) == CAT_Ps ||
                                 category(_uc) == CAT_Pe ||
                                 category(_uc) == CAT_Pi ||
                                 category(_uc) == CAT_Pf ||
                                 category(_uc) == CAT_Po)
             );
    }

    bool is_Line_Separator(const UCS4 & _uc) const {
      return (isDefined(_uc) && category(_uc) == CAT_Zl);
    }

    bool is_Paragraph_Separator(const UCS4 & _uc) const {
      return (isDefined(_uc) && category(_uc) == CAT_Zp);
    }

    bool is_Currency_Symbol(const UCS4 & _uc) const {
      return (isDefined(_uc) && category(_uc) == CAT_Sc);
    }

    bool is_Titlecase(const UCS4 & _uc) const {
      return (isDefined(_uc) && category(_uc) == CAT_Lt);
    }


  private:
    // functions
    Basic_Latin0(const Basic_Latin0 &) {}
 
    Babylon::UCS4 my_first_letter;
    Babylon::UCS4 my_last_letter;
    static const UCS4 upper[128];
    static const UCS4 lower[128];
    static const UCS4 title[128];
    static const unsigned char cat[128];
    static const unsigned char bidir[128];
    static const bool mirror[128];
    static const unsigned char lb[128];
    static const unsigned char ea[128];
    map<UCS4, UCS4> composeMap;
    static const bool White_space[128];
    static const bool Dash[128];
    static const bool Hyphen[128];
    static const bool Quotation_Mark[128];
    static const bool Terminal_Punctuation[128];
    static const bool Math[128];
    static const bool Paired_Punctuation[128];
    static const bool Left_of_Pair[128];
    static const bool Hex_Digit[128];
    static const bool Alphabetic[128];
    static const bool Diacritic[128];
    static const bool Identifier_Part[128];
    static const bool Ignorable_Control[128];
    static const bool Uppercase[128];
    static const bool Lowercase[128];

  }; // class Basic_Latin0

  const UCS4 Basic_Latin0::upper[] = {
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

  const UCS4 Basic_Latin0::lower[] = {
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

  const UCS4 Basic_Latin0::title[] = {
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

  const unsigned char Basic_Latin0::cat[] = {
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

  const unsigned char Basic_Latin0::bidir[] = {
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

  const bool Basic_Latin0::mirror[] = {
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

  const unsigned char Basic_Latin0::lb[] = {
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

  const unsigned char Basic_Latin0::ea[] = {
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

    const bool Basic_Latin0::White_space[] = {
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

    const bool Basic_Latin0::Dash[] = {
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

    const bool Basic_Latin0::Hyphen[] = {
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

    const bool Basic_Latin0::Quotation_Mark[] = {
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

    const bool Basic_Latin0::Terminal_Punctuation[] = {
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

    const bool Basic_Latin0::Math[] = {
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

    const bool Basic_Latin0::Paired_Punctuation[] = {
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

    const bool Basic_Latin0::Left_of_Pair[] = {
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

    const bool Basic_Latin0::Hex_Digit[] = {
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

    const bool Basic_Latin0::Alphabetic[] = {
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

    const bool Basic_Latin0::Diacritic[] = {
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

    const bool Basic_Latin0::Identifier_Part[] = {
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

    const bool Basic_Latin0::Ignorable_Control[] = {
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

    const bool Basic_Latin0::Uppercase[] = {
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
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    const bool Basic_Latin0::Lowercase[] = {
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
        0, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 0, 0, 0, 0, 0
    };

}; // namespace Babylon
 
dload(Babylon::Basic_Latin0);
