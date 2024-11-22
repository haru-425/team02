#include "../GameLib/game_lib.h"
#include "audio.h"
// namespace
using namespace GameLib;
void audio_init()
{


	music::load(BGM_TITLE, L"./Data/Musics/Courage_to_Stand_Up.wav");
	music::load(BGM_GAME, L"./Data/Musics/Scramble_Line.wav");
	music::load(BGM_RESULT, L"./Data/Musics/Starlights.wav");

	//sound::load(XWB_SYSTEM, L"./Data/Sounds/system.xwb");

	//sound::setVolume(XWB_STAGE1, XWB_STAGE1_MISSILE, 4.0f);
}

void audio_deinit()
{

	music::clear;

}
