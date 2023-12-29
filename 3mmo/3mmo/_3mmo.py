#!/usr/bin/env python
# -*- coding: cp1251 -*-
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LassoCV
from sklearn.preprocessing import StandardScaler
import matplotlib.pyplot as plt

def Learn(x,y, count):
    result = 0
    resultAccuracy = []
    for _ in range(count):
        x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.3)
        model = LassoCV()
        model.fit(x_train, y_train)
        predict = model.predict(x_test)

        success = 0
        for i in range(len(x_test)):
            if abs(y_test[i] - predict[i]) < 1:
                success += 1
        print(f'ACCURACY: {success / len(x_test) * 100:.4}%')
        resultAccuracy.append(success / len(x_test) * 100)
        result += success / len(x_test) * 100

    print(f'AVERAGE ACCURACY: {result / 10:.4}%\n')

    return resultAccuracy


if __name__ == '__main__':

    white = 0

    data = pd.read_csv('winequalityN.csv', header=0).fillna(0).values
    scaler = StandardScaler()
    count = 10
    for i in data:
        if i[0] == 'white':
            i[0] = 0
            white += 1
        else:
            i[0] = 1


    x = data[:, 0:12]
    y = data[:, 12]
    x = scaler.fit_transform(x)

    print(f'ALL:')
    allresult = Learn(x,y,count)

    x = data[0:white, 0:12]
    y = data[0:white, 12]
    x = scaler.transform(x)

    print(f'WHITE:')
    whiteresult = Learn(x,y,count)

    x = data[white:, 0:12]
    y = data[white:, 12]
    x = scaler.transform(x)

    print(f'RED:')
    redresult = Learn(x,y,count)

    plt.figure(figsize=(8, 6))
    plt.plot(range(2, count+2), allresult, label='Все')
    plt.plot(range(2, count+2), whiteresult, label='Белые')
    plt.plot(range(2, count+2), redresult, label='Красные')
    plt.xlabel('Номер итерации')
    plt.ylabel('Точность')
    plt.legend()
    plt.show()