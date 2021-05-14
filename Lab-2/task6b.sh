#!/bin/sh
# task6a.sh

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

    numD=`expr $num - 2`
    for i  in `seq 1 2 $numD`;
    do
        for s in `seq $i $num`;
        do
            echo -n " "
        done

        for j  in `seq 1 $i` ;
        do
            echo -n "*"
        done
        echo
    done
    
    tail=`expr $tail + $num`
    
    for j  in `seq 1 $tail` ;
    do
        echo -n "*"
    done

    for i  in `seq $numD -2 1`;
    do
        echo
        for s in `seq $num -1 $i`;
        do
            echo -n " "
        done

        for j in `seq 1 $i`;
        do
            echo -n "*"
        done 
        
    done
    exit 1
fi