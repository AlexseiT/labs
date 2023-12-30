#pragma once
#include"BasisFinder.h"
class SimplexMethod
{
private:
    vector<vector<Fraction>> matrix;
    vector<vector<Fraction>> results;
    vector<Fraction> Z;
    vector<Combination> combination;
    int countCombination;
    bool Zchanged = false;
    bool CheckSD;
    int countStartZ;;
    string statusZ;
    vector<string> signs;
    int iLeaderIndex;
    int jLeaderIndex;
    BasisFinder startFinder;
public:
    bool CheckZ()
    {
        for (int i = 1; i < Z.size(); ++i)
        {
            if (Z[i].numerator < 0) return false;
        }
        return true;
    }
    bool CheckElementZ()
    {
        for (int i = 1; i < Z.size(); ++i)
        {
            bool check = true;
            for (int j = 0; j < combination.size(); ++j)
            {
                if (combination[j].index == i - 1) check = false;
            }
            if (check && Z[i].numerator == 0)
            {
                jLeaderIndex = i - 1;
                return true;
            }
        }
        return false;
    }
    void Print(int indexi = -1, int indexj = -1)
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
    void PrintSimplex(int indexi = -1, int indexj = -1)
    {
        for (int i = 0; i < matrix[0].size() + 1; ++i)
        {
            cout << "_____________";
        }
        cout << "\n";
        cout << setw(15) << "1";
        for (int i = 0; i < matrix[0].size()-1; ++i)
        {
            cout << setw(13) << "x" << i+1;
        }
        cout << "\n";
        for (int i = 0; i < matrix[0].size() + 1; ++i)
        {
            cout << "_____________";
        }
        cout << "\n";
        for (int i = 0; i < matrix.size(); ++i)
        {
            cout << setw(5) << "x" << combination[i].index + 1 << " |";
            cout << setw(10) << matrix[i][matrix[0].size() - 1].GetStringNumber() << " |";
            for (int j = 0; j < matrix[0].size() - 1; ++j)
            {
                if (i == indexi && j == indexj) cout << "\033[38;2;256;0;0m\033[48;2;50;50;50m";
                cout << setw(10) << matrix[i][j].GetStringNumber() << "   ";
                if (i == indexi && j == indexj) cout << "\033[0m";
                cout << "|";
            }
            cout << "\n";
        }
        for (int i = 0; i < matrix[0].size() + 1; ++i)
        {
            cout << "_____________";
        }
        cout << "\n";
        cout << setw(5) << "    Z  |";
        cout << setw(10) << Z[0].GetStringNumber() << " |";
        for (int i = 1; i < Z.size(); ++i)
        {
            cout << setw(10) << Z[i].GetStringNumber() << "   |";
        }
        cout << "\n";
        for (int i = 0; i < matrix[0].size() + 1; ++i)
        {
            cout << "_____________";
        }
        cout << "\n";
        cout << "\n";
    }
    void PrintTask()
    {
        cout << "Z = ";
        for (int i = 0; i < Z.size(); ++i)
        {
            if (i != 0)
            {
                cout << "+ ";
                cout << "(" << Z[i].GetStringNumber() << " x" << i << ") ";
            }
            else
            {
                cout << Z[i].GetStringNumber() << " ";
            }
        }
        cout << "--> " << statusZ << endl;

        for (int i = 0; i < matrix.size(); ++i)
        {
            for (int j = 0; j < matrix[0].size()-1; ++j)
            {
                if (j != 0) cout << "+ ";
                cout << "(" << matrix[i][j].GetStringNumber() << " x" << j + 1 << ") ";
            }
            cout << signs[i];
            cout << " " << matrix[i][matrix[0].size() - 1].GetStringNumber();
            cout << "\n";
        }
        cout << "\n";
    }
    void ReadFile(std::string filename)
    {
        std::ifstream file(filename);
        std::string line;
        int checkStr = 0;
        while (getline(file, line))
        {
            if (checkStr == 0)
            {
                statusZ = line;
                checkStr = 1;
            }
            else if (checkStr == 1)
            {
                while (line.size() > 0)
                {
                    int endSubstr = line.find(' ');
                    Fraction element;
                    element.numerator = stoi(line.substr(0, endSubstr));
                    Z.push_back(element);
                    line.erase(0, endSubstr + 1);
                }
                checkStr = 2;
            }
            else if (line.size() == 1)
            {
                signs.push_back(line);
            }
            else
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
        }
        file.close();
    }
	void LeadCanonicalForm()
	{
        Fraction elementNull;
        elementNull.numerator = 0;
        countStartZ = Z.size() - 1;
        if (statusZ == "min")
        {
            for (int i = 0; i < Z.size(); ++i)
            {
                Z[i].minus();
            }
            Zchanged = true;
            statusZ = "max";
        }
        for (int i = 0; i < signs.size(); ++i)
        {
            if (signs[i] != "=")
            {
                int size = matrix[0].size();
                Fraction element;
                if (signs[i] == ">")
                {
                    element.numerator = -1;

                }
                if (signs[i] == "<")
                {
                    element.numerator = 1;
                }
                for (int j = 0; j < matrix.size(); ++j)
                {
                    if (i == j)
                        matrix[j].insert(matrix[j].begin() + size - 1, element);
                    else
                        matrix[j].insert(matrix[j].begin() + size - 1, elementNull);
                }
                Z.push_back(elementNull);
                signs[i] = "=";
            }
        }
        
	}
    void FindLeaderIndexJ()
    {
        Fraction minElement;
        // находим j минимального элемента
        for (int i = 1; i < Z.size(); ++i)
        {
            if (Z[i].numerator < 0)
            {
                minElement = Z[i];
                jLeaderIndex = i - 1;
            }
        }
        for (int i = 1; i < Z.size(); ++i)
        {
            if (Z[i].numerator < 0 && minElement > Z[i])
            {
                minElement = Z[i];
                jLeaderIndex = i - 1;
            }
        }
    }
    void FindLeaderIndexI()
    {
        Fraction minElement;
        for (int i = 0; i < matrix.size(); ++i)
        {
            if (matrix[i][jLeaderIndex].numerator != 0)
            {
                Fraction resultNumber = matrix[i][matrix[0].size()-1] / matrix[i][jLeaderIndex];
                if (resultNumber.numerator > 0)
                {
                    minElement = resultNumber;
                    iLeaderIndex = i;
                }
            }
        }
        cout << "\n\n\n_____" << endl;
        cout << " SD " << endl;
        cout << "_____" << endl;
        CheckSD = true;
        for (int i = 0; i < matrix.size(); ++i)
        {
            if (matrix[i][jLeaderIndex].numerator != 0)
            {
                Fraction resultNumber = matrix[i][matrix[0].size() - 1] / matrix[i][jLeaderIndex];
                if(resultNumber.numerator > 0)
                {
                    cout << resultNumber.GetStringNumber() << endl;
                    CheckSD = false;
                }
                else
                {
                    cout << "-" << endl;
                }
                if (resultNumber.numerator > 0 && minElement > resultNumber)
                {
                    minElement = resultNumber;
                    iLeaderIndex = i;
                }
            }
            else
            {
                cout << "-" << endl;
            }
        }
        cout << "_____" << endl;
    }
    void FindMatrixRectangle()
    {
        vector<vector<Fraction>> newMatrix = matrix;
        vector<Fraction> newZ = Z;
        vector<Fraction> reverseZ;
        for (int i = 0; i < matrix.size(); ++i)
        {
            for (int j = 0; j < matrix[0].size(); ++j)
            {
                if (i == iLeaderIndex) newMatrix[i][j] = matrix[i][j] / matrix[iLeaderIndex][jLeaderIndex];
                else if (i != iLeaderIndex && j == jLeaderIndex) newMatrix[i][j].zero();
                else
                {
                    int iIndex1 = iLeaderIndex;
                    int jIndex1 = j;
                    int iIndex2 = i;
                    int jIndex2 = jLeaderIndex;
                    newMatrix[i][j] = matrix[i][j] - ((matrix[iIndex1][jIndex1] * matrix[iIndex2][jIndex2]) / matrix[iLeaderIndex][jLeaderIndex]);
                }
            }
        }

        for (int j = 1; j < Z.size(); ++j)
        {
            reverseZ.push_back(Z[j]);
        }
        reverseZ.push_back(Z[0]);

        for (int j = 0; j < Z.size(); ++j)
        {
            if (j == jLeaderIndex) newZ[j].zero();
            else
            {
                int iIndex = iLeaderIndex;
                int jIndex = j;
                int Index = jLeaderIndex;
                newZ[j] = reverseZ[j] - ((reverseZ[Index] * matrix[iIndex][jIndex]) / matrix[iLeaderIndex][jLeaderIndex]);
                //cout << reverseZ[j].GetStringNumber() << " - " << reverseZ[Index].GetStringNumber() << "*" << matrix[iIndex][jIndex].GetStringNumber() << "/" << matrix[iLeaderIndex][jLeaderIndex].GetStringNumber() << endl;
                //cout << newZ[j].GetStringNumber() << endl;
            }
        }

        Z[0] = newZ[Z.size()-1];
        for (int j = 1; j < Z.size(); ++j)
        {
            Z[j] = newZ[j - 1];
        }

        combination[iLeaderIndex].index = jLeaderIndex;
        matrix = newMatrix;

    }
    int Factorial(int i)
    {
        if (i == 0) return 1;
        else return i * Factorial(i - 1);
    }
    void FindCountCombination()
    {
        countCombination = Factorial(matrix[0].size() - 1) / (Factorial(matrix.size()) * Factorial(matrix[0].size() - 1 - matrix.size()));
    }
    void AddResult()
    {
        vector<Fraction> resultElement(matrix[0].size() - 1);
        Fraction zero;
        for (int i = 0; i < matrix[0].size() - 1; ++i)
        {
            bool check = false;
            int index;
            for (int j = 0; j < combination.size(); ++j)
            {
                if (combination[j].index == i)
                {
                    check = true;
                    index = j;
                }
            }
            if (check)
            {
                resultElement[i] = matrix[index][matrix[0].size() - 1];
            }
            else
            {
                resultElement[i] = zero;
            }
        }
        results.push_back(resultElement);
    }
    void DeployResult()
    {
        Fraction resultZ = Z[0];
        if (Zchanged)
        {
            resultZ.numerator *= -1;
            cout << "Zmin = ";
        }
        else
        {
            cout << "Zmax = ";
        }

        if (results.size() == 1)
        {
            cout << "Z( ";
            for (int i = 0; i < countStartZ; ++i)
            {
                cout << results[0][i].GetStringNumber();
                if (i != countStartZ-1) cout << " ; ";
            }
            cout << " ) = " << resultZ.GetStringNumber() << endl;;
        }
        else
        {
            cout << "Z(X*) = Z( ";
            for (int i = 0; i < countStartZ; ++i)
            {
                cout << "(" << results[1][i].GetStringNumber() << ") + (" << (results[0][i] - results[1][i]).GetStringNumber() << ")L";
                if (i != countStartZ-1) cout << " ; ";
            }
            cout << " ) = " << resultZ.GetStringNumber() << endl;
        }
    }
    bool CheckEndResult()
    {
        Fraction zero;
        for (int i = 0; i < matrix.size(); i++)
        {
            if (zero > matrix[i][matrix.size() - 1]) return false;
        }
        return true;
    }
    void Solve(std::string filename = "file.txt")
    {
        ReadFile(filename);
        PrintTask();
        LeadCanonicalForm();
        PrintTask();
        startFinder.SetMatrix(matrix);
        startFinder.SetZ(Z);
        startFinder.StartFindCorrectBasis();
        if (startFinder.CheckBasisFind())
        {
            matrix = startFinder.GetMatrix();
            Z = startFinder.GetZ();
            combination = startFinder.GetCombination();
            PrintSimplex();
            FindCountCombination();
            for (int i = 0; i < countCombination; ++i)
            {
                if (CheckSD) break;
                if (CheckZ())
                {
                    break;
                }
                FindLeaderIndexJ();
                FindLeaderIndexI();
                PrintSimplex(iLeaderIndex, jLeaderIndex);
                FindMatrixRectangle();
            }
            if (CheckZ())
            {
                AddResult();
                if (CheckElementZ())
                {
                    FindLeaderIndexI();
                    PrintSimplex(iLeaderIndex, jLeaderIndex);
                    FindMatrixRectangle();
                    PrintSimplex();
                    AddResult();
                }
                PrintSimplex();
                DeployResult();

            }
            else
            {
                cout << "There is no solution" << endl;
            }
        }
        else
        {
            cout << "There is no solution" << endl;
            cout << "Reference solution not found" << endl;
        }
    }
};