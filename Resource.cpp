#include "Resource.h"
#include "Game.h"

Resource::Resource()
{
}

void Resource::SetTextFromKey(sf::Font& font)
{
	std::string s;
	s += key;
	displayText.SetText(s);
	displayText.SetFont(font);
	displayText.SetSize(50);
}

void Resource::AlignText()
{
	displayText.SetPosition(GetPosition());
}
