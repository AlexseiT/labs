#include <iostream>
#include <cstdlib>
#include <vector>
#include <time.h>
struct ID
{
    double totalTest;
    double insertVector;
    double eraceVector;
    double doubleRand;
    double intRandMatrix;
};
void Test(ID* benchmarkInfo, int numberTasks)
{
    int quantityElement = 10000;
    for (int i = 0; i < numberTasks; i++)
    {
        clock_t globalVectorTimer = clock();
        std::vector<int> vectorTest;

        clock_t timer = clock();
        for (int count = 0; count < quantityElement; count++)
        {
            vectorTest.emplace_back(count);
        } 
        benchmarkInfo[i].insertVector = clock() - timer; // Insert Test

        timer = clock();
        for (int count = 0; count < quantityElement; count++)
        {
            vectorTest.emplace_back(count);
        }
        benchmarkInfo[i].eraceVector = clock() - timer; // Erace Test

        double doubleVar;
        timer = clock();
        for (int count = 0; count < quantityElement; count++)
        {
            doubleVar = (double)rand() / (double)RAND_MAX * (-100 - 100) + 100;
        }
        benchmarkInfo[i].doubleRand = clock() - timer; // Rand Test

        int** matrix = new int*[100];
        timer = clock();
        for (int count = 0; count < 100; count++)
        {
            matrix[count] = new int[100];
            for (int count1 = 0; count1 < 100; count1++)
            {
                matrix[count][count1] = rand() % 100;
            }
        }
        benchmarkInfo[i].intRandMatrix = clock() - timer; // Rand Matrix Test

        benchmarkInfo[i].totalTest = clock() - globalVectorTimer; // Total Test
    }

    double minTest = benchmarkInfo[0].totalTest;
    double maxTest = benchmarkInfo[0].totalTest;;
    double averageTest = 0;
    for (int i = 0; i < numberTasks; i++)
    {
        if (minTest > benchmarkInfo[i].totalTest) minTest = benchmarkInfo[i].totalTest;
        if (maxTest < benchmarkInfo[i].totalTest) maxTest = benchmarkInfo[i].totalTest;
        averageTest += benchmarkInfo[i].totalTest;
    }
    std::cout << "Total test  " << " Min: " << minTest << " Max: " << maxTest << " Average: " << averageTest / numberTasks << std::endl;

    minTest = benchmarkInfo[0].insertVector;
    maxTest = benchmarkInfo[0].insertVector;;
    averageTest = 0;
    for (int i = 0; i < numberTasks; i++)
    {
        if (minTest > benchmarkInfo[i].insertVector) minTest = benchmarkInfo[i].insertVector;
        if (maxTest < benchmarkInfo[i].insertVector) maxTest = benchmarkInfo[i].insertVector;
        averageTest += benchmarkInfo[i].insertVector;
    }
    std::cout << "Insert vector test  " << " Min: " << minTest << " Max: " << maxTest << " Average: " << averageTest / numberTasks << std::endl;

    minTest = benchmarkInfo[0].eraceVector;
    maxTest = benchmarkInfo[0].eraceVector;;
    averageTest = 0;
    for (int i = 0; i < numberTasks; i++)
    {
        if (minTest > benchmarkInfo[i].eraceVector) minTest = benchmarkInfo[i].eraceVector;
        if (maxTest < benchmarkInfo[i].eraceVector) maxTest = benchmarkInfo[i].eraceVector;
        averageTest += benchmarkInfo[i].eraceVector;
    }
    std::cout << "Erace vector test  " << " Min: " << minTest << " Max: " << maxTest << " Average: " << averageTest / numberTasks << std::endl;

    minTest = benchmarkInfo[0].doubleRand;
    maxTest = benchmarkInfo[0].doubleRand;;
    averageTest = 0;
    for (int i = 0; i < numberTasks; i++)
    {
        if (minTest > benchmarkInfo[i].doubleRand) minTest = benchmarkInfo[i].doubleRand;
        if (maxTest < benchmarkInfo[i].doubleRand) maxTest = benchmarkInfo[i].doubleRand;
        averageTest += benchmarkInfo[i].doubleRand;
    }
    std::cout << "Double rand test  " << " Min: " << minTest << " Max: " << maxTest << " Average: " << averageTest / numberTasks << std::endl;

    minTest = benchmarkInfo[0].intRandMatrix;
    maxTest = benchmarkInfo[0].intRandMatrix;;
    averageTest = 0;
    for (int i = 0; i < numberTasks; i++)
    {
        if (minTest > benchmarkInfo[i].intRandMatrix) minTest = benchmarkInfo[i].intRandMatrix;
        if (maxTest < benchmarkInfo[i].intRandMatrix) maxTest = benchmarkInfo[i].intRandMatrix;
        averageTest += benchmarkInfo[i].intRandMatrix;
    }
    std::cout << "Rand matrix test  " << " Min: " << minTest << " Max: " << maxTest << " Average: " << averageTest / numberTasks << std::endl;
}
int main() 
{
    srand(time(0));

    int numberTasks;
    ID* benchmarkInfo;

    std::cin >> numberTasks;

    benchmarkInfo = new ID[numberTasks];

    Test(benchmarkInfo, numberTasks);
}

