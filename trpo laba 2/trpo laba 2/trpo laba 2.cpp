#include <iostream>
#include <string>
using namespace std;

enum Figures {
	CIRCLE, TRIANGLE, POLYGON, ERROR
};

struct circle
{
	int Point;
	int Point1;
	int Number;
};

string word_tolower(string word)
{
	int n = word.length();
	for (int i = 0; i < n; i++) {
		word[i] = tolower(word[i]);
	}
	return word;
}

void find_circle_param(circle circ) {
	float perimetr = 2 * 3.14 * circ.Number;
	float area = 3.14 * circ.Number * circ.Number;

	cout << " Perimetr: " << perimetr << endl;
	cout << " Area: " << area << endl;
}

Figures identify(string figure) {
	string figureName;
	figure = word_tolower(figure);

	figureName = "circle";
	if (figure == figureName) return CIRCLE;

	figureName = "triangle";
	if (figure == figureName) return TRIANGLE;

	figureName = "polygon";
	if (figure == figureName) return POLYGON;

	return ERROR;
}

void parse_circle()
{

}

int main()
{
	string input, figureName;
	circle circ;

	getline(cin, input);

	if (input.substr(0, 1) == " ") {
		input.erase(0, input.find_first_not_of(" "));
	}
	if (input.substr(input.find("(") - 1, 1) == " ") {
		input = input.erase(input.find(" "), input.find("(") - input.find(" "));
	}
	figureName = input.substr(0, input.find("("));


	switch (identify(figureName)) {
	case CIRCLE:
		input = input.erase(0, 6);
		circ.Point = stof(input.substr(1, input.find(" ")));
		input = input.erase(0, input.find(" "));
		circ.Point1 = stof(input.substr(1, input.find(",") - 1));
		input = input.erase(0, input.find(",") + 1);
		circ.Number = stof(input.substr(1, input.find(")") - 1));
		cout << "Point = " << circ.Point << endl;
		cout << "Point1 = " << circ.Point1 << endl;
		cout << "Number = " << circ.Number << endl;
		break;
	case TRIANGLE:
		cout << "triangle" << endl;
		break;
	case POLYGON:
		cout << "polygon" << endl;
		break;
	case ERROR:
		cout << "Error: the figure was not found";
	}
}
