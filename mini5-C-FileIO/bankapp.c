
/** bankapp, a simple bank implementation
 * Create accounts, withdraw, deposit
 * To compile: $ gcc -o bankapp bankapp.c
 * Author: Ding Yi Zhang        Department: Faculty of Science
 * Changelog:
 * 03/01: created bankapp.c
 * 03/03: error handling done
 * 03/07: fileIO, create, deposit, withdraw done (used brute force)!
**/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ERRORMSG "Error, incorrect usage!\n"
#define ACCNTMSG "-a ACCTNUM NAME\n"
#define DEPOSMSG "-d ACCTNUM DATE AMOUNT\n"
#define WITHDMSG "-w ACCTNUM DATE AMOUNT\n"

const int N = 100;
const int M = 100;

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

void readFile(char *filename, char target[N][M]) {
    // reads the content of f into the target pointer
    FILE *f = fopen(filename, "rt");
    if (f == NULL) exit(1);
    // data allows 100 lines of records to be stored
    for(int i = 0;!feof(f) && i<100;i++) {
        fgets(target[i], 999, f);
    }
    fclose(f);
}

int findEmptyRow(char data[N][M]) {
    // finds the first empty "row" in data and returns the index
    // returns -1 if all full
    for (int i = 0;i < N;i++) {
        if (!((data[i][0] == 'A' && data[i][1] == 'C') ||
        (data[i][0] == 'T' && data[i][1] == 'X'))) {
            return i;
        }
    }
    return -1;
}

int testAccountExist(char *number, char data[N][M], int exitIfFound) {
    // test if a specific account number exists in the record
    char ID[4];
    for (int i = 0;i < N;i++) {
        ID[0] = data[i][3];
        ID[1] = data[i][4];
        ID[2] = data[i][5];
        ID[3] = data[i][6];
        if (data[i][0] == 'A' && data[i][1] == 'C' && strstr(ID, number)) {
            if (exitIfFound) {
                fprintf(stderr, "Error, account number %s already exists\n", number);
                exit(50);
            }
            else return 1;
        }
    }
    return 0;
}

void addAccount(char *number, char *name, char data[N][M]) {
    // tries to add an account to the data
    // scans for existing acc number
    int num = findEmptyRow(data);
    if (!testAccountExist(number, data, 1)) {
        char line[100] = "";
        strcat(line, "AC,");
        strcat(line, number);
        strcat(line, ",");
        strcat(line, name);
        strcat(line, "\n");
        // strcpy(data[num], line);
        appendFile("bankdata.csv", line);
    }
}


void deposit(char *number, char *date, char *amount, char data[N][M]) {
    // deposites the money into the account record
    if (testAccountExist(number, data, 0)) {
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
        fprintf(stderr, "Error, account number %s does not exists\n", number);
        exit(50);
    }
}

double balance(char *number, char data[N][M]) {
    // returns the balance that the account has including multiple deposits and withdraws
    double sum = 0.0;
    for (int i = 0;i < N;i++) {
        char ID[4];
        ID[0] = data[i][3];
        ID[1] = data[i][4];
        ID[2] = data[i][5];
        ID[3] = data[i][6];
        if (data[i][0] == 'T' && ID[0] == number[0] && ID[1] == number[1] && ID[2] == number[2] && ID[3] == number[3]) {
            char *money = strrchr(data[i], ',');
            // to bump off the ',' in the beginning of money so atof can work
            money++;
            sum += atof(money);
        }
    }
    return sum;
}

void withdraw(char *number, char *date, char *amount, char data[N][M]) {
    // withdraws money if funds is available
    if (testAccountExist(number, data, 0)) {
        double money = balance(number, data);
        if (money < atof(amount)) {
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
        fprintf(stderr, "Error, account number %s does not exists\n", number);
        exit(50);
    }
}

void appendFile(char *filename, char *content) {
    FILE *f = fopen(filename, "at");
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
    char data[N][M];
    readFile("bankdata.csv", data);
    if (strcmp(argv[1], "-a") == 0) addAccount(argv[2], argv[3], data);
    else if (strcmp(argv[1], "-d") == 0) deposit(argv[2], argv[3], argv[4], data);
    else  withdraw(argv[2], argv[3], argv[4], data);
    // for (int i = 0;i < 6;i++) {
    //     puts(data[i]);
    // }
    // writeFile("bankdata.csv", data);
    
    return 0;
}
