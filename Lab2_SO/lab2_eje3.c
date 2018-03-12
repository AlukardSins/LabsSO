#include <stdio.h>

char *obtenerSubcadena(char *array,int index);

int main(int argc, char const *argv[]) {
  test();
  return 0;
}

char *obtenerSubcadena(char *array,int index){
  char *p1= &array[index];
  return p1;
}

void test (void){
	char cad[]="tengo una cadena de caracteres";
	char *p1 = obtenerSubcadena(cad,8);
	printf("%s\n", p1);
}
