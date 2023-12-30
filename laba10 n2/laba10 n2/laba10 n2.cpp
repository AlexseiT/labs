#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <map>

using namespace std;

pair <string, int> func(string A) {
	int k = 0;
	string B = A.substr(0, A.find(','));
	if (A.find(',') != -1)
		while (A.find(B) != -1 && A.find(',') != -1)
		{
			k++;
			A.erase(A.find(B), A.find(',') + 1);
		}
	else
	{
		A.clear();
		k++;
	}
	return pair <string, int>(A, k);
}

int main()
{
	string A, B , text;
	pair <string, int> n;
	map <string, int> k;
	cin >> A;
	text = A;

	while (text[0] != '\0') 
	{
		if (A.find(',') != -1)
		{
			B = text.substr(0, text.find(','));
		}
		else B = text;
		n = func(text);
		text = n.first;
		k[B] += n.second;
	}
	cout << endl;
	for (auto& m : k)
		cout << m.first << " " << m.second << endl;
}

