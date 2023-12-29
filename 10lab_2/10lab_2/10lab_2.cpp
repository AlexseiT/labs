#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

int main()
{
	string str, str2;
	string str_erase;
	int N;

	cout << "Enter N: ";
	cin >> N;

	ofstream fout("input.txt");

	for (int i = 0; i < N; i++) {
		cin >> str;
		fout << str << endl;
		str.clear();
	}

	ifstream file("input.txt");
	ofstream file2("input2.txt");

	while (getline(file, str)) {
		str_erase = str;
		while (str_erase != "") {
			str2 += str_erase.substr(str_erase.size() - 1);
			str_erase.erase(str_erase.size() - 1);
		}
		file2 << str2 << endl;
		str2.clear();
	}

	file2.close();
	fout.close();
	system("pause");
	return 0;

}