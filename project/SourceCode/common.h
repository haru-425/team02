#ifndef COMMON_H
#define COMMON_H

#include "../GameLib/game_lib.h"
using namespace GameLib;

//  定数
extern const FLOAT PI;
extern const LONG SCREEN_W;
extern const LONG SCREEN_H;
extern const BOOL FULLSCREEN;
extern const LPCWSTR APPLICATION_NAME;

//const double GRAVITY = 9.81; // 重力加速度 (m/s^2)
const double GRAVITY = 100; // 重力加速度 (m/s^2)
//  関数ポインタ
extern float(* const ToRadian)(float);// 角度をラジアンに
extern float(* const ToDegree)(float);// ラジアンを角度に
#endif // !COMMON_H
