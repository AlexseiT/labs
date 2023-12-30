#!/usr/bin/env python
# -*- coding: cp1251 -*-
import numpy as np
import pandas as pd

def EuclideanDistance(x1,y1,x2,y2):
    h = np.sqrt((y1-x1)^2 + (y2-x2)^2)
    return h

def SplitData(dataFrame, sizeTest, dataSize):

    xPointTest = dataFrame['MrotInHour'][0:sizeTest].values
    yPointTest = dataFrame['Salary'][0:sizeTest].values
    classPointTest = dataFrame['Class'][0:sizeTest].values
    
    xPointTraining = dataFrame['MrotInHour'][sizeTest:dataSize].values
    yPointTraining = dataFrame['Salary'][sizeTest:dataSize].values
    classPointTraining = dataFrame['Class'][sizeTest:dataSize].values
    
    testStructs = np.vstack((xPointTest, yPointTest,classPointTest))
    trainingStructs = np.vstack((xPointTraining, yPointTraining,classPointTraining))

    return testStructs, trainingStructs

def CalculateWeight(structs, i, index, h, classFirst, classZero, direction):

    hTemp = EuclideanDistance(structs[0][index], structs[1][index], structs[0][i + direction], structs[1][i + direction])
    r = hTemp / h # Относительное расстояние
    if r <= 1:
        K = (1 - r ** 2) ** 2 # Квартическое ядро
        if structs[2][i + direction] == 1:
            classFirst += K
        else:
            classZero += K

    return classFirst, classZero

def ParsenovWindowMethod(structs, h, size):
    index = 0
    correctCounter = 0
    while index != (size - 1):
        classZero = 0
        classFirst = 0
        for i in range(index, 0, -1):
            classFirst, classZero = CalculateWeight(structs, i, index, h, classFirst, classZero, -1)

        for i in range(index, size - 1, 1):
            classFirst, classZero = CalculateWeight(structs, i, index, h, classFirst, classZero, 1)

        if classFirst > classZero:
            predict = 1
        else:
            predict = 0
        if structs[2][index] == predict:
            correctCounter += 1
        index += 1
    return correctCounter

def main():
    h = int(input("Введите значение окна h: "))

    dataFrame = pd.read_csv('data1.csv')
    dataSize = len(dataFrame['Salary'])
    sizeTest = int(dataSize / 3)
    testStructs, trainingStructs = SplitData(dataFrame, sizeTest, dataSize)


    resultFile = open("result"+str(h)+".txt", "w")
    print("\nРабота программы:\n")
    resultFile.write("\nРабота программы:\n")
    resultFile.write("Размер окна h = "+ str(h)+"\n")
    correctClassPoints = ParsenovWindowMethod(trainingStructs, h, 2 * sizeTest)
    correctClassPoints = correctClassPoints / (2 * sizeTest) * 100
    print("Точность на тренировочном наборе данных: " + str(correctClassPoints) + "%\n")
    resultFile.write("Точность на тренировочном наборе данных: " + str(correctClassPoints) + "%\n")


    correctClassPoints = ParsenovWindowMethod(testStructs, h, sizeTest)
    correctClassPoints = correctClassPoints / sizeTest * 100
    print("Точность на тестовом наборе данных: " + str(correctClassPoints) + "%\n")
    resultFile.write("Точность на тестовом наборе данных: " + str(correctClassPoints) + "%\n")

    resultFile.close()

if __name__ == '__main__':
    main()