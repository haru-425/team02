//------< インクルード >---------------------------------------------------------
#include "../GameLib/game_lib.h"
#include "common.h"
#include "audio.h"
#include "m_scene.h"
// namespace
using namespace GameLib;
using namespace input;
//------< 変数 >----------------------------------------------------------------

//------------------------------------------------------------------------------
//  WinMain（エントリポイント）
//------------------------------------------------------------------------------
int APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)// 使用しない変数は記述しない
{
	// ゲームライブラリの初期設定
	GameLib::init(L"ゲームプログラミングⅠ", SCREEN_W, SCREEN_H, FULLSCREEN);

	// オーディオの初期設定
	audio_init();

	while (GameLib::gameLoop())
	{
		M_SCENE::SceneChangeProcessing();
		M_SCENE::SceneUpdateProcessing();
		M_SCENE::SceneRenderProcessing();
		GameLib::present(1, 0);

		GameLib::init(L"ゲームプログラミングⅠ", SCREEN_W, SCREEN_H, FULLSCREEN);
	}
	M_SCENE::SceneEndProcessing;
	GameLib::uninit();

	return 0;
}