#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char filename[] = "test_table.md";

char* addlb(char *str) {
  char *lb = "\n";
  // Allocate the length of the string passed in + 2 for linebreak and null byte
  str = (char *)realloc(str, strlen(str) + strlen(lb) + 1);
  // Concatenate the linebreak onto the string
  strcat(str, lb);
  return str;
}

char* addspace(char *str) {
  char *space = " ";
  // Allocate the length of the string passed in + 2 for linebreak and null byte
  str = (char *)realloc(str, strlen(str) + strlen(space) + 1);
  // Concatenate the linebreak onto the string
  strcat(str, space);
  return str;
}

char* addarg(char *linetowrite, char *nextarg) {
  // Allocate the length of the string passed in + 2 for linebreak and null byte
  linetowrite =
      (char *)realloc(linetowrite, strlen(linetowrite) + strlen(nextarg) + 1);
  // Concatenate the linebreak onto the string
  strcat(linetowrite, nextarg);
  // Return linetowrite as realloc gave me a pointer that is potentially different. 
  return linetowrite;
}

int writeargstofile(int argc, char **argv) {
  // Create a pointer of type FILE to the textfile filemode.txt
  FILE *fptr;
  fptr = fopen(filename, "a");
  // If file doesn't exist (pointer is null) return
  if (fptr == NULL) {
    return 1;
  }
  // Create Line that will be appended to and written at end
  char *linetowrite = (char *)malloc(1);
  strcpy(linetowrite, "");
  // Iterate through all args
  for (int i = 0; i < argc; i++) {
    // Allocate Memory of length arg + 1 so that there is room for null byte
    char *argcopy = (char *)malloc(strlen(argv[i]) + 1);
    // Copy the sys arg to a copy as the sys arg can't be mutated without
    // undefined behavior
    strcpy(argcopy, argv[i]);
    // Append this arg onto linetowrite
    linetowrite = addarg(linetowrite, argcopy);
    // Add space onto linetowrite
    linetowrite = addspace(linetowrite);
  }
  // Add linebreak using function defined above
  linetowrite = addlb(linetowrite);
  // Write this arg to file
  fprintf(fptr, "%s", linetowrite);
  // Free the files pointer in memory
  fclose(fptr);
  return 0;
}

int main(int argc, char **argv) {
    writeargstofile(argc, argv);
    return 0;
   // Get Bounding Lines For CSV Table From File. 
}
