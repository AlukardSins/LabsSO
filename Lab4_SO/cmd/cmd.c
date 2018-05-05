#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <linux/limits.h>
#include <time.h>
#include <wait.h>
#include <stdbool.h>

#include "parser.h"

#define TAM 100


int launch(char *command, char **params, bool background);

int main ()
{
	char ** items;
	int num, background;
	char expresion[TAM];
	int status;

	while(1)
	{
		printf (" >> ");
		fgets (expresion, TAM, stdin);

		// Obtener los parámetros de la consola
		num = separaItems (expresion, &items, &background);

		if (num > 0)
		{
			// comparar para extraer el nombre del programa a ejecutar
			if (strcmp(items[0], "mypwd") == 0)
			{
				char* cwd;
				char buff[PATH_MAX + 1];

				cwd = getcwd( buff, PATH_MAX + 1 );
				if( cwd != NULL )
				{
					return printf( "Directorio actual %s.\n", cwd );
				}
			}
			if (strcmp(items[0], "mycp") == 0)
			{
				char *params[1];
				strcpy(params[0], items[0]);
				return launch(items[0], params, background);
			}
			if (strcmp(items[0], "myecho") == 0)
			{
				printf("%s\n", items[1]);
			}
			if (strcmp(items[0], "myclr") == 0)
			{
				char *params[1];
				strcpy(params[0], items[0]);
				return launch(items[0], params, background);
			}
			if (strcmp(items[0], "mytime") == 0)
			{
				time_t r_time;
				struct tm * timeinfo;
				time (&r_time);
				timeinfo = localtime (&r_time);
				printf ("Fecha y hora actual: %s", ctime(timeinfo));
			}
			if (strcmp(items[0], "mykill") == 0)
			{
				char *params[1];
				strcpy(params[0], items[0]);
				return launch(items[0], params, background);
			}
			if (strcmp(items[0], "mypause") == 0)
			{
				system("pause");
			}
			if (strcmp(items[0], "psinfo") == 0)
			{
				char *params[1];
				strcpy(params[0], items[0]);
				return launch(items[0], params, background);
			}
			if (strcmp(items[0], "myps") == 0)
			{
				char *params[1];
				strcpy(params[0], items[0]);
				return launch(items[0], params, background);
			}
			if (strcmp(items[0], "mygrep") == 0)
			{
				char *params[1];
				strcpy(params[0], items[0]);
				return launch(items[0], params, background);
			}
			if (strcmp(items[0], "myexit") == 0)
			{
				exit(0);
			}
		}

		// Liberar recursos
		liberaItems (items);
	}

	return 0;
}

int launch(char *command, char **params, bool background)
{
	int status;
	pid_t pid_programa;
	switch (pid_programa = fork())
	{
		case -1: // Validar error al crear hijo
			printf("Error ejecutando el comando.\n");
			return -1;
		case 0:
			// sustituir el programa por el programa externo
			execv( strcat("./", command), params);

			// Validar si hubo error al sobreescribirlo
			printf("Hubo un error llamando el programa\n");
			exit(0);
	}

	// Validar si el programa padre espera al hijo o no
	if (!background)
		wait(&status);

	return 0;
}