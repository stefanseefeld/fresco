//
// $Id$
//
// This source file is a part of the Berlin Project.
// Copyright (C) 1998 Graydon Hoare <graydon@pobox.com> 
// http://www.berlin-consortium.org
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public License
// as published by the Free Software Foundation; either version 2 of
// the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
//
//
// this program reads the unifont format as specified on
// http://czyborra.com/unifont/ and writes a berkeley DB file appropriate for
// rendering said font using an openGL "glbitmap()" call.
//
// it is to be used when building berlin for distribution, so that we can have a
// nice default font which can at least show a primitive version of most
// languages.
//

#include <db2/db_cxx.h>
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char **argv) {

    if (argc != 3) {
	cerr << "usage: buildDB <input-filename> <output-db-name>" << endl;
    }

    ifstream from(argv[1]);

    Db *glyphdb;
    Db::open(argv[2], DB_BTREE, DB_CREATE, 0644, NULL, NULL, &glyphdb);

    unsigned int sz;
    unsigned short unichar ;
    Dbt glyph;

    Dbt key;
    key.set_size(2); // unicode values -- 2 bytes

    char line[256]; // next line of input from unicode DB
    char codepoint[5]; // textual hex representation of unicode code point
    char glyphdata[65]; // textual hex representation of glyph
    unsigned char glyphbuf[32]; // decoded glyph in numeric form      

    memset(codepoint,0,5); // clear codepoint buffer      
    memset(line,0,256); // clear line buffer

    while (from.getline(line,256)) {	  

	memcpy(codepoint,line,4); // pull out first 4 digits as codepoint	  
	memset(glyphdata,0,65);  // clear buffer
	memcpy(glyphdata,line+5,64); // next 32 - 64 digits as glyph data	  
	unichar = (unsigned short)(strtol(codepoint,NULL,16)); // convert codepoint
	sz = strlen(glyphdata); // measure glyph data to determine image width	  
	char tmp[3]; // buffer for converting 2 hex digits to 1 unsigned char
	memset(tmp,0,3);
	  
	// we loop backwards over glyph because we are storing in a GL-friendly
	// format. GL renders bitmaps "up" the screen, bottom-to-top.
	for (int i = (sz - 2); i >= 0; i-=2) {  
	    int k = i / 2;
	    memcpy(tmp,glyphdata + i,2);
	    if (sz == 32) { 
		// halfwidth glyphs
		int j = (k % 2 == 0) ? k + 1 : i - 1;
		glyphbuf[j] = (unsigned char)(strtol(tmp,NULL,16));
	    } else {
		// fullwidth glyphs
		glyphbuf[k] = (unsigned char)(strtol(tmp,NULL,16));
	    }		
	}
	  
	glyph.set_size(sz/2); // load into DBT ("data base thang", literally)
	glyph.set_data(glyphbuf);
	key.set_data(&unichar);
	glyphdb->put(NULL,&key,&glyph,0);
    }
    glyphdb->close(0);
}

