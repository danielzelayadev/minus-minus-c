#!/bin/bash

run () {
    ./bin/mmc "$1" vmipssoc/src/main.S
    cd vmipssoc/src
    make run
}

if [ "$#" -lt 1 ]; then
    cd vmipssoc/src
    make run
else
    if [ "$1" == "--all" ]; then
        for f in samples/*.c ; do  
            run "$f"
            cd ../.. ; 
        done
    else
        run "$1"
    fi
fi