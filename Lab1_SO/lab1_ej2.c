#include <stdio.h>
#include <math.h>

double progresion(double x, double n);

int main() {
	double base;
	double exponente;
	double progresionG;

	printf("%s\n","Ingrese X y n");
	scanf("%lf %lf" , &base, &exponente);

	progresionG = progresion(base,exponente);

	printf("%.1lf\n", progresionG );
	
	return 0;
}

double progresion(double x, double n) {
	double res = 0;

	for (int i = 0; i <= n; ++i) {
		res = res + pow(x,i);
	}
	return res;
}