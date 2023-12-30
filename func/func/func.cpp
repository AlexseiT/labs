#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

int sum(int a, int b) {
	int c = a + b;
	return c;
}
int raz(int a, int b) {
	int c = a - b;
	return c;
}
int del(float a, float b) {
	float c = a / b;
	return c;
}
int koren(float a) {
	float c = sqrt(a);
	return c;
}
int kv(int a) {
	int c = a * a;
	return c;
}
int umn(int a, int b) {
	int c = a * b;
	return c;
}
int Disk2(int a, int b, int c) {
	int x = del(raz(umn(-1,koren( kv (b) - 4 * umn(a,c))),b),umn(2,a));
	return x;
}
int Disk1(int a, int b, int c) {
	int x = del(raz(koren(kv(b) - 4 * umn(a, c)), b), umn(2, a));
	return x;
}
int main() {

	float  a, b,c,x1,x2;

	scanf_s("%f %f %f", &a, &b, &c);
	
	x1 = Disk1(a, b, c);

	x2 = Disk2(a, b, c);

	if (koren(kv(b) - 4 * umn(a, c) < 0)) printf("Diskriminant < 0"); 

	else if (x1 == x2) printf("%3.1f", x1); else

	printf("%3.1f and %3.1f", x1, x2);
}