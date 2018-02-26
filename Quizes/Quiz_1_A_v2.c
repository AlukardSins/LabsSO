#include "stdio.h"

int main(void) {
	
	int i = 0;

	while (i < 3) {
		switch (i++) {
			case 0	:	printf("Merry");
						break;
			case 1	:	printf("Merr");
						break;
			case 2	:	printf("Mer");
						break;
			default	: 	printf("Oh no!");
						break;
		}
		printf("\n");
	}
	return 0;
}
