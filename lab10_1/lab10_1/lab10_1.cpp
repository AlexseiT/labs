#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

string consonantsEnglish = "qwrtplkjhgfdszxcvbnmyQWRTPLKJHGFDSZXCVBNMY";

int main()
{
	string str, str2;
	string str_erase;
	string str_sogl, str_glas;
	int N;
	int count;

	cout << "Enter N: ";
	cin >> N;

	ofstream fout("input.txt");

	for (int i = 0; i < N; i++) {
		cin >> str;
		fout << str << endl;
		str.clear();
	}

	ofstream glas("glas.txt");
	ofstream sogl("sogl.txt");
	ifstream file("input.txt");

	while (getline(file, str)) {
		str_erase = str;
		while (str_erase != "") {
			count = str_erase.find(",") + 1;
			if (count == -1) {
				count = str_erase.find(" ");
			}
			str2 = str_erase.substr(0, count);
			if (consonantsEnglish.find(str2.substr(0, 1)) != -1){
				str_sogl += str2;
			}
			else {
				str_glas += str2;
			}
			str_erase.erase(0, count);
		}
	}

	sogl << str_sogl;
	glas << str_glas;

	sogl.close();
	glas.close();
	file.close();
	fout.close();

	system("pause");
	return 0; 
}