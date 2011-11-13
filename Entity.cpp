#include "Entity.h"
#include "Game.h"
#include "ImagePool.h"
#include <sstream>

Entity::Entity()
:
myPoints(0)
{
	speed = sf::Vector2f( 2.0f, 2.0f );
}

void Entity::Initialize(Game *game, std::string filename)
{
	SetImage(*(game->imagePool.loadWithPool(filename)));
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
	return sf::Vector2f( (x + w) / 2.0f, (y + h) / 2.0f );
}