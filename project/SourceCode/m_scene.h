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
//------< �֐� >----------------------------------------------------------------

//------< �N���X�E�\���� >-------------------------------------------------------
class M_SCENE
{
public:

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
