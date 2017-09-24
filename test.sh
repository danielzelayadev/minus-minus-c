if [ "$#" -lt 1 ]; then
    for f in samples/*.c ; do  
        ./bin/mmc "$f" vmipssoc/src/main.S
        cd vmipssoc/src
        make run
        cd ../.. ; 
    done
else
    ./bin/mmc "$1" vmipssoc/src/main.S
    cd vmipssoc/src
    make run
fi