#pragma once
#include "../GameLib/game_lib.h"
#include "audio.h"
#include "common.h"
#include <cmath>
#include <vector>

using namespace std;

extern VECTOR2 magnetic_force;

//----------------------------
// �w�肵���^�[�Q�b�g���������ۂ̊p�x��Ԃ��֐�
// target: �Ǐ]���ׂ��^�[�Q�b�g�̍��W
// tracking_person: �p�x���v�Z����Ώۂ̍��W
//----------------------------
float tracking(VECTOR2 target, VECTOR2 tracking_person);

//----------------------------
// �x�N�g����P�ʃx�N�g��������֐�
// vec: �P�ʃx�N�g��������Ώۂ̃x�N�g��
// �߂�l: ���K�����ꂽ�P�ʃx�N�g��
//----------------------------
VECTOR2 unit_vectorization(VECTOR2 vec);

//----------------------------
// ���˕��̏����A�p�x�A���Ԃ���Ɍ��݂̈ʒu���v�Z����֐�
// angle: ���ˊp�x (���W�A��)
// force: ���ˑ��x
// time: �o�ߎ���
// �߂�l: ���݂̈ʒu���W
//----------------------------
VECTOR2 LaunchCalculatePosition(float angle, float force, float time);

//----------------------------
// ���˕��̏����A�p�x�A���ԁA�d�͂���Ɍ��݂̈ʒu���v�Z����֐�
// angle: ���ˊp�x (���W�A��)
// force: ���ˑ��x
// time: �o�ߎ���
// gravity: �d�͉����x
// �߂�l: ���݂̈ʒu���W
//----------------------------
VECTOR2 LaunchCalculatePosition(float angle, float force, float time, float gravity);

//----------------------------
// ���˕��̏����A�p�x�A���Ԃ���Ɍ��݂̉�]�p�x���v�Z����֐�
// angle: ���ˊp�x (���W�A��)
// force: ���ˑ��x
// time: �o�ߎ���
// �߂�l: ���݂̉�]�p�x
//----------------------------
float LaunchCalculateRotation(float angle, float force, float time);

//----------------------------
// ���˕��̏����A�p�x�A���ԁA�d�͂���Ɍ��݂̉�]�p�x���v�Z����֐�
// angle: ���ˊp�x (���W�A��)
// force: ���ˑ��x
// time: �o�ߎ���
// gravity: �d�͉����x
// �߂�l: ���݂̉�]�p�x
//----------------------------
float LaunchCalculateRotation(float angle, float force, float time, float gravity);

//----------------------------
// ���͂ɂ���ă^�[�Q�b�g�̍��W���z������֐�
// target_BasePos: �Ώە��̌��ݍ��W
// magnetic_force: ���͂̋�����\���x�N�g��
// �߂�l: ���͂̉e�����󂯂��V�������W
//----------------------------
VECTOR2 magnetic_force_suction(VECTOR2 target_BasePos, VECTOR2 magnetic_force);

//----------------------------
// ���݂̃J�[�\���ʒu���擾����֐�
// �߂�l: �J�[�\���̍��W
//----------------------------
VECTOR2 cursor_position();

//----------------------------
// �I�u�W�F�N�g����ʒ[�ɒB�����Ƃ��̔��ˏ������s���֐�
// pos: �I�u�W�F�N�g�̌��݈ʒu
// �߂�l: ���ˌ�̈ʒu
//----------------------------
VECTOR2 edge_reflecting(VECTOR2 pos);

//----------------------------
// ��]�����`�Ɖ~�̓����蔻����s���֐�
// rec_center: ��`�̒��S���W
// size: ��`�̕��ƍ���
// angle: ��`�̉�]�p�x (���W�A��)
// cir_center: �~�̒��S���W
// radius: �~�̔��a
// �߂�l: �����蔻�肪���邩�ǂ��� (true/false)
//----------------------------
bool intersectRectCircle(VECTOR2 rec_center, VECTOR2 size, float angle, VECTOR2 cir_center, float radius);

//----------------------------
// ��]�����`�Ƌ�`�̓����蔻����s���֐�
// _center: ��]���Ă��Ȃ���`�̒��S���W
// _size: ��]���Ă��Ȃ���`�̕��ƍ���
// rot_center: ��]�����`�̒��S���W
// rot_size: ��]�����`�̕��ƍ���
// angle: ��]�����`�̉�]�p�x (���W�A��)
// �߂�l: �����蔻�肪���邩�ǂ��� (true/false)
//----------------------------
bool isColliding(VECTOR2 _center, VECTOR2 _size, VECTOR2 rot_center, VECTOR2 rot_size, float angle);

//--------------------------------------------------------------
// ��`�̃|���S����`�悷��֐�
// center: ��`�̒��S���W
// radius: ��`�̔��a
// startAngle: ��`�̊J�n�p�x (�x)
// endAngle: ��`�̏I���p�x (�x)
// polygon: �~���\������|���S���̕�����
// color: ��`�̐F (r, g, b, a)
//--------------------------------------------------------------
void draw_fan_triangle_quad(VECTOR2 center, float radius, float startAngle, float endAngle, int polygon, VECTOR4 color);

//----------------------------
// �~�Ɖ~�̓����蔻����s���֐�
// a_position: �~A�̒��S���W
// a_radius: �~A�̔��a
// b_position: �~B�̒��S���W
// b_radius: �~B�̔��a
// �߂�l: �����蔻�肪���邩�ǂ��� (true/false)
//----------------------------
bool isCircleColliding(const VECTOR2 a_position, float a_radius, VECTOR2 b_position, float b_radius);
