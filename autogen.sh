#!/bin/sh
#

packages="Prague Babylon Fresco Berlin Clients-C++ Clients-Python Clients-Java Clients-Perl GGI SDL"

for package in $packages;
    do
    if test -d $package; then
	(cd $package;
	 echo Generating ${package}/configure...
	 aclocal --output=config/aclocal.m4 -I ../config/macros
	 autoheader -l config configure.ac > config/acconfig.hh.in
	 autoconf --include=config
         chmod a+x configure)
    fi
    done
