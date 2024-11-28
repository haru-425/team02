#include "player.h"

using namespace input;

// �v���C���[�̏�Ԃ��Ǘ�����ϐ�
int player_state; // �v���C���[�̌��݂̏�ԁi�t�F�[�Y�j��\��
float force = 0.0f; // �v���C���[�̍s���Ɋ֘A�����
float angle = 0.0f; // �v���C���[�̊p�x
float click_time = 0; // �N���b�N��ێ��������ԁi���e�`���[�W�Ɏg�p�j
Sprite* sprPLAYER; // �v���C���[�̃X�v���C�g�f�[�^
extern std::vector<ENEMY> enemy_pop; // �Q�[�����̓G���X�g�i�O���Œ�`�j
extern Bomb bomb; // ���e�̊Ǘ��N���X�i�O���Œ�`�j
extern S_SCENE game_state; // �Q�[���̌��݂̏�ԁi�O���Œ�`�j

//--------------------------------------
//  �v���C���[�̏����ݒ�
//--------------------------------------
void player_init()
{
	// �v���C���[�̏�Ԃ�������
	player_state = 0; // ��Ԃ�������
	player.player_time = 0; // �v���C���[�̍s�����Ԃ����Z�b�g
	player.position = VECTOR2(500.0f, 350.0f); // �v���C���[�̏����ʒu
	player.strat_position = player.position; // �����ʒu���L�^
	player.hp = PLAYER_MAX_HP; // �ő�HP��ݒ�
	player.damege_invincible = false; // ���G��Ԃ�����
	player.invincible_time = true; // ���G���Ԃ�������
	player.bomb_reinforce_item = 0; // ���e�����A�C�e���̏�����
}

//--------------------------------------
//  �v���C���[�̏I������
//--------------------------------------
void player_deinit()
{
	safe_delete(sprPLAYER); // �X�v���C�g�f�[�^�����S�ɍ폜
}

//--------------------------------------
//  �v���C���[�̍X�V����
//--------------------------------------
void player_update(PLAYER& player)
{
	switch (player_state)
	{
	case 0: // ���������
		player.position = VECTOR2(500, 350); // �����ʒu���Đݒ�
		++player_state; // ���̏�Ԃ�
		/*fallthrough*/

	case 1: // �p�����[�^�̐ݒ�
		sprPLAYER = sprite_load(L"./Data/Images/Entity/player.png"); // �X�v���C�g��ǂݍ���
		player.color.w = 1; // �v���C���[�̐F�ݒ�i�s�����j
		++player_state; // ���̏�Ԃ�
		/*fallthrough*/

	case 2: // �v���C���̍X�V����
		player.player_time += 0.1f; // �s�����Ԃ��X�V
		player_act(player); // �v���C���[�̍s��������

		// �G�Ƃ̓����蔻�菈��
		for (auto& enemy : enemy_pop)
		{
			if (isColliding(player.position, player.texSize, enemy.position, enemy.texSize, enemy.angle)
				&& player.damege_invincible == false) // ���G�łȂ��ꍇ
			{
				player.hp -= 1; // HP������
				sound::play(XWB_SOUNDS, XWB_SOUND_HIT); // ��e�����Đ�
				player.damege_invincible = true; // ���G��Ԃɐ؂�ւ�
				break;
			}
		}

		for (auto& enemy : enemy_thrown_item)
		{
			if (isColliding(player.position, player.texSize, enemy.position, (enemy.texSize / 2) * (1 / 3.5f), enemy.angle)
				&& player.damege_invincible == false) // ���G�łȂ��ꍇ
			{
				player.hp -= 1; // HP������
				sound::play(XWB_SOUNDS, XWB_SOUND_HIT); // ��e�����Đ�
				player.damege_invincible = true; // ���G��Ԃɐ؂�ւ�
				break;
			}

		}

		if (player.hp <= 0)
		{
			game_state.state = S_SCENE::F_TRANSITION; // �Q�[���I����Ԃֈڍs
		}

		// ���G��Ԃ̏���
		if (player.damege_invincible == true)
		{
			player.invincible_time++;
			if (player.invincible_time % 30 == 0)
			{
				player.color.w = 0.5; // �_�ł̂��߂ɓ����ɂ���
			}
			else if (player.invincible_time % 15 == 0)
			{
				player.color.w = 1; // �_�ł̂��߂ɕs�����ɂ���
			}
			if (player.invincible_time >= PLAYER_MAX_INVINCIBLE_TIME * 60)
			{
				player.color.w = 1;
				player.damege_invincible = false; // ���G���I��
				player.invincible_time = 0;
			}
		}

		// ��ʂɒB�����ꍇ�̏���
		if (player.position.y >= 720)
		{
			player.strat_position.x = player.position.x; // ���Z�b�g�ʒu��ݒ�
			player.strat_position.y = 300;
			returnplayer(); // �v���C���[�����X�|�[��
			player.player_time = 0;
			player.hp -= 2; // �����_���[�W
			player.damege_invincible = true; // ���G��Ԃ�

			sound::play(XWB_SOUNDS, XWB_SOUND_HIT); // ��e�����Đ�
		}

		// �f�o�b�O�����o��
		debug::setString("player.hp:%d", player.hp);
		break;
	}
}

//--------------------------------------
//  �v���C���[�̕`�揈��
//--------------------------------------
void player_render()
{
	// �v���C���[�̈ʒu�ɉ~��`��i�f�o�b�O�p�j
	/*primitive::circle(player.position.x, player.position.y, 10, 1, 1, 0, 1, 0, 1); */

	if (player.position.x >= SCREEN_H - 50 && player.position.y <= 0 + 90)
	{
		primitive::line(player.position.x - 23, player.position.y + 34, player.position.x - 5, player.position.y, 0.5, 0.5, 0.5, 1, 2);
	}
	else if (player.position.x >= SCREEN_H - 50)
	{
		primitive::line(player.position.x - 65, player.position.y - 32, player.position.x - 5, player.position.y, 0.5, 0.5, 0.5, 1, 2);
	}
	else if (player.position.y <= 0 + 80)
	{
		primitive::line(player.position.x + 15, player.position.y + 34, player.position.x - 5, player.position.y, 0.5, 0.5, 0.5, 1, 2);
	}
	else
	{
		primitive::line(player.position.x + 15, player.position.y - 32, player.position.x - 5, player.position.y, 0.5, 0.5, 0.5, 1, 2);
	}

	// ���e�̍ő唚���͈͂�`��
	if (STATE(0) & L_CLICK && click_time && bomb.bomb_state == 0)
	{
		primitive::circle(player.position.x, player.position.y, BOMB_BLAST_MAX_INIT_RANGE + (click_time * 5), 1, 1, 0, 0.0f, 0.2f, 0.4f, 0.2f);
	}

	// �v���C���[�̃X�v���C�g��`��
	sprite_render(sprPLAYER,
		player.position.x, player.position.y,
		0.3f, 0.3f,
		0, 0,
		128, 128,
		64, 64,
		LaunchCalculateRotation(ToRadian(player.angle), force, player.player_time),
		1, 1, 1, player.color.w);

	for (int i = 0; i < 120; i++)
	{
		primitive::circle(edge_reflecting(
			player.position + LaunchCalculatePosition(
				-tracking(
					cursor_position(
					), player.position
				), bomb.bomb_speed, i * 0.5f
			)
		).x,
			edge_reflecting(player.position + LaunchCalculatePosition(-tracking(cursor_position(), player.position), bomb.bomb_speed, i * 0.5f)).y,
			3,
			1, 1,
			0,
			1, 1, 1, 0.5f);
	}

	// �͂̒l���f�o�b�O�o��
	debug::setString("force%f", force);

	float r = HPColor(player.hp).x;
	float g = HPColor(player.hp).y;
	float b = HPColor(player.hp).z;

	//�v���C���[�̗͕̑\��
	if (player.position.x >= SCREEN_H - 50 && player.position.y <= 0 + 90)
	{
		primitive::rect(player.position.x - 69, player.position.y + 33, 42, 9, 0, 0, 0, 0.5, 0.5, 0.5);
		primitive::rect(player.position.x - 65, player.position.y + 35, 35 * player.hp * 0.1, 5, 0, 0, 0, r, g, b);
	}
	else if (player.position.x >= SCREEN_H - 50)
	{
		primitive::rect(player.position.x - 69, player.position.y - 35, 42, 9, 0, 0, 0, 0.5, 0.5, 0.5);
		primitive::rect(player.position.x - 65, player.position.y - 33, 35 * player.hp * 0.1, 5, 0, 0, 0, r, g, b);
	}
	else if (player.position.y <= 0 + 80)
	{
		primitive::rect(player.position.x + 15, player.position.y + 33, 42, 9, 0, 0, 0, 0.5, 0.5, 0.5);
		primitive::rect(player.position.x + 19, player.position.y + 35, 35 * player.hp * 0.1, 5, 0, 0, 0, r, g, b);
	}
	else
	{
		primitive::rect(player.position.x + 15, player.position.y - 35, 42, 9, 0, 0, 0, 0.5, 0.5, 0.5);
		primitive::rect(player.position.x + 19, player.position.y - 33, 35 * player.hp * 0.1, 5, 0, 0, 0, r, g, b);
	}
}



//--------------------------------------
//  �v���C���[�̍s������
//--------------------------------------
void player_act(PLAYER& player)
{
	if (STATE(0) & L_CLICK && click_time <= BOMB_MAX_CHARGE)
	{
		click_time += 0.2; // �N���b�N�Ń`���[�W����
	}

	if (bomb.bomb_state == 0)
	{
		if (TRG_RELEASE(0) & L_CLICK) // �N���b�N�𗣂����Ƃ�
		{
			bomb_throw(click_time, player.bomb_reinforce_item, player.position); // ���e�𓊂���
			click_time = 0; // �`���[�W�����Z�b�g
			bomb.bomb_state = 1; // ���e��Ԃ�i�߂�
		}
	}
	else if (bomb.bomb_state == 2)
	{
		if (TRG(0) & L_CLICK) // �N���b�N�����Ƃ�
		{
			sound::play(XWB_SOUNDS, XWB_SOUND_BOMB); // ���e�����Đ�
			bomb_expansion(player); // ���e��c��������
			bomb.bomb_state = -1; // ��Ԃ����Z�b�g
		}
	}
	else if (TRG_RELEASE(0) & L_CLICK && bomb.bomb_state == -1)
	{
		bomb.bomb_state = 0; // ���e�̏�����Ԃɖ߂�
	}
}

//--------------------------------------
//  �v���C���[�̈ړ�����
//--------------------------------------
void player_movement(PLAYER& player, float angle, float force)
{
	player.position = player.strat_position + LaunchCalculatePosition(angle, force, player.player_time, PLAYER_GRAVITY); // �ړ��v�Z
	player.position = edge_reflecting(player.position); // �ǂł̔��ˏ���
	if (player.position.y < 18)
	{
		::angle = ToRadian(-90);
		::force *= 0.5f;
		player.player_time = 0;
		player.strat_position = { player.position.x, 18 };
		player.position = player.strat_position + LaunchCalculatePosition(angle, force, player.player_time, PLAYER_GRAVITY); // �ړ��v�Z
		//force *= 0.5;
	}
}

VECTOR3 HPColor(int HP)
{
	if (HP < 3)
	{
		return VECTOR3(1.0, 0, 0);
	}
	else if (HP < 5)
	{
		return VECTOR3(1.0, 1.0, 0);
	}
	else
	{
		return VECTOR3(0.5, 1, 0.5);
	}
}