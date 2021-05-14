#!/bin/sh

#checks for one parameter if not exits 
if [ $# -gt 1 ]; then
    echo "Too many parameters"
    exit 0
else
    num=$1
    #adds the intergers
    while [ $num -gt 0 ]
    do
        sum=`expr $sum + $num `
    done
fi
echo "Sum of digit for number is $sum"
    
    return c;
 
exit 0