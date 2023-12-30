#include <graphics.h>
#include <conio.h>
void flake(int x, int y, int rad)
{
	line(x, y, x + rad, y);
	line(x, y, x, y + rad);
	line(x, y, x - rad, y);
	line(x, y, x, y - rad);
	line(x, y, x + rad / 2, y + rad / 2);
	line(x, y, x + rad / 2, y - rad / 2);
	line(x, y, x - rad / 2, y - rad / 2);
	line(x, y, x - rad / 2, y + rad / 2);
}
void draw(int x, int y, int rad, int color)
{
	setcolor(color);
	flake(x, y, rad);
}
int main()
{
	const int n = 100;
	int w = 400, h = 400, x[n], y[n], color[n], rad[n], k[n], dir[n];

	initwindow(w, h);

	for (int i = 0; i < n; i++)
	{
		x[i] = rand() % w;
		y[i] = rand() % h;
		k[i] = (rand() % 2) + 1;
		color[i] = rand() % 16;
		dir[i] = rand() % 8;
		rad[i] = (rand() % 10) + 5;
	}

	while (1) {
		for (int i = 0; i < n; i++)
		{
			draw(x[i], y[i], rad[i], 0);
			switch (n[i])
			{
			case 0: y[i] += k[i]; break;
			case 1: y[i] += k[i]; x[i] += k[i]; break;
			case 2: x[i] += k[i]; break;
			case 3: y[i] -= k[i]; x[i] += k[i]; break;
			case 4: y[i] -= k[i]; break;
			case 5: y[i] -= k[i]; x[i] -= k[i]; break;
			case 6: x[i] -= k[i]; break;
			case 7: x[i] -= k[i]; y[i] += k[i]; break;
			}
			if ((x[i] > w + 5) || (y[i] > h + 5) || (x[i] < -5) || (y[i] < -5))
			{
				x[i] = rand() % w;
				y[i] = rand() % h;
				n[i] = rand() % 8;
				color[i] = rand() % 16;
				rad[i] = (rand() % 10) + 5;
				k[i] = (rand() % 2) + 1;
			}
			draw(x[i], y[i], rad[i], color[i]);
		}
	}
	getch();
}
