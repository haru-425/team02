#include "bomb.h"

Bomb bomb; // 爆弾管理用のグローバル変数
extern PLAYER player; // プレイヤー情報（外部で定義）
POINT screenPoint; // スクリーン座標用の変数
extern float force; // 爆発力（外部で定義）
extern float angle; // 爆発角度（外部で定義）
float flepX = 0.0f; // 爆弾とプレイヤー間のX軸距離
float flepY = 0.0f; // 爆弾とプレイヤー間のY軸距離
std::vector<Bomb_range> range_Box; // 爆風範囲のリスト
float blast_max_range = 0; // 爆風の最大範囲
extern int tutorial_progress; // チュートリアル進行状況（外部で定義）
Sprite* sprBOMB; // 爆弾のスプライトデータ

//--------------------------------------
// 爆弾の初期化
//--------------------------------------
void bomb_init()
{
    bomb.bomb_state = 0; // 爆弾状態を初期化
    bomb.start_bomb_position = player.position; // 爆弾の開始位置をプレイヤー位置に設定
    bomb.bomb_position.x = -200; // 爆弾の初期位置（非表示）
    bomb.bomb_position.y = -200; // 同上
    bomb.bomb_speed = 50.0f; // 初期速度を設定
    bomb.bomb_angle = 0.0f; // 初期角度を設定
    bomb.bom_time = 0; // 爆弾の経過時間を初期化
    bomb.bomb_blast = 0.0f; // 爆風の範囲を初期化
}

//--------------------------------------
// 爆弾の終了処理
//--------------------------------------
void bomb_deinit()
{
    bomb.bomb_state = 0; // 状態をリセット
    bomb.bomb_position.x = -100; // 非表示状態に戻す
    bomb.bomb_position.y = -100;
    bomb.bomb_speed = 50.0f; // 速度を初期化
    bomb.bomb_angle = 0.0f; // 角度を初期化
    bomb.bom_time = 0; // 時間を初期化
    safe_delete(sprBOMB); // スプライトデータを削除
}

//--------------------------------------
// 爆弾を投げる処理
//--------------------------------------
void bomb_throw(float muster_up, int bomb_up, VECTOR2 position)
{
    bomb.start_bomb_position = position; // 爆弾の開始位置を設定

    VECTOR2 Point = cursor_position(); // マウスカーソル位置を取得
    bomb.bomb_angle = tracking(Point, position); // プレイヤー位置からカーソル位置への角度を計算

    // 爆風の最大範囲を計算
    blast_max_range = BOMB_BLAST_MAX_INIT_RANGE + (muster_up * 5) + (float)(bomb_up * 8);

    bomb.bomb_state++; // 状態を更新（投げる準備完了）
}

//--------------------------------------
// 爆弾の爆風による処理
//--------------------------------------
void bomb_expansion(PLAYER& player)
{
    // プレイヤーと爆弾間の距離を計算
    flepX = player.position.x - bomb.bomb_position.x;
    flepY = player.position.y - bomb.bomb_position.y;

    // 爆風範囲内にプレイヤーがいる場合
    if (blast_max_range - sqrtf(flepX * flepX + flepY * flepY) > 0)
    {
        player.player_time = 0; // プレイヤーの行動時間をリセット
        player.strat_position = player.position; // 現在位置を新たなスタート位置に
        force = (blast_max_range - sqrtf(flepX * flepX + flepY * flepY)) * BOMB_BLAST_STRANGE; // 爆風による力を計算
        angle = -tracking(player.position, bomb.bomb_position); // 爆風方向の角度を計算
    }

    range_Box.push_back(bomb.bomb_position); // 爆風範囲をリストに追加
    bomb_deinit(); // 爆弾を終了状態にする
}

//--------------------------------------
// 爆弾の更新処理
//--------------------------------------
void bomb_update(PLAYER& player)
{
    debug::setString("bomb_blast_max_range:%f", blast_max_range); // デバッグ情報を出力
    debug::setString("bomb_state:%d", bomb.bomb_state);

    switch (bomb.bomb_state)
    {
    case 1: // 爆弾が投げられた直後
        sprBOMB = sprite_load(L"./Data/Images/Bomb/bomb.png"); // スプライトを読み込む
        bomb.bom_time = 0.0f; // 時間をリセット
        bomb.bomb_state++; // 状態を更新
        /*fallthrough*/

    case 2: // 爆弾が移動中
        bomb.bom_time += 0.1f; // 経過時間を更新
        bomb.bomb_position = bomb.start_bomb_position + LaunchCalculatePosition(-bomb.bomb_angle, bomb.bomb_speed, bomb.bom_time); // 新しい位置を計算

        bomb.bomb_position = edge_reflecting(bomb.bomb_position); // 壁に当たったら反射

        if (bomb.bomb_position.y >= SCREEN_H) // 底面に到達した場合
        {
            bomb_deinit(); // 爆弾をリセット
        }

    default:
        // 爆風範囲を拡大
        for (auto& renge : range_Box)
        {
            renge.bomb_range_expansion();
        }

        // 範囲が最大に達した爆風を削除
        auto it = std::remove_if(range_Box.begin(), range_Box.end(),
            [](const Bomb_range& renge) { return renge.bomb_blast_range >= renge.bomb_blast_max_range; });
        range_Box.erase(it, range_Box.end());

        // チュートリアル中でない場合、プレイヤーを移動
        if (tutorial_progress != 1)
        {
            player_movement(player, angle, force + BOMB_ADJUSTMENT);
        }
        return; // 処理終了
    }
}

//--------------------------------------
// 爆弾の描画処理
//--------------------------------------
void bomb_render()
{
    // 爆風範囲を描画
    for (auto& range : range_Box) {
        primitive::circle(range.judg_position.x, range.judg_position.y, range.bomb_blast_max_range, range.bomb_blast_range / range.bomb_blast_max_range, range.bomb_blast_range / range.bomb_blast_max_range, 0, 1, 0, 0, 0.2f);
    }

    // 爆弾のスプライトを描画
    primitive::circle(bomb.bomb_position.x, bomb.bomb_position.y, 10, 1, 1);
    sprite_render(sprBOMB,
        bomb.bomb_position.x, bomb.bomb_position.y,
        40.0f / 128.0f, 40.0f / 128.0f,
        0, 0,
        128, 128,
        64, 64,
        LaunchCalculateRotation(ToRadian(bomb.bomb_angle), bomb.bomb_speed, bomb.bom_time)
    );
}

//--------------------------------------
// プレイヤーのリセット
//--------------------------------------
void returnplayer()
{
    force = 0; // 力をリセット
    angle = 0; // 角度をリセット
}


Bomb_range::Bomb_range(VECTOR2 position) :judg_position(position)
{
	bomb_blast_range = 0;
	this->bomb_blast_max_range = blast_max_range;
	player_launch = false;
}

Bomb_range::~Bomb_range()
{
}

void Bomb_range::bomb_range_expansion()
{
	bomb_blast_range += BOMB_BLAST_R_INC;
	/*if (sqrtf(flepX * flepX + flepY * flepY) - bomb_blast_range <= 0 && player_launch == false)
	{
		player.player_time = 0;
		player.strat_position = player.position;
		force = (BOMB_BLAST_MAX_RANGE - sqrtf(flepX * flepX + flepY * flepY)) * BOMB_BLAST_STRANGE;
		angle = tracking(player.position, bomb.start_bomb_position);
		player_launch = true;
	}
	if (bomb_blast_range >= BOMB_BLAST_MAX_RANGE)
	{
		player_launch = false;
	}*/
	enemy_kill(bomb_blast_range, judg_position);

}
