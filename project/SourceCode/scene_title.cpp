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
SCENE_TYPE _next;

Sprite* sprTITLE_UI_BACK;
Sprite* sprTITLE_BUTTON[3];
Sprite* sprTITLE_BUTTON_TEXT;


Sprite* sprBG_TITLE;
float title_text_scale[3];
float title_text_y[3];

void title_init()
{
	title_state.state = 0;
	title_timer = 0;
}

void title_deinit()
{

	music::stop(BGM_TITLE);

	safe_delete(sprTITLE_UI_BACK);
	safe_delete(sprTITLE_BUTTON_TEXT);
	for (int i = 0; i < 3; i++)
	{

		safe_delete(sprTITLE_BUTTON[i]);
	}
	safe_delete(sprBG_TITLE);


}

void title_update()
{
	switch (title_state.state)
	{
	case title_state.INITIALIZE:


		music::play(BGM_TITLE, true);
		title_state.state = title_state.B_TRANSIATON;

		sprTITLE_UI_BACK = sprite_load(L"./Data/Images/UI/TITLE_UI_BACK.png");
		sprTITLE_BUTTON[0] = sprite_load(L"./Data/Images/UI/playButton.png");
		sprTITLE_BUTTON[1] = sprite_load(L"./Data/Images/UI/helpButton.png");
		sprTITLE_BUTTON[2] = sprite_load(L"./Data/Images/UI/settingButton.png");


		sprTITLE_BUTTON_TEXT = sprite_load(L"./Data/Images/UI/title_text.png");

		sprBG_TITLE = sprite_load(L"./Data/Images/BG/title01.png");



		title_text_scale[0] = 0.0f;
		title_text_scale[1] = 0.0f;
		title_text_scale[2] = 0.0f;


		title_text_y[0] = SCREEN_H / 10.0f * 8.0f;
		title_text_y[1] = SCREEN_H / 10.0f * 8.0f;
		title_text_y[2] = SCREEN_H / 10.0f * 8.0f;


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
		//if (TRG(0) & PAD_START)
		//{
		//	title_state.state = title_state.F_TRANSITION;
		//	break;
		//}
		break;
	case title_state.F_TRANSITION:
		if (true)
		{
			nextScene = _next;
		}


	}

	title_timer++;
}

void title_render()
{
	// 画面を青で塗りつぶす
	GameLib::clear(0.3f, 0.5f, 1.0f);

	sprite_render(sprBG_TITLE, 0, 0, SCREEN_W / 1920.0f, SCREEN_H / 1080.0f);

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

		if (title_text_scale[int(TITLE_BUTTON::START)] < 2.0f)
		{
			title_text_scale[int(TITLE_BUTTON::START)] += 0.1f;

		}
		if (title_text_y[int(TITLE_BUTTON::START)] > SCREEN_H / 10.0f * 8.0f - 100)
		{
			title_text_y[int(TITLE_BUTTON::START)] -= 10;
		}

		if (TRG_RELEASE(0) & L_CLICK) {
			title_state.state = S_SCENE::F_TRANSITION;
			_next = SCENE_TYPE::GAME;
		}
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
		if (title_text_scale[int(TITLE_BUTTON::START)] > 0.0f)
		{
			title_text_scale[int(TITLE_BUTTON::START)] -= 0.1f;
		}
		if (title_text_y[int(TITLE_BUTTON::START)] < SCREEN_H / 10.0f * 8.0f)
		{
			title_text_y[int(TITLE_BUTTON::START)] += 20;
		}
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
		if (title_text_scale[int(TITLE_BUTTON::SETTING)] < 2.0f)
		{
			title_text_scale[int(TITLE_BUTTON::SETTING)] += 0.1f;

		}
		if (title_text_y[int(TITLE_BUTTON::SETTING)] > SCREEN_H / 10.0f * 8.0f - 100)
		{
			title_text_y[int(TITLE_BUTTON::SETTING)] -= 10;
		}
		if (TRG_RELEASE(0) & L_CLICK) {
			title_state.state = S_SCENE::F_TRANSITION;
			_next = SCENE_TYPE::GAME;
		}
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
		if (title_text_scale[int(TITLE_BUTTON::SETTING)] > 0.0f)
		{
			title_text_scale[int(TITLE_BUTTON::SETTING)] -= 0.1f;
		}
		if (title_text_y[int(TITLE_BUTTON::SETTING)] < SCREEN_H / 10.0f * 8.0f)
		{
			title_text_y[int(TITLE_BUTTON::SETTING)] += 20;
		}
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

		if (title_text_scale[int(TITLE_BUTTON::HELP)] < 2.0f)
		{
			title_text_scale[int(TITLE_BUTTON::HELP)] += 0.1f;

		}
		if (title_text_y[int(TITLE_BUTTON::HELP)] > SCREEN_H / 10.0f * 8.0f - 100)
		{
			title_text_y[int(TITLE_BUTTON::HELP)] -= 10;
		}		if (TRG_RELEASE(0) & L_CLICK) {
			title_state.state = S_SCENE::F_TRANSITION;
			_next = SCENE_TYPE::TUTORIAL;
		}
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

		if (title_text_scale[int(TITLE_BUTTON::HELP)] > 0.0f)
		{
			title_text_scale[int(TITLE_BUTTON::HELP)] -= 0.1f;
		}
		if (title_text_y[int(TITLE_BUTTON::HELP)] < SCREEN_H / 10.0f * 8.0f)
		{
			title_text_y[int(TITLE_BUTTON::HELP)] += 20;
		}
	}



	sprite_render(sprTITLE_BUTTON_TEXT,
		SCREEN_W / 2.0f, title_text_y[int(TITLE_BUTTON::START)],
		title_text_scale[int(TITLE_BUTTON::START)], title_text_scale[int(TITLE_BUTTON::START)],
		576 / 3 * int(TITLE_BUTTON::START), 0,
		576 / 3.0f, 64,
		576 / 6.0f, 32,
		0,
		1, 1, 1, 1);


	sprite_render(sprTITLE_BUTTON_TEXT,
		SCREEN_W / 4.0f, title_text_y[int(TITLE_BUTTON::HELP)],
		title_text_scale[int(TITLE_BUTTON::HELP)], title_text_scale[int(TITLE_BUTTON::HELP)],
		576 / 3 * int(TITLE_BUTTON::HELP), 0,
		576 / 3.0f, 64,
		576 / 6.0f, 32,
		0,
		1, 1, 1, 1);

	sprite_render(sprTITLE_BUTTON_TEXT,
		SCREEN_W / 4.0f * 3.0f, title_text_y[int(TITLE_BUTTON::SETTING)],
		title_text_scale[int(TITLE_BUTTON::SETTING)], title_text_scale[int(TITLE_BUTTON::SETTING)],
		576 / 3 * int(TITLE_BUTTON::SETTING), 0,
		576 / 3.0f, 64,
		576 / 6.0f, 32,
		0,
		1, 1, 1, 1);

}
