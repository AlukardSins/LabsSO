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
		printf (" Lab3-Shell>> ");
		fgets (expresion, TAM, stdin);

		// Obtener los parámetros de la consola
		num = separaItems (expresion, &items, &background);

		if (num > 0)
		{
			// comparar para extraer el nombre del programa a ejecutar

			//funcion mypwd para extraer el Dir actual
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

			//funcion mycp que permite copiar el contenido de un archivo a otro
			if (strcmp(items[0], "mycp") == 0)
			{
						pid_t pid_programa;
						switch (pid_programa = fork())
						{
							case -1: // Validar error al crear hijo
								printf("Error ejecutando el comando.\n");
								return -1;
							case 0:

								execl("./libs/sources/mycp", "./mycp", items[1], items[2], items[3], NULL);
								// Validar si hubo error al sobreescribirlo
								printf("Hubo un error llamando el programa\n");
								exit(0);
						}
						// Valida si el programa padre espera al hijo o no
						if (!background)
							wait(&status);

			}

			//funcion myecho para mostrar en consola
			if (strcmp(items[0], "myecho") == 0)
			{
				printf("%s\n", items[1]);
			}


			//funcion myclr para borrar la consola
			if (strcmp(items[0], "myclr") == 0)
			{
						pid_t pid_programa;
						switch (pid_programa = fork())
						{
							case -1: // Validar error al crear hijo
								printf("Error ejecutando el comando.\n");
								return -1;
							case 0:

								execl("./libs/sources/myclr", "./myclr",items[1], NULL);
								// Validar si hubo error al sobreescribirlo
								printf("Hubo un error llamando el programa\n");
								exit(0);
						}
						// Validar si el programa padre espera al hijo o no
						if (!background)
							wait(&status);

			}

			//funcion mytime para mostrar la fecha actual
			if (strcmp(items[0], "mytime") == 0)
			{
				time_t r_time;
				time (&r_time);
				printf ("Fecha y hora actual: %s", ctime(&r_time));
			}

			//funcion mykill manda señal a un proceso
			if (strcmp(items[0], "mykill") == 0)
			{
					pid_t pid_programa;
					switch (pid_programa = fork())
					{
						case -1: // Validar error al crear hijo
							printf("Error ejecutando el comando.\n");
							return -1;
						case 0:

							execl("./libs/sources/mykill", "./mykill",items[1], items[2],
							 																	items[3], items[4],NULL);
							// Validar si hubo error al sobreescribirlo
							printf("Hubo un error llamando el programa\n");
							exit(0);
					}
					// Validar si el programa padre espera al hijo o no
					if (!background)
						wait(&status);
			}

			//funcion psinfo de la practica 2
			if (strcmp(items[0], "psinfo") == 0)
			{
					pid_t pid_programa;
					switch (pid_programa = fork())
					{
						case -1: // Validar error al crear hijo
							printf("Error ejecutando el comando.\n");
							return -1;
						case 0:

							execl("./libs/sources/psinfo", "./psinfo",
							items[1],items[2],items[3],items[4],NULL);
							// Validar si hubo error al sobreescribirlo
							printf("Hubo un error llamando el programa\n");
							exit(0);
					}
					// Validar si el programa padre espera al hijo o no
					if (!background)
						wait(&status);
			}
			if (strcmp(items[0], "myps") == 0)
			{
					pid_t pid_programa;
					switch (pid_programa = fork())
					{
						case -1: // Validar error al crear hijo
							printf("Error ejecutando el comando.\n");
							return -1;
						case 0:

							execl("./libs/sources/myps", "./myps",items[1],NULL);
							// Validar si hubo error al sobreescribirlo
							printf("Hubo un error llamando el programa\n");
							exit(0);
					}
					// Validar si el programa padre espera al hijo o no
					if (!background)
						wait(&status);
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
