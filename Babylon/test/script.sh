#!/bin/sh

# This is just a testscript.

if [ $1 = "list" ]; then
    echo script_test
    exit 0
fi

echo Result: PASSED
exit 0
