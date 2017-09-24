if [ "$#" -lt 1 ]; then
    ./bin/mmc samples/HelloWorld.c vmipssoc/src/main.S
    cd vmipssoc/src
    make run
    cd ../..
    ./bin/mmc samples/ForTest.c vmipssoc/src/main.S
    cd vmipssoc/src
    make run
    cd ../..
    ./bin/mmc samples/IfTest.c vmipssoc/src/main.S
    cd vmipssoc/src
    make run
    cd ../..
    ./bin/mmc samples/WhileTest.c vmipssoc/src/main.S
    cd vmipssoc/src
    make run
    cd ../..
    ./bin/mmc samples/ArithOperators.c vmipssoc/src/main.S
    cd vmipssoc/src
    make run
    cd ../..
    ./bin/mmc samples/RelOperators.c vmipssoc/src/main.S
    cd vmipssoc/src
    make run
    cd ../..
    ./bin/mmc samples/Globals.c vmipssoc/src/main.S
    cd vmipssoc/src
    make run
    cd ../..
    ./bin/mmc samples/MultipleFunctions.c vmipssoc/src/main.S
    cd vmipssoc/src
    make run
else
    ./bin/mmc "$1" vmipssoc/src/main.S
    cd vmipssoc/src
    make run
fi