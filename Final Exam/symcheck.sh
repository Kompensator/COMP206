# Student name: Ding Yi Zhang
# 260923676
# Faculty of Science

#!/bin/bash

file=$1

# testing for whether $file is non zero (input not provvided!)
if [ -z $file ]
then
    echo "Input file is not provided!"
fi

# testing for whether $file exists
if ! [ -f $file ]
then
    echo "Input file does not exist!"
fi

# if we have not compiled the symword yet, compile it
if ! [ -f symword ] 
then
    gcc symword.c -o symword -O2
fi

# MAIN LOOP, redirect output of cat to read command
# need to make sure we don't give symword an empty line
cat $file | while read line || ! [ -z $line ]
do
    ./symword $line
    if [ $? -eq 0 ]
    then
        echo $line is symmetric
    else
        echo $line is not symmetric
    fi
done