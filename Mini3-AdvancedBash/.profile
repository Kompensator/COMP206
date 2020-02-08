# .bashrc

# Source global definitions
if [ -f /usr/socs/Profile ]; then
        . /usr/socs/Profile
fi

# User specific aliases and function

# printing the greeing message
echo "Welcome to $HOSTNAME!"

# store the username to later use in grep
myID=`whoami`

# use who and grep to get how many lines of login names I have
# and wc to count the lines (sessions)
number=`who | grep $myID | wc -l`
echo "You have $number login sessions to this host."

# set comp206 to a cd command
alias comp206='cd ~/Projects/COMP206'

# set prompt to the desired format:
# username@server[time]:dir $ 
export PS1="\u@\h[\t]:\w$ "

# print a random quote
fortune

# git pull all my repos on the server
for repo in ~/java ~/COMP206
do
    cd $repo
    echo "git pulling $repo repo..."
    git pull
done
cd ~
