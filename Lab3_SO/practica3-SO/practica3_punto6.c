#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
  int PID ,PID_NIETO;
   printf("PADRE :Hola\n");
   PID = fork();
   if(PID == 0){ // HIJO
     printf("HIJO: Mundo\n");
     PID_NIETO  = fork();
     if(PID_NIETO == 0){ // HIJO
       printf("NIETO : !\n");
       PID_NIETO  = fork();
     }
   }
}
