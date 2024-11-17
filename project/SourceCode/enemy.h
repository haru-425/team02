#pragma once
#include "../GameLib/game_lib.h"
#include <vector>
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
#define E_SCALE	(1.0f)
#define ENEMY_CD 1
//------< 構造体 >---------------------------------------------------------------


//------< 変数 >----------------------------------------------------------------
extern enum class ENEMY_TYPE;

//------< プロトタイプ宣言 >-----------------------------------------------------
void enemy_init();
void enemy_update();
void enemy_render();
void enemy_deinit();
void enemy_act();
void enemy_kill(float bomb_blast_range,VECTOR2 blast_posison);
