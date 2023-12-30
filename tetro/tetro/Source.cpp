#include <SFML/Graphics.hpp>
#include <sstream>
#include <time.h>
using namespace sf;

const int height = 20;
const int width = 10;
const int x = 7;
const int y = 4;
const int block = 36;
const int min = 1;
const int max = 10;
int counter = 1;
int playing_area[height][width];
int array_blocks[x][y] = { 1,3,5,7,  2,4,5,7,  3,5,4,6,  3,5,4,7,  2,3,5,7,  3,5,7,6,  2,3,4,5 };

struct Point
{
	int x_pos, y_pos;
} point1[4], point2[4];

bool check()
{
	for (int i = 0; i < 4; i++)
		if (point1[i].x_pos < 0 || point1[i].x_pos >= width || point1[i].y_pos >= height) return 0;
		else if (playing_area[point1[i].y_pos][point1[i].x_pos]) return 0;
	return 1;
};

void Load_textures(Texture& texture, Texture& texture_background, Font& typeface)
{
	texture.loadFromFile("images/block_texture.jpg");
	texture_background.loadFromFile("images/back_texture.jpg");
	typeface.loadFromFile("text.ttf");
}

void spin_true()
{
	Point centr = point1[1];
	for (int i = 0; i < 4; i++)
	{
		int x = point1[i].y_pos - centr.y_pos;
		int y = point1[i].x_pos - centr.x_pos;
		point1[i].x_pos = centr.x_pos - x;
		point1[i].y_pos = centr.y_pos + y;
	}
	if (!check())
		for (int i = 0; i < 4; i++)
			point1[i] = point2[i];
}

void start_game(bool& start)
{
	if (start) {
		start = false;
		int tetr = rand() % x;
		for (int i = 0; i < 4; i++)
		{
			point1[i].x_pos = array_blocks[tetr][i] % 2;
			point1[i].y_pos = array_blocks[tetr][i] / 2;
		}
	}
}

void down_timer(float& timer, float& suspend_timer, int& palette)
{
	if (timer > suspend_timer)
	{
		for (int i = 0; i < 4; i++) { point2[i] = point1[i]; point1[i].y_pos += 1; }
		if (!check())
		{
			for (int i = 0; i < 4; i++) playing_area[point2[i].y_pos][point2[i].x_pos] = palette;
			palette = min + rand() % (max - min);
			int tetr = rand() % x;
			counter++;
			for (int i = 0; i < 4; i++)
			{
				point1[i].x_pos = array_blocks[tetr][i] % 2;
				point1[i].y_pos = array_blocks[tetr][i] / 2;
			}

		}
		timer = 0;

	}
}

void line(int& del)
{
	del = height - 1;
	for (int i = height - 1; i > 0; i--)
	{
		int count = 0;
		for (int j = 0; j < width; j++)
		{
			if (playing_area[i][j]) count++;
			playing_area[del][j] = playing_area[i][j];
		}
		if (count < width) del--;
	}
}

void vertical(int& speed_x, float& suspend_timer)
{
	if (Keyboard::isKeyPressed(Keyboard::Down)) suspend_timer = 0.1;
	for (int i = 0; i < 4; i++) {
		point2[i] = point1[i];
		point1[i].x_pos += speed_x;
	}
	if (!check())
		for (int i = 0; i < 4; i++) point1[i] = point2[i];
}

void windows(RenderWindow& window, Sprite& sprite, Sprite& sprite_background, int& palette, Text& text)
{
	window.clear(Color::White);
	window.draw(sprite_background);
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			if (playing_area[i][j] == 0) continue;
			sprite.setTextureRect(IntRect(playing_area[i][j] * block, 0, block, block));
			sprite.setPosition(j * block, i * block);
			sprite.move(144, 80);
			window.draw(sprite);
		}

	for (int i = 0; i < 4; i++)
	{
		sprite.setTextureRect(IntRect(palette * block, 0, block, block));
		sprite.setPosition(point1[i].x_pos * block, point1[i].y_pos * block);
		sprite.move(144, 80);
		window.draw(sprite);
	}
	std::ostringstream score;
	score << counter;
	text.setString("Score: " + score.str());
	text.setPosition(50, 200);
	window.draw(text);
	window.display();
}

void game_over(RenderWindow& window)
{
	for (int i = 0; i < width; i++)
	{
		if (playing_area[1][i])
		{
			window.close();
		}
	}
}

void press_key(RenderWindow& window, int& speed_x, Event& action) {
	while (window.pollEvent(action))
	{
		switch (action.type) {
		case(Event::Closed):
			window.close();
			break;
		case(Event::KeyPressed):
			switch (action.key.code) {
			case(Keyboard::Up):
				spin_true();
				break;
			case(Keyboard::Left):
				speed_x = -1;
				break;
			case(Keyboard::Right):
				speed_x = 1;
				break;
			}
			break;
		}
	}
}

int main()
{
	srand(time(0));
	Clock clock;
	int speed_x = 0, palette = 1, tetr = rand() % x;
	bool spin = 0, start = true;
	float timer = 0, suspend_timer = 0.5;
	int del;

	RenderWindow window(VideoMode(640, 960), "Tetris by Alexey Todorov");
	Font typeface;
	Texture texture, texture_background;
	Text text("", typeface, 20);
	Load_textures(texture, texture_background, typeface);
	Sprite sprite(texture), sprite_background(texture_background);
	sprite.setTextureRect(IntRect(0, 0, block, block));

	while (window.isOpen())
	{
		Event action;
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		press_key(window, speed_x, action);
		vertical(speed_x, suspend_timer);
		down_timer(timer, suspend_timer, palette);

		line(del);
		start_game(start);

		speed_x = 0; spin = 0; suspend_timer = 0.4;
		windows(window, sprite, sprite_background, palette, text);
		game_over(window);
	}

	return 0;
}