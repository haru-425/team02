#pragma once
#define BOMB_H

#include "../GameLib/game_lib.h"
#include "system.h"
#include "common.h"

void tutorial_init();
void tutorial_deinit();
void tutorial_update();
void tutorial_render();

class Bomb
{
public:
	int bomb_state;
	VECTOR2 bomb_position;
	VECTOR2 start_bomb_position;
	float bom_time;
	float bomb_speed;
	float bomb_angle;
	float bomb_blast;
};

class Bomb_range
{
public:
	Bomb_range(VECTOR2 position);
	~Bomb_range();
	bool player_launch;
	VECTOR2 judg_position;
	float bomb_blast_range;
	float bomb_blast_max_range;
	void bomb_range_expansion();
};

extern std::vector<Bomb_range> range_Box;
