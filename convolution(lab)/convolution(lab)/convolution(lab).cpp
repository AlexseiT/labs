#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
int N;
const int arraySize1 = 3;
const int arraySize2 = 4;
int p1;
int p2;
const double pi = 3.141592653589793;
int convolutionArraySize = arraySize1 + arraySize2 - 1;
int T = 0;

struct complexNumber
{
    double imaginary = 0;
    double valid = 0;
};

complexNumber* revercehalfFastPF(int N, complexNumber* complex)
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
                newComplexA1[n].valid += complex[j2 + p2 * j1].valid * cos(degree) - complex[j2 + p2 * j1].imaginary * sin(degree);
                newComplexA1[n].imaginary += complex[j2 + p2 * j1].valid * sin(degree) + complex[j2 + p2 * j1].imaginary * cos(degree);
                T += 5;
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
                T += 5;
            }
        }
    }
    return newComplexA2;
}
complexNumber* halfFastPF(int N, complexNumber* complex)
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
                T += 5;
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
                T += 5;
            }

            newComplexA2[n].valid = newComplexA2[n].valid / p2;
            newComplexA2[n].imaginary = newComplexA2[n].imaginary / p2;
        }
    }
    return newComplexA2;
}
complexNumber* reverseDPF(int sizeArray, complexNumber* complex)
{
    complexNumber* reverseComplex = new complexNumber[sizeArray];
    for (int i = 0; i < sizeArray; i++)
    {
        for (int j = 0; j < sizeArray; j++)
        {
            double expDegree = (2 * pi * j * i) / sizeArray;
            reverseComplex[i].valid += complex[j].valid * cos(expDegree) - complex[j].imaginary * sin(expDegree);
            reverseComplex[i].imaginary += complex[j].valid * sin(expDegree) + complex[j].imaginary * cos(expDegree);
            T += 5;
        }
    }
    return reverseComplex;
}
complexNumber* directDPF(int sizeArray, complexNumber* complex)
{
    complexNumber* directComplex = new complexNumber[sizeArray];
    for (int i = 0; i < sizeArray; i++)
    {
        for (int j = 0; j < sizeArray; j++)
        {
            double expDegree = (2 * pi * j * i) / sizeArray;
            directComplex[i].valid += complex[j].valid * cos(expDegree) + complex[j].imaginary * sin(expDegree);
            directComplex[i].imaginary += -complex[j].valid * sin(expDegree) + complex[j].imaginary * cos(expDegree);
            T += 5;
        }
        directComplex[i].imaginary = directComplex[i].imaginary / sizeArray;
        directComplex[i].valid = directComplex[i].valid / sizeArray;
    }
    return directComplex;
}

void printArray(std::string title, int size, double* convolutionArray)
{
    std::cout << "  " << title << " Convolution\n";
    for (int i = 0; i < size; i++)
    {
        std::cout << convolutionArray[i] << "\n";
    }
    std::cout << "  Operations = " << T << "\n\n";
}
void printArray(std::string title, int size, complexNumber* convolutionArray)
{
    std::cout << "  " << title << " Convolution\n";
    for (int i = 0; i < size; i++)
    {
        std::cout << convolutionArray[i].valid << "\n";
    }
    std::cout << "  Operations = " << T << "\n\n";
}

void justConvolution(double* convolutionArray, double* firstArray, double* secondArray)
{
    for (int i = 0; i < arraySize1; i++)
    {
        for (int j = 0; j < arraySize2; j++)
        {
            convolutionArray[j + i] += firstArray[i] * secondArray[j];
            T += 2;
        }
    }
}
complexNumber* fastConvolutionDPF(complexNumber* complex1, complexNumber* complex2)
{
    complexNumber* complexResult = new complexNumber[2 * N];
    complex1 = directDPF(2 * N, complex1);
    complex2 = directDPF(2 * N, complex2);
    for (int i = 0; i < 2 * N; i++)
    {
        complexResult[i].valid = complex1[i].valid * complex2[i].valid - complex1[i].imaginary * complex2[i].imaginary;
        complexResult[i].imaginary = complex1[i].valid * complex2[i].imaginary + complex1[i].imaginary * complex2[i].valid;
        complexResult[i].valid *= 2 * N;
        complexResult[i].imaginary *= 2 * N;
        T += 2;
    }
    complexResult = reverseDPF(2 * N, complexResult);
    for (int i = 0; i < 2 * N; i++)
    {
        complexResult[i].valid = floor(complexResult[i].valid+0.5);
    }
    return complexResult;
}
complexNumber* fastConvolutionHFF(complexNumber* complex1, complexNumber* complex2)
{
    complexNumber* complexResult = new complexNumber[2 * N];
    complex1 = halfFastPF(2 * N, complex1);
    complex2 = halfFastPF(2 * N, complex2);
    for (int i = 0; i < 2 * N; i++)
    {
        complexResult[i].valid = complex1[i].valid * complex2[i].valid - complex1[i].imaginary * complex2[i].imaginary;
        complexResult[i].imaginary = complex1[i].valid * complex2[i].imaginary + complex1[i].imaginary * complex2[i].valid;
        complexResult[i].valid *= 2 * N;
        complexResult[i].imaginary *= 2 * N;
        T += 2;
    }
    complexResult = revercehalfFastPF(2 * N, complexResult);
    for (int i = 0; i < 2 * N; i++)
    {
        complexResult[i].valid = floor(complexResult[i].valid + 0.5);
    }
    return complexResult;
}

int main()
{
    if (arraySize1 > arraySize2) N = arraySize1;
    else N = arraySize2;

    p1 = 2;
    p2 = N;




    double firstArray[arraySize1] = { 1,2,3};

    double secondArray[arraySize2] = { 4,5,6,7 };

    double* convolutionArray = new double [convolutionArraySize]{0};

    complexNumber* complexFirstArray = new complexNumber[2 * N];
    complexNumber* complexSecondArray = new complexNumber[2 * N];
    complexNumber* complexConvolutionArray = new complexNumber[2 * N];

    for (int i = 0; i < arraySize1; i++)
    {
        complexFirstArray[i].valid = firstArray[i];
    }
    for (int i = 0; i < arraySize2; i++)
    {
        complexSecondArray[i].valid = secondArray[i];
    }
    justConvolution(convolutionArray, firstArray, secondArray);
    printArray("Just", convolutionArraySize, convolutionArray);
    T = 0;
    complexConvolutionArray = fastConvolutionDPF(complexFirstArray, complexSecondArray);
    printArray("(DPF) Fast", convolutionArraySize, complexConvolutionArray);
    T = 0;
    complexConvolutionArray = fastConvolutionHFF(complexFirstArray, complexSecondArray);
    printArray("(HHF) Fast", convolutionArraySize, complexConvolutionArray);
}
