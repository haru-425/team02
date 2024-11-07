#pragma once
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

//------< �\���� >---------------------------------------------------------------


//------< �ϐ� >----------------------------------------------------------------

//------< �v���g�^�C�v�錾 >-----------------------------------------------------
void player_init();
void player_update();
void player_render();
void player_deinit();
void player_act();