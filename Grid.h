#ifndef GRID
#define GRID

#include <SFML/Graphics.hpp>
#include "Resource.h"

#define NUM_RESOURCE_KINDS 5

class Game;

enum ResourceType
{
	RESOURCE_MEAT,
	RESOURCE_WOOD,
	RESOURCE_STEEL,
	RESOURCE_GOLD,
	RESOURCE_SILICON,
	RESOURCE_LOVE,

	RESOURCE_COUNT
};

class Grid
{
private:
public:
	sf::Vector2f position;

	// Attributes
	static const int MAX_GRID_WIDTH = 8;
	static const int MAX_GRID_HEIGHT = 5;

	static const int NUM_MEAT_VALUES = 10;
	static const int NUM_WOOD_VALUES = 10;
	static const int NUM_STEEL_VALUES = 9;
	static const int NUM_GOLD_VALUES = 7;
	static const int NUM_SILICON_VALUES = 1;
	static const int NUM_HEART_VALUES = NUM_MEAT_VALUES + NUM_WOOD_VALUES + NUM_STEEL_VALUES + NUM_GOLD_VALUES + NUM_SILICON_VALUES;
	// <= the max values
	// rows and columns

	std::map<sf::Key::Code, sf::Vector2i> keyMap;

	char meatChars[NUM_MEAT_VALUES + 1];
	char woodChars[NUM_WOOD_VALUES + 1];
	char steelChars[NUM_STEEL_VALUES + 1];
	char goldChars[NUM_GOLD_VALUES + 1];
	char siliconChars[NUM_SILICON_VALUES + 1];
	char heartChars[NUM_HEART_VALUES + 1];

	int meatCharsIt;
	int woodCharsIt;
	int steelCharsIt;
	int goldCharsIt;
	int siliconCharsIt;
	int heartCharsIt;

	int meatCharsActive;
	int woodCharsActive;
	int steelCharsActive;
	int goldCharsActive;
	int siliconCharsActive;
	int heartCharsActive;

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