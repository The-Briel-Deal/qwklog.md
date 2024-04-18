#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *filename;

typedef struct LineBounds {
  int start_line;
  int end_line;
} LineBound;

typedef struct DividedFile {
  char *beginning;
  int beginningMemoryAllocated;
  char *table;
  int tableMemoryAllocated;
  char *end;
  int endMemoryAllocated;
} DividedFile;

char *addlb(char *str) {
  char *lb = "\n";
  // Allocate the length of the string passed in + 2 for linebreak and null byte
  str = (char *)realloc(str, strlen(str) + strlen(lb) + 1);
  // Concatenate the linebreak onto the string
  strcat(str, lb);
  return str;
}

char *addseperator(char *str) {
  char *space = " | ";
  // Allocate the length of the string passed in + 2 for linebreak and null byte
  str = (char *)realloc(str, strlen(str) + strlen(space) + 1);
  // Concatenate the linebreak onto the string
  strcat(str, space);
  return str;
}

char *addarg(char *linetowrite, char *nextarg) {
  // Allocate the length of the string passed in + 2 for linebreak and null byte
  linetowrite =
      (char *)realloc(linetowrite, strlen(linetowrite) + strlen(nextarg) + 1);
  // Concatenate the linebreak onto the string
  strcat(linetowrite, nextarg);
  // Return linetowrite as realloc gave me a pointer that is potentially
  // different.
  return linetowrite;
}

char *concatargstotable(int argc, char **argv) {
  // Create a pointer of type FILE to the textfile filemode.txt
  FILE *fptr;
  fptr = fopen(filename, "a");
  // Create Line that will be appended to and written at end
  char *linetowrite = (char *)malloc(4);
  strcpy(linetowrite, "\n| ");
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
    linetowrite = addseperator(linetowrite);
  }
  // Add linebreak using function defined above
  // linetowrite = addlb(linetowrite);
  return linetowrite;
}

LineBound getfirsttablebounds(const char *pfilename) {
  // Create pointer to file and read it.
  FILE *fptr = fopen(pfilename, "r");
  // Declare variable for bounds and set start and end line to -1 so we know
  // they weren't set.
  LineBound bounds;
  bounds.start_line = -1;
  bounds.end_line = -1;
  // Declare a single int that will hold all of the characters as we iterate
  // through them.
  int c;
  // Declare a integer that tracks the current line we are on as we iterate.
  int currline = 0;
  // Creating backup file here in case something breaks.
  char *backupfilename = malloc(256); // The max length of a filename.
  strcpy(backupfilename, ".old-");
  strcat(backupfilename, pfilename);
  FILE *fbackupptr = fopen(backupfilename, "w");
  //free(backupfilename);

  printf("We are ok here!");
  // Iterate through until we hit the end of file and run checks of each
  // character.
  while ((c = fgetc(fptr)) != EOF) {
    fputc(c, fbackupptr);
    // If we hit a new line increment the current line.
    if (c == '\n') {
      currline += 1;
    }
    // If we hit a pipe we know this we where a table stops.
    if ((c == '|') && (bounds.start_line == -1)) {
      bounds.start_line = currline;
    }
    // Every time we hit a pipe that line will be the new end point.
    if (c == '|') {
      bounds.end_line = currline;
    }
  }
  // Return the Bounds we got from the previous iteration.
  //fclose(fptr);
  //fclose(fbackupptr);
  return bounds;
}

DividedFile checkforlowsize(DividedFile dividedfile) {

  // If Memory Allocated - Used Space is less than 64, add another 128 bytes.
  if ((dividedfile.beginningMemoryAllocated - strlen(dividedfile.beginning)) <
      64) {
    dividedfile.beginningMemoryAllocated += 128;
    dividedfile.beginning =
        realloc(dividedfile.beginning, dividedfile.beginningMemoryAllocated);
  }

  // If Memory Allocated - Used Space is less than 64, add another 128 bytes.
  if ((dividedfile.tableMemoryAllocated - strlen(dividedfile.table)) < 64) {
    dividedfile.tableMemoryAllocated += 128;
    dividedfile.table =
        realloc(dividedfile.table, dividedfile.tableMemoryAllocated);
  }

  // If Memory Allocated - Used Space is less than 64, add another 128 bytes.
  if ((dividedfile.endMemoryAllocated - strlen(dividedfile.end)) < 64) {
    dividedfile.endMemoryAllocated += 128;
    dividedfile.end = realloc(dividedfile.end, dividedfile.endMemoryAllocated);
  }

  return dividedfile;
}

DividedFile dividefile(const char *pfilename, const LineBound bounds) {
  // Declare struct instance for divided file.
  DividedFile dividedfile;

  // Give all parts of divided file a starting buffer size of 128.
  dividedfile.beginning = malloc(128);
  dividedfile.beginningMemoryAllocated = 128;
  dividedfile.table = malloc(128);
  dividedfile.tableMemoryAllocated = 128;
  dividedfile.end = malloc(128);
  dividedfile.endMemoryAllocated = 128;

  // Declare ptr to the file buffer we are reading.
  FILE *fptr = fopen(pfilename, "r");
  int c;
  int currline = 0;
  // Iterate through every character and move to the next part of the
  // dividedfile.
  while ((c = fgetc(fptr)) != EOF) {
    if (c == '\n') {
      currline += 1;
    }

    dividedfile = checkforlowsize(dividedfile);
    if (currline < bounds.start_line) {
      char cc = (char)c;
      strncat(dividedfile.beginning, &cc, 1);
    } else if (currline <= bounds.end_line) {
      char cc = (char)c;
      strncat(dividedfile.table, &cc, 1);
    } else {
      char cc = (char)c;
      strncat(dividedfile.end, &cc, 1);
    }
  }

  return dividedfile;
}

char *getrowtoadd(int argc, char **argv) {
  int argstart = 2;
  // Get the new count of args to put together as a markdown row.
  int newargscount = argc - argstart;

  // Get the new args we will use for the markdown row.
  char **newargs = malloc(128);
  int i;
  for (i = 0; i < argc - argstart; i++) {
    newargs[i] = malloc(128);
    strcpy(newargs[i], argv[i + argstart]);
  }
  char *rowtoadd = concatargstotable(newargscount, newargs);
  return rowtoadd;
}

DividedFile addargstotable(int argc, char **argv, DividedFile dividedfile) {
  char *rowtoadd = getrowtoadd(argc, argv);
  strcat(dividedfile.table, rowtoadd);
  return dividedfile;
}

int main(int argc, char **argv) {
  // Pull filename out of args. Filename is the first argument.
  filename = argv[1];

  printf("Testing da makefile");
  // Get Bounding Lines For CSV Table From File.
  LineBound bounds = getfirsttablebounds(filename);

  // Split the file up into 3 different strings.
  DividedFile dividedfile = dividefile(filename, bounds);

  // Take the middle string (table) and append the record you
  // specify.
  dividedfile = addargstotable(argc, argv, dividedfile);
  // TODO: Write this out to same text file and rename/copy the old one.
  FILE *fptr;
  fptr = fopen(filename, "w");
  char *recombinedtextfile = malloc(1);
  strcpy(recombinedtextfile, "");
  recombinedtextfile = addarg(recombinedtextfile, dividedfile.beginning);
  recombinedtextfile = addarg(recombinedtextfile, dividedfile.table);
  recombinedtextfile = addarg(recombinedtextfile, dividedfile.end);
  printf("Testing da makefile");
  // TODO: (Bug) If I run the command without a path I get a segfault.
  fprintf(fptr, "%s", recombinedtextfile);
  // Return 0 if I made it to the end successfully.
  return 0;
}
