#pragma once
//------< �C���N���[�h >---------------------------------------------------------
#include "scene_game.h"
#include "scene_title.h"
#include "scene_start.h"
//------< �萔 >----------------------------------------------------------------

enum class SCENE_TYPE
{
	NONE = -1,
	START,
	TITLE,
	GAME,
};


//------< �ϐ� >----------------------------------------------------------------
extern SCENE_TYPE curScene;
extern SCENE_TYPE nextScene;

//extern FADE fade;

//------< �֐� >----------------------------------------------------------------

//------< �N���X�E�\���� >-------------------------------------------------------
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