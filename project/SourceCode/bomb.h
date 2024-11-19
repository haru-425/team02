#pragma once // ��d�C���N���[�h��h�����߂̃f�B���N�e�B�u
#define BOMB_H

#include "../GameLib/game_lib.h"
#include <vector>
#include <algorithm>
#include <DirectXMath.h>

using namespace DirectX;

#define BOMB_BLAST_STRANGE 0.28f
#define BOMB_BLAST_MAX_RANGE 180.0f
#define BOMB_BLAST_R_INC 10.0f
#define BOMB_ADJUSTMENT 9.0f

void bomb_init();			// ���e�̏�����
void bomb_deinit();			// ���e�̃��Z�b�g
void bomb_throw();			// �v���C���[�����e�𓊂���
void bomb_update();			// ���e�̏�ԁi�^�C�}�[�Ȃǁj���X�V
void bomb_render();			// ���e�Ɣ����͈͂̕`�揈��

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
	void bomb_range_expansion();
};

extern std::vector<Bomb_range> range_Box;
