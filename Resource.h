#ifndef RESOURCE
#define RESOURCE

#include "Entity.h"
#include <SFML/Graphics.hpp>

enum ResourceType
{
	RESOURCE_MEAT,
	RESOURCE_WOOD,
	RESOURCE_STEEL,
	RESOURCE_GOLD,
	RESOURCE_SILICON,
	RESOURCE_LOVE,

	RESOURCE_COUNT
};

class Resource: public Entity
{
private:
public:

	ResourceType type;

	char key;

	int pointValue;

	// Font used for all resources
	sf::Font font;

	sf::String displayText;

	Resource();

	Resource(std::string _type, std::string key, float _probability);

	void SetTextFromKey(sf::Font& font);

	void AlignText();

};

#endif // RESOURCE