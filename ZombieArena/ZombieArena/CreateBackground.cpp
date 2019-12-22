#include "stdafx.h"
#include "ZombieArena.h"
#include <SFML\Graphics.hpp>


int createBackground(VertexArray& rVA, IntRect arena)
{
	const int TILE_SIZE = 50;
	const int TILE_TYPES = 3;
	const int VERTS_IN_QUAD = 4;

	//Sizes are in tiles not pixels
	int worldWidth = arena.width / TILE_SIZE; 
	int worldHeight = arena.height / TILE_SIZE;

	// What kind of primitive are we using?
	rVA.setPrimitiveType(Quads);

	// Set the size of the vertex array
	rVA.resize(worldWidth * worldHeight * VERTS_IN_QUAD);

	// Start at the begining of the vertex array
	int currentVertex = 0;

	for (int w = 0; w < worldHeight; w++)
	{
		for (int h = 0; h < worldWidth; h++)
		{
			// Position each vertex in the current quad
			//verts go(0,0)->(49,0)->(49,49)->(0,49)  <- IMPORTANT that is only the first one
			rVA[currentVertex + 0].position = Vector2f(w * TILE_SIZE, h * TILE_SIZE);
			rVA[currentVertex + 1].position = Vector2f((w * TILE_SIZE) + TILE_SIZE, h * TILE_SIZE);
			rVA[currentVertex + 2].position = Vector2f((w * TILE_SIZE) + TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE);
			rVA[currentVertex + 3].position = Vector2f(w * TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE);

			// Define the position in the Texture for current quad
			// Either grass, stone, bush or wall
			if (h == 0 || h == worldHeight - 1 || w == 0 || w == worldWidth - 1)
			{
				// Use the wall texture
				rVA[currentVertex + 0].texCoords = Vector2f(0, 0 + TILE_TYPES * TILE_SIZE - 1);
				rVA[currentVertex + 1].texCoords = Vector2f(TILE_SIZE - 1, 0 + TILE_TYPES * TILE_SIZE - 1);
				rVA[currentVertex + 2].texCoords = Vector2f(TILE_SIZE - 1, TILE_SIZE + TILE_TYPES * TILE_SIZE - 1);
				rVA[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + TILE_TYPES * TILE_SIZE - 1);
			}
			else
			{
				// Use a random floor texture
				srand((int)time(0) + h * w - h);
				int mOrG = (rand() % TILE_TYPES);
				int verticalOffset = mOrG * TILE_SIZE;

				rVA[currentVertex + 0].texCoords = Vector2f(0, 0 + verticalOffset - 1);
				rVA[currentVertex + 1].texCoords = Vector2f(TILE_SIZE - 1, 0 + verticalOffset - 1);
				rVA[currentVertex + 2].texCoords = Vector2f(TILE_SIZE - 1, TILE_SIZE + verticalOffset - 1);
				rVA[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + verticalOffset - 1);
			}

			currentVertex = currentVertex + VERTS_IN_QUAD;
		}
	}

	return TILE_SIZE;
}