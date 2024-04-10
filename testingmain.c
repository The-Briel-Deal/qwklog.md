#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addlb(char *str) {
  // Allocate the length of the string passed in + 2 for linebreak and null byte
  str = (char *)realloc(str, strlen(str) + 3);
  // Create linebreak in memory
  char *lb = (char *)malloc(3);
  strcpy(lb, "\n");
  // Concatenate the linebreak onto the string
  strcat(str, lb);
  free(lb);
}

void addspace(char *str) {
  // Allocate the length of the string passed in + 2 for linebreak and null byte
  str = (char *)realloc(str, strlen(str) + 3);
  // Create linebreak in memory
  char *space = (char *)malloc(3);
  strcpy(space, " ");
  // Concatenate the linebreak onto the string
  strcat(str, space);
  free(space);
}

void addarg(char *linetowrite, char *nextarg) {
  // Allocate the length of the string passed in + 2 for linebreak and null byte
  linetowrite =
      (char *)realloc(linetowrite, strlen(linetowrite) + strlen(nextarg) + 1);
  // Concatenate the linebreak onto the string
  strcat(linetowrite, nextarg);
}

int main(int argc, char **argv) {
  // Create a pointer of type FILE to the textfile filemode.txt
  FILE *fptr;
  fptr = fopen("test_log.txt", "a");
  // Create Line that will be appended to and written at end
  char *linetowrite;
  linetowrite = (char *)malloc(7);
  // Iterate through all args
  for (int i = 0; i < argc; i++) {
    // Allocate Memory of length arg + 1 so that there is room for null byte
    char *argcopy = (char *)malloc(strlen(argv[i]) + 10);
    // Copy the sys arg to a copy as the sys arg can't be mutated without
    // undefined behavior
    strcpy(argcopy, argv[i]);
    printf("argis: %s\n", argcopy);
    // Append this arg onto linetowrite
    addarg(linetowrite, argcopy);
    free(argcopy);
    printf("line after addarg: %s\n", linetowrite);
    // Add space onto linetowrite
    addspace(linetowrite);
    printf("line at end of loop: %s\n", linetowrite);
  }
  // Add linebreak using function defined above
  addlb(linetowrite);
  // Write this arg to file
  printf("%s", linetowrite);
  fprintf(fptr, "%s", linetowrite);
  // Free the files pointer in memory
  fclose(fptr);
}
