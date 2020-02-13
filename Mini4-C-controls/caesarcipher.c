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
    long len;
    int index;

    // keep scrambing msgs until EOF breaks the loop
    while(1) {
        gets(input);        //TOFIX: it reads its own output
        //TOFIX:
        if (strlen(input) == 0) {
            break;
        }
        for (unsigned i = 0;i < strlen(input);i++) {
            if (input[i] >= 97 && input[i] <= 122) {
                // normalize the char so 'a' = 0
                index = input[i] - 97;
                if ((index + offset) < 26) {
                    // normal case: no re
                    input[i] += offset;
                }
                else {
                    input[i] = input[i] + offset - 26;
                }
            }
        }
        printf("%s\n", input);
    }

    return 0;
}
