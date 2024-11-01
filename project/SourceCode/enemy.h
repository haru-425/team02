#pragma once
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

//------< �\���� >---------------------------------------------------------------
class ENEMY {
public:
	float angle;
	float speed;
	VECTOR2 position;
	VECTOR2 scale;
	VECTOR2 texPos;
	VECTOR2 texSize;
	VECTOR2 pivot;
	VECTOR4 color;



};

//------< �ϐ� >----------------------------------------------------------------

//------< �v���g�^�C�v�錾 >-----------------------------------------------------
void enemy_init();
void enemy_update();
void enemy_render();
void enemy_deinit();
void enemy_act();
