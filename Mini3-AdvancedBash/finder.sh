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

# list all files in dir 
files=`ls $DIRNAME | grep $EXTENSION`;

# test if DIRNAME is an empty dir
if [ -z "$files" ]
then
    echo "Unable to locate any files with extension $EXTENSION in $DIRNAME"
    exit
fi


# loops thru all files
for file in $files
do
    # for each filename check for the extension at the end
    if [ ! -z `echo $file | grep "$EXTENSION$"` ]
    then
        echo "$DIRNAME$file"
        if [ "$SHOW" = "true" ]
        then
            cat $file
        fi
    fi
done
