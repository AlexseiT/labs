#include <stdlib.h>
#include <stdio.h>
int main() {
	float a[3], ma, mi;

	printf("Enter:\n");
	scanf_s("%f %f %f", &a[0], &a[1], &a[2]);

	ma = a[0];
	mi = a[0];

	for (int i = 0; i < 3; i++) {
		if (a[i] > ma) ma = a[i];
		if (a[i] < mi) mi = a[i];
	}
	for (int i = 0; i < 3; i++) {
		if (a[i] == ma) a[i] = mi; else
		if (a[i] == mi) a[i] = ma;
	}
	printf("%3.1f %3.1f %3.1f", a[0], a[1], a[2]);

	return 0;
}