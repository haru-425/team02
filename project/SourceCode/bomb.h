#pragma once // 二重インクルードを防ぐためのディレクティブ
#define BOMB_H

#include "../GameLib/game_lib.h"
#include "player.h"
#include "enemy.h"
#include "system.h"

#include "common.h"
#include <vector>
#include <algorithm>
#include <DirectXMath.h>

using namespace DirectX;

#define BOMB_BLAST_STRANGE 0.28f
#define BOMB_BLAST_MAX_INIT_RANGE 100.0f
#define BOMB_BLAST_R_INC 10.0f
#define BOMB_ADJUSTMENT 20.0f
#define BOMB_MAX_CHARGE 20
#define BOMB_ADD_CLIKC_TIME (float)(BOMB_MAX_CHARGE/3/60)//　爆弾の最大爆発範囲/チャージできる最大秒数/フレーム数

void bomb_init();							// 爆弾の初期化
void bomb_deinit();							// 爆弾のリセット
void bomb_throw(float muster_up, int bomb_up);			// プレイヤーが爆弾を投げる
void bomb_expansion();						//爆発処理
void bomb_update();							// 爆弾の状態（タイマーなど）を更新
void bomb_render();							// 爆弾と爆風範囲の描画処理

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

class Bomb_range
{
public:
	Bomb_range(VECTOR2 position);
	~Bomb_range();
	bool player_launch;
	VECTOR2 judg_position;
	float bomb_blast_range;
	float bomb_blast_max_range;
	void bomb_range_expansion();
};

extern std::vector<Bomb_range> range_Box;
