#include <cassert>
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
	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			resourceCellArray[i][j] = NULL;
		}
	}
	numActiveResources = 0;
}

Grid::~Grid()
{
	// Set all NULL
	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			if(resourceCellArray[i][j] != NULL )
			{
				delete resourceCellArray[i][j];
			}
		}
	}
}

void Grid::SetSize(int rows, int columns)
{
	if (rows <= GRID_SIZE)
	{
		gridHeight = rows;
	}
	if (columns <= GRID_SIZE)
	{
		gridWidth = columns;
	}
}

void Grid::SpawnResource(Game *game)
{
	int randomResourcePosition = 0;
	if( (gridWidth * gridHeight ) > numActiveResources )
	{
		randomResourcePosition= sf::Randomizer::Random(0, (gridWidth * gridHeight ) - numActiveResources - 1);
	}
	else if( (gridWidth * gridHeight ) != numActiveResources )
	{
		assert(true); // Should not call this function if no slots are available
	}
	int randomResourceKind = sf::Randomizer::Random(0, NUM_RESOURCE_KINDS - 1 );

	for (int i = 0; i < gridWidth; i++)
	{
		for (int j = 0; j < gridHeight; j++)
		{
			if( resourceCellArray[i][j] == NULL)
			{
				if( randomResourcePosition == 0 )
				{
					resourceCellArray[i][j] = new Resource();

					std::string resourceType;
					int pointValue;

					// Random resource
					switch(randomResourceKind)
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

					resourceCellArray[i][j]->SetImage(*(game->imagePool.loadWithPool("Art/" + resourceType + ".png")));
					resourceCellArray[i][j]->type = resourceType;
					resourceCellArray[i][j]->key = key;
					resourceCellArray[i][j]->SetTextFromKey(game->resourceFont);
					resourceCellArray[i][j]->pointValue = pointValue;

			// Position of cell that contains resource (cell is bigger than resource)
					float cellWidth = (float)(viewportWidth) / (float)(gridWidth);
					float cellHeight = (float)(viewportHeight) / (float)(gridHeight);
					sf::Vector2f cellPosition(position.x + ((float)i * cellWidth), position.y + ((float)j * cellHeight));
					resourceCellArray[i][j]->SetPosition(sf::Vector2f(cellPosition.x + (cellWidth / 2.0f) - (resourceCellArray[i][j]->GetImage()->GetWidth() / 2.0f), cellPosition.y + (cellHeight / 2.0f) - (resourceCellArray[i][j]->GetImage()->GetHeight() / 2.0f)));
					resourceCellArray[i][j]->AlignText();
					numActiveResources++;
					return;
				}
				else
				{
					randomResourcePosition--;
				}
			}
		}
	}
}

void Grid::RemoveResource(Resource* resourceCell)
{
	delete resourceCell;
	numActiveResources--;

}

void Grid::Display(Game *game)
{
	for (int i = 0; i < gridWidth; i++)
	{
		for (int j = 0; j < gridHeight; j++)
		{
			if( game->grid.resourceCellArray[i][j] != NULL )
			{
				game->window.Draw(*resourceCellArray[i][j]);
				game->window.Draw(resourceCellArray[i][j]->displayText);
			}
		}
	}
}