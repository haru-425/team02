#pragma once
#include "../GameLib/game_lib.h"
#include <vector>
#include"system.h"
//------< 定数 >----------------------------------------------------------------
#define ITEM_TEX_W        (128.0f)   // プレイヤーの画像1つの幅
#define ITEM_TEX_H        (128.0f)   // プレイヤーの画像1つの高さ
#define ITEM_PIVOT_X      (ITEM_TEX_W/2)    // プレイヤーの横方向の中心
#define ITEM_PIVOT_Y      (ITEM_TEX_H/2)   // プレイヤーの縦方向の下端

#define ITEM_SPEED		(5)
#define E_SCALE	(1.0f)
#define ITEM_CD 1
//------< 構造体 >---------------------------------------------------------------
enum class ITEM_TYPE {
	LimitTimeExtended		/*制限時間延長*/,
	HPRecovery				/*HP回復*/,
	ExplosionRangeCloseUp	/*爆発範囲拡大*/,
	TopEnemyInvalid			/*上の敵からの弾が降ってこなくなる*/,
	ScoreTwoTimes			/*スコア二倍*/
};
class ITEM {
private:
public:
	float timer;
	ITEM_TYPE type;
	float angle;
	float speed;
	VECTOR2 BasePosition;
	VECTOR2 position;
	VECTOR2 scale;
	VECTOR2 texPos;
	VECTOR2 texSize;
	VECTOR2 pivot;
	VECTOR4 color;


	ITEM(VECTOR2 pos, ITEM_TYPE _type, float _time) {
		timer = _time;
		BasePosition = pos;
		type = _type;
		angle = -180;
		scale = { 1 ,1 };
		texPos = { int(type) * ITEM_TEX_W, 0 };
		texSize = { ITEM_TEX_W, ITEM_TEX_H };
		pivot = { ITEM_PIVOT_X, ITEM_PIVOT_Y };
		color = { 1.000f, 1.0f, 1.0f, 1.0f };
		speed = 0;
	}


};
//------< 変数 >----------------------------------------------------------------
extern enum class ITEM_TYPE;

//------< プロトタイプ宣言 >-----------------------------------------------------
void item_init();
void item_update();
void item_render();
void item_deinit();
void item_act();
void item_spawn(VECTOR2 _pos, ITEM_TYPE _type);
void item_spawn(VECTOR2 _pos, ITEM_TYPE _type, float _time);
