// Student name: Ding Yi Zhang
// 260923676
// Faculty of Science

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// length of the int array
const int len = 100;

void readfile(char *filename, int *array, int len) {
    /** reads the numbers inside filename to the provided array
     */
    FILE *f = fopen(filename, "rt");
    // if file opening isn't successeful, exit the program
    if (f == NULL)  exit(1);
    // ints in C cannot exceed +- 2.147e10, so it's safe to use only 16 chars per line
    char line[16];
    for (int i = 0; !feof(f) && i < len; i++) {
        fgets(line, 15, f);
        array[i] = atoi(line);
    }
    fclose(f);
}

void writeArrayToFile(int *array, int start, int stop, char *filename) {
    /** Writes parts of an int array to a file called filename
     * start is included in the slice, stop is NOT included in the slice
     * writes filename as environment variable to shell
     */
    // opens in write mode, always overwrites the content!
    FILE *output = fopen(filename, "wt");
    if (output == NULL)    exit(1);
    char buffer[16];
    for (int i = start; i < stop; i++) {
        // holds the string value of the int
        sprintf(buffer, "%d\n", array[i]);
        fputs(buffer, output);
    }
    fclose(output);
}

int readSum(char *sumFile) {
    /** reads and returns the sum computed by sum1 and sum2
     * waits first for the sumFile to exist before reading
     */
    FILE *f;
    do {
        f = fopen(sumFile, "rt");
    } while (f == NULL);
    // waits for some more for the sum file to be finished writing...
    for (int i = 0; i < 1000000; i++) {
        int j = i * i;
    }
    char line[16];
    fgets(line, 15, f);
    return atoi(line);
}

int main(int argc, char *argv[]) {
    char *filename = argv[1];
    int data[100];
    readfile(filename, data, len);
    writeArrayToFile(data, 0, 50, "values1.txt");
    writeArrayToFile(data, 50, 100, "values2.txt");
    int totalSum = 0;
    totalSum += readSum("sum1.txt");
    totalSum += readSum("sum2.txt");
    printf("The total sum is: %d\n", totalSum); 
    return 0;
}