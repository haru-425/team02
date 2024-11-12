#include "bomb.h"
#include "player.h"
#include "system.h"

#include "common.h"

Bomb bomb;
extern PLAYER player;
POINT point;
POINT screenPoint;
float force = 0.0f;
float angle = 0.0f;
float flepX = 0.0f;
float flepY = 0.0f;
void bomb_init()
{
	bomb.bomb_state = 0;
	bomb.bomb_position.x = -100;
	bomb.bomb_position.y = -100;
	bomb.bomb_speed = 0.0f;
	bomb.bomb_angle = 0.0f;
	bomb.bom_time=0;
	bomb.bomb_blast = 0.0f;
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

	 //マウスカーソルの現在位置を取得
	GetCursorPos(&point);

	// スクリーン座標をクライアント座標に変換
	ScreenToClient(window::getHwnd(), &point);

	VECTOR2 Point = { (float)point.x, (float)point.y };
	bomb.bomb_angle = tracking(Point, player.position);


	bomb.bomb_speed = 50.0f;

	bomb.bomb_state++;
}

void bomb_update()
{
	debug::setString("%f", bomb.start_bomb_position.x);
	switch (bomb.bomb_state)
	{
	case 3:
		flepX = player.position.x - bomb.bomb_position.x;
		flepY = player.position.y - bomb.bomb_position.y;
		force = sqrtf(flepX * flepX + flepY * flepY) - BOMB_BLAST_STRANGE;
		angle = tracking(player.position, bomb.bomb_position);
		bomb_deinit();
		break;

	case 1:
		bomb.bom_time = 0.0f;
		bomb.bomb_state++;

	case 2:

		bomb.bom_time += 0.1f;
		bomb.bomb_position = bomb.start_bomb_position + LaunchCalculatePosition(ToDegree(-bomb.bomb_angle), bomb.bomb_speed, bomb.bom_time);

		if (bomb.bomb_position.y >= SCREEN_H)
		{
			bomb_deinit();
		}
	default:

		player_movement(angle, force);
		return;

		break;
	}

}

void bomb_render()
{
	primitive::circle(bomb.bomb_position.x, bomb.bomb_position.y, 10, 1, 1);
}
