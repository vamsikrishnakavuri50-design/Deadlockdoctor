#!/bin/bash

echo "========================================="
echo "   DEADLOCKDOCTOR AUTOMATED TESTS"
echo "========================================="

echo
echo "Compiling test program..."

gcc -Wall -Wextra -std=c11 -Iinclude \
    tests/test_banker.c \
    src/banker.c \
    -o tests/test_banker

if [ $? -ne 0 ]; then
    echo
    echo "Compilation FAILED"
    exit 1
fi

echo "Compilation successful."

echo
echo "Running tests..."
echo

./tests/test_banker

RESULT=$?

echo
echo "========================================="

if [ $RESULT -eq 0 ]; then
    echo "ALL TESTS PASSED"
else
    echo "SOME TESTS FAILED"
fi

echo "========================================="

exit $RESULT
