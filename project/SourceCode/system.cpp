//------< �C���N���[�h >---------------------------------------------------------
#include "../GameLib/game_lib.h"
#include "m_scene.h"
#include "audio.h"
#include "common.h"
#include "system.h"

//A��B����������
float tracking(VECTOR2 target, VECTOR2 tracking_person) {
	VECTOR2 subVector;
	float angle;

	// �^�[�Q�b�g�ƒǐՎ҂̍��W�������v�Z
	subVector.x = target.x - tracking_person.x;
	subVector.y = target.y - tracking_person.y;

	// ��������p�x���v�Z
	angle = (float)atan2(subVector.y, subVector.x);
	return angle;
}
//�P�ʃx�N�g����Ԃ�
VECTOR2 unit_vectorization(VECTOR2 vec) {
	float length = std::sqrtf(powf(vec.x, 2) + powf(vec.y, 2));
	vec.x /= length;
	vec.y /= length;
	return vec;
}
//�����Ɗp�x���ƍ��̎��Ԃ�n���Ƃ��̎��̈ʒu��Ԃ�
VECTOR2 launch_alculate_position(double initialSpeed, double angle, double time) {
	VECTOR2 position;
	time /= 10;//�����p10�͉�
	double angleRad = ToRadian(angle); // �p�x�����W�A���ɕϊ�
	position.x = initialSpeed * cos(angleRad) * time;
	position.y = initialSpeed * sin(angleRad) * time - 0.5 * GRAVITY * time * time;
	return position;
}