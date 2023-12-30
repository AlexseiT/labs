#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <vector>
#include <algorithm>




int main() {

	using namespace std;

	std::vector <int> C;
	std::vector <int> D;
	std::vector <int> E;

	for (int i = 0; i <20 ; i++) {
		C.push_back(rand() % 20 + 1);
		D.push_back(rand() % 20 + 1);
	}

	sort(C.begin(), C.end());
	sort(D.begin(), D.end());

	for (int i = 0; i < 20; i++) {
		E.push_back(C.at(i));
	}
	for (int i = 0; i < 20; i++) {
		E.push_back(D.at(i));
	}
	for (int i = 0; i < E.size(); i++) {
		printf("%d\n",E.at(i));
	}

}
