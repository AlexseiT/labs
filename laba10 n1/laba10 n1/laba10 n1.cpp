#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

string func(string A) {
	if (A.find(',') != -1) A.erase(0, A.find(',') + 1);
	else A.clear();
	return(A);
}

int main()
{
	string A, text, pri;
	int i;
	cin >> A;
	cin >> pri;
	text = A;
	cout << endl;
	while (text[0] != '\0') {
		i = text.find(pri);
		if (i != 0) {
			text = func(text);
		}
		cout << text.substr(0, text.find(',')) << endl;
		text = func(text);
	}
}

