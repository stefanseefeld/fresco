#!/bin/sh

export BABYLON_PATH=/usr/lib/Berlin/modules/Babylon
if [ $# == 0 ] ; then
  exec /usr/lib/Berlin/bin/server -r /usr/lib/Berlin/etc/berlinrc
else
  exec /usr/lib/Berlin/bin/server $*
fi
