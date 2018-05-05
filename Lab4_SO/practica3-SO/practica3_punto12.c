#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>



int main()
{
	//Crear hijo
	int pid = fork();

	if (pid == 0) {
		//Se creo correctamente
		//Ruta del proceso
		char ruta[20];
		char args[20];
		//Ingresar la ruta
		printf("Ingresar la ruta del proceso a ejecutar: ");
		scanf("%s", ruta);
		//Ingresar argumentos
		printf("Ingresar los argumentos: ");
		scanf("%s", args);
		//Se asigna ruta y argumentos al nuevo exec
		char const *argv[] = args;
		execv(ruta,argv);
	} else if (pid < 0){
		printf("Valio madres\n");
	} else {
		waitpid(pid,0,0); /* wait for child to exit */
	}
	return 0;
}
