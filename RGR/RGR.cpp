#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
using namespace sf;
//Клавиши
struct Keys
{
	Keyboard::Key upKey = Keyboard::Num8;//Вверх
	Keyboard::Key downKey = Keyboard::Num2;//Вниз
	Keyboard::Key leftKey = Keyboard::Num4;//Влево
	Keyboard::Key rightKey = Keyboard::Num6;//Вправо
} keys;
int main()
{
	srand(time(0));//Рандом
	const int SIZE = 600;//Размер окна(высота, ширина)
	float x = 0;//Координаты по ширине окна
	float y = 0;//Координаты по высоте окна
	float dx = 0.5;//Скорость по оси x
	float dy = 0.5;//Скорость по оси y
	bool program1 = 0;// Подменю программы "Движение объекта с помощью клавиатуры"
		bool program1_1 = 0;
	bool program1_2 = 0;
	bool program2 = 0;// Подменю программы "Свободное движение объекта""
	bool program2_1 = 0;
	bool program2_2 = 0;
	bool way = 0;//Движение по часовой и против часовой стрелки в program2_2
	Font font;//Шрифт
	font.loadFromFile("ofont.ru_OpenGost Type A TT.ttf");//Загрузка шрифта
	Text p1("", font, 35);
	Text p1_1("", font, 35);
	Text p1_2("", font, 35);
	Text p2("", font, 35);
	Text p3("", font, 35);
	Texture pl_1;
	Texture pl_2;
	pl_1.loadFromFile("pl1.png");
	pl_2.loadFromFile("pl2.png");
	p1.setString(L"1. Движение объекта с помощью клавиатуры");
	p2.setString(L"2. Свободное движение объекта");
	p3.setString(L"3. Выход из программы");
	p1_1.setString(L"4. Корабль");
	p1_2.setString(L"5. Лицо");
	p1.setPosition(10, 40);
	p2.setPosition(10, 80);
	p1_1.setPosition(10, 40);
	p1_2.setPosition(10, 80);
	p3.setPosition(10, 120);
	RenderWindow window(VideoMode(SIZE, SIZE), "KR", Style::Close);//Создание окна
		window.setKeyRepeatEnabled(false);
	Sprite player_1;
	Sprite player_2;
	player_1.setTexture(pl_2);
	player_2.setTexture(pl_1);
	while (window.isOpen())
	{
		Event event;
		window.setKeyRepeatEnabled(false);
		//Проверка закрытия окна
		while (window.pollEvent(event))
			if (event.type == Event::Closed || event.key.code == Keyboard::Escape)
				window.close();
		if (program1 == 0 && program1_1 == 0 && program1_2 == 0 && program2
			== 0 && program2_1 == 0 && program2_2 == 0)
		{
			if (event.type == Event::KeyReleased) {
				switch (event.key.code)
				{
				case Keyboard::Num1:
					p1.setFillColor(Color::Red);
					p2.setFillColor(Color::White);
					p3.setFillColor(Color::White);
					program1 = 1;
					break;
				case Keyboard::Num2:
					p1.setFillColor(Color::White);
					p2.setFillColor(Color::Red);
					p3.setFillColor(Color::White);
					program2 = 1;
					break;
				case Keyboard::Num3:
					p1.setFillColor(Color::White);
					p2.setFillColor(Color::White);
					p3.setFillColor(Color::Red);
					window.close();
					break;
				}
			}
			window.clear();
			window.draw(p1);
			window.draw(p2);
			window.draw(p3);
		}
		if (program1 == 1)
		{
			if (event.type == Event::KeyReleased)
				switch (event.key.code)
				{
				case Keyboard::Num4:
					p1_1.setFillColor(Color::Red);
					p1_2.setFillColor(Color::White);
					program1_1 = 1;
					break;
				case Keyboard::Num5:
					p1_1.setFillColor(Color::White);
					p1_2.setFillColor(Color::Red);
					program1_2 = 1;
					break;
				}
			window.clear();
			window.draw(p1_1);
			window.draw(p1_2);
		}
		if (program2 == 1)
		{
			if (event.type == Event::KeyReleased)
				switch (event.key.code)
				{
				case Keyboard::Num4:
					p1_1.setFillColor(Color::Red);
					p1_2.setFillColor(Color::White);
					program2_1 = 1;
					break;
				case Keyboard::Num5:
					p1_1.setFillColor(Color::White);
					p1_2.setFillColor(Color::Red);
					program2_2 = 1;
					break;
				}
			window.clear();
			window.draw(p1_1);
			window.draw(p1_2);
		}
		if (program1_1 == 1 || program1_2 == 1)
		{
			if (y > 0)
				if (Keyboard::isKeyPressed(keys.upKey))
					y -= 0.5;
			if (y < SIZE - 72)
				if (Keyboard::isKeyPressed(keys.downKey))
					y += 0.5;
			if (x > 0)
				if (Keyboard::isKeyPressed(keys.leftKey))
					x -= 0.5;
			if (x < SIZE - 72)
				if (Keyboard::isKeyPressed(keys.rightKey))
					x += 0.5;
			player_1.setPosition(x, y);
			window.clear(Color::White);
			if (program1_1 == 1)
			{
				player_1.setPosition(x, y);
				window.draw(player_1);//Отрисовка фигуры
			}
			if (program1_2 == 1)
			{
				player_2.setPosition(x, y);
				window.draw(player_2);//Отрисовка фигуры
			}
		}
		if (program2_1 == 1)
		{
			if (x<0 || x>SIZE - 72)
				dx = -dx;
			if (y<0 || y>SIZE - 72)
			{
				dy = -dy;
			}
			x += dx;
			y += dy;
			player_1.setPosition(x, y);
			window.clear(Color::White);
			window.draw(player_1);
		}
		if (program2_2 == 1)
		{
			if (rand() % 5000 == 2500)
				way = !way;
			if (way == 1)
			{
				//Против часовой
				if (x == 0 && y != SIZE - 72)
					y += dy;
				if (y == SIZE - 72 && x != SIZE - 72)
					x += dx;
				if (x == SIZE - 72 && y != 0)
					y -= dy;
				if (y == 0 && x != 0)
					x -= dx;
			}
			else
			{
				//По часовой
				if (y == 0 && x != SIZE - 72)
					x += dx;
				if (x == SIZE - 72 && y != SIZE - 72)
					y += dy;
				if (y == SIZE - 72 && x != 0)
					x -= dx;
				if (x == 0 && y != 0)
					y -= dy;
			}
			player_2.setPosition(x, y);
			window.clear(Color::White);
			window.draw(player_2);
		}
		window.display();//Отрисовка окна
	}
}