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

	// Just load img
	void Initialize(Game *game, std::string filename);

	// For players
	void PlayerInitialize(Game *game, std::string filename, sf::Font& font, float fontSize);

	void Update(Game *game, float deltaTime);

	sf::Rect<float> GetRect();

	void UpdatePointDisplay();
};

#endif // ENTITY