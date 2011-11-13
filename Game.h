#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "ImagePool.h"
#include "Player.h"
#include "Cannon.h"
#include "Entity.h"
#include "Grid.h"

class Game
{
private:
public:
	int screenWidth;
	int screenHeight;

	// Total elapsed game time
	sf::Clock gameTime;

	int gameState;
	enum
	{
		TITLE_SCREEN,
		INSTRUCTION_SCREEN,
		GAME_PLAYING,
		GAME_OVER
	};

	// Key times
	int gameEra;
	enum
	{
		FIRST_AGE = 0,
		SECOND_AGE = 5,
		THIRD_AGE = 10,
		TIME_OVER = 15
	};

	sf::Clock resourceSpawnTimer;
	sf::RenderWindow window;

	ImagePool imagePool;

	Player player1;
	Player player2;
	Cannon cannon;
	Entity titleScreen;
	Entity instructionScreen;

	Grid grid;
	int numActiveResources;

	Entity background;

	// Drawn on resources
	sf::Font resourceFont;

	// Player point totals
	sf::Font pointFont;

	sf::String player1Points;
	sf::String player2Points;

	Game(int _screenWidth, int _screenHeight, int bpp, unsigned long mode, std::string title);

	void Initialize();

	void DisplayTitleScreen();

	void DisplayInstructionScreen();

	void DisplayGameOver();

	void Run();

	void Update(float deltaTime);

	void UpdateInput(float deltaTime);

	void Display();

	void KeepPlayerInScreen(Player& player);

	//static std::string KeyToString(int keyCode);
};

#endif // GAME