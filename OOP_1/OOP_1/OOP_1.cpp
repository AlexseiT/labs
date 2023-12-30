#include <time.h>
#include <iostream>
using namespace std;
int* genRandArray(int size, int maxValue) {
	int* arr = new int[];
	for (int i = 0; i < size; i++) {
		arr[i] = rand() % 11;
	}
	return arr;
}
void print(int* arr) {
	int i = 0;
	while (arr) {
		cout << arr[i];
		i++;
}
}

int main()
{
	srand(time(NULL));
	int size = rand() % 10;
	int maxValue = 100;
	int* arr = genRandArray(size, maxValue);
	print(arr);
}

