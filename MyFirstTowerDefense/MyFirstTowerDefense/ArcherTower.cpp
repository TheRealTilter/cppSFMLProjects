#include "stdafx.h"
#include "Tower.h"
#include "ArcherTower.h"

ArcherTower::ArcherTower()
{
	m_Sprite.setOrigin(25, 25);
}

void ArcherTower::placeTower(Vector2f position)
{
	m_isPlaced = true;

	m_Sprite.setPosition(position);
}

