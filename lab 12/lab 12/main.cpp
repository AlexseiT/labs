#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdlib.h.>
#include "func.h"

using namespace std;

void FillRand(double a[], int n)
{
	for (int i = 0; i < n; i++)
		a[i] = rand() % n;
}

void FillRand_double(double a[], int n)
{
	for (int i = 0; i < n; i++)
		a[i] = (double)rand() * n / RAND_MAX + n;
}


int timer(int tip, double* a, int n) {
	unsigned int start_time = clock();
	switch (tip) {
	case 0:
		SelectSort(a,  n);
		break;
	case 1:
		InsertSort(a, n);
		break;
	case 3:
		HeapSort(a, n);
		break;
	case 4:
		QuickSort(a, 0, n-1);
		break;
	default:
		return 0;
		break;
	}
	unsigned int end_time = clock();
	return end_time - start_time;
}

int main() {

	setlocale(LC_ALL, "Rus");
	int time;
	int tip_sort;
	int n, i;

	cout << "Введите длину массива:" << endl;
	cin >> n;

	double *a = new double [n];

	cout << "Заполнение массива:" << endl;
	cout << "0 - Целыми" << endl;
	cout << "1 - Вещественными" << endl;
	cin >> i;
	switch (i) {
	case 0:
		FillRand(a, n);
		break;
	case 1:
		FillRand_double(a, n);
		break;
	default:
		system("pause");
	break;
	}

	cout << "Введите тип сортировки" << endl;

	cout << "0 - SelectSort " << endl;
	cout << "1 - InsertSort " << endl;
	cout << "2 - HeapSort " << endl;
	cout << "3 - QuickSort " << endl;

	cin >> tip_sort;

	time = timer(tip_sort, a, n);

	cout << "Время сортировки = " << time << " милисекунд";
}