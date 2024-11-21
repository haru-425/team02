#pragma once
#include "../GameLib/game_lib.h"
#include "m_scene.h"
#include "audio.h"
#include "common.h"

#include <cmath>
#include <vector>


using namespace std;

extern VECTOR2 magnetic_force;

//trackingpersonがtargetを向いた時の角度を返す関数
float tracking(VECTOR2 target, VECTOR2 tracking_person);
//ベクトルを単位ベクトル化
VECTOR2 unit_vectorization(VECTOR2 vec);

//初速と角度をと今の時間を渡すとその時の位置を返す
VECTOR2 LaunchCalculatePosition(float angle, float force, float time);
VECTOR2 LaunchCalculatePosition(float angle, float force, float time, float gravity);

float LaunchCalculateRotation(float angle, float force, float time);
float LaunchCalculateRotation(float angle, float force, float time, float gravity);

VECTOR2 magnetic_force_suction(VECTOR2 target_BasePos, VECTOR2 magnetic_force);

VECTOR2 cursor_position();

VECTOR2 edge_reflecting(VECTOR2 pos);


//回転する矩形との当たり判定

bool intersectRectCircle(VECTOR2 rec_center, VECTOR2 size, float angle, VECTOR2 cir_center, float radius);//回転する矩形と矩形の当たり判定

bool isColliding(VECTOR2 _center, VECTOR2  _size, VECTOR2 rot_center, VECTOR2  rot_size, float angle);
//--------------------------------------------------------------
// 扇形ポリゴン描画
//--------------------------------------------------------------
//VECTOR2 center		中心点
//float	  radius		半径
//float	  startAngle	開始角度(Degree)
//float	  endAngle	終了角度(Degree)
//int	  polygon	円の分割数
//VECTOR4  color		色 (r, g, b, a)
//--------------------------------------------------------------
void draw_fan_triangle_quad(VECTOR2 center, float radius, float startAngle, float endAngle, int polygon, VECTOR4 color);

bool isCircleColliding(const VECTOR2 a_position, float a_radius, VECTOR2 b_position, float b_radius);
