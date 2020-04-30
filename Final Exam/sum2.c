// Student name: Ding Yi Zhang
// 260923676
// Faculty of Science

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "common.h"

int main() {
    int len = 50;
    int data[len];
    for (int i = 0; i < len; i++) {
        // sets arbitrary initial values
        data[i] = i;
    }
    while(readNumbers("values2.txt", data, 50)) ;
    int sum = arraySum(data, len);
    writeSum(sum, "sum2.txt");
    return 0;
}