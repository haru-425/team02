#include "player.h"
#include "../GameLib/game_lib.h"
#include "../GameLib/obj2d_data.h"
#include "common.h"
#include "audio.h"
#include "m_scene.h"
#include "bomb.h"
#include "system.h"
using namespace input;

// プレイヤーの状態を管理する変数
int player_state;

PLAYER player;
extern Bomb bomb;
//--------------------------------------
//  プレイヤーの初期設定
//--------------------------------------
void player_init()
{
	// プレイヤーの状態を初期化
	player_state = 0;
	player.player_time = 0;
	player.position = VECTOR2(500.0f, 350.0f);
	player.strat_position = player.position;
}

//--------------------------------------
//  プレイヤーの終了処理
//--------------------------------------
void player_deinit()
{
}

//--------------------------------------
//  プレイヤーの更新処理
//--------------------------------------
void player_update()
{
	switch (player_state)
	{
	case 0:
		//////// 初期設定 ////////

		player.position = VECTOR2(500, 350);
		// 次の状態に遷移
		++player_state;
		/*fallthrough*/

	case 1:
		//////// パラメータの設定 ////////

		// 次の状態に遷移
		++player_state;
		/*fallthrough*/

	case 2:
		player.player_time+=0.1f;
		player_act();
		if (TRG(0)& L_CLICK)
		{
			bomb_throw();
		}
		debug::setString("player.position.x:%f", player.position.x);
		break;
	}
}

//--------------------------------------
//  プレイヤーの描画処理
//--------------------------------------
void player_render()
{

	primitive::circle(player.position.x, player.position.y, 10, 1, 1, 0, 1, 0, 1);
}

//--------------------------------------
//  プレイヤーの行動処理
//--------------------------------------
void player_act()
{

}

//--------------------------------------
//  プレイヤーの行動処理
//--------------------------------------
void player_movement(float angle, float force)
{
	player.position = player.strat_position + LaunchCalculatePosition(angle, force, player.player_time, PLAYER_GRAVITY);
}