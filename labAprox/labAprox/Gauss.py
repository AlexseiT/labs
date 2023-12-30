import numpy as np

def method(matrix):
    n = len(matrix)
    a = matrix.copy()
    x = np.zeros(n)

    for i in range(n):
        if a[i][i] == 0.0:
            print('Divide by zero')
            break
        
        for j in range(i+1, n):
            ratio = a[j][i]/a[i][i]
        
            for k in range(n+1):
                a[j][k] = a[j][k] - ratio * a[i][k]

    x[n-1] = a[n-1][n]/a[n-1][n-1]

    for i in range(n-2,-1,-1):
        x[i] = a[i][n]
    
        for j in range(i+1,n):
            x[i] = x[i] - a[i][j]*x[j]
    
        x[i] = x[i]/a[i][i]

    return x

def link_to_Gauss_matrix(matrix, array):
    gaussMatrix = np.empty((len(matrix), len(matrix[0]) + 1))

    for i in range(len(gaussMatrix)):
        for j in range(len(matrix[0])):
            gaussMatrix[i][j] = matrix[i][j]
        gaussMatrix[i][len(gaussMatrix[0]) - 1] = array[i]

    return gaussMatrix