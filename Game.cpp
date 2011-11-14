#include "Game.h"
#include "Entity.h"
#include <sstream>



Game::Game(int _screenWidth, int _screenHeight, int bpp, unsigned long mode, std::string title)
:
screenWidth(_screenWidth),
screenHeight(_screenHeight)
{
	SetVideoMode(_screenWidth, _screenHeight, bpp, mode, title);

	sf::Randomizer::SetSeed(static_cast<unsigned int>(time(NULL)));

	resourceFont.LoadFromFile("arial.ttf", 50);

	ageFont.LoadFromFile("arial.ttf", 30);

	pointFont.LoadFromFile("arial.ttf", 80);
}

void Game::SetVideoMode(int _screenWidth, int _screenHeight, int bpp, unsigned long mode, std::string title)
{
	sf::VideoMode vmode = sf::VideoMode(screenWidth, screenHeight, bpp);

	window.Create(vmode, title, mode);
}

void Game::Initialize()
{
	grid.position = sf::Vector2f(0.0f, 0.0f);

	player1.Initialize(this, "Art/player1.png", pointFont, 80.0f);
	player2.Initialize(this, "Art/player2.png", pointFont, 80.0f);
	player2.SetX(screenWidth - player2.GetRect().GetWidth());
	cannon.Initialize( this );
	music.OpenFromFile( "Sound/Modest_Mussorgsky_-_night_on_bald_mountain.ogg" );
	music.Play();

	collection.LoadFromFile( "Sound/75235__creek23__cha-ching.wav" );

	background.Initialize(this, "Art/background.png");

	titleScreen.Initialize(this, "Art/title.png");
	instructionScreen.Initialize(this, "Art/instructions.png");

	grid.SpawnResource(this);
	resourceSpawnTimer.Reset();

	ageDisplay.SetText("first age");
	ageDisplay.SetFont(resourceFont);
	ageDisplay.SetSize(30);
	ageDisplay.SetPosition(0.0f, 660.0f);

	gameState = TITLE_SCREEN;

	gameEra = FIRST_AGE;
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
				if( grid.keyMap.find(Event.Key.Code) != grid.keyMap.end() )
				{
					sf::Vector2i target(grid.keyMap[Event.Key.Code].x, grid.keyMap[Event.Key.Code].y);

					cannon.FireShot( target, this );

				}
				// Escape key : exit
				if (Event.Key.Code == sf::Key::Escape)
					window.Close();
				if (Event.Key.Code == sf::Key::Return)
				{
					if (gameState == TITLE_SCREEN)
					{
						gameState = INSTRUCTION_SCREEN;
					}
					else if (gameState == INSTRUCTION_SCREEN)
					{
						gameState = GAME_PLAYING;
						gameTime.Reset();
					}
				}

				if (Event.Key.Code == sf::Key::F11)
				{
					// Switch to windowed mode
					SetVideoMode(screenWidth, screenHeight, 32, sf::Style::Close, "A History of Humanity: 0-2011");
				}
				else if (Event.Key.Code == sf::Key::F12)
				{
					// Fullscreen
					SetVideoMode(screenWidth, screenHeight, 32, sf::Style::Fullscreen, "A History of Humanity: 0-2011");
				}

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

		if (gameState == TITLE_SCREEN)
		{
			DisplayTitleScreen();
		}
		else if (gameState == INSTRUCTION_SCREEN)
		{
			DisplayInstructionScreen();
		}
		else if (gameState == GAME_PLAYING)
		{
			Update(window.GetFrameTime());
			Display();
		}
		else if (gameState == GAME_OVER)
		{
			DisplayGameOver();
		}

		// Display window contents on screen
		window.Display();
	}
}

void Game::KeepPlayerInScreen(Player& player)
{
	sf::Vector2f myCenter = player.GetCenter();
	sf::Vector2f myPosition = player.GetPosition();

	if (myCenter.x <= 0)
	{
		player.SetX(-(player.GetRect().GetWidth() / 2.0f));
	}
	else if (myCenter.x > (screenWidth - 2))
	{
		player.SetX((screenWidth - 2) - (player.GetRect().GetWidth() / 2.0f));
	}

	if( myCenter.y <= 0 )
	{
		player.SetY(-(player.GetRect().GetHeight() / 2.f));
	}
	else if( myCenter.y > 658 )
	{
		player.SetY( 658 - (player.GetRect().GetHeight() / 2.f) );
	}
}

void Game::DisplayTitleScreen()
{
	window.Draw(titleScreen);
}

void Game::DisplayInstructionScreen()
{
	window.Draw(instructionScreen);
}

void Game::DisplayGameOver()
{
	window.Draw(player1Points);
	window.Draw(player2Points);
}

void Game::Update(float deltaTime)
{
	if (gameTime.GetElapsedTime() > TIME_OVER)
	{
		// Game over
		gameState = GAME_OVER;

		// Set display text for endgame
		std::stringstream ss;
		ss << "Player 1 total: ";
		ss << player1.myPoints;
		player1Points.SetText(ss.str());
		player1Points.SetFont(pointFont);
		player1Points.SetSize(80);
		player1Points.SetPosition(10.0f, 0.0f);


		std::stringstream ss2;
		ss2 << "Player 2 total: ";
		ss2 << player2.myPoints;
		ss2 << "\n\n\t   who won?";
		player2Points.SetText(ss2.str());
		player2Points.SetFont(pointFont);
		player2Points.SetSize(80);
		player2Points.SetPosition(10.0f, 80.0f);
	}
	else if (gameTime.GetElapsedTime() > THIRD_AGE)
	{
		gameEra = THIRD_AGE;
		ageDisplay.SetText("final age");
	}
	else if (gameTime.GetElapsedTime() > SECOND_AGE)
	{
		gameEra = SECOND_AGE;
		ageDisplay.SetText("second age");
	}
	else if (gameTime.GetElapsedTime() > FIRST_AGE)
	{
		gameEra = FIRST_AGE;
		ageDisplay.SetText("first age");
	}

	UpdateInput(deltaTime);

	KeepPlayerInScreen(player1);
	KeepPlayerInScreen(player2);

	if(numActiveResources < Grid::MAX_GRID_WIDTH * Grid::MAX_GRID_HEIGHT && resourceSpawnTimer.GetElapsedTime() > 1.5f )
	{
		grid.SpawnResource(this);
		resourceSpawnTimer.Reset();
	}

	sf::Vector2i playerCell1 = player1.getCellLocation(grid);
	sf::Vector2i playerCell2 = player2.getCellLocation(grid);
	bool p1_collect = false;
	bool p2_collect = false;

	if( grid.resourceCellArray[playerCell1.x][playerCell1.y] && // Check to see if cell Exists
		window.GetInput().IsKeyDown((sf::Key::Code)grid.resourceCellArray[playerCell1.x][playerCell1.y]->key) )// If key for cell is pressed
	{
		p1_collect = true;

		player1.myPoints += grid.resourceCellArray[playerCell1.x][playerCell1.y]->pointValue;
	}
	if( grid.resourceCellArray[playerCell2.x][playerCell2.y] && // Check to see if cell Exists
		window.GetInput().IsKeyDown((sf::Key::Code)grid.resourceCellArray[playerCell2.x][playerCell2.y]->key) )// If key for cell is pressed
	{
		p2_collect = true;

		player2.myPoints += grid.resourceCellArray[playerCell2.x][playerCell2.y]->pointValue;
	}
	if( p1_collect )
	{
		grid.RemoveResource( playerCell1.x, playerCell1.y );
		grid.resourceCellArray[playerCell1.x][playerCell1.y] = NULL;
	}
	if( p2_collect && !(playerCell1.x == playerCell2.x && playerCell1.y == playerCell2.y) )
	{
		grid.RemoveResource( playerCell2.x, playerCell2.y );
		grid.resourceCellArray[playerCell2.x][playerCell2.y] = NULL;
	}

	player1.Update(this, deltaTime);
	player2.Update(this, deltaTime);
	cannon.UpdateShots(deltaTime, this);

	// Points display in the appropriate corner
	static const float TEXT_INSET = 10.0f;
	player1.pointDisplay.SetPosition(sf::Vector2f(0.0f + TEXT_INSET, screenHeight - player1.pointDisplay.GetRect().GetHeight() - TEXT_INSET));
	player2.pointDisplay.SetPosition(sf::Vector2f(screenWidth - player1.pointDisplay.GetRect().GetWidth() - TEXT_INSET, screenHeight - player1.pointDisplay.GetRect().GetHeight() - TEXT_INSET));

	for (int i = 0; i < Grid::MAX_GRID_HEIGHT; i++)
	{
		for (int j = 0; j < Grid::MAX_GRID_WIDTH; j++)
		{
			if (grid.resourceCellArray[i][j])
			{
				grid.resourceCellArray[i][j]->UpdateFade(this);
			}
		}
	}
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
	window.Draw(ageDisplay);
}
/*
std::string Game::KeyToString(int keyCode)
{
	std::string character = "abcdefghijklmnopqrstuvwxyz";

	// Normalize to 0, yes this is dumb
	keyCode -= 97;

	return alphabet.substr(keyCode, 1);
}*/
