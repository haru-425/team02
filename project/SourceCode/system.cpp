//------< �C���N���[�h >---------------------------------------------------------
#include "../GameLib/game_lib.h"
#include "m_scene.h"
#include "audio.h"
#include "common.h"
#include "system.h"


VECTOR2 magnetic_force = { 0,0 };

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
//VECTOR2 launch_alculate_position(double initialSpeed, double angle, double time) {
//	VECTOR2 position;
//	//time /= 100;//�����p10�͉�
//	double angleRad = ToRadian(angle); // �p�x�����W�A���ɕϊ�
//	position.x = initialSpeed * cos(angleRad) * time;
//	position.y = initialSpeed * sin(angleRad) * time - 0.5 * GRAVITY * time * time;
//	return position;
//}

VECTOR2 LaunchCalculatePosition(float angle, float force, float time) {
	// �������x���v�Z
	float v0 = force;
	float vx = v0 * cos(angle);
	float vy = v0 * sin(angle);

	// �d�͉����x���`
	float g = 9.8f;

	// n�b��̈ʒu���v�Z
	float x = vx * time;

	float y = vy * time - 0.5f * g * time * time;
	y *= -1;
	// �ʒu��Ԃ�
	return VECTOR2(x, y);
}
VECTOR2 LaunchCalculatePosition(float angle, float force, float time, float gravity)
{
	// �������x���v�Z
	float v0 = force;
	float vx = v0 * cos(angle);
	float vy = v0 * sin(angle);

	// �d�͉����x���`
	float g = gravity;

	// n�b��̈ʒu���v�Z
	float x = vx * time;

	float y = vy * time - 0.5f * g * time * time;
	y *= -1;

	// �ʒu��Ԃ�
	return VECTOR2(x, y);
}

VECTOR2 magnetic_force_suction(VECTOR2 target_BasePos, VECTOR2 magnetic_force) {
	VECTOR2 Vec = target_BasePos;
	if (Vec.x <= 0) Vec.x += magnetic_force.x / 2.0f;

	if (Vec.x >= SCREEN_H)Vec.x -= magnetic_force.x / 2.0f;

	Vec.x += magnetic_force.x;
	Vec.y += magnetic_force.y;

	return Vec;
}

VECTOR2 edge_reflecting(VECTOR2 pos) {
	// ��ʊO�ɏo���ꍇ�̏���
	if (pos.x < 0)  pos.x *= -1;
	if (pos.x > SCREEN_H) pos.x = SCREEN_H - (pos.x - SCREEN_H);
	//	if (pos.y <= 0) pos.y *= -1;
	return pos;

}
VECTOR2 cursor_position() {

	POINT point;
	//�}�E�X�J�[�\���̌��݈ʒu���擾
	GetCursorPos(&point);

	// �X�N���[�����W���N���C�A���g���W�ɕϊ�
	ScreenToClient(window::getHwnd(), &point);

	VECTOR2 Point = { (float)point.x, (float)point.y };
	return Point;
}
// ��`�|���S���`��
void draw_fan_triangle_quad(VECTOR2 center, float radius, float startAngle, float endAngle, int polygon, VECTOR4 color)
{
	float angleStep = (endAngle - startAngle) / polygon;
	for (int i = 0; i < polygon; i++) {
		float angle1 = ToRadian(startAngle + i * angleStep);
		float angle2 = ToRadian(startAngle + (i + 1) * angleStep);
		VECTOR2 p1 = { center.x + radius * sinf(angle1), center.y - radius * cosf(angle1) };
		VECTOR2 p2 = { center.x + radius * sinf(angle2), center.y - radius * cosf(angle2) };
		VECTOR2 vertex[4] = {
			{center.x,center.y},
			{center.x,center.y},
			{p1.x,p1.y},
			{p2.x,p2.y}
		};
		primitive::quad(vertex, color, true);
	}
}
