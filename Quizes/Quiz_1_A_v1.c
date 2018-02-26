#include "stdio.h"

int main(void) {
	int num;
	for (num = 1; num <= 11; num++) {
		if (num % 3 == 0)
			printf("$");
		else
			printf("*");
		printf("#");
		printf("%");
	}
	
	printf("\n");
	return 0;
}