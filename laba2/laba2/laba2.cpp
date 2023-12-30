#include <stdlib.h>
#include <stdio.h>
int main() {
	float a[2], ma, mi;

	printf("Enter:\n");
	scanf_s("%f %f %f", &a[0], &a[1], &a[2]);

	ma = a[0];
	mi = a[0];

	for (int i = 0; i < 3; i++) {
		if (a[i] > ma) ma = a[i];
		if (a[i] < mi) mi = a[i];
	}
	printf("%f %f\n", ma, mi);

	for (int i = 0; i < 3; i++) {
		if (a[i] == ma) a[i] = mi;
		if (a[i] == mi) a[i] = ma;
	}
	printf("%f %f %f", a[0], a[1], a[2]);

	return 0;
}