
#!/bin/bash

passing=0
failing=0
count=0

test () {
    snapName=snapshots/$(basename -s .c "$1").s
    if [ -e "$snapName" ]; then
        ./compile.sh "$1" cmp/out.s > /dev/null
        sort cmp/out.s > cmp/actual.s
        sort "$snapName" > cmp/expected.s
        output=$(diff cmp/actual.s cmp/expected.s)
        len=${#output}
        if [ $len -gt 0 ]; then
            echo -e "\e[31m[FAILED]: $1"
            failing=$((failing + 1))
        else
            echo -e "\e[32m[SUCCESS]: $1"
            passing=$((passing + 1))
        fi
        count=$((count + 1))
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

echo -e "\e[0m"
echo "Passing $passing -- Failing $failing"
echo "$count test(s) ran."