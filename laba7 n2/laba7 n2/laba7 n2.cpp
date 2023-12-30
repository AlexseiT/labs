#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <iostream>

int main() {

	using namespace std;
	int k = 0;
	
	std::vector <int> a;

	

	for (int i = 0; i < 15 ; i++) {
		a.push_back(rand() % 10 + 1);
		printf("%d\n", a.at(i));
	}

	printf("--------------------------\n");

	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++)
			if (a.at(i) == a.at(j)) k += 1;
		if (k == 1) printf("%d\n", a.at(i));
		k = 0;
	}

}

