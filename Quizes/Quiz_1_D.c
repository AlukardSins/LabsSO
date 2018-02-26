#include "stdio.h"

long long d2b (int dec);

int main() {
	int ingresado;

	printf("Por favor ingresar el numero a convertir: ");
	scanf("%d", &ingresado);

	printf("El numero: %d representado en binario es: %lld\n", ingresado, d2b(ingresado));
		
	return 0;
}

long long d2b (int dec) {
	long long bin = 0;
 	int sobrante, ubicacion = 1, paso = 1;

 	while (dec != 0) {
 		sobrante = dec % 2;
        printf("Paso %d: %d/2, Sobrante = %d, Divisor = %d\n", paso++, dec, sobrante, dec/2);
 		dec = dec / 2;
 		bin = bin + (sobrante * ubicacion);
 		ubicacion = ubicacion * 10;
 	}

	return bin;
}