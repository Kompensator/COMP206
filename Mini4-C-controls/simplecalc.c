#include <stdio.h>
#include <stdlib.h>

// main program
int main(int argc, char *argv[]) {
    // test if the user passed 3 argv
    if (argc != 4) {
        puts("Error: usage is simplecalc <x> <op> <y>");
        return 1;
    } 

    char operator = argv[2][0];
    int x, y, ans;
    x = atoi(argv[1]);
    y = atoi(argv[3]);
    // switching the operator for each + - * /
    switch (operator) {
        case '+':
            ans = x + y;
            break;
        case '-':
            ans = x - y;
            break;
        case '*':
            ans = x * y;
            break;
        case '/':
            ans = x / y;
            break;
        default:
            // print op is not recongnized and exit with 1
            printf("%c is not a valid operator\n", operator);
            return 2;
    }
    // prints the answer if the program hasn't exited yet
    printf("%d\n", ans);


    return 0;
}
