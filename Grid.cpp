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
	strcpy_s(meatChars, "1234567890");
	strcpy_s(woodChars, "QWERTYUIOP");
	strcpy_s(steelChars, "ASDFGHJKL");
	strcpy_s(goldChars, "ZXCVBNM");
	strcpy_s(siliconChars, "_");
	strcpy_s(heartChars, "1234567890QWERTYUIOPASDFGHJKLZXCVBNM");

	meatCharsIt = 0;
	woodCharsIt = 0;
	steelCharsIt = 0;
	goldCharsIt = 0;
	siliconCharsIt = 0;
	heartCharsIt = 0;
	
	meatCharsActive = 0;
	woodCharsActive = 0;
	steelCharsActive = 0;
	goldCharsActive = 0;
	siliconCharsActive = 0;
	heartCharsActive = 0;

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
	for (int i = 0; i < MAX_GRID_HEIGHT; i++)
	{
		for (int j = 0; j < MAX_GRID_WIDTH; j++)
		{
			if(resourceCellArray[i][j] )
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
			if( !resourceCellArray[i][j] )
			{
				if( randomResourcePosition == 0 )
				{
					resourceCellArray[i][j] = new Resource();

					std::string resourceType;
					int pointValue;

					// Key from random resource
					char key = '~';
					while(key == '~')
					{
						// Random resource
						switch(randomResourceKind)
						{
						case RESOURCE_MEAT:
							if( meatCharsActive < NUM_MEAT_VALUES )
							{
								key = meatChars[meatCharsIt];
								meatCharsIt = (meatCharsIt+1)%NUM_MEAT_VALUES;
								meatCharsActive++;
								pointValue = 1;
								resourceType = "meat";
								break;
							}				
						case RESOURCE_WOOD:
							if( woodCharsActive < NUM_WOOD_VALUES )
							{
								key = woodChars[woodCharsIt];
								woodCharsIt = (woodCharsIt+1)%NUM_WOOD_VALUES;
								woodCharsActive++;
								pointValue = 2;
								resourceType = "wood";
								break;
							}	
						case RESOURCE_STEEL:
							if( steelCharsActive < NUM_STEEL_VALUES )
							{
								key = steelChars[steelCharsIt];
								steelCharsIt = (steelCharsIt+1)%NUM_STEEL_VALUES;
								steelCharsActive++;
								pointValue = 3;
								resourceType = "steel";
								break;
							}
						case RESOURCE_GOLD:
							if( goldCharsActive < NUM_GOLD_VALUES )
							{
								key = goldChars[goldCharsIt];
								goldCharsIt = (goldCharsIt+1)%NUM_GOLD_VALUES;
								goldCharsActive++;
								pointValue = 4;
								resourceType = "gold";
								break;
							}
						case RESOURCE_SILICON:
							if( siliconCharsActive < NUM_SILICON_VALUES )
							{
								key = siliconChars[siliconCharsIt];
								siliconCharsIt = (siliconCharsIt+1)%NUM_SILICON_VALUES;
								siliconCharsActive++;
								pointValue = 7;
								resourceType = "silicon";
								break;
							}
						case RESOURCE_LOVE:
							int randomResourceCharType = sf::Randomizer::Random(0, 2);
							pointValue = 5;
							resourceType = "love";
							switch( randomResourceCharType )
							{
							case 0:
								if( meatCharsActive < NUM_MEAT_VALUES )
								{
									key = meatChars[meatCharsIt];
									meatCharsIt = (meatCharsIt+1)%NUM_MEAT_VALUES;
									meatCharsActive++;
									break;
								}
							case 1:
								if( woodCharsActive < NUM_WOOD_VALUES - 1 )
								{
									key = woodChars[woodCharsIt];
									woodCharsIt = (woodCharsIt+1)%NUM_WOOD_VALUES;
									woodCharsActive++;
									break;
								}
							case 2:
								if( goldCharsActive < NUM_GOLD_VALUES - 1 )
								{
									key = goldChars[goldCharsIt];
									goldCharsIt = (goldCharsIt+1)%NUM_GOLD_VALUES;
									goldCharsActive++;
									break;
								}
							default:
								randomResourceKind = 0;
							}

						}
					}

					resourceCellArray[i][j]->key = key;
					keyMap[static_cast<sf::Key::Code>(key)] = sf::Vector2i(i, j);
					
					resourceCellArray[i][j]->SetImage(*(game->imagePool.loadWithPool("Art/" + resourceType + ".png")));
					resourceCellArray[i][j]->type = resourceType;
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

void Grid::RemoveResource(int row, int col)
{
	delete resourceCellArray[row][col];
	numActiveResources--;
}

void Grid::Display(Game *game)
{
	for (int i = 0; i < MAX_GRID_HEIGHT; i++)
	{
		for (int j = 0; j < MAX_GRID_WIDTH; j++)
		{
			if( resourceCellArray[i][j] )
			{
				game->window.Draw(*resourceCellArray[i][j]);
				game->window.Draw(resourceCellArray[i][j]->displayText);
			}
		}
	}
}