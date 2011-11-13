#ifndef GRID
#define GRID

#include <SFML/Graphics.hpp>
#include "Resource.h"

#define NUM_RESOURCE_KINDS 3

class Game;

class Grid
{
private:
public:
	sf::Vector2f position;

	// Attributes
	static const int MAX_GRID_WIDTH = 8;
	static const int MAX_GRID_HEIGHT = 5;
	// <= the max values
	// rows and columns

	int numActiveResources;

	Resource* resourceCellArray[MAX_GRID_HEIGHT][MAX_GRID_WIDTH];

	// actual pixel size of grid
	int viewportWidth;
	int viewportHeight;

	Grid();
	~Grid();

	void SpawnResource(Game *game);
	void RemoveResource(int row, int col);

	void Display(Game *game);
};

#endif // GRID