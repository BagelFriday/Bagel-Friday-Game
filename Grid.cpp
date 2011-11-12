#include "Grid.h"
#include "Entity.h"
#include "ImagePool.h"
#include "Game.h"

Grid::Grid()
:
viewportWidth(660),
viewportHeight(660)
{
	// Set all NULL
	for (int i = 0; i < MAX_GRID_HEIGHT; i++)
	{
		for (int j = 0; j < MAX_GRID_WIDTH; j++)
		{
			grid[i][j] = NULL;
		}
	}
}

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
			if (grid[i][j] != NULL)
			{
				delete grid[i][j];
			}

			grid[i][j] = new Resource();

			// Make a random choice of resource
			const int NUM_RESOURCES = 3;
			int randomResource = sf::Randomizer::Random(0, NUM_RESOURCES - 1);
			std::string resourceType;
			int pointValue;

			// Random resource
			switch(randomResource)
			{
			case 0:
				resourceType = "meat";
				pointValue = 2;
				break;
			case 1:
				resourceType = "sticks";
				pointValue = 1;
				break;
			case 2:
				resourceType = "gold";
				pointValue = 3;
				break;
			}

			// Key from random resource
			int key;
			if		(resourceType == "meat")		key = sf::Key::M;
			else if (resourceType == "gold")		key = sf::Key::G;
			else if (resourceType == "sticks")		key = sf::Key::S;
			else									key = sf::Key::Z;

			grid[i][j]->SetImage(*(game->imagePool.loadWithPool("Art/" + resourceType + ".png")));
			grid[i][j]->type = resourceType;
			grid[i][j]->key = key;
			grid[i][j]->SetTextFromKey(game->resourceFont);
			grid[i][j]->pointValue = pointValue;

			// Position of cell that contains resource (cell is bigger than resource)
			float cellWidth = (float)(viewportWidth) / (float)(gridWidth);
			float cellHeight = (float)(viewportHeight) / (float)(gridHeight);
			sf::Vector2f cellPosition(position.x + ((float)i * cellWidth), position.y + ((float)j * cellHeight));
			grid[i][j]->SetPosition(sf::Vector2f(cellPosition.x + (cellWidth / 2.0f) - (grid[i][j]->GetImage()->GetWidth() / 2.0f), cellPosition.y + (cellHeight / 2.0f) - (grid[i][j]->GetImage()->GetHeight() / 2.0f)));
			grid[i][j]->AlignText();
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
			game->window.Draw(grid[i][j]->displayText);
		}
	}
}