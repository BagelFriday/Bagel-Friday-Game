#include "Entity.h"
#include "Game.h"
#include "ImagePool.h"
#include <sstream>

Entity::Entity()
:
myPoints(0)
{
	speed = sf::Vector2f( 2.0f, 2.0f );
}

void Entity::Initialize(Game *game, std::string filename, sf::Font& font, float fontSize, sf::Vector2f pointPos)
{
	SetImage(*(game->imagePool.loadWithPool(filename)));

	pointDisplay.SetFont(font);
	pointDisplay.SetText("0");
	pointDisplay.SetSize(fontSize);
	pointDisplay.SetPosition(pointPos);
}

void Entity::Update(Game *game, float deltaTime)
{
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

sf::Rect<float> Entity::GetRect()
{
	float x, y, w, h;
	x = GetPosition().x;
	y = GetPosition().y;
	w = GetSubRect().GetWidth() * GetScale().x;
	h = GetSubRect().GetHeight() * GetScale().y;
	return sf::Rect<float>(x, y, x + w, y + h);
}

void Entity::UpdatePointDisplay()
{
	std::stringstream ss;
	ss << myPoints;
	pointDisplay.SetText(ss.str());
}