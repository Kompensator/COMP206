# Student Name: Ding Yi Zhang
# ID: 260923676

#!/bin/bash

#check if both command line arguments are passed
# if not, tell user the proper usage
if [ -z "$1" ] || [ -z "$2" ]
then
    echo "Usage ./tarzan.sh filename tarfile"
    exit
fi

# test to see if tarfile exists
if [ ! -f $2 ]
then
    echo "Error cannot find tar file $2"
    exit
fi

#use grep and tar -tf to find the query
file=`tar -tf $2 | grep $1`

#check if $file is empty
# if empty, then file isn't found
if [ -z "$file" ]
then
    echo "$1 does not exist in $2"
else
    echo "$1 exists in $2"
fi

