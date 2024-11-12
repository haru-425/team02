#pragma once
#include "../GameLib/game_lib.h"

//------< �萔 >----------------------------------------------------------------
#define PLAYER_TEX_W        (400.0f)   // �v���C���[�̉摜1�̕�
#define PLAYER_TEX_H        (400.0f)   // �v���C���[�̉摜1�̍���
#define PLAYER_PIVOT_X      (PLAYER_TEX_W/2)    // �v���C���[�̉������̒��S
#define PLAYER_PIVOT_Y      (PLAYER_TEX_H/2)   // �v���C���[�̏c�����̉��[

#define PLAYER_SPEED		(5)

#define PLAYER_CORE_TEX_W        (128.0f)   // �v���C���[�̉摜1�̕�
#define PLAYER_CORE_TEX_H        (128.0f)   // �v���C���[�̉摜1�̍���
#define PLAYER_CORE_PIVOT_X      (PLAYER_CORE_TEX_W/2)    // �v���C���[�̉������̒��S
#define PLAYER_CORE_PIVOT_Y      (PLAYER_CORE_TEX_H/2)   // �v���C���[�̏c�����̉��[
#define PLAYER_GRAVITY 2.45f

//------< �\���� >---------------------------------------------------------------


//------< �ϐ� >----------------------------------------------------------------

//------< �v���g�^�C�v�錾 >-----------------------------------------------------
void player_init();
void player_update();
void player_render();
void player_deinit();
void player_act();
void player_movement(float angle,float force);

class PLAYER {
public:
	float angle;
	float speed;
	VECTOR2 position;
	VECTOR2 strat_position;
	VECTOR2 scale;
	VECTOR2 texPos;
	VECTOR2 texSize;
	VECTOR2 pivot;
	VECTOR4 color;



};