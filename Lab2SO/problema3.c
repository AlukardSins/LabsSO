#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int numeroAleatorio(int N,int M);

int main () { 
  /*int N, M, cant, i, aleatorio;
  printf("Digite la cantidad de números que desea generar: ");
  scanf("%d",&cant);
  printf("Digite los limites (primero el superior, luego el inferior): ");
  scanf("%d%d",&N,&M);
  srand(time(NULL)); // Inicializacion del generador
  for(i = 0; i < cant; i ++) { 
    aleatorio = rand()%(N-M+1)+M; //Genera un numero entre M y N
    printf("%d ", aleatorio);
  } 
  printf("%d\n", aleatorio);
  */



  srand(time(NULL));
  int N , M , cantidad , i;
  
  printf("Digite la cantidad de números que desea generar: ");
  scanf("%d",&cantidad);
  printf("Digite los limites (primero el superior, luego el inferior): ");
  scanf("%d %d" , &N,&M);

  for(i = 0; i < cantidad; i ++) { 
    int numAl= numeroAleatorio(N,M);
    printf("%d\n" , numAl);
  }

  system("PAUSE");
  return 0;
}


int numeroAleatorio(int N , int M){
  int aleatorio = rand()%(N-M+1) +M;
  return aleatorio;
}


