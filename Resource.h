#ifndef RESOURCE
#define RESOURCE

#include "Entity.h"

class Resource: public Entity
{
private:
public:
	bool isAlive;

	std::string type;

	std::string key;

	float probability;

	// Font used for all resources
	sf::Font font;

	sf::String displayText;

	Resource();

	Resource(std::string _type, std::string key, float _probability);

	void SetTextFromKey(sf::Font& font);

	void AlignText();

	void Die();
};

#endif // RESOURCE