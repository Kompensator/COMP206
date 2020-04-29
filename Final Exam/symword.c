// Student name: Ding Yi Zhang
// 260923676
// Faculty of Science

#include <string.h>

int main(int argc, char *argv[]) {
    char *word = argv[1];
    int len = (int)strlen(word);
    // stop is used to stop comparing when we finished comparing the first half with the last half
    int stop = len/2;
    // if the length is odd, stop will be 'rounded down' due to integer division
    // in this case we increment stop so the loop will scan through all chars
    if (len % 2 == 1)   stop ++;
    for (int i = 0; i < stop; i++) {
        // the last char is at index [len-1] and not [len], so we subtract 1
        if (word[i] != word[len-i-1])   return 1; 
    }
    return 0;
}