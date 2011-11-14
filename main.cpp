#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Game.h"

int main()
{
	Game theGame(1024, 768, 32, sf::Style::Fullscreen, "A History of Humanity: 0-2011");

	theGame.Run();

	return EXIT_SUCCESS;
}
