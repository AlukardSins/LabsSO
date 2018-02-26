#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int lanzamiento();

int main() {
	int cant_caras=0;
	int cant_sellos=0;
	int lanzamientos, moneda;

	srand(time(NULL));

	printf("%s\n", "Ingrese la cantidad de lanzamientos " );
	scanf("%d" ,&lanzamientos);

	printf("%s\n"," " );

	for (int i = 0; i < lanzamientos; ++i)
	{
		moneda = lanzamiento();
		if (moneda==0)
		{
			printf("%s", "C" ); // imrprime cara
			cant_caras ++;
		}
		else{
			printf("%s", "S" ); //imprime sello
			cant_sellos ++;
		}
	}

	printf(" cantidad de caras: %d cantidad de sellos: %d\n", cant_caras , cant_sellos   );

	return 0;
}


int lanzamiento() {	
	int aleatorio = rand()% 2;

	return aleatorio;
}