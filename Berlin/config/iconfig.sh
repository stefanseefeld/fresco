#! /bin/sh

# query_word asks for a single word. It takes the following parameters:
#     1. The prompt
#     2. The switch to set equal to the answer
query_word () {
    read -e -p "$1" answer dummy
    if [ ! ".$answer" = "." ] ; then
	CONFIGURE_OPTIONS="$CONFIGURE_OPTIONS $2=$answer"
    fi
}

# query_line asks for a complete line. It takes the following parameters:
#     1. The prompt
#     2. The switch to set equal to the answer
query_line () {
    read -e -p "$1" answer
    if [ ! ".$answer" = "." ] ; then
	CONFIGURE_OPTIONS="$CONFIGURE_OPTIONS $2=\"$answer\""
    fi
}

CONFIGURE_OPTIONS=""

query_word "Build libBerlin? [yes] " --enable-berlin
query_line "Drawing Kits to build: [all] " --enable-drawing
query_line "Other Kits to build: [all] " --enable-kits
query_word "Build the server? [yes] " --enable-server
query_word "Prefix for FreeType 2: [none] " --with-freetype-prefix
query_word "Console to use: [GGI] " --with-console
query_word "Prefix for GGI: [none] " --with-ggi-prefix
query_word "Prefix for libArt: [none] " --with-art-prefix
query_word "Prefix for GGIMesa: [none] " --with-ggimesa-prefix

echo $CONFIGURE_OPTIONS | sed 's/^ +//' > config
