#ifndef ENTITY
#define ENTITY

#include <SFML/Graphics.hpp>

class Entity : public sf::Sprite
{
private:
public:
	sf::Vector3f velocity;
	sf::Vector3f position;

	Entity();
};

#endif // ENTITY