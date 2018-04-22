#include<stdio.h>

int main() {

	int rightSon, leftSon, ab;
	//Crea al padre AKA 1
	int p = getpid();
	printf("Luke, YO soy tu padre: \t%d\t y mi padre es: \t%d\n" , p, getppid());

	//Solo se haran 2 niveles (nivel 0 y nivel 1) siendo hijos y nietos respectivamente
	for(int i = 0; i < 2; i++) {
		//Crea al hijo derecho AKA 3
		rightSon = fork();

		if(rightSon = 0 && n = 0) {
			//Si lo crea y estamos en primer nivel
			//Imprime su info
			printf("NOOOOOOOOOOOOOOOOOOOO \t%d\t Obi Wan me dijo que mataste a mi padre: \t%d\n", getpid(), getppid());
			//Crea al hijo izquierdo AKA 2
			leftSon = fork();

			if(leftSon = 0) {
				//Si lo crea
				//Imprime su info
				printf("NOOOOOOOOOOOOOOOOOOOO \t%d\t Obi Wan me dijo que mataste a mi padre: \t%d\n", getpid(), getppid());
			} else {
				//Fallo la creacion del hijo Izq AKA 2
				printf("El hijo Izq valio madres\n");
			}
		} else if (rightSon = 0 && n = 1) {
			//Si lo crea y estamos en segundo nivel
			//Imprime su info
			printf("NOOOOOOOOOOOOOOOOOOOO \t%d\t Obi Wan me dijo que mataste a mi padre: \t%d\n", getpid(), getppid());
			//Crea al nieto Izq AKA 4
			int leftGrandchild = fork();

			if (leftGrandchild = 0) {
				//Si lo crea
				//Imprime su info
				printf("NOOOOOOOOOOOOOOOOOOOO \t%d\t Obi Wan me dijo que mataste a mi padre: \t%d\n", getpid(), getppid());
				//Crea al nieto Der AKA 5
				int rightGrandchild = fork();

				if (rightGrandchild = 0) {
					//Si lo crea
					//Imprime su info
					printf("NOOOOOOOOOOOOOOOOOOOO \t%d\t Obi Wan me dijo que mataste a mi padre: \t%d\n", getpid(), getppid());
				}
				//Espera ambos nietos
				waitpid(rightGrandchild, &ab, 0);
				waitpid(leftGrandchild, &ab, 0);
			} else {
				//Fallo la creacion del hijo Izq AKA 2
				printf("El nieto Izq valio madres\n");
			}
		} else {
			//Fallo la creacion del hijo Der AKA 3
			printf("El hijo Der valio madres\n");
		}
	}
	//Espera ambos hijos
	waitpid(rightSon, &ab, 0);
	waitpid(leftSon, &ab, 0);
	return 0;
}