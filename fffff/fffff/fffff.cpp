#include <algorithm>
#include <iostream>
#include <libgeometry/func.h>
#include <libgeometry/parsing.h>
#include <limits>
#include <string>

using namespace std;

#include <cmath>
#include <iostream>
#include <libgeometry/func.h>
#include <string>
using namespace std;
double circle_p(double number) {
    double perim;
    perim = 2 * M_PI * number;
    return perim;
}

double circle_area(double number) {
    double area;
    area = M_PI * number * number;
    return area;
}

double triangle_area(double x1, double x2, double x3, double y1, double y2,
    double y3) {
    double area;
    area = abs(((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1)) / 2);
    return area;
}

double triangle_p(double x1, double x2, double x3, double y1, double y2,
    double y3) {
    double perim;
    perim = distance_between_points(x1, x2, y1, y2) +
        distance_between_points(x2, x3, y2, y3) +
        distance_between_points(x3, x1, y3, y1);
    return perim;
}

void find_circle_param(mass_object circl, float* perimeter, float* area) {
    *perimeter = 2 * M_PI * circl.obj_circle.number;

    *area = M_PI * circl.obj_circle.number * circl.obj_circle.number;
}

double distance_between_points(double x1, double x2, double y1, double y2) {
    double i = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));

    return i;
}

void find_triangle_param(mass_object triang, float* perimeter, float* area) {
    double x1 = triang.obj_triangle.point_1[0];
    double x2 = triang.obj_triangle.point_2[0];
    double x3 = triang.obj_triangle.point_3[0];
    double y1 = triang.obj_triangle.point_1[1];
    double y2 = triang.obj_triangle.point_2[1];
    double y3 = triang.obj_triangle.point_3[1];
    *perimeter = distance_between_points(x1, x2, y1, y2) +
        distance_between_points(x2, x3, y2, y3) +
        distance_between_points(x3, x1, y3, y1);

    *area = abs(((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1)) / 2);
}

void print_circle(mass_object* circl, float* perimeter, float* area) {
    cout << circl->order_number << "."

        << "circle(" << circl->obj_circle.point[0] << ' '
        << circl->obj_circle.point[1] << ", "

        << circl->obj_circle.number << ")" << endl;

    find_circle_param(*circl, perimeter, area);

    cout << "Perimetr: " << *perimeter << endl;

    cout << "Area: " << *area << endl;
}

void print_triangle(mass_object* triang, float* perimeter, float* area) {
    cout << triang->order_number << "."
        << "triangle((" << triang->obj_triangle.point_1[0] << ' '
        << triang->obj_triangle.point_1[1] << ","
        << triang->obj_triangle.point_2[0] << ' '
        << triang->obj_triangle.point_2[1] << ","
        << triang->obj_triangle.point_3[0] << ' '
        << triang->obj_triangle.point_3[1] << ","
        << triang->obj_triangle.point_4[0] << ' '
        << triang->obj_triangle.point_4[1] << "))" << endl;

    find_triangle_param(*triang, perimeter, area);

    cout << "Perimeter: " << *perimeter << endl;

    cout << "Area: " << *area << endl;

    cout << endl;
}

void circle_circle(circle* cir, int countC, int count) {
    double Length;
    for (int i = 0; i < countC; i++) {
        if (i != count) {
            Length = sqrt((cir[count].point[0] - cir[i].point[0]) *
                (cir[count].point[0] - cir[i].point[0]) +
                (cir[count].point[1] - cir[i].point[1]) *
                (cir[count].point[1] - cir[i].point[1]));
            if ((Length - 2 * cir[count].number) <= 0)
                if ((Length - cir[count].number - cir[i].number) <= 0)
                    cout << i + 1 << ". circle" << endl;
        }
    }
}

int main()
{
    string input, figureName;

    int figures_count, countC = 0;
    float perimeter, area;
    cout << "Enter number:" << endl;
    cin >> figures_count;

    circle* cir = new circle[figures_count];
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    mass_object figures[figures_count];

    for (int i = 0; i < figures_count; i++) {
        getline(cin, input);
        figureName = parsing_name(&input);

        switch (identify(figureName)) {
        case CIRCLE:
            figures[i].tag = CIRCLE;
            figures[i].order_number = i + 1;
            parsing_circle(input, &figures[i], &cir[countC]);
            countC++;
            break;
        case TRIANGLE:
            figures[i].tag = TRIANGLE;
            figures[i].order_number = i + 1;
            parsing_triangle(input, &figures[i]);
            break;
        case ERROR:
            cout << input << endl;
            cout << '^' << endl;
            cout << "Error: figure not found";
        }
    }

    cout << endl;
    for (int i = 0; i < figures_count; i++) {
        if (figures[i].tag == CIRCLE) {
            print_circle(&figures[i], &perimeter, &area);
            cout << "interesection: " << endl;
            circle_circle(cir, countC, i);
            cout << endl;
        }
        if (figures[i].tag == TRIANGLE) {
            print_triangle(&figures[i], &perimeter, &area);
            cout << endl;
        }
    }
}
































void circle_circle(circle* cir, int countC, int count)
{
    double Length;
    for (int i = 0; i < countC; i++) {
        if (i != count) {
            Length = sqrt((cir[count].point[0] - cir[i].point[0]) *
                (cir[count].point[0] - cir[i].point[0]) +
                (cir[count].point[1] - cir[i].point[1]) *
                (cir[count].point[1] - cir[i].point[1]));
            if ((Length - 2 * cir[count].number) <= 0) {
                if ((Length - cir[count].number - cir[i].number) <= 0) {
                    cout << i + 1 << ". circle" << endl;
                }
            }
        }
    }
}