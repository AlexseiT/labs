#include "Header.h"
using namespace std;

void Spiral(LIST<int>* lst, int N, int** A)
{
	int x = 0, y = 0;
	int a = N, b = 0;
	int Line = 0;
	for (int i = 0; i < N * N; ++i)
	{
		(*lst).Input(A[y][x]);;
		a--;
		if (a == 0)
		{
			b++;
			if (b > 3) b = 0;
			if (b == 1 || b == 3) Line++;
			a = N - Line;
		}

		if (b == 0) x++;
		if (b == 1) y++;
		if (b == 2) x--;
		if (b == 3) y--;
	}
}
void Diagonal_1(LIST<int>* lst, int N, int** A)
{
	int I = 0;
	for (int i = 0; i < N; i++) {
		int a = -1;
		int b = N - 2 - i;
		while (b != N - 1) {
			a++;
			b++;
			(*lst).Input(A[a][b]);;
			I++;
		}
	}
	for (int i = 0; i < N; i++) {
		int a = i;
		int b = -1;
		while (a != N - 1) {
			a++;
			b++;
			(*lst).Input(A[a][b]);;
			I++;
		}
	}
}
void Diagonal_2(LIST<int>* lst, int N, int** A)
{
	int I = 0;
	for (int i = 0; i < N; i++) {
		int a = -1;
		int b = i + 1;
		while (b != 0) {
			a++;
			b--;
			(*lst).Input(A[a][b]);;
			I++;
		}
	}

	for (int i = 0; i < N; i++) {
		int a = i;
		int b = N;
		while (a != N - 1) {
			a++;
			b--;
			(*lst).Input(A[a][b]);;
			I++;
		}
	}
}
void Write_List(LIST<int>* lst)
{
	for (int i = 0; i < (*lst).Size(); i++) {
		cout << "  " << (*lst)[i] ;
	}
}

void Rand_Mass(int** A, int N) {
	for (int i = 0; i < N; i++) {
		A[i] = new int[N];
		for (int j = 0; j < N; j++) {
			A[i][j] = rand() % 20;
			std::cout << A[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}
const int kol = 10;
int main()
{
	setlocale(LC_ALL, "ru");
	LIST<int> *lst;
	srand(time(NULL));
	int N;
	std::cin >> N;
	int** A = new int* [N];
	Rand_Mass(A, N);

	std::cout << "-----ЗАДАНИЕ 1-----" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;


	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "a) По правым диагоналям" << std::endl;
	std::cout << std::endl;
	lst = new QUEUE<int>;
	(*lst).Create();
	Diagonal_1(lst, N, A);
	Write_List(lst);

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "a) По левым диагоналям" << std::endl;
	std::cout << std::endl;
	(*lst).Clear();
	Diagonal_2(lst, N, A);
	Write_List(lst);


	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "c) По спирали с верхнего левого элемента" << std::endl;
	std::cout << std::endl;
	(*lst).Clear();
	Spiral(lst, N, A);
	Write_List(lst);

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "d) По спирали с центрального элемента" << std::endl;
	std::cout << std::endl;
	lst = new STACK<int>;
	Spiral(lst, N, A);
	Write_List(lst);

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "-----ЗАДАНИЕ 2-----" << std::endl;

	LIST<int>* lst1[kol];

	for (int i = 0; i < kol; i++) {
		int s = rand() % 10 + 1;
		lst1[i] = new QUEUE<int>;
		(*lst1[i]).Create();
		for (int j = 1; j < s + 1; j++) {
			(*lst1[i]).Input(rand() % 10);
		}
	}
	for (int i = 0; i < kol; i++) {
		std::cout << std::endl;
		Write_List(lst1[i]);
	}
	std::cout << std::endl;
	return 0;
};