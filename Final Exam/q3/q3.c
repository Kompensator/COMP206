#include <stdio.h>
#include <stdlib.h>
char *getInfo() {
   char buffer[1000];
   scanf("%s", buffer);
   return buffer;
}
int main() {
   char *ptr;
   ptr = getInfo();
   printf("%s\n", ptr); // <--- error
   return 0;
}