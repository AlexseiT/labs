#include <iostream>
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>

struct Data
{
	char full_name[30];
	unsigned short int department_number;
	char post[22];
	char date[10];
	Data* next;
};
struct Data_1
{
	char full_name[30];
	unsigned short int department_number;
	char post[22];
	char date[10];
};

Data* Fill_base(Data* Head) {
	Data* p, * pred, * h;
	h = pred = new Data;
	Data_1 base[4000];
	FILE* fp;
	fp = fopen("testBase3.dat", "rb");
	int i;
	i = fread((Data_1*)base, sizeof(Data_1), 4000, fp);
	for (int j = 0; j < 4000; ++j) {
		p = new Data;
		memcpy(p->full_name, base[j].full_name, 30);
		p->department_number = base[j].department_number;
		memcpy(p->post, base[j].post, 22);
		memcpy(p->date, base[j].date, 10);
		pred->next = p;
		pred = p;
	}
	p->next = NULL;
	return h;
}

void clear(Data* head) {
	Data* p, * q;
	q = p = head;
	while (p != NULL) {
		p = q->next;
		delete q;
		q = p;
	}
	head = NULL;
}

void show(Data* head, int current, bool direction) {
	Data* p = new Data;
	p = head;
	if (direction) {
		for (int i = 0; i < current; ++i) {
			p = p->next;
		}
		for (int j = current; j < current + 20; ++j) {
			std::cout << p->full_name << std::endl;
			std::cout << p->department_number << std::endl << p->post << std::endl << p->date << std::endl;
			p = p->next;
		}
		std::cout << std::endl;
	}
	else {
		for (int i = 0; i < current; ++i) {
			p = p->next;
		}
		for (int j = current; j < current + 20; ++j) {
			std::cout << p->full_name << std::endl;
			std::cout << p->department_number << std::endl << p->post << std::endl << p->date << std::endl;
			p = p->next;
		}
	}
}

void data_print(Data* tt, int i)
{
	std::cout << tt[i].full_name << std::endl << tt[i].department_number << std::endl << tt[i].post << std::endl << tt[i].date << std::endl << std::endl;
}

void case_func(int page, int j, int i, Data* tt)
{
	j = 20 * page;
	i = 20 * (page - 1);
	system("cls");
	for (i; i < j; i++) data_print(tt, i);
}

int main()
{
	int page = 0;
	int var;
	bool exit = 0;
	FILE* file;
	file = fopen("testBase2.dat", "rb");
	Data* p = new Data;  
	Data* Head = new Data;
	Head = Fill_base(Head);
	Head = Head->next;
	int i = 0, j = 0;

	while (1) {
		exit = 0;
		std::cout << "1) Data base" << std::endl;
		std::cout << "2) Exit" << std::endl;
		std::cin >> var;
		system("cls");
		switch (var) {
		case 1: {
			page = 1;
			show(Head, 0, 1);
			break;
		}
		case 2: return 0;
		}
		while (!exit) {
			std::cout << "1) --->" << std::endl;
			std::cout << "2) <---" << std::endl;
			std::cout << "3) Menu" << std::endl;
			std::cin >> var;

			switch (var) {
			case 1: {
				if (page < 4000) {
					i = 20 * page;
					page += 1;
					system("cls");
					show(Head, i, 1);
					break;
				}
			}
			case 2: {
				if (page > 1) {
					page -= 1;
					i = 20 * page;
					system("cls");
					show(Head, i, 0);
				}
				break;
			}
			case 3: {
				system("cls");
				exit = 1;
				break;
			}
			}
		}
	}
	clear(Head);
	return 0;
}
