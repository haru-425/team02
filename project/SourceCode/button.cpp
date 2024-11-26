#include "button.h"

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

void Button::tutorial_next_button_set()
{
	position = { 1080, 660 };
	scale = { 1,1 };
	texPos={50,20};
	texSize = { 100, 40 };
	enabled = true;

}

void Button::tutorial_buck_button_set()
{
	position;
	scale;
	texPos;
	texSize;
	enabled = true;

}

void Button::bgm_volume_Down_init()
{
	position = { 1027, 390 };
	scale = { 0.3f, 0.2f };
	texPos = { 0, 0 };
	texSize = { 400, 400 };
	color = { 1.0f, 1.0f, 1.0f, 1.0f };
}
void Button::bgm_volume_Up_init()
{
	position = { 1513, 390 };  // 中心位置
	scale = { 0.3f, 0.2f };
	texPos = { 0, 0 };
	texSize = { 400, 400 };
	color = { 1.0f, 1.0f, 1.0f, 1.0f };
}
void Button::se_volume_Down_init()
{
	position = { 1027, 590 };  // 中心位置
	scale = { 0.3f, 0.2f };
	texPos = { 0, 0 };
	texSize = { 400, 400 };
	color = { 1.0f, 1.0f, 1.0f, 1.0f };
}
void Button::se_volume_Up_init()
{
	position = { 1513, 590 };  // 中心位置
	scale = { 0.3f, 0.2f };
	texPos = { 0, 0 };
	texSize = { 400, 400 };
	color = { 1.0f, 1.0f, 1.0f, 1.0f };
}