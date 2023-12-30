#include <iostream>
#include <stdlib.h>
#include <ctime>

using namespace std;

void FillRand(int* a, int n)
{
	for (int i = 0; i < n; i++)
			a[i] = (rand() % 9)+1;
}
void PrintMas(int** a, int m, int n)
{
	for (int i = 0; i < m; i++) {
		cout << endl;
		for (int j = 0; j < n; j++)
			cout << a[i][j] << "    ";
	}
	cout << endl;
}
void PrintMas1(int* a, int n)
{
	for (int i = 0; i < n; i++) {
			cout << a[i]<< " ";
	}
	cout << endl;
}
int main()
{
	srand(time(NULL));
	int n, k, p;
	int l = 0;
	cin >> n;
	int* a = new int [n];
	FillRand(a, n);
	PrintMas1(a, n);
	cin >> k;
	if (n % k == 0) p = n / k;
	else p = n / k + 1;
	int** b = new int* [p];
	for (int i = 0; i < p; i++) {
		b[i] = new int[k];
		for (int j = 0; j < k; j++) {
			if (l < n) {
				b[i][j] = a[l];
				l++;
			}
			else b[i][j] = 0;
		}
	}
	PrintMas(b,p,k);
}
