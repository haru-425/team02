#ifndef COMMON_H
#define COMMON_H

#include "../GameLib/game_lib.h"
using namespace GameLib;

//  �萔
extern const FLOAT PI;
extern const LONG SCREEN_W;
extern const LONG SCREEN_H;
extern const BOOL FULLSCREEN;
extern const LPCWSTR APPLICATION_NAME;

//const double GRAVITY = 9.81; // �d�͉����x (m/s^2)
const double GRAVITY = 100; // �d�͉����x (m/s^2)
//  �֐��|�C���^
extern float(* const ToRadian)(float);// �p�x�����W�A����
extern float(* const ToDegree)(float);// ���W�A�����p�x��
#endif // !COMMON_H
