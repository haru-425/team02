#include "item.h"
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

#include "player.h"
#include "enemy.h"
#include "score.h"
#include "bomb.h"

Sprite* sprItem;
float ITEM_EFFECT_TRANSPARENCY[5] = { 0.5f,0.5f,0.5f,0.5f,0.5f };

using namespace input;

// プレイヤーの状態を管理する変数
int item_state;
int item_timer;

std::vector<ITEM> item;
//--------------------------------------
//  プレイヤーの初期設定
//--------------------------------------
void item_init()
{
	// プレイヤーの状態を初期化
	item_state = 0;
	item_timer = 0;


}

//--------------------------------------
//  プレイヤーの終了処理
//--------------------------------------
void item_deinit()
{

	safe_delete(sprItem);

}

//--------------------------------------
//  プレイヤーの更新処理
//--------------------------------------
void item_update()
{
	switch (item_state)
	{
	case 0:
		//////// 初期設定 ////////
		sprItem = sprite_load(L"./Data/Images/Entity/Items.png");
		// 次の状態に遷移
		++item_state;
		/*fallthrough*/

	case 1:
		//////// パラメータの設定 ////////
		// 次の状態に遷移

		for (int i = 0; i < 5; i++)
		{

			ITEM_EFFECT_TRANSPARENCY[i] = 0.7f;
		}
		++item_state;
		/*fallthrough*/

	case 2:
		item_act();

		item_timer++;
		break;
	}
}

//--------------------------------------
//  プレイヤーの描画処理
//--------------------------------------
void item_render()
{
	for (auto& items : item) {
		//primitive::circle(items.position.x, items.position.y, 15, 1, 1, 0, 1, 0.4f, 0.6f, 1.0f);

		sprite_render(sprItem,
			items.position.x, items.position.y,
			items.scale.x * ITEM_SCALE, items.scale.y * ITEM_SCALE,
			items.texPos.x, items.texPos.y,
			items.texSize.x, items.texSize.y,
			items.pivot.x, items.pivot.y,
			items.angle,
			items.color.x, items.color.y, items.color.z, items.color.w);
	}



	string effect_str = "Score x" + to_string(int(SCORE_DIAMETER));
	text_out(6, effect_str, SCREEN_H, SCREEN_H / 100 * 10, 0.8f, 0.8f, 1, 1, 1, ITEM_EFFECT_TRANSPARENCY[int(ITEM_TYPE::ScoreTwoTimes)], TEXT_ALIGN::UPPER_RIGHT);

	effect_str = "Range x" + to_string(player.bomb_reinforce_item);
	text_out(6, effect_str, SCREEN_H, SCREEN_H / 100 * 15, 0.8f, 0.8f, 1, 1, 1, 1, TEXT_ALIGN::UPPER_RIGHT);



}
//--------------------------------------
//  プレイヤーの行動処理
//--------------------------------------
void item_act()
{
	for (auto& items : item) {
		//primitive::circle(enemy.position.x, enemy.position.y, 15, 1, 1, 0, 1, 0.4f, 0.6f, 1.0f);
		items.timer -= 1.0f;

		if (items.scale.x * ITEM_SCALE <= 0.3f)
		{

			items.color.w = (int(items.timer / 10.0f) % 2) * 0.2f + 0.5f;
		}
		else
		{
			items.scale -= { 0.2f / items.timer, 0.2f / items.timer };

		}
		items.position.y -= 0.5f;
	}


	for (auto& items : item) {
		//primitive::circle(enemy.position.x, enemy.position.y, 15, 1, 1, 0, 1, 0.4f, 0.6f, 1.0f);
		items.timer -= 1.0f;

		if (items.scale.x * ITEM_SCALE <= 0.3f)
		{

			items.color.w = (int(items.timer / 10.0f) % 2) * 0.2f + 0.5f;
		}
		else
		{
			items.scale -= { 0.2f / items.timer, 0.2f / items.timer };

		}
	}




	auto item_it = std::remove_if(item.begin(), item.end(),
		[](const ITEM& items) { return items.timer <= 0; });
	item.erase(item_it, item.end());


	for (auto& items : item) {

		if (isCircleColliding(items.position, 64 * (items.scale.x * ITEM_SCALE), player.position, 10)) {
			switch (items.type)
			{
			case  ITEM_TYPE::ExplosionRangeCloseUp:
				if (player.bomb_reinforce_item < 3)
				{
					player.bomb_reinforce_item++;

				}
				sound::play(XWB_SOUNDS, XWB_SOUND_ITEM_ACQUISITION);
				break;
			case ITEM_TYPE::HPRecovery:
				if (player.hp > PLAYER_MAX_HP)break;
				else player.hp += 1;
				sound::play(XWB_SOUNDS, XWB_SOUND_HEALING);
				break;
			case ITEM_TYPE::LimitTimeExtended:
				LIMIT_TIME += 60 * 5;
				sound::play(XWB_SOUNDS, XWB_SOUND_ITEM_ACQUISITION);
				break;
			case  ITEM_TYPE::ScoreTwoTimes:
				score_diameter_set(2, 60 * 5);
				sound::play(XWB_SOUNDS, XWB_SOUND_ITEM_ACQUISITION);
				break;
			case ITEM_TYPE::TopEnemyInvalid:
				IsThrowing = false;
				ThrowTimer = 60 * 10;
				sound::play(XWB_SOUNDS, XWB_SOUND_ITEM_ACQUISITION);
				break;
			}
		}
	}


	item.erase(
		std::remove_if(item.begin(), item.end(),
			[&](const ITEM& items) {
				return isCircleColliding(items.position, 64 * (items.scale.x * ITEM_SCALE), player.position, 10);
			}),
		item.end()
	);
}


void item_spawn(VECTOR2 _pos) {
	int ITEM_POP_RATE = rand() % 10;
	if (ITEM_POP_RATE < 10)
	{
		switch (rand() % 5)
		{
		case 0:
			item.push_back(ITEM(_pos, ITEM_TYPE::ExplosionRangeCloseUp, 60 * 10.0f));
			break;
		case 1:
			item.push_back(ITEM(_pos, ITEM_TYPE::HPRecovery, 60 * 10.0f));
			break;
		case 2:
			item.push_back(ITEM(_pos, ITEM_TYPE::LimitTimeExtended, 60 * 10.0f));
			break;
		case 3:
			item.push_back(ITEM(_pos, ITEM_TYPE::ScoreTwoTimes, 60 * 10.0f));
			break;
		case 4:
			item.push_back(ITEM(_pos, ITEM_TYPE::TopEnemyInvalid, 60 * 10.0f));
			break;
		}
	}

}
void item_spawn(VECTOR2 _pos, ITEM_TYPE _type, float _time) {

	item.push_back(ITEM(_pos, _type, 60.0f * _time));
}
