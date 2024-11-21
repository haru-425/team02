//------< インクルード >---------------------------------------------------------
#include "../GameLib/game_lib.h"
#include "common.h"
#include "audio.h"
#include "m_scene.h"
// namespace
using namespace GameLib;
using namespace input;

//------< 定数 >----------------------------------------------------------------


//------< 変数 >----------------------------------------------------------------
S_SCENE title_state;
int title_timer;

Sprite* sprTITLE_UI_BACK;
Sprite* sprTITLE_BUTTON[3];
Sprite* sprTITLE_BUTTON_TEXT[3];

void title_init()
{
	title_state.state = 0;
	title_timer = 0;
}

void title_deinit()
{

	//music::stop(0);

	safe_delete(sprTITLE_UI_BACK);
}

void title_update()
{
	switch (title_state.state)
	{
	case title_state.INITIALIZE:
		title_state.state = title_state.B_TRANSIATON;

		sprTITLE_UI_BACK = sprite_load(L"./Data/Images/UI/TITLE_UI_BACK.png");
		sprTITLE_BUTTON[0] = sprite_load(L"./Data/Images/UI/playButton.png");
		sprTITLE_BUTTON[1] = sprite_load(L"./Data/Images/UI/helpButton.png");
		sprTITLE_BUTTON[2] = sprite_load(L"./Data/Images/UI/settingButton.png");


	case title_state.B_TRANSIATON:
		if (true)
		{
			title_state.state = title_state.PARAMETER;
		}
		break;

	case title_state.PARAMETER:
		GameLib::setBlendMode(Blender::BS_ALPHA);

		title_state.state = title_state.NORMAL;

	case title_state.NORMAL:
		if (TRG(0) & PAD_START)
		{
			title_state.state = title_state.F_TRANSITION;
			break;
		}
		break;
	case title_state.F_TRANSITION:
		if (true)
		{
			nextScene = SCENE_TYPE::GAME;
		}


	}

	title_timer++;
}

void title_render()
{
	// 画面を青で塗りつぶす
	GameLib::clear(0.3f, 0.5f, 1.0f);


	sprite_render(sprTITLE_UI_BACK,
		SCREEN_W / 2.0f, SCREEN_H / 10.0f * 8.0f,
		1280.0 / SCREEN_W, 720.0f / SCREEN_H / 5.0f,
		0, 0,
		1280, 720,
		640, 360,
		0,
		1, 1, 1, 1);
	VECTOR2 cursorPos = cursor_position();
	if (isCircleColliding(cursorPos, 0.0f, { SCREEN_W / 2.0f, SCREEN_H / 10.0f * 8.0f }, 128.0f / 2.0f))
	{

		sprite_render(sprTITLE_BUTTON[int(TITLE_BUTTON::START)],
			SCREEN_W / 2.0f, SCREEN_H / 10.0f * 8.0f,
			1, 1,
			128, 0,
			128, 128,
			64, 64,
			0,
			1, 1, 1, 1);


	}
	else {
		sprite_render(sprTITLE_BUTTON[int(TITLE_BUTTON::START)],
			SCREEN_W / 2.0f, SCREEN_H / 10.0f * 8.0f,
			1, 1,
			0, 0,
			128, 128,
			64, 64,
			0,
			1, 1, 1, 1);
	}


	if (isCircleColliding(cursorPos, 0.0f, { SCREEN_W / 4.0f * 3.0f, SCREEN_H / 10.0f * 8.0f }, 128.0f / 2.0f))
	{

		sprite_render(sprTITLE_BUTTON[int(TITLE_BUTTON::SETTING)],
			SCREEN_W / 4.0f * 3.0f, SCREEN_H / 10.0f * 8.0f,
			1, 1,
			128, 0,
			128, 128,
			64, 64,
			0,
			1, 1, 1, 1);


	}
	else {
		sprite_render(sprTITLE_BUTTON[int(TITLE_BUTTON::SETTING)],
			SCREEN_W / 4.0f * 3.0f, SCREEN_H / 10.0f * 8.0f,
			1, 1,
			0, 0,
			128, 128,
			64, 64,
			0,
			1, 1, 1, 1);
	}


	if (isCircleColliding(cursorPos, 0.0f, { SCREEN_W / 4.0f, SCREEN_H / 10.0f * 8.0f }, 128.0f / 2.0f))
	{

		sprite_render(sprTITLE_BUTTON[int(TITLE_BUTTON::HELP)],
			SCREEN_W / 4.0f, SCREEN_H / 10.0f * 8.0f,
			1, 1,
			128, 0,
			128, 128,
			64, 64,
			0,
			1, 1, 1, 1);


	}
	else {
		sprite_render(sprTITLE_BUTTON[int(TITLE_BUTTON::HELP)],
			SCREEN_W / 4.0f, SCREEN_H / 10.0f * 8.0f,
			1, 1,
			0, 0,
			128, 128,
			64, 64,
			0,
			1, 1, 1, 1);
	}

}
