#include <stdio.h>
#include <stdlib.h>

void myIncrement(int *);

int main() {
//	int lucky = 23;

//	printf("Value: %i \n", lucky);
//	printf("Address: %p \n", &lucky);

//	char *str = malloc(4);
//	
//	str[0] = 'h';
//	str[1] = 'e';
//	str[2] = 'y';
//	str[3] = '\0';
//
//	char * secondString = 
//
//	unsigned char num = 130;
//	printf("test: %s, I love the number %i.\n",str,num);
//	int x = 4;
//	int y = 10;
//
//	int * pX = &x;
//
//	*pX = 8;
//	pX = &y;
//
//	printf("x = %i\n&pX = %i\n", x, *pX);
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

