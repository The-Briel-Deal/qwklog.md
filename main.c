#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addlb(char *str) {
  str = (char *)realloc(str, strlen(str) + 2);
  char *lb = (char *)malloc(2);
  strcpy(lb, "\n");
  strcat(str, lb);
}

int main(int argc, char **argv) {
  for (int i = 0; i < argc; i++) {
    char *arg = argv[i];
    char *argcopy = (char *)malloc(strlen(arg) + 1);
    strcpy(argcopy, arg);
    addlb(argcopy);
    printf("%s", argcopy);
  }
}
