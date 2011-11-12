#include "Game.h"

Game::Game(int screenWidth, int screenHeight, int bpp, unsigned long mode, std::string title)
{
	sf::VideoMode vmode = sf::VideoMode(screenWidth, screenHeight, bpp);

	window.Create(vmode, title, mode);
}

void Game::Initialize()
{ }

void Game::Run()
{
	Initialize();

	while (window.IsOpened())
	{
		// Process events
		sf::Event Event;
		while (window.GetEvent(Event))
		{
			// Close window : exit
			if (Event.Type == sf::Event::Closed)
				window.Close();

			// A key has been pressed
			if (Event.Type == sf::Event::KeyPressed)
			{
				// Escape key : exit
				if (Event.Key.Code == sf::Key::Escape)
					window.Close();

				// F1 key : capture a screenshot
				if (Event.Key.Code == sf::Key::F1)
				{
					sf::Image Screen = window.Capture();
					Screen.SaveToFile("screenshot.jpg");
				}
			}
		}

		// Clear the screen with red color
		window.Clear(sf::Color(200, 0, 0));

		Update(window.GetFrameTime());

		Display();

		// Display window contents on screen
		window.Display();
	}
}

void Game::Update(float deltaTime)
{ }

void Game::Display()
{ }