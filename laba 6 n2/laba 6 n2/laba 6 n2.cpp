#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <vector>

long int fact(long int m)
{
	if (m == 0 || m == 1) return 1;
	return m * fact(m - 1);
}

long int formula(long int a, long int b)
{
	long int c = fact(a) * fact(b - a);
	return c;
}

int main() {

	using namespace std;

	int n,x;

	std::vector <int> C;
	
	scanf_s("%d", &n);

	for (int i = 0; i <= n; i++) {
		x = fact(n) / formula(i, n);
		C.push_back(x);
	}
	for (int i = 0; i <= n; i++) {
		printf("%d  ", C.at(i));
	}
}
