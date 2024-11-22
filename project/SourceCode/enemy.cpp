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

#include "score.h"

Sprite* sprEnemy;
bool IsThrowing = true;

int ThrowTimer;
using namespace input;

// プレイヤーの状態を管理する変数
int enemy_state;
int enemy_timer;


float spawnPointIncreaseValue = 5;
VECTOR2 spawnPoint;
float spawnAngle = 90;
float spawnAngleIncreaseValue = 1;
int spawnrate = 60;
std::vector<ENEMY> enemy_pop;
std::vector<ENEMY> enemy_thrower;
std::vector<ENEMY> enemy_thrown_item;
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
	safe_delete(sprEnemy);

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
		enemy_thrower.push_back(ENEMY({ SCREEN_H / 2.0f,80 }, 0, 0, ENEMY_TYPE::ENEMY_TYPE_THROWER));
		sprEnemy = sprite_load(L"./Data/Images/Entity/Enemy/Enemy.png");
		// 次の状態に遷移
		++enemy_state;
		/*fallthrough*/

	case 1:
		//////// パラメータの設定 ////////
		IsThrowing = true;
		// 次の状態に遷移
		++enemy_state;
		/*fallthrough*/

	case 2:
		enemy_act();
		enemy_timer++;

		if (enemy_timer % 15 == 0)
		{

			enemy_pop.push_back(ENEMY(spawnPoint, spawnAngle, rand() % (SCREEN_H / 24) + 50, ENEMY_TYPE::ENEMY_TYPE_POP));
		}

		break;
	}
}

//--------------------------------------
//  プレイヤーの描画処理
//--------------------------------------
void enemy_render()
{
	//for (auto& enemy : enemy_pop) {
	//	primitive::circle(enemy.position.x + 5, enemy.position.y + 5, 15, 1, 1, 0, 0, 0, 0, 0.5f);
	//}

	//GameLib::setBlendMode(Blender::BS_SUBTRACT);

	//for (auto& enemy : enemy_pop) {
	//	//primitive::circle(enemy.position.x, enemy.position.y, 15, 1, 1, 0, 1, 0.4f, 0.6f, 1.0f);
	//	sprite_render(sprEnemy,
	//		enemy.position.x, enemy.position.y,
	//		enemy.scale.x, enemy.scale.y,
	//		enemy.texPos.x, enemy.texPos.y,
	//		enemy.texSize.x, enemy.texSize.y,
	//		enemy.pivot.x, enemy.pivot.y,
	//		LaunchCalculateRotation(ToRadian(enemy.angle), enemy.force, enemy.timer),
	//		1, 1, 1, 1);

	//	GameLib::setBlendMode(Blender::BS_ALPHA);
	//}
	for (auto& enemy : enemy_pop) {
		//primitive::circle(enemy.position.x, enemy.position.y, 15, 1, 1, 0, 1, 0.4f, 0.6f, 1.0f);
		sprite_render(sprEnemy,
			enemy.position.x + 5, enemy.position.y - 5,
			enemy.scale.x, enemy.scale.y,
			enemy.texPos.x, enemy.texPos.y,
			enemy.texSize.x, enemy.texSize.y,
			enemy.pivot.x, enemy.pivot.y,
			LaunchCalculateRotation(ToRadian(enemy.angle), enemy.force, enemy.timer),
			enemy.color.x, enemy.color.y, enemy.color.z, enemy.color.w);

	}



	for (auto& enemy : enemy_thrower) {
		//primitive::circle(enemy.position.x, enemy.position.y, 20, 1, 1, 0, 1, 1.0f, 0.6f, 1.0f);
		sprite_render(sprEnemy, enemy.position.x, enemy.position.y, enemy.scale.x, enemy.scale.y, enemy.texPos.x, enemy.texPos.y, enemy.texSize.x, enemy.texSize.y, enemy.pivot.x, enemy.pivot.y, enemy.angle, enemy.color.x, enemy.color.y, enemy.color.z, enemy.color.w);
	}



	for (auto& enemy : enemy_thrown_item) {
		//primitive::circle(enemy.position.x, enemy.position.y, 10, 1, 1, 0, 1, 0.6f, 0.4f, 1.0f);
		sprite_render(sprEnemy,
			enemy.position.x, enemy.position.y,
			enemy.scale.x, enemy.scale.y,
			enemy.texPos.x, enemy.texPos.y,
			enemy.texSize.x, enemy.texSize.y,
			enemy.pivot.x, enemy.pivot.y,
			LaunchCalculateRotation(ToRadian(enemy.angle), enemy.force, enemy.timer),
			enemy.color.x, enemy.color.y, enemy.color.z, enemy.color.w);
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




	if (enemy_timer % spawnrate == 0 && IsThrowing)
	{
		enemy_thrown_item.push_back(ENEMY(enemy_thrower[0].position, rand() % 3 - 1, 25.0f, ENEMY_TYPE::ENEMY_TYPE_THROWN_ITEM));
	}


	for (auto& enemy : enemy_thrown_item) {
		enemy.timer += 0.1f;
		enemy.position = enemy.BasePosition + LaunchCalculatePosition(ToRadian(enemy.angle * 45 + 90), enemy.force, enemy.timer);
		enemy.position = edge_reflecting(enemy.position);

		enemy.BasePosition = magnetic_force_suction(enemy.BasePosition, magnetic_force);
	}

	auto thrown_it = std::remove_if(enemy_thrown_item.begin(), enemy_thrown_item.end(),
		[](const ENEMY& enemy) { return enemy.position.y >= SCREEN_H + 100; });
	enemy_thrown_item.erase(thrown_it, enemy_thrown_item.end());



	if (ThrowTimer <= 0)
	{
		if (!IsThrowing)
		{
			IsThrowing = true;
		}
	}
	else {

		ThrowTimer--;
	}

}


void enemy_kill(float bomb_blast_range, VECTOR2 blast_posison)
{
	for (auto& enemy : enemy_pop) {


		if (isCircleColliding(blast_posison, bomb_blast_range, enemy.position, ENEMY_CD)) {
			score_add(10);
			item_spawn(enemy.position);

		}

	}
	enemy_pop.erase(
		std::remove_if(enemy_pop.begin(), enemy_pop.end(),
			[&](const ENEMY& enemy) {
				return isCircleColliding(blast_posison, bomb_blast_range, enemy.position, ENEMY_CD);
			}),
		enemy_pop.end()
	);
}