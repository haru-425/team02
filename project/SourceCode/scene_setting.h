#pragma once

//******************************************************************************
//
//
//      scene_title.h
//
//
//******************************************************************************
//------< インクルード >---------------------------------------------------------
#include "../GameLib/game_lib.h"
#include "common.h"
#include "audio.h"
#include "m_scene.h"
#include "button.h"
// namespace
using namespace GameLib;
using namespace input;
//------< 変数 >----------------------------------------------------------------
//------< クラス・構造体 >-------------------------------------------------------

class Bolume
{
public:
	Bolume()
	{
		bgm_volume = 3;
		se_volume = 3;
	}

	int bgm_volume;
	int se_volume;

};
extern Bolume game_volume;
//------< 定数 >----------------------------------------------------------------



// 関数のプロトタイプ宣言

void setting_init();
void setting_deinit();
void setting_update();
void setting_render();
