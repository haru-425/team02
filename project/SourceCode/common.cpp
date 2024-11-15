#include "common.h"

//  定数
const FLOAT PI{ DirectX::XM_PI };
const LONG SCREEN_W{ 1280 };
//const LONG SCREEN_W{ 1792 };
const LONG SCREEN_H{ 720 };

const LONG GAME_SCREEN_H{ 720 };
const LONG GAME_SCREEN_W{ 720 };
//const LONG SCREEN_H{ 1008 };
const BOOL FULLSCREEN{ TRUE };
const LPCWSTR APPLICATION_NAME{ L"C++ project template" };

//  関数ポインタ
float(* const ToRadian)(float) = DirectX::XMConvertToRadians;  // 角度をラジアンに
float(* const ToDegree)(float) = DirectX::XMConvertToDegrees;  // ラジアンを角度に
