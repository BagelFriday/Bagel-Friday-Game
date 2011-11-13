#ifndef GRID
#define GRID

#include <SFML/Graphics.hpp>
#include "Resource.h"

#define GRID_SIZE 5
#define NUM_RESOURCE_KINDS 3

class Game;

class Grid
{
private:
public:
	sf::Vector2f position;

	static const int MAX_GRID_WIDTH = 5;
	static const int MAX_GRID_HEIGHT = 5;
	// <= the max values
	// rows and columns

	int gridWidth;
	int gridHeight;
	int numActiveResources;

	Resource* resourceCellArray[GRID_SIZE][GRID_SIZE];
	// actual pixel size of grid
	int viewportWidth;
	int viewportHeight;

	Grid();
	~Grid();

	void SpawnResource(Game *game);
	void RemoveResource(Resource* resourceCell);

	void Display(Game *game);

	void SetSize(int rows, int columns);
};

#endif // GRID