#! /bin/bash
#
# This just sets up the glyph database, sets some environment paths, 
# and runs a program from the test/ directory
#

export WARSAW=`pwd`/modules
export LD_LIBRARY_PATH=`pwd`/lib:$LD_LIBRARY_PATH
export GLYPH_DB=`pwd`/etc/glyphs.db

if  [[ ! (-e $GLYPH_DB) ]]; then
    test/buildDB etc/unifont.hex $GLYPH_DB;
fi

exec test/$1
