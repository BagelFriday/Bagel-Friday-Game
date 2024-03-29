#ifndef ENTITY
#define ENTITY

#include <SFML/Graphics.hpp>

class Game;

class Entity : public sf::Sprite
{
private:
public:
	float timeOfSpawn;

	int transparency;

	sf::Vector2f speed;

	int myPoints;

	float Z_Velocity;
	float Z_Pos;
	sf::Vector2f ShotTarget;
	sf::Vector2i ShotTargetCell;
	bool Visible;

	sf::String pointDisplay;

	Entity();

	void UpdateFade(Game *game);

	void StartFadeIn();

	virtual void Initialize(Game *game, std::string filename);

	virtual void Update(Game *game, float deltaTime);

	sf::Rect<float> GetRect();
	sf::Vector2f GetCenter();
};

#endif // ENTITY