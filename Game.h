#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "ImagePool.h"

class Entity;;

class Game
{
private:
public:
	sf::RenderWindow window;

	ImagePool imagePool;

	std::vector<Entity*> entities;

	Game(int screenWidth, int screenHeight, int bpp, unsigned long mode, std::string title);

	void Initialize();

	void Run();

	void Update(float deltaTime);

	void Display();
};

#endif // GAME