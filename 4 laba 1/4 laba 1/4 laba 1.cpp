#include <iostream>
#include <stdlib.h>
#include <ctime>

using namespace std;

void FillRand(int **a, int m, int n)
{
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
		a[i][j] = rand() % 100;
}

void PrintMas(int **a, int m, int n)
{
	for (int i = 0; i < m; i++) {
		cout << endl;
		for (int j = 0; j < n; j++)
			cout << a[i][j] << "    ";
	}
	cout << endl;
}

const int n = 5;

int main() 
{
	srand(time(NULL));
	int m, x, y, ma;

	cin >> m;

	int** a = new int* [m];
	for (int i = 0; i < m; i++)
		a[i] = new int[n];

	int** b = new int* [m-1];
	for (int i = 0; i < m-1; i++)
		b[i] = new int[n-1];

	FillRand(a, m, n);

	PrintMas(a, m, n);
	
	ma = a[0][0];
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			if (ma <= a[i][j])
			{
				ma = a[i][j];
				x = i;
				y = j;
			}

	cout << endl;
	cout << x << endl;
	cout << y << endl;

	int i1 = 0;
	int j1 = 0;

	for (int i = 0; i < m - 1; i++) {
		if (i == x) i1++;
		for (int j = 0; j < n - 1; j++) {
			if (j == y) j1++;
			b[i][j] = a[i1][j1];
			j1++;
		}
		i1++;
		j1 = 0;
	}

	PrintMas(b, m-1, n-1);

	
}
