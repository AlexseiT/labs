#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <vector>

int func(int a) {
	int c;
	a = a * 2;
	if (a > 9 && a != 0) c = a - 9; else c = a;
	return c;
}

int main() {
	int const n = 15;
	int a[n], kol1 = 0, kol2 = 0, x;


	for (int i = 0; i < n; i++) {
		scanf_s("%d ", &a[i]);
	}

	for (int i = 0; i < n; i++) {
		if (i % 2 == 0) kol1 = +a[i]; else 
			kol2 = +func(a[i]);
		
	}
	x = kol1 + kol2;
	printf("%d ",x);
}
