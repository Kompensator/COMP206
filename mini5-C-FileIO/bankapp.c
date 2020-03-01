/** bankapp, a simple bank implementation
 * Create accounts, withdraw, deposit
 * To compile: $ gcc -o bankapp bankapp.c
 * Author: Ding Yi Zhang        Department: Faculty of Science
 * Changelog:
 * 03/01: created bankapp.c
 * 03/03: error handling done
**/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ERRORMSG "Error, incorrect usage!\n"
#define ACCNTMSG "-a ACCTNUM NAME\n"
#define DEPOSMSG "-d ACCTNUM DATE AMOUNT\n"
#define WITHDMSG "-w ACCTNUM DATE AMOUNT\n"


void argtest(int argc, char* argv[]) {
    // checks if the args passed into main() are valid
    // displays the appropriate error msg if not valid
    if (argc == 1) {
        // if no extra args are passed
        fprintf(stderr, ERRORMSG);
        fprintf(stderr, ACCNTMSG);
        fprintf(stderr, DEPOSMSG);
        fprintf(stderr, WITHDMSG);
        exit(1);
    }
    else if (strcmp(argv[1], "-a") == 0) {
        if (argc != 4) {
            // insufficient args for account creation
            fprintf(stderr, ERRORMSG);
            fprintf(stderr, ACCNTMSG);
            exit(1);
        }
    }
    else if (strcmp(argv[1], "-d") == 0) {
        if (argc != 5 || strlen(argv[3]) != 10) {
            // insufficient args OR args in the wrong order
            fprintf(stderr, ERRORMSG);
            fprintf(stderr, DEPOSMSG);
            exit(1);
        }
    }
    else if (strcmp(argv[1], "-w") == 0) {
        if (argc != 5 || strlen(argv[3]) != 10) {
            // insufficient args OR args in the wrong order
            fprintf(stderr, ERRORMSG);
            fprintf(stderr, WITHDMSG);
            exit(1);
        }
    }
}

int main(int argc, char* argv[]) {
    argtest(argc, argv);
    if (system("test -f bankdata.csv") == 256) {
        // test comamnd will somehow return 256 if file not found
        fprintf(stderr, "Error, unable to locate the data file bankdata.csv\n");
        exit(100);
    }
    char* datafile = "bankdata.csv";
    
    return 0;
}