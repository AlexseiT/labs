#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <string>
#include <string.h>
#include <math.h>
using namespace std;

enum Figures { CIRCLE, TRIANGLE, ERROR };

struct circle {
  float point[2];
  float number;
  string intr;
};

struct triangle {
  float point_1[2];
  float point_2[2];
  float point_3[2];
  float point_4[2];
};

struct mass_object {
  Figures tag;
  int order_number;
  union {
    struct circle obj_circle;
    struct triangle obj_triangle;
  };
};

double circle_p(double number) {
  double perim;
  perim = 2 * 3.14 * number;
  return perim;
}

double circle_area(double number) {
  double area;
  area = 3.14 * number * number;
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


void find_circle_param(mass_object circl, float *perimeter, float *area) {
  *perimeter = 2 * 3.14 * circl.obj_circle.number;

  *area = 3.14 * circl.obj_circle.number * circl.obj_circle.number;
}

double distance_between_points(double x1, double x2, double y1, double y2) {
  double i = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));

  return i;
}

void find_triangle_param(mass_object triang, float *perimeter, float *area) {
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

void print_circle(mass_object *circl, float *perimeter, float *area) {
  cout << circl->order_number << "."

       << "circle(" << circl->obj_circle.point[0] << ' '
       << circl->obj_circle.point[1] << ", "

       << circl->obj_circle.number << ")" << endl;

  find_circle_param(*circl, perimeter, area);

  cout << "Perimetr: " << *perimeter << endl;

  cout << "Area: " << *area << endl;
}

void print_triangle(mass_object *triang, float *perimeter, float *area) {
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
}

std::string word_tolower(std::string word) {
  int n = word.length();
  for (int i = 0; i < n; i++) {
    word[i] = tolower(word[i]);
  }
  return word;
}

Figures identify(std::string figure) {
  std::string figureName;
  figure = word_tolower(figure);

  figureName = "circle";
  if (figure == figureName)
    return CIRCLE;

  figureName = "triangle";
  if (figure == figureName)
    return TRIANGLE;

  return ERROR;
}

void parsing_circle(std::string input, mass_object *circl, circle *cir) {
  size_t end;
  input = input.erase(0, 6);
  if (input[0] == '(') {
    input.erase(0, 1);
    circl->obj_circle.point[0] = stod(input, &end);
    cir->point[0] = stod(input, &end); 
    input = input.erase(0, end);
    circl->obj_circle.point[1] = stod(input, &end);
    cir->point[1] = stod(input, &end); 
    input = input.erase(0, end + 1);
    circl->obj_circle.number = stod(input, &end);
    cir->number = stod(input, &end); 
  };
}

void parsing_triangle(std::string input, mass_object *triang) {
  size_t end;
  input = input.erase(0, 8);
  if ((input[0] == '(') && (input[1] == '(')) {
    input = input.erase(0, 2);
    replace(input.begin(), input.end(), ',', ' ');
    triang->obj_triangle.point_1[0] = stod(input, &end);
    input.erase(0, end);
    triang->obj_triangle.point_1[1] = stod(input, &end);
    input.erase(0, end);
    triang->obj_triangle.point_2[0] = stod(input, &end);
    input.erase(0, end);
    triang->obj_triangle.point_2[1] = stod(input, &end);
    input.erase(0, end);
    triang->obj_triangle.point_3[0] = stod(input, &end);
    input.erase(0, end);
    triang->obj_triangle.point_3[1] = stod(input, &end);
    input.erase(0, end);
    triang->obj_triangle.point_4[0] = stod(input, &end);
    input.erase(0, end);
    triang->obj_triangle.point_4[1] = stod(input, &end);
    input.erase(0, end);
  }
}

std::string parsing_name(std::string *input) {
  std::string figureName;
  if (input->substr(0, 1) == " ") {
    input->erase(0, input->find_first_not_of(" "));
  }
  if (input->substr(input->find("(") - 1, 1) == " ") {
    input->erase(input->find(" "), input->find("(") - input->find(" "));
  }
  figureName = input->substr(0, input->find("("));
  return figureName;
}

double circle_circle(circle *cir, int countC, int count) {
  double Length;
  for (int i = 0; i < countC; i++) {
    if (i != count) {
      Length = sqrt((cir[count].point[0] - cir[i].point[0]) *
                        (cir[count].point[0] - cir[i].point[0]) +
                    (cir[count].point[1] - cir[i].point[1]) *
                        (cir[count].point[1] - cir[i].point[2]));
      if ((Length - 2 * cir[count].number) <= 0) {
        if ((Length - cir[count].number - cir[i].number) <= 0) {
            return i + 1;
        } else
          return 0;
      } else
        return 0;
    }
  }
  return 0;
}

int main() {
  string input, figureName;

  int figures_count, countC = 0;
  cout << "Enter number:" << endl;
  cin >> figures_count;

  circle *cir = new circle[figures_count]; 

  triangle *tri = new triangle[figures_count]; 

  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  mass_object *figures = new mass_object[figures_count];

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

  float perimeter, area;
  double Numb;
  cout << endl;
  for (int i = 0; i < figures_count; i++) {
    if (figures[i].tag == CIRCLE) {
      print_circle(&figures[i], &perimeter, &area);
      Numb = circle_circle(cir, countC, i);
      if (Numb != 0) {
        cout << "interesection: " << endl;
        cout << circle_circle(cir, countC, i) << ". circle" << endl;
      }
    }
    if (figures[i].tag == TRIANGLE)
      print_triangle(&figures[i], &perimeter, &area);
  }

  float perimeter, area;
  cout << endl;
  for (int i = 0; i < figures_count; i++) {
    if (figures[i].tag == CIRCLE) {
      print_circle(&figures[i], &perimeter, &area);
      cout << "interesection: " << endl;
      circle_circle(cir, countC, i);
    }
    if (figures[i].tag == TRIANGLE)
      print_triangle(&figures[i], &perimeter, &area);
  }
  }

double circle_circle(circle *cir, int countC, int count) {
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

float perimeter, area;
cout << endl;
for (int i = 0; i < figures_count; i++) {
  if (figures[i].tag == CIRCLE) {
    print_circle(&figures[i], &perimeter, &area);
    cout << "interesection: " << endl;
    circle_circle(cir, countC, i);
  }
  if (figures[i].tag == TRIANGLE)
    print_triangle(&figures[i], &perimeter, &area);
}
}
