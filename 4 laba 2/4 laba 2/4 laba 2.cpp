#include <iostream>
#include <time.h>

using namespace std;

int stroke(int** arr, int i, int n) {
	int j, sum = 0;
	for (j = 0; j < n; j++)
		sum += arr[i][j];
	return sum;
}

int stolb(int** arr, int i, int m) {
	int j, sum = 0;
	for (j = 0; j < m; j++)
		sum += arr[j][i];
	return sum;
}

int main() {
	int** arr, ** darr, i, j, n, m;
	srand(time(NULL));
	cout << "m:";
	cin >> m;
	cout << "n:";
	cin >> n;
	arr = new int* [m];
	for (i = 0; i < m; i++)
		arr[i] = new int[n];
	printf("Array A:\n");
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			arr[i][j] = rand() % 11;
			printf("%4d", arr[i][j]);
		}
		puts("\n");
	}

	puts("\n");
	darr = new int* [m + 1];
	for (i = 0; i < m + 1; i++)
		darr[i] = new int[n + 1];
	printf("Array D:\n");
	for (i = 0; i < m + 1; i++) {
		for (j = 0; j < n + 1; j++) {
			if (i < m && j < n) {
				darr[i][j] = arr[i][j];
				printf("%4d", darr[i][j]);
			}
			else {
				if (i < m && j == n) {
					darr[i][j] = stroke(arr, i, n);
					printf("%4d\n", darr[i][j]);
				}
				else {
					if (i == m && j < n) {
						darr[i][j] = stolb(arr, j, m);
						printf("%4d", darr[i][j]);
					}
				}
			}
		}
		if (i == m && j == n + 1) {
			darr[m][n] = stolb(darr, n, m);
			printf("%4d", darr[m][n]);
		}
		puts("\n");
	}
	for (i = 0; i < m; i++)
		delete arr[i];
	delete arr;
	for (i = 0; i < m + 1; i++)
		delete darr[i];
	delete darr;
}
