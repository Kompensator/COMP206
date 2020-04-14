/** polyapp.c: application file for polynomial expressions
Author: Ding Yi Zhang
Faculty: Science
To compile:
Changelog:
- April 8 14h30: initializing polyapp.c
- April 12 14h30: called other functions, basically done
- April 12 14h50: everything works but minitester6 doesnt work..
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "poly.h"
#include "utils.h"

// global variable for the head
struct PolyTerm *head;

int main(int argc, char **argv) {
    if (argc == 1) {
        fprintf(stderr, "Error, missing data file!\n");
        exit(10);
    }
    FILE *f = fopen(argv[1], "rt");
    int coeff, expo, returnVal;
    while (!feof(f)) {
        // fgets will rewrite this array IF ONLY the file isn't empty
        char line[100] = "0 -10";
        fgets(line, 99, f);
        parse(line, &coeff, &expo);
        // expo cannot normally take -10, so in case it does, the file reaches its end
        if (expo == -10) break;
        returnVal = addPolyTerm(coeff, expo);
        if (returnVal == -1) {
            printf("Error, out of memory!\n");
            exit(-1);
        }
    }
    fclose(f);
    displayPolynomial();
    int values[] = {-2, -1, 0, 1, 2};
    int x, y;
    for (int i = 0; i < 5; i++) {
        x = values[i];
        y = evaluatePolynomial(x);
        printf("for x=%d, y=%d\n", x, y);
    }
    return 0;
}