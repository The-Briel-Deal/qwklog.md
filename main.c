#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char **argv)
{
	char *str[1];
	sprintf(str, "%f", argc);
	printf(str);    
	for (int i; i<argc; i++) {
		char *arg = argv[i];
		printf(arg);
	}
}
