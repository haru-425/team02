#pragma once // ��d�C���N���[�h��h�����߂̃f�B���N�e�B�u
#ifndef BOMB_H 
#define BOMB_H

#include "../GameLib/game_lib.h"
#include <DirectXMath.h>
using namespace DirectX;

void bomb_init();			// ���e�̏�����
void bomb_deinit();			// ���e�̃��Z�b�g
void bomb_throw();			// �v���C���[�����e�𓊂���
void bomb_update();			// ���e�̏�ԁi�^�C�}�[�Ȃǁj���X�V
void bomb_explosion();		// ���e�̔�������
void bomb_render();			// ���e�Ɣ����͈͂̕`�揈��

class Bomb
{
public:
	int bomb_state;
	int bom_time;
	VECTOR2 bomb_position;
	VECTOR2 start_bomb_position;
	float bomb_speed;
	float bomb_angle;
};

#endif // BOMB_H