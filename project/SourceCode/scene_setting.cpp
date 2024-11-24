#include "scene_setting.h"

int setting_timer;
S_SCENE setting_state;

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
		setting_state.state = setting_state.B_TRANSIATON;
		
	case setting_state.B_TRANSIATON:
		if (true)
		{
			setting_state.state = setting_state.PARAMETER;
		}
		break;

	case setting_state.PARAMETER:

		GameLib::setBlendMode(Blender::BS_ALPHA);

		setting_state.state = setting_state.NORMAL;

	case setting_state.NORMAL:

		
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
	// ‰æ–Ê‚ğÂ‚Å“h‚è‚Â‚Ô‚·
	GameLib::clear(0.3f, 0.5f, 1.0f);

	
}
