#include <stdio.h>
#include <stdlib.h>

void myIncrement(int *);

int main() {
	int x = 1;
	printf("\nx = %i\n", x);
	myIncrement(&x);
	printf("x = %i\n", x);

	return 0;
}

void myIncrement(int * pInput) 
{
	int input_before_increment = ((*pInput)++); 
	printf("input_before_increment = %i\n");
}

