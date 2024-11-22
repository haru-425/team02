#pragma once
#include "../GameLib/game_lib.h"
#include "../GameLib/obj2d_data.h"
#include "common.h"
#include "audio.h"
#include "bomb.h"
#include "enemy.h"
#include "system.h"
#include "m_scene.h"
#include <vector>
#include <algorithm>
#include <DirectXMath.h>

//------< 定数 >----------------------------------------------------------------
#define PLAYER_TEX_W        (400.0f)   // プレイヤーの画像1つの幅
#define PLAYER_TEX_H        (400.0f)   // プレイヤーの画像1つの高さ
#define PLAYER_PIVOT_X      (PLAYER_TEX_W/2)    // プレイヤーの横方向の中心
#define PLAYER_PIVOT_Y      (PLAYER_TEX_H/2)   // プレイヤーの縦方向の下端

#define PLAYER_SPEED		(5)

#define PLAYER_CORE_TEX_W        (128.0f)   // プレイヤーの画像1つの幅
#define PLAYER_CORE_TEX_H        (128.0f)   // プレイヤーの画像1つの高さ
#define PLAYER_CORE_PIVOT_X      (PLAYER_CORE_TEX_W/2)    // プレイヤーの横方向の中心
#define PLAYER_CORE_PIVOT_Y      (PLAYER_CORE_TEX_H/2)   // プレイヤーの縦方向の下端
#define PLAYER_GRAVITY 2.45f
#define PLAYER_MAX_INVINCIBLE_TIME 3
#define PLAYER_MAX_HP 10


//------< 構造体 >---------------------------------------------------------------


//------< プロトタイプ宣言 >-----------------------------------------------------
void player_init();
void player_update();
void player_render();
void player_deinit();
void player_act(PLAYER player);
void player_movement(float angle, float force);

class PLAYER {
public:
	float angle;
	float speed;
	float player_time;
	int hp;
	bool damege_invincible;
	int invincible_time;
	VECTOR2 position;
	VECTOR2 strat_position;
	VECTOR2 scale;
	VECTOR2 texPos;
	VECTOR2 texSize;
	VECTOR2 pivot;
	VECTOR4 color;

	int bomb_reinforce_item;
};
//------< 変数 >----------------------------------------------------------------
extern PLAYER player;