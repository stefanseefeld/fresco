#! /bin/sh

CONFIGURE_OPTIONS=""

read -e -p "Which ORB do you want to use? [omniORB] " orbname dummy
if [ ! ".$orbname" = "." ] ; then
    CONFIGURE_OPTIONS="$CONFIGURE_OPTIONS --with-orb=$orbname"
fi

read -e -p "Prefix for omniORB: " orbprefix dummy
if [ ! ".$orbprefix" = "." ] ; then
    CONFIGURE_OPTIONS="$CONFIGURE_OPTIONS --with-omniorb-prefix=$orbprefix"
fi

echo $CONFIGURE_OPTIONS | sed 's/^ +//' > config
