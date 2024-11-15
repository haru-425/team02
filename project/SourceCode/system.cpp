//------< インクルード >---------------------------------------------------------
#include "../GameLib/game_lib.h"
#include "m_scene.h"
#include "audio.h"
#include "common.h"
#include "system.h"


VECTOR2 magnetic_force = { 0,0 };

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
//VECTOR2 launch_alculate_position(double initialSpeed, double angle, double time) {
//	VECTOR2 position;
//	//time /= 100;//調整用10は仮
//	double angleRad = ToRadian(angle); // 角度をラジアンに変換
//	position.x = initialSpeed * cos(angleRad) * time;
//	position.y = initialSpeed * sin(angleRad) * time - 0.5 * GRAVITY * time * time;
//	return position;
//}

VECTOR2 LaunchCalculatePosition(float angle, float force, float time) {
	// 初期速度を計算
	float v0 = force;
	float vx = v0 * cos(angle);
	float vy = v0 * sin(angle);

	// 重力加速度を定義
	float g = 9.8f;

	// n秒後の位置を計算
	float x = vx * time;

	float y = vy * time - 0.5f * g * time * time;
	y *= -1;
	// 位置を返す
	return VECTOR2(x, y);
}
VECTOR2 LaunchCalculatePosition(float angle, float force, float time, float gravity)
{
	// 初期速度を計算
	float v0 = force;
	float vx = v0 * cos(angle);
	float vy = v0 * sin(angle);

	// 重力加速度を定義
	float g = gravity;

	// n秒後の位置を計算
	float x = vx * time;

	float y = vy * time - 0.5f * g * time * time;
	y *= -1;

	// 位置を返す
	return VECTOR2(x, y);
}

VECTOR2 magnetic_force_suction(VECTOR2 target_BasePos, VECTOR2 magnetic_force) {
	VECTOR2 Vec = target_BasePos;
	if (Vec.x <= 0) Vec.x += magnetic_force.x / 2.0f;

	if (Vec.x >= SCREEN_H)Vec.x -= magnetic_force.x / 2.0f;

	Vec.x += magnetic_force.x;
	Vec.y += magnetic_force.y;

	return Vec;
}

VECTOR2 edge_reflecting(VECTOR2 pos) {
	// 画面外に出た場合の処理
	if (pos.x < 0)  pos.x *= -1;
	if (pos.x > SCREEN_H) pos.x = SCREEN_H - (pos.x - SCREEN_H);
	//	if (pos.y <= 0) pos.y *= -1;
	return pos;

}
VECTOR2 cursor_position() {

	POINT point;
	//マウスカーソルの現在位置を取得
	GetCursorPos(&point);

	// スクリーン座標をクライアント座標に変換
	ScreenToClient(window::getHwnd(), &point);

	VECTOR2 Point = { (float)point.x, (float)point.y };
	return Point;
}
// 扇形ポリゴン描画
void draw_fan_triangle_quad(VECTOR2 center, float radius, float startAngle, float endAngle, int polygon, VECTOR4 color)
{
	float angleStep = (endAngle - startAngle) / polygon;
	for (int i = 0; i < polygon; i++) {
		float angle1 = ToRadian(startAngle + i * angleStep);
		float angle2 = ToRadian(startAngle + (i + 1) * angleStep);
		VECTOR2 p1 = { center.x + radius * sinf(angle1), center.y - radius * cosf(angle1) };
		VECTOR2 p2 = { center.x + radius * sinf(angle2), center.y - radius * cosf(angle2) };
		VECTOR2 vertex[4] = {
			{center.x,center.y},
			{center.x,center.y},
			{p1.x,p1.y},
			{p2.x,p2.y}
		};
		primitive::quad(vertex, color, true);
	}
}
