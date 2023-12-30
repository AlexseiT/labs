#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <vector>
#include <algorithm>

float func( float a, float b, float x, float c)
{
	float y = a * x * x * sinh(x) + b * x + c;
	return y;
}


int main() {

	using namespace std;
	int k;
	float x1, x2, h, a, c, b;

	std::vector <float> M;

	scanf_s("%f %f %f %f %f %f", &a, &b, &c, &x1, &x2, &h);

	if (x1 > x2) h *= -1;

	for (int i = 0; x1 > x2; i++) {
		x1 += h;
		M.push_back(func(a, b, x1, c));
		k = i;
	}

	sort(M.begin(), M.end(), std::greater<float>());

	

	for (int i = 0; i <= k; i++) {
		printf("%3.2f \n", M.at(i));
	}
}

