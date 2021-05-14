#!/bin/sh
# task6b.sh

echo "Choose an odd number 3 or greater"
read num

if [ `expr $num % 2` -eq 0 ]; then
    echo "This even, enter a odd number greater than 3"
    exit 1
fi

if [ $num -lt 3 ]; then
    echo "This number is less than 3 enter a bigger number"
    exit 1
else
    echo "Choose the tail size for arrow"
    read tail

    numD2=`expr $num + $tail` 
    end=`expr $num - 1`

    for i  in `seq 1 2 $end`;
    do
        for s in `seq 1 $tail`;
        do
            echo -n " "
        done

        for j  in `seq 1 $i` ;
        do
            echo -n "*"
        done
        echo
    done

    for j  in `seq 1 $numD2` ;
    do
        echo -n "*"
    done
    echo

    numD=`expr $num - 2`

    for i  in `seq $numD -2 1`;
    do
        for s in `seq 1 $tail`;
        do
            echo -n " "
        done

        for j in `seq 1 $i`;
        do
            echo -n "*"
        done 
        echo
    done
    exit 1
fi