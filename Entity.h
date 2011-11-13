#ifndef ENTITY
#define ENTITY

#include <SFML/Graphics.hpp>

class Game;

class Entity : public sf::Sprite
{
private:
public:
	sf::Vector2f speed;

	int myPoints;

	sf::String pointDisplay;

	Entity();

	virtual void Initialize(Game *game, std::string filename);

	virtual void Update(Game *game, float deltaTime);

	sf::Rect<float> GetRect();
	sf::Vector2f GetCenter();
};

#endif // ENTITY