#pragma once
#include <SFML\Graphics.hpp>
#include "TextureHolder.h"

class Engine 
{
private:
	TextureHolder textureHolder;

	Time m_gameTimeTotal;

	sf::RenderWindow m_Window;


	//Private functions
	void input();
	void update(float dtAsSeconds);
	void draw();

public:
	//The constructor
	Engine();

	//run the engine
	void run();
};