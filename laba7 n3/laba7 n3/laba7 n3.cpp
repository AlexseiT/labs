#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <iostream>

int main() {

	using namespace std;

	std::vector <float> a;
	std::vector <float> b;


	for (int i = 0; i < 20; i++) {
		a.push_back((float) rand() * (20) / RAND_MAX - 10);
		if (a[i]>0) b.push_back(a.at(i));
		printf("%2.2f\n", a.at(i));
		
	}

	printf("--------------------------\n");
	for (int i = 0; i < 20; i++) {
		printf("%2.2f\n", b.at(i));
	}

}

