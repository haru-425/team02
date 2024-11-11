#pragma once

extern VECTOR2 magnetic_force;

//trackingpersonがtargetを向いた時の角度を返す関数
float tracking(VECTOR2 target, VECTOR2 tracking_person);
//ベクトルを単位ベクトル化
VECTOR2 unit_vectorization(VECTOR2 vec);

//初速と角度をと今の時間を渡すとその時の位置を返す
VECTOR2 LaunchCalculatePosition(float angle, float force, float time);
VECTOR2 LaunchCalculatePosition(float angle, float force, float time, float gravity);

VECTOR2 magnetic_force_suction(VECTOR2 target_BasePos, VECTOR2 magnetic_force);

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
