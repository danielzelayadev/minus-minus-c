#!/bin/bash

if [ "$#" -lt 1 ]; then
    echo "You must provide an input file!"
else
    dst=vmipssoc/src/main.S
    if [ "$#" -gt 1 ]; then
        dst="$2"
    fi
    ./bin/mmc "$1" "$dst"
fi