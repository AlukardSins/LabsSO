#include <stdio.h>

void test(void);
int contarCaracter(char *,char);


int main()
{
	test();
	return 0;
}

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
	char cad[] = "cadenadecaracteres";
	int res = contarCaracter(cad,'w');
	printf("%d\n", res);
}
