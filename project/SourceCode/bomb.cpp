#include "bomb.h"
#include "player.h"
#include "system.h"

#include "common.h"

Bomb bomb;
extern PLAYER player;
POINT point;
POINT screenPoint;

void bomb_init()
{
	bomb.bomb_state = 0;
	bomb.bomb_position.x = -100;
	bomb.bomb_position.y = -100;
	bomb.bomb_speed = 0.0f;
	bomb.bomb_angle = 0;
	bomb.bom_time=0;
}

void bomb_deinit()
{
	bomb.bomb_state = 0;
	bomb.bomb_position.x = -100;
	bomb.bomb_position.y = -100;
	bomb.bomb_speed = 0.0f;
	bomb.bomb_angle = 0.0f;
	bomb.bom_time = 0;
}

void bomb_throw()
{

	bomb.start_bomb_position = player.position;


	// マウスカーソルの現在位置を取得
	GetCursorPos(&point);

	// スクリーン座標をクライアント座標に変換
	ScreenToClient(window::getHwnd(), &point);

	VECTOR2 Point = { point.x, point.y };
	bomb.bomb_angle = tracking(Point, player.position);

	bomb.bomb_state++;
}

void bomb_update()
{
	if (bomb.bomb_state!=1)
	{
		return;
	}
	bomb.bomb_position = bomb.start_bomb_position + LaunchCalculatePosition(bomb.bomb_angle, bomb.bomb_speed, bomb.bom_time);
	/*if (true)
	{
		bomb_explosion();
	}*/
	if (bomb.bomb_position.y == SCREEN_H)
	{
		void bomb_deinit();
	}

}

void bomb_explosion()
{
	float flepX = player.position.x - bomb.bomb_position.x;
	float flepY = player.position.y - bomb.bomb_position.y;
	
}

void bomb_render()
{
	primitive::circle(bomb.bomb_position.x, bomb.bomb_position.y, 1, 1, 1);
}
