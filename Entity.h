#ifndef ENTITY
#define ENTITY

#include <SFML/Graphics.hpp>

class Game;

class Entity : public sf::Sprite
{
private:
public:
	sf::Vector3f velocity;
	sf::Vector3f position;

	sf::Vector2f speed;
	sf::Vector2f direction;

	Entity();

	void Update(Game *game, float deltaTime);

	sf::Rect<float> GetRect();
};

#endif // ENTITY