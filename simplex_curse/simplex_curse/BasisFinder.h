#pragma once
#include"Fraction.h"
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
class BasisFinder
{
private:
    vector<vector<Fraction>> matrix;
    vector<Fraction> Z;
    vector<Combination> combination;
    bool basisFind = false;
public:
    vector<Combination> GetCombination()
    {
        return combination;
    }
    void SetMatrix(vector<vector<Fraction>> matrix)
    {
        this->matrix = matrix;
    }
    void SetZ(vector<Fraction> Z)
    {
        this->Z = Z;
    }
    vector<vector<Fraction>> GetMatrix()
    {
        return matrix;
    }
    vector<Fraction> GetZ()
    {
        return Z;
    }
    bool Compare(Fraction& number1, Fraction& number2)
    {
        if (abs(number1.numerator * number2.denominator) > abs(number2.numerator * number1.denominator))
            return true;
        else return false;
    }
    void PrintCombination()
    {
        for (auto element : combination)
        {
            cout << element.index << " ";
        }
        cout << "\n";
    }
    void Print(vector <vector<Fraction>>& matrix, int indexi = -1, int indexj = -1)
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
    void Subtraction(Fraction& multiplier, Fraction& number1, Fraction number2)
    {
        number2.numerator *= multiplier.numerator;
        number2.denominator *= multiplier.denominator;
        number1.numerator = number1.numerator * number2.denominator - (number2.numerator * number1.denominator);
        number1.denominator = number1.denominator * number2.denominator;
        number1.Divide();
    }
    void Sum(Fraction& number1, Fraction number2)
    {
        number1.numerator = number1.numerator * number2.denominator + (number2.numerator * number1.denominator);
        number1.denominator = number1.denominator * number2.denominator;
        number1.Divide();
    }
    int Deploy(vector <vector<Fraction>>& matrix)
    {
        for (int i = 0; i < matrix.size(); ++i)
        {
            int checkLine = 0;
            if (matrix[i][matrix[0].size() - 1].numerator != 0)
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
    void CalculateJordanGauss()
    {
        int index = 0;
        for (int j = 0; j < matrix[0].size(); ++j)
        {
            int maxIndex = index;
            Fraction maxNumber = matrix[maxIndex][j];
            for (int i = index + 1; i < matrix.size(); ++i)
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

                for (int i = 0; i < matrix[0].size(); ++i)
                {
                    matrix[index][i].numerator *= maxNumber.denominator;
                    matrix[index][i].denominator *= maxNumber.numerator;
                    matrix[index][i].Divide();
                }

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
                ++index;
            }
            if (index == matrix.size()) break;
        }
        //Print(matrix);
        //Deploy(matrix);
        Remove(matrix);
    }
    void Deploy(vector<vector<Fraction>>& matrix, vector<Combination>& combination)
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
    void PrintLine(vector<Fraction> line)
    {
        for (int i = 0; i < line.size(); ++i)
        {
            if (line[i].numerator != 0 && line[i].denominator != 1)
                cout << line[i].numerator << "/" << line[i].denominator << " ";
            else
                cout << line[i].numerator << " ";
        }
        cout << endl;
    }
    void ExpressZ(vector<vector<Fraction>> matrix, vector<Combination>& combination, vector<Fraction>& Z)
    {
        //PrintLine(Z);

        vector<vector<Fraction>> newParametrs;

        for (int i = 0; i < matrix.size(); ++i)
        {

            vector<Fraction> lineParametr;
            lineParametr.push_back(matrix[i][matrix[0].size() - 1]);
            for (int j = 0; j < matrix[0].size() - 1; ++j)
            {
                if (combination[i].index == j)
                {
                    matrix[i][j].zero();
                }
                else
                {
                    matrix[i][j].minus();
                }
                lineParametr.push_back(matrix[i][j]);
            }
            //PrintLine(lineParametr);
            Fraction Ztemp = Z[combination[i].index + 1];
            for (int j = 0; j < lineParametr.size(); ++j)
            {
                lineParametr[j].numerator *= Ztemp.numerator;
                lineParametr[j].denominator *= Ztemp.denominator;
                lineParametr[j].Divide();
                if (j == combination[i].index + 1) Z[j].zero();
                Sum(Z[j], lineParametr[j]);
            }
        }
        for (int i = 1; i < Z.size(); ++i)
        {
            Z[i].minus();
        }
    }
    void SolutionBasis(vector<vector<Fraction>> matrix, vector<Combination>& combination, bool& checkReference, vector<Fraction>& Z)
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
        for (int i = 0; i < matrix.size(); ++i)
        {
            if (matrix[i][matrix[0].size() - 1].numerator < 0)
            {
                checkReference = false;
                break;
            }
        }
        if (checkReference == true)
        {
            this->matrix = matrix;
            this->combination = combination;
            //PrintCombination();
            ExpressZ(matrix, combination, Z);
        }
    }
    void Arrange(vector<vector<Fraction>>& matrix, vector<Combination>& combination, bool& checkReference, vector<Fraction>& Z)
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
                    break;
                }
            }
        }
        if (newCombination.size() == matrix.size())
        {
            SolutionBasis(matrix, newCombination, checkReference, Z);
        }
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
    void SearchBasisCombinations()
    {
        int n = matrix[0].size() - 1;
        int k = matrix.size();
        bool checkReference = false;
        for (int i = 0; i < (1 << n); ++i) {
            vector<Combination> combination;
            int mask = CodeGray(i);
            if (checkReference == true)
            {
                basisFind = true;
                break;
            }
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
                checkReference = true;
                Arrange(matrix, combination, checkReference, Z);
            }
        }
    }
    bool CheckBasisFind()
    {
        return basisFind;
    }
    void StartFindCorrectBasis()
    {
        CalculateJordanGauss();
        SearchBasisCombinations();
    }
};