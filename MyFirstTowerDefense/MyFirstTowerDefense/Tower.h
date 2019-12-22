#pragma once
#include <SFML\Graphics.hpp>

using namespace sf;

class Tower
{
private:

	//The sprite for this tower
	Sprite m_Sprite;

	//The position
	Vector2f m_Position;

	//The damage
	int m_Damage;

	bool isPlaced;
public:
	
	void update();

};