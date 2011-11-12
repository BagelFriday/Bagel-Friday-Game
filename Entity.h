#ifndef ENTITY
#define ENTITY

#include <SFML/Graphics.hpp>

class Game;

class Entity : public sf::Sprite
{
private:
public:
	sf::Vector2f speed;
	sf::Vector2f direction;

	int myPoints;

	sf::String pointDisplay;

	Entity();

	void Initialize(Game *game, std::string filename, sf::Font& font, float fontSize, sf::Vector2f pointPos);

	void Update(Game *game, float deltaTime);

	sf::Rect<float> GetRect();

	void UpdatePointDisplay();
};

#endif // ENTITY