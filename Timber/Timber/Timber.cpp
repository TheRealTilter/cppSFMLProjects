// HelloSFML.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>


using namespace sf;

//Function declaration
void updateBranches(int seed);

const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];

//Where is the player/branch
//Left or Right
enum class side { LEFT, RIGHT, NONE};
side branchPositions[NUM_BRANCHES];

int main()
{
	//Create a video mode object
	VideoMode vm(1920, 1080);

	//Create and open a window for the game
	RenderWindow Window(vm, "Timber!!!", Style::Fullscreen);

	// Create a texture to hold a graphic on the GPU
	Texture textureBackground;

	// Load a graphic into the texture
	textureBackground.loadFromFile("graphics/background.png");

	// Create a sprite
	Sprite spriteBackground;

	// Attach the texture to the sprite
	spriteBackground.setTexture(textureBackground);

	// Set the spriteBackground to cover the screen
	spriteBackground.setPosition(0, 0);

	// Make a tree sprite
	Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");
	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(810, 0);

	// Prepare the bee
	Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0, 800);

	// Is the bee currently moving?
	bool beeActive = false;

	// How fast can the bee fly
	float beeSpeed = 0.0f;

	//Making the 3 clouds
	Texture textureCloud;
	textureCloud.loadFromFile("graphics/cloud.png");
	Sprite spriteCloud1;
	Sprite spriteCloud2;
	Sprite spriteCloud3;
	spriteCloud1.setTexture(textureCloud);
	spriteCloud2.setTexture(textureCloud);
	spriteCloud3.setTexture(textureCloud);

	//Positioning the 3 clouds
	spriteCloud1.setPosition(0, 0);
	spriteCloud2.setPosition(0, 250);
	spriteCloud3.setPosition(0, 500);

	//Are the clouds on the screen
	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;

	//How fast is each cloud?
	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;

	//Controling time itself
	Clock clock;

	//Time bar
	RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHeight = 80;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

	Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

	// Track whether the game is running
	bool paused = true;

	//Draw some text
	int score = 0;

	Text messageText;
	Text scoreText;

	//We need to choose a font
	Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	//Set the font to our message
	messageText.setFont(font);
	scoreText.setFont(font);

	//Assing the actual message
	messageText.setString("Press Enter to start!");
	scoreText.setString("Score = 0");

	//Make it really big
	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);

	//Choose a color
	messageText.setFillColor(Color::White);
	scoreText.setFillColor(Color::White);

	//Position the text
	FloatRect textRect = messageText.getLocalBounds();

	messageText.setOrigin
	(
		textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f
	);

	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
	scoreText.setPosition(20, 20);

	//Prepare 6 branches
	Texture textureBranch;
	textureBranch.loadFromFile("graphics/branch.png");

	//Set the texture for each branch sprite
	for (int i = 0; i < NUM_BRANCHES; i++)
	{
		branches[i].setTexture(textureBranch);
		branches[i].setPosition(-2000, -2000);
		//Set the sprite's origin to dead center
		//We can then spin it round without changing its position
		branches[i].setOrigin(220, 20);
	}

	//Prepare the player
	Texture texturePlayer;
	texturePlayer.loadFromFile("graphics/player.png");
	Sprite spritePlayer;
	spritePlayer.setTexture(texturePlayer);
	spritePlayer.setPosition(580,720);

	//The player starts on the left side
	side playerSide = side::LEFT;

	//Prepare the gravestone
	Texture textureRIP;
	textureRIP.loadFromFile("graphics/rip.png");
	Sprite spriteRIP;
	spriteRIP.setTexture(textureRIP);
	spriteRIP.setPosition(600, 860);

	//Prepare the axe
	Texture textureAxe;
	textureAxe.loadFromFile("graphics/axe.png");
	Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);
	spriteAxe.setPosition(700, 830);

	//Line the axe up with the tree
	const float AXE_POSITION_LEFT = 700;
	const float AXE_POSITION_RIGHT = 1075;

	//Prepare the flying log
	Texture textureLog;
	textureLog.loadFromFile("graphics/log.png");
	Sprite spriteLog;
	spriteLog.setTexture(textureLog);
	spriteLog.setPosition(810, 720);

	//Useful log related variables
	bool logActive = false;
	float logSpeedX = 1000;
	float logSpeedY = -1500;

	//Control the player input
	bool acceptInput = false;

	//Prepare the sound
	SoundBuffer chopBuffer;
	chopBuffer.loadFromFile("sound/chop.wav");
	Sound chopSound;
	chopSound.setBuffer(chopBuffer);

	SoundBuffer deathBuffer;
	deathBuffer.loadFromFile("sound/death.wav");
	Sound deathSound;
	deathSound.setBuffer(deathBuffer);

	SoundBuffer ootBuffer;
	ootBuffer.loadFromFile("sound/out_of_time.wav");
	Sound outOfTimeSound;
	outOfTimeSound.setBuffer(ootBuffer);




	//Main game loop
	while (Window.isOpen()) 
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/

		Event event;

		while (Window.pollEvent(event))
		{
			if (event.type == Event::KeyReleased && !paused)
			{
				//accept key inputs again
				acceptInput = true;

				//hide the axe
				spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			Window.close();
		}

		// Start the game
		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			paused = false;

			//Reset the time and score
			score = 0;
			timeRemaining = 6;

			//Make all the branches dissappear
			for (int i = 1; i < NUM_BRANCHES; i++)
			{
				branchPositions[i] = side::NONE;
			}

			//make sure the gravestone is hidden
			spriteRIP.setPosition(675, 2000);

			//Move the player into position
			spritePlayer.setPosition(580, 720);

			acceptInput = true;

		}

		//Wrap the player controls to
		//make sure we are accepting input
		if (acceptInput)
		{
			//More code here later...
			//First handle pressing the right cursor key
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				//Make sure the player is on the right
				playerSide = side::RIGHT;
				score++;

				//Add to the amount of the time remaining
				timeRemaining += (2 / score) + .15;

				spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);

				spritePlayer.setPosition(1200, 720);

				//update the branches
				updateBranches(score);

				//set the log flying to the left
				spriteLog.setPosition(810, 720);
				logSpeedX = -5000;
				logActive = true;

				acceptInput = false;

				//Play a chop sound
				chopSound.play();

			}

			//Handle the left cursor key
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				//Make sure the player is on the left
				playerSide = side::LEFT;
				score++;

				//Add to the amount of time remaining
				timeRemaining += (2 / score) + .15;

				spriteAxe.setPosition(AXE_POSITION_LEFT, spriteAxe.getPosition().y);

				spritePlayer.setPosition(580, 720);

				//upodate the branches
				updateBranches(score);

				//set the log flying
				spriteLog.setPosition(810, 720);
				logSpeedX = 5000;
				logActive = true;

				acceptInput = false;

				//Play a chop sound
				chopSound.play();
			}

		}

		/*
		****************************************
		Update the scene
		****************************************
		*/
		if (!paused)
		{

			//Measure time
			Time dt = clock.restart();

			//Subtract from the total time remaining
			timeRemaining -= dt.asSeconds();

			//resize up the time bar
			timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

			if (timeRemaining <= 0.0f)
			{
				//Pauze the game
				paused = true;

				//Change the message shown to the player
				messageText.setString("Out of time!!");

				//reposition the text based on its new size
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin
				(
					textRect.left + textRect.width / 2.0f,
					textRect.top + textRect.height / 2.0f
				);

				messageText.setPosition(1920 / 2.0, 1080 / 2.0);
				outOfTimeSound.play();
			}


			// Setup the bee
			if (!beeActive)
			{
				//How fast is the bee
				srand((int)time(0));
				beeSpeed = (rand() % 200) + 200;

				//How high is the bee
				srand((int)time(0) * 10);
				float height = (rand() % 500) + 500;
				spriteBee.setPosition(2000, height);
				beeActive = true;
			}
			else
				//Move the bee
			{
				spriteBee.setPosition
				(
					spriteBee.getPosition().x - (beeSpeed *dt.asSeconds()),
					spriteBee.getPosition().y
				);

				//Has the bee reached the left hand edge of the screen
				if (spriteBee.getPosition().x < -100)
				{
					//Set it up to be a whole new bee next frame
					beeActive = false;
				}
			}

			//Manage the clouds
			//Cloud 1
			if (!cloud1Active)
			{
				//How fast is the cloud
				srand((int)time(0) * 10);
				cloud1Speed = (rand() % 200);

				//How high is the cloud
				srand((int)time(0) * 10);
				float height = (rand() % 150);
				spriteCloud1.setPosition(-200, height);
				cloud1Active = true;
			}
			else
			{
				spriteCloud1.setPosition
				(
					spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()),
					spriteCloud1.getPosition().y
				);

				//Has the cloud reached the right side of the screen?
				if (spriteCloud1.getPosition().x > 1920)
				{
					//Set it to be a new cloud next frame
					cloud1Active = false;
				}
			}
			//Cloud 2
			if (!cloud2Active)
			{
				//How fast is the cloud
				srand((int)time(0) * 20);
				cloud2Speed = (rand() % 200);

				//How high is the cloud
				srand((int)time(0) * 20);
				float height = (rand() % 300) - 150;
				spriteCloud2.setPosition(-200, height);
				cloud2Active = true;
			}
			else
			{
				spriteCloud2.setPosition
				(
					spriteCloud2.getPosition().x + (cloud2Speed * dt.asSeconds()),
					spriteCloud2.getPosition().y
				);

				//Has the cloud reached the right side of the screen?
				if (spriteCloud2.getPosition().x > 1920)
				{
					//Set it to be a new cloud next frame
					cloud2Active = false;
				}
			}
			//Cloud 3
			if (!cloud3Active)
			{
				//How fast is the cloud
				srand((int)time(0) * 30);
				cloud3Speed = (rand() % 200);

				//How high is the cloud
				srand((int)time(0) * 30);
				float height = (rand() % 450) - 150;
				spriteCloud3.setPosition(-200, height);
				cloud3Active = true;
			}
			else
			{
				spriteCloud3.setPosition
				(
					spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()),
					spriteCloud3.getPosition().y
				);

				//Has the cloud reached the right side of the screen?
				if (spriteCloud3.getPosition().x > 1920)
				{
					//Set it to be a new cloud next frame
					cloud3Active = false;
				}
			}

			//update the score text
			std::stringstream ss;
			ss << "Score = " << score;
			scoreText.setString(ss.str());

			//Update the branch sprites
			for (int i = 0; i < NUM_BRANCHES; i++)
			{
				float height = i * 150;
				if (branchPositions[i] == side::LEFT)
				{
					//Move the sprite to the left side
					branches[i].setPosition(610, height);

					//Flop it 180 degrees
					branches[i].setRotation(180);
				}
				else if (branchPositions[i] == side::RIGHT)
				{
					//Move the sprite to the right side
					branches[i].setPosition(1330, height);

					//Set rotation to normal
					branches[i].setRotation(0);
				}
				else
				{
					//Hide the branch
					branches[i].setPosition(3000, height);
				}
			}

			//Handle a flying log
			if (logActive)
			{

				spriteLog.setPosition
				(
					spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()),
					spriteLog.getPosition().y + (logSpeedY * dt.asSeconds())
				);

				//Has the log reached the right hand edge?
				if (spriteLog.getPosition().x < -100 || spriteLog.getPosition().x > 2000)
				{
					//Set it up ready to be a whole new log next frame
					logActive = false;
					spriteLog.setPosition(810, 720);
				}
			}

			//Has the player been squashed by a branch?
			if (branchPositions[5] == playerSide)
			{
				//death
				paused = true;
				acceptInput = false;

				//Draw the graestone
				spriteRIP.setPosition(525, 760);

				//hide the player
				spritePlayer.setPosition(2000, 600);

				//Change the text of the message
				messageText.setString("SQUISHED!!");

				// Center it on the screen
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin
				(
					textRect.left + textRect.width / 2.0f,
					textRect.top + textRect.height / 2.0f
				);

				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

				//Play the death sound
				deathSound.play();
			}

		}//End if not paused

		/*
		****************************************
		Draw the scene
		****************************************
		*/

		// Clear everything from the last frame
		Window.clear();

		//Draw our scene here
		//Window.draw(spriteBackground);

		//Draw the clouds
		Window.draw(spriteCloud1);
		Window.draw(spriteCloud2);
		Window.draw(spriteCloud3);

		//Draw the branches
		for (int i = 0; i < NUM_BRANCHES; i++)
		{
			Window.draw(branches[i]);
		}

		//Draw the tree
		Window.draw(spriteTree);

		//Draw the player
		Window.draw(spritePlayer);

		//Draw the axe
		Window.draw(spriteAxe);

		//Draw the flying log
		Window.draw(spriteLog);

		//Draw thegravestone
		Window.draw(spriteRIP);

		//Draw the bee
		Window.draw(spriteBee);

		//Draw the score
		Window.draw(scoreText);

		//Draw the timebar
		Window.draw(timeBar);

		if (paused)
		{
			//Draw our message
			Window.draw(messageText);
		}

		//Show everything we just drew
		Window.display();

	}

    return 0;
}

//Function definiton
void updateBranches(int seed)
{
	//Move all branches down one place
	for (int j = NUM_BRANCHES - 1; j > 0; j--)
	{
		branchPositions[j] = branchPositions[j - 1];
	}

	// Spawn a new branch on position 0
	// LEFT, RIGHT or NONE
	srand((int)time(0) + seed);
	int r = (rand() % 5);
	switch (r)
	{
	case 0:
		branchPositions[0] = side::LEFT;
		break;
	case 1:
		branchPositions[0] = side::RIGHT;
		break;
	default:
		branchPositions[0] = side::NONE;
		break;
	}
}