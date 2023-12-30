# -*- coding: utf-8 -*-
import math
import matplotlib.pyplot as plt

e = 0.01


class DiffUr:
    def __init__(self):
        self.x0 = 0
        self.y0 = 0.8
        self.xn = 1
        self.yn = 0.691149
        self.a = 0
        self.b = 2
        self.h = 0.05
        self.result = []

    def f(self, x, y, dy):
         return (math.exp(x) + y + dy) / 3

    #def f(self, x, y, dy):
     #   return math.cos(3*x) - 4*y

    def g(self, x, y, dy):
        return dy

    def runge_cutta(self, x, y, dy):
        resultK = dy
        resultQ = y

        k1 = self.h * self.f(x, y, dy)
        q1 = self.h * self.g(x, y, dy)

        k2 = self.h * self.f(x + self.h / 2.0, y + q1 / 2.0, dy + k1 / 2.0)
        q2 = self.h * self.g(x + self.h / 2.0, y + q1 / 2.0, dy + k1 / 2.0)

        k3 = self.h * self.f(x + self.h / 2.0, y + q2 / 2.0, dy + k2 / 2.0)
        q3 = self.h * self.g(x + self.h / 2.0, y + q2 / 2.0, dy + k2 / 2.0)

        k4 = self.h * self.f(x + self.h, y + q3, dy + k3)
        q4 = self.h * self.g(x + self.h, y + q3, dy + k3)

        resultK += (k1 + 2.0 * k2 + 2.0 * k3 + k4) / 6.0
        resultQ += (q1 + 2.0 * q2 + 2.0 * q3 + q4) / 6.0

        return [resultK, resultQ]

    def decide(self, Y0):
        self.result.clear()
        xi = 0
        t = 0
        y = Y0[0]
        dy = Y0[1]
        count = 0

        while t < self.xn:
            result = self.runge_cutta(t, y, dy)
            t += self.h
            dy = result[0]
            y = result[1]
            self.result.append([t, y, dy])

        dif = 100
        while dif > (15 * e):
            self.h = self.h / 2
            t = 0
            self.result.clear()
            y = Y0[0]
            dy = Y0[1]
            while t < self.xn:
                result = self.runge_cutta(t, y, dy)
                t += self.h
                dy = result[0]
                y = result[1]
                self.result.append([t, y, dy])
            count += 1
            dif = self.result[-1][1] - self.result[-2][1]


        print("Iterations = ", count)

        self.h = 0.05
        return [y, dy]

    def print(self):
        X = []
        Y = []
        DY = []
        inX = []
        for i in range(len(self.result)):
            X.append(self.result[i][0])
            Y.append(self.result[i][1])
            DY.append(self.result[i][2])
            inX.append(self.FFF(X[i]) - 0.1)

        plt.plot(X, Y, label="Y")
        plt.plot(X, DY, label="DY")
        plt.plot(X, inX, label="Right")
        plt.legend()
        for i in range(len(self.result)):
            print(self.result[i])
        plt.show()

    def calculate(self):
        Y0 = [self.y0, self.a]
        ya = self.decide(Y0)[0]
        Y0 = [self.y0, self.b]
        yb = self.decide(Y0)[0]

        while abs(yb-ya) > e:
            self.c = (self.b + self.a) / 2
            Y0 = [self.y0, self.c]
            yc = self.decide(Y0)[0]
            if self.yn - yc < 0:
                self.b = self.c
                yb = yc
            else:
                self.a = self.c
                ya = yc

        self.print()

    def FFF(self, x):
        return -math.cos(3*x)/5 + math.sin(2*x) + math.cos(2*x)


app = DiffUr()
app.calculate()