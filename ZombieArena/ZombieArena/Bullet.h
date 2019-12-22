#pragma once
#include <SFML\Graphics.hpp>

using namespace sf;

class Bullet
{
private:
	
	//Where is the bullet
	Vector2f m_Position;

	//What each bullet looks like
	RectangleShape m_BulletShape;

	//Is the bullet currently in the air
	bool m_InFlight = false;

	//How fast does each bullet fly
	float m_BulletSpeed = 1000;

	//What fractio of a pixel does the bullet travel every frame
	//Horizontaly and verticaly
	//These values will be derived from m_BulletSpeed
	float m_BulletDistanceX;
	float m_BulletDistanceY;

	//Some variables so the bullet doesn't fly forever
	float m_MaxX;
	float m_MinX;
	float m_MaxY;
	float m_MinY;

public:

	//The constructor
	Bullet();

	//Stop the bullet
	void stop();

	//Returns the value of m_isInFlight
	bool isInFlight();

	//Launch a new bullet
	void shoot(float startX, float startY, float targetX, float targetY);

	//Tell the calling code where is the bullet
	FloatRect getPosition();

	//Return the shape for drawing
	RectangleShape getShape();

	//Update the bullet each frame
	void update(float elapsedTime);
};