#include <iostream>
#include <iomanip>
#include <cmath>
const double pi = 3.141592653589793;
int p1 = 0;
int p2 = 0;
int T1 = 0;
int T2 = 0;
struct complexNumber
{
    double imaginary = 0;
    double valid = 0;
};
void PrintComplex(complexNumber* complex)
{
    std::cout << std::fixed << std::setprecision(10);
    std::cout << "x[" << 0 << "] (" << complex[0].valid << ") + (" << complex[0].imaginary << ")i" << std::endl;
    for (int i = (p1 * p2 - 1); i > 0; i--)
    {
        std::cout << "x[" << (p1 * p2) - i << "] (" << complex[i].valid << ") + (" << complex[i].imaginary << ")i" << std::endl;
    }
}
void revercehalfFastPF(int N, complexNumber* complex)
{
    std::cout << "Reverse FastPF" << std::endl;
    complexNumber* newComplexA1 = new complexNumber[N];
    complexNumber* newComplexA2 = new complexNumber[N];

    for (int j2 = 0; j2 < p2; j2++)
    {
        for (int k1 = 0; k1 < p1; k1++)
        {
            int n = k1 + p1 * j2;

            for (int j1 = 0; j1 < p1; j1++)
            {
                double degree = (2 * pi * j1 * k1) / p1;
                newComplexA1[n].valid += complex[j2 + p2 * j1].valid * cos(degree) - complex[j2 + p2 * j1].imaginary * sin(degree);
                newComplexA1[n].imaginary += complex[j2 + p2 * j1].valid * sin(degree) + complex[j2 + p2 * j1].imaginary * cos(degree);
            }
        }
    }

    for (int k2 = 0; k2 < p2; k2++)
    {
        for (int k1 = 0; k1 < p1; k1++)
        {
            int n = k1 + p1 * k2;

            for (int j2 = 0; j2 < p2; j2++)
            {

                double degree = (2 * pi * j2 * n) / N;
                newComplexA2[n].valid += newComplexA1[k1 + p1 * j2].valid * cos(degree) - newComplexA1[k1 + p1 * j2].imaginary * sin(degree);
                newComplexA2[n].imaginary += newComplexA1[k1 + p1 * j2].valid * sin(degree) + newComplexA1[k1 + p1 * j2].imaginary * cos(degree);
            }

            std::cout << std::fixed << std::setprecision(10);
            std::cout << "x[" << n << "] (" << newComplexA2[n].valid << ") + (" << newComplexA2[n].imaginary << ")i" << std::endl;
        }
    }

}
void halfFastPF(int N, complexNumber* complex)
{
    complexNumber* newComplexA1 = new complexNumber[N];
    complexNumber* newComplexA2 = new complexNumber[N];

    for (int j2 = 0; j2 < p2; j2++)
    {
        for (int k1 = 0; k1 < p1; k1++)
        {
            int n = k1 + p1 * j2;

            for (int j1 = 0; j1 < p1; j1++)
            {
                double degree = (2 * pi * j1 * k1) / p1;
                newComplexA1[n].valid += complex[j2 + p2 * j1].valid * cos(degree) + complex[j2 + p2 * j1].imaginary * sin(degree);
                newComplexA1[n].imaginary += -complex[j2 + p2 * j1].valid * sin(degree) + complex[j2 + p2 * j1].imaginary * cos(degree);
                T2 += 5;
            }

            newComplexA1[n].valid = newComplexA1[n].valid / p1;
            newComplexA1[n].imaginary = newComplexA1[n].imaginary / p1;
        }
    }

    for (int k2 = 0; k2 < p2; k2++) 
    {
        for (int k1 = 0; k1 < p1; k1++) 
        {
            int n = k1 + p1 * k2;

            for (int j2 = 0; j2 < p2; j2++) 
            {

                double degree = (2 * pi * j2 * n) / N;
                newComplexA2[n].valid += newComplexA1[k1 + p1 * j2].valid * cos(degree) + newComplexA1[k1 + p1 * j2].imaginary * sin(degree);
                newComplexA2[n].imaginary += -newComplexA1[k1 + p1 * j2].valid * sin(degree) + newComplexA1[k1 + p1 * j2].imaginary * cos(degree);
                T2 += 5;
            }

            newComplexA2[n].valid = newComplexA2[n].valid / p2;
            newComplexA2[n].imaginary = newComplexA2[n].imaginary / p2;
            
            std::cout << std::fixed << std::setprecision(10);
            std::cout << "x[" << n << "] (" << newComplexA2[n].valid << ") + (" << newComplexA2[n].imaginary << ")i" << std::endl;
        }
    }
    revercehalfFastPF(N, newComplexA2);
}
void reverseDPF(int sizeArray, complexNumber* complex)
{
    std::cout << "Reverse DPF" << std::endl;
    complexNumber* reverseComplex = new complexNumber[sizeArray];
    for (int i = 0; i < sizeArray; i++) 
    { 
        for (int j = 0; j < sizeArray; j++) 
        { 
            double expDegree = (2 * pi * j * i) / sizeArray;
            reverseComplex[i].valid += complex[j].valid * cos(expDegree) - complex[j].imaginary * sin(expDegree);
            reverseComplex[i].imaginary += complex[j].valid * sin(expDegree) + complex[j].imaginary * cos(expDegree);
        }
        std::cout << std::fixed << std::setprecision(10);
        std::cout << "x[" << i << "] (" << reverseComplex[i].valid << ") + (" << reverseComplex[i].imaginary << ")i" << std::endl;
    }
}
void directDPF(int sizeArray, complexNumber* complex)
{
    complexNumber* directComplex = new complexNumber[sizeArray];
    for (int i = 0; i < sizeArray; i++) 
    { 
        for (int j = 0; j < sizeArray; j++) 
        { 
            double expDegree = (2 * pi * j * i) / sizeArray; 
            directComplex[i].valid += complex[j].valid * cos(expDegree) + complex[j].imaginary * sin(expDegree);
            directComplex[i].imaginary += -complex[j].valid * sin(expDegree) + complex[j].imaginary * cos(expDegree);
            T1 += 5;
        }
        directComplex[i].imaginary = directComplex[i].imaginary / sizeArray;
        directComplex[i].valid = directComplex[i].valid / sizeArray;
        std::cout << std::fixed << std::setprecision(10);
        std::cout << "x[" << i << "] (" << directComplex[i].valid << ") + (" << directComplex[i].imaginary << ")i" << std::endl;

    }
    reverseDPF(sizeArray, directComplex);
}

int main()
{
    complexNumber *complex;
    int sizeArray; 
    int C = 5;
    std::cout << "p1: " << std::endl;
    std::cin >> p1;
    std::cout << "p2: " << std::endl;
    std::cin >> p2;
    std::cout << "Size array (N) = " << p1 * p2 << std::endl;
    sizeArray = p1 * p2;
    complex = new complexNumber[sizeArray];

    for (int i = 0; i < sizeArray; i++)
    {
        if (i < sizeArray / 2)
        {
            complex[i].valid = i + 1;
            complex[i].imaginary = 0;
        }
        std::cout << "x[" << i << "] (" << complex[i].valid << ") + (" << complex[i].imaginary << ")i" << std::endl;
    }


    std::cout << "Direct DPF" << std::endl;

    directDPF(sizeArray, complex);

    std::cout << "Half Fast PF" << std::endl;

    halfFastPF(sizeArray, complex);

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "T DPF:" << T1 << std::endl;
    std::cout << "T half fast PF:" << T2 << std::endl;
}


