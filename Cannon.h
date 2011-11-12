#ifndef CANNON_H
#define CANNON_H

#include <vector>
#include "Entity.h"
#include <SFML/Graphics.hpp>

class Cannon
{
	float rotation;
	std::vector<Entity> Shots;
	Entity* sprite;
};

#endif