import numpy as np
import Gauss as gs

def calculation_approximation(equation, termsX, termsY):
    sumDegreeX = calculation_sum_degree_x(equation, termsX)
    B = calculation_B(equation, termsX, termsY)

    matrix = make_matrix(equation, B, sumDegreeX)

    approxEquation = gs.method(matrix)

    pointsY = np.zeros(len(termsX))
    for i in range(len(termsX)):
        pointsY[i] += approxEquation[0]
        for j in range(1, len(equation)):
            pointsY[i] += pow(termsX[i], j) * approxEquation[j]
          
    return pointsY

def calculation_sum_degree_x(equation, termsX):
    sumDegreeX = np.zeros(len(equation) + 2)
    for i in range(len(sumDegreeX)):
        for j in range(len(termsX)):
            sumDegreeX[i] += pow(termsX[j], i)

    return sumDegreeX

def calculation_B(equation, termsX, termsY):
    B = np.zeros(len(equation))
    for i in range(len(B)):
        for j in range(len(termsY)):
            B[i] += pow(termsX[j], i) * termsY[j]

    return B

def make_matrix(equation, B, sumDegreeX):
    matrix = np.empty((len(equation), len(B) + 1))
    for i in range(matrix.shape[0]):
        matrix[i][matrix.shape[0]] = B[i]

    for i in range(matrix.shape[0]):
        for j in range(matrix.shape[0]):
            matrix[i][j] = sumDegreeX[j + i]

    return matrix
