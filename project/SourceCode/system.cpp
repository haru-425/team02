//------< インクルード >---------------------------------------------------------
#include "../GameLib/game_lib.h"
#include "m_scene.h"
#include "audio.h"
#include "common.h"
#include "system.h"

//AがBを向く処理
float tracking(VECTOR2 target, VECTOR2 tracking_person) {
	VECTOR2 subVector;
	float angle;

	// ターゲットと追跡者の座標差分を計算
	subVector.x = target.x - tracking_person.x;
	subVector.y = target.y - tracking_person.y;

	// 差分から角度を計算
	angle = (float)atan2(subVector.y, subVector.x);
	return angle;
}
//単位ベクトルを返す
VECTOR2 unit_vectorization(VECTOR2 vec) {
	float length = std::sqrtf(powf(vec.x, 2) + powf(vec.y, 2));
	vec.x /= length;
	vec.y /= length;
	return vec;
}
//初速と角度をと今の時間を渡すとその時の位置を返す
VECTOR2 launch_alculate_position(double initialSpeed, double angle, double time) {
	VECTOR2 position;
	time /= 10;//調整用10は仮
	double angleRad = ToRadian(angle); // 角度をラジアンに変換
	position.x = initialSpeed * cos(angleRad) * time;
	position.y = initialSpeed * sin(angleRad) * time - 0.5 * GRAVITY * time * time;
	return position;
}