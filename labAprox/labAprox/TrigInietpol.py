import numpy as np
import math

def calculation_inter(x, termsX, termsY):
    h = termsX[1] - termsX[0]
    n = len(termsX)
    T = h * n
    A = []
    
    elemA = 0   
    for i in range(int(-n/2) + 1, int(n/2) + 1):
        for k in range(n):
            coefDegree = -2 * math.pi * (k * i) / (n)
            elemA += termsY[k] * (math.cos(coefDegree) + 1j * math.sin(coefDegree))
        A.append(elemA)
        elemA = 0
    
    answer = 0
    index = 0
    for i in range(int(-n/2) + 1, int(n/2) + 1):
        coefDegree = 2 * math.pi * i * (x - termsX[0]) / (T)
        answer += A[index] * (math.cos(coefDegree) + 1j * math.sin(coefDegree))
        index += 1

    answer *= 1 / n
    return answer

