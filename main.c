#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addlb(char *str) {
  // Allocate the length of the string passed in + 2 for linebreak and null byte
  str = (char *)realloc(str, strlen(str) + 2);
  // Create linebreak in memory
  char *lb = (char *)malloc(2);
  strcpy(lb, "\n");
  // Concatenate the linebreak onto the string
  strcat(str, lb);
}

int main(int argc, char **argv) {
  // Create a pointer of type FILE to the textfile filemode.txt
  FILE *fptr;
  fptr = fopen("test_log.txt", "w");
  // Iterate through all args
  for (int i = 0; i < argc; i++) {
    // Allocate Memory of length arg + 1 so that there is room for null byte 
    char *argcopy = (char *)malloc(strlen(argv[i]) + 1);
    // Copy the sys arg to a copy as the sys arg can't be mutated without undefined behavior
    strcpy(argcopy, argv[i]);
    // Add linebreak using function defined above
    addlb(argcopy);
    // Write this arg to file.
    fprintf(fptr, "%s", argcopy);
  }
  // Free the files pointer in memory
  fclose(fptr);
}
