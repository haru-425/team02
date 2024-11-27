#include "../GameLib/game_lib.h"
#include "audio.h"
#include "scene_setting.h"
// namespace
using namespace GameLib;
void audio_init()
{


	music::load(BGM_TITLE, L"./Data/Musics/Courage_to_Stand_Up.wav");
	music::load(BGM_GAME, L"./Data/Musics/Scramble_Line.wav");
	music::load(BGM_RESULT, L"./Data/Musics/Starlights.wav");

	sound::load(XWB_SOUNDS, L"./Data/Sounds/sounds.xwb");

}

void audio_deinit()
{

	music::clear;

}
