#include <iostream>
using namespace std;

long func(int n) {
	if (n == 0) return 1; 
	else {
		cin >> n;
		if (n > 0) cout << n << ' ';
		return func(n);
	}
}
int main()
{
	int n = 1;
	func(n);
	
}
