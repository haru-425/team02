#include "bomb.h"

Bomb bomb; // ���e�Ǘ��p�̃O���[�o���ϐ�
extern PLAYER player; // �v���C���[���i�O���Œ�`�j
POINT screenPoint; // �X�N���[�����W�p�̕ϐ�
extern float force; // �����́i�O���Œ�`�j
extern float angle; // �����p�x�i�O���Œ�`�j
float flepX = 0.0f; // ���e�ƃv���C���[�Ԃ�X������
float flepY = 0.0f; // ���e�ƃv���C���[�Ԃ�Y������
std::vector<Bomb_range> range_Box; // �����͈͂̃��X�g
float blast_max_range = 0; // �����̍ő�͈�
extern int tutorial_progress; // �`���[�g���A���i�s�󋵁i�O���Œ�`�j
Sprite* sprBOMB; // ���e�̃X�v���C�g�f�[�^

//--------------------------------------
// ���e�̏�����
//--------------------------------------
void bomb_init()
{
    bomb.bomb_state = 0; // ���e��Ԃ�������
    bomb.start_bomb_position = player.position; // ���e�̊J�n�ʒu���v���C���[�ʒu�ɐݒ�
    bomb.bomb_position.x = -200; // ���e�̏����ʒu�i��\���j
    bomb.bomb_position.y = -200; // ����
    bomb.bomb_speed = 50.0f; // �������x��ݒ�
    bomb.bomb_angle = 0.0f; // �����p�x��ݒ�
    bomb.bom_time = 0; // ���e�̌o�ߎ��Ԃ�������
    bomb.bomb_blast = 0.0f; // �����͈̔͂�������
}

//--------------------------------------
// ���e�̏I������
//--------------------------------------
void bomb_deinit()
{
    bomb.bomb_state = 0; // ��Ԃ����Z�b�g
    bomb.bomb_position.x = -100; // ��\����Ԃɖ߂�
    bomb.bomb_position.y = -100;
    bomb.bomb_speed = 50.0f; // ���x��������
    bomb.bomb_angle = 0.0f; // �p�x��������
    bomb.bom_time = 0; // ���Ԃ�������
    safe_delete(sprBOMB); // �X�v���C�g�f�[�^���폜
}

//--------------------------------------
// ���e�𓊂��鏈��
//--------------------------------------
void bomb_throw(float muster_up, int bomb_up, VECTOR2 position)
{
    bomb.start_bomb_position = position; // ���e�̊J�n�ʒu��ݒ�

    VECTOR2 Point = cursor_position(); // �}�E�X�J�[�\���ʒu���擾
    bomb.bomb_angle = tracking(Point, position); // �v���C���[�ʒu����J�[�\���ʒu�ւ̊p�x���v�Z

    // �����̍ő�͈͂��v�Z
    blast_max_range = BOMB_BLAST_MAX_INIT_RANGE + (muster_up * 5) + (float)(bomb_up * 8);

    bomb.bomb_state++; // ��Ԃ��X�V�i�����鏀�������j
}

//--------------------------------------
// ���e�̔����ɂ�鏈��
//--------------------------------------
void bomb_expansion(PLAYER& player)
{
    // �v���C���[�Ɣ��e�Ԃ̋������v�Z
    flepX = player.position.x - bomb.bomb_position.x;
    flepY = player.position.y - bomb.bomb_position.y;

    // �����͈͓��Ƀv���C���[������ꍇ
    if (blast_max_range - sqrtf(flepX * flepX + flepY * flepY) > 0)
    {
        player.player_time = 0; // �v���C���[�̍s�����Ԃ����Z�b�g
        player.strat_position = player.position; // ���݈ʒu��V���ȃX�^�[�g�ʒu��
        force = (blast_max_range - sqrtf(flepX * flepX + flepY * flepY)) * BOMB_BLAST_STRANGE; // �����ɂ��͂��v�Z
        angle = -tracking(player.position, bomb.bomb_position); // ���������̊p�x���v�Z
    }

    range_Box.push_back(bomb.bomb_position); // �����͈͂����X�g�ɒǉ�
    bomb_deinit(); // ���e���I����Ԃɂ���
}

//--------------------------------------
// ���e�̍X�V����
//--------------------------------------
void bomb_update(PLAYER& player)
{
    debug::setString("bomb_blast_max_range:%f", blast_max_range); // �f�o�b�O�����o��
    debug::setString("bomb_state:%d", bomb.bomb_state);

    switch (bomb.bomb_state)
    {
    case 1: // ���e��������ꂽ����
        sprBOMB = sprite_load(L"./Data/Images/Bomb/bomb.png"); // �X�v���C�g��ǂݍ���
        bomb.bom_time = 0.0f; // ���Ԃ����Z�b�g
        bomb.bomb_state++; // ��Ԃ��X�V
        /*fallthrough*/

    case 2: // ���e���ړ���
        bomb.bom_time += 0.1f; // �o�ߎ��Ԃ��X�V
        bomb.bomb_position = bomb.start_bomb_position + LaunchCalculatePosition(-bomb.bomb_angle, bomb.bomb_speed, bomb.bom_time); // �V�����ʒu���v�Z

        bomb.bomb_position = edge_reflecting(bomb.bomb_position); // �ǂɓ��������甽��

        if (bomb.bomb_position.y >= SCREEN_H) // ��ʂɓ��B�����ꍇ
        {
            bomb_deinit(); // ���e�����Z�b�g
        }

    default:
        // �����͈͂��g��
        for (auto& renge : range_Box)
        {
            renge.bomb_range_expansion();
        }

        // �͈͂��ő�ɒB�����������폜
        auto it = std::remove_if(range_Box.begin(), range_Box.end(),
            [](const Bomb_range& renge) { return renge.bomb_blast_range >= renge.bomb_blast_max_range; });
        range_Box.erase(it, range_Box.end());

        // �`���[�g���A�����łȂ��ꍇ�A�v���C���[���ړ�
        if (tutorial_progress != 1)
        {
            player_movement(player, angle, force + BOMB_ADJUSTMENT);
        }
        return; // �����I��
    }
}

//--------------------------------------
// ���e�̕`�揈��
//--------------------------------------
void bomb_render()
{
    // �����͈͂�`��
    for (auto& range : range_Box) {
        primitive::circle(range.judg_position.x, range.judg_position.y, range.bomb_blast_max_range, range.bomb_blast_range / range.bomb_blast_max_range, range.bomb_blast_range / range.bomb_blast_max_range, 0, 1, 0, 0, 0.2f);
    }

    // ���e�̃X�v���C�g��`��
    primitive::circle(bomb.bomb_position.x, bomb.bomb_position.y, 10, 1, 1);
    sprite_render(sprBOMB,
        bomb.bomb_position.x, bomb.bomb_position.y,
        40.0f / 128.0f, 40.0f / 128.0f,
        0, 0,
        128, 128,
        64, 64,
        LaunchCalculateRotation(ToRadian(bomb.bomb_angle), bomb.bomb_speed, bomb.bom_time)
    );
}

//--------------------------------------
// �v���C���[�̃��Z�b�g
//--------------------------------------
void returnplayer()
{
    force = 0; // �͂����Z�b�g
    angle = 0; // �p�x�����Z�b�g
}


Bomb_range::Bomb_range(VECTOR2 position) :judg_position(position)
{
	bomb_blast_range = 0;
	this->bomb_blast_max_range = blast_max_range;
	player_launch = false;
}

Bomb_range::~Bomb_range()
{
}

void Bomb_range::bomb_range_expansion()
{
	bomb_blast_range += BOMB_BLAST_R_INC;
	/*if (sqrtf(flepX * flepX + flepY * flepY) - bomb_blast_range <= 0 && player_launch == false)
	{
		player.player_time = 0;
		player.strat_position = player.position;
		force = (BOMB_BLAST_MAX_RANGE - sqrtf(flepX * flepX + flepY * flepY)) * BOMB_BLAST_STRANGE;
		angle = tracking(player.position, bomb.start_bomb_position);
		player_launch = true;
	}
	if (bomb_blast_range >= BOMB_BLAST_MAX_RANGE)
	{
		player_launch = false;
	}*/
	enemy_kill(bomb_blast_range, judg_position);

}
