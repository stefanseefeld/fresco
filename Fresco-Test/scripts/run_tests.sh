#!/bin/sh

# This script runs all tests of all test programs given on the commandline
# and returns an exitcode of 0 if all tests passed or 1 if one or more tests
# failed.
#
# Additionally you can specify tests to run with the FRESCO_TESTS environment
# variable. Make sure all test programs know the test routines given there!
#
# It is meant as a quick and dirty way to run our tests from a Makefile
# without needing to register all tests with qmtest manually.

TEST_LOG=test.log

ALL_PASSED=1



run_test ()
{
    TESTPROG="$1"
    for TEST in ${FRESCO_TESTS:-`$TESTPROG list`} ; do
        if ! $TESTPROG run $TEST | tee -a $TEST_LOG | egrep -q '^Result:[[:space:]]+PASS'; then
            echo "Test $TEST in $TESTPROG FAILED!"
            ALL_PASSED=0;
	else
	    echo "Test $TEST in $TESTPROG passed."
        fi
    done
}

date >> $TEST_LOG
echo "Running \"$*\":" >> $TEST_LOG
echo "Using LD_LIBRARY_PATH=$LD_LIBRARY_PATH" >> $TEST_LOG
echo >> $TEST_LOG

for CURRENT in "$@"; do
    run_test "$CURRENT"
done

if [ $ALL_PASSED -eq 0 ]; then
    exit 1
fi

exit 0
