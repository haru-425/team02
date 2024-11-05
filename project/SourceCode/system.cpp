//------< インクルード >---------------------------------------------------------
#include "../GameLib/game_lib.h"
#include "m_scene.h"
#include "audio.h"
#include "common.h"
#include "system.h"


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
VECTOR2 unit_vectorization(VECTOR2 vec) {
	float length = std::sqrtf(powf(vec.x, 2) + powf(vec.y, 2));
	return vec;
}
