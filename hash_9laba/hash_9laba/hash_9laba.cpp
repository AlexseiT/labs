#include <iostream>
#include <time.h>
#include <cmath>
#include <string.h>
using namespace std;
struct tabl {
	int hash[7];
	int symbol[7];
	int collision1[7];
	int collision2[7];
};
template<typename T>
class List
{
public:
	List();
	~List();
	void push_back(T data);
	T& operator[](const int index);
private:
	template<typename T>
	class node
	{
	public:
		node* pNext;
		T data;
		node(T data = T(), node* pNext = NULL)
		{
			this->data = data;
			this->pNext = pNext;
		}
	};
	node<T>* head;
};
template<typename T>
List<T>::List()
{
	head = NULL;
}
template<typename T>
List<T>::~List()
{
}
template<typename T>
void List<T>::push_back(T data)
{
	if (head == NULL)
	{
		head = new node<T>(data);
	}
	else
	{
		node<T>* current = this->head;
		while (current->pNext != NULL)
		{
			current = current->pNext;
		}
		current->pNext = new node<T>(data);
	}
}
template<typename T>
T& List<T>::operator[](const int index)
{
	int counter = 0;

	node<T>* current = this->head;

	while (current != nullptr)
	{
		if (counter == index)
		{
			return current->data;
		}
		current = current->pNext;
		counter++;
	}
}
void Hash(int* A, int N, List<int>* lst, int* B, int m) {
	int k;
	int s;
	for (int i = 0; i < N; i++) {
		k = A[i] % m;
		s = 0;
		for (int j = 0; j < B[k]; j++) {
			if (A[i] == lst[k][j]) s++;
		}
		if (s == 0) lst[k].push_back(A[i]), B[k]++;
	}
}
void print_lst(List<int>* lst, int* B, int m) {
	for (int i = 0; i < m; i++) {
		cout << i << " : ";
		for (int j = 0; j < B[i]; j++) {
			cout << lst[i][j] << " ";
		}
		cout << endl;
	}
}
string search(List<int>* lst, int C, int* B, int m) {
	int k = C % m;
	for (int i = 0; i < B[k]; i++) {
		if (lst[k][i] == C) {
		cout << endl;
		return "элемент найден";
		} 
	}
	cout << endl;
	return "элемент не найден";
}
int coll = 0;
int mod(char k, int m)
{
	int rez = (k - 'a') % m;
	return rez;
}
int Hash_line(char T[], char K, int m)
{
	int i;
	i = mod(K,m);
	while (i < m) {
		if (T[i] == '0') {
			T[i] = K;
			return i;
		}
		if (i + 1 == m) {
			i = 0;
		}
		i++;
		coll++;
	}
}
void Hash_square(char T[], char K, int m)
{
	int h = mod(K,m);
	int d = 1;
	while (true) {
		if (T[h] == '0') {
			T[h] = K;
			break;
		}
		coll++;
		if (d >= m) {
			break;
		}
		h = h + d;
		if (h >= m) {
			h = h - m;
		}
		d = d + 2;
	}
}
int main()
{
	tabl tabl;
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");
	char Alf[] = "qwertyuiopasdfghjklzxcvbnm";
	int C;
	int N;
	int kol;
	int size;
	// 1 часть
	cout << "1 часть" << endl;
	cout << endl;
	cout << "Длина хеш таблицы: ";
	cin >> size;
	List<int>* lst = new List<int> [size];
	cout << endl;
	cout << "Количество элементов: ";
	cin >> N;
	int* B = new int [size];
	for (int i = 0; i < size; i++) {
		B[i] = 0;
	}
	int* A = new int[N];
	for (int i = 0; i < N; i++) {
		A[i] = rand() % 30;
		cout << A[i] << " ";
	}
	cout << endl;
	Hash(A, N, lst, B, size);
	print_lst(lst, B, size);
	cout << endl;
	cout << "элемент: ";
	cin >> C;
	cout << search(lst,C,B, size);
	cout << endl;
	cout << "2 часть" <<endl;

	// 2 часть Линейное решение коллизии
	for (int k = 0; k < 7; k++) {
		cout << "------Линейное решение коллизии------" << endl;

		coll = 0;
		cout << endl;

		cout << "Длина хеш таблицы: " << endl;
		cin >> size;

		cout << "Колличество символов: " << endl;
		cin >> kol;

		char* s = new char[kol];

		for (int i = 0; i < kol; i++) {
			int j = rand() % 26;
			s[i] = Alf[j];
			cout << s[i] << " ";
		}

		cout << endl;

		char* T = new char[size];

		for (int i = 0; i < size; i++) {
			T[i] = '0';
		}

		for (int i = 0; i < kol; i++) {
			if (i < size)Hash_line(T, s[i], size);
			else { 
				cout << "переполнение" << endl;
				break;
			}
		}
		for (int i = 0; i < size; i++) {
			cout << i << "\t";
		}

		cout << endl;

		for (int i = 0; i < size; i++) {
			cout << T[i] << "\t";
		}

		cout << endl;
		cout << "Коллизий = " << coll;

		tabl.collision1[k] = coll;

		cout << endl;
		cout << endl;

		cout << "------Квадратичное решение коллизии------" << endl;
		// 2 часть Квадратичное решение коллизии
		coll = 0;
		cout << endl;
		for (int i = 0; i < kol; i++) {
			int j = rand() % 26;
			s[i] = Alf[j];
			cout << s[i] << " ";
		}
		cout << endl;
	
		for (int i = 0; i < size; i++) {
			T[i] = '0';
		}
		for (int i = 0; i < kol; i++) {
			if (i < size)Hash_square(T, s[i], size);
			else {
				cout << "переполнение" << endl;
				break;
			}
		}
		for (int i = 0; i < size; i++) {
			cout << i << "\t";
		}
		cout << endl;
		for (int i = 0; i < size; i++) {
			cout << T[i] << "\t";
		}
		cout << endl;

		cout << "Коллизий = " << coll;
		tabl.collision2[k] = coll;
		cout << endl;
		tabl.hash[k] = size;
		tabl.symbol[k] = kol;
	}
	// Общая таблица

	cout << endl;
	cout << "----------Таблица----------" << endl;
	cout << "Размер хеш таблицы\t" << "Количество исходных символов\t"<<"Коллизии в линейных пробах\t" <<"Коллизии в квадратичных пробах\t" << endl;

	for (int i = 0; i < 7; i++) {
		cout << "\t" << tabl.hash[i]<< "\t\t\t\t" << tabl.symbol[i] << "\t\t\t\t" << tabl.collision1[i] << "\t\t\t\t" << tabl.collision2[i] << endl;
	}
	//return 0;
}