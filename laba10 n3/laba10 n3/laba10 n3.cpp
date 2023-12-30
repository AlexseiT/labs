#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <map>

using namespace std;

string func(string A) {
	if (A.find(',') != -1) A.erase(0, A.find(',') + 1);
	else A.clear();
	return(A);
}

int main()
{
	string A, text;
	multimap<string, int> n;
	cin >> A;
	text = A;

	while (text[0] != '\0') {
		n.insert(make_pair(text.substr(0, text.find(',')), 0));
		text = func(text);
	}
	cout << endl;
	for (auto& m : n) cout << m.first << endl;

}

