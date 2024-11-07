#pragma once
//trackingpersonがtargetを向いた時の角度を返す関数
float tracking(VECTOR2 target, VECTOR2 tracking_person);
//ベクトルを単位ベクトル化
VECTOR2 unit_vectorization(VECTOR2 vec);

//初速と角度をと今の時間を渡すとその時の位置を返す
VECTOR2 LaunchCalculatePosition(float angle, float force, float time);