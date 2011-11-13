#ifndef CANNON_H
#define CANNON_H

#include <deque>
#include "Entity.h"
#include <SFML/Graphics.hpp>

class Game;

class Cannon
{
public:
	std::deque<Entity> Shots;
	Entity sprite;

	Cannon(){};

	void Initialize( Game *game );
	void FireShot( sf::Vector2i hit_pos, Game *game );
	void UpdateShots( float deltaTime, Game* game );
};

#endif