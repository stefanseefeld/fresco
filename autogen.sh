#!/bin/sh
#

conf() 
{
  if test -d $1; then
  (cd $1
   echo "Generating $1/configure..."
   aclocal --output=config/aclocal.m4 -I ../config
   autoconf --include=config)
  fi
}

conf_with_header() 
{
  if test -d $1; then
    (cd $1
     echo "Generating $1/configure..."
     aclocal --output=config/aclocal.m4 -I ../config
     autoconf --include=config
     autoheader -l config)
  fi
}

echo "Generating toplevel configure..."
autoconf
conf_with_header Prague
conf_with_header Babylon
conf_with_header Fresco
conf_with_header Berlin
conf GGI
conf SDL
conf Clients-C++
conf Clients-Python
conf Clients-Java
conf Clients-Perl
