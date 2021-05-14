#!/bin/sh

echo "Choose an odd number 3 or greater"
read num

if [ `expr $num % 2` -eq 0 ]; then
    echo "This even, enter a odd number greater than 3"
    exit 1
elif [ $num -lt 3 ]; then
    echo "This number is less than 3 enter a bigger number"
    exit 1
else

    numD=`expr $num - 1`
    for i  in `seq 1 2 $numD`;
    do
        for j  in `seq $i 2 $num` ;
        do
            echo -n " "
        done
        for k in `seq 1 $i`;
        do
            echo -n "*"
        done 
        echo
    done
fi 
exit 0 