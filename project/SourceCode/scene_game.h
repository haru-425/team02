#ifndef SCENE_GAME_H
#define SCENE_GAME_H

//******************************************************************************
//
//
//      scene_game.h
//
//
//******************************************************************************
//------< インクルード >---------------------------------------------------------
#include "../GameLib/game_lib.h"
#include "common.h"
#include "audio.h"
#include "m_scene.h"
#include "system.h"
#include "score.h"
#include "player.h"
#include "enemy.h"
#include "bomb.h"
#include"item.h"

// namespace
using namespace GameLib;
using namespace input;



 //------< 変数 >----------------------------------------------------------------
 //
extern int LIMIT_TIME;
//------< クラス・構造体 >-------------------------------------------------------
//------< 定数 >----------------------------------------------------------------
#define LIMT_TIME_MAX (60*60)

//------< 関数 >----------------------------------------------------------------
// 関数のプロトタイプ宣言
void game_init();
void game_deinit();
void game_update();
void game_render();

#endif//SCENE_GAME_H
