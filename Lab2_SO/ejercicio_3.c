#include <stdio.h>

char *obtenerSubcadena(char *array,int index);

int main(int argc, char const *argv[]) {
  char cad[]="tengo una cadena de caracteres";
  char *p1 = obtenerSubcadena(cad,8);
  printf("%s\n", p1);
  return 0;
}

char *obtenerSubcadena(char *array,int index){
  char *p1= &array[index];
  return p1;
}
