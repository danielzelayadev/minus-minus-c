#!/bin/bash

if [ "$#" -lt 1 ]; then
    echo -e "\e[31mYou must provide the path for the sample of the snapshot!"
else
    fname=$(basename -s .c $1).s
    ./bin/mmc "$1" "snapshots/$fname" > /dev/null
    echo -e "\e[32mSnapshot created."
fi