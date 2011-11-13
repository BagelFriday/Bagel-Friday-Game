#include <sstream>
#include "Player.h"
#include "Game.h"
#include "ImagePool.h"

Player::Player()
: Entity()
{
}

void Player::Initialize(Game *game, std::string filename, sf::Font& font, float fontSize)
{
	Entity::Initialize(game, filename);

	pointDisplay.SetFont(font);
	pointDisplay.SetText("0");
	pointDisplay.SetSize(fontSize);
}

void Player::Update(Game *game, float deltaTime)
{
	Entity::Update(game, deltaTime);
}

bool Player::IsColliding( sf::Rect<float>& rect )
{
	sf::Vector2f point = GetCenter();
	return (	point.x < rect.Right && point.x > rect.Left &&
				point.y < rect.Bottom && point.y > rect.Top );
}

void Player::UpdatePointDisplay()
{
	std::stringstream ss;
	ss << myPoints;
	pointDisplay.SetText(ss.str());
}