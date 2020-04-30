// Student name: Ding Yi Zhang
// 260923676
// Faculty of Science

#include <string.h>

int main(int argc, char *argv[]) {
    char *word = *(argv + 1);      // equals to word = argv[1]
    int len = (int)strlen(word);
    // empty string!
    if (len == 0)   return 1;
    // stop is used to stop comparing when we finished comparing the first half with the last half
    int stop = len/2;
    // if the length is odd, stop will be 'rounded down' due to integer division
    // in this case we increment stop so the loop will scan through all chars
    if (len % 2 == 1)   stop ++;
    char c1, c2;
    for (int i = 0; i < stop; i++) {
        // the last char is at index [len-1] and not [len], so we subtract 1
        c1 = *(word + i);                  // equivalent tot word[i]
        c2 = *(word + len - i - 1);        // eqiuvalent to word[len-i-1]
        if (c1 != c2)   return 1; 
    }
    return 0;
}