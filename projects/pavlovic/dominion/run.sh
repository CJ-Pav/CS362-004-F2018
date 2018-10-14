#!/bin/bash

# compile
make clean
reset
make all

if [ $? -eq 0 ]; then
    ./playdom 30
else
    echo "Error: compiler exited with non-zero status" >&2
    exit 1
fi

exit 0
