#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace std;
using namespace sf;

constexpr int windowWidth{ 800 }, windowHeight{ 600 };
constexpr int countBlocksX{ 11 }, countBlocksY{ 4 };

int helth = 3;

class Objects
{
public:
    virtual float x() { return 0; }
    virtual float y() { return 0; }
    virtual float left() { return 0; }
    virtual float right() { return 0; }
    virtual float top() { return 0; }
    virtual float bottom() { return 0; }
    virtual void update() { }
    Objects();
    float return_radius() { return radius; }
    float return_ball_velocity() { return ball_velocity; }
    float return_block_width() { return block_width; }
    float return_block_height() { return block_height; }
protected:
    float radius, ball_velocity;
    float block_width, block_height;
    float paddleWidth, paddleHeight, paddleVelocity;
};

Objects::Objects() {
    radius = 10.f;
    ball_velocity = 8.f;
    block_width = 60.f,
        block_height = 20.f;
    paddleWidth = 100;
    paddleHeight = 10;
    paddleVelocity = 6.f;
}


class Ball :public Objects
{
public:

    CircleShape shape;

    Vector2f velocity{ -ball_velocity, -ball_velocity };

    Ball(float X, float Y);

    void update()
    {
        shape.move(velocity);
        if (left() < 0)
            velocity.x = ball_velocity;
        else if (right() > windowWidth)
            velocity.x = -ball_velocity;
        if (top() < 0)
            velocity.y = ball_velocity;
        else if (bottom() > windowHeight)
            velocity.y = -ball_velocity;
    }

    float x() { return shape.getPosition().x; }

    float y() { return shape.getPosition().y; }

    float left() { return x() - shape.getRadius(); }

    float right() { return x() + shape.getRadius(); }

    float top() { return y() - shape.getRadius(); }

    float bottom() { return y() + shape.getRadius(); }

protected:
};

Ball::Ball(float X, float Y) {
    shape.setPosition(X, Y);
    shape.setRadius(radius);
    shape.setFillColor(Color::Red);
    shape.setOrigin(radius, radius);
}

class Rectangle :public Objects
{
public:
    RectangleShape shape;

    float x() { return shape.getPosition().x; }

    float y() { return shape.getPosition().y; }

    float left() { return x() - shape.getSize().x / 2.f; }

    float right() { return x() + shape.getSize().x / 2.f; }

    float top() { return y() - shape.getSize().y / 2.f; }

    float bottom() { return y() + shape.getSize().y / 2.f; }

protected:
};

class Paddle : public Rectangle
{
public:
    Vector2f velocity;

    Paddle(float mX, float mY)
    {
        shape.setPosition(mX, mY);
        shape.setSize({ paddleWidth, paddleHeight });
        shape.setFillColor(Color::Blue);
        shape.setOrigin(paddleWidth / 2.f, paddleHeight / 2.f);
    }

    void update()
    {
        shape.move(velocity);

        if (Keyboard::isKeyPressed(Keyboard::Key::Left) && left() > 0)
            velocity.x = -paddleVelocity;
        else if (Keyboard::isKeyPressed(Keyboard::Key::Right) &&
            right() < windowWidth)
            velocity.x = paddleVelocity;
        else
            velocity.x = 0;
    }
protected:
};

class Brick : public Rectangle
{
public:

    bool destroyed{ false };

    Brick(float mX, float mY)
    {
        shape.setPosition(mX, mY);
        shape.setSize({ block_width, block_height });
        shape.setFillColor(Color::White);
        shape.setOrigin(block_width / 2.f, block_height / 2.f);
    }
private:
};

class HP
{
public:
    Texture texture;
    Sprite sprite;
    HP(float mX, float mY);
    void HP_init() {
        texture.loadFromFile("HP.jpg");
        sprite.setTexture(texture);
    }
private:
};

HP::HP(float mX, float mY) {
    sprite.setPosition(mX, mY);
}

template <class T1, class T2>
bool isIntersecting(T1& mA, T2& mB)
{
    return mA.right() >= mB.left() && mA.left() <= mB.right() &&
        mA.bottom() >= mB.top() && mA.top() <= mB.bottom();
}

void testCollision(Paddle& mPaddle, Ball& mBall)
{
    if (!isIntersecting(mPaddle, mBall)) return;

    mBall.velocity.y = -mBall.return_ball_velocity();
    if (mBall.x() < mPaddle.x())
        mBall.velocity.x = -mBall.return_ball_velocity();
    else
        mBall.velocity.x = mBall.return_ball_velocity();
}

void testCollision(Brick& mBrick, Ball& mBall)
{
    if (!isIntersecting(mBrick, mBall)) return;
    mBrick.destroyed = true;

    float overlapLeft{ mBall.right() - mBrick.left() };
    float overlapRight{ mBrick.right() - mBall.left() };
    float overlapTop{ mBall.bottom() - mBrick.top() };
    float overlapBottom{ mBrick.bottom() - mBall.top() };

    bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
    bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

    float minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
    float minOverlapY{ ballFromTop ? overlapTop : overlapBottom };

    if (abs(minOverlapX) < abs(minOverlapY))
        mBall.velocity.x = ballFromLeft ? -mBall.return_ball_velocity() : mBall.return_ball_velocity();
    else
        mBall.velocity.y = ballFromTop ? -mBall.return_ball_velocity() : mBall.return_ball_velocity();

}

int main()
{
    Ball ball{ windowWidth / 2, windowHeight / 2 };
    Paddle paddle{ windowWidth / 2, windowHeight - 50 };
    vector<Brick> bricks;
    vector<HP> hp;

    for (int iX{ 0 }; iX < countBlocksX; ++iX)
        for (int iY{ 0 }; iY < countBlocksY; ++iY)
            bricks.emplace_back((iX + 1) * (paddle.return_block_width() + 3) + 22, (iY + 2) * (paddle.return_block_height() + 3));

    for (int i = 0; i < 3; i++) {
        hp.emplace_back(windowWidth - (32 * 3) + (i * 32), windowHeight - 32);
    }

    for (auto& hill_point : hp) hill_point.HP_init();

    int c;
    cin >> c;
    while (c == 1) {
        RenderWindow window{ {windowWidth, windowHeight}, "Arkanoid - 9" };
        window.setFramerateLimit(60);

        while (true)
        {
            window.clear(Color::Black);

            if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) break;

            ball.update();
            paddle.update();
            if (ball.y() == windowHeight) { window.close(); }
            testCollision(paddle, ball);
            for (auto& brick : bricks) testCollision(brick, ball);
            bricks.erase(remove_if(begin(bricks), end(bricks),
                [](const Brick& mBrick)
                {
                    return mBrick.destroyed;
                }),
                end(bricks));

            window.draw(ball.shape);
            window.draw(paddle.shape);
            for (auto& brick : bricks) window.draw(brick.shape);
            for (auto& hill_point : hp) window.draw(hill_point.sprite); // рисуем хп
            window.display();
            if (ball.y() > paddle.y() + 50 - (ball.return_radius() / 2)) // соприкосновение с нижней границей
            {
                helth--; hp.erase(hp.begin());  // отнимаем жизнь и удаляем элемент вектора
                for (auto& hill_point : hp) if (helth != 0) hill_point.HP_init(); // рисуем поверх вектора спрайт
            }
            if (helth == 0) { window.close(); }
        }
    }
    return 0;
}
