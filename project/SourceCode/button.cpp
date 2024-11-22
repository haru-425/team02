#include "button.h"

void Button::tutorial_next_button_set()
{
	position;
	scale;
	texPos;
	texSize;
	pivot;
	enabled=true;

}

bool Button::rect_click(Button button_info)
{
	// �}�E�X�J�[�\���̍��W�擾
	POINT nextpoint;
	GetCursorPos(&nextpoint);
	ScreenToClient(window::getHwnd(), &nextpoint);
	// �{�^���̎l�ӂ��擾
	float button_right = button_info.position.x + button_info.texSize.x * button_info.scale.x / 2;
	float button_left = button_info.position.x - button_info.texSize.x * button_info.scale.x / 2;
	float button_top = button_info.position.y - button_info.texSize.y * button_info.scale.y / 2;
	float button_bottom = button_info.position.y + button_info.texSize.y * button_info.scale.y / 2;

	// �}�E�X�̍��W���{�^���͈͓̔����`�F�b�N
	bool isWithinX = (nextpoint.x >= button_left && nextpoint.x <= button_right);
	bool isWithinY = (nextpoint.y >= button_top && nextpoint.y <= button_bottom);

	// �}�E�X���{�^���͈͓��Ȃ�N���b�N���ꂽ�Ɣ���
	return isWithinX && isWithinY;
}