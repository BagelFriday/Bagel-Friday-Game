#include "Entity.h"
#include "Game.h"

Entity::Entity()
{
	speed = sf::Vector2f( 2.0f, 2.0f );
}

void Entity::Update(Game *game, float deltaTime)
{
	// Are we over a tile?
	for (int i = 0; i < game->grid.gridWidth; i++)
	{
		for (int j = 0; j < game->grid.gridHeight; j++)
		{
			if (game->grid.grid[i][j]->isAlive && game->IsColliding(GetRect(), game->grid.grid[i][j]->GetRect()))
			{
				game->grid.grid[i][j]->Die();
				// do thangs
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