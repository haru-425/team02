#include "scene_setting.h"

int setting_timer;
S_SCENE setting_state;
Bolume game_volume;
Button bgm_volume_up;
Button bgm_volume_Down;
Button se_volume_up;
Button se_volume_Down;
extern Button EndButton;

Sprite* sprBG_S;
Sprite* sprOverley_S;
Sprite* volume_change;
Sprite* volume_setting;


void setting_init()
{
	setting_timer = 0;
	setting_state.state = setting_state.INITIALIZE;
	
}
void setting_deinit()
{
	//music::stop(0);

}

void setting_update()
{
	switch (setting_state.state)
	{
	case setting_state.INITIALIZE:

		GameLib::setBlendMode(Blender::BS_ALPHA);
		volume_change = sprite_load(L"./Data/Images/arrow01.png");
		sprBG_S = sprite_load(L"./Data/Images/title_layer01.png");
		sprOverley_S = sprite_load(L"./Data/Images/title_layer02.png");
		volume_setting = sprite_load(L"./Data/Images/setting.png");
		setting_state.state = setting_state.B_TRANSIATON;
		
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
			//sound::play(XWB_SYSTEM, XWB_SYSTEM_BUTTON);


		}
		if (TRG(0) & L_CLICK && bgm_volume_Down.rect_click(bgm_volume_Down) && game_volume.bgm_volume > 0)
		{
			game_volume.bgm_volume--;
			//sound::play(XWB_SYSTEM, XWB_SYSTEM_BUTTON);

		}
		if (TRG(0) & L_CLICK && se_volume_up.rect_click(se_volume_up) && game_volume.se_volume < 5)
		{
			game_volume.se_volume++;

			/*for (int i = 0; i < SOUND_EFFECT_COUNT; i++)
			{

				sound::setVolume(XWB_SYSTEM, i, game_volume.se_volume * (1.0f / 5.0f));
			}*/

			/*sound::play(XWB_SYSTEM, XWB_SYSTEM_BUTTON);*/
		}
		if (TRG(0) & L_CLICK && se_volume_Down.rect_click(se_volume_Down) && game_volume.se_volume > 0)
		{
			game_volume.se_volume--;
			/*for (int i = 0; i < SOUND_EFFECT_COUNT; i++)
			{

				sound::setVolume(XWB_SYSTEM, i, game_volume.se_volume * (1.0f / 5.0f));
			}
			sound::play(XWB_SYSTEM, XWB_SYSTEM_BUTTON);*/
		}

		/*EndButton.end_button_update();*/
		
		break;
	case setting_state.F_TRANSITION:
		if (setting_timer >= 240)
		{
			nextScene = SCENE_TYPE::GAME;
		}

	}
	setting_timer++;
}


void setting_render()
{
	// âÊñ Çê¬Ç≈ìhÇËÇ¬Ç‘Ç∑
	GameLib::clear(0.3f, 0.5f, 1.0f);

	
}
