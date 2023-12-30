#include <stdio.h>

int main() {
	float a, b, c;
	char x;

	
	scanf_s("%d", &a);
	
	scanf_s("%d", &c);

	scanf_s("%c", &x);

	if (x == '+') {
		c = a + b;
		printf("%d\n", c);
	}
	if (x == '-') {
		c = a - b;
		printf("%d\n", c);
	}
	if (x == '*') {
		c = a * b;
		printf("%d\n", c);
	}
	if (x == '/') {
		c = a / b;
		printf("%d\n", c);
	}
	return 0;
}