# Student name: Ding Yi Zhang
# 260923676
# Faculty of Science

#!/bin/bash

div () {
    # recursive function to find the GCD of X and Y
    # get rid of this special case (X = Y)
    if [ $1 -eq $2 ]
    then
        N=$1
        echo Largest divisor of $1 and $2 is $N
    else
    # X < Y, set N initially to the value of X
        if [ $1 -lt $2 ]
        then
            N=$1
        # X > Y set N to Y initially
        else
            N=$2
        fi
        # if N cannot fully divide both X and Y, decrement N until it can
        while [ $(($1 % $N)) -ne 0 ] || [ $(($2 % $N)) -ne 0 ]
        do
            N=$(($N - 1))
        done
        echo Largest divisor of $1 and $2 is $N
    fi
}

# running will stop the main loop if user dones't input 'y'
running=y

# mainloop
while [ $running == y ]
do
    echo 'Enter first number:'
    read X
    echo 'Enter second number:'
    read Y
    # calls div to compute and print GCD
    div $X $Y
    echo 'Do you want to continue?'
    # if user inputs anything else but 'y', the while loop will stop
    read running
done