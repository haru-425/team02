#include "bomb.h"
#include "player.h"
#include "system.h"

#include "common.h"

Bomb bomb;
extern PLAYER player;
POINT screenPoint;
extern float force;
extern float angle;
float flepX = 0.0f;
float flepY = 0.0f;
void bomb_init()
{
	bomb.bomb_state = 0;
	bomb.start_bomb_position = player.position;
	bomb.bomb_position.x = -200;
	bomb.bomb_position.y = -200;
	bomb.bomb_speed = 50.0f;
	bomb.bomb_angle = 0.0f;
	bomb.bom_time = 0;
	bomb.bomb_blast = 0.0f;
}

void bomb_deinit()
{
	bomb.bomb_state = 0;
	bomb.bomb_position.x = -100;
	bomb.bomb_position.y = -100;
	bomb.bomb_speed = 50.0f;
	bomb.bomb_angle = 0.0f;
	bomb.bom_time = 0;
}

void bomb_throw()
{

	bomb.start_bomb_position = player.position;



	VECTOR2 Point = cursor_position();
	bomb.bomb_angle = tracking(Point, player.position);


	//bomb.bomb_speed = 50.0f;

	bomb.bomb_state++;
}

void bomb_update()
{

	debug::setString("bomb.start_bomb_position.x:%f", bomb.start_bomb_position.x);
	switch (bomb.bomb_state)
	{
	case 3:
		flepX = player.position.x - bomb.bomb_position.x;
		flepY = player.position.y - bomb.bomb_position.y;
		if (BOMB_BLAST_RANGE - sqrtf(flepX * flepX + flepY * flepY) > 0)
		{
			player.player_time = 0;
			player.strat_position = player.position;
			force = (BOMB_BLAST_RANGE - sqrtf(flepX * flepX + flepY * flepY)) * BOMB_BLAST_STRANGE;
			angle = -tracking(player.position, bomb.bomb_position);
		}

		bomb_deinit();
		break;

	case 1:
		bomb.bom_time = 0.0f;
		bomb.bomb_state++;

	case 2:

		bomb.bom_time += 0.1f;
		bomb.bomb_position = bomb.start_bomb_position + LaunchCalculatePosition(-bomb.bomb_angle, bomb.bomb_speed, bomb.bom_time);

		if (bomb.bomb_position.y >= SCREEN_H)
		{
			bomb_deinit();
		}
	default:

		player_movement(angle, force);
		return;

		break;
	}

}

void bomb_render()
{
	primitive::circle(bomb.bomb_position.x, bomb.bomb_position.y, BOMB_BLAST_RANGE, 1, 1, 0, 0.0f, 0.2f, 0.4f, 0.2f);
	primitive::circle(bomb.bomb_position.x, bomb.bomb_position.y, 10, 1, 1);

	for (int i = 0; i < 120; i++)
	{
		primitive::circle(edge_reflecting(
			player.position + LaunchCalculatePosition(
				-tracking(
					cursor_position(
					), player.position
				), bomb.bomb_speed, i * 0.5f
			)
		).x,
			edge_reflecting(player.position + LaunchCalculatePosition(-tracking(cursor_position(), player.position), bomb.bomb_speed, i * 0.5f)).y,
			3,
			1, 1,
			0,
			1, 1, 1, 0.5f);
	}






	debug::setString("%f", bomb.bomb_position.x);
}
