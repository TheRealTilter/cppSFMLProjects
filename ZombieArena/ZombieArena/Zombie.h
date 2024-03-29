#pragma once
#include <SFML\Graphics.hpp>

using namespace sf;

class Zombie
{
private:

	// How fast is each zombie type
	const float BLOATER_SPEED = 40;
	const float CHASER_SPEED = 80;
	const float CRAWLER_SPEED = 20;

	// How tough is each zombie
	const float BLOATER_HEALTH = 5;
	const float CHASER_HEALTH = 1;
	const float CRAWLER_HEALTH = 3;

	// Make each zombie vary its speed slightly
	const int MAX_VARIANCE = 30;
	const int OFFSET = 101 - MAX_VARIANCE;

	// Where is the zombie
	Vector2f m_Position;

	//A sprite for the zombie
	Sprite m_Sprite;

	//How fast can this one run/crawl
	float m_Speed;

	//How much health has it got?
	float m_Health;

	//Is it still alive?
	bool m_Alive;

public:

	//Handles a zobie getting hit
	bool hit();

	//Find out if the zombie is alive
	bool isAlive();

	//Spawn a new zombie, Types: 0 - Bloater, 1 - Chaser, 2 - Crawler
	void spawn(float startX, float startY, int type, int seed);

	//Return the rectangle of the zombies position
	FloatRect getPosition();

	//Get a copy of the sprite to draw
	Sprite getSprite();

	//Update the zombie each frame
	void update(float elapsedTime, Vector2f playerLocation);

};