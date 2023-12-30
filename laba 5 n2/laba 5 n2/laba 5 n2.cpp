#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <math.h>


int main() {
	setlocale(LC_ALL, "Russian");
	float a, b, c, xn, xk, h, y, ma, mi, i,s;
	printf("Введи a, b, c, x нач., x кон., h\n");
	scanf_s("%f %f %f %f %f %f", &a ,&b ,&c ,&xn , &xk ,&h);

	i = xn;
	ma = a * pow(xn, 2) * sin(xn) + b * xn * sin(xn) + c * sin(xn);
	mi = ma;
	do {
		i -= h;
		s = a * pow(i, 2) * sin(i) + b * i * sin(i) + c * sin(i);
		if (s > ma) ma = s;
		if (s < mi) mi = s;
	} while (i > xk);
	i = xn;
	printf("max = %f\n", ma);
	printf("min = %f\n", mi);
}