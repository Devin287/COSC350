#!/bin/sh

    num=0
    for i in $@; 
    do 
        if [ `expr $i % 2` != 0 ]; then
            num=`expr $num + $i`
        fi
    done 
    echo "The sum is: $num"

exit 0