#include "Cannon.h"

Cannon::Cannon( Game *game )
{
	sprite.Initialize( game, "Art/turret.png");
	sprite.SetCenter( sf::Vector2f( sprite->GetRect().Right / 2.f, sprite->GetRect().Bottom / 2.f ) );
	rotation = 0.f;
}

void Cannon::FireShot( sf::Vector2f hit_pos )
{
}
