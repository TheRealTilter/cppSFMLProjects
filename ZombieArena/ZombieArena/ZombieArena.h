#pragma once
#include "Zombie.h"
#include <SFML\Graphics.hpp>


int createBackground(sf::VertexArray& rVA, IntRect arena);
Zombie* createHorde(int numZombies, sf::IntRect arena);