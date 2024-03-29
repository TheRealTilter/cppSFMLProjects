// HelloSFML.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML\Graphics.hpp>
#include <iostream>

using namespace sf;

enum class Direction { UP, DOWN, LEFT, RIGHT };

void move(Direction dir, int bodySize);

int main()
{
	RectangleShape testShape;
	testShape.setSize(Vector2f(2, 2));
	testShape.setPosition(500, 500);

	Time timePassed;

	sf::VideoMode vm(1920, 1080);
	sf::RenderWindow window(vm, "Snake", sf::Style::Default);

	View mainView(FloatRect(0, 0, 1920, 1080));

	bool acceptInput = false;

	Clock clock;

	Direction dir = Direction::RIGHT;

	Time gameTimeTotal;

	int bodySize = 6;

	CircleShape body[30];
	body[0].setPosition(500, 500);
	body[1].setPosition(480, 500);
	body[2].setPosition(460, 500);
	body[3].setPosition(440, 500);
	body[4].setPosition(420, 500);
	body[5].setPosition(400, 500);
	for (int i = 0; i < 30; i++)
	{
		body[i].setRadius(9);
		body[i].setOrigin(9, 9);
	}
	while (window.isOpen())
	{

		Event event;
		while (window.pollEvent(event))
		{
			
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			dir = Direction::UP;
		}

		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			dir = Direction::LEFT;
		}

		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			dir = Direction::DOWN;
		}

		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			dir = Direction::RIGHT;
		}
		Time dt = clock.restart();
		gameTimeTotal += dt;
		std::cout << gameTimeTotal.asMilliseconds() << "\n";
		/////////////////////////////////////////////////////////////////////
		if (gameTimeTotal.asMilliseconds() - timePassed.asMilliseconds() >= 500) {
			////////////////////////////////////
			for (int i = bodySize; i > 0; i--)
			{
				Vector2f pos = body[i - 1].getPosition();
				body[i].setPosition(pos);
			}
			////////////////////////////////////
			std::cout << "Move called\n";
			timePassed = gameTimeTotal;
			int moveX, moveY;
			switch (dir)
			{
			case Direction::LEFT:
				moveX = - 20;
				moveY = 0;
				break;

			case Direction::RIGHT:
				moveX = + 20;
				moveY = 0;
				break;

			case Direction::UP:
				moveX = 0;
				moveY = - 20;
				break;

			case Direction::DOWN:
				moveX = 0;
				moveY = + 20;
				break;

			}
			int posX = body[0].getPosition().x;
			int posY = body[0].getPosition().y;
			body[0].setPosition(Vector2f(posX + moveX, posY + moveY));
		}
		/////////////////////////////////////////////////////////////////////
		window.clear();

		for (int i = 0; i < bodySize; i++)
		{
			window.draw(body[i]);
		}
		

		window.display();

	}
    return 0;
}

/*void move(Direction dir, int bodySize)
{
	int moveX, moveY;
	switch (dir)
	{
	case Direction::LEFT:
		moveX = -20;
		moveY = 0;
		break;

	case Direction::RIGHT:
		moveX = +20;
		moveY = 0;
		break;

	case Direction::UP:
		moveX = 0;
		moveY = -20;
		break;

	case Direction::DOWN:
		moveX = 0;
		moveY = +20;
		break;

	}

	body[0];
}*/
