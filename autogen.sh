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
     autoheader --include=config)
  fi
}

echo "Generating toplevel configure..."
autoconf
conf_with_header Prague
conf_with_header Babylon
conf Fresco-IDL
conf_with_header Fresco-C++
conf_with_header Berlin
conf_with_header GGI
conf SDL
conf Fresco-Python
conf Fresco-Java
conf Fresco-Perl
conf Fresco-C++-demos
conf Fresco-Python-demos
