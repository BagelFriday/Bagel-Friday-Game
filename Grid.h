#ifndef GRID
#define GRID

#include <SFML/Graphics.hpp>
#include "Resource.h"

class Game;

class Grid
{
private:
public:
	// Attributes
	static const int MAX_GRID_WIDTH = 4;
	static const int MAX_GRID_HEIGHT = 4;
	// <= the max values
	int gridWidth;
	int gridHeight;

	Resource* grid[MAX_GRID_WIDTH][MAX_GRID_HEIGHT];

	Grid();

	void Populate(Game *game);

	void Display(Game *game);

	void SetSize(int rows, int columns);
};

#endif // GRID