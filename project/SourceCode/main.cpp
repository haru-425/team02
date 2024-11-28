//------< インクルード >---------------------------------------------------------
// GameLibゲームライブラリのヘッダファイルをインクルード
#include "../GameLib/game_lib.h"
// 共通ヘッダファイルをインクルード
#include "common.h"
// オーディオ関連のヘッダファイルをインクルード
#include "audio.h"
// シーン管理関連のヘッダファイルをインクルード
#include "m_scene.h"

// namespaceを使用する
using namespace GameLib;
using namespace input;

//------< 変数 >----------------------------------------------------------------

//------------------------------------------------------------------------------
//   WinMain（エントリポイント）
//------------------------------------------------------------------------------
// Windowsアプリケーションのエントリポイント
int APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)// 使用しない変数は記述しない
{
	// ゲームライブラリの初期設定
	// タイトル、画面幅、画面高さ、フルスクリーンモードを指定
	GameLib::init(L"ゲームプログラミングⅠ", SCREEN_W, SCREEN_H, FULLSCREEN);

	// オーディオの初期設定
	audio_init();

	// ゲームループ
	while (GameLib::gameLoop())
	{
		// シーンの変更処理

		M_SCENE::SceneChangeProcessing();
		// シーンの更新処理
		M_SCENE::SceneUpdateProcessing();
		// シーンの描画処理
		M_SCENE::SceneRenderProcessing();
		// フレームを表示
		GameLib::present(1, 0);
		for (int i = 0; i < 8; i++)
		{

			sound::setVolume(XWB_SOUNDS, i, 1.0f / 5.0f * game_volume.se_volume);
		}
		for (int i = 0; i < 3; i++)
		{
			music::setVolume(i, 1.0f / 5.0f * game_volume.bgm_volume);
		}

	}

	GameLib::present(1, 0);
	// シーンの終了処理
	M_SCENE::SceneEndProcessing; // <- ここにセミコロンが必要
	// ゲームライブラリの終了処理
	GameLib::uninit();

	// 正常終了
	return 0;
}