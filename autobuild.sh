#!/bin/sh
#

packages="Prague Babylon Fresco Berlin Clients-C++ Clients-Python Clients-Java Clients-Perl GGI SDL"

for package in $packages;
    do
    if test -d $package; then
	(cd $package;
	 echo configuring ${package}...
	 ./configure --prefix=`cd ..;pwd;` "$@"
         make -s install)
    fi
    done
