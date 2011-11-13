#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Game.h"

int main()
{
	Game theGame(1024, 768, 32, sf::Style::Close, "TeamBagelFriday");

	theGame.Run();

	return EXIT_SUCCESS;
}
