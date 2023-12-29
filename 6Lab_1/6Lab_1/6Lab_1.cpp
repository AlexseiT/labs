#include <iostream>
#include <math.h>

using namespace std;

int ParamArea(double* Param, double* Area, double a, double b, double c) {
	if (a < (b + c) && b < (a + c) && c < (a + b)) {
		*Param = a + b + c;
		*Area = (*Param) / 2;
		*Area = sqrt(*Area * (*Area - a) * (*Area - b) * (*Area - c));
		return 1;
	}
	else return 0;
}

int main() {
	double a, b, c, Param, Area; 
	cin >> a >> b >> c;
	if (ParamArea(&Param, &Area, a, b, c) == 1)
		cout << "Parameter = " << Param << "\n" << "Area = " << Area << "\n";
	else cout << "Error" << "\n";
}