//******************************************************************************
//
//
//      main
//
//
//******************************************************************************

//------< インクルード >---------------------------------------------------------
#include "all.h"

//------< 変数 >----------------------------------------------------------------
int curScene = SCENE_NONE;
int nextScene = SCENE_TITLE;

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
		// シーン切り替え処理
		if (curScene != nextScene)
		{
			// 現在のシーンに応じた終了処理
			switch (curScene)
			{
			case SCENE_TITLE:
				title_deinit();
				break;

			case SCENE_GAME:
				game_deinit();
				break;
			}

			// 次のシーンに応じた初期設定処理
			switch (nextScene)
			{
			case SCENE_TITLE:
				title_init();
				break;

			case SCENE_GAME:
				game_init();
				break;
			}

			curScene = nextScene;
		}

		// 入力を更新する
		input::update();

		music::update();

		// 現在のシーンに応じた更新・描画処理
		switch (curScene)
		{
		case SCENE_TITLE:
			title_update();
			title_render();
			break;

		case SCENE_GAME:
			game_update();
			game_render();
			break;
		}

		// デバッグ文字列の描画
		debug::display(1.0f, 0.4f, 0.6f, 1, 1);

		GameLib::present(1, 0);
	}

	// 現在のシーンに応じた終了処理
	switch (curScene)
	{
	case SCENE_TITLE:
		title_deinit();
		break;

	case SCENE_GAME:
		game_deinit();
		break;
	}

	// オーディオの終了処理
	audio_deinit();

	// ゲームライブラリの終了処理
	GameLib::uninit();

	return 0;
}