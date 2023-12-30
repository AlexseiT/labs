#ifndef GPUHANDLER
#define GPUHANDLER

#include <thrust/device_vector.h>
#include <thrust/iterator/zip_iterator.h>
#include <thrust/tuple.h>
#include <thrust/functional.h>
#include <thrust/transform.h>
#include <thrust/execution_policy.h>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <cuda_runtime.h>
#include <cublas_v2.h>
#include "device_launch_parameters.h"

using namespace std;

#define MATRIX 512
#define BLOCK 32 

class GPU
{
protected:

    float time = 0.0f;

    cudaEvent_t start;
    cudaEvent_t stop;

    int matrixSize;
    int numberEements;
    int blockSize;
    int tileSize;

public:
    float GetTime()
    {
        return time;
    }
    void SetParams(int size, int number, int block, int title)
    {
        matrixSize = size;
        numberEements = number;
        blockSize = block;
        tileSize = title;
    }
};

class Thrust : public GPU
{
private:
public:
    void Transpose(float* matrix, float* matrixResult)
    {
        cudaEventCreate(&start);
        cudaEventCreate(&stop);
        cudaEventRecord(start);

        thrust::device_vector<float> input(numberEements);
        thrust::device_vector<float> output(numberEements);

        thrust::copy(matrix, matrix + numberEements, input.begin());

        thrust::counting_iterator<int> begin(0);
        int size = matrixSize;
        auto iterator = thrust::make_permutation_iterator(input.begin(), thrust::make_transform_iterator(begin, [=] __host__ __device__(int i) mutable
        {
            int row = i / size;
            int col = i % size;
            return col * size + row;
        }));

        thrust::copy(iterator, iterator + numberEements, output.begin());
        thrust::copy(output.begin(), output.end(), matrixResult);

        cudaEventRecord(stop);
        cudaEventSynchronize(stop);
        cudaEventElapsedTime(&time, start, stop);
    }
    void Multiply(float* matrixFirst, float* matrixSecond, float* matrixResult)
    {
        cudaEventCreate(&start);
        cudaEventCreate(&stop);
        cudaEventRecord(start);

        thrust::device_ptr<float> deviceMatrixFirst(matrixFirst);
        thrust::device_ptr<float> deviceMatrixSecond(matrixSecond);
        thrust::device_ptr<float> deviceMatrixResult(matrixResult);

        thrust::counting_iterator<int> begin(0);
        thrust::counting_iterator<int> end = begin + matrixSize * matrixSize;
        int size = matrixSize;
        thrust::transform(begin, end, deviceMatrixResult, [deviceMatrixFirst, deviceMatrixSecond, size] __device__(int index) -> float
        {
            int row = index / size;
            int col = index % size;
            float sum = 0.0f;
            for (int i = 0; i < size; i++)
            {
                sum += deviceMatrixFirst[row * size + i] * deviceMatrixSecond[i * size + col];
            }
            return sum;
        });
        cudaEventRecord(stop);
        cudaEventSynchronize(stop);
        cudaEventElapsedTime(&time, start, stop);
    }
};
class Cublas : public GPU
{
private:
    float alpha = 1.0f;
    float beta = 0.0f;
public:
    void Transpose(float* matrix, float* matrixResult)
    {
        cudaEventCreate(&start);
        cudaEventCreate(&stop);

        cublasHandle_t handle;
        cublasCreate(&handle);

        cudaEventRecord(start);
        cublasSgeam(handle, CUBLAS_OP_T, CUBLAS_OP_N, matrixSize, matrixSize, &alpha, matrix, matrixSize, &beta, matrix, matrixSize, matrixResult, matrixSize);
        cudaEventRecord(stop);
        cudaEventSynchronize(stop);
        cudaEventElapsedTime(&time, start, stop);

        cublasDestroy(handle);
    }
    void Multiply(float* matrixFirst, float* matrixSecond, float* matrixResult)
    {

        cublasHandle_t handle;
        cublasCreate(&handle);

        cudaEventCreate(&start);
        cudaEventCreate(&stop);
        cudaEventRecord(start);

        cublasSgemm(handle, CUBLAS_OP_N, CUBLAS_OP_N, matrixSize, matrixSize, matrixSize, &alpha, matrixSecond, matrixSize, matrixFirst, matrixSize, &beta, matrixResult, matrixSize);

        cudaEventRecord(stop);
        cudaEventSynchronize(stop);
        cudaEventElapsedTime(&time, start, stop);

        cublasDestroy(handle);
    }
};

__global__ void KernelTranspose(float* matrix, float* matrixResult, int matrixSize)
{
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x < matrixSize && y < matrixSize)
    {
        int index_in = y * matrixSize + x;
        int index_out = x * matrixSize + y;
        matrixResult[index_out] = matrix[index_in];
    }
}
__global__ void KernelMultiply(float* matrixFirst, float* matrixSecond, float* matrixResult, int matrixSize)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < matrixSize && col < matrixSize)
    {
        float sum = 0.0f;
        for (int i = 0; i < matrixSize; i++)
        {
            sum += matrixFirst[row * matrixSize + i] * matrixSecond[i * matrixSize + col];
        }
        matrixResult[row * matrixSize + col] = sum;
    }
}
class SimpleCUDA : public GPU
{
private:
public:
    void Transpose(float* matrix, float* matrixResult)
    {
        cudaEventCreate(&start);
        cudaEventCreate(&stop);
        cudaEventRecord(start);

        dim3 dimGrid((matrixSize - 1) / blockSize + 1, (matrixSize - 1) / blockSize + 1);
        dim3 dimBlock(tileSize, blockSize, 1);

        KernelTranspose <<< dimGrid, dimBlock >>> (matrix, matrixResult, matrixSize);
        cudaEventRecord(stop);
        cudaEventSynchronize(stop);
        cudaEventElapsedTime(&time, start, stop);
    }
    void Multiply(float* matrixFirst, float* matrixSecond, float* matrixResult)
    {
        cudaEventCreate(&start);
        cudaEventCreate(&stop);
        cudaEventRecord(start);

        dim3 dimGrid((matrixSize - 1) / blockSize + 1, (matrixSize - 1) / blockSize + 1);
        dim3 dimBlock(tileSize, blockSize, 1);

        KernelMultiply << < dimGrid, dimBlock >> > (matrixFirst, matrixSecond, matrixResult, matrixSize);

        cudaEventRecord(stop);
        cudaEventSynchronize(stop);
        cudaEventElapsedTime(&time, start, stop);
    }
};
#endif