/** common functions for sum1.c and sum2.c
 * 
 */
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

// deprecated function, sum1.c and sum2.c use writeArrayToFile()
// void writeSum(int sum, char *filename) {
//     /** Writes a sum to a given filename
//      */
//     FILE *f = fopen(filename, "wt");
//     if (f == NULL)  exit(1);
//     char buffer[16];
//     sprintf(buffer, "%d\n", sum);
//     fputs(buffer, f);
//     fclose(f);
// }

int readNumbers(char *filename, int *data, int len) {
    /** reads the ints from a file and store them into data
     * len is when reading stops
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
    for (int i = 0; !feof(f) && i < len; i++) {
        fgets(line, 15, f);
        data[i] = atoi(line);
    }
    fclose(f);
    int unmodifiedCount = 0;
    // check how many items in data are actually modified
    for (int i = 0; i < 50; i++) {
        // previously we set data[i] to i arbitrarily
        if (data[i] == i) unmodifiedCount++;
    }
    // if more than 5 numbers remain unmodified, the read has failed and we redo the read
    if (unmodifiedCount > 5) return 1;
    else return 0;
}

void writeArrayToFile(int *array, int start, int stop, char *filename) {
    /** Writes parts of an int array to a file called filename
     * start is included in the slice, stop is NOT included in the slice
     * sum1.c sum2.c also use this function to write their sum to file
     */
    // opens in write mode, always overwrites the content!
    FILE *output = fopen(filename, "wt");
    if (output == NULL) exit(1);
    char buffer[16];
    for (int i = start; i < stop; i++) {
        // holds the string value of the int
        sprintf(buffer, "%d\n", array[i]);
        fputs(buffer, output);
    }
    fclose(output);
}