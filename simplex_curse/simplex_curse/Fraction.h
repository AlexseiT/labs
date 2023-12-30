#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
class Fraction
{
public:
    long long numerator;
    long long denominator;
    Fraction operator + (Fraction right)
    {
        Fraction number;
        number.numerator = this->numerator * right.denominator + this->denominator * right.numerator;
        number.denominator = this->denominator * right.denominator;
        number.Divide();
        return number;
    }
    Fraction operator - (Fraction right)
    {
        Fraction number;
        number.numerator = this->numerator * right.denominator - this->denominator * right.numerator;
        number.denominator = this->denominator * right.denominator;
        number.Divide();
        return number;
    }
    Fraction operator / (Fraction right)
    {
        Fraction number;
        number.numerator = this->numerator * right.denominator;
        number.denominator = this->denominator * right.numerator;
        number.Divide();
        return number;
    }
    Fraction operator * (Fraction right)
    {
        Fraction number;
        number.numerator = this->numerator * right.numerator;
        number.denominator = this->denominator * right.denominator;
        number.Divide();
        return number;
    }
    bool operator > (Fraction right)
    {
        if (this->numerator * right.denominator > right.numerator * this->denominator) 
            return true;
        return false;
    }
    string GetStringNumber()
    {
        if (denominator == 1)
        {
            return to_string(numerator);
        }
        else if (numerator != 0)
        {
            string str = to_string(numerator) + "/" + to_string(denominator);
            return str;
        }
        return "0";
    }
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
    void minus()
    {
        numerator = -numerator;
    }
    void zero()
    {
        numerator = 0;
        denominator = 1;
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