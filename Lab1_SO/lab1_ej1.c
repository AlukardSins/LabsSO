#include <stdio.h>

int multiplo(int a,int b);

int main() {
	int res = multiplo(4,2);

	printf("%d\n", res);

	return 0;
}

int multiplo(int a, int b) {
	
	if ((a % b) ==0) {
		return 1;
	} else {
		return 0;
	}
}