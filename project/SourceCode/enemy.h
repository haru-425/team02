#pragma once
#include "../GameLib/game_lib.h"
#include <vector>
#include"system.h"
//------< 定数 >----------------------------------------------------------------
#define ENEMY_TEX_W        (128.0f)   // プレイヤーの画像1つの幅
#define ENEMY_TEX_H        (128.0f)   // プレイヤーの画像1つの高さ
#define ENEMY_PIVOT_X      (ENEMY_TEX_W/2)    // プレイヤーの横方向の中心
#define ENEMY_PIVOT_Y      (ENEMY_TEX_H/2)   // プレイヤーの縦方向の下端

#define ENEMY_SPEED		(5)

#define ENEMY_CORE_TEX_W        (128.0f)   // プレイヤーの画像1つの幅
#define ENEMY_CORE_TEX_H        (128.0f)   // プレイヤーの画像1つの高さ
#define ENEMY_CORE_PIVOT_X      (ENEMY_CORE_TEX_W/2)    // プレイヤーの横方向の中心
#define ENEMY_CORE_PIVOT_Y      (ENEMY_CORE_TEX_H/2)   // プレイヤーの縦方向の下端
#define E_SCALE	(1.0f)
#define ENEMY_CD 1
//------< 構造体 >---------------------------------------------------------------

enum class ENEMY_TYPE { ENEMY_TYPE_POP, ENEMY_TYPE_THROWER, ENEMY_TYPE_THROWN_ITEM };
class ENEMY {
private:
public:
	float timer;
	ENEMY_TYPE type;
	float angle;
	float speed;
	VECTOR2 BasePosition;
	VECTOR2 position;
	float force;
	VECTOR2 scale;
	VECTOR2 texPos;
	VECTOR2 texSize;
	VECTOR2 pivot;
	VECTOR4 color;
	VECTOR2 faceing = { 1,0 };


	ENEMY(VECTOR2 pos, float _angle, float _force, ENEMY_TYPE _type) {
		timer = 0;
		BasePosition = pos;
		type = _type;
		angle = _angle;
		force = _force;
		position = pos + LaunchCalculatePosition(_angle, _force, timer);
		scale = { E_SCALE, E_SCALE };
		texPos = { int(type) * ENEMY_TEX_W, 0 };
		texSize = { ENEMY_TEX_W, ENEMY_TEX_H };
		pivot = { ENEMY_PIVOT_X, ENEMY_PIVOT_Y };
		color = { 1.000f, 1.0f, 1.0f, 1.0f };
		speed = 0;
	}


};
//------< 変数 >----------------------------------------------------------------
extern enum class ENEMY_TYPE;

//------< プロトタイプ宣言 >-----------------------------------------------------
void enemy_init();
void enemy_update();
void enemy_render();
void enemy_deinit();
void enemy_act();
void enemy_kill(float bomb_blast_range, VECTOR2 blast_posison);
