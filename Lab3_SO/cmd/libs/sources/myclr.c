#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TAM 100

int main(int argc, char *argv[])
{
	// Validar el mínimo de argumentos
	int result;
	if (argc == 1)
	{
		// Ejecutar el llamado al sistema "cls"
		result = system("reset");
		if (result == -1)
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