#!/bin/bash

# loading variables from a3config
if [ -f a3config ]
then
    source a3config
else
    echo "Error cannot find a3config"
    exit 1

fi 

# test if DIRNAME and EXTENSION are set
if [ -z $DIRNAME ] || [ -z $EXTENSION ]
then
    echo "Error DIRNAME and EXTENSION must be set"
    exit 2
fi

# test if DIRNAME actually exists
if [ ! -d $DIRNAME ]
then
    echo "Error directory $DIRNAME does not exist"
    exit 3
fi

# search for files in dir with grep
files=`ls $DIRNAME | grep $EXTENSION`

# test if DIRNAME is an empty dir
if [ -z "$files" ]
then
    echo "Unable to locate any files with extension $EXTENSION in $DIRNAME"
    exit
fi


# displays all the files using a for loop
for file in $files
do
    echo "$DIRNAME/$file"
    if [ "$SHOW" = "true" ]
    then
        cat $file
    fi
done
