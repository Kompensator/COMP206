#include <stdio.h>
#include <stdlib.h>
char *getInfo() {
   char buffer[1000] = "12345";
   // char buffer[1000];
   // scanf("%s", buffer);
   return buffer;
}
int main() {
   char *ptr;
   ptr = getInfo();
   for (int i = 0; i < 5; i++) putc(*(ptr+i), stdout);
   // printf("%s\n", ptr); // <--- error
   return 0;
}