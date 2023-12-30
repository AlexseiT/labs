#include <iostream>
#include <string>
using namespace std;

enum Figures {
	Circle, Trinagle, Polygon, Error
};

struct circle {
	float Point;
	float Point1;
	float Number;
};

struct trinagle {
	float Point;
	float Point1;
	float Point2;
	float Point3;
	float Point4;
	float Point5;
};

string word_tolower(string word)
{
	int n = word.length();
	for (int i = 0; i < n; i++) {
		word[i] = tolower(word[i]);
	}
	return word;
}

void Сircle_func(float Number) {
	float perimetr = 2 * 3.14 * Number;
	float area = 3.14 * Number * Number;
	cout << "Perimetr: " << perimetr << endl;
	cout << "area: " << area << endl;
}

void Trinagle_func(float Number) {
	float perimetr = 2 * 3.14 * Number;
	float area = 3.14 * Number * Number;
	cout << "Perimetr: " << perimetr << endl;
	cout << "area: " << area << endl;
}


Figures identify(string figure) {
	string figureName;
	figure = word_tolower(figure);

	figureName = "circle";
	if (figure == figureName) return Circle;

	figureName = "triangle";
	if (figure == figureName) return Trinagle;

	figureName = "polygon";
	if (figure == figureName) return Polygon;

	return Error;
}

int main() {
	string ObjectName;
	string ObjectString;
	circle ObjectCircle;
	trinagle ObjectTrinagle;
	getline(cin, ObjectString);

	if (ObjectString.substr(0, 1) == " ") {
		ObjectString.erase(0, ObjectString.find_first_not_of(" "));
	}
	if (ObjectString.substr(ObjectString.find("(") - 1, 1) == " ") {
		ObjectString = ObjectString.erase(ObjectString.find(" "), ObjectString.find("(") - ObjectString.find(" "));
	}

	ObjectName = ObjectString.substr(0, ObjectString.find("("));

	switch (identify(ObjectName)) {
	case Circle:
		cout << "circle" << endl;
		ObjectString = ObjectString.erase(0, 6);
		ObjectCircle.Point = stof(ObjectString.substr(1, ObjectString.find(" ")));
		ObjectString = ObjectString.erase(0, ObjectString.find(" "));
		ObjectCircle.Point1 = stof(ObjectString.substr(1, ObjectString.find(",") - 1));
		ObjectString = ObjectString.erase(0, ObjectString.find(",") + 1);
		ObjectCircle.Number = stof(ObjectString.substr(1, ObjectString.find(")") - 1));
		cout << "Point = " << ObjectCircle.Point << endl;
		cout << "Point1 = " << ObjectCircle.Point1 << endl;
		cout << "Number = " << ObjectCircle.Number << endl;
		Сircle_func(ObjectCircle.Number);
		break;
	case Trinagle:
		cout << "triangle" << endl;
		ObjectString = ObjectString.erase(0, 8);

		ObjectTrinagle.Point = stof(ObjectString.substr(2, ObjectString.find(" ")));
		ObjectString = ObjectString.erase(0, ObjectString.find(" "));

		cout << ObjectString << endl;

		ObjectTrinagle.Point1 = stof(ObjectString.substr(1, ObjectString.find(",") - 1));
		ObjectString = ObjectString.erase(0, ObjectString.find(",") + 2);

		cout << ObjectString << endl;

		ObjectTrinagle.Point2 = stof(ObjectString.substr(0, ObjectString.find(" ")));
		ObjectString = ObjectString.erase(0, ObjectString.find(" "));

		ObjectTrinagle.Point3 = stof(ObjectString.substr(0, ObjectString.find(",")));
		ObjectString = ObjectString.erase(0, ObjectString.find(","));

		cout << ObjectString << endl;
		cout << "Point  = " << ObjectTrinagle.Point << endl;
		cout << "Point1 = " << ObjectTrinagle.Point1 << endl;
		cout << "Point2 = " << ObjectTrinagle.Point2 << endl;
		cout << "Point3 = " << ObjectTrinagle.Point3 << endl;
		break;
	case Polygon:
		cout << "polygon" << endl;
		break;
	case Error:
		cout << "Error: the figure was not found";
	}
}