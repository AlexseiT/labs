#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main() {
	int n, m = 0, k = 0, j = 0;
	int* b, * c, * d;

	printf("Array size=");
	scanf("%d", &n);

	b = new int[n];
	srand(time(NULL));
	for (int i = 0; i < n; i++)
	{
		b[i] = rand() % 101 - 50;
		printf("%d ", b[i]);
	}
	for (int i = 0; i < n; i++) {
		if (b[i] >= 0)
			m++; 
		else
			k++;

	}
	printf("\nMemory for c=%d Memory for d=%d\n", m, k);

	c = new int[m];
	d = new int[k];

	printf("\nArray c\n");

	for (int i = 0; i < n; i++) {
		if (b[i] >= 0) {
			c[j] = b[i];
			printf("%d ", c[j]);
			j++;
		}
	}
	delete[] c;
	j = 0;

	printf("\nArray d\n");

	for (int i = 0; i < n; i++) {
		if (b[i] < 0) {
			d[j] = b[i];

			printf("%d ", d[j]);

			j++;
		}
	}
	delete[] b;
	delete[] d;
}
