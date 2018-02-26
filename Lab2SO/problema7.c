#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int num_aleatorio();

int main(int argc, char const *argv[])
{
	int a,b,res,solucion;
	srand(time(NULL));
	int final;
	int continuar;

	printf("%s\n", " 1 para continuar 0 si desea terminar" );
	scanf("%d" , &final);
	

	while(final==1){

		a=num_aleatorio();
		b=num_aleatorio();
		solucion=a*b;
		continuar=1;

		printf("cuanto es %d veces %d\n ", a,b);
		scanf("%d", &res);


		continuar=1;

		while(continuar==1){
			if (res==solucion)
			{
				printf("%s\n", "Muy bien!" );
				printf("Desea continuar? 1 para SI, 0 para NO \n");
				scanf("%d" , &continuar);
				if (continuar==0)
				{
					final=0;
				}
				else{
					continuar=0;
				}

			}
			else{
				printf("%s\n", "No. Por favor intenta nuevamente");
				printf("%s\n","1 para SI, 0 para NO" );
				scanf("\n%d" , &continuar);
				if (continuar==0)
				{
					final=0;
				}
				else{
					printf("cuanto es %d veces %d\n", a,b);
					scanf("%d", &res);

				}

			}
		}
	}

	return 0;
}

int num_aleatorio(){
	int X = rand() % 10;
	return X;
}