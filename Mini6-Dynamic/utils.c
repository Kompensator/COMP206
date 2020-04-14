/** utils.c: helpers for polyapp.c
Author: Ding Yi Zhang
Faculty: Science
To compile:
Changelog:
- April 8 15h30: file created
- April 8 16h05: parse() and powi() are working!
*/

#include <stdlib.h>
#include <string.h>

void parse(char *input, int *coeff, int *expo);
int powi(int base, int expo);

void parse(char *input, int *coeff, int *expo) {
    /** reads input into coeff and expo, separated by a space
    */
    // atoi will convert  the first number in the row until the space
    *coeff = atoi(input);
    for (int i = 0;i < strlen(input);i++) {
        // shift the input pointer when we find the space char
        if (input[i] == ' ') input += i;
    }
    *expo = atoi(input);
}

int powi(int base, int expo) {
    /** returns base ** expo
     */
    // assuming base is >= 0
    if (expo == 0) return 1;
    int ans = 1;
    for (int i = 0;i < expo;i++) {
        ans *= base;
    }
    return ans;
}