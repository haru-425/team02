//------< インクルード >---------------------------------------------------------
#include "../GameLib/game_lib.h"
#include "m_scene.h"
#include "audio.h"
#include "common.h"
// namespace
using namespace GameLib;
using namespace input;


//------< 変数 >----------------------------------------------------------------
SCENE_TYPE curScene = SCENE_TYPE::NONE;
SCENE_TYPE nextScene = SCENE_TYPE::START;
//FADE fade;


//------< 関数 >----------------------------------------------------------------

static void SceneInitProcessing() {

}
void M_SCENE::SceneChangeProcessing() {
	// シーン切り替え処理
	if (curScene != nextScene)
	{
		// 現在のシーンに応じた終了処理
		switch (curScene)
		{
		case SCENE_TYPE::START:
			start_deinit();
			break;

		case SCENE_TYPE::TITLE:
			title_deinit();
			break;

		case SCENE_TYPE::GAME:
			game_deinit();
			break;
		}

		// 次のシーンに応じた初期設定処理
		switch (nextScene)
		{
		case SCENE_TYPE::START:
			start_init();
			break;

		case SCENE_TYPE::TITLE:
			title_init();
			break;

		case SCENE_TYPE::GAME:
			game_init();
			break;
		}

		curScene = nextScene;
	}
}
void M_SCENE::SceneUpdateProcessing() {

	// 入力を更新する
	input::update();
	music::update();
	// 現在のシーンに応じた更新・描画処理
	switch (curScene)
	{
	case SCENE_TYPE::START:
		start_update();
		break;

	case SCENE_TYPE::TITLE:
		title_update();
		break;

	case SCENE_TYPE::GAME:
		game_update();
		break;
	}

}
void M_SCENE::SceneRenderProcessing() {
	// 現在のシーンに応じた更新・描画処理
	switch (curScene)
	{
	case SCENE_TYPE::START:
		start_render();
		break;

	case SCENE_TYPE::TITLE:
		title_render();
		break;

	case SCENE_TYPE::GAME:
		game_render();
		break;
	}

	debug::display(1.0f, 0.4f, 0.6f, 1, 1);

}

void M_SCENE::SceneEndProcessing() {
	// 現在のシーンに応じた終了処理
	switch (curScene)
	{
	case SCENE_TYPE::START:
		start_deinit();
		break;

	case SCENE_TYPE::TITLE:
		title_deinit();
		break;

	case SCENE_TYPE::GAME:
		game_deinit();
		break;
	}

	// オーディオの終了処理
	audio_deinit();
}



//FADE::FADE() {
//	POS = { SCREEN_W / 2.0f, SCREEN_H / 2.0f };
//	SCALE = { 1, 1 };
//	texPOS = { 0, 0 };
//	WH = { 1280, 720 };
//	PIVOT = { 1280 / 2.0f, 720 / 2.0f };
//	ANGLE = 0;
//	COLOR = { 0, 0, 0, 1 };
//	sprFADE = sprite_load(L"./Data/Images/transitions/fade.png");
//}