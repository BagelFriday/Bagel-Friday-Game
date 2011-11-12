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
			grid[i][j] = new Resource();
			
			// Make a random choice of resource
			const int NUM_RESOURCES = 3;
			int randomResource = sf::Randomizer::Random(0, NUM_RESOURCES - 1);
			std::string resourceType;

			switch(randomResource)
			{
			case 0:
				resourceType = "meat";
				break;
			case 1:
				resourceType = "sticks";
				break;
			case 2:
				resourceType = "gold";
				break;
			}
			grid[i][j]->SetImage(*(game->imagePool.loadWithPool("Art/" + resourceType + ".png")));
			grid[i][j]->type = resourceType;

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