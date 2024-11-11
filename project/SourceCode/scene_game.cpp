//******************************************************************************
//
//
//      scene_game
//
//
//******************************************************************************

//------< インクルード >---------------------------------------------------------
#include "../GameLib/game_lib.h"
#include "common.h"
#include "audio.h"
#include "m_scene.h"
#include "bomb.h"
#include "system.h"
// namespace
using namespace GameLib;
using namespace input;

//debug
Sprite* sprArrow;
//------< 定数 >----------------------------------------------------------------


//------< 変数 >----------------------------------------------------------------
S_SCENE game_state;
int game_timer;

void game_init()
{
	game_state.state = 0;
	game_timer = 0;

}
void game_deinit()
{
	//debug
	safe_delete(sprArrow);
}
void game_update()
{
	switch (game_state.state)
	{
	case game_state.INITIALIZE:
		game_state.state = game_state.B_TRANSIATON;
		player_init();
		enemy_init();

		//debug

		sprArrow = sprite_load(L"./Data/Images/unnamed.png");
	case game_state.B_TRANSIATON:
		if (true)
		{
			game_state.state = game_state.PARAMETER;
		}
		break;

	case game_state.PARAMETER:
		GameLib::setBlendMode(Blender::BS_ALPHA);

		game_state.state = game_state.NORMAL;

	case game_state.NORMAL:
		if (TRG(0) & PAD_SELECT)
		{
			game_state.state = game_state.F_TRANSITION;
			break;
		}





		//debug用定期磁力変更
		if (game_timer % 60 == 0) magnetic_force = { rand() % 1000 / 100.0f - 5.0f,rand() % 1000 / 1000.0f - 0.5f };
		//if (game_timer % 180 == 0) magnetic_force = { 1 ,1 };





		enemy_update();
		player_update();
		bomb_update();
		break;
	case game_state.F_TRANSITION:
		if (true)
		{
			nextScene = SCENE_TYPE::TITLE;
		}


	}

	game_timer++;
}

//--------------------------------------
//  描画処理
//--------------------------------------
void game_render()
{
	GameLib::clear(0.2f, 0.2f, 0.4f);

	enemy_render();
	bomb_render();
	player_render();
	debug::setString("game_timer%d", game_timer);
	debug::setString("game_state%d", game_state.state);
	debug::setString("magnet(%f:%f)", magnetic_force.x, magnetic_force.y);

	if (magnetic_force.x == 0 && magnetic_force.y == 0)
	{

	}
	else {
		sprite_render(
			sprArrow,
			SCREEN_H + ((SCREEN_W - SCREEN_H) / 2.0f), SCREEN_H / 2.0f,
			0.1f, 0.1f,
			0, 0,
			2067, 1646,
			1033.5f, 823,
			(float)atan2(magnetic_force.y, magnetic_force.x)
		);
	}


}
