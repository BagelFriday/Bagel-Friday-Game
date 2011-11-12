#include "Resource.h"
#include "Game.h"

Resource::Resource() : isAlive(true)
{
}

Resource::Resource(std::string _type, std::string _key, float _probability) : isAlive(true)
{
	type = _type;
	probability = _probability;
}

void Resource::SetTextFromKey(sf::Font& font)
{
	displayText.SetText(Game::KeyToString(key));
	displayText.SetFont(font);
	displayText.SetSize(50);
}

void Resource::AlignText()
{
	displayText.SetPosition(GetPosition());
}

void Resource::Die()
{
	const sf::Color transparent(255, 255, 255, 0);
	isAlive = false;
	SetColor(transparent);
	displayText.SetColor(transparent);
}