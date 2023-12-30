#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

#define m 1000
#define n 1000
double lNum = 10.0;
void Vector(float* matrix, float* vector, float* vectorIt)
{
    for (int i = 0; i < m; i++)
    {
        vectorIt[i] = 0.0;
        for (int j = 0; j < n; j++)
            vectorIt[i] += matrix[i * n + j] * vector[j];
    }
}

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

double test()
{
    srand(time(0));
    float* matrix, * vector, * vectorIt;
    matrix = malloc(sizeof(*matrix) * m * n);
    vector = malloc(sizeof(*vector) * n);
    vectorIt = malloc(sizeof(*vectorIt) * n);

    double t;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            matrix[i * n + j] = rand() % 1000;
    }
    for (int j = 0; j < n; j++)
        vector[j] = rand() % 1000;

    t = wtime();
    Vector(matrix, vector, vectorIt);
    t = (wtime() - t);
    //printf("Elapsed time (serial): %.6f sec.\n", t);
    free(matrix);
    free(vector);
    free(vectorIt);
    return t;
}

void Math()
{
    double dispersion = 0, average = 0, deviation = 0, taskPerf = 0, absError = 0, relError = 0;
    int insCount = n * (m + (n - 1)) + m;
    double testAr[10];
    double t = test();

    for (int i = 0; i < 10; i++)
    {
        testAr[i] += test();
        average += testAr[i];
    }

    for (int i = 0; i < 10; i++)
    {
        testAr[i] = test();
        average += testAr[i];
        taskPerf += (insCount / testAr[i]);
        dispersion += pow(testAr[i] - average, 2);
    }

    taskPerf = pow((1 / taskPerf), -1);

    deviation = sqrt(dispersion / lNum);
    average /= lNum;//среднеквадратичное отклонение
    absError = average - t;
    relError = (absError / average) * 100;

    FILE* file;

    file = fopen("itog.cvs", "a");
    fprintf(file, "PModel: Intel(R) Core(TM) i3-6006U CPU @ 2.00GHz \n");
    fprintf(file, "Task: multiplying a matrix by a vector OpType: -O \nOpt float\nInsCount %d \n", insCount);
    fprintf(file, "Timer: time()\nTime: %.6f \nLNum: 10 \nAvTime: %.6f \nAbsErr: %.6f \n", t, average, absError);
    fprintf(file, "RelErr: %.6f \nTaskPer: %.2f % \n\n", relError, taskPerf);
    fclose(file);
}

int main()
{
    Math();
    return 0;
}
