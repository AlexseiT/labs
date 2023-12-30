#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
int maximum = 1E8;
struct Matrix
{
    int rows;
    int cols;
};
struct Bracket {
    int open;
    int close;
};

vector<Bracket> operator + (vector<Bracket> object1, vector<Bracket> object2)
{
    vector<Bracket> result = object1;
    for (int i = 0; i < object2.size(); i++)
    {
        result.push_back(object2[i]);
    }
    return result;
}
void operator += (vector<Bracket>& object1, vector<Bracket> object2)
{
    object1 = object1 + object2;
}

vector<Bracket> FindBracket(int** fMinimum, int begin, int end) 
{
    vector<Bracket> result;
    if (begin == end) 
    {
        return result;
    }
    int minimum = fMinimum[begin][end];
    Bracket bracket1, bracket2;
    bracket1.open = begin;
    bracket1.close = minimum;
    bracket2.open = minimum + 1;
    bracket2.close = end;
    if (bracket1.open != bracket1.close) 
    {
        result.push_back(bracket1);
    }
    if (bracket2.open != bracket2.close) 
    {
        result.push_back(bracket2);
    }
    result += FindBracket(fMinimum, begin, minimum) + FindBracket(fMinimum, minimum + 1, end);
    return result;
}

void Multiplication(vector<Matrix> listMatrix) 
{
    int sizelistMatrix = listMatrix.size();
    int** f = new int* [sizelistMatrix];
    int** fMinimum = new int* [sizelistMatrix];
    for (int i = 0; i < sizelistMatrix; i++) 
    {
        f[i] = new int[sizelistMatrix];
        f[i][i] = 0;
        fMinimum[i] = new int[sizelistMatrix];
        fMinimum[i][i] = i;
    }
    for (int t = 0; t < sizelistMatrix; t++) 
    {
        for (int k = 0; k < sizelistMatrix - t; k++) 
        {
            int minimum = maximum;
            for (int j = k; j < k + t; j++) 
            {
                int minimumTemp = minimum;
                minimumTemp = f[k][j] + f[j + 1][k + t] + listMatrix[k].rows * listMatrix[j].cols * listMatrix[k + t].cols;
                if (minimumTemp < minimum) 
                {
                    minimum = minimumTemp;
                    fMinimum[k][k + t] = j;
                }
            }
            if (minimum < maximum)
            {
                f[k][k + t] = minimum;
            }
        }
    }
    vector<Bracket> bracket = FindBracket(fMinimum, 0, sizelistMatrix - 1);

    for (int i = 0; i < sizelistMatrix; i++)
    {
        cout << "m" << i+1 
            << "[" 
            << listMatrix[i].rows << " x " << listMatrix[i].cols 
            << "]" 
            << endl;
    }
    cout << endl;
    string stringResult;
    for (int i = 0; i < sizelistMatrix; i++) 
    {
        string stringResultMatrix;
        //bool check = false;
        for (int j = 0; j < bracket.size(); j++)
        {
            if (bracket[j].open == i)
            {
                stringResultMatrix += "(";
            }
        }
        stringResultMatrix += " m";
        stringResultMatrix += std::to_string(i + 1);
        stringResultMatrix += " ";
        for (int j = 0; j < bracket.size(); j++)
        {
            if (bracket[j].close == i)
            {
                stringResultMatrix += ")";
            }
        }
        stringResult += stringResultMatrix;
    }
    cout << stringResult << endl << endl;
    cout << "Operations: " << f[0][sizelistMatrix - 1] << endl;
}

int main()
{
    ifstream file;
    file.open("matrix.txt", ios::in);
    vector<Matrix> listMatrix;
    while (!file.eof()) 
    {
        Matrix matrix;
        file >> matrix.rows >> matrix.cols;
        listMatrix.push_back(matrix);
    }
    for (int i = 0; i < listMatrix.size() - 1; i++) 
    {
        if (listMatrix[i].cols != listMatrix[i + 1].rows) 
        {
            cout << "Matrix size don't match: " 
                << listMatrix[i].rows
                << " x " 
                << listMatrix[i].cols 
                <<" and " 
                << listMatrix[i + 1].rows 
                << " x " 
                << listMatrix[i + 1].cols
                << endl;
            return 0;
        }
    }
    Multiplication(listMatrix);
}