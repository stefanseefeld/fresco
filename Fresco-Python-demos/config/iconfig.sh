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

CONFIGURE_OPTIONS=""

query_word "Prefix for omniORBpy: [none] " --with-omniorbpy-prefix

echo $CONFIGURE_OPTIONS | sed 's/^ +//' > config
