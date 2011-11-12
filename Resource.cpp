#include "Resource.h"

Resource::Resource()
{
}

Resource::Resource(std::string _type, std::string _key, float _probability)
{
	type = _type;
	probability = _probability;
}

void Resource::SetTextFromKey(sf::Font& font)
{
	displayText.SetText(key);
	displayText.SetFont(font);
	displayText.SetSize(50);
}

void Resource::AlignText()
{
	displayText.SetPosition(GetPosition());
}