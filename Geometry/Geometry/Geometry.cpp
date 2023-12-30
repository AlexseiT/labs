#include <iostream>
#include <string>

using namespace std;

const double pi = 3.141592653589793238463;

void ind(string Object) 
{
	string ObjectName;
	ObjectName = "circle";
	if (_stricmp(Object.c_str(), ObjectName.c_str()) == 0) Object = ObjectName;
	ObjectName = "triangle";
	if (_stricmp(Object.c_str(), ObjectName.c_str()) == 0) Object = ObjectName;
	ObjectName = "polygon";
	if (_stricmp(Object.c_str(), ObjectName.c_str()) == 0) Object = ObjectName;
}

int main()
{
	string Object, ObjectName, s2;
	float Point1, Point2, Number, perimeter, area;
	int Count;
	cin >> Count;
	int** a = new int* [Count];
	for (int i = 0; i < 5; i++)
		a[i] = new int[Count];
	getline(cin, Object);

	if (Object.substr(Object.find("(") - 1, 1) == " ") {
		Object = Object.erase(Object.find(" "), Object.find("(") - Object.find(" "));
	}
	while (Object.substr(1,1) == " "){}

	ObjectName = Object.substr(0, Object.find("("));

	ind(ObjectName);

	if (ObjectName == "circle") 
	{            
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
	}
}

