#!/bin/sh
#

top_srcdir=`dirname $0`
packages="Prague Babylon Fresco Berlin Clients-C++ Clients-Python Clients-Java Clients-Perl GGI SDL"

for package in $packages;
    do
    if test -d ${top_srcdir}/${package}; then
	(mkdir -p $package;
	 cd $package;
	 echo configuring ${package}...
	 ../${top_srcdir}/${package}/configure --prefix=`cd ..;pwd;` "$@"
         make -s install)
    fi
    done
