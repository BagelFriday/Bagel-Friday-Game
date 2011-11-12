#ifndef PLAYER
#define PLAYER

#include "Entity.h"

class Game;

class Player : public Entity
{
private:
public:
	Player();

	void Initialize(Game *game, std::string filename, sf::Font& font, float fontSize);

	void Update(Game *game, float deltaTime);

	void UpdatePointDisplay();
};

#endif // PLAYER