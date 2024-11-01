#include "../GameLib/game_lib.h"
#include "audio.h"
// namespace
using namespace GameLib;
void audio_init()
{


	//music::load(0, L"./Data/Musics/bgm_maoudamashii_8bit29.wav");

	//sound::load(XWB_SYSTEM, L"./Data/Sounds/system.xwb");

	//sound::setVolume(XWB_STAGE1, XWB_STAGE1_MISSILE, 4.0f);
}

void audio_deinit()
{

	music::clear;

}
