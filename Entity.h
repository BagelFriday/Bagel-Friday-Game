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

	float Z_Velocity;
	float Z_Pos;
	sf::Vector2f ShotTarget;
	bool Visible;

	sf::String pointDisplay;

	Entity();

	virtual void Initialize(Game *game, std::string filename);

	virtual void Update(Game *game, float deltaTime);

	sf::Rect<float> GetRect();
};

#endif // ENTITY