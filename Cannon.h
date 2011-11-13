#ifndef CANNON_H
#define CANNON_H

#include <deque>
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Game;

class Cannon
{
public:
	std::deque<Entity> Shots;
	Entity sprite;

	sf::SoundBuffer cannonShot;
	sf::SoundBuffer explosion;

	std::deque<sf::Sound> cannonShots;
	std::deque<sf::Sound> explosions;

	Cannon(){};

	void Initialize( Game *game );
	void FireShot( sf::Vector2f hit_pos, Game *game );
	void UpdateShots( float deltaTime );
};

#endif