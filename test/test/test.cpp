#include <iostream>
#include <iomanip>
const double pi = 3.141592653589793;

void reverseDPF(int sizeArray, double* validArray, double* imaginaryArray)
{
    std::cout << "Reverse DPF" << std::endl;
    double* imaginary = new double[sizeArray];
    double* valid = new double[sizeArray];
    for (int i = 0; i < sizeArray; i++) { // i = j
        imaginary[i] = 0;
        valid[i] = 0;
        for (int j = 0; j < sizeArray; j++) { // j = k
            double expDegree = (2 * pi * j * i) / sizeArray; // 2*pi*k*j/N
            // ( validArray + i * imaginaryArray ) * ( cos ( 2*pi*k*j/N ) + i * sin( 2*pi*k*j/N ) )
            valid[i] += validArray[j] * cos(expDegree) + imaginaryArray[j] * sin(expDegree);
            imaginary[i] += validArray[j] * sin(expDegree) + imaginaryArray[j] * cos(expDegree);
        }
        std::cout << std::fixed << std::setprecision(10);
        std::cout << "x[" << i << "] (" << valid[i] << ") + (" << imaginary[i] << ")i" << std::endl;
    }
}

void directDPF(int sizeArray, double* validArray, double* imaginaryArray)
{
    double* imaginary = new double[sizeArray];
    double* valid = new double[sizeArray];
    for (int i = 0; i < sizeArray; i++) { // i = j
        imaginary[i] = 0;
        valid[i] = 0;
        for (int j = 0; j < sizeArray; j++) { // j = k
            double expDegree = (2 * pi * j * i) / sizeArray; // 2*pi*k*j/N
            // ( validArray + i * imaginaryArray ) * ( cos ( 2*pi*k*j/N ) - i * sin( 2*pi*k*j/N ) )
            valid[i] += validArray[j] * cos(expDegree) - imaginaryArray[j] * sin(expDegree);
            imaginary[i] += -validArray[j] * sin(expDegree) + imaginaryArray[j] * cos(expDegree);
        }
        // 1/N
        imaginary[i] = imaginary[i] / sizeArray;
        valid[i] = valid[i] / sizeArray;
        std::cout << "x[" << i << "] (" << valid[i] << ") + (" << imaginary[i] << ")i" << std::endl;
    }
    reverseDPF(sizeArray, valid, imaginary);
}

int main()
{
    double* validArray;
    double* imaginaryArray;
    int sizeArray; // N
    int C = 5;
    std::cout << "Size array (N): ";
    std::cin >> sizeArray;
    validArray = new double[sizeArray];
    imaginaryArray = new double[sizeArray];
    for (int i = 0; i < sizeArray; i++)
    {
        std::cout << "v = ";
        std::cin >> validArray[i];
        std::cout << "i = ";
        std::cin >> imaginaryArray[i];
        std::cout << ";" << std::endl;
    }
    std::cout << "Direct DPF" << std::endl;
    directDPF(sizeArray, validArray, imaginaryArray);
    //std::cout << "Reverse DPF" << std::endl;
    //reverseDPF(sizeArray, validArray, imaginaryArray);
    std::cout << C * sizeArray * sizeArray;
}

