#include <iostream>
#include <vector>
#include <locale.h>
using namespace std;

class Number {
public:
    vector<short> number;
    Number(){}
    Number(string numberstring) 
    {
        int size = numberstring.length();
        number.resize(size);
        for (int i = 0; i < size; i++) {
            number[size - i - 1] = numberstring[i] - '0';
        }
    }
    Number(int size)
    {
        number.resize(size);
    }
    string NumberString() 
    {
        string numberstring;
        int size = number.size();
        for (int i = 0; i < size; i++) 
        {
            numberstring.push_back(number[size - i - 1] + '0');
        }
        return numberstring;
    }
    void Standardize() 
    {
        for (int i = 0; i < number.size() - 1; i++) 
        {
            short carry = number[i] / 10;
            if (number[i] < 0) 
            {
                carry--;
                number[i] += 10 * (-carry);
            }
            else 
            {
                number[i] %= 10;
            }
            number[i + 1] += carry;
        }
    }
    void RemoveUnnecessary() 
    {
        while (number.size() > 1 && number.back() == 0) number.pop_back();
    }
};
Number Sum(Number number1, Number number2, int& T)
{
    Number result;
    int size = max(number1.number.size(), number2.number.size());
    result.number.resize(size);
    for (int i = 0; i < size; i++) 
    {
        if (i == number1.number.size())
            number1.number.push_back(0);
        else if (i == number2.number.size())
            number2.number.push_back(0);
        result.number[i] = number1.number[i] + number2.number[i];
    }
    result.Standardize();
    return result;
}
Number Multiplication(Number number1, Number number2, int& T) 
{
    Number result(number1.number.size() + number2.number.size());
    for (int i = 0; i < number2.number.size(); i++)
    {
        Number tempnumber(i);
        for (int j = 0; j < number1.number.size(); j++)
        {
            tempnumber.number.push_back(number1.number[j] * number2.number[i]);
            T++;
        }
        result = Sum(result, tempnumber, T);
        T++;
        result.Standardize();
    }
    T--;
    result.RemoveUnnecessary();
    return result;
}
void Separation(Number number, int k, Number& leftpart, Number& rightpart) 
{
    for (int i = 0; i < k; i++) 
    {
        rightpart.number[i] = number.number[i];
        leftpart.number[i] = number.number[i + k];
    }
}
void PrintNumber(Number number)
{
    for(int i = 0; i < number.number.size(); i++)
    { 
        cout << number.number[i] << " ";
    }
    cout << endl;
}
Number FastMultiplicationRecursion(Number number1, Number number2, int& T) 
{
    //PrintNumber(number1);
    //PrintNumber(number2);
    int size1 = number1.number.size();
    int size2 = number1.number.size();
    Number result(2 * size1);
    if (size1 == 1 && size2 == 1)
    {

        if (number1.number[0] == 0 || number2.number[0] == 0)
        {
         result.number[0] = 0;
        }
        else
        {
         result.number[0] = number1.number[0] * number2.number[0];
         //cout << number1.number[0] << endl;
         //cout << number2.number[0] << endl;
         T++;
         cout << T << ") " << number1.number[0] << " * " << number2.number[0] << " = " << result.number[0] << endl;
        }
        result.Standardize();
        return result;
    }

    int k = size1 / 2;

    Number a(k);
    Number b(k);
    Number c(k);
    Number d(k);

    Separation(number1, k, a, b);
    Separation(number2, k, c, d);

    Number v = FastMultiplicationRecursion(a, c, T);
    Number w = FastMultiplicationRecursion(b, d, T);
    Number u = FastMultiplicationRecursion(Sum(a, b, T), Sum(c, d, T), T);

    for (int i = 0; i < size1; i++)
    {
        u.number[i] -= (v.number[i] + w.number[i]);
    }
    u.Standardize();
    for (int i = 0; i < size1; i++)
    {
        result.number[i] = w.number[i];
    }
    for (int i = size1; i < 2 * size1; i++)
    {
        result.number[i] = v.number[i - size1];
    }
    for (int i = k; i < size1 + k; i++)
    {
        result.number[i] += u.number[i - k];
    }
    result.Standardize();
    return result;
}

Number FastMultiplication(Number number1, Number number2, int& T) 
{
    int size = max(number1.number.size(), number2.number.size());
    int n = 1;

    while (n < size) n <<= 1;
    PrintNumber(number1);
    PrintNumber(number2);
    number1.number.resize(n);
    number2.number.resize(n);

    PrintNumber(number1);
    PrintNumber(number2);
    Number result = FastMultiplicationRecursion(number1, number2, T);
    result.RemoveUnnecessary();
    number1.RemoveUnnecessary();
    number2.RemoveUnnecessary();
    // проверка на все 9, если да то формула трудоемкости если нет то как в коде. (проверку вынести в функцию подальше)
    return result;
}

int main()
{
    string numberinput;
    int T = 0;

    cin >> numberinput;
    Number number1(numberinput);

    cin >> numberinput;
    Number number2(numberinput);
    cout << "Multiplication\n" << Multiplication(number1, number2, T).NumberString() << endl;
    cout << T << endl;
    T = 0;
    cout << "Fast Multiplication\n" << FastMultiplication(number1, number2, T).NumberString() << endl;
    cout << T << endl;
}