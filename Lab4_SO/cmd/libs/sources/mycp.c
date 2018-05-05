#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	// Validar el mínimo de argumentos
	if (argc == 3)
	{
		// Obtener los argumentos
		FILE *origen;
		FILE *destino;
		char ch;
		origen = fopen(argv[1], "r");
		destino = fopen(argv[2], "w");

		// Iniciar copia
		if(origen == NULL){
			printf("No ha sido posible abrir el archivo de origen\n");
			fclose(destino);
		} else {
			while((ch = fgetc(origen)) != EOF){
				fputc(ch, destino);
			}
			printf("La copia se ha realizado con éxito\n");
			fclose(origen);
			fclose(destino);
		}
	}
	else
	{
		printf("Número incorrecto de parámetros.\n");
	}
	return 0;
}
