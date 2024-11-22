#pragma once
#include "../GameLib/game_lib.h"
#include"system.h"
#include "m_scene.h"

extern float SCORE_DIAMETER;
extern int score;
//------< プロトタイプ宣言 >-----------------------------------------------------
void score_init();
void score_update();
void score_render();
void score_deinit();
void score_act();
void score_set(int _score);
void score_add(int _score);
void score_diameter_set(int _diameter, int _time);