#include "enemy.h"
#include "../GameLib/game_lib.h"
#include "../GameLib/input_manager.h"
#include "../GameLib/obj2d_data.h"

#include <windowsx.h>
#include "common.h"
#include "audio.h"
#include "m_scene.h"
#include "system.h"
#include <time.h>
#include<stdlib.h>


#include <vector>
#include <algorithm>



using namespace input;

// プレイヤーの状態を管理する変数
int enemy_state;
int enemy_timer;
enum class ENEMY_TYPE {
	JUMP,
};
class ENEMY {
private:
public:
	ENEMY_TYPE type;
	float timer;

	float angle;
	float speed;
	float trackingRange;
	VECTOR2 BasePosition;
	VECTOR2 position;
	float force;
	VECTOR2 scale;
	VECTOR2 texPos;
	VECTOR2 texSize;
	VECTOR2 pivot;
	VECTOR4 color;

	ENEMY(VECTOR2 pos, float _angle, float _force) {
		timer = 0;
		BasePosition = pos;
		angle = _angle;
		force = _force;
		position = pos + LaunchCalculatePosition(_angle, _force, timer);
		type = ENEMY_TYPE::JUMP;
		scale = { E_SCALE, E_SCALE };
		texPos = { ENEMY_TEX_W * int(type), 0 };
		texSize = { ENEMY_TEX_W, ENEMY_TEX_H };
		pivot = { ENEMY_PIVOT_X, ENEMY_PIVOT_Y };
		color = { 1.000f, 1.0f, 1.0f, 1.0f };
		trackingRange = 0;
		speed = 0;
	}


};

float spawnPointIncreaseValue = 5;
VECTOR2 spawnPoint;
float spawnAngle = 90;
float spawnAngleIncreaseValue = 1;

std::vector<ENEMY> enemy;
//--------------------------------------
//  プレイヤーの初期設定
//--------------------------------------
void enemy_init()
{
	// プレイヤーの状態を初期化
	enemy_state = 0;
	enemy_timer = 0;
	spawnPoint = { 0,float(SCREEN_H / 2.0f) };
	srand(time(NULL));
}

//--------------------------------------
//  プレイヤーの終了処理
//--------------------------------------
void enemy_deinit()
{
}

//--------------------------------------
//  プレイヤーの更新処理
//--------------------------------------
void enemy_update()
{
	switch (enemy_state)
	{
	case 0:
		//////// 初期設定 ////////

		// 次の状態に遷移
		++enemy_state;
		/*fallthrough*/

	case 1:
		//////// パラメータの設定 ////////

		// 次の状態に遷移
		++enemy_state;
		/*fallthrough*/

	case 2:
		enemy_act();
		enemy_timer++;

		if (enemy_timer % 20 == 0)
		{

			enemy.push_back(ENEMY(spawnPoint, spawnAngle, rand() % 50 + 50));
		}
		break;
	}
}

//--------------------------------------
//  プレイヤーの描画処理
//--------------------------------------
void enemy_render()
{
	for (auto& enemy : enemy) {
		primitive::circle(enemy.position.x, enemy.position.y, 15, 1, 1, 0, 1, 1, 2, 0.5f);
	}

	//以下debagu用

	//debug::setString("enemytimer%d", enemy_timer);
	//debug::setString("add%f", spawnPointIncreaseValue);
	//debug::setString("angle%f", spawnAngle);
	//debug::setString("spawnpoint%f,%f", spawnPoint.x, spawnPoint.y);
	//for (auto& enemy : enemy) {

	//	debug::setString("enemy[]%f:pos%f.%f", enemy.timer, enemy.position.x, enemy.position.y);
	//}
	primitive::line(SCREEN_H, 0, SCREEN_H, SCREEN_H);

}
//--------------------------------------
//  プレイヤーの行動処理
//--------------------------------------
void enemy_act()
{
	spawnPoint.x += spawnPointIncreaseValue;
	if (spawnPoint.x <= 0 || spawnPoint.x >= SCREEN_H)
	{
		spawnPointIncreaseValue *= -1;
	}


	spawnAngle += spawnAngleIncreaseValue;
	if (spawnAngle >= 105 || spawnAngle <= 75)
	{
		spawnAngleIncreaseValue *= -1;
	}
	//要素数だけループ
	for (auto& enemy : enemy) {
		enemy.timer += 0.1f;
		enemy.position = enemy.BasePosition + LaunchCalculatePosition(enemy.angle, enemy.force, enemy.timer);
		// 画面外に出た場合の処理
		if (enemy.position.x < 0) enemy.position.x *= -1;
		if (enemy.position.x > SCREEN_H) enemy.position.x = SCREEN_H - (enemy.position.x - SCREEN_H);
	}

	auto it = std::remove_if(enemy.begin(), enemy.end(),
		[](const ENEMY& enemy) { return enemy.position.y >= SCREEN_H + 100; });
	enemy.erase(it, enemy.end());

}
