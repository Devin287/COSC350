#!/bin/sh
# task7.sh

echo "Choose an odd number 1 or greater"
read num
fact=1
    #sums factorial until desired number
    while [ $num -gt 1 ]
    do
        fact=` expr $fact \* $num `
        num=` expr $num - 1 `
    done
    echo $fact

    exit 0