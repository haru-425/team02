#include "enemy.h"
#include "../GameLib/game_lib.h"
#include "../GameLib/input_manager.h"
#include "../GameLib/obj2d_data.h"

#include <windowsx.h>
#include "common.h"
#include "audio.h"
#include "m_scene.h"
using namespace input;

// プレイヤーの状態を管理する変数
int enemy_state;
enum class ENEMY_TYPE {
	JUMP,
};
class ENEMY {
private:
public:
	ENEMY_TYPE type;
	int timer;

	int trackingRangeDiameter;
	float angle;
	float speed;
	float trackingRange;
	VECTOR2 BasePosition;
	VECTOR2 scale;
	VECTOR2 texPos;
	VECTOR2 texSize;
	VECTOR2 pivot;
	VECTOR4 color;

	ENEMY(VECTOR2 pos, float angle, float initialSpeed) {
		timer = 0;
		BasePosition = pos;
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

float spawnPointIncreaseValue = 1;
VECTOR2 spawnPoint;

ENEMY* enemy[100];
//--------------------------------------
//  プレイヤーの初期設定
//--------------------------------------
void enemy_init()
{
	// プレイヤーの状態を初期化
	enemy_state = 0;
	spawnPoint = { 0,SCREEN_H };
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
		break;
	}
}

//--------------------------------------
//  プレイヤーの描画処理
//--------------------------------------
void enemy_render()
{

}

//--------------------------------------
//  プレイヤーの行動処理
//--------------------------------------
void enemy_act()
{
	for (ENEMY* time : enemy) {

	}
}
