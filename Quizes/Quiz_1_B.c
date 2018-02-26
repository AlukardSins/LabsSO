#include "stdio.h"

int main(void) {
	
	int n, m;
	n = 10;

	while (++n <= 13) {
		printf("%d\n", n);
	}

	do {
		printf("\t%d\n", n);
	} while (++n <= 12);

	printf("\n***\n");

	for (n = 1; n*n < 60; n+=3) {
		printf("%d\n", n);
	}

	printf("\n***\n");

	for (n = 4; n > 0; n--) {
		for (m = 0; m <= n; m++) {
			printf("+");
		} printf("\n");
	}
	return 0;
}