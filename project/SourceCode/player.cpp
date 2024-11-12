#include "player.h"
#include "../GameLib/game_lib.h"
#include "../GameLib/obj2d_data.h"
#include "common.h"
#include "audio.h"
#include "m_scene.h"
#include "bomb.h"
#include "system.h"
using namespace input;

// �v���C���[�̏�Ԃ��Ǘ�����ϐ�
int player_state;

PLAYER player;
extern Bomb bomb;
//--------------------------------------
//  �v���C���[�̏����ݒ�
//--------------------------------------
void player_init()
{
	// �v���C���[�̏�Ԃ�������
	player_state = 0;
	player.player_time = 0;
	player.position = VECTOR2(500.0f, 350.0f);
	player.strat_position = player.position;
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

		player.position = VECTOR2(500, 350);
		// ���̏�ԂɑJ��
		++player_state;
		/*fallthrough*/

	case 1:
		//////// �p�����[�^�̐ݒ� ////////

		// ���̏�ԂɑJ��
		++player_state;
		/*fallthrough*/

	case 2:
		player.player_time+=0.1f;
		player_act();
		if (TRG(0)& L_CLICK)
		{
			bomb_throw();
		}
		debug::setString("player.position.x:%f", player.position.x);
		break;
	}
}

//--------------------------------------
//  �v���C���[�̕`�揈��
//--------------------------------------
void player_render()
{

	primitive::circle(player.position.x, player.position.y, 10, 1, 1, 0, 1, 0, 1);
}

//--------------------------------------
//  �v���C���[�̍s������
//--------------------------------------
void player_act()
{

}

//--------------------------------------
//  �v���C���[�̍s������
//--------------------------------------
void player_movement(float angle, float force)
{
	player.position = player.strat_position + LaunchCalculatePosition(angle, force, player.player_time, PLAYER_GRAVITY);
}