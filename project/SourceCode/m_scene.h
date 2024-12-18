#pragma once
//------< インクルード >---------------------------------------------------------
#include "../GameLib/game_lib.h"
#include "scene_game.h"
#include "scene_title.h"
#include "scene_start.h"
#include "scene_tutorial.h"
#include "scene_result.h"
#include "scene_setting.h"
#include "audio.h"
#include "common.h"

// namespace
using namespace GameLib;
using namespace input;


//------< 定数 >----------------------------------------------------------------

enum class SCENE_TYPE
{
	NONE = -1,
	START,
	TITLE,
	GAME,
	TUTORIAL,
	RESULT,
	SETTING,
};


//------< 変数 >----------------------------------------------------------------
extern SCENE_TYPE curScene;
extern SCENE_TYPE nextScene;

//extern FADE fade;

//------< 関数 >----------------------------------------------------------------

//------< クラス・構造体 >-------------------------------------------------------
class M_SCENE
{
public:

	static void SceneInitProcessing();
	static void SceneChangeProcessing();
	static void SceneUpdateProcessing();
	static void SceneRenderProcessing();
	static void SceneEndProcessing();

private:

};
class S_SCENE {
public:
	enum
	{
		INITIALIZE,
		B_TRANSIATON,
		PARAMETER,
		NORMAL,
		F_TRANSITION,
	};
	int state;

};
class TRANSITION {
public:
	VECTOR2 POS = { 0,0 };
	VECTOR2 SCALE = { 1, 1 };
	VECTOR2 texPOS;
	VECTOR2 WH;
	VECTOR2 PIVOT;
	float ANGLE;
	VECTOR4 COLOR;

};
class FADE :public TRANSITION {
public:

	static float alpha;

};