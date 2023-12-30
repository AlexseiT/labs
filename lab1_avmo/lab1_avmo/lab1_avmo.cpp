#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
class Combination
{
public: 
    int index;
    int counter;
    bool check = false;
    bool operator<(const Combination& x) const
    {
        return counter < x.counter;
    }
};
class Fraction
{
public:
    long long numerator;
    long long denominator;
    Fraction()
    {
        this->numerator = 0;
        this->denominator = 1;
    }
    Fraction(long long numerator, long long denominator)
    {
        this->numerator = numerator;
        this->denominator = denominator;
    }
    double GetFraction()
    {
        return numerator / denominator;
    }
    long long FindDivider()
    {
        long long number1 = abs(numerator);
        long long number2 = abs(denominator);
        long long temp;
        if (number1 < number2) 
        { 
            temp = number1;
            number1 = number2; 
            number2 = temp;
        }
        while (number2 != 0) {
            temp = number2;
            number2 = number1 % number2;
            number1 = temp;
        }
        return number1;
    }
    void Divide() 
    {
        long long divider = FindDivider();
        if (divider != 0)
        {
            numerator = numerator / divider;
            denominator = denominator / divider;
            if (denominator < 0)
            {
                denominator *= -1;
                numerator /= -1;
            }
        }
    }
};
bool Compare(Fraction &number1, Fraction &number2)
{
    if (abs(number1.numerator * number2.denominator) > abs(number2.numerator * number1.denominator))
        return true;
    else return false;
}
void Print(vector <vector<Fraction>> &matrix, int indexi = -1, int indexj = -1)
{
    cout << endl;
    for (int i = 0; i < matrix.size(); ++i)
    {
        cout << "| ";
        for (int j = 0; j < matrix[0].size(); j++)
        {
            if (j == matrix[0].size() - 1) cout << "|\t";

            if (i == indexi && j == indexj) cout << "\033[38;2;256;0;0m\033[48;2;50;50;50m";

            cout << matrix[i][j].numerator;
            if (matrix[i][j].denominator != 1) cout << "/" << matrix[i][j].denominator;

            if (i == indexi && j == indexj) cout << "\033[0m";

            cout << "\t";    
        }
        cout << " |";
        cout << endl;
    }
    cout << endl;
}
void Remove(vector<vector<Fraction>>& matrix)
{
    int index = 0;
    while (index != matrix.size())
    {
        int counter = 0;
        for (int j = 0; j < matrix[index].size(); ++j)
        {
            if (matrix[index][j].numerator == 0) ++counter;
        }

        if (counter == matrix[index].size())
        {
            matrix.erase(matrix.begin() + index);
            index = 0;
        }
        else
        {
            ++index;
        }
    }
}
void Subtraction(Fraction &multiplier, Fraction &number1, Fraction number2)
{
    number2.numerator *= multiplier.numerator;
    number2.denominator *= multiplier.denominator;
    number1.numerator = number1.numerator * number2.denominator - (number2.numerator * number1.denominator);
    number1.denominator = number1.denominator * number2.denominator;
    number1.Divide();
}
int Deploy(vector <vector<Fraction>> &matrix)
{
    for (int i = 0; i < matrix.size(); ++i)
    {
        int checkLine = 0;
        if (matrix[i][matrix[0].size()-1].numerator != 0)
        {
            for (int j = 0; j < matrix[0].size() - 1; ++j)
            {
                if (matrix[i][j].numerator == 0) checkLine += 1;
            }
        }
        if (checkLine == matrix[0].size() - 1)
        {
            cout << "\033[38;2;256;0;0m\033[48;2;50;50;50mThe system has no solution\033[0m" << endl;
            return 0;
        }
    }
    for (int i = 0; i < matrix.size(); ++i)
    {
        bool checkElement = false;
        for (int j = 0; j < matrix[0].size() - 1; ++j)
        {
            if (checkElement == false && matrix[i][j].numerator == 1 && matrix[i][j].denominator == 1)
            {
                cout << "x" << j + 1 << " = " << matrix[i][matrix[0].size() - 1].numerator;
                if (matrix[i][matrix[0].size() - 1].denominator != 1) cout << "/" << matrix[i][matrix[0].size() - 1].denominator;
                checkElement = true;
            }
            else if (matrix[i][j].numerator != 0)
            {
                cout << " - (x" << j + 1 << " * " << matrix[i][j].numerator;
                if (matrix[i][j].denominator != 1) cout << "/" << matrix[i][j].denominator;
                cout << ")";
            }
        }
        cout << endl;
    }
    cout << endl;
    cout << endl;
}
void CalculateJordanGauss(vector <vector<Fraction>> &matrix)
{
    int index = 0;
    for (int j = 0; j < matrix[0].size(); ++j)
    {
        int maxIndex = index;
        Fraction maxNumber = matrix[maxIndex][j];
        for (int i = index+1; i < matrix.size(); ++i)
        {
            if (Compare(matrix[i][j], maxNumber) == true) 
            {
                maxNumber = matrix[i][j];
                maxIndex = i;
            }
        }
        vector<Fraction> temp = matrix[index];
        matrix[index] = matrix[maxIndex];
        matrix[maxIndex] = temp;
        if (matrix[index][j].numerator != 0)
        {
            if (index == maxIndex) cout << "No swap";
            else cout << "Swap " << index + 1 << " and " << maxIndex + 1;
            Print(matrix,index,j);

            for (int i = 0; i < matrix[0].size(); ++i)
            {
                matrix[index][i].numerator *= maxNumber.denominator;
                matrix[index][i].denominator *= maxNumber.numerator;
                matrix[index][i].Divide();
            }

            cout << "Devide " << maxNumber.numerator << "/" << maxNumber.denominator;
            Print(matrix,index,j);

            for (int i = 0; i < matrix.size(); ++i)
            {
                if (i != index)
                {
                    Fraction multiplier = matrix[i][j];
                    for (int k = 0; k < matrix[0].size(); ++k)
                    {
                        Subtraction(multiplier, matrix[i][k], matrix[index][k]);
                    }
                }
            }
            cout << "Subtraction";
            Print(matrix,index,j);
            ++index;
        }
        if (index == matrix.size()) break;
    }
    cout << "Result matrix:";
    Print(matrix);
    Deploy(matrix);
    Remove(matrix);
}
void ReadFile(vector<vector<Fraction>> &matrix)
{
    std::string line;
    std::ifstream file("file.txt");

    bool checkLine = false;
    while (getline(file, line))
    {
        vector<Fraction> lineMatrix;
        while (line.size() > 0)
        {
            int endSubstr = line.find(' ');
            Fraction element;
            element.numerator = stoi(line.substr(0, endSubstr));
            lineMatrix.push_back(element);

            line.erase(0, endSubstr + 1);
        }
        matrix.push_back(lineMatrix);
    }
    file.close();

    cout << "Matrix:";
    Print(matrix);
}
void Deploy(vector<vector<Fraction>> &matrix, vector<Combination> &combination)
{
    for (int i = 0; i < combination.size(); ++i)
    {
        cout << "x" << combination[i].index + 1 << " ";
    }
    cout << endl;
    cout << "( ";
    for (int j = 0; j < matrix[0].size() - 1; ++j)
    {
        int index = -1;
        for (int i = 0; i < combination.size(); ++i)
        {
            if (j == combination[i].index) index = i;
        }
        if (index != -1)
        {
            cout << matrix[index][matrix[index].size() - 1].numerator;
            if (matrix[index][matrix[index].size() - 1].denominator != 1) cout << "/" << matrix[index][matrix[index].size() - 1].denominator;
            cout << " ";
        }
        else
        {
            cout << "0 ";
        }
    }
    cout << ")\n\n";
}
void SolutionBasis(vector<vector<Fraction>> matrix, vector<Combination> &combination)
{
    for (int indexComb = 0; indexComb < combination.size(); ++indexComb)
    {
        int indexX = combination[indexComb].index;
        //Devide
        Fraction devideNumber = matrix[indexComb][indexX];
        for (int j = 0; j < matrix[0].size(); ++j)
        {
            matrix[indexComb][j].numerator *= devideNumber.denominator;
            matrix[indexComb][j].denominator *= devideNumber.numerator;
            matrix[indexComb][j].Divide();
        }
        //Substraction
        for (int i = 0; i < matrix.size(); ++i)
        {
            if (i != indexComb)
            {
                Fraction multiplier = matrix[i][indexX];
                for (int j = 0; j < matrix[0].size(); ++j)
                {
                    Subtraction(multiplier, matrix[i][j], matrix[indexComb][j]);
                }
            }
        }
    }
    //Result
    Deploy(matrix, combination);
    Print(matrix);
    //cout << "-------------------------------\n\n";
}
void Arrange(vector<vector<Fraction>>& matrix, vector<Combination>& combination)
{
    for (int indexComb = 0; indexComb < combination.size(); ++indexComb)
    {
        for (int i = 0; i < matrix.size(); ++i)
        {
            if (matrix[i][indexComb].numerator == 0) ++combination[indexComb].counter;
        }
    }
    sort(combination.begin(), combination.end());

    vector<Combination> newCombination;
    for (int i = 0; i < matrix.size(); ++i)
    {
        for (int indexComb = 0; indexComb < combination.size(); ++indexComb)
        {
            int indexX = combination[indexComb].index;

            if (matrix[i][indexX].numerator != 0 && combination[indexComb].check != true)
            {
                combination[indexComb].check = true;
                newCombination.push_back(combination[indexComb]);
                //cout << "| " << combination[indexComb].index + 1 << " ";
                break;
            }
        }
    }
    //cout << endl;
    //cout << endl;
    if (newCombination.size() == matrix.size()) SolutionBasis(matrix, newCombination);
}

int CodeGray(int n) {
    return n ^ (n >> 1);
}
int BitCounter(int n) {
    int res = 0;
    for (; n; n >>= 1)
        res += n & 1;
    return res;
}
void SearchBasisCombinations(vector<vector<Fraction>>& matrix)
{
    cout << "Basis:\n\n";
    int n = matrix[0].size() - 1;
    int k = matrix.size();
    //Ckn = n!/k!(n-m)!
    for (int i = 0; i < (1 << n); ++i) {
        vector<Combination> combination;
        int mask = CodeGray(i);
        if (BitCounter(mask) == k) {
            for (int j = 0; j < n; ++j)
            {
                if (mask & (1 << j))
                {
                    Combination element;
                    element.index = j;
                    combination.push_back(element);
                    
                }
            }
            cout << "!\n";
            Arrange(matrix, combination);
        }
    }
}
int main()
{
    vector<vector<Fraction>> matrix;
    ReadFile(matrix);
    CalculateJordanGauss(matrix);
    SearchBasisCombinations(matrix);
}