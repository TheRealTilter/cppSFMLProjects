#include "stdafx.h"
#include "Engine.h"


Engine::Engine() 
{
	// Get the screen resolution and create an SFML window and View
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	//The VideoMode init
	VideoMode vm(resolution.x, resolution.y);

	//Get a window
	m_Window.create(VideoMode(resolution.x, resolution.y), "Tower Defense", Style::Fullscreen);

	RectangleShape emptyPlace;
	emptyPlace.setSize(Vector2f(50, 50));
	emptyPlace.setOrigin(Vector2f(25, 25));

	Vector2f towerPlaces[2];
	towerPlaces[0] = Vector2f(500, 500);
	towerPlaces[1] = Vector2f(1000, 800);
}

void Engine::run()
{
	//Time Control
	Clock clock;

	while (m_Window.isOpen())
	{
		Time dt = clock.restart();
		m_gameTimeTotal += dt;
		float dtAsSeconds = dt.asSeconds();

		input();
		update(dtAsSeconds);
		draw();
	}
}