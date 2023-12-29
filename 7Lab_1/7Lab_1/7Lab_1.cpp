#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;

int i;

void BubbleSort(int* a, int n)
{
	int k;
	for (i = 0; i <= n - 1; i++) {
		for (int j = n; j >= i + 1; j--) {
			if (a[j] > a[j - 1]) {
				k = a[j];
				a[j] = a[j - 1];
				a[j - 1] = k;
			}
		}
	}
}

int BinarySearch(int* a, int x, int n)
{
	int k;
	int L = 0, R = n, m;
	while (L <= R)
	{
		m = L + (R - L) / 2;
		if (x > a[m]) R = m - 1;
		else if (x < a[m]) {
			L = m + 1;
			k += 1;
		}
		else return k;
	}
	return 0;
}

int enumer(int* a, int n, int x) {
	for (i = 0; i < n; ++i) {
		if (a[i] == x) break;
	}
	return i;
}

int main() {
	srand(time(NULL));
	int a[100];
	int b[1000];
	int x;
	for (i = 0; i < 100; ++i) a[i] = rand() % 100;
	for (i = 0; i < 1000; ++i) b[i] = rand() % 100;
	cout << "What element you want to find?" << endl;
	cin >> x;
	BubbleSort(a, 100);
	BubbleSort(b, 1000);

	cout << "BinarySearch 100 = " << BinarySearch(a, x, 100) << "\n";
	cout << "EnumSearch 100 = " << enumer(a, 100, x) << "\n";
	cout << "BinarySearch 1000 = " << BinarySearch(b, x, 1000) << "\n";
	cout << "EnumSearch 1000 = " << enumer(b, 1000, x) << "\n";
	system("pause");
}
