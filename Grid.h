#ifndef GRID
#define GRID

#include <SFML/Graphics.hpp>
#include "Resource.h"

class Game;

class Grid
{
private:
public:
	sf::Vector2f position;

	// Attributes
	static const int MAX_GRID_WIDTH = 5;
	static const int MAX_GRID_HEIGHT = 5;
	// <= the max values
	// rows and columns
	int gridWidth;
	int gridHeight;

	// actual pixel size of grid
	int viewportWidth;
	int viewportHeight;

	Resource* grid[MAX_GRID_WIDTH][MAX_GRID_HEIGHT];

	Grid();

	void Populate(Game *game);

	void Display(Game *game);

	void SetSize(int rows, int columns);
};

#endif // GRID