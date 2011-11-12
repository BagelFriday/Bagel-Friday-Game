#include <sstream>
#include "Player.h"
#include "Game.h"
#include "ImagePool.h"

Player::Player()
: Entity()
{
}

void Player::Initialize(Game *game, std::string filename, sf::Font& font, float fontSize)
{
	Entity::Initialize(game, filename);

	pointDisplay.SetFont(font);
	pointDisplay.SetText("0");
	pointDisplay.SetSize(fontSize);
}

void Player::Update(Game *game, float deltaTime)
{
	Entity::Update(game, deltaTime);

	// Are we over a tile?
	for (int i = 0; i < game->grid.gridWidth; i++)
	{
		for (int j = 0; j < game->grid.gridHeight; j++)
		{
			if (game->grid.grid[i][j]->isAlive		// This tile is active
				&& game->IsColliding(GetRect(), game->grid.grid[i][j]->GetRect())	// We're touching it
				&& game->window.GetInput().IsKeyDown((sf::Key::Code)game->grid.grid[i][j]->key))	// We're pressing the right key
			{
				// Kill the tile
				game->grid.grid[i][j]->Die();

				// Grab points
				myPoints += game->grid.grid[i][j]->pointValue;
				UpdatePointDisplay();
			}
		}
	}
}

void Player::UpdatePointDisplay()
{
	std::stringstream ss;
	ss << myPoints;
	pointDisplay.SetText(ss.str());
}