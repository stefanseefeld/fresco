#!/bin/sh
#

packages="Prague Babylon Fresco Berlin Clients-C++ Clients-Python Clients-Java Clients-Perl GGI SDL"

for package in $packages;
    do
    if test -d $package; then
	(cd $package;
	 echo Generating ${package}/configure...
	 aclocal --output=config/aclocal.m4 -I ../config/macros
	 if test -f config/acconfig.h; then
	    autoheader -l config configure.ac > config/config.hh.in
	 fi;
	 autoconf --include config
         chmod a+x configure)
    fi
    done
