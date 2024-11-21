#include "player.h"
#include "../GameLib/game_lib.h"
#include "../GameLib/obj2d_data.h"
#include "common.h"
#include "audio.h"
#include "bomb.h"
#include "enemy.h"
#include "system.h"
#include "m_scene.h"
#include <vector>
#include <algorithm>
#include <DirectXMath.h>
using namespace input;

// プレイヤーの状態を管理する変数
int player_state;
float force = 0.0f;
float angle = 0.0f;
float click_time = 0;
PLAYER player;
extern std::vector<ENEMY> enemy_pop;
extern Bomb bomb;
extern S_SCENE game_state;
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
	player.hp = PLAYER_MAX_HP;
	player.damege_invincible = false;
	player.bomb_reinforce_item=0;
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
		player.player_time += 0.1f;
		player_act();
		if (STATE(0) & L_CLICK && click_time<= BOMB_MAX_CHARGE)
		{
			click_time += 0.2;
		}
		if (bomb.bomb_state == 0)
		{
			// クリックを離した瞬間に爆弾を投げる
			if (TRG_RELEASE(0) & L_CLICK)
			{
				bomb_throw(click_time, player.bomb_reinforce_item);
				click_time = 0;
				bomb.bomb_state = 1; // 次の状態に進む
			}
		}
		else if (bomb.bomb_state == 2)
		{
			// クリックを押した瞬間に爆弾を膨張させる
			if (TRG(0) & L_CLICK)
			{
				bomb_expansion();
				bomb.bomb_state = -1; // 状態を初期化
			}
		}
		else if(TRG_RELEASE(0) & L_CLICK && bomb.bomb_state == -1)
		{
			bomb.bomb_state = 0;
		}
		
		for (auto& enemy: enemy_pop)
		{
			if (isColliding(player.position, player.texSize, enemy.position, enemy.texSize, enemy.angle)
				&& player.damege_invincible == false)//敵と自分との当たり判定を条件に入れる
			{
				player.hp -= 1;
				if (player.hp == 0)
				{
					game_state.state = S_SCENE::F_TRANSITION;
				}
				player.damege_invincible = true;
				break;
			}
		}
		if (player.damege_invincible == true)
		{
			player.invincible_time++;
			if (player.invincible_time % 120 == 0)
			{
				player.color.w = 0;
			}
			else if (player.invincible_time % 60 == 0)
			{
				player.color.w = 1;
			}
			if (player.invincible_time >= PLAYER_MAX_INVINCIBLE_TIME*60)
			{
				player.color.w = 1;
				player.damege_invincible = false;
				player.invincible_time = 0;
			}
		}

		//デバックログ
		debug::setString("player.hp:%d", player.hp);
		break;
	}
}

//--------------------------------------
//  プレイヤーの描画処理
//--------------------------------------
void player_render()
{

	primitive::circle(player.position.x, player.position.y, 10, 1, 1, 0, 1, 0, 1);
	debug::setString("force%f", force);


	if (STATE(0) & L_CLICK && click_time)
	{
		primitive::circle(player.position.x, player.position.y, BOMB_BLAST_MAX_INIT_RANGE + (click_time * 5), 1, 1, 0, 0.0f, 0.2f, 0.4f, 0.2f);
	}
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
	player.position = edge_reflecting(player.position);
	//if (player.position.y < 0)
	//{
	//	::force = 0.0;
	//	player.player_time = 0.0f;
	//	player.strat_position = { player.position.x, 0.0f };
	//}


}