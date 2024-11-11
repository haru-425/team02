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
// namespace
using namespace GameLib;
using namespace input;

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

}
void game_update()
{
	switch (game_state.state)
	{
	case game_state.INITIALIZE:
		game_state.state = game_state.B_TRANSIATON;
		player_init();
		enemy_init();
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
}
