
#include <iostream>
#include <utility> 
#include <time.h> 

void Bubble(int* array, int sizeArray, int& S, int& P)
{
    for (int i = 0; i < sizeArray; i++) {
        for (int j = 0; j < sizeArray - ( 1 + i); j++) {
            S++;
            if (array[j] > array[j + 1]) {
                std::swap(array[j], array[j+1]);
                P += 3;
            }
        }
    }
}

void Select(int* array, int sizeArray, int& S, int& P)
{
    int i, j, min;
    
    for (i = 0; i < sizeArray - 1; i++)
    {
        min = i;
        for (j = i + 1; j < sizeArray; j++) 
        {
            S++;
            if (array[j] < array[min]) 
            {
                min = j;
            }
        }

        if (min != i)
        {
            std::swap(array[min], array[i]);
            P += 3;
        }
    }
    
}


int* Merge(int* array1, int* array2, int sizeArray1, int sizeArray2, int &S, int &P)
{
    int* newarray = new int[sizeArray1 + sizeArray2];
    int n = 0;

    while (sizeArray1 && sizeArray2) {
        S++;
        if (*array1 < *array2) {
            newarray[n] = *array1;
            array1++;
            sizeArray1--;

        } else {
            newarray[n] = *array2;
            array2++;
            sizeArray2--;

        }
        P++;
        ++n;

    }
    if (sizeArray1 == 0) {
        for (int i = 0; i < sizeArray2; ++i) {
            newarray[n++] = *array2++;
            P++;
        }
    } else { 
        for (int i = 0; i < sizeArray1; ++i) {
            newarray[n++] = *array1++;
            P++;
        }
    };
    return newarray;
}
 
void MergeSort(int * array, int sizeArray, int &S, int &P)
{
    int n1 = 1, n2, remains;
    int* newArray;
    while (n1 < sizeArray) {

        n2 = 0;
    
        while (n2 < sizeArray) {

            if (n2 + n1 >= sizeArray) break;

            if (n2 + n1 * 2 > sizeArray)
            {
                remains = (sizeArray - (n2 + n1));
           
            }
            else
            {
                remains = n1;
        
            }

            newArray = Merge(array + n2, array + n2 + n1, n1, remains,S,P);

            std::cout << "| ";
            for (int i = 0; i < n1 + remains; ++i)
            {
                array[n2 + i] = newArray[i];
                std::cout << array[n2 + i] << " ";
            }
            std::cout << "|";
            delete [] newArray;
            n2 += n1 * 2;
   
        }
        std::cout << std::endl;
        n1 *= 2;
       
    }
}

void PrintArray(int* array, int sizeArray) 
{
    for (int i = 0; i < sizeArray; i++)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

int main()
{
    srand(time(NULL));
    int size;
    int ch;

    std::cin >> size;

    int* array = new int[size];
    for (int i = 0; i < size; i++) 
    {
        //array[i] = rand() % 100;
        std::cin >> array[i];
    }

    std::cout << "[1] Merge Sort" << std::endl;
    std::cout << "[2] Select Sort" << std::endl;
    std::cout << "[3] Bubble Sort" << std::endl;

    std::cin >> ch;

    system("cls");

    PrintArray(array, size);

    int S = 0;
    int P = 0;

    if (ch == 1) 
    {
        MergeSort(array, size, S, P);
        PrintArray(array, size);
        std::cout << std::endl;
        std::cout << "S = " << S << std::endl;
        std::cout << "P = " << P << std::endl;
        std::cout << "S + P = " << S + P << std::endl;
    }
    else if (ch == 2)
    {
        Select(array, size, S, P);
        PrintArray(array, size);
        std::cout << std::endl;
        std::cout << "S = " << S << std::endl;
        std::cout << "P = " << P << std::endl;
        std::cout << "S + P = " << S + P << std::endl;
    }
    else if (ch == 3)
    {
        Bubble(array, size, S, P);
        PrintArray(array, size);
        std::cout << std::endl;
        std::cout << "S = " << S << std::endl;
        std::cout << "P = " << P << std::endl;
        std::cout << "S + P = " << S + P << std::endl;
    }
}

