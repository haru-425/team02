#include "bomb.h"

Bomb bomb;
extern PLAYER player;
POINT screenPoint;
extern float force;
extern float angle;
float flepX = 0.0f;
float flepY = 0.0f;
std::vector<Bomb_range> range_Box;
float blast_max_range = 0;

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

void bomb_throw(float muster_up, int bomb_up)
{
	bomb.start_bomb_position = player.position;

	VECTOR2 Point = cursor_position();
	bomb.bomb_angle = tracking(Point, player.position);

	blast_max_range = BOMB_BLAST_MAX_INIT_RANGE + (muster_up * 5) + (float)(bomb_up * 10);
	//bomb.bomb_speed = 50.0f;

	bomb.bomb_state++;


}

void bomb_expansion()
{
	flepX = player.position.x - bomb.bomb_position.x;
	flepY = player.position.y - bomb.bomb_position.y;

	if (blast_max_range - sqrtf(flepX * flepX + flepY * flepY) > 0)
	{
		player.player_time = 0;
		player.strat_position = player.position;
		force = (blast_max_range - sqrtf(flepX * flepX + flepY * flepY)) * BOMB_BLAST_STRANGE;
		angle = -tracking(player.position, bomb.bomb_position);
	}

	range_Box.push_back(bomb.bomb_position);
	bomb_deinit();
}

void bomb_update()
{

	debug::setString("bomb_blast_max_range:%f", blast_max_range);
	debug::setString("bomb_state:%d", bomb.bomb_state);
	/*for (auto& renge : range_Box)
	{
		renge.bomb_blast_max_range = bomb_blast_max_range;
	}*/
	switch (bomb.bomb_state)
	{
	case 1:
		bomb.bom_time = 0.0f;
		bomb.bomb_state++;

	case 2:

		bomb.bom_time += 0.1f;
		bomb.bomb_position = bomb.start_bomb_position + LaunchCalculatePosition(-bomb.bomb_angle, bomb.bomb_speed, bomb.bom_time);

		bomb.bomb_position = edge_reflecting(bomb.bomb_position);

		if (bomb.bomb_position.y >= SCREEN_H)
		{
			bomb_deinit();
		}
	default:
		for (auto& renge : range_Box)
		{
			renge.bomb_range_expansion();
		}
		auto it = std::remove_if(range_Box.begin(), range_Box.end(),
			[](const Bomb_range& renge) { return renge.bomb_blast_range >= renge.bomb_blast_max_range; });
		range_Box.erase(it, range_Box.end());
		player_movement(angle, force + BOMB_ADJUSTMENT);
		return;

		break;
	}

}

void bomb_render()
{

	for (auto& range : range_Box) {
		primitive::circle(range.judg_position.x, range.judg_position.y, range.bomb_blast_max_range, range.bomb_blast_range / range.bomb_blast_max_range, range.bomb_blast_range / range.bomb_blast_max_range, 0, 1, 1, 1, 0.2f);
	}



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

Bomb_range::Bomb_range(VECTOR2 position) :judg_position(position)
{
	bomb_blast_range = 0;
	this->bomb_blast_max_range = blast_max_range;
	player_launch = false;
}

Bomb_range::~Bomb_range()
{
}

void Bomb_range::bomb_range_expansion()
{
	bomb_blast_range += BOMB_BLAST_R_INC;
	/*if (sqrtf(flepX * flepX + flepY * flepY) - bomb_blast_range <= 0 && player_launch == false)
	{
		player.player_time = 0;
		player.strat_position = player.position;
		force = (BOMB_BLAST_MAX_RANGE - sqrtf(flepX * flepX + flepY * flepY)) * BOMB_BLAST_STRANGE;
		angle = tracking(player.position, bomb.start_bomb_position);
		player_launch = true;
	}
	if (bomb_blast_range >= BOMB_BLAST_MAX_RANGE)
	{
		player_launch = false;
	}*/
	enemy_kill(bomb_blast_range, judg_position);

}
