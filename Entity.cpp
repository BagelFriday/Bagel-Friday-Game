#include "Entity.h"
#include "Game.h"
#include "ImagePool.h"
#include <sstream>

Entity::Entity()
:
myPoints(0),
timeOfSpawn(0),
transparency(255)
{
	speed = sf::Vector2f( 2.0f, 2.0f );
}

void Entity::Initialize(Game *game, std::string filename)
{
	timeOfSpawn = game->gameTime.GetElapsedTime();

	SetImage(*(game->imagePool.loadWithPool(filename)));
}

void Entity::StartFadeIn()
{
	transparency = 0;
	SetColor(sf::Color(255, 255, 255, transparency));
}

void Entity::UpdateFade(Game *game)
{
	static float timeToFade = 4.0f;
	float timeSpentFading = (game->gameTime.GetElapsedTime() - timeOfSpawn) / timeToFade;

	transparency = 255 * timeSpentFading;

	if (transparency < 0)
	{
		transparency = 0;
	}
	else if (transparency > 255)
	{
		transparency = 255;
	}

	SetColor(sf::Color(255, 255, 255, transparency));
}

void Entity::Update(Game *game, float deltaTime)
{
}

sf::Rect<float> Entity::GetRect()
{
	float x, y, w, h;
	x = GetPosition().x;
	y = GetPosition().y;
	w = GetSubRect().GetWidth() * GetScale().x;
	h = GetSubRect().GetHeight() * GetScale().y;
	return sf::Rect<float>(x, y, x + w, y + h);
}

sf::Vector2f Entity::GetCenter()
{
	float x, y, w, h;
	x = GetPosition().x;
	y = GetPosition().y;
	w = GetSubRect().GetWidth() * GetScale().x;
	h = GetSubRect().GetHeight() * GetScale().y;
	return sf::Vector2f( x + (w / 2.0f), y + (h / 2.0f) );
}