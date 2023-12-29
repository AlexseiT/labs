#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <string>
#include <cmath>

using namespace std;

#ifndef IND_GEOMETRY;
#define IND_GEOMETRY

#include <iostream>
#include <string.h>

using namespace std;

const double pi = 3.141592653589793238463;

struct cir {
    string Ob;
    double p1;
    double p2;
    double r;
    double per;
    double ar;
    int* intersec;
    string* inter;
};

struct tri {
    string Ob;
    double ps[6];
    double per;
    double ar;
    int* intersec;
    string* inter;
};
string strtolower(string a)
{
    for (int i = 0; i < 8; ++i)
        a[i] = tolower(a[i]);
    return a;
}
double calcParam(double Number)
{
    double perimeter = 2 * pi * Number;
    return perimeter;
}

double calcArea(double Number)
{
    double area = pi * Number * Number;
    return area;
}

double calcParamtriandArea(double* Points, double* area)
{
    double length[3];
    int i;
    double Param;
    for (i = 0; i < 6; i += 2) {
        if (i == 4) {
            length[i / 2]
                = sqrt((Points[0] - Points[4]) * (Points[0] - Points[4])
                    + (Points[1] - Points[5]) * (Points[1] - Points[5]));
        }
        else
            length[i / 2] = sqrt(
                (Points[i + 2] - Points[i]) * (Points[i + 2] - Points[i])
                + (Points[i + 3] - Points[i + 1])
                * (Points[i + 3] - Points[i + 1]));
    }
    for (i = 0; i < 3; ++i)
        Param += length[i];
    if (length[0] < (length[1] + length[2])
        && length[1] < (length[0] + length[2])
        && length[2] < (length[0] + length[1])) {
        *area
            = sqrt((Param / 2) * (Param / 2 - length[0])
                * (Param / 2 - length[1]) * (Param / 2 - length[2]));
        return Param;
    }
    else
        return -1;
}
int ind(string Object)
{
    string Object1 = "circle";
    string Object2 = "triangle";
    string Object3 = "polygon";
    Object = strtolower(Object.substr(0, Object.find('(')));
    if (strcmp(Object1.c_str(), Object.c_str()) == 0) {
        return 1;
    }
    if (strcmp(Object2.c_str(), Object.c_str()) == 0) {
        return 2;
    }
    if (strcmp(Object3.c_str(), Object.c_str()) == 0) {
        return 3;
    }
    return 0;
}
void checkCircCirc(cir* circles, int n)
{
    double Length;
    int i, j;
    for (i = 0; i < n; ++i) {
        if (circles[i].Ob == " ")
            continue;
        for (j = 0; j < n; ++j) {
            if (circles[j].Ob == " ")
                continue;
            if (j == i)
                continue;
            Length
                = sqrt((circles[i].p1 - circles[j].p1)
                    * (circles[i].p1 - circles[j].p1)
                    + (circles[i].p2 - circles[j].p2)
                    * (circles[i].p2 - circles[j].p2));
            if ((Length - 2 * circles[i].r) <= 0) {
                if ((Length - circles[i].r - circles[j].r) <= 0) {
                    circles[i].intersec[j] = 1;
                    circles[j].intersec[i] = 1;
                    circles[i].inter[j] = "circle";
                    circles[j].inter[i] = "circle";
                }
                else {
                    circles[i].intersec[j] = 0;
                    circles[j].intersec[i] = 0;
                }
            }
        }
    }
}

void checkCircTri(cir* circles, tri* tr, int n)
{
    double X, Y, R, X1, Y1, D;
    for (int i = 0; i < n; ++i) {
        if (tr[i].Ob == " " || (tr[i].ar == 0 && tr[i].ar == 0))
            continue;
        for (int j = 0; j < n; ++j) {
            if (j == i)
                continue;
            if (circles[j].Ob == " ")
                continue;
            R = circles[j].r;
            for (int g = 0; g <= 4; g += 2) {
                if (g == 4) {
                    X1 = tr[i].ps[4] - circles[j].p1;
                    Y1 = tr[i].ps[5] - circles[j].p2;
                    X = tr[i].ps[0] - tr[i].ps[4];
                    Y = tr[i].ps[1] - tr[i].ps[5];
                    D = 16 * (X1 * X + Y1 * Y) * (X1 * X + Y1 * Y)
                        - 4 * (X * X + Y * Y) * (X1 * X1 + Y1 * Y1 - R * R);
                    if (D >= 0) {
                        circles[j].intersec[i] = 1;
                        tr[i].intersec[j] = 1;
                        circles[j].inter[i] = "triangle";
                        tr[i].inter[j] = "circle";
                    }
                    else {
                        circles[j].intersec[i] = 0;
                        tr[i].intersec[j] = 0;
                    }
                }
                else {
                    X1 = tr[i].ps[g] - circles[j].p1;
                    Y1 = tr[i].ps[g + 1] - circles[j].p2;
                    X = tr[i].ps[g + 2] - tr[i].ps[g];
                    Y = tr[i].ps[g + 3] - tr[i].ps[g + 1];
                    D = 16 * (X1 * X + Y1 * Y) * (X1 * X + Y1 * Y)
                        - 4 * (X * X + Y * Y) * (X1 * X1 + Y1 * Y1 - R * R);
                    if (D >= 0) {
                        circles[j].intersec[i] = 1;
                        tr[i].intersec[j] = 1;
                        circles[j].inter[i] = "triangle";
                        tr[i].inter[j] = "circle";
                    }
                    else {
                        circles[j].intersec[i] = 0;
                        tr[i].intersec[j] = 0;
                    }
                }
            }
        }
    }
}

void findPoints(string Object, double* Points)
{
    int i = 7;
    int j = i;
    if (Object[i - 1] == ')') {
        printf("Error at column %d : expected '('\n", i - 1);
        system("pause");
        exit(0);
    }
    while (Object[j] != ' ') {
        j += 1;
    }
    if ((strtod(Object.substr(i, j - 1).c_str(), NULL) == 0)
        && ((Object.substr(i, j - 1) != "0")
            || (Object.substr(i, j - 1) != "0.0"))) {
        printf("Error at column %d: expected '<double>'\n", i - 1);
        system("pause");
        exit(0);
    }
    Points[0] = strtod(Object.substr(i, j - 1).c_str(), NULL);
    while (Object[j] == ' ') {
        j += 1;
    }
    i = j;
    while (Object[j] != ',') {
        j += 1;
    }
    if ((strtod(Object.substr(i, j - 1).c_str(), NULL) == 0)
        && (Object.substr(i, j - 1) != "0")
        && (Object.substr(i, j - 1) != "0.0")) {
        printf("Error at column %d: expected '<double>'\n", i - 1);
        system("pause");
        exit(0);
    }
    Points[1] = strtod(Object.substr(i, j - 1).c_str(), NULL);
    j += 1;
    while (Object[j] == ' ') {
        j += 1;
    }
    i = j;
    while (1) {
        j += 1;
        if (Object[j] == ')') break;
        if (Object[j] == '(') break;
    }
    if ((strtod(Object.substr(i, j - 1).c_str(), NULL) == 0)
        && (Object.substr(i, j - 1) != "0")
        && (Object.substr(i, j - 1) != "0.0")) {
        printf("Error at column %d: expected '<double>'\n", i - 1);
        system("pause");
        exit(0);
    }
    Points[2] = strtod(Object.substr(i, j - 1).c_str(), NULL);

    if (Object[j] == '(') {
        printf("Error at column %d : expected ')'\n", j);
        system("pause");
        exit(0);
    }

    i = Object.length();
    if (i != j + 1) {
        while (Object[j] == ' ') {
            j += 1;
        }
        printf("Error at column %d: unexpected token\n", j);
        system("pause");
        exit(0);
    }
}

void findvert(string Object, double* Points)
{
    int i, j;
    j = i = 9;
    if (Object[i] == ')') {
        printf("Error at column %d : expected '('\n", i - 1);
        system("pause");
        exit(0);
    }
    while (Object[j] != ' ') {
        j += 1;
    }
    if ((strtod(Object.substr(i, j - 1).c_str(), NULL) == 0)
        && (Object.substr(i, j - 1) != "0")
        && (Object.substr(i, j - 1) != "0.0")) {
        printf("Error at column %d: expected '<double>'\n", i - 1);
        system("pause");
        exit(0);
    }
    Points[0] = strtod(Object.substr(i, j - 1).c_str(), NULL);
    while (Object[j] == ' ') {
        j += 1;
    }
    i = j;
    while (Object[j] != ',') {
        j += 1;
    }
    if ((strtod(Object.substr(i, j - 1).c_str(), NULL) == 0)
        && (Object.substr(i, j - 1) != "0")
        && (Object.substr(i, j - 1) != "0.0")) {
        printf("Error at column %d: expected '<double>'\n", i - 1);
        system("pause");
        exit(0);
    }
    Points[1] = strtod(Object.substr(i, j - 1).c_str(), NULL);
    j += 1;
    while (Object[j] == ' ') {
        j += 1;
    }
    i = j;
    while (Object[j] != ' ') {
        j += 1;
    }
    if ((strtod(Object.substr(i, j - 1).c_str(), NULL) == 0)
        && (Object.substr(i, j - 1) != "0")
        && (Object.substr(i, j - 1) != "0.0")) {
        printf("Error at column %d: expected '<double>'\n", i - 1);
        system("pause");
        exit(0);
    }
    Points[2] = strtod(Object.substr(i, j - 1).c_str(), NULL);
    while (Object[j] == ' ') {
        j += 1;
    }
    i = j;
    while (Object[j] != ',') {
        j += 1;
    }
    if ((strtod(Object.substr(i, j - 1).c_str(), NULL) == 0)
        && (Object.substr(i, j - 1) != "0")
        && (Object.substr(i, j - 1) != "0.0")) {
        printf("Error at column %d: expected '<double>'\n", i - 1);
        system("pause");
        exit(0);
    }
    Points[3] = strtod(Object.substr(i, j - 1).c_str(), NULL);
    j += 1;
    while (Object[j] == ' ') {
        j += 1;
    }
    i = j;
    while (Object[j] != ' ') {
        j += 1;
    }
    if ((strtod(Object.substr(i, j - 1).c_str(), NULL) == 0)
        && (Object.substr(i, j - 1) != "0")
        && (Object.substr(i, j - 1) != "0.0")) {
        printf("Error at column %d: expected '<double>'\n", i - 1);
        system("pause");
        exit(0);
    }
    Points[4] = strtod(Object.substr(i, j - 1).c_str(), NULL);
    while (Object[j] == ' ') {
        j += 1;
    }
    i = j;
    while (1) {
        j += 1;
        if (Object[j] == ')') break;
        if (Object[j] == '(') break;
    }
    if ((strtod(Object.substr(i, j - 1).c_str(), NULL) == 0)
        && ((Object.substr(i, j - 1) != "0")
            || (Object.substr(i, j - 1) != "0.0"))) {
        printf("Error at column %d: expected '<double>'\n", i - 1);
        system("pause");
        exit(0);
    }
    Points[5] = strtod(Object.substr(i, j - 1).c_str(), NULL);
    if (Object[j] == '(') {
        printf("Error at column %d : expected ')'\n", j);
        system("pause");
        exit(0);
    }
    i = Object.length();
    if (i != j + 1) {
        while (Object[j] == ' ') {
            j += 1;
        }
        printf("Error at column %d: unexpected token\n", j);
        system("pause");
        exit(0);
    }
}


int input()
{
    string in;
    getline(cin, in);
    int n = stoi(in);
    return n;
}

void output(cir* circles, tri* tr, int n)
{
    int i, j;
    for (i = 0; i < n; ++i) {
        if (circles[i].Ob == " ")
            continue;
        cout << circles[i].Ob << endl;
        cout << "Point 1 = " << circles[i].p1 << endl;
        cout << "Point 2 = " << circles[i].p2 << endl;
        cout << "Perimeter = " << circles[i].per << endl;
        cout << "Area = " << circles[i].ar << endl;
        cout << "intersections:" << endl;
        for (j = 0; j < n; ++j) {
            if (circles[i].intersec[j] == 1) {
                cout << j + 1 << "." << circles[i].inter[j] << endl;
            }
        }
    }
    for (i = 0; i < n; ++i) {
        if (tr[i].Ob == " " || (tr[i].ar == 0 && tr[i].ar == 0))
            continue;
        cout << tr[i].Ob << endl;
        for (j = 0; j < 6; ++j)
            printf("Point[%d] = %f\n", j + 1, tr[i].ps[j]);
        printf("Perimeter = %f\n", tr[i].per);
        printf("Area = %f\n", tr[i].ar);
        cout << "intersections:" << endl;
        for (j = 0; j < n; ++j) {
            if (tr[i].intersec[j] == 1) {
                cout << j + 1 << "." << tr[i].inter[j] << endl;
            }
        }
    }
}

int main()
{
    int n, i, j;
    double Points[6];
    double perimeter, area;
    bool HaveCir = 0;
    bool HaveTri = 0;

    printf("How many objects you wish input?\n");
    n = input();
    printf("Input your objects\n");

    cir* circles = new cir[n];
    tri* tr = new tri[n];

    for (i = 0; i < n; ++i) {
        tr[i].intersec = new int[n];
        tr[i].inter = new string[n];
        circles[i].intersec = new int[n];
        circles[i].inter = new string[n];
    }
    string Object;

    for (i = 0; i < n; i++) {
        getline(cin, Object);
        switch (ind(Object)) {
        case (1): {
            HaveCir = 1;
            tr[i].Ob = " ";
            circles[i].Ob = Object;
            findPoints(Object, Points);
            perimeter = calcParam(Points[2]);
            area = calcArea(Points[2]);
            circles[i].p1 = Points[0];
            circles[i].p2 = Points[1];
            circles[i].r = Points[2];
            circles[i].per = perimeter;
            circles[i].ar = area;
            break;
        }
        case (2): {
            HaveTri = 1;
            circles[i].Ob = " ";
            findvert(Object, Points);
            tr[i].Ob = Object;
            perimeter = calcParamtriandArea(Points, &area);
            if (perimeter == -1) {
                cout << "This triangle not exists" << endl;
                tr[i].ar = 0;
                tr[i].per = 0;
                break;
            }
            for (j = 0; j < 6; ++j)
                tr[i].ps[j] = Points[j];
            tr[i].ar = area;
            tr[i].per = perimeter;

            break;
        }
        case (0): {
            cout << "Error at column 0: expected 'circle', 'triangle' or "
                "'polygon'"
                << endl;
            break;
        }
        }
    }

    if (HaveCir == 1)
        checkCircCirc(circles, n);
    if (HaveTri == 1)
        checkCircTri(circles, tr, n);
    output(circles, tr, n);
    system("pause");
    delete[] tr;
    delete[] circles;
    return 0;
}