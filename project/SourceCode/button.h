#pragma once
#include "../GameLib/game_lib.h"
#include "common.h"

class Button
{
public:

    VECTOR2 position;   // �{�^���̈ʒu
    VECTOR2 scale;      // �{�^���̃T�C�Y
    VECTOR2 texPos;     // �e�N�X�`���̈ʒu
    VECTOR2 texSize;    // �e�N�X�`���̃T�C�Y
    VECTOR4 color;      //�{�^���̐F
    bool enabled;       // �{�^�����L�����ǂ���

    void tutorial_next_button_set();
    void tutorial_buck_button_set();
    void bgm_volume_Up_init();
    void bgm_volume_Down_init();
    void se_volume_Up_init();
    void se_volume_Down_init();

    bool rect_click(Button button_info);
};