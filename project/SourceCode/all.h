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
#include "m_scene.h"
// namespace
using namespace GameLib;
using namespace input;
#endif//ALL_H
