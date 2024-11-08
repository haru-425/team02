#pragma once // 二重インクルードを防ぐためのディレクティブ
#ifndef BOMB_H 
#define BOMB_H

#include "../GameLib/game_lib.h"
#include <DirectXMath.h>
using namespace DirectX;

void bomb_init();			// 爆弾の初期化
void bomb_deinit();			// 爆弾のリセット
void bomb_throw();			// プレイヤーが爆弾を投げる
void bomb_update();			// 爆弾の状態（タイマーなど）を更新
void bomb_explosion();		// 爆弾の爆発処理
void bomb_render();			// 爆弾と爆風範囲の描画処理

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