#!/usr/bin/env python
# -*- coding: cp1251 -*-
from collections import defaultdict
import random
import matplotlib.pyplot as plt
import networkx as nx
import os
import eel
from termcolor import colored

arrGraph = list()

def SimpleCheck(p):
    if p <= 1:
        return False
    elif p == 2:
        return True
    a = random.randint(2, p - 1)
    # print(p, "-", a)
    if Module(a, (p - 1), p) != 1 or Euqlid(p, a) > 1:
        return False
    return True

def SimpleGen(left, right):
    while True:
        p = random.randint(left, right)
        # print("--", p)
        if SimpleCheck(p):
            return p

def CoprimeGen(p):
    result = random.randint(2, p)
    # print(result)
    while Euqlid(p, result) != 1:
        result = random.randint(2, p)
    # print(result)
    return result

def Module(a, x, p):
    result = 1
    a = a % p
    if a == 0:
        return 0;
    while x > 0:
        if x & 1 == 1: # ���� ������� ������ ��� ������� ����� lib
            result = (result * a) % p
        a = (a ** 2) % p
        x >>= 1 # �������� ������� �������
    return result

def Euqlid(a, b):
    while b != 0:
        r = a % b
        a = b
        b = r
    return a
def GeneralEuqlid(a, b):
    U = (a, 1, 0)
    V = (b, 0, 1)
    while V[0] != 0:
        q = U[0] // V[0]
        T = (U[0] % V[0], U[1] - q * V[1], U[2] - q * V[2])
        U = V
        V = T
    return U
def Read(file_path='Path.txt'):
    try:
        with open(file_path, 'r') as file:
            lines = file.read().splitlines()
    except OSError:
        print("������ �������� ����� � �������")
        return -1

    N = int(lines[0])
    M = int(lines[1])
    node_ids = list(range(1, N + 1))
    header = "\t" + "\t".join(map(str, node_ids))

    graph_G = [[0] * N for _ in range(N)]
    graph_H = [[0] * N for _ in range(N)]

    print("��������� ����:")
    print(header)
    
    for i in range(N):
        print(f" {node_ids[i]}", end="\t")
        for j in range(N):
            graph_G[i][j] = 0
            print(graph_G[i][j], end="\t")
        print()

    print("\n���� ����� ���������� ������:")
    print(header)
    
    for k in range(M):
        line = lines[k + 2]
        i, j = map(int, line.split(","))
        graph_G[i - 1][j - 1] = 1
        graph_G[j - 1][i - 1] = 1
        graph_H[i - 1][j - 1] = 1
        graph_H[j - 1][i - 1] = 1

    for i in range(N):
        print(f" {node_ids[i]}", end="\t")
        for j in range(N):
            print(graph_G[i][j], end="\t")
        print()
    return N, M, graph_G, graph_H, header
def Path(graph):
    paths = defaultdict(list)
    for i in range(len(graph)):
        for j in range(len(graph[i])):
            if graph[i][j] == 1:
                paths[i].append(j + 1)
    return paths
def SearchHam(graph, size, pt, path=[]):
    if pt not in set(path):
        path.append(pt)
        if len(path) == size:
            return path
        for pt_next in graph.get(pt - 1, []):
            res_path = path.copy()
            candidate = SearchHam(graph, size, pt_next, res_path)
            if candidate is not None:
                return candidate
def RSAencode(new_graph, x, p, N):
    temp_graph = [[0] * N for _ in range(N)]
    for i in range(len(new_graph)):
        for j in range(len(new_graph[i])):
            temp_graph[i][j] = Module(new_graph[i][j], x, p)
    return temp_graph
GRAPH_G = []
GRAPH_H = []
@eel.expose
def HamCycle():
    N, M, graph_G, graph_H, header = Read()
    list_path = list()
    new_graph_H = [[0] * N for _ in range(N)]
    new_graph_G = [[0] * N for _ in range(N)]
    left_random = list(range(1, N + 1))
    random.shuffle(left_random)

    print(colored(f"\nN = {N}, M = {M}","green"))
    paths = Path(graph_G)

    print("\n��������:")
    for i in range(len(paths)):
        print(colored(f"{i + 1}: {paths[i]}","green"))

    cycle_path = SearchHam(paths, N, 1, list_path)
    print(f"\n����������� ����: {cycle_path}\n")


    print(colored("\n�����\n","blue"))
 

    new_list = list(range(N))
    random.shuffle(new_list)
    new_list_str = [i + 1 for i in new_list]
    print(f"(�����) �������� ������� �����: {new_list_str} \n")

    k, z = 0, 0
    for i in new_list:
        for j in new_list:
            new_graph_H[k][z] = graph_G[int(i)][int(j)]
            z += 1
        z = 0
        k += 1

    print(colored("���������� ����: ","green"))
    print(header)
    for i in range(len(new_graph_H)):
        print(" " + str(i + 1), end="\t")
        for j in range(len(new_graph_H[i])):
            print(new_graph_H[i][j], end="\t")
        print("\n", end="")

    print("\n����� ���������� ���������� RSA\n" +
          f"�������� ��������� ����� �� ������ {left_random}")

    k, z = 0, 0
    for i in left_random:
        for j in left_random:
            new_graph_H[k][z] = int(str(j) + str(new_graph_H[k][z]))
            z += 1
        z = 0
        k += 1

    print(colored("\n�������� �� �������������� RSA:", "red"))
    print(header)
    for i in range(len(new_graph_H)):
        print(" " + str(i + 1), end="\t")
        for j in range(len(new_graph_H[i])):
            print(new_graph_H[i][j], end="\t")
        print("\n", end="")

    print("\n(�����) ���������� �����: ")
    P = SimpleGen(0, 10 ** 9)
    Q = SimpleGen(0, 10 ** 9)
    N_encode = P * Q
    print(colored("���� N: ", "green"), N_encode)
    Phi = (P - 1) * (Q - 1)
    d = CoprimeGen(Phi)
    c = GeneralEuqlid(d, Phi)[1]
    if c < 0:
        c += Phi
    print(colored("���� �: ", "green"), c)
    graph_F = RSAencode(new_graph_H, d, N_encode, N)

    print("\n(���) ������� ����� (RSA)")
    print(header)
    for i in range(len(graph_F)):
        print(" " + str(i + 1), end="\t")
        for j in range(len(graph_F[i])):
            print(graph_F[i][j], end="\t")
        print("\n", end="")

    print()
    print(colored("���","blue"))
    print()

    print("��� ������� ������� F\n")
    print("����� ������ ������� ���?")
    print("1.'�����, ����� ����������� ���� ��� ����� H?'")
    print("2.'�����, ������������� �� ���� H ��������� G?'")

    answer = int(input())
    if answer == 1:
        print("-'�����, ������ ����������� ����?'")
        print(f"����������� ����: {cycle_path}")
        print("��� �������� �� ������� �-�����, ���������� ��������������� ������� �����")
        print("���� �������� ������� F ����� ���� ���������������, �� ��� �������� �� ������� ����� ������ ���� ����\n"
              + "���� ��� ��� �������, �� ��� � �������. ���� ���, �� �������� ������ � ���������")
        bob_check = RSAencode(new_graph_H, d, N_encode, N)
        flag = all(bob_check[i][j] == graph_F[i][j] for i in range(len(graph_F)) for j in range(len(graph_F[i])))
        if flag:
            print(f"\n������� ���������, �.�. flag = {flag}")
            print(f"����������� ���� �����: {cycle_path}")
            print(f"����������� ���� ����: {cycle_path}")
        else:
            print(f"������� ������ flag = {flag}")

    if answer == 2:
        print("-'������ ����������, �����?'")
        print("\n����� �������� ���� �������, ������� ��� �� ������������� � RSA\n" +
              "� ������ ��������, ������� ��� ������������ ����� ��������� ������������ �����")
        print("\n��� ��������� �������: ���������� ������� F � H-����� �����\n" +
              "���������� ���������� � ��������� ������")
        bob_check = RSAencode(new_graph_H, d, N_encode, N)
        flag = all(bob_check[i][j] == graph_F[i][j] for i in range(len(graph_F)) for j in range(len(graph_F[i])))
        if flag:
            print(f"\n������� ���������, �.�. flag = {flag}")
        else:
            print(f"\n������� ������ flag = {flag}")
        print("����� ��� ����������� ��� ������� ����� ���������� �� ������� �������� ������� � �������� �������,\n" +
              "���������� ���������\n")
        print(header)
        for i in range(len(new_graph_H)):
            print(" " + str(i + 1), end="\t")
            for j in range(len(new_graph_H[i])):
                num_str = str(new_graph_H[i][j])
                new_graph_H[i][j] = int(num_str[-1])
                print(new_graph_H[i][j], end="\t")
            print("\n", end="")

    print("\n����� ��� ������������ ������� � ������������ � ���������� ���������� �� �����")
    print(f"\n������ ����� ������ �����: {new_list_str}")

    k, z = 0, 0
    for i in new_list:
        for j in new_list:
            new_graph_G[int(i)][int(j)] = new_graph_H[k][z]
            z += 1
        z = 0
        k += 1

    print("\n����� ����� ��������� ���� H, ���������� ��� �� ���� �����, � �������� ���� �����\n" +
          "���� ��� ���������, �� �� ����� H �� �������� ���� G")
    flag = all(graph_H[i][j] == new_graph_G[i][j] for i in range(len(graph_H)) for j in range(len(graph_H[i])))
    if flag:
        print()
        print(f"������� ���������, �.�. flag = {flag}")
    else:
        print(f"������� ������ flag = {flag}")

    return graph_G, new_graph_H

@eel.expose
def GetResultGraph():
    return GRAPH_G, GRAPH_H

@eel.expose
def GetValues():
    N, M, graph_G, graph_H, header = Read()
    return N, M, graph_G, graph_H

if __name__ == '__main__':
    os.system('color')
    eel.init('init')
    eel.start('index.html', size = (1024, 768))