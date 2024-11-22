#pragma once
#include "../GameLib/game_lib.h"
#include "audio.h"
#include "common.h"
#include <cmath>
#include <vector>

using namespace std;

extern VECTOR2 magnetic_force;

//----------------------------
// 指定したターゲットを向いた際の角度を返す関数
// target: 追従すべきターゲットの座標
// tracking_person: 角度を計算する対象の座標
//----------------------------
float tracking(VECTOR2 target, VECTOR2 tracking_person);

//----------------------------
// ベクトルを単位ベクトル化する関数
// vec: 単位ベクトル化する対象のベクトル
// 戻り値: 正規化された単位ベクトル
//----------------------------
VECTOR2 unit_vectorization(VECTOR2 vec);

//----------------------------
// 投射物の初速、角度、時間を基に現在の位置を計算する関数
// angle: 投射角度 (ラジアン)
// force: 投射速度
// time: 経過時間
// 戻り値: 現在の位置座標
//----------------------------
VECTOR2 LaunchCalculatePosition(float angle, float force, float time);

//----------------------------
// 投射物の初速、角度、時間、重力を基に現在の位置を計算する関数
// angle: 投射角度 (ラジアン)
// force: 投射速度
// time: 経過時間
// gravity: 重力加速度
// 戻り値: 現在の位置座標
//----------------------------
VECTOR2 LaunchCalculatePosition(float angle, float force, float time, float gravity);

//----------------------------
// 投射物の初速、角度、時間を基に現在の回転角度を計算する関数
// angle: 投射角度 (ラジアン)
// force: 投射速度
// time: 経過時間
// 戻り値: 現在の回転角度
//----------------------------
float LaunchCalculateRotation(float angle, float force, float time);

//----------------------------
// 投射物の初速、角度、時間、重力を基に現在の回転角度を計算する関数
// angle: 投射角度 (ラジアン)
// force: 投射速度
// time: 経過時間
// gravity: 重力加速度
// 戻り値: 現在の回転角度
//----------------------------
float LaunchCalculateRotation(float angle, float force, float time, float gravity);

//----------------------------
// 磁力によってターゲットの座標を吸引する関数
// target_BasePos: 対象物の現在座標
// magnetic_force: 磁力の強さを表すベクトル
// 戻り値: 磁力の影響を受けた新しい座標
//----------------------------
VECTOR2 magnetic_force_suction(VECTOR2 target_BasePos, VECTOR2 magnetic_force);

//----------------------------
// 現在のカーソル位置を取得する関数
// 戻り値: カーソルの座標
//----------------------------
VECTOR2 cursor_position();

//----------------------------
// オブジェクトが画面端に達したときの反射処理を行う関数
// pos: オブジェクトの現在位置
// 戻り値: 反射後の位置
//----------------------------
VECTOR2 edge_reflecting(VECTOR2 pos);

//----------------------------
// 回転する矩形と円の当たり判定を行う関数
// rec_center: 矩形の中心座標
// size: 矩形の幅と高さ
// angle: 矩形の回転角度 (ラジアン)
// cir_center: 円の中心座標
// radius: 円の半径
// 戻り値: 当たり判定があるかどうか (true/false)
//----------------------------
bool intersectRectCircle(VECTOR2 rec_center, VECTOR2 size, float angle, VECTOR2 cir_center, float radius);

//----------------------------
// 回転する矩形と矩形の当たり判定を行う関数
// _center: 回転していない矩形の中心座標
// _size: 回転していない矩形の幅と高さ
// rot_center: 回転する矩形の中心座標
// rot_size: 回転する矩形の幅と高さ
// angle: 回転する矩形の回転角度 (ラジアン)
// 戻り値: 当たり判定があるかどうか (true/false)
//----------------------------
bool isColliding(VECTOR2 _center, VECTOR2 _size, VECTOR2 rot_center, VECTOR2 rot_size, float angle);

//--------------------------------------------------------------
// 扇形のポリゴンを描画する関数
// center: 扇形の中心座標
// radius: 扇形の半径
// startAngle: 扇形の開始角度 (度)
// endAngle: 扇形の終了角度 (度)
// polygon: 円を構成するポリゴンの分割数
// color: 扇形の色 (r, g, b, a)
//--------------------------------------------------------------
void draw_fan_triangle_quad(VECTOR2 center, float radius, float startAngle, float endAngle, int polygon, VECTOR4 color);

//----------------------------
// 円と円の当たり判定を行う関数
// a_position: 円Aの中心座標
// a_radius: 円Aの半径
// b_position: 円Bの中心座標
// b_radius: 円Bの半径
// 戻り値: 当たり判定があるかどうか (true/false)
//----------------------------
bool isCircleColliding(const VECTOR2 a_position, float a_radius, VECTOR2 b_position, float b_radius);
