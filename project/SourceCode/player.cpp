#include "player.h"
#include "../GameLib/game_lib.h"
#include "../GameLib/obj2d_data.h"
#include "common.h"
#include "audio.h"
#include "m_scene.h"
using namespace input;

// プレイヤーの状態を管理する変数
int player_state;
class PLAYER {
public:
	float angle;
	float speed;
	VECTOR2 position;
	VECTOR2 scale;
	VECTOR2 texPos;
	VECTOR2 texSize;
	VECTOR2 pivot;
	VECTOR4 color;



};

//--------------------------------------
//  プレイヤーの初期設定
//--------------------------------------
void player_init()
{
	// プレイヤーの状態を初期化
	player_state = 0;
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

		// 次の状態に遷移
		++player_state;
		/*fallthrough*/

	case 1:
		//////// パラメータの設定 ////////

		// 次の状態に遷移
		++player_state;
		/*fallthrough*/

	case 2:

		player_act();
		break;
	}
}

//--------------------------------------
//  プレイヤーの描画処理
//--------------------------------------
void player_render()
{

}

//--------------------------------------
//  プレイヤーの行動処理
//--------------------------------------
void player_act()
{

}
