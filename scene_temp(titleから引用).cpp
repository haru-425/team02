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


void title_init()
{
	title_state.state = 0;
	title_timer = 0;
}

void title_deinit()
{

	//music::stop(0);

}

void title_update()
{
	switch (title_state.state)
	{
	case title_state.B_TRANSIATON:
		if (true)
		{
			title_state.state = title_state.INITIALIZE;
		}
		break;
	case title_state.INITIALIZE:

		title_state.state = title_state.PARAMETER;
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
}
