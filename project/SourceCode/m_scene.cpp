//------< �C���N���[�h >---------------------------------------------------------
#include "../GameLib/game_lib.h"
#include "m_scene.h"
#include "audio.h"
// namespace
using namespace GameLib;
using namespace input;


//------< �ϐ� >----------------------------------------------------------------
SCENE_TYPE curScene = SCENE_TYPE::NONE;
SCENE_TYPE nextScene = SCENE_TYPE::TITLE;


//------< �֐� >----------------------------------------------------------------
void M_SCENE::SceneChangeProcessing() {
	// �V�[���؂�ւ�����
	if (curScene != nextScene)
	{
		// ���݂̃V�[���ɉ������I������
		switch (curScene)
		{
		case SCENE_TYPE::TITLE:
			title_deinit();
			break;

		case SCENE_TYPE::GAME:
			game_deinit();
			break;
		}

		// ���̃V�[���ɉ����������ݒ菈��
		switch (nextScene)
		{
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

	// ���͂��X�V����
	input::update();
	music::update();
	// ���݂̃V�[���ɉ������X�V�E�`�揈��
	switch (curScene)
	{
	case SCENE_TYPE::TITLE:
		title_update();
		break;

	case SCENE_TYPE::GAME:
		game_update();
		break;
	}

}
void M_SCENE::SceneRenderProcessing() {
	// ���݂̃V�[���ɉ������X�V�E�`�揈��
	switch (curScene)
	{
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
	// ���݂̃V�[���ɉ������I������
	switch (curScene)
	{
	case SCENE_TYPE::TITLE:
		title_deinit();
		break;

	case SCENE_TYPE::GAME:
		game_deinit();
		break;
	}

	// �I�[�f�B�I�̏I������
	audio_deinit();
}