#ifndef CANNON_H
#define CANNON_H

#include <vector>
#include "Entity.h"
#include <SFML/Graphics.hpp>

class Cannon
{
	float rotation;
	std::vector<Entity> Shots;
	Entity sprite;

	Cannon();
	void update_shots();

	void FireShot( sf::Vector2f hit_pos );
};

#endif