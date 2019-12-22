#pragma once
#include <SFML\Graphics.hpp>
#include "Tower.h"
#include "TextureHolder.h"

class ArcherTower : public Tower
{
private:
	Sprite m_Sprite = Sprite(TextureHolder::GetTexture("graphics/player.png"));

	int m_Damage = 10;

	bool m_isPlaced = false;

public:

	ArcherTower::ArcherTower();

	void placeTower(Vector2f position);

	bool getIsAlive();

};