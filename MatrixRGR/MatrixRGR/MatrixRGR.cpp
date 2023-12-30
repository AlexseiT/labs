#include <iostream>  
#include <vector>
#include <algorithm>  
using namespace std;

int counter = 0;

void Print(vector <vector<int>> matrix)
{
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[0].size(); j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
vector <vector<int>> Duplicate(vector <vector<int>> matrix, vector <vector<int>> resultmatrix)
{
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[0].size(); j++)
		{
			resultmatrix[i][j] = matrix[i][j];
		}
	}
	return resultmatrix;
}
vector <vector<int>> ExpandColumn(vector <vector<int>> matrix, int number)
{
	while ((number & (number - 1)) != 0)
	{
		number++;
	}
	vector <vector<int>> resultmatrix(matrix.size(), vector <int>(number));

	resultmatrix = Duplicate(matrix, resultmatrix);

	return resultmatrix;
}
vector <vector<int>> ExpandRow(vector <vector<int>> matrix, int number)
{
	while ((number & (number - 1)) != 0)
	{
		number++;
	}
	vector <vector<int>> resultmatrix(number, vector <int>(matrix[0].size()));

	resultmatrix = Duplicate(matrix, resultmatrix);

	return resultmatrix;
}
vector <vector<int>> TranslateMatrix(vector <vector<int>> matrix, int row, int column)
{
	return ExpandColumn(ExpandRow(matrix, row), column);
}
vector <vector<int>> Separate(vector <vector<int>> matrix, int row, int column)
{
	int number = matrix.size() / 2;
	vector <vector<int>> resultmatrix(number, vector <int>(number));

	for (int i = row; i < row + number; i++)
	{
		for (int j = column; j < column + number; j++)
		{
			resultmatrix[i - row][j - column] = matrix[i][j];
		}
	}

	return resultmatrix;
}
vector <vector<int>> Sum(vector <vector<int>> matrix1, vector <vector<int>> matrix2, int sign)
{
	vector <vector<int>> resultmatrix(matrix1.size(), vector <int>(matrix1.size()));

	for (int i = 0; i < resultmatrix.size(); i++)
	{
		for (int j = 0; j < resultmatrix.size(); j++)
		{
			if (matrix1[i][j] == 0 && matrix2[i][j] == 0) break;
			else if (matrix1[i][j] == 0) resultmatrix[i][j] = sign * matrix2[i][j];
			else if (matrix2[i][j] == 0) resultmatrix[i][j] = matrix1[i][j];
			else
			{
				resultmatrix[i][j] = matrix1[i][j] + sign * matrix2[i][j];
				counter++;
			}
		}
	}

	return resultmatrix;
}
vector <vector<int>> UniteSection(vector <vector<int>> resultmatrix_C, vector <vector<int>> section_C, int row, int column)
{
	int number = resultmatrix_C.size() / 2;

	for (int i = row; i < row + number; i++)
	{
		for (int j = column; j < column + number; j++)
		{
			resultmatrix_C[i][j] = section_C[i - row][j - column];
		}
	}
	return resultmatrix_C;
}
vector <vector<int>> SectionMultiply(vector <vector<int>> matrix1, vector <vector<int>> matrix2)
{
	vector <vector<int>> resultmatrix =
	{
		{matrix1[0][0] * matrix2[0][0] + matrix1[0][1] * matrix2[1][0], matrix1[0][0] * matrix2[0][1] + matrix1[0][1] * matrix2[1][1]},
		{matrix1[1][0] * matrix2[0][0] + matrix1[1][1] * matrix2[1][0], matrix1[1][0] * matrix2[0][1] + matrix1[1][1] * matrix2[1][1]}
	};
	counter++;
	return resultmatrix;
}
bool CheckZero(vector <vector<int>> matrix)
{	
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[0].size(); j++)
		{
			if (matrix[i][j] != 0) return false;
		}
	}
	return true;
};
vector <vector<int>> Multiply(vector <vector<int>> matrix1, vector <vector<int>> matrix2)
{
	int row = max(matrix1.size(), matrix2.size());
	int column = max(matrix1[0].size(), matrix2[0].size());
	//cout << "1" << endl;
	//Print(matrix1);
	//cout << "2" << endl;
	//Print(matrix2);
	if (row <= 2 && row == column)
	{
		return SectionMultiply(matrix1,matrix2);
	};

	// Приведение матриц

	matrix1 = TranslateMatrix(matrix1, row, column);
	matrix2 = TranslateMatrix(matrix2, row, column);
	int number = matrix1.size();
	vector <vector<int>> resultmatrix_С(number, vector <int>(number));

	// Разделение матриц

	vector <vector<int>> matrix1_A1 = Separate(matrix1, 0, 0);
	vector <vector<int>> matrix1_A2 = Separate(matrix1, 0, number/2);
	vector <vector<int>> matrix1_A3 = Separate(matrix1, number/2, 0);
	vector <vector<int>> matrix1_A4 = Separate(matrix1, number/2, number/2);
	vector <vector<int>> matrix2_B1 = Separate(matrix2, 0, 0);
	vector <vector<int>> matrix2_B2 = Separate(matrix2, 0, number/2);
	vector <vector<int>> matrix2_B3 = Separate(matrix2, number/2, 0);
	vector <vector<int>> matrix2_B4 = Separate(matrix2, number/2, number/2);

	// Формулы Штрассена

	//M1
	vector <vector<int>> matrix_M1;
	vector <vector<int>> part1_M1 = Sum(matrix1_A2, matrix1_A4, -1);
	vector <vector<int>> part2_M1 = Sum(matrix2_B3, matrix2_B4, 1);
	if (CheckZero(part1_M1))
		matrix_M1 = part1_M1;
	else if (CheckZero(part2_M1))
		matrix_M1 = part2_M1;
	else
		matrix_M1 = Multiply(part1_M1, part2_M1);
		//Print(matrix_M1);
	//M2
	vector <vector<int>> matrix_M2;
	vector <vector<int>> part1_M2 = Sum(matrix1_A1, matrix1_A4, 1);
	vector <vector<int>> part2_M2 = Sum(matrix2_B1, matrix2_B4, 1);
	if (CheckZero(part1_M2))
		matrix_M2 = part1_M2;
	else if (CheckZero(part2_M2))
		matrix_M2 = part2_M2;
	else
		matrix_M2 = Multiply(part1_M2, part2_M2);

	//M3
	vector <vector<int>> matrix_M3;
	vector <vector<int>> part1_M3 = Sum(matrix1_A1, matrix1_A3, -1);
	vector <vector<int>> part2_M3 = Sum(matrix2_B1, matrix2_B2, 1);
	if (CheckZero(part1_M3))
		matrix_M3 = part1_M3;
	else if (CheckZero(part2_M3))
		matrix_M3 = part2_M3;
	else
		matrix_M3 = Multiply(part1_M3, part2_M3);

	//M4
	vector <vector<int>> matrix_M4;
	vector <vector<int>> part1_M4 = Sum(matrix1_A1, matrix1_A2, 1);
	vector <vector<int>> part2_M4 = matrix2_B4;
	if (CheckZero(part1_M4))
		matrix_M4 = part1_M4;
	else if (CheckZero(part2_M4))
		matrix_M4 = part2_M4;
	else
		matrix_M4 = Multiply(part1_M4, part2_M4);

	//M5
	vector <vector<int>> matrix_M5;
	vector <vector<int>> part1_M5 = matrix1_A1;
	vector <vector<int>> part2_M5 = Sum(matrix2_B2, matrix2_B4, -1);
	if (CheckZero(part1_M5))
		matrix_M5 = part1_M5;
	else if (CheckZero(part2_M5))
		matrix_M5 = part2_M5;
	else
		matrix_M5 = Multiply(part1_M5, part2_M5);

	//M6
	vector <vector<int>> matrix_M6;
	vector <vector<int>> part1_M6 = matrix1_A4;
	vector <vector<int>> part2_M6 = Sum(matrix2_B3, matrix2_B1, -1);
	if (CheckZero(part1_M6))
		matrix_M6 = part1_M6;
	else if (CheckZero(part2_M6))
		matrix_M6 = part2_M6;
	else
		matrix_M6 = Multiply(part1_M6, part2_M6);

	//M7
	vector <vector<int>> matrix_M7;
	vector <vector<int>> part1_M7 = Sum(matrix1_A3, matrix1_A4, 1);
	vector <vector<int>> part2_M7 = matrix2_B1;
	if (CheckZero(part1_M7))
		matrix_M7 = part1_M7;
	else if (CheckZero(part2_M7))
		matrix_M7 = part2_M7;
	else
		matrix_M7 = Multiply(part1_M7, part2_M7);

	vector <vector<int>> resultmatrix_С1 = Sum(Sum(matrix_M1, matrix_M2, 1), Sum(matrix_M4, matrix_M6, 1), -1);
	vector <vector<int>> resultmatrix_С2 = Sum(matrix_M4, matrix_M5, 1);
	vector <vector<int>> resultmatrix_С3 = Sum(matrix_M6, matrix_M7, 1);
	vector <vector<int>> resultmatrix_С4 = Sum(Sum(matrix_M2, matrix_M3, -1), Sum(matrix_M5, matrix_M7, -1), 1);

	resultmatrix_С = UniteSection(resultmatrix_С, resultmatrix_С1, 0, 0);
	resultmatrix_С = UniteSection(resultmatrix_С, resultmatrix_С2, 0, number / 2);
	resultmatrix_С = UniteSection(resultmatrix_С, resultmatrix_С3, number / 2, 0);
	resultmatrix_С = UniteSection(resultmatrix_С, resultmatrix_С4, number / 2, number / 2);

	return resultmatrix_С;
}
vector <vector<int>> MatrixMultiply(vector <vector<int>> matrix1, vector <vector<int>> matrix2)
{
	vector <vector<int>> resultmatrix(matrix1.size(), vector <int>(matrix2[0].size()));
	vector <vector<int>> resultmultiply = Multiply(matrix1, matrix2);

	for (int i = 0; i < resultmatrix.size(); i++)
	{
		for (int j = 0; j < resultmatrix[0].size(); j++)
		{
			resultmatrix[i][j] = resultmultiply[i][j];
		}
	}
	return resultmatrix;
}
void Print()
{
	vector <vector<int>> matrix1(100, vector <int>(100));
	vector <vector<int>> matrix2(100, vector <int>(100));
	counter = 0;
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			matrix1[i][j] = j;
			matrix2[i][j] = j;
		}
	}
	vector <vector<int>> resultmatrix = MatrixMultiply(matrix1, matrix2);
}
int main()
{
	
	vector <vector<int>> matrix1 
	{ 
		{ 1, 2, 3, 4 ,5, 6, 7, 8},
		{ 1, 2, 3, 4 ,5, 6, 7, 8},
		{ 1, 2, 3, 4 ,5, 6, 7, 8},
		{ 1, 2, 3, 4 ,5, 6, 7, 8},
		{ 1, 2, 3, 4 ,5, 6, 7, 8},
		{ 1, 2, 3, 4 ,5, 6, 7, 8},
		{ 1, 2, 3, 4 ,5, 6, 7, 8},
		{ 1, 2, 3, 4 ,5, 6, 7, 8},
	};
	vector <vector<int>> matrix2 
	{ 
		{ 1, 2, 3, 4 ,5, 6, 7, 8},
		{ 1, 2, 3, 4 ,5, 6, 7, 8},
		{ 1, 2, 3, 4 ,5, 6, 7, 8},
		{ 1, 2, 3, 4 ,5, 6, 7, 8},
		{ 1, 2, 3, 4 ,5, 6, 7, 8},
		{ 1, 2, 3, 4 ,5, 6, 7, 8},
		{ 1, 2, 3, 4 ,5, 6, 7, 8},
		{ 1, 2, 3, 4 ,5, 6, 7, 8},
	};
	
	/*
	vector <vector<int>> matrix2(100, vector <int>(100));
    vector <vector<int>> matrix1(100, vector <int>(100));
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			matrix1[i][j] = pow(-1,j) * (i + j);
			matrix2[i][j] = i - j;
		}
	}
	*/
	vector <vector<int>> resultmatrix = MatrixMultiply(matrix1, matrix2);
	
	Print(matrix2);
	Print(matrix1);

	cout << "Result" << endl;

	Print(resultmatrix);
	//Print();
	cout << endl;
	cout << "Fast = " << counter << endl;
	cout << "Default = " << matrix1.size() * matrix1[0].size() * matrix2.size() << endl;
}

