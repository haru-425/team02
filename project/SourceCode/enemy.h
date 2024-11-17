#pragma once
#include "../GameLib/game_lib.h"
#include <vector>
//------< �萔 >----------------------------------------------------------------
#define ENEMY_TEX_W        (400.0f)   // �v���C���[�̉摜1�̕�
#define ENEMY_TEX_H        (400.0f)   // �v���C���[�̉摜1�̍���
#define ENEMY_PIVOT_X      (ENEMY_TEX_W/2)    // �v���C���[�̉������̒��S
#define ENEMY_PIVOT_Y      (ENEMY_TEX_H/2)   // �v���C���[�̏c�����̉��[

#define ENEMY_SPEED		(5)

#define ENEMY_CORE_TEX_W        (128.0f)   // �v���C���[�̉摜1�̕�
#define ENEMY_CORE_TEX_H        (128.0f)   // �v���C���[�̉摜1�̍���
#define ENEMY_CORE_PIVOT_X      (ENEMY_CORE_TEX_W/2)    // �v���C���[�̉������̒��S
#define ENEMY_CORE_PIVOT_Y      (ENEMY_CORE_TEX_H/2)   // �v���C���[�̏c�����̉��[
#define E_SCALE	(1.0f)
#define ENEMY_CD 1
//------< �\���� >---------------------------------------------------------------


//------< �ϐ� >----------------------------------------------------------------
extern enum class ENEMY_TYPE;

//------< �v���g�^�C�v�錾 >-----------------------------------------------------
void enemy_init();
void enemy_update();
void enemy_render();
void enemy_deinit();
void enemy_act();
void enemy_kill(float bomb_blast_range,VECTOR2 blast_posison);
