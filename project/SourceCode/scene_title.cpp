#include "all.h"

int title_state;
int title_timer;


void title_init()
{
	title_state = 0;
	title_timer = 0;
}

void title_deinit()
{

	//music::stop(0);

}

void title_update()
{
	switch (title_state)
	{
	case 0:
		//////// ‰Šúİ’è ////////

		title_state++;
		/*fallthrough*/

	case 1:
		//////// ƒpƒ‰ƒ[ƒ^‚Ìİ’è ////////

		GameLib::setBlendMode(Blender::BS_ALPHA);

		music::play(0, false);

		title_state++;
		/*fallthrough*/

	case 2:
		//////// ’Êí ////////

		if (TRG(0) & PAD_START)
		{
			nextScene = SCENE_GAME;
			break;
		}

		break;
	}


	title_timer++;
}

void title_render()
{
	// ‰æ–Ê‚ğÂ‚Å“h‚è‚Â‚Ô‚·
	GameLib::clear(0.3f, 0.5f, 1.0f);
}
