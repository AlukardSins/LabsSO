#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
 #include <signal.h> 

int main(int argc, char *argv[])
{
	// Validar el mínimo de argumentos
	if (argc == 3)
	{
		// Obtener los argumentos
		int signal = atoi(argv[1]);
		pid_t pid = atoi(argv[2]);

		// Ejecutar el llamado al sistema "kill"
		if (kill(pid, signal) == 0)
		{
			printf("Se envió la señal.\n");
		}
		else if (kill(pid, signal) == -1)
		{
			printf("Hubo un error enviando la señal.\n");
		}
	}
	else
	{
		printf("Número incorrecto de parámetros.\n");
	}

	return 0;
}
