
#!/bin/bash

test () {
    snapName=snapshots/$(basename -s .c "$1").s
    if [ -e "$snapName" ]; then
        ./compile.sh "$1" cmp/out.s > /dev/null
        sort cmp/out.s > cmp/actual.s
        sort "$snapName" > cmp/expected.s
        output=$(diff cmp/actual.s cmp/expected.s)
        len=${#output}
        if [ $len -gt 0 ]; then
            echo -e "\e[31m$1 test failed."
        else
            echo -e "\e[32m$1 test success."
        fi
    fi
}

mkdir -p cmp
if [ "$#" -lt 1 ]; then
    for f in samples/*.c ; do  
       test "$f"
    done
else
    test "$1"
fi
rm -r cmp