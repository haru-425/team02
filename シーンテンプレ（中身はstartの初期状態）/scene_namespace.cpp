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
S_SCENE start_state;
int start_timer;
VECTOR3 start_color;

void start_init()
{
	start_state.state = 0;
	start_timer = 0;
}

void start_deinit()
{

	//music::stop(0);

}

void start_update()
{
	switch (start_state.state)
	{
	case start_state.INITIALIZE:
		start_state.state = start_state.B_TRANSIATON;
	case start_state.B_TRANSIATON:
		if (true)
		{
			start_state.state = start_state.PARAMETER;
		}
		break;

	case start_state.PARAMETER:
		GameLib::setBlendMode(Blender::BS_ALPHA);

		start_state.state = start_state.NORMAL;

	case start_state.NORMAL:
		if (/*TRG(0) & PAD_START*/true)
		{
			start_state.state = start_state.F_TRANSITION;
			break;
		}
		break;
	case start_state.F_TRANSITION:
		if (start_timer >= 240)
		{
			nextScene = SCENE_TYPE::GAME;
		}
		STRATCOLOR

	}

	start_timer++;
}

void start_render()
{
	// 画面を青で塗りつぶす
	GameLib::clear(0.3f, 0.5f, 1.0f);
}
