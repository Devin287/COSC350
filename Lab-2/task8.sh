#!/bin/sh
# task8.sh

#checks for one parameter if not exits 
if [ $# -gt 1 ]; then
    echo "Too many parameters"
    exit 0
else
    num=$1
    #adds the intergers
    while [ $num -gt 0 ]
    do
        rem=`expr $num % 10 `
        num=`expr $num / 10 `

        sum=`expr $sum + $rem `
    done
fi
echo "Sum of digit for number is $sum"

 
exit 0