import numpy as np

import Gauss

def calculation_spline(x, termsX, termsY):
    h = calculation_lens_intervals(termsX)
    C = calculation_C(h)
    d = calculation_d(termsY, h)
    M = calculation_M(C, d)

    indexInterval = search_index_interval(x, termsX)

    spline = 0
    spline += M[indexInterval - 1] * (termsX[indexInterval] - x) ** 3 / (6 * h[indexInterval - 1])  
    spline += M[indexInterval] * (x - termsX[indexInterval - 1]) ** 3 / (6 * h[indexInterval - 1])
    spline += (termsY[indexInterval - 1] - (M[indexInterval - 1] * h[indexInterval - 1] ** 2) / (6)) * (termsX[indexInterval] - x) / (h[indexInterval - 1])
    spline += (termsY[indexInterval] - (M[indexInterval] * h[indexInterval - 1] ** 2) / (6)) * (x - termsX[indexInterval - 1]) / (h[indexInterval - 1])

    return spline

def search_index_interval(x, termsX):
    indexInterval = 0

    for i in range(len(termsX) - 1):
        if x >= termsX[i] and x <= termsX[i + 1]:
            indexInterval = i + 1
            break

    return indexInterval

def calculation_lens_intervals(termsX):
    h = np.empty(len(termsX) - 1)

    for i in range(len(termsX) - 1):
        h[i] = termsX[i + 1] - termsX[i]

    return h

def calculation_C(h):
    C = np.zeros((len(h) - 1, len(h) - 1))

    for i in range(len(C)):
        for j in range(len(C[0])):
            if i == j: 
                C[i][j] = (h[i] + h[i + 1]) / 3
            elif j == i + 1:
                C[i][j] = h[i + 1] / 6
            elif j == i - 1:
                C[i][j] = h[i] / 6
            else:
                C[i][j] = 0

    return C

def calculation_d(termsY, h):
    d = np.empty(len(h) - 1)

    for i in range(1, len(d) + 1):
        d[i - 1] = (termsY[i + 1] - termsY[i]) / h[i] - (termsY[i] - termsY[i - 1]) / h[i - 1]

    return d

def calculation_M(C, d):
    M = np.zeros(len(d) + 2)

    termsM = Gauss.method(Gauss.link_to_Gauss_matrix(C, d))

    for i in range(1, len(M) - 1):
        M[i] = termsM[i - 1]

    return M