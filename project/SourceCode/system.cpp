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

// 円と円の当たり判定関数
bool isCircleColliding(const VECTOR2 a_position, float a_radius, VECTOR2 b_position, float b_radius) {
	// 中心間の距離を計算
	float dx = b_position.x - a_position.x;
	float dy = b_position.y - a_position.y;
	float distance = std::sqrt(dx * dx + dy * dy);

	// 半径の和と距離を比較
	return distance <= (a_radius + b_radius);
}


//回転する矩形と矩形の当たり判定


struct Rect {
	VECTOR2 center;
	VECTOR2 size;
};

struct RotatedRect {
	VECTOR2 center;
	VECTOR2 size;
	float angle;
};

bool intersectRectRotatedRect(VECTOR2 _center, VECTOR2  _size, VECTOR2 rot_center, VECTOR2  rot_size, float angle) {

	const Rect& rect = { _center, _size };
	const RotatedRect& rotatedRect = { rot_center, rot_size, angle };
	// 回転する矩形の頂点を取得する
	VECTOR2 vertices[4];
	vertices[0] = { rotatedRect.center.x - rotatedRect.size.x / 2, rotatedRect.center.y - rotatedRect.size.y / 2 };
	vertices[1] = { rotatedRect.center.x + rotatedRect.size.x / 2, rotatedRect.center.y - rotatedRect.size.y / 2 };
	vertices[2] = { rotatedRect.center.x + rotatedRect.size.x / 2, rotatedRect.center.y + rotatedRect.size.y / 2 };
	vertices[3] = { rotatedRect.center.x - rotatedRect.size.x / 2, rotatedRect.center.y + rotatedRect.size.y / 2 };

	// 回転行列を計算する
	float cosAngle = std::cos(rotatedRect.angle);
	float sinAngle = std::sin(rotatedRect.angle);

	// 回転する矩形の頂点を変換する
	for (int i = 0; i < 4; i++) {
		float x = vertices[i].x - rotatedRect.center.x;
		float y = vertices[i].y - rotatedRect.center.y;
		vertices[i].x = x * cosAngle - y * sinAngle + rotatedRect.center.x;
		vertices[i].y = x * sinAngle + y * cosAngle + rotatedRect.center.y;
	}

	// 当たり判定を実行する
	for (int i = 0; i < 4; i++) {
		if (rect.center.x - rect.size.x / 2 <= vertices[i].x && vertices[i].x <= rect.center.x + rect.size.x / 2 &&
			rect.center.y - rect.size.y / 2 <= vertices[i].y && vertices[i].y <= rect.center.y + rect.size.y / 2) {
			return true;
		}
	}

	return false;
}


//回転する矩形と円の当たり判定

bool intersectRectCircle(VECTOR2 rec_center, VECTOR2 size, float angle, VECTOR2 cir_center, float radius) {
	// 回転行列を計算する
	float cosAngle = std::cos(angle);
	float sinAngle = std::sin(angle);

	// 矩形の頂点を取得する
	VECTOR2 vertices[4];
	vertices[0] = { rec_center.x - size.x / 2, rec_center.y - size.y / 2 };
	vertices[1] = { rec_center.x + size.x / 2, rec_center.y - size.y / 2 };
	vertices[2] = { rec_center.x + size.x / 2, rec_center.y + size.y / 2 };
	vertices[3] = { rec_center.x - size.x / 2, rec_center.y + size.y / 2 };

	// 回転行列を使用して頂点を変換する
	for (int i = 0; i < 4; i++) {
		float x = vertices[i].x - rec_center.x;
		float y = vertices[i].y - rec_center.y;
		vertices[i].x = x * cosAngle - y * sinAngle + rec_center.x;
		vertices[i].y = x * sinAngle + y * cosAngle + rec_center.y;
	}

	// 当たり判定を実行する
	for (int i = 0; i < 4; i++) {
		VECTOR2 v = { cir_center.x - vertices[i].x, cir_center.y - vertices[i].y };
		float distance = std::sqrt(v.x * v.x + v.y * v.y);
		if (distance <= radius) {
			return true;
		}
	}

	return false;
}