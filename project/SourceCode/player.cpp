#include "player.h"

using namespace input;

// プレイヤーの状態を管理する変数
int player_state; // プレイヤーの現在の状態（フェーズ）を表す
float force = 0.0f; // プレイヤーの行動に関連する力
float angle = 0.0f; // プレイヤーの角度
float click_time = 0; // クリックを保持した時間（爆弾チャージに使用）
Sprite* sprPLAYER; // プレイヤーのスプライトデータ
extern std::vector<ENEMY> enemy_pop; // ゲーム内の敵リスト（外部で定義）
extern Bomb bomb; // 爆弾の管理クラス（外部で定義）
extern S_SCENE game_state; // ゲームの現在の状態（外部で定義）

//--------------------------------------
//  プレイヤーの初期設定
//--------------------------------------
void player_init()
{
	// プレイヤーの状態を初期化
	player_state = 0; // 状態を初期化
	player.player_time = 0; // プレイヤーの行動時間をリセット
	player.position = VECTOR2(500.0f, 350.0f); // プレイヤーの初期位置
	player.strat_position = player.position; // 初期位置を記録
	player.hp = PLAYER_MAX_HP; // 最大HPを設定
	player.damege_invincible = false; // 無敵状態を解除
	player.invincible_time = true; // 無敵時間を初期化
	player.bomb_reinforce_item = 0; // 爆弾強化アイテムの初期化
}

//--------------------------------------
//  プレイヤーの終了処理
//--------------------------------------
void player_deinit()
{
	safe_delete(sprPLAYER); // スプライトデータを安全に削除
}

//--------------------------------------
//  プレイヤーの更新処理
//--------------------------------------
void player_update(PLAYER& player)
{
	switch (player_state)
	{
	case 0: // 初期化状態
		player.position = VECTOR2(500, 350); // 初期位置を再設定
		++player_state; // 次の状態へ
		/*fallthrough*/

	case 1: // パラメータの設定
		sprPLAYER = sprite_load(L"./Data/Images/Entity/player.png"); // スプライトを読み込む
		player.color.w = 1; // プレイヤーの色設定（不透明）
		++player_state; // 次の状態へ
		/*fallthrough*/

	case 2: // プレイ中の更新処理
		player.player_time += 0.1f; // 行動時間を更新
		player_act(player); // プレイヤーの行動を処理

		// 敵との当たり判定処理
		for (auto& enemy : enemy_pop)
		{
			if (isColliding(player.position, player.texSize, enemy.position, enemy.texSize, enemy.angle)
				&& player.damege_invincible == false) // 無敵でない場合
			{
				player.hp -= 1; // HPを減少
				sound::play(XWB_SOUNDS, XWB_SOUND_HIT); // 被弾音を再生
				player.damege_invincible = true; // 無敵状態に切り替え
				break;
			}
		}

		for (auto& enemy : enemy_thrown_item)
		{
			if (isColliding(player.position, player.texSize, enemy.position, (enemy.texSize / 2) * (1 / 3.5f), enemy.angle)
				&& player.damege_invincible == false) // 無敵でない場合
			{
				player.hp -= 1; // HPを減少
				sound::play(XWB_SOUNDS, XWB_SOUND_HIT); // 被弾音を再生
				player.damege_invincible = true; // 無敵状態に切り替え
				break;
			}

		}

		if (player.hp <= 0)
		{
			game_state.state = S_SCENE::F_TRANSITION; // ゲーム終了状態へ移行
		}

		// 無敵状態の処理
		if (player.damege_invincible == true)
		{
			player.invincible_time++;
			if (player.invincible_time % 30 == 0)
			{
				player.color.w = 0.5; // 点滅のために透明にする
			}
			else if (player.invincible_time % 15 == 0)
			{
				player.color.w = 1; // 点滅のために不透明にする
			}
			if (player.invincible_time >= PLAYER_MAX_INVINCIBLE_TIME * 60)
			{
				player.color.w = 1;
				player.damege_invincible = false; // 無敵が終了
				player.invincible_time = 0;
			}
		}

		// 底面に達した場合の処理
		if (player.position.y >= 720)
		{
			player.strat_position.x = player.position.x; // リセット位置を設定
			player.strat_position.y = 300;
			returnplayer(); // プレイヤーをリスポーン
			player.player_time = 0;
			player.hp -= 2; // 落下ダメージ
			player.damege_invincible = true; // 無敵状態に

			sound::play(XWB_SOUNDS, XWB_SOUND_HIT); // 被弾音を再生
		}

		// デバッグ情報を出力
		debug::setString("player.hp:%d", player.hp);
		break;
	}
}

//--------------------------------------
//  プレイヤーの描画処理
//--------------------------------------
void player_render()
{
	// プレイヤーの位置に円を描画（デバッグ用）
	/*primitive::circle(player.position.x, player.position.y, 10, 1, 1, 0, 1, 0, 1); */

	if (player.position.x >= SCREEN_H - 50 && player.position.y <= 0 + 90)
	{
		primitive::line(player.position.x - 23, player.position.y + 34, player.position.x - 5, player.position.y, 0.5, 0.5, 0.5, 1, 2);
	}
	else if (player.position.x >= SCREEN_H - 50)
	{
		primitive::line(player.position.x - 65, player.position.y - 32, player.position.x - 5, player.position.y, 0.5, 0.5, 0.5, 1, 2);
	}
	else if (player.position.y <= 0 + 80)
	{
		primitive::line(player.position.x + 15, player.position.y + 34, player.position.x - 5, player.position.y, 0.5, 0.5, 0.5, 1, 2);
	}
	else
	{
		primitive::line(player.position.x + 15, player.position.y - 32, player.position.x - 5, player.position.y, 0.5, 0.5, 0.5, 1, 2);
	}

	// 爆弾の最大爆発範囲を描画
	if (STATE(0) & L_CLICK && click_time && bomb.bomb_state == 0)
	{
		primitive::circle(player.position.x, player.position.y, BOMB_BLAST_MAX_INIT_RANGE + (click_time * 5), 1, 1, 0, 0.0f, 0.2f, 0.4f, 0.2f);
	}

	// プレイヤーのスプライトを描画
	sprite_render(sprPLAYER,
		player.position.x, player.position.y,
		0.3f, 0.3f,
		0, 0,
		128, 128,
		64, 64,
		LaunchCalculateRotation(ToRadian(player.angle), force, player.player_time),
		1, 1, 1, player.color.w);

	for (int i = 0; i < 120; i++)
	{
		primitive::circle(edge_reflecting(
			player.position + LaunchCalculatePosition(
				-tracking(
					cursor_position(
					), player.position
				), bomb.bomb_speed, i * 0.5f
			)
		).x,
			edge_reflecting(player.position + LaunchCalculatePosition(-tracking(cursor_position(), player.position), bomb.bomb_speed, i * 0.5f)).y,
			3,
			1, 1,
			0,
			1, 1, 1, 0.5f);
	}

	// 力の値をデバッグ出力
	debug::setString("force%f", force);

	float r = HPColor(player.hp).x;
	float g = HPColor(player.hp).y;
	float b = HPColor(player.hp).z;

	//プレイヤーの体力表示
	if (player.position.x >= SCREEN_H - 50 && player.position.y <= 0 + 90)
	{
		primitive::rect(player.position.x - 69, player.position.y + 33, 42, 9, 0, 0, 0, 0.5, 0.5, 0.5);
		primitive::rect(player.position.x - 65, player.position.y + 35, 35 * player.hp * 0.1, 5, 0, 0, 0, r, g, b);
	}
	else if (player.position.x >= SCREEN_H - 50)
	{
		primitive::rect(player.position.x - 69, player.position.y - 35, 42, 9, 0, 0, 0, 0.5, 0.5, 0.5);
		primitive::rect(player.position.x - 65, player.position.y - 33, 35 * player.hp * 0.1, 5, 0, 0, 0, r, g, b);
	}
	else if (player.position.y <= 0 + 80)
	{
		primitive::rect(player.position.x + 15, player.position.y + 33, 42, 9, 0, 0, 0, 0.5, 0.5, 0.5);
		primitive::rect(player.position.x + 19, player.position.y + 35, 35 * player.hp * 0.1, 5, 0, 0, 0, r, g, b);
	}
	else
	{
		primitive::rect(player.position.x + 15, player.position.y - 35, 42, 9, 0, 0, 0, 0.5, 0.5, 0.5);
		primitive::rect(player.position.x + 19, player.position.y - 33, 35 * player.hp * 0.1, 5, 0, 0, 0, r, g, b);
	}
}



//--------------------------------------
//  プレイヤーの行動処理
//--------------------------------------
void player_act(PLAYER& player)
{
	if (STATE(0) & L_CLICK && click_time <= BOMB_MAX_CHARGE)
	{
		click_time += 0.2; // クリックでチャージ増加
	}

	if (bomb.bomb_state == 0)
	{
		if (TRG_RELEASE(0) & L_CLICK) // クリックを離したとき
		{
			bomb_throw(click_time, player.bomb_reinforce_item, player.position); // 爆弾を投げる
			click_time = 0; // チャージをリセット
			bomb.bomb_state = 1; // 爆弾状態を進める
		}
	}
	else if (bomb.bomb_state == 2)
	{
		if (TRG(0) & L_CLICK) // クリックしたとき
		{
			sound::play(XWB_SOUNDS, XWB_SOUND_BOMB); // 爆弾音を再生
			bomb_expansion(player); // 爆弾を膨張させる
			bomb.bomb_state = -1; // 状態をリセット
		}
	}
	else if (TRG_RELEASE(0) & L_CLICK && bomb.bomb_state == -1)
	{
		bomb.bomb_state = 0; // 爆弾の初期状態に戻す
	}
}

//--------------------------------------
//  プレイヤーの移動処理
//--------------------------------------
void player_movement(PLAYER& player, float angle, float force)
{
	player.position = player.strat_position + LaunchCalculatePosition(angle, force, player.player_time, PLAYER_GRAVITY); // 移動計算
	player.position = edge_reflecting(player.position); // 壁での反射処理
	if (player.position.y < 18)
	{
		::angle = ToRadian(-90);
		::force *= 0.5f;
		player.player_time = 0;
		player.strat_position = { player.position.x, 18 };
		player.position = player.strat_position + LaunchCalculatePosition(angle, force, player.player_time, PLAYER_GRAVITY); // 移動計算
		//force *= 0.5;
	}
}

VECTOR3 HPColor(int HP)
{
	if (HP < 3)
	{
		return VECTOR3(1.0, 0, 0);
	}
	else if (HP < 5)
	{
		return VECTOR3(1.0, 1.0, 0);
	}
	else
	{
		return VECTOR3(0.5, 1, 0.5);
	}
}