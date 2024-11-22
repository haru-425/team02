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
S_SCENE tutorial_state;
int tutorial_timer;
int tutorial_progress;
VECTOR3 tutorial_color;

void tutorial_init()
{
	tutorial_progress = 0;
	tutorial_timer = 0;
	tutorial_state.state = tutorial_state.INITIALIZE;
}
void tutorial_deinit()
{

	//music::stop(0);

}

void tutorial_update()
{
	switch (tutorial_state.state)
	{
	case tutorial_state.INITIALIZE:
		tutorial_state.state = tutorial_state.B_TRANSIATON;
	case tutorial_state.B_TRANSIATON:
		if (true)
		{
			tutorial_state.state = tutorial_state.PARAMETER;
		}
		break;

	case tutorial_state.PARAMETER:

		GameLib::setBlendMode(Blender::BS_ALPHA);

		tutorial_state.state = tutorial_state.NORMAL;

	case tutorial_state.NORMAL:

		break;
		switch (tutorial_progress)
		{
		case 1:

			break;
		case 2:

			break;
		default:
			break;
		}

	case tutorial_state.F_TRANSITION:
		if (tutorial_timer >= 240)
		{
			nextScene = SCENE_TYPE::GAME;
		}

	}
	tutorial_timer++;
}


void tutorial_render()
{
	// 画面を青で塗りつぶす
	GameLib::clear(0.3f, 0.5f, 1.0f);
}
