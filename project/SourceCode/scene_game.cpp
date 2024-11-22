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
#include "system.h"
#include "score.h"
// namespace
using namespace GameLib;
using namespace input;

//debug
Sprite* sprArrow;

Sprite* sprBG_GAME;
Sprite* sprFRAME_GAME;
//------< 定数 >----------------------------------------------------------------


//------< 変数 >----------------------------------------------------------------
S_SCENE game_state;
int game_timer;

int LIMIT_TIME;

void game_init()
{
	game_state.state = 0;
	game_timer = 0;

}
void game_deinit()
{
	//debug
	safe_delete(sprArrow);
	safe_delete(sprBG_GAME);
	safe_delete(sprFRAME_GAME);
	enemy_deinit();
	player_deinit();
	bomb_deinit();
	item_deinit();
	score_deinit();
}
void game_update()
{
	switch (game_state.state)
	{
	case game_state.INITIALIZE:
		game_state.state = game_state.B_TRANSIATON;
		player_init();
		enemy_init();
		bomb_init();
		item_init();

		score_init();
		score_set(0);
		//debug

		sprArrow = sprite_load(L"./Data/Images/unnamed.png");
		sprBG_GAME = sprite_load(L"./Data/Images/BG/game.png");
		sprFRAME_GAME = sprite_load(L"./Data/Images/BG/frame.png");
	case game_state.B_TRANSIATON:
		if (true)
		{
			game_state.state = game_state.PARAMETER;
		}
		break;

	case game_state.PARAMETER:
		GameLib::setBlendMode(Blender::BS_ALPHA);

		game_state.state = game_state.NORMAL;
		LIMIT_TIME = LIMT_TIME_MAX;

	case game_state.NORMAL:
		if (TRG(0) & PAD_SELECT)
		{
			game_state.state = game_state.F_TRANSITION;
			break;
		}





		//debug用定期磁力変更
		if (game_timer % 1200 == 0) magnetic_force = { rand() % 1000 / 100.0f - 5.0f,rand() % 1000 / 1000.0f - 0.5f };
		//if (game_timer % 180 == 0) magnetic_force = { 0 ,0 };



		if (LIMIT_TIME <= 0)
		{
			game_state.state = game_state.F_TRANSITION;
		}

		item_update();
		score_update();
		enemy_update();
		player_update();
		bomb_update();
		LIMIT_TIME--;
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

	sprite_render(sprBG_GAME, 0, 0, SCREEN_W / 1920.0f, SCREEN_H / 1080.0f);
	enemy_render();
	bomb_render();
	player_render();
	score_render();
	item_render();
	//debug::setString("game_timer%d", game_timer);
	//debug::setString("game_state%d", game_state.state);
	//debug::setString("magnet(%f:%f)", magnetic_force.x, magnetic_force.y);

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



	text_out(6, "SCORE", SCREEN_W - (SCREEN_W - SCREEN_H) + (SCREEN_W - SCREEN_H) / 2.0f, SCREEN_H / 100 * 10, 1, 1, 1, 1, 1, 1, TEXT_ALIGN::MIDDLE);
	text_out(6, to_string(score), SCREEN_W - (SCREEN_W - SCREEN_H) + (SCREEN_W - SCREEN_H) / 2.0f, SCREEN_H / 100 * 20, 1, 1, 1, 1, 1, 1, TEXT_ALIGN::MIDDLE);

	sprite_render(sprFRAME_GAME, 0, 0, SCREEN_W / 1920.0f, SCREEN_H / 1080.0f, 0, 0, 1920, 1080);


	string time_str = to_string(LIMIT_TIME / 60 / 60) + ":" + to_string(LIMIT_TIME / 60 % 60) + ":" + to_string(LIMIT_TIME % 60);
	text_out(6, "TIME", SCREEN_W - (SCREEN_W - SCREEN_H) + (SCREEN_W - SCREEN_H) / 2.0f, SCREEN_H / 100 * 30, 1, 1, 1, 1, 1, 1, TEXT_ALIGN::MIDDLE);
	text_out(6, time_str, SCREEN_W - (SCREEN_W - SCREEN_H) + (SCREEN_W - SCREEN_H) / 2.0f, SCREEN_H / 100 * 40, 1, 1, 1, 1, 1, 1, TEXT_ALIGN::MIDDLE);

}
