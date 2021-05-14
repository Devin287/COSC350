#!/bin/bash

let sum=0
if [ $# -eq 0 ]; then
    echo "No arguments passed!";
    exit 0;
fi

for x in $*
do
    let sum=$sum+$x
done
echo "The sum is $sum";
exit 0;