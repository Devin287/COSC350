#!/bin/sh
# task9.sh

echo "Input the directory to find file"
read dName
#Checks if the directory exits
if [ -d $dName ]; then
    echo "Input name of readable file in directory"
    read fName
    counter=0
    #gives user three attempts for file name
    while [ $counter -lt 2 ]
    do  
            #checks if the file exsits in the directory
            if [ -e "$dName/$fName" ]; then
                #checks if the file is readable
                if [ -r "$dName/$fName" ]; then
                    echo "Search for a word"
                    read word
                    #checks if the word input is in the file
                    if [ `grep -c "$word" "$dName/$fName"` -gt 0 ]; then
                        echo "$word FOUND!"
                        exit 0
                    else
                        #exits if word is not found
                        echo "$word NOT FOUND"
                        exit 4
                    fi
                else
                    #exits if file is not readable
                    echo "File is not readable"
                    exit 3
                fi
            fi
            echo "Try again file not found"
            read fName
            counter=`expr $counter + 1`
    done
    #exits if file is not found
    echo "No such file"
    exit 2
else
    #exits if directory is not found
    echo "No such directory"
    exit 1
fi
exit 0