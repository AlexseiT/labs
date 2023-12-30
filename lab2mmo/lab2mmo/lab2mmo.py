#!/usr/bin/env python
# -*- coding: cp1251 -*-
import pandas as pd
from sklearn import tree
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt
import random

column_names = ["age", "sex", "cp", "trestbps", "chol", "fbs", "restecg", "thalach", "exang", "oldpeak", "slope", "ca", "thal", "target"]
clf = pd.read_csv('heart_data.csv', header=None, names=column_names)
clf = clf.replace("?", None)
clf = clf.apply(pd.to_numeric, errors='ignore')

x = clf.iloc[1:, 0:13]  
y = clf.iloc[1:, 13]    

clf = tree.DecisionTreeClassifier(random_state=0, max_depth=12, max_leaf_nodes=2)

accuracyTrainingAll = []
accuracyTestingAll = []

print('| ��������\t | ��������� \t | �������� |', sep=" ")
maxTraining = 0
maxTesting = 0

for i in range(10):
    random_seed = random.randint(1, 1000)
    xTraining, xTesting, yTraining, yTesting = train_test_split(x, y, test_size=0.3, random_state=random_seed)
    clf.fit(xTraining, yTraining)
    accuracyTraining = clf.score(xTraining, yTraining)
    accuracyTesting = clf.score(xTesting, yTesting)

    accuracyTrainingAll.append(accuracyTraining)
    accuracyTestingAll.append(accuracyTesting)

    if(accuracyTraining > maxTraining):
       maxTraining = accuracyTraining
    if(accuracyTesting > maxTesting):
       maxTesting = accuracyTesting
    print('-------------------------------------------', sep=" ")
    print(f'|\t{i+1} \t | {accuracyTraining:.6f}\t | {accuracyTesting:.6f} |')

print('-------------------------------------------', sep=" ")
print(f'������������ �� ���������: {maxTraining:.6f}')
print(f'������������ �� ��������: {maxTesting:.6f}')

# Plot the results
plt.figure(figsize=(8, 6))
plt.plot(range(2, 12), accuracyTrainingAll, label='���������')
plt.plot(range(2, 12), accuracyTestingAll, label='��������')
plt.xlabel('����� ��������')
plt.ylabel('��������')
plt.legend()
plt.title('��������� ��������� � �������� ���������')
plt.show()