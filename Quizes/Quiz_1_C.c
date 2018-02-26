#include "stdio.h"

int sumaCifras (int numero);

int main() {
	int ingresado, suma, continuar = 1;

	do {

		printf("Por favor ingresar un numero positivo: ");
		scanf("%d", &ingresado);

		if (ingresado >= 0) {
			suma = sumaCifras(ingresado);

			printf("La suma de los digitos del numero: %d\tEs: %d\n", ingresado, suma);

			printf("Presione 1 para continuar: ");
			scanf("%d", &continuar);
		} else if (ingresado < 0) {
			printf("\nPor favor ingresar un numero positivo.\n");

			printf("\nPresione 1 para continuar 0 para terminar la ejecucion: ");
			scanf("%d", &continuar);
		}

	} while (continuar == 1);

	return 0;
}

int sumaCifras (int numero) {
	int resultado = 0, sumCifras = 0;

	while (numero != 0){
		resultado = numero % 10;
		numero = numero / 10;
		sumCifras = sumCifras + resultado;
	}

	return sumCifras;
}