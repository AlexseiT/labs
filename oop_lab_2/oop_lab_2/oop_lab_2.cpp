#include <iostream>
#include <time.h>

void Spiral_1(int* D, int N, int** A)
{
	int x = N / 2;
	int y = N / 2;
	int a = 2, b = 0;
	int Line = N - 1;
	if (N % 2 == 0) b = 1;
	for (int i = 0; i < N * N; ++i)
	{
		D[i] = A[y][x];
		a--;
		std::cout << D[i] << " ";
		if (a == 0)
		{
			b++;

			if (N % 2 == 0)
			{
				if (b == 1 || b == 3) Line--;
			}
			else
			{
				if (b == 2 || b == 4) Line--;
			}

			if (b > 3) b = 0;
			a = N - Line;
		}
		if (b == 0) x++;
		if (b == 1) y--;
		if (b == 2) x--;
		if (b == 3) y++;
	}
}
void Spiral_2(int* D, int N, int** A)
{
	int x = 0, y = 0;
	int a = N, b = 0;
	int Line = 0;
	for (int i = 0; i < N * N; ++i)
	{
		D[i] = A[y][x];
		a--;
		std::cout << D[i] << " ";
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
void Diagonal_1(int* D, int N, int** A)
{
	int I = 0;
	for (int i = 0; i < N; i++) {
		int a = -1;
		int b = N - 2 - i;
		std::cout << std::endl;
		while (b != N - 1) {
			a++;
			b++;
			D[I] = A[a][b];
			std::cout << D[I] << "\t";
			I++;
		}
	}
	for (int i = 0; i < N; i++) {
		int a = i;
		int b = -1;
		std::cout << std::endl;
		while (a != N - 1) {
			a++;
			b++;
			D[I] = A[a][b];
			std::cout << D[I] << "\t";
			I++;
		}
	}
}
void Diagonal_2(int* D, int N, int** A)
{
	int I = 0;
	for (int i = 0; i < N; i++) {
		int a = -1;
		int b = i + 1;
		std::cout << std::endl;
		while (b != 0) {
			a++;
			b--;
			D[I] = A[a][b];
			std::cout << D[I] << "\t";
			I++;
		}
	}

	for (int i = 0; i < N; i++) {
		int a = i;
		int b = N;
		std::cout << std::endl;
		while (a != N - 1) {
			a++;
			b--;
			D[I] = A[a][b];
			std::cout << D[I] << "\t";
			I++;
		}
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

int main()
{
	srand(time(NULL));
	int N;
	std::cin >> N;
	int* D = new int[N * N];
	int** A = new int* [N];
	Rand_Mass(A, N);

	// 1 часть
	std::cout << std::endl;
	std::cout << "a)" << std::endl;
	std::cout << std::endl;
	Diagonal_1(D, N, A);

	// 2 часть
	std::cout << std::endl;
	std::cout << "b)" << std::endl;
	std::cout << std::endl;
	Diagonal_2(D, N, A);

	// 3 часть
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "c)" << std::endl;
	std::cout << std::endl;
	Spiral_1(D, N, A);

	// 4 часть
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "d)" << std::endl;
	std::cout << std::endl;
	Spiral_2(D, N, A);
	std::cout << std::endl;
}


