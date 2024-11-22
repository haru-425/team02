#pragma once
#include "../GameLib/game_lib.h"
#include "common.h"

class Button
{
public:

    VECTOR2 position;   // ボタンの位置
    VECTOR2 scale;      // ボタンのサイズ
    VECTOR2 texPos;     // テクスチャの位置
    VECTOR2 texSize;    // テクスチャのサイズ
    VECTOR2 pivot;      // ピボットポイント
    bool enabled;       // ボタンが有効かどうか

    void tutorial_next_button_set();
    bool rect_click(Button button_info);
};