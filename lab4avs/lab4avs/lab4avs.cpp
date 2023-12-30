#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

const int sizeblock = 100;

void DGEMMBLAS(double* matrix1, double* matrix2, double* matrixresult, int size)
{
	int i;
	int j;
	int k;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			for (k = 0; k < size; k++) {
				*(matrixresult + i * size + j) += *(matrix1 + i * size + k) * *(matrix2 + k * size + j);
			}
		}
	}
}

void DGEMMOPT1(double* matrix1, double* matrix2, double* matrixresult, int size)
{
	int i;
	int j;
	int k;
	for (i = 0; i < size; i++)
	{
		for (k = 0; k < size; k++)
		{
			for (j = 0; j < size; j++)
			{
				*(matrixresult + i * size + j) += *(matrix1 + i * size + k) * *(matrix2 + k * size + j);
			}
		}
	}
}

void DGEMMOPT2(double* matrix1, double* matrix2, double* matrixresult, int size, int block)
{
	int i0;
	int j0;
	int k0;
	int *matrixresult_0 = new int[size];
	int *matrix1_0 = new int[size];
	int *matrix2_0 = new int[size];
	for (int i = 0; i < size; i += block)
	{
		for (int j = 0; j < size; j += block)
		{
			for (int k = 0; k < size; k += block)
			{
				for (i0 = 0, *matrixresult_0 = *(matrixresult + i * size + j), *matrix1_0 = *(matrix1 + i * size + k); i0 < block; ++i0, *matrixresult_0 += size, *matrix1_0 += size)
				{
					for (k0 = 0, *matrix2_0 = *(matrix2 + k * size + j); k0 < block; ++k0, *matrix2_0 += size)
					{
						for (j0 = 0; j0 < block; ++j0)
						{
							matrixresult_0[j0] += matrix1_0[k0] * matrix2_0[j0];
						}
					}
				}
			}
		}
	}
}

void MatrixRand(double* matrix, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			for (int k = 0; k < size; k++)
			{
				*(matrix + i * size + j) = rand() % 100;
			}
		}
	}
}

void MatrixZero(double* matrix, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			for (int k = 0; k < size; k++)
			{
				*(matrix + i * size + j) = 0;
			}
		}
	}
}

void MatrixPrint(double* a, int size)
{
	printf("Matrix:\n");
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf("%.2f  ", *(a + i * size + j));
		}
		printf("\n");
	}
}

void Test()
{
	int N = 10;
	for (int i = 1; i < N + 1; i++)
	{
		struct timespec timebegin, timeend;
		long int timeresult = 0;
		long int time[8];
		int size = sizeblock * i;

		double *matrix1 = new double[size * size];
		double *matrix2 = new double[size * size];
		double *matrixresult = new double[size * size];

		MatrixRand(matrix1, size);
		MatrixRand(matrix2, size);
		MatrixZero(matrixresult, size);

		clock_gettime(CLOCK_REALTIME, &timebegin);
		DGEMMBLAS(matrix1, matrix2, matrixresult, size);
		clock_gettime(CLOCK_REALTIME, &timeend);
		timeresult = pow(10, 9) * (timeend.tv_sec - timebegin.tv_sec) + (timeend.tv_nsec - timebegin.tv_nsec);
		time[0] = timeresult;
		//printf("DGEMMBLAS = %f\n", (double)timeresult / pow(10, 9));

		MatrixZero(matrixresult, size);

		clock_gettime(CLOCK_REALTIME, &timebegin);
		DGEMMOPT1(matrix1, matrix2, matrixresult, size);
		clock_gettime(CLOCK_REALTIME, &timeend);
		timeresult = pow(10, 9) * (timeend.tv_sec - timebegin.tv_sec) + (timeend.tv_nsec - timebegin.tv_nsec);
		time[1] = timeresult;
		//printf("DGEMMOPT1 = %f\n", (double)timeresult / pow(10, 9));

		for (int j = 1; j < 6 + 1; j++)
		{
			MatrixZero(matrixresult, size);

			int block = pow(2, j);
			clock_gettime(CLOCK_REALTIME, &timebegin);
			DGEMMOPT2(matrix1, matrix2, matrixresult, size, block);
			clock_gettime(CLOCK_REALTIME, &timeend);
			timeresult = pow(10, 9) * (timeend.tv_sec - timebegin.tv_sec) + (timeend.tv_nsec - timebegin.tv_nsec);
			time[j + 1] = timeresult;
			//printf("time block= %f\n", (double)tt / pow(10, 9));
		}
		FILE* file;
		file = fopen("test.cvs", "a");
		fprintf(file, "\n");
		for (int j = 0; j < 8; j++)
		{
			fprintf(file, "%ld;", time[j]);
		}
		fclose(file);
	}

}

int main()
{
	Test();
	return 0;
}