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
	// マウスカーソルの座標取得
	POINT nextpoint;
	GetCursorPos(&nextpoint);
	ScreenToClient(window::getHwnd(), &nextpoint);
	// ボタンの四辺を取得
	float button_right = button_info.position.x + button_info.texSize.x * button_info.scale.x / 2;
	float button_left = button_info.position.x - button_info.texSize.x * button_info.scale.x / 2;
	float button_top = button_info.position.y - button_info.texSize.y * button_info.scale.y / 2;
	float button_bottom = button_info.position.y + button_info.texSize.y * button_info.scale.y / 2;

	// マウスの座標がボタンの範囲内かチェック
	bool isWithinX = (nextpoint.x >= button_left && nextpoint.x <= button_right);
	bool isWithinY = (nextpoint.y >= button_top && nextpoint.y <= button_bottom);

	// マウスがボタン範囲内ならクリックされたと判定
	return isWithinX && isWithinY;
}