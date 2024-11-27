//------< インクルード >---------------------------------------------------------
#include "../GameLib/game_lib.h"
#include "common.h"
#include "audio.h"
#include "m_scene.h"
// namespace
using namespace GameLib;
using namespace input;
VECTOR2 score_pos;
float score_angle;

//------< 定数 >----------------------------------------------------------------


//------< 変数 >----------------------------------------------------------------
S_SCENE result_state;
int result_timer;
SCENE_TYPE __next;

Sprite* sprRESULT_UI_BACK;
Sprite* sprRESULT_BUTTON[2];
Sprite* sprRESULT_BUTTON_TEXT;


Sprite* sprBG_RESULT;
float result_text_scale[2];
float result_text_y[2];

void result_init()
{
	result_state.state = 0;
	result_timer = 0;
}

void result_deinit()
{

	music::stop(BGM_RESULT);

	safe_delete(sprRESULT_UI_BACK);
	safe_delete(sprRESULT_BUTTON_TEXT);
	for (int i = 0; i < 3; i++)
	{

		safe_delete(sprRESULT_BUTTON[i]);
	}
	safe_delete(sprBG_RESULT);


}

void result_update()
{
	switch (result_state.state)
	{
	case result_state.INITIALIZE:


		music::play(BGM_RESULT, true);
		result_state.state = result_state.B_TRANSIATON;

		sprRESULT_UI_BACK = sprite_load(L"./Data/Images/UI/TITLE_UI_BACK.png");
		sprRESULT_BUTTON[0] = sprite_load(L"./Data/Images/UI/playButton.png");
		sprRESULT_BUTTON[1] = sprite_load(L"./Data/Images/UI/homeButton.png");


		sprRESULT_BUTTON_TEXT = sprite_load(L"./Data/Images/UI/result_text.png");

		sprBG_RESULT = sprite_load(L"./Data/Images/BG/title01.png");



		result_text_scale[0] = 0.0f;
		result_text_scale[1] = 0.0f;


		result_text_y[0] = SCREEN_H / 10.0f * 8.0f;
		result_text_y[1] = SCREEN_H / 10.0f * 8.0f;


	case result_state.B_TRANSIATON:
		if (true)
		{
			result_state.state = result_state.PARAMETER;
		}
		break;

	case result_state.PARAMETER:
		GameLib::setBlendMode(Blender::BS_ALPHA);

		result_state.state = result_state.NORMAL;

	case result_state.NORMAL:
		//if (TRG(0) & PAD_START)
		//{
		//	result_state.state = result_state.F_TRANSITION;
		//	break;
		//}

		score_pos.x = cos(score_angle) * 20;
		score_pos.y = sin(2 * score_angle) * 10;
		score_angle += ToRadian(1);
		break;
	case result_state.F_TRANSITION:
		if (true)
		{
			nextScene = __next;
		}


	}

	result_timer++;
}

void result_render()
{
	// 画面を青で塗りつぶす
	GameLib::clear(0.3f, 0.5f, 1.0f);

	sprite_render(sprBG_RESULT, 0, 0, SCREEN_W / 1920.0f, SCREEN_H / 1080.0f);

	sprite_render(sprRESULT_UI_BACK,
		SCREEN_W / 2.0f, SCREEN_H / 10.0f * 8.0f,
		1280.0 / SCREEN_W, 720.0f / SCREEN_H / 5.0f,
		0, 0,
		1280, 720,
		640, 360,
		0,
		1, 1, 1, 1);
	VECTOR2 cursorPos = cursor_position();
	if (isCircleColliding(cursorPos, 0.0f, { SCREEN_W / 3.0f, SCREEN_H / 10.0f * 8.0f }, 128.0f / 2.0f))
	{

		sprite_render(sprRESULT_BUTTON[int(RESULT_BUTTON::START)],
			SCREEN_W / 3.0f, SCREEN_H / 10.0f * 8.0f,
			1, 1,
			128, 0,
			128, 128,
			64, 64,
			0,
			1, 1, 1, 1);

		if (result_text_scale[int(RESULT_BUTTON::START)] < 2.0f)
		{
			result_text_scale[int(RESULT_BUTTON::START)] += 0.1f;

		}
		if (result_text_y[int(RESULT_BUTTON::START)] > SCREEN_H / 10.0f * 8.0f - 100)
		{
			result_text_y[int(RESULT_BUTTON::START)] -= 10;
		}

		if (TRG_RELEASE(0) & L_CLICK) {
			result_state.state = S_SCENE::F_TRANSITION;
			__next = SCENE_TYPE::GAME;
		}
	}
	else {
		sprite_render(sprRESULT_BUTTON[int(RESULT_BUTTON::START)],
			SCREEN_W / 3.0f, SCREEN_H / 10.0f * 8.0f,
			1, 1,
			0, 0,
			128, 128,
			64, 64,
			0,
			1, 1, 1, 1);
		if (result_text_scale[int(RESULT_BUTTON::START)] > 0.0f)
		{
			result_text_scale[int(RESULT_BUTTON::START)] -= 0.1f;
		}
		if (result_text_y[int(RESULT_BUTTON::START)] < SCREEN_H / 10.0f * 8.0f)
		{
			result_text_y[int(RESULT_BUTTON::START)] += 20;
		}
	}





	if (isCircleColliding(cursorPos, 0.0f, { SCREEN_W / 3 * 2.0f, SCREEN_H / 10.0f * 8.0f }, 128.0f / 2.0f))
	{

		sprite_render(sprRESULT_BUTTON[int(RESULT_BUTTON::HOME)],
			SCREEN_W / 3 * 2.0f, SCREEN_H / 10.0f * 8.0f,
			1, 1,
			128, 0,
			128, 128,
			64, 64,
			0,
			1, 1, 1, 1);

		if (result_text_scale[int(RESULT_BUTTON::HOME)] < 2.0f)
		{
			result_text_scale[int(RESULT_BUTTON::HOME)] += 0.1f;

		}
		if (result_text_y[int(RESULT_BUTTON::HOME)] > SCREEN_H / 10.0f * 8.0f - 100)
		{
			result_text_y[int(RESULT_BUTTON::HOME)] -= 10;
		}		if (TRG_RELEASE(0) & L_CLICK) {
			result_state.state = S_SCENE::F_TRANSITION;
			__next = SCENE_TYPE::TITLE;
			sound::play(XWB_SOUNDS, XWB_SOUND_RETURN_BUTTON);
		}
	}
	else {
		sprite_render(sprRESULT_BUTTON[int(RESULT_BUTTON::HOME)],
			SCREEN_W / 3 * 2.0f, SCREEN_H / 10.0f * 8.0f,
			1, 1,
			0, 0,
			128, 128,
			64, 64,
			0,
			1, 1, 1, 1);

		if (result_text_scale[int(RESULT_BUTTON::HOME)] > 0.0f)
		{
			result_text_scale[int(RESULT_BUTTON::HOME)] -= 0.1f;
		}
		if (result_text_y[int(RESULT_BUTTON::HOME)] < SCREEN_H / 10.0f * 8.0f)
		{
			result_text_y[int(RESULT_BUTTON::HOME)] += 20;
		}
	}



	sprite_render(sprRESULT_BUTTON_TEXT,
		SCREEN_W / 3.0f, result_text_y[int(RESULT_BUTTON::START)],
		result_text_scale[int(RESULT_BUTTON::START)], result_text_scale[int(RESULT_BUTTON::START)],
		576 / 3 * int(RESULT_BUTTON::START), 0,
		576 / 3.0f, 64,
		576 / 6.0f, 32,
		0,
		1, 1, 1, 1);


	sprite_render(sprRESULT_BUTTON_TEXT,
		SCREEN_W / 3 * 2.0f, result_text_y[int(RESULT_BUTTON::HOME)],
		result_text_scale[int(RESULT_BUTTON::HOME)], result_text_scale[int(RESULT_BUTTON::HOME)],
		576 / 3 * int(RESULT_BUTTON::HOME), 0,
		576 / 3.0f, 64,
		576 / 6.0f, 32,
		0,
		1, 1, 1, 1);
	int BOLD = 1;
	text_out(6, "SCORE", SCREEN_W / 2.0f + score_pos.x + BOLD, SCREEN_H / 100 * 30 + score_pos.y, 3, 3, 0, 0, 0.7f, 1, TEXT_ALIGN::MIDDLE);
	text_out(6, "SCORE", SCREEN_W / 2.0f + score_pos.x - BOLD, SCREEN_H / 100 * 30 + score_pos.y, 3, 3, 0, 0, 0.7f, 1, TEXT_ALIGN::MIDDLE);

	text_out(6, "SCORE", SCREEN_W / 2.0f + score_pos.x, SCREEN_H / 100 * 30 + score_pos.y + BOLD, 3, 3, 0, 0, 0.7f, 1, TEXT_ALIGN::MIDDLE);
	text_out(6, "SCORE", SCREEN_W / 2.0f + score_pos.x, SCREEN_H / 100 * 30 + score_pos.y - BOLD, 3, 3, 0, 0, 0.7f, 1, TEXT_ALIGN::MIDDLE);

	text_out(6, "SCORE", SCREEN_W / 2.0f + score_pos.x + BOLD, SCREEN_H / 100 * 30 + score_pos.y + BOLD, 3, 3, 0, 0, 0.7f, 1, TEXT_ALIGN::MIDDLE);
	text_out(6, "SCORE", SCREEN_W / 2.0f + score_pos.x + BOLD, SCREEN_H / 100 * 30 + score_pos.y - BOLD, 3, 3, 0, 0, 0.7f, 1, TEXT_ALIGN::MIDDLE);

	text_out(6, "SCORE", SCREEN_W / 2.0f + score_pos.x - BOLD, SCREEN_H / 100 * 30 + score_pos.y + BOLD, 3, 3, 0, 0, 0.7f, 1, TEXT_ALIGN::MIDDLE);
	text_out(6, "SCORE", SCREEN_W / 2.0f + score_pos.x - BOLD, SCREEN_H / 100 * 30 + score_pos.y - BOLD, 3, 3, 0, 0, 0.7f, 1, TEXT_ALIGN::MIDDLE);

	text_out(6, "SCORE", SCREEN_W / 2.0f + score_pos.x, SCREEN_H / 100 * 30 + score_pos.y, 3, 3, 1, 1, 1, 1, TEXT_ALIGN::MIDDLE);


	string str_score = to_string(score);
	text_out(6, str_score, SCREEN_W / 2.0f + BOLD, SCREEN_H / 100 * 30 + 150, 5, 5, 0, 0, 0.7f, 1, TEXT_ALIGN::MIDDLE);
	text_out(6, str_score, SCREEN_W / 2.0f - BOLD, SCREEN_H / 100 * 30 + 150, 5, 5, 0, 0, 0.7f, 1, TEXT_ALIGN::MIDDLE);
	text_out(6, str_score, SCREEN_W / 2.0f, SCREEN_H / 100 * 30 + BOLD + 150, 5, 5, 0, 0, 0.7f, 1, TEXT_ALIGN::MIDDLE);
	text_out(6, str_score, SCREEN_W / 2.0f, SCREEN_H / 100 * 30 - BOLD + 150, 5, 5, 0, 0, 0.7f, 1, TEXT_ALIGN::MIDDLE);
	text_out(6, str_score, SCREEN_W / 2.0f + BOLD, SCREEN_H / 100 * 30 + 150 + BOLD, 5, 5, 0, 0, 0.7f, 1, TEXT_ALIGN::MIDDLE);
	text_out(6, str_score, SCREEN_W / 2.0f + BOLD, SCREEN_H / 100 * 30 + 150 - BOLD, 5, 5, 0, 0, 0.7f, 1, TEXT_ALIGN::MIDDLE);
	text_out(6, str_score, SCREEN_W / 2.0f - BOLD, SCREEN_H / 100 * 30 + 150 + BOLD, 5, 5, 0, 0, 0.7f, 1, TEXT_ALIGN::MIDDLE);
	text_out(6, str_score, SCREEN_W / 2.0f - BOLD, SCREEN_H / 100 * 30 + 150 - BOLD, 5, 5, 0, 0, 0.7f, 1, TEXT_ALIGN::MIDDLE);
	text_out(6, str_score, SCREEN_W / 2.0f, SCREEN_H / 100 * 30 + 150, 5, 5, 1, 1, 1, 1, TEXT_ALIGN::MIDDLE);





}
