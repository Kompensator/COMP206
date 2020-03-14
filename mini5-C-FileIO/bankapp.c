
/** bankapp, a simple bank implementation
 * Create accounts, withdraw, deposit
 * To compile: $ gcc -o bankapp bankapp.c
 * Author: Ding Yi Zhang        Department: Faculty of Science
 * Changelog:
 * 03/01: created bankapp.c
 * 03/03: error handling done
 * 03/07: fileIO, create, deposit, withdraw done (used brute force)!
 * 03/08: used more pointer and less brutforcing!
 * 03/13: completed the comments, final testing
**/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// define the most common errors
#define ERRORMSG "Error, incorrect usage!\n"
#define ACCNTMSG "-a ACCTNUM NAME\n"
#define DEPOSMSG "-d ACCTNUM DATE AMOUNT\n"
#define WITHDMSG "-w ACCTNUM DATE AMOUNT\n"

const int N = 100;          // number of records the array stores
const int M = 100;          // number of chars each row has (should be enough)

void appendFile(char *, char *);

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
        // deposit option
        if (argc != 5 || strlen(argv[3]) != 10) {
            // insufficient args OR args in the wrong order
            fprintf(stderr, ERRORMSG);
            fprintf(stderr, DEPOSMSG);
            exit(1);
        }
    }
    else if (strcmp(argv[1], "-w") == 0) {
        // withdrawal option
        if (argc != 5 || strlen(argv[3]) != 10) {
            // insufficient args OR args in the wrong order
            fprintf(stderr, ERRORMSG);
            fprintf(stderr, WITHDMSG);
            exit(1);
        }
    }
}

void readFile(char *filename, char target[N][M]) {
    // reads the content of into the target 2D char array
    // each line in file will be row in the array
    FILE *f = fopen(filename, "rt");
    if (f == NULL) exit(1);
    for(int i = 0;!feof(f) && i<100;i++) {
        fgets(target[i], 99, f);
    }
    fclose(f);
}

int testAccountExist(char *number, char data[N][M]) {
    // test if a specific account number exists in the record
    char *p;
    int ID;
    for (int i = 0;i < N;i++) {
        // point p to the start of the account number in the csv data
        p = &data[i][3];
        ID = atoi(p);
        if (data[i][0] == 'A' && data[i][1] == 'C' && ID == atoi(number)) {
            return 1;
        }
    }
    return 0;
}

void addAccount(char *number, char *name, char data[N][M]) {
    // tries to add an account to the data
    // scans for existing acc number
    if (!testAccountExist(number, data)) {
        char line[100] = "";
        strcat(line, "AC,");
        strcat(line, number);
        strcat(line, ",");
        strcat(line, name);
        strcat(line, "\n");
        appendFile("bankdata.csv", line);
    }
    else {
        // print the error to stderr if acc exists already
        fprintf(stderr, "Error, account number %s already exists\n", number);
        exit(50);
    }
}


void deposit(char *number, char *date, char *amount, char data[N][M]) {
    // deposites the money into the account record, if account is created
    if (testAccountExist(number, data)) {
        char line[100] = "TX,";
        strcat(line, number);
        strcat(line, ",");
        strcat(line, date);
        strcat(line, ",");
        strcat(line, amount);
        strcat(line, "\n");
        appendFile("bankdata.csv", line);
    }
    else {
        // prints to stderr that account is not created
        fprintf(stderr, "Error, account number %s does not exists\n", number);
        exit(50);
    }
}

double balance(char *number, char data[N][M]) {
    // returns the balance that the account has, including multiple deposits and withdraws
    double sum = 0.0;
    char *p;
    int ID;
    for (int i = 0;i < N;i++) {
        // points p to the start of account number in the data
        p = &data[i][3];
        ID = atoi(p);
        if (data[i][0] == 'T' && atoi(number) == ID) {
            // points q to the current row and increment it by 19 will point it to the transfer amount
            // in the array
            char *q = data[i];
            q += 19;
            sum += atof(q);
        }
    }
    return sum;
}

void withdraw(char *number, char *date, char *amount, char data[N][M]) {
    // withdraws money if funds is available and account exist
    if (testAccountExist(number, data)) {
        double money = balance(number, data);
        if (money < atof(amount)) {
            // if not enough balance, print this to stderr
            fprintf(stderr, "Error, account number %s has only %.2f\n", number, money);
            exit(60);
        }
        else {
            char line[100] = "TX,";
            strcat(line, number);
            strcat(line, ",");
            strcat(line, date);
            strcat(line, ",-");
            strcat(line, amount);
            strcat(line, "\n");
            appendFile("bankdata.csv", line);
        }
    }
    else {
        // print to stderr if account does not exist
        fprintf(stderr, "Error, account number %s does not exists\n", number);
        exit(50);
    }
}

void appendFile(char *filename, char *content) {
    // opens the file and writes the content at the end of the file
    FILE *f = fopen(filename, "at");        // mode 'at' = append text
    fputs(content, f);
    fclose(f);
}

int main(int argc, char* argv[]) {
    argtest(argc, argv);
    if (system("test -f bankdata.csv") != 0) {
        // test comamnd will somehow return 256 if file not found
        fprintf(stderr, "Error, unable to locate the data file bankdata.csv\n");
        exit(100);
    }
    // if the argv is good and bankdata exists, create the data array and read to it
    char data[N][M];
    readFile("bankdata.csv", data);
    // comparing argv[1] with the options to call the right function
    if (strcmp(argv[1], "-a") == 0) addAccount(argv[2], argv[3], data);
    else if (strcmp(argv[1], "-d") == 0) deposit(argv[2], argv[3], argv[4], data);
    else if (strcmp(argv[1], "-w") == 0) withdraw(argv[2], argv[3], argv[4], data);
    return 0;
}
