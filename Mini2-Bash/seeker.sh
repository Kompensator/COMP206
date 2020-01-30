# ID: 260923676
# Name: Ding Yi Zhang

#!/bin/bash

#setting default values for the user options
# 0 is default
c=0
a=0
pattern=0
dir=`pwd`

# if no argument provided
if [ $# -eq 0 ]
then
    echo "Error missing the pattern argument."
    echo "Usage ./seeker.sh [-c] [-a] pattern [path]"
    exit
fi


# if 1 argument provided
if [ $# -eq 1 ]
then
    # $1 cannot be -c or -a, else it's an error
    if [ $1 != "-c" ] && [ $1 != "-a" ]
    then
        pattern=$1
    else
        echo "Error missing the pattern argument."
        echo "Usage ./seeker.sh [-c] [-a] pattern [path]"
        exit
    fi
fi


# 2 arguments provided
if [ $# -eq 2 ]
then
    # $2 must not be -a or -c, else it throws error
    if [ $2 != "-a" ] && [ $2 != "-c" ]
    then

        if [ $1 = "-c" ]
        then
            c=1
            pattern=$2
        elif [ $1 = "-a" ]
        then
            a=1
            pattern=$2
        # if $1 isn't -c or -a, then it must pattern
        else
            pattern=$1
            # $2 contains dir
            dir=$2
        fi
    else
        echo "Error missing the pattern argument."
        echo "Usage ./seeker.sh [-c] [-a] pattern [path]"
        exit
    fi
fi


# 3 arguments provided
if [ $# -eq 3 ]
then

    if [ $1 = "-c" ]
    then
        c=1
        if [ $2 = "-a" ]
        then
            a=1
            pattern=$3
        # if $2 isn't -a, $2 contains pattern
        else
            pattern=$2
            dir=$3
        fi
    fi

    # handling the case of ./seeker.sh -a -c pattern
    if [ $1 = "-a" ]
    then
        a=1
        if [ $2 = "-c" ]
        then
            c=1
            pattern=$3
        else
            pattern=$2
            dir=$3
        fi
    fi
fi


# 4 arguments, we can assume user wants -c -a and provides a dir
if [ $# -eq 4 ]
then
    c=1
    a=1
    pattern=$3
    dir=$4
fi


#testing if dir provided exists
if [ ! -d $dir ]
then
    echo Error $dir is not a valid directory
    exit
fi


#try to find the file
files=`ls $dir | grep "$pattern"`
# if $files is empty, then no match found
if [ -z "$files" ]
then
    echo Unable to locate any files that has the pattern $pattern in its name in $dir
fi

for file in $files
do
# if user use switch -c
    if [ $c = 1 ]
    then
        echo "==== Contents of: $dir/$file ===="
        cat $dir/$file
        # if user did not use -c
    else
        echo "$dir/$file"
    fi

        # is user did not use switch -a, break after first file
    if [ ! $a = 1 ]
    then
        break
    fi
done
