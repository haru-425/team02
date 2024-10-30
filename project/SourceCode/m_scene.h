#pragma once
//------< �C���N���[�h >---------------------------------------------------------
#include "scene_game.h"
#include "scene_title.h"
//------< �萔 >----------------------------------------------------------------

enum class SCENE_TYPE
{
	NONE = -1,
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
		B_TRANSIATON,
		INITIALIZE,
		PARAMETER,
		NORMAL,
		F_TRANSITION,
	};
	int state;

};
class TRANSITION {
public:
	VECTOR2 POS;
	VECTOR2 SCALE;
	VECTOR2 texPOS;
	VECTOR2 WH;
	VECTOR2 PIVOT;
	float ANGLE;
	VECTOR4 COLOR;

};
//class FADE :public TRANSITION {
//public:
//
//	Sprite* sprFADE;
//	FADE();
//
//};