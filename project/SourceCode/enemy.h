#pragma once
//------< 定数 >----------------------------------------------------------------
#define ENEMY_TEX_W        (400.0f)   // プレイヤーの画像1つの幅
#define ENEMY_TEX_H        (400.0f)   // プレイヤーの画像1つの高さ
#define ENEMY_PIVOT_X      (ENEMY_TEX_W/2)    // プレイヤーの横方向の中心
#define ENEMY_PIVOT_Y      (ENEMY_TEX_H/2)   // プレイヤーの縦方向の下端

#define ENEMY_SPEED		(5)

#define ENEMY_CORE_TEX_W        (128.0f)   // プレイヤーの画像1つの幅
#define ENEMY_CORE_TEX_H        (128.0f)   // プレイヤーの画像1つの高さ
#define ENEMY_CORE_PIVOT_X      (ENEMY_CORE_TEX_W/2)    // プレイヤーの横方向の中心
#define ENEMY_CORE_PIVOT_Y      (ENEMY_CORE_TEX_H/2)   // プレイヤーの縦方向の下端

//------< 構造体 >---------------------------------------------------------------
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

//------< 変数 >----------------------------------------------------------------

//------< プロトタイプ宣言 >-----------------------------------------------------
void enemy_init();
void enemy_update();
void enemy_render();
void enemy_deinit();
void enemy_act();
