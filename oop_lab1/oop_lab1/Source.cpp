#include <time.h>
#include <iostream>

using namespace std;

int* genRandArray(int size, int maxValue) {
	int* arr = new int[size+1];
	arr[0] = size;
	for (int i = 1; i < size+1; i++) {
		arr[i] = rand() % maxValue;
	}

	return arr;
}
void print(int* arr) {
	int i = 0;
	cout << arr[i] << " : ";
	for (i; i < arr[0]; i++) {
		cout << arr[i+1] << "\t";
	} 
}
int main()
{
	srand(time(NULL));
	int size = rand() % 10;
	int maxValue = 100;
	int* arr = genRandArray(size, maxValue);
	print(arr);
	delete arr;
}