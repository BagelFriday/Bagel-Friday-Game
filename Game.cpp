#include "Game.h"
#include "Entity.h"


Game::Game(int screenWidth, int screenHeight, int bpp, unsigned long mode, std::string title)
{
	sf::VideoMode vmode = sf::VideoMode(screenWidth, screenHeight, bpp);

	window.Create(vmode, title, mode);
}

void Game::Initialize()
{
	// Populate the grid
	for (int i = 0; i < GRID_WIDTH; i++)
	{
		for (int j = 0; j < GRID_HEIGHT; j++)
		{
			grid[i][j] = new Entity();
			grid[i][j]->SetImage(*(imagePool.loadWithPool("Art/meat.png")));
			grid[i][j]->SetPosition(sf::Vector2f((float)j * grid[i][j]->GetImage()->GetWidth(), (float)i * grid[i][j]->GetImage()->GetHeight()));
		}
	}

	player1.SetImage(*(imagePool.loadWithPool("Art/player1.png")));
	player2.SetImage(*(imagePool.loadWithPool("Art/player2.png")));
}

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
{
	UpdateInput(deltaTime);
}

void Game::UpdateInput(float deltaTime)
{
	const sf::Input& input = window.GetInput();

	if( fabs( input.GetJoystickAxis( 0, sf::Joy::AxisX ) ) > 25.0f )
	{
		player1.Move( player1.speed.x * input.GetJoystickAxis( 0, sf::Joy::AxisX ) * deltaTime, 0.0f );
	}
	if( fabs( input.GetJoystickAxis( 0, sf::Joy::AxisY ) ) > 25.0f )
	{
		player1.Move( 0.0f, player1.speed.y * input.GetJoystickAxis( 0, sf::Joy::AxisY ) * deltaTime );
	}
	if( fabs( input.GetJoystickAxis( 0, sf::Joy::AxisU ) ) > 25.0f )
	{
		player2.Move( player1.speed.x * input.GetJoystickAxis( 0, sf::Joy::AxisU ) * deltaTime, 0.0f );
	}
	if( fabs( input.GetJoystickAxis( 0, sf::Joy::AxisR ) ) > 25.0f )
	{
		player2.Move( 0.0f, player1.speed.y * input.GetJoystickAxis( 0, sf::Joy::AxisR ) * deltaTime );
	}
}

void Game::Display()
{
	// Display grid
	for (int i = 0; i < GRID_WIDTH; i++)
	{
		for (int j = 0; j < GRID_HEIGHT; j++)
		{
			Entity d = *grid[i][j];
			window.Draw(d);
		}
	}

	window.Draw(player1);
	window.Draw(player2);
}