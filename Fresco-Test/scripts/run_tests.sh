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
    ALL_PASSED=1;
    echo "Running test in $TESTPROG:"
    echo "PROCESSING: $TESTPROG" >> $TEST_LOG
    for TEST in ${FRESCO_TESTS:-`$TESTPROG list`} ; do
        if ! $TESTPROG run $TEST | tee -a $TEST_LOG | egrep -q '^Result:[[:space:]]+PASS'; then
            echo "    FAILED: Test $TEST in $TESTPROG FAILED!"
            CAUSE=$(tail -n5 $TEST_LOG | egrep '^Cause:[[:space:]]' | \
                sed -e 's/^Cause: //')
            echo "            $CAUSE"
            ALL_PASSED=0;
	else
	    echo "    passed: Test $TEST in $TESTPROG passed."
        fi
        echo "" >> $TEST_LOG
    done
    if test ALL_PASSED = 0; then
        echo "One or more tests in $TESTPROG FAILED."
        echo "STATUS: $TESTPROG FAILED." >> $TEST_LOG
    else
        echo "All tests in $TESTPROG processed: OK."
        echo "STATUS: $TESTPROG OK." >> $TEST_LOG
    fi
    echo
    echo >> $TEST_LOG
}

date >> $TEST_LOG
echo "Running \"$*\":" >> $TEST_LOG
echo "Using LD_LIBRARY_PATH=$LD_LIBRARY_PATH" >> $TEST_LOG
echo >> $TEST_LOG

for CURRENT in "$@"; do
    echo "--------------------------------------------------------------" \
        >> $TEST_LOG
    run_test "$CURRENT"
done
echo "--------------------------------------------------------------" \
    >> $TEST_LOG

if [ $ALL_PASSED -eq 0 ]; then
    exit 1
fi

exit 0
