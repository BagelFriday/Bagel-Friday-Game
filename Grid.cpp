#include "Grid.h"
#include "Entity.h"
#include "ImagePool.h"
#include "Game.h"

Grid::Grid()
{ }

void Grid::SetSize(int rows, int columns)
{
	if (rows <= MAX_GRID_HEIGHT)
	{
		gridHeight = rows;
	}
	if (columns <= MAX_GRID_WIDTH)
	{
		gridWidth = columns;
	}
}

void Grid::Populate(Game *game)
{
	for (int i = 0; i < gridWidth; i++)
	{
		for (int j = 0; j < gridHeight; j++)
		{
			grid[i][j] = new Entity();
			
			// Make a random choice of resource
			const int NUM_RESOURCES = 3;
			int randomResource = sf::Randomizer::Random(0, NUM_RESOURCES - 1);
			std::string resourceToLoad;

			switch(randomResource)
			{
			case 0:
				resourceToLoad = "Art/meat.png";
				break;
			case 1:
				resourceToLoad = "Art/sticks.png";
				break;
			case 2:
				resourceToLoad = "Art/gold.png";
				break;
			}
			grid[i][j]->SetImage(*(game->imagePool.loadWithPool(resourceToLoad)));

			grid[i][j]->SetPosition(sf::Vector2f((float)j * grid[i][j]->GetImage()->GetWidth(), (float)i * grid[i][j]->GetImage()->GetHeight()));
		}
	}
}

void Grid::Display(Game *game)
{
	for (int i = 0; i < gridWidth; i++)
	{
		for (int j = 0; j < gridHeight; j++)
		{
			game->window.Draw(*grid[i][j]);
		}
	}
}