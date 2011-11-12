#ifndef ENTITY
#define ENTITY

#include <SFML/Graphics.hpp>

class Entity : public sf::Sprite
{
private:
public:
	sf::Vector2f velocity;

	Entity();
};

#endif // ENTITY