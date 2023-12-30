#include <stdlib.h>
#include <stdio.h>
#include <math.h>
int main() {
	int n, m, a;
	scanf_s("%d %d %d", &n , &m , &a);
	if (a % 2 == 0 && a != 2)  printf("YES");
	else printf("NO");
}