#ifndef ALL_H
#define ALL_H

//******************************************************************************
//
//
//      all.h
//
//
//******************************************************************************

// システムやライブラリのヘッダーファイルは上の方へ
#include "../GameLib/game_lib.h"

// 共通で使われるようなヘッダー
#include "common.h"

// 個々のヘッダーファイルは下の方へ
#include "audio.h"
#include "scene_game.h"
#include "scene_title.h"

// namespace
using namespace GameLib;
using namespace input;
extern int curScene;
extern int nextScene;
#endif//ALL_H
