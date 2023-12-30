#include <stdlib.h>
#include <graphics.h>
#include <math.h>
#include <locale.h>

float f1(float x) {
	return x * x;
}

float f2(float x) {
	return cos(x);
}

int sign(float a, float b) {
	if (a > b) {
		return 1;
	}
	else if (a == b) {
		return 0;
	}
	else {
		return -1;
	}
}

bool crossing(float y11, float y12, float y21, float y22) {
	if ((sign(y11, y21) != sign(y12, y22)) || (sign(y11, y21) == 0) || (sign(y12, y22) == 0)) {
		return true;
	}
	return false;
}

float mean(float a, float b) {
	return (a + b) / 2;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int width = 640;
	int height = 360;
	initwindow(width, height);
	float x1, x2;
	float y11, y12, y21, y22;
	float scaleX, scaleY;
	scaleX = 30;
	scaleY = 30;
	float step = 1 / scaleX;

	setcolor(15);

	x1 = (-width / 2) / scaleX;
	y11 = -f1(x1) * scaleY + height / 2;
	y21 = -f2(x1) * scaleY + height / 2;

	x2 = x1 + step;

	printf("Точки пересечения:\n");

	for (int i = 0; i < width; i++) {

		y12 = -f1(x2) * scaleY + height / 2;
		y22 = -f2(x2) * scaleY + height / 2;

		line(i, round(y11), i + 1, round(y12));
		line(i, round(y21), i + 1, round(y22));


		if (crossing(y11, y12, y21, y22)) {
			printf("x = %.2f; y = %.2f\n", mean(x1, x2), f1(mean(x1, x2)));
		}

		y11 = y12;
		y21 = y22;
		x1 = x2;
		x2 += step;

	}

	setfillstyle(1, 11);
	floodfill(321, 170, 15);

	outtextxy(90, 120, "f(1) = cos(x)");
	outtextxy(400, 30, "f(2) = x*x");

	getch();
	closegraph();
	return 0;
}
