#include <iostream>
#include <math.h>

using namespace std;

double step(double x, long n) {
	double y = 1;
	while (n) {
		if (n % 2 == 0) {
			n /= 2;
			x *= x;
		}
		else {
			n--;
			y *= x;
		}
	}
	return y;
}

int combo(int n, int m) { 
	return m == 0 || n == m ? 1 : combo(n - 1, m) + combo(n - 1, m - 1);
}

void Potent(double& pd, double& pm, int n, int m) {
	if (n >= m) {
		double p = 0.45, q = 0.55;
		int Cn;
		cout << "Control input: \nn = " << n << "\nm = " << m << "\n";
		Cn = combo(n, m);
		printf("Cn = %u \n", Cn);
		pd = Cn * step(p, m) * step(q, n - m);
		pm = Cn * step(q, m) * step(p, n - m);
		printf("pd = %f\npm = %f \n", pd, pm);
	}
}

int main() {
	int n, m;
	double pd, pm;
	cin >> n >> m;
	Potent(pd, pm, n, m);
	system("pause");
}