/*
* Caesar Cipher program for basic encryption
* Usage: ./caesarcipher <offset>
* to compile: $ gcc -o caesarcipher caesarcipher.c
* <offset> can be positive or negative, anything in the range of int
* When ran, enter a message to encrypt, and lower case alphabet letters will be 
* shifted by <offset>
* Ex: offset = 2 
* Hello wor1d -> Hgnnq yqt1f
*************************************************************** 
* Author            Dept.           Date        Notes 
***************************************************************
* Ding Yi Zhang     Fac. Science    Feb 16      Initial commmit, user input working, EOF -> infinite loop
* Ding Yi Zhang     Fac. Science    Feb 17      Scrambling working mostly
* Ding Yi Zhang     Fac. Science    Feb 18      Scramping works! But EOF exit is not working
* Ding Yi Zhang     Fac. Science    Feb 21      EOF detection + added comments
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main(int argc, char * argv[]) {
    // test if the offset arg is passed
    if (argc == 1) {
        printf("Error: usage is caesarcipher <offset>\n");
        return 1;
    }

    int offset = atoi(argv[1]);
    // handle the case where abs(offset) > 26
    if (abs(offset) > 26) {
        offset = offset % 26;
    }

    // hopefully 1000 is enough to avoid using malloc
    char input[1000];
    int index;

    // keep scrambing msgs until EOF breaks the loop
    while(1) {
        fgets(input, 999, stdin);
        // fgets will not alter 'input' if it finds nothing but EOF in stdin
        // so if the first char is still null, then it read EOF -> exit 0
        // strlen(input) == 1 when user only press RETURN -> exit 0
        if (strlen(input) == 1 || input[0] == 0) {
            return 0;
        }

        for (unsigned int i = 0;i < strlen(input);i++) {
            if (input[i] >= 97 && input[i] <= 122) {
                // normalize the char so 'a' = 0
                index = input[i] - 97;
                if ((index + offset) < 26 && (index + offset) >= 0) {
                    // normal case: no rewinding the letters
                    input[i] += offset;
                }
                else if (offset >= 0) {
                    // alphabet underflow, back rewind
                    input[i] = input[i] + offset - 26;
                }
                else {
                    // alphabet overflow, forward rewind
                    input[i] = input[i] + offset + 26;
                }
            }
        }
        printf("%s", input);
        // set the first char to null for EOF detection
        input[0] = 0;
    }

    return 0;
}
