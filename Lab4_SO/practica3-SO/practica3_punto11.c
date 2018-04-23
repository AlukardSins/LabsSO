#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

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

	//Crear 3 hijos
	for (int i = 0; i < 3; i++) {
		int son = fork();
		if (son == 0) {
			printf("Soy el hijo #%d\t y solucione 10! = %lu\t\n", i, factorial(factor));
		} else if (son < 0){
			printf("Esto valio madres\n");
		} else {
			waitpid(son, 0, 0);
		}
	}
	return 0;
}
