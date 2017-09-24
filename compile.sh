if [ "$#" -lt 1 ]; then
    echo "You must provide an input file!"
else
    ./bin/mmc "$1" vmipssoc/src/main.S
fi