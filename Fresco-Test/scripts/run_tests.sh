#!/bin/sh

# This script runs all tests given on the commandline and returns an
# exitcode of 0 if all tests passed or 1 if one or more tests failed.
#
# It is meant as a quick and dirty way to run our tests from a Makefile
# without needing to register all tests with qmtest manually.

ALL_PASSED=1

function run_test()
{
    TESTPROG="$1"
    for TEST in `$TESTPROG list` ; do
        if ! $TESTPROG run $TEST | egrep -q '^Result:[[:space:]]+PASS'; then
            echo "Test $TEST in $TESTPROG FAILED!"
            ALL_PASSED=0;
	else
	    echo "Test $TEST in $TESTPROG passed."
        fi
    done
}

for CURRENT in "$@"; do
    run_test "$CURRENT"
done

if [ ALL_PASSED == 0 ]; then
    exit 1
fi

exit 0
