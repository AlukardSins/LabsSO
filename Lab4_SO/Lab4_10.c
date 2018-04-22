#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

	int rightSon, leftSon;
	//Crea al padre AKA 1
	int p = getpid();
	printf("Luke, YO soy tu padre: \t%d\t y mi padre es: \t%d\n" , p, getppid());

	//Solo se haran 2 niveles (nivel 0 y nivel 1) siendo hijos y nietos respectivamente
	for(int i = 0; i < 2; i++) {
		//Crea al hijo derecho AKA 3
		rightSon = fork();

		if(rightSon == 0 && n == 0) {
			//Si lo crea y estamos en primer nivel
			//Imprime su info
			printf("NOOOOOOOOOOOOOOOOOOOO \t%d\t Obi Wan me dijo que mataste a mi padre: \t%d\n", getpid(), getppid());
			//Crea al hijo izquierdo AKA 2
			leftSon = fork();

			if(leftSon == 0) {
				//Si lo crea
				//Imprime su info
				printf("NOOOOOOOOOOOOOOOOOOOO \t%d\t Obi Wan me dijo que mataste a mi padre: \t%d\n", getpid(), getppid());
			} else if (leftSon < 0){
				//Fallo la creacion del hijo Izq AKA 2
				printf("El hijo Izq valio madres\n");
			} else {
				break;
			}
		} else if (rightSon == 0 && n == 1) {
			//Si lo crea y estamos en segundo nivel
			//Imprime su info
			printf("NOOOOOOOOOOOOOOOOOOOO \t%d\t Obi Wan me dijo que mataste a mi padre: \t%d\n", getpid(), getppid());
			//Crea al nieto Izq AKA 4
			int leftGrandchild = fork();

			if (leftGrandchild == 0) {
				//Si lo crea
				//Imprime su info
				printf("NOOOOOOOOOOOOOOOOOOOO \t%d\t Obi Wan me dijo que mataste a mi padre: \t%d\n", getpid(), getppid());
				//Crea al nieto Der AKA 5
				int rightGrandchild = fork();

				if (rightGrandchild == 0) {
					//Si lo crea
					//Imprime su info
					printf("NOOOOOOOOOOOOOOOOOOOO \t%d\t Obi Wan me dijo que mataste a mi padre: \t%d\n", getpid(), getppid());
				} else if (rightGrandchild < 0) {
					printf("El nieto Der valio madres\n");
				} else {
					//Espera ambos nietos
					waitpid(rightGrandchild, 0, 0);
					waitpid(leftGrandchild, 0, 0);
				}
			} else if (leftSon < 0) {
				//Fallo la creacion del hijo Izq AKA 2
				printf("El nieto Izq valio madres\n");
			} else {
				break;
			}
		} else if (rightSon < 0){
			//Fallo la creacion del hijo Der AKA 3
			printf("El hijo Der valio madres\n");
		} else {
			//Espera ambos hijos
			waitpid(rightSon, 0, 0);
			waitpid(leftSon, 0, 0);
			return 0;
		}
	}
}