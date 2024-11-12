#pragma once // ��d�C���N���[�h��h�����߂̃f�B���N�e�B�u
#ifndef BOMB_H 
#define BOMB_H

#include "../GameLib/game_lib.h"
#include <DirectXMath.h>

using namespace DirectX;

#define BOMB_BLAST_STRANGE 5.0f

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

#endif // BOMB_H