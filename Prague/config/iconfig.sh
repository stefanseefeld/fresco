#! /bin/sh

source ../iconfig-funcs.sh

CONFIGURE_OPTIONS=""

query_word "Compile with tracer support? [no] " --enable-tracer
query_word "Compile all Unicode blocks or just Latin? [complete] " --enable-unicode-blocks

echo $CONFIGURE_OPTIONS | sed 's/^ +//' > config
