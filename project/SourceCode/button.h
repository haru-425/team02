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
    VECTOR4 color;      //ボタンの色
    bool enabled;       // ボタンが有効かどうか

    void tutorial_next_button_set();
    void tutorial_buck_button_set();
    void bgm_volume_Up_init();
    void bgm_volume_Down_init();
    void se_volume_Up_init();
    void se_volume_Down_init();

    bool rect_click(Button button_info);
};