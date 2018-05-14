#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  int estado1 ,estado2, estado3;

  pid_t pid_h1, pid_h2, pid_h3;
  pid_t pid_n;
  int i = 0;
  pid_h1 = fork();
  if(pid_h1 == 0) {// hijo
    i++;
    pid_n = fork();
    if(pid_n==0) {
      i++;
      printf("NIETO DEL HIJO 1: i = %d\n",i);
    }else {
      printf("HIJO 1: i = %d\n",i);
    }
  }else {
    wait(&estado1);
    pid_h2 = fork();
    if(pid_h2 == 0) {
      i++;
      printf("HIJO 2: i = %d\n",i);
    }else {
      wait(&estado1);
      pid_h3 = fork();
      if(pid_h3 == 0) {
        i++;
         printf("HIJO 3: i = %d\n",i);
      }else {
         wait(&estado1);
         printf("PAPA: i = %d\n",i);
      }
    }
  }
  return 0;
}
