#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "ImagePool.h"
#include "Entity.h"

class Game
{
private:
public:
	static const int GRID_WIDTH = 4;
	static const int GRID_HEIGHT = 4;

	sf::RenderWindow window;

	ImagePool imagePool;

	Entity player1;
	Entity player2;

	Entity* grid[GRID_WIDTH][GRID_HEIGHT];

	Game(int screenWidth, int screenHeight, int bpp, unsigned long mode, std::string title);

	void Initialize();

	void Run();

	void Update(float deltaTime);

	void UpdateInput(float deltaTime);

	void Display();
};

#endif // GAME