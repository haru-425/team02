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
	VECTOR2 BasePosition;
	VECTOR2 position;
	float force;
	VECTOR2 scale;
	VECTOR2 texPos;
	VECTOR2 texSize;
	VECTOR2 pivot;
	VECTOR4 color;
	VECTOR2 faceing = { 1,0 };


	ENEMY(VECTOR2 pos, float _angle, float _force) {
		timer = 0;
		BasePosition = pos;
		angle = _angle;
		force = _force;
		position = pos + LaunchCalculatePosition(_angle, _force, timer);
		scale = { E_SCALE, E_SCALE };
		texPos = { ENEMY_TEX_W * int(type), 0 };
		texSize = { ENEMY_TEX_W, ENEMY_TEX_H };
		pivot = { ENEMY_PIVOT_X, ENEMY_PIVOT_Y };
		color = { 1.000f, 1.0f, 1.0f, 1.0f };
		speed = 0;
	}


};

float spawnPointIncreaseValue = 5;
VECTOR2 spawnPoint;
float spawnAngle = 90;
float spawnAngleIncreaseValue = 1;
int spawnrate = 60;
std::vector<ENEMY> enemy_pop;
std::vector<ENEMY> enemy_thrower;
std::vector<ENEMY> enemy_thrown_item;
;
//--------------------------------------
//  プレイヤーの初期設定
//--------------------------------------
void enemy_init()
{
	// プレイヤーの状態を初期化
	enemy_state = 0;
	enemy_timer = 0;
	spawnPoint = { 0,float(SCREEN_H) };
	srand(time(NULL));
}

//--------------------------------------
//  プレイヤーの終了処理
//--------------------------------------
void enemy_deinit()
{
	enemy_pop.erase(enemy_pop.begin(), enemy_pop.end());
	enemy_thrower.erase(enemy_thrower.begin(), enemy_thrower.end());
	enemy_thrown_item.erase(enemy_thrown_item.begin(), enemy_thrown_item.end());

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
		enemy_thrower.push_back(ENEMY({ SCREEN_H / 2.0f,50 }, 0, 0));
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

			enemy_pop.push_back(ENEMY(spawnPoint, spawnAngle, rand() % 50 + 50));
		}

		break;
	}
}

//--------------------------------------
//  プレイヤーの描画処理
//--------------------------------------
void enemy_render()
{
	for (auto& enemy : enemy_pop) {
		primitive::circle(enemy.position.x + 5, enemy.position.y + 5, 15, 1, 1, 0, 0, 0, 0, 0.5f);
	}

	for (auto& enemy : enemy_pop) {
		primitive::circle(enemy.position.x, enemy.position.y, 15, 1, 1, 0, 1, 0.4f, 0.6f, 1.0f);
	}


	for (auto& enemy : enemy_thrower) {
		primitive::circle(enemy.position.x, enemy.position.y, 15, 1, 1, 0, 1, 0.4f, 0.6f, 1.0f);
	}
	//以下debagu用

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
	for (auto& enemy : enemy_pop) {
		enemy.timer += 0.1f;
		enemy.position = enemy.BasePosition + LaunchCalculatePosition(ToRadian(enemy.angle), enemy.force, enemy.timer);
		enemy.position = edge_reflecting(enemy.position);

		enemy.BasePosition = magnetic_force_suction(enemy.BasePosition, magnetic_force);
	}

	auto it = std::remove_if(enemy_pop.begin(), enemy_pop.end(),
		[](const ENEMY& enemy) { return enemy.position.y >= SCREEN_H + 100; });
	enemy_pop.erase(it, enemy_pop.end());




	for (auto& enemy : enemy_thrower) {
		enemy.position += enemy.faceing;
		if (enemy.position.x > SCREEN_H || enemy.position.x < 0 || enemy.position.y > SCREEN_H || enemy.position.y < 0)
		{
			enemy.faceing *= -1;
		}
	}




	if (enemy_timer % spawnrate == 0)
	{

		enemy_pop.push_back(ENEMY(spawnPoint, spawnAngle, rand() % 50 + 50));
	}
}


void enemy_kill(int kill_num) {

	enemy_pop.erase(enemy_pop.begin() + kill_num);
}