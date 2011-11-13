#include <cassert>
#include "Grid.h"
#include "Entity.h"
#include "ImagePool.h"
#include "Game.h"

Grid::Grid()
:
viewportWidth(1024),
viewportHeight(660)
{
	// Set all NULL
	for (int i = 0; i < MAX_GRID_HEIGHT; i++)
	{
		for (int j = 0; j < MAX_GRID_WIDTH; j++)
		{
			resourceCellArray[i][j] = NULL;
		}
	}
	numActiveResources = 0;
}

Grid::~Grid()
{
	// Set all NULL
	for (int i = 0; i < MAX_GRID_HEIGHT; i++)
	{
		for (int j = 0; j < MAX_GRID_WIDTH; j++)
		{
			if(resourceCellArray[i][j] != NULL )
			{
				delete resourceCellArray[i][j];
			}
		}
	}
}

void Grid::SpawnResource(Game *game)
{
	int randomResourcePosition = 0;
	if( (MAX_GRID_WIDTH * MAX_GRID_HEIGHT ) > numActiveResources )
	{
		randomResourcePosition= sf::Randomizer::Random(0, (MAX_GRID_WIDTH * MAX_GRID_HEIGHT ) - numActiveResources - 1);
	}
	else if( (MAX_GRID_WIDTH * MAX_GRID_HEIGHT ) != numActiveResources )
	{
		assert(true); // Should not call this function if no slots are available
	}
	int randomResourceKind = sf::Randomizer::Random(0, NUM_RESOURCE_KINDS - 1 );

	for (int i = 0; i < MAX_GRID_HEIGHT; i++)
	{
		for (int j = 0; j < MAX_GRID_WIDTH; j++)
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
					case 3:
						resourceType = "silicon";
						pointValue = 4;
						break;
					case 4:
						resourceType = "love";
						pointValue = 5;
						break;
					}

					// Key from random resource
					int key;
					if		(resourceType == "meat")		key = sf::Key::M;
					else if (resourceType == "gold")		key = sf::Key::G;
					else if (resourceType == "sticks")		key = sf::Key::S;
					else if (resourceType == "silicon")		key = sf::Key::H;
					else if (resourceType == "love")		key = sf::Key::L;
					else									key = sf::Key::Z;

					resourceCellArray[i][j]->SetImage(*(game->imagePool.loadWithPool("Art/" + resourceType + ".png")));
					resourceCellArray[i][j]->type = resourceType;
					resourceCellArray[i][j]->key = key;
					resourceCellArray[i][j]->SetTextFromKey(game->resourceFont);
					resourceCellArray[i][j]->pointValue = pointValue;

					// Position of cell that contains resource (cell is bigger than resource)
					float cellWidth = (float)(viewportWidth) / (float)(MAX_GRID_WIDTH);
					float cellHeight = (float)(viewportHeight) / (float)(MAX_GRID_HEIGHT);
					sf::Vector2f cellPosition(position.x + ((float)j * cellWidth), position.y + ((float)i * cellHeight));
					resourceCellArray[i][j]->SetPosition(sf::Vector2f(cellPosition.x + (cellWidth / 2.0f) - (resourceCellArray[i][j]->GetImage()->GetWidth() / 2.0f), cellPosition.y + (cellHeight / 2.0f) - (resourceCellArray[i][j]->GetImage()->GetHeight() / 2.0f)));
					resourceCellArray[i][j]->SetPosition(cellPosition);
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
	for (int i = 0; i < MAX_GRID_HEIGHT; i++)
	{
		for (int j = 0; j < MAX_GRID_WIDTH; j++)
		{
			if( game->grid.resourceCellArray[i][j] != NULL )
			{
				game->window.Draw(*resourceCellArray[i][j]);
				game->window.Draw(resourceCellArray[i][j]->displayText);
			}
		}
	}
}