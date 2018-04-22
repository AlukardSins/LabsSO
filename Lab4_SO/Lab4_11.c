#include <stdio.h>

unsigned long long int factorial(unsigned int i) {
	if(i <= 1) {
		return 1;
	}
	return i * factorial(i - 1);
}

int  main() {
	//Factorial de 10
	int factor = 10;
	//Crear el padre
	int p = getpid();
	//Variable para almacenar respuesta de waitpid
	int ab;

	//Crear 3 hijos
	for (int i = 0; i < 3; i++) {
		int son = fork()
		if (son = 0) {
			printf("Soy el hijo #%d\t y solucione 10! = %d\t asi que admiradme soy inteligente. *se va a la mesa a comer colbon*\n", i, factorial(factor));
		} else {
			waitpid(son, &ab, 0);
		}
	}
	return 0;
}