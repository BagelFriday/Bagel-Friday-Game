#include "Cannon.h"
#include "Game.h"

void Cannon::Initialize( Game *game )
{
	sprite.Initialize( game, "Art/turret.png");
	sprite.SetPosition( sf::Vector2f( game->screenWidth / 2.f, game->screenHeight - 50.f ) );
	sprite.SetRotation( 0.f );
	sprite.SetCenter( sf::Vector2f( sprite.GetRect().GetWidth() / 2.f, sprite.GetRect().GetHeight() / 2.f ) );
}

//float Dot( sf::Vector2f v1, sf::Vector2f v2 )
//{
//	float v1_length = sqrtf((v1.x * v1.x) + (v1.y * v1.y));
//	float v2_length = sqrtf((v2.x * v2.x) + (v2.y * v2.y));
//
//
//}

void Cannon::FireShot( sf::Vector2f hit_pos, Game *game )
{
	Entity shot;
	shot.Initialize( game, "Art/shot.png" );
	shot.ShotTarget = hit_pos;
	shot.SetPosition( sprite.GetPosition() );
	shot.Z_Pos = .01f;
	shot.Z_Velocity = 300.f;
	shot.Visible = true;
	shot.SetCenter( sf::Vector2f( shot.GetRect().GetWidth() / 2.f, shot.GetRect().GetHeight() / 2.f ) );
	Shots.push_back( shot );

	//Vector2f direction = hit_pos - sprite->GetPosition();
	//sprite->SetRotation()
}

void Cannon::UpdateShots( float deltaTime )
{
	std::deque<Entity>::iterator i = Shots.begin();
	for(; i != Shots.end(); ++i )
	{
		//i->Z_Pos = i->Z_Pos + i->Z_Velocity * deltaTime - 9.8 * (deltaTime * deltaTime);
		i->Z_Velocity += -200.f * deltaTime;
		i->Z_Pos += i->Z_Velocity * deltaTime;

		if( i->Z_Pos > 200.f )
		{
			i->SetPosition( i->ShotTarget );
			i->Visible = false;
		}
		else if( i->Z_Pos < 200.f )
		{
			i->Visible = true;
		}

		i->SetScale( sf::Vector2f( i->Z_Pos * .1f , i->Z_Pos * .1f ) );

		if( i->Z_Pos <= 0.f )
		{
			// TODO hurt player and destroy resource

			Shots.pop_front();
			i = Shots.begin();

			if(Shots.empty())
				break;
		}
	}
}
