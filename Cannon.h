#ifndef CANNON_H
#define CANNON_H

#include <list>
#include "Entity.h"
#include <SFML/Graphics.hpp>

class Game;

class Cannon
{
public:
	std::list<Entity> Shots;
	Entity sprite;

	Cannon(){};

	void Initialize( Game *game );
	void FireShot( sf::Vector2f hit_pos, Game *game );
	void UpdateShots( float deltaTime );
};

#endif