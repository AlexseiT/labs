#include <iostream>
#include <stdlib.h>
#include <ctime>

using namespace std;

int main()
{
	int n;
	cin >> n;

	int** a = new int* [n];
	for (int i = 0; i < n; i++) {

		a[i] = new int[i+1];

		for (int j = 0; j <= i; j++) {

				a[i][j] = (i + 1) * (j + 1);

				cout << a[i][j] << " ";

		}
		cout << endl;
	}

	for (int i = 0; i < n; i++) {
		delete[] a[i];
		delete[] a;
}

