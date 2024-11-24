//------< �C���N���[�h >---------------------------------------------------------

#include "m_scene.h"


//------< �ϐ� >----------------------------------------------------------------
SCENE_TYPE curScene = SCENE_TYPE::NONE;
SCENE_TYPE nextScene = SCENE_TYPE::START;
//FADE fade;


//------< �֐� >----------------------------------------------------------------

static void SceneInitProcessing() {

}
void M_SCENE::SceneChangeProcessing() {
	// �V�[���؂�ւ�����
	if (curScene != nextScene)
	{
		// ���݂̃V�[���ɉ������I������
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

		case SCENE_TYPE::TUTORIAL:
			tutorial_deinit();
			break;
		case SCENE_TYPE::RESULT:
			result_deinit();
		case SCENE_TYPE::SETTING:
			result_deinit();
			break;
		}

		// ���̃V�[���ɉ����������ݒ菈��
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

		case SCENE_TYPE::TUTORIAL:
			tutorial_init();
			break;
		case SCENE_TYPE::RESULT:
			result_init();
			break;
		case SCENE_TYPE::SETTING:
			result_init();
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
	case SCENE_TYPE::START:
		start_update();
		break;

	case SCENE_TYPE::TITLE:
		title_update();
		break;

	case SCENE_TYPE::GAME:
		game_update();
		break;

	case SCENE_TYPE::TUTORIAL:
		tutorial_update();
		break;
	case SCENE_TYPE::RESULT:
		result_update();
		break;
	case SCENE_TYPE::SETTING:
		result_init();
		break;
	}

}
void M_SCENE::SceneRenderProcessing() {
	// ���݂̃V�[���ɉ������X�V�E�`�揈��
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

	case SCENE_TYPE::TUTORIAL:
		tutorial_render();
		break;
	case SCENE_TYPE::RESULT:
		result_render();
		break;
	case SCENE_TYPE::SETTING:
		result_init();
		break;
	}

	debug::display(1.0f, 0.4f, 0.6f, 1, 1);

}

void M_SCENE::SceneEndProcessing() {
	// ���݂̃V�[���ɉ������I������
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

	case SCENE_TYPE::TUTORIAL:
		tutorial_deinit();
		break;
	case SCENE_TYPE::RESULT:
		result_deinit();
		break;
	case SCENE_TYPE::SETTING:
		result_init();
		break;
	}

	// �I�[�f�B�I�̏I������
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