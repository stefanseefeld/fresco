#!/bin/sh
#

#by default, run autoconf in each package
packages="Prague Babylon Warsaw Server Clients-C++ Clients-Python Clients-Java Clients-Perl Docs"

# Touch the timestamps on all the files since CVS messes them up
#directory=`dirname $0`
#touch $directory/configure.in

# Regenerate configuration files
echo "Generating configure...";
aclocal -I config/macros
autoconf

for package in $packages;
    do
    if test -d config/$package; then
	(cd config/$package;
	 echo Generating config/${package}/configure...;
	 aclocal -I ../macros;
	 if test -f acconfig.h; then
	    autoheader configure.in > config.hh.in
	 fi;
	 autoconf)
    fi
    done
