#!/bin/sh
#
# This just sets up the glyph database, sets some environment paths, 
# and runs a program from the test/ directory
#

export BERLIN_ROOT=`pwd`
export WARSAW=$BERLIN_ROOT/modules
export LD_LIBRARY_PATH=$BERLIN_ROOT/lib:$LD_LIBRARY_PATH
export BERLIN_DATA=$BERLIN_ROOT/etc
export GLYPH_DB=$BERLIN_DATA/glyph.db

exec test/$1
