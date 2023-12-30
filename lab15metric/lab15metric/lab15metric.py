#!/usr/bin/env python
# -*- coding: cp1251 -*-

import math

def calculate_metrics(eta_2):
    k = eta_2 / 8
    i = 0
    total_modules = 0

    if k > 8:
        i = 1
        while k > 8:
            k /= 8
            i += 1
        total_modules = k * (8 ** i)
    else:
        total_modules = eta_2

    N = 2 ** total_modules
    V = N * eta_2

    k_2 = eta_2
    P = N * (math.log(k_2, 2) / 8)

    n = 5
    v = 20

    Tk = V / (n * v)
    tau = 0.5 * Tk
    B = tau / Tk

    t_n = math.exp(-B)

    return i, total_modules, N, V, P, Tk, B, t_n

values_of_eta_2 = [300, 400, 512]

for eta_2 in values_of_eta_2:
    i, total_modules, N, V, P, Tk, B, t_n = calculate_metrics(eta_2)
    print(f"����������� �������������� ��� eta_2 = {eta_2}:")
    print("------------------------------------------------")
    print(f"����� ������ ��������: {i}")
    print(f"����� ���-�� ������� � PS: {total_modules}")
    print(f"����� ��������� N: {N}")
    print(f"����� V PS:{V}")
    print(f"����� PS � ���������� ������ ���������� P: {P}")
    print(f"����� ���������������� ��������� Tk: {Tk}")
    print(f"��������� ���������� ������ B: {B}")
    print(f"�������������� ���������� ����:{t_n}")
    print("")