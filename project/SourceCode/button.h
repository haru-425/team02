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
    bool enabled;       // �{�^�����L�����ǂ���

    void tutorial_next_button_set();
    void tutorial_buck_button_set();
    bool rect_click(Button button_info);
};