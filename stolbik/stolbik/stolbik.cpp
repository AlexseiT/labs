#include <vector>
#include <iostream>
#include <cmath>

int T = 0;
int n;

void Print(std::vector<int> vector)
{
    std::cout << "\n";
    for (int i = 0; i < vector.size(); i++)
    {
        std::cout << vector[i] << "";
    }
    std::cout << "\n";
}


int Number(std::vector<int> vector)
{
    int number = 0;
    for (int i = 0; i < vector.size(); i++)
    {
        number += vector[vector.size() - i - 1] * pow(10, i);
    }
    return number;
}
std::vector<int> Vector(int number)
{
    std::vector<int> numbers;
    int index = 0;
    while (number != 0)
    {
        index++;
        numbers.insert(numbers.begin(), number % 10);
        number /= 10;
    }
    return numbers;
}
std::vector<int> Enter()
{
    int number;
    std::cin >> number;
    return Vector(number);
}
std::vector<int> Sum(std::vector<int> number1, std::vector<int> number2)
{
    std::vector<int> vector = Vector(Number(number1) + Number(number2));
    //if (vector.size() % 2 != 0) vector.insert(vector.begin(), 0);
    return vector;
}
std::vector<int> Diff(std::vector<int> number1, std::vector<int> number2)
{
    std::vector<int> vector = Vector(Number(number1) - Number(number2));
    //if (vector.size() % 2 != 0) vector.insert(vector.begin(), 0);
    return vector;
}
std::vector<int> VectorSeparation(std::vector<int> vector, int begin, int end)
{
    std::vector<int> part;
    for (int i = begin; i < end; i++)
    {
        part.push_back(vector[i]);
    }
    return part;

}
std::vector<int> Multiplication(std::vector<int> number1, std::vector<int> number2)
{
    std::vector<int> result(number1.size() + number2.size() - 1);
    int transfer = 0;
    for (int i = 0; i < number1.size(); i++)
    {
        for (int j = 0; j < number2.size(); j++)
        {
            result[j + i] += number1[i] * number2[j];
            T += 2;
        }
    }
    T -= result.size();
    for (int i = result.size() - 1; i >= 0; i--)
    {
        if (transfer != 0)
        {
            result[i] = result[i] + transfer;
        }
        transfer = result[i] / 10;
        if (i != 0) result[i] = result[i] % 10;
    }
    return result;
}
std::vector<int> RemoveUnnecessary(std::vector<int> number)
{
    std::vector<int> result;
    bool check = false;
    for (int i = 0; i < number.size(); i++)
    {
        if (number[i] != 0) check = true;
        if (check) result.insert(result.begin(), number[i]);
    }
    return result;
}
std::vector<int> FastMultiplication(std::vector<int> number1, std::vector<int> number2)
{
   /* std::vector<int> num1 = RemoveUnnecessary(number1);
    std::vector<int> num2 = RemoveUnnecessary(number2);
    if (Number(number1) < 10 && Number(number2) < 10)
    {
        return Multiplication(number1, number2);
    }
    */
    n = number1.size() / 2;
    int k = number1.size() / 2;

    std::vector<int> a = VectorSeparation(number1, 0, k);
    std::vector<int> b = VectorSeparation(number1, k, 2 * k);
    std::vector<int> c = VectorSeparation(number2, 0, k);
    std::vector<int> d = VectorSeparation(number2, k, 2 * k);

    std::vector<int> u = Multiplication(Sum(a, b), Sum(c, d));
    std::vector<int> v = Multiplication(a, c);
    std::vector<int> w = Multiplication(b, d);

    std::vector<int> partFirst = Multiplication(v, Vector(pow(2, 2 * k)));
    std::vector<int> partSecond = Multiplication(Diff(Diff(u, v), w), Vector(pow(2, k)));
    std::vector<int> result = Sum(Sum(partFirst, partSecond), w);
    T += 7;
    return result;
}
int main()
{
    std::vector<int> number1 = Enter();
    std::vector<int> number2 = Enter();
    std::cout << "\nMultiplication" ;
    Print(Multiplication(number1, number2));
    std::cout << "Operations = " << T << "\n";
    T = 0;

    if (number1.size() > number2.size())
    {
        while(number1.size() != number2.size())
            number2.insert(number2.begin(), 0);
    }
    else
    {
        while (number1.size() != number2.size())
            number1.insert(number1.begin(), 0);
    }
    if (number1.size() % 2 != 0)
    {
        number1.insert(number1.begin(), 0);
        number2.insert(number2.begin(), 0);
    }
    Print(number1);
    Print(number2);
    std::cout << "\nFast Multiplication\n";
    Print(FastMultiplication(number1, number2));
    //std::cout << FastMultiplication(numberVar1, numberVar2) << "\n";
    //std::cout << "Operations = " << T << "\n";
   // std::cout << "Formula Operations = " << 2 * n + 2 * (n/2) << "\n";
}


