#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Auhor: Ding Yi Zhang, Faculty of Science
 * Usage: caesarcipher <offset>
 * This program will scrambles the message you input by
 * the amount you indicated as a command line argument
 * Ex: offset = 3
 * defghijklmnopqrstuvwxyzabc -> abcdefghijklmnopqrstuvwxyz
 * offset can be negative, the scrambling will occur in resvere
 * Changelog:
 * feb 12: inital version, many bugs to be fixed
 * feb 16: temporary fix, still have to handle neg. offset 
 * feb 17: neg. offset handled!
 */


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
        // fgets will not alter input if it finds EOF in stdin
        // so if the first char is still null, then we know the user
        // has entered EOF, so we exit the program
        // strlen(input) == 1 when user only press RETURN
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
                    input[i] = input[i] + offset - 26;
                }
                else {
                    input[i] = input[i] + offset + 26;
                }
            }
        }
        printf("%s", input);
        // set the first char to null for later use
        input[0] = 0;
        
    }

    return 0;
}
