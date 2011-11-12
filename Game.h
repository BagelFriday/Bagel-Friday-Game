#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "ImagePool.h"
#include "Entity.h"
#include "Grid.h"

class Game
{
private:
public:
	int screenWidth;
	int screenHeight;

	sf::RenderWindow window;

	ImagePool imagePool;

	Entity player1;
	Entity player2;

	Grid grid;

	// Drawn on resources
	sf::Font resourceFont;

	// Player point totals
	sf::Font pointFont;

	Game(int _screenWidth, int _screenHeight, int bpp, unsigned long mode, std::string title);

	void Initialize();

	void Run();

	void Update(float deltaTime);

	void UpdateInput(float deltaTime);

	void Display();

	bool IsColliding(sf::Rect<float>& rect1, sf::Rect<float>& rect2);

	static std::string KeyToString(int keyCode);
};

#endif // GAME