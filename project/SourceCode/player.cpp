#include "player.h"
#include "../GameLib/game_lib.h"
#include "../GameLib/obj2d_data.h"
#include "common.h"
#include "audio.h"
#include "m_scene.h"
using namespace input;

// �v���C���[�̏�Ԃ��Ǘ�����ϐ�
int player_state;
class PLAYER {
public:
	float angle;
	float speed;
	VECTOR2 position;
	VECTOR2 scale;
	VECTOR2 texPos;
	VECTOR2 texSize;
	VECTOR2 pivot;
	VECTOR4 color;



};

//--------------------------------------
//  �v���C���[�̏����ݒ�
//--------------------------------------
void player_init()
{
	// �v���C���[�̏�Ԃ�������
	player_state = 0;
}

//--------------------------------------
//  �v���C���[�̏I������
//--------------------------------------
void player_deinit()
{
}

//--------------------------------------
//  �v���C���[�̍X�V����
//--------------------------------------
void player_update()
{
	switch (player_state)
	{
	case 0:
		//////// �����ݒ� ////////

		// ���̏�ԂɑJ��
		++player_state;
		/*fallthrough*/

	case 1:
		//////// �p�����[�^�̐ݒ� ////////

		// ���̏�ԂɑJ��
		++player_state;
		/*fallthrough*/

	case 2:

		player_act();
		break;
	}
}

//--------------------------------------
//  �v���C���[�̕`�揈��
//--------------------------------------
void player_render()
{

}

//--------------------------------------
//  �v���C���[�̍s������
//--------------------------------------
void player_act()
{

}
