#include <stdio.h>
#include <string.h>

int obtenerIndice(char *array, char ch);
int contarCaracter(char *array,char ch);
void test(void);

int main(int argc, char const *argv[])
{
	test();
	return 0;

}

int obtenerIndice(char *array, char ch){
	int num = contarCaracter(array,ch);
	if(num ==-1) return -1;
	char *apuntador;
	int subindice;
	apuntador = strchr(array,ch);
	subindice = apuntador - array;
	return subindice;
}

//funcion del ejercicio 1
int contarCaracter(char *array,char ch){
	int num_veces =0;

	while(*array != '\0'){ //lo que hay en el array
		if (*array == ch)
		{
			num_veces++;
		}
		array ++;
	}
	if (num_veces==0)
	{
		return -1;
	}
	return num_veces;
}

void test (void){
	char cad[]="tengo_una_cadena_de_caracteres";
	char ch = 'w';
	int res = obtenerIndice(cad,ch);
	printf("%d\n",res);
}
