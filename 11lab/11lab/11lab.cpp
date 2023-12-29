#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

struct Info
{
	char* FIO[100];
	int bag;
	float weight;
} t1 ;

void input(Info t1) {
	int i = 1;
	ofstream file("log.txt", ios::binary);
	while (i != 0) {
		cout << "F.I.O: ";
		scanf_s("%s",&t1.FIO);
		cout << "baggage: ";
		scanf_s("%s", &t1.bag);
		cout << "weight: ";
		scanf_s("%s", &t1.weight);

		file.write((char*)&t1.FIO, sizeof(t1.FIO));
	

		cout << "Continue recording yes = 1, no = 0:" << endl;
		cin >> i;
	}
}
int main()
{
	Info str;
	input(str);
}