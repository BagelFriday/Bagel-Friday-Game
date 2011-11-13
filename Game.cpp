#include "Game.h"
#include "Entity.h"


Game::Game(int _screenWidth, int _screenHeight, int bpp, unsigned long mode, std::string title)
:
screenWidth(_screenWidth),
screenHeight(_screenHeight)
{
	sf::VideoMode vmode = sf::VideoMode(screenWidth, screenHeight, bpp);

	window.Create(vmode, title, mode);

	sf::Randomizer::SetSeed(static_cast<unsigned int>(time(NULL)));

	resourceFont.LoadFromFile("arial.ttf", 50);

	pointFont.LoadFromFile("arial.ttf", 80);
}

void Game::Initialize()
{
	grid.position = sf::Vector2f(0.0f, 0.0f);

	player1.Initialize(this, "Art/player1.png", pointFont, 80.0f);
	player2.Initialize(this, "Art/player2.png", pointFont, 80.0f);
	cannon.Initialize( this );

	background.Initialize(this, "Art/background.png");

	grid.SpawnResource(this);
	resourceSpawnTimer.Reset();
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
				if(Event.Key.Code == sf::Key::Space)
					cannon.FireShot( sf::Vector2f(100, 100), this );
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
		window.Clear(sf::Color(0, 0, 0));

		Update(window.GetFrameTime());

		Display();

		// Display window contents on screen
		window.Display();
	}
}

void Game::Update(float deltaTime)
{
	UpdateInput(deltaTime);

	if(numActiveResources < Grid::MAX_GRID_WIDTH * Grid::MAX_GRID_HEIGHT && resourceSpawnTimer.GetElapsedTime() > 1.0f )
	{
		grid.SpawnResource(this);
		resourceSpawnTimer.Reset();
	}

	for (int i = 0; i < Grid::MAX_GRID_HEIGHT; i++)
	{
		for (int j = 0; j < Grid::MAX_GRID_WIDTH; j++)
		{
			if( grid.resourceCellArray[i][j] != NULL && // Check to see if cell Exists
				window.GetInput().IsKeyDown((sf::Key::Code)grid.resourceCellArray[i][j]->key) )// If key for cell is pressed
			{
				bool p1_collect = player1.CheckSquare( grid.resourceCellArray[i][j] );
				bool p2_collect = player2.CheckSquare( grid.resourceCellArray[i][j] );

				if( p1_collect )
				{
					player1.myPoints += grid.resourceCellArray[i][j]->pointValue;
				}
				if( p2_collect )
				{
					player1.myPoints += grid.resourceCellArray[i][j]->pointValue;
				}
				if( p1_collect || p2_collect )
				{
					grid.RemoveResource( grid.resourceCellArray[i][j] );
				}
			}
		}
	}

	player1.Update(this, deltaTime);
	player2.Update(this, deltaTime);
	cannon.UpdateShots(deltaTime);

	// Points display in the appropriate corner
	static const float TEXT_INSET = 10.0f;
	player1.pointDisplay.SetPosition(sf::Vector2f(0.0f + TEXT_INSET, screenHeight - player1.pointDisplay.GetRect().GetHeight() - TEXT_INSET));
	player2.pointDisplay.SetPosition(sf::Vector2f(screenWidth - player1.pointDisplay.GetRect().GetWidth() - TEXT_INSET, screenHeight - player1.pointDisplay.GetRect().GetHeight() - TEXT_INSET));
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
	window.Draw(background);

	// Display grid
	grid.Display(this);

	window.Draw(player1);
	window.Draw(player2);
	window.Draw(cannon.sprite);
	
	std::deque<Entity>::iterator i = cannon.Shots.begin();
	for(; i != cannon.Shots.end(); ++i)
	{
		if( i->Visible )
		{
			window.Draw(*i);
		}
	}
	window.Draw(player1.pointDisplay);
	window.Draw(player2.pointDisplay);
}

std::string Game::KeyToString(int keyCode)
{
	std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

	// Normalize to 0, yes this is dumb
	keyCode -= 97;

	return alphabet.substr(keyCode, 1);
}