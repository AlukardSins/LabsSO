#include <stdio.h>

int reversar (int x);

int main() {
	int n, res;

	printf("Ingresa un numero: ");
	scanf("%d", &n);

	res = reversar(n);

	printf("Numero invertido = %d", res);

	return 0;
}

int reversar (int x) {
	int rev = 0, sobra;

	while(x != 0) {
		sobra = x%10;
		rev = rev*10 + sobra;
		x /= 10;
	}

	return rev;
}