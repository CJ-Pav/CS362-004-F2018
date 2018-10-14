#!/bin/bash -e
# Author: Chris Pavlovich
# Purpose: Compile & run assignment

# init status
status=0

# compile
make clean
reset
make all

# set status
status=$?

# run if no errors, error & exit otherwise
if [ $status -eq 0 ]; then
    ./playdom 30
else
    echo "Error: compiler exited with non-zero status" >&2
    status=1
fi

exit $status
