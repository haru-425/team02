//------< �C���N���[�h >---------------------------------------------------------
// GameLib�Q�[�����C�u�����̃w�b�_�t�@�C�����C���N���[�h
#include "../GameLib/game_lib.h"
// ���ʃw�b�_�t�@�C�����C���N���[�h
#include "common.h"
// �I�[�f�B�I�֘A�̃w�b�_�t�@�C�����C���N���[�h
#include "audio.h"
// �V�[���Ǘ��֘A�̃w�b�_�t�@�C�����C���N���[�h
#include "m_scene.h"

// namespace���g�p����
using namespace GameLib;
using namespace input;

//------< �ϐ� >----------------------------------------------------------------

//------------------------------------------------------------------------------
//   WinMain�i�G���g���|�C���g�j
//------------------------------------------------------------------------------
// Windows�A�v���P�[�V�����̃G���g���|�C���g
int APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)// �g�p���Ȃ��ϐ��͋L�q���Ȃ�
{
	// �Q�[�����C�u�����̏����ݒ�
	// �^�C�g���A��ʕ��A��ʍ����A�t���X�N���[�����[�h���w��
	GameLib::init(L"�Q�[���v���O���~���O�T", SCREEN_W, SCREEN_H, FULLSCREEN);

	// �I�[�f�B�I�̏����ݒ�
	audio_init();

	// �Q�[�����[�v
	while (GameLib::gameLoop())
	{
		// �V�[���̕ύX����

		M_SCENE::SceneChangeProcessing();
		// �V�[���̍X�V����
		M_SCENE::SceneUpdateProcessing();
		// �V�[���̕`�揈��
		M_SCENE::SceneRenderProcessing();
		// �t���[����\��
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
	// �V�[���̏I������
	M_SCENE::SceneEndProcessing; // <- �����ɃZ�~�R�������K�v
	// �Q�[�����C�u�����̏I������
	GameLib::uninit();

	// ����I��
	return 0;
}