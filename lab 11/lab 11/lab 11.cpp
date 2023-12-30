#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <windows.h>
using namespace std;

struct info
{
	string Names;
	string Names2;
	string Names3;
	int b = 0;
	float w = 0;

};

void NewFile(string filename, info* Mass, int kol)
{
	ofstream file;
	file.open(filename);
	for (int i = 0; i < kol; i++)

	{
		cin >> Mass[i].Names2 >>
			Mass[i].Names >>
			Mass[i].Names3 >>
			Mass[i].b >>
			Mass[i].w;

		file << Mass[i].Names2 <<
		" " << Mass[i].Names <<
		" " << Mass[i].Names3 <<
		" " << Mass[i].b <<
		" " << Mass[i].w << endl;

		cout << endl;
	}

}

void Open(string filename, info* Mass, int kol)
{
	ifstream file;
	file.open(filename);
	char bok;
	while (file.get(bok))
	{
		cout << bok;
	}
	cout << endl;

}

void Remove(info* Mass, int kol)
{
	for (int i = 0; i < kol; i++)
	{
		if (Mass[i].b < 10)
		{
			Mass[i].Names2 = "";
			Mass[i].Names = "";
			Mass[i].Names3 = "";
			Mass[i].b = 0;
			Mass[i].w = 0;

		}

	}

}

void NewInf(string filename, info* Mass, int kol)
{

	ofstream file;
	file.open(filename);
	for (int i = 0; i < kol; i++)
	{
		if (Mass[i].b == 0)
		continue;
		file << Mass[i].Names2
		<< " " << Mass[i].Names
		<< " " << Mass[i].Names3
		<< " " << Mass[i].b
		<< " " << Mass[i].w << endl;
		cout << endl;
	}
}

void ReverseW(string filename, info* Mass)
{
	string file, s1, s2;
	ifstream fout(filename.c_str(), std::ios::in);
	if (!fout.good())
	{
		exit(1);
	}
	cout << "Фамилия: " << endl;
	cin >> s2;
	int count_word = 0;
	int count_line = 0;
	while (fout >> s1)
	{
		count_word++;

		if (count_word == 5)
		{
			count_line++;
			count_word = 0;
		}
		if (s1 == s2)
		{
			cout << "Новый вес: " << endl;
			cin >> Mass[count_line].w;
			fout.close();
		}
	}
}

void NewInsert(string filename, info* Mass)
{
	ofstream file(filename, ios::app);
	info Insert;
	cin >> Insert.Names2 >>
		Insert.Names >>
		Insert.Names3 >>
		Insert.b >>
		Insert.w;

	file << endl << Insert.Names2
		 << " " << Insert.Names
		 << " " << Insert.Names3
		 << " " << Insert.b
		 << " " << Insert.w << endl;
	file.close();
	system("CLS");
}

void PressKey(int key, info* Mass, int kol)
{
	string filename = "input.txt";
	switch (key)
	{

	case '1': 
	NewFile(filename, Mass, kol);
	break;

	case '2': 
	Open(filename, Mass, kol);
	break;

	case '3': 
	NewInsert(filename, Mass);
    break;

	case '4': 
	Remove(Mass, kol);
	NewInf(filename, Mass, kol);
	break;

	case '5': 
	ReverseW(filename, Mass); 
	NewInf(filename, Mass, kol);
	break;

	default:
    cout << "Error";

	}
}

int main()

{
	setlocale(LC_ALL, "ru");
	int kol = 0, key;
	cout << "Введите количество запией" << endl;
	cin >> kol;
	info* Mass = new info[kol];
	while (1)
	{
		cout << "1)Новый файл" << endl;
		cout << "2)Открыть файл" << endl;
		cout << "3)Новая запись" << endl;
		cout << "4)Удалить записи /вес < 10кг/" << endl;
		cout << "5)Изменить вес вещей" << endl;
		key = _getch();
		system("CLS");
		PressKey(key,Mass,kol);
	}

}