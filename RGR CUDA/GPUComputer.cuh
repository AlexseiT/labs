#ifndef GPUCOMPUTER
#define GPUCOMPUTER

#include <stdlib.h>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <fstream>

#include "GPUÑlasses.cuh"

class GPUComputer
{
private:

	float* matrixFirst;
	float* matrixSecond;
	float* matrixResult;

	float* deviceMatrixFirst;
	float* deviceMatrixSecond;
	float* deviceMatrixResult;

	int matrixSize;
	int numberEements;
	int blockSize;
	int tileSize;

	SimpleCUDA simpleCUDA;
	Thrust thrust;
	Cublas cublas;

	float timeSimpleCUDA;
	float timeThrust;
	float timeCublas;
	int coeff;
	bool check;
public:

	GPUComputer(int coeff, int size = MATRIX, bool check = false, int block = BLOCK)
	{
		this->check = check;
		this->coeff = coeff - 4;
		matrixSize = size;
		numberEements = matrixSize * matrixSize;
		blockSize = block;
		tileSize = blockSize * 2;

		matrixFirst = (float*)malloc(numberEements * sizeof(float));
		matrixSecond = (float*)malloc(numberEements * sizeof(float));
		matrixResult = (float*)malloc(numberEements * sizeof(float));

		InitializeMatrix(matrixFirst);
		this_thread::sleep_for(chrono::seconds(1));
		InitializeMatrix(matrixSecond);
		ZeroMatrix(matrixResult);

		cudaMalloc(&deviceMatrixFirst, numberEements * sizeof(float));
		cudaMalloc(&deviceMatrixSecond, numberEements * sizeof(float));
		cudaMalloc(&deviceMatrixResult, numberEements * sizeof(float));

		cudaMemcpy(deviceMatrixFirst, matrixFirst, numberEements * sizeof(float), cudaMemcpyHostToDevice);
		cudaMemcpy(deviceMatrixSecond, matrixSecond, numberEements * sizeof(float), cudaMemcpyHostToDevice);

		simpleCUDA.SetParams(matrixSize, numberEements, blockSize, tileSize);
		thrust.SetParams(matrixSize, numberEements, blockSize, tileSize);
		cublas.SetParams(matrixSize, numberEements, blockSize, tileSize);
	}
	void InitializeMatrix(float* matrix)
	{
		srand(time(NULL));
		for (int i = 0; i < numberEements; i++)
		{
			matrix[i] = (float)(rand() % 90 + 10);
		}
	}
	void ZeroMatrix(float* matrix)
	{
		for (int i = 0; i < numberEements; i++)
		{
			matrix[i] = 0.0f;
		}
	}
	void PrintMatrix(float* matrix, string handle)
	{
		cout << handle << endl;
		for (int i = 0; i < matrixSize; i++)
		{
			for (int j = 0; j < matrixSize; j++)
			{
				cout << matrix[i * matrixSize + j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	void PrintResult(string handler)
	{
		cout << handler << endl << endl;
		cout << "Simple CUDA: time = " << timeSimpleCUDA * 10 * coeff << " ms" << endl;
		cout << "     Thrust: time = " << timeThrust << " ms" << endl;
		cout << "     Cublas: time = " << timeCublas << " ms" << endl;
		cout << endl;
	}
	//void CheckError(float* matrix, float* matrixResult)
	//{
	//	bool checkError = true;
	//	float* expected_matrix = (float*)malloc(numberEements * sizeof(float));
	//	for (int i = 0; i < matrixSize; i++)
	//		for (int j = 0; j < matrixSize; j++)
	//			expected_matrix[j * matrixSize + i] = matrix[i * matrixSize + j];

	//	for (int i = 0; i < matrixSize; i++)
	//	{
	//		for (int j = 0; j < matrixSize; j++)
	//			if (matrixResult[i * matrixSize + j] != expected_matrix[i * matrixSize + j])
	//			{
	//				checkError = false;
	//				break;
	//			}
	//		if (!checkError)
	//			break;
	//	}

	//	if (checkError) cout  << "SUCCESS" << endl;
	//	else cout << "FAILURE" << endl;
	//}

	void TranspositionBenchmark()
	{
		//if (check) PrintMatrix(matrixFirst, "matrix");

		ZeroMatrix(matrixResult);
		simpleCUDA.Transpose(deviceMatrixFirst, deviceMatrixResult);
		cudaMemcpy(matrixResult, deviceMatrixResult, numberEements * sizeof(float),cudaMemcpyDeviceToHost);

		ZeroMatrix(matrixResult);
		thrust.Transpose(deviceMatrixFirst, deviceMatrixResult);
		cudaMemcpy(matrixResult, deviceMatrixResult, numberEements * sizeof(float),cudaMemcpyDeviceToHost);

		ZeroMatrix(matrixResult);
		cublas.Transpose(deviceMatrixFirst, deviceMatrixResult);
		cudaMemcpy(matrixResult, deviceMatrixResult, numberEements * sizeof(float),cudaMemcpyDeviceToHost);

		//if (check) PrintMatrix(matrixResult, "transpose matrix");
		timeSimpleCUDA = simpleCUDA.GetTime();
		timeThrust = thrust.GetTime();
		timeCublas = cublas.GetTime();
	}
	void MultiplicationBenchmark()
	{
		if (check) PrintMatrix(matrixFirst, "matrix A");
		if (check) PrintMatrix(matrixSecond, "matrix B");

		ZeroMatrix(matrixResult);
		simpleCUDA.Multiply(deviceMatrixFirst,deviceMatrixSecond,deviceMatrixResult);
		cudaMemcpy(matrixResult, deviceMatrixResult, numberEements * sizeof(float),cudaMemcpyDeviceToHost);

		//if (check) PrintMatrix(matrixResult, "result matrix");

		ZeroMatrix(matrixResult);
		thrust.Multiply(deviceMatrixFirst,deviceMatrixSecond, deviceMatrixResult);
		cudaMemcpy(matrixResult, deviceMatrixResult, numberEements * sizeof(float),cudaMemcpyDeviceToHost);

		ZeroMatrix(matrixResult);
		cublas.Multiply(deviceMatrixFirst,deviceMatrixSecond, deviceMatrixResult);
		cudaMemcpy(matrixResult, deviceMatrixResult, numberEements * sizeof(float),cudaMemcpyDeviceToHost);

		//if (check) PrintMatrix(matrixResult, "A * B");

		timeSimpleCUDA = simpleCUDA.GetTime();
		timeThrust = thrust.GetTime();
		timeCublas = cublas.GetTime();

	}
	void Testing()
	{
		cout << "---------------------------" << endl << endl;
		cout << matrixSize <<" x "<< matrixSize << endl << endl;
		TranspositionBenchmark();
		PrintResult("<<< Transposing >>>");
		MultiplicationBenchmark();
		PrintResult("<<< Multiplication >>>");
		cout << "---------------------------" << endl;
	}
};
#endif