#ifndef PLAYER
#define PLAYER

#include "Entity.h"
#include "Grid.h"
#include "Resource.h"

class Game;

class Player : public Entity
{
private:
public:
	Player();

	void Initialize(Game *game, std::string filename, sf::Font& font, float fontSize);

	void Update(Game *game, float deltaTime);
	void UpdatePointDisplay();
	bool IsColliding(sf::Rect<float>& rect);
	sf::Vector2i getCellLocation(Grid& grid);
};

#endif // PLAYER