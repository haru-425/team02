//------< �C���N���[�h >---------------------------------------------------------
#include "../GameLib/game_lib.h"
#include "common.h"
#include "audio.h"
#include "m_scene.h"
// namespace
using namespace GameLib;
using namespace input;
//------< �ϐ� >----------------------------------------------------------------

//------------------------------------------------------------------------------
//  WinMain�i�G���g���|�C���g�j
//------------------------------------------------------------------------------
int APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)// �g�p���Ȃ��ϐ��͋L�q���Ȃ�
{
	// �Q�[�����C�u�����̏����ݒ�
	GameLib::init(L"�Q�[���v���O���~���O�T", SCREEN_W, SCREEN_H, FULLSCREEN);

	// �I�[�f�B�I�̏����ݒ�
	audio_init();

	while (GameLib::gameLoop())
	{
		M_SCENE::SceneChangeProcessing();
		M_SCENE::SceneUpdateProcessing();
		M_SCENE::SceneRenderProcessing();
		GameLib::present(1, 0);

		GameLib::init(L"�Q�[���v���O���~���O�T", SCREEN_W, SCREEN_H, FULLSCREEN);
	}
	M_SCENE::SceneEndProcessing;
	GameLib::uninit();

	return 0;
}