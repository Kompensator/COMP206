#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int arraySum(int *array, int len) {
    /** Sums the int array from 0 to len
     */
    int sum = 0;
    for (int i = 0; i < len; i++) {
        sum += array[i];
    }
    return sum;
}

void writeSum(int sum, char *filename) {
    /** Writes a sum to a given filename
     */
    FILE *f = fopen(filename, "wt");
    if (f == NULL)  exit(1);
    char buffer[16];
    sprintf(buffer, "%d\n", sum);
    fputs(buffer, f);
    fclose(f);
}

int readNumbers(char *filename, int *data) {
    /** reads the ints from a file and store them into data
     * returns 0 if most of the entries in data are modified (correct read)
     * returns 1 if most of the entries are NOT modified (value1.txt has not been written yet)
     */
    FILE *f;
    // waits for value1.txt to be created
    do {
        f = fopen(filename, "rt");
    }
    while (f == NULL);
    // uses similar logic to readfile in main.c
    char line[16];
    for (int i=0; !feof(f) && i < 50; i++) {
        fgets(line, 15, f);
        data[i] = atoi(line);
    }
    fclose(f);
    int unmodifiedCount = 0;
    for (int i = 0; i < 50; i++) {
        if (data[i] == i) unmodifiedCount++;
    }
    if (unmodifiedCount > 5) return 1;
    else return 0;
}