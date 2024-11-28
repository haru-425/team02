#include "scene_setting.h"

int setting_timer;
S_SCENE setting_state;
Bolume game_volume;
Button bgm_volume_up;
Button bgm_volume_Down;
Button se_volume_up;
Button se_volume_Down;
extern Button EndButton;

Sprite* volume_change;
Sprite* volume_setting;
Sprite* BG_Image;
Sprite* sprRetern;


void setting_init()
{
	setting_timer = 0;
	setting_state.state = setting_state.INITIALIZE;

}
void setting_deinit()
{
	//music::stop(0);
	safe_delete(volume_change);
	safe_delete(volume_setting);
	safe_delete(BG_Image);
	safe_delete(sprRetern);
	music::stop(BGM_RESULT);

}

void setting_update()
{
	switch (setting_state.state)
	{
	case setting_state.INITIALIZE:

		GameLib::setBlendMode(Blender::BS_ALPHA);
		volume_change = sprite_load(L"./Data/Images/UI/arrow01.png");
		volume_setting = sprite_load(L"./Data/Images/UI/setting.png");
		sprRetern = sprite_load(L"./Data/Images/UI/reternButton.png");
		BG_Image = sprite_load(L"./Data/Images/BG/title01.png");
		setting_state.state = setting_state.B_TRANSIATON;

		music::play(BGM_RESULT, true);

	case setting_state.B_TRANSIATON:

		if (true)
		{
			setting_state.state = setting_state.PARAMETER;
		}
		break;

	case setting_state.PARAMETER:

		GameLib::setBlendMode(Blender::BS_ALPHA);
		bgm_volume_up.bgm_volume_Up_init();
		bgm_volume_Down.bgm_volume_Down_init();
		se_volume_up.se_volume_Up_init();
		se_volume_Down.se_volume_Down_init();


		setting_state.state = setting_state.NORMAL;

	case setting_state.NORMAL:
		if (TRG(0) & L_CLICK && bgm_volume_up.rect_click(bgm_volume_up) && game_volume.bgm_volume < 5)
		{
			game_volume.bgm_volume++;

			sound::play(XWB_SOUNDS, XWB_SOUND_BUTTON);
			//sound::play(XWB_SYSTEM, XWB_SYSTEM_BUTTON);


		}
		if (TRG(0) & L_CLICK && bgm_volume_Down.rect_click(bgm_volume_Down) && game_volume.bgm_volume > 0)
		{
			game_volume.bgm_volume--;

			sound::play(XWB_SOUNDS, XWB_SOUND_BUTTON);
			//sound::play(XWB_SYSTEM, XWB_SYSTEM_BUTTON);

		}
		if (TRG(0) & L_CLICK && se_volume_up.rect_click(se_volume_up) && game_volume.se_volume < 5)
		{
			game_volume.se_volume++;

			sound::play(XWB_SOUNDS, XWB_SOUND_BUTTON);

			/*for (int i = 0; i < SOUND_EFFECT_COUNT; i++)
			{

				sound::setVolume(XWB_SYSTEM, i, game_volume.se_volume * (1.0f / 5.0f));
			}*/

			/*sound::play(XWB_SYSTEM, XWB_SYSTEM_BUTTON);*/
		}
		if (TRG(0) & L_CLICK && se_volume_Down.rect_click(se_volume_Down) && game_volume.se_volume > 0)
		{
			game_volume.se_volume--;

			sound::play(XWB_SOUNDS, XWB_SOUND_BUTTON);
			/*for (int i = 0; i < SOUND_EFFECT_COUNT; i++)
			{

				sound::setVolume(XWB_SYSTEM, i, game_volume.se_volume * (1.0f / 5.0f));
			}
			sound::play(XWB_SYSTEM, XWB_SYSTEM_BUTTON);*/
		}

		/*EndButton.end_button_update();*/

		break;
	case setting_state.F_TRANSITION:
		if (true)
		{
			nextScene = SCENE_TYPE::TITLE;
		}

	}
	setting_timer++;
}


void setting_render()
{
	// ‰æ–Ê‚ðÂ‚Å“h‚è‚Â‚Ô‚·
	GameLib::clear(0.3f, 0.5f, 1.0f);

	sprite_render(BG_Image, 0, 0, SCREEN_W / 1920.0f, SCREEN_H / 1080.0f);
	primitive::rect(90, 175, 1100, 470, 0, 0, 0, 0, 0, 0, 0.8);
	sprite_render(volume_setting, 0, 0, SCREEN_W / 1920.0f, SCREEN_H / 1080.0f, 0, 0);
	GameLib::text_out(6, "BGM VOLUME", 425, 300, 1, 1, 1, 1, 1, 1, TEXT_ALIGN::MIDDLE_RIGHT);
	GameLib::text_out(6, std::to_string(game_volume.bgm_volume), 825, 300, 1, 1, 1, 1, 1, 1, TEXT_ALIGN::MIDDLE_LEFT);
	GameLib::text_out(6, "SE VOLUME", 425, 400, 1, 1, 1, 1, 1, 1, TEXT_ALIGN::MIDDLE_RIGHT);
	GameLib::text_out(6, std::to_string(game_volume.se_volume), 825, 400, 1, 1, 1, 1, 1, 1, TEXT_ALIGN::MIDDLE_LEFT);
	if (game_volume.bgm_volume < 5)
	{
		sprite_render(volume_change, 925, 265, (SCREEN_W / 1920.0f) * 0.3f, (SCREEN_H / 1080.0f) * 0.3f, 0, 0, 400, 400, 0, 400, ToRadian(90));
	}
	else
	{
		sprite_render(volume_change, 925, 265, (SCREEN_W / 1920.0f) * 0.3f, (SCREEN_H / 1080.0f) * 0.3f, 0, 0, 400, 400, 0, 400, ToRadian(90), 1, 1, 1, 0.5);
	}
	if (game_volume.bgm_volume > 0)
	{
		sprite_render(volume_change, 685, 265, (SCREEN_W / 1920.0f) * 0.3f, (SCREEN_H / 1080.0f) * 0.3f, 0, 0, 400, 400, 400, 0, ToRadian(-90));
	}
	else
	{
		sprite_render(volume_change, 685, 265, (SCREEN_W / 1920.0f) * 0.3f, (SCREEN_H / 1080.0f) * 0.3f, 0, 0, 400, 400, 400, 0, ToRadian(-90), 1, 1, 1, 0.5);
	}
	if (game_volume.se_volume < 5)
	{
		sprite_render(volume_change, 925, 365, (SCREEN_W / 1920.0f) * 0.3f, (SCREEN_H / 1080.0f) * 0.3f, 0, 0, 400, 400, 0, 400, ToRadian(90));
	}
	else
	{
		sprite_render(volume_change, 925, 365, (SCREEN_W / 1920.0f) * 0.3f, (SCREEN_H / 1080.0f) * 0.3f, 0, 0, 400, 400, 0, 400, ToRadian(90), 1, 1, 1, 0.5);
	}
	if (game_volume.se_volume > 0)
	{
		sprite_render(volume_change, 685, 365, (SCREEN_W / 1920.0f) * 0.3f, (SCREEN_H / 1080.0f) * 0.3f, 0, 0, 400, 400, 400, 0, ToRadian(-90));
	}
	else
	{
		sprite_render(volume_change, 685, 365, (SCREEN_W / 1920.0f) * 0.3f, (SCREEN_H / 1080.0f) * 0.3f, 0, 0, 400, 400, 400, 0, ToRadian(-90), 1, 1, 1, 0.5);
	}

	VECTOR2 cursorPos = cursor_position();
	if (isCircleColliding(cursorPos, 0.0f, { SCREEN_W - 200.0f, 100 }, 128.0f / 2.0f))
	{


		sprite_render(sprRetern, SCREEN_W - 200, 100, 1, 1, 128, 0, 128, 128, 64, 64, 0);
		if (TRG_RELEASE(0) & L_CLICK) {
			setting_state.state = S_SCENE::F_TRANSITION;

			sound::play(XWB_SOUNDS, XWB_SOUND_BUTTON);
		}
	}
	else
	{

		sprite_render(sprRetern, SCREEN_W - 200, 100, 1, 1, 0, 0, 128, 128, 64, 64, 0);
	}
}
