#!/bin/sh 
num=0
for i in $@; 
do 
    num=`expr $num + $i` 
done 
echo "The sum is: $num"

exit 0 