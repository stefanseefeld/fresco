
*** Modified files in JOE when it aborted on Sat Oct 30 20:03:26 1999
*** JOE was aborted by signal 1

*** File 'runtest.sh'
#! /bin/bash
#
# This just sets up the glyph database, sets some environment paths, 
# and runs a program from the test/ directory
#

export WARSAW=`pwd`/modules
export LD_LIBRARY_PATH=`pwd`/lib:$LD_LIBRARY_PATH
export BERLIN_DATA=`pwd`/etc
export GLYPH_DB=$BERLIN_DATA/glyph.db

if  [[ ! (-e $GLYPH_DB) ]]; then
    test/buildDB etc/unifont.hex $GLYPH_DB;
fi

exec test/$1
