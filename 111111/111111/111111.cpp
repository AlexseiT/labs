#include <stdlib.h>
#include <stdio.h>
#include <math.h>
int main() {
	int a;
	scanf_s("%d", &a);
	if (a % 2 == 0 && a!=2)  printf("YES");
	else printf("NO");
}