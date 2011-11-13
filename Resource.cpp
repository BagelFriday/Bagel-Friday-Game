#include "Resource.h"
#include "Game.h"

Resource::Resource()
{
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
