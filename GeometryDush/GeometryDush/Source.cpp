#include <iostream>
#include <string>
using namespace std;
const double pi = 3.141592653589793238463;
int ind(string Object)
{
	string ObjectName;
	ObjectName = "circle";
	if (_stricmp(Object.c_str(), ObjectName.c_str()) == 0) return 1;
	ObjectName = "triangle";
	if (_stricmp(Object.c_str(), ObjectName.c_str()) == 0) return 2;
	ObjectName = "polygon";
	if (_stricmp(Object.c_str(), ObjectName.c_str()) == 0) return 3;
	return 0;
}
int main()
{
	string Object, ObjectName, s2;
	float Point1, Point2, Number;
	float perimeter, area;
	getline(cin, Object);
	if (Object.substr(Object.find("(") - 1, 1) == " ")
		Object = Object.erase(Object.find(" "), Object.find("(") - Object.find(" "));

	ObjectName = Object.substr(0, Object.find("("));

	switch (ind(ObjectName))
	{
	case (1):
		Object = Object.erase(0, 6);
		Point1 = stof(Object.substr(1, Object.find(" ")));
		Object = Object.erase(0, Object.find(" "));
		Point2 = stof(Object.substr(1, Object.find(",") - 1));
		Object = Object.erase(0, Object.find(",") + 1);
		Number = stof(Object.substr(1, Object.find(")") - 1));
		cout << "Point1 = " << Point1 << endl;
		cout << "Point2 = " << Point2 << endl;
		cout << "Number = " << Number << endl;
		perimeter = 2 * pi * Number;
		cout << "perimeter = " << perimeter << endl;
		area = pi * Number * Number;
		cout << "area = " << area << endl;
		break;
	case (2):
		cout << "triangle" << endl;
		break;
	case (3):
		cout << "polygon" << endl;
		break;
	}
}