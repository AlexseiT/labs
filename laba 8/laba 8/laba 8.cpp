#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <vector>
#include <algorithm>

float func(float x)
{
	float y = (x+1)*(x+1)*sqrt(log10(x));
	return y;
}

// 3 задание

int main() {

	using namespace std;
	float a,b,h,N;

	std::vector <float> M;

	scanf_s("%f %f %f", &a, &b, &N);

	h = (b - a) / N;


	for (int i = 0; a <= b; i++) {
		M.push_back(func(a));
		a += h;
		printf("%2.2f\n",M.at(i));
	}

	
}


