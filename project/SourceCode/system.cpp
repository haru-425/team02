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

// �~�Ɖ~�̓����蔻��֐�
bool isCircleColliding(const VECTOR2 a_position, float a_radius, VECTOR2 b_position, float b_radius) {
	// ���S�Ԃ̋������v�Z
	float dx = b_position.x - a_position.x;
	float dy = b_position.y - a_position.y;
	float distance = std::sqrt(dx * dx + dy * dy);

	// ���a�̘a�Ƌ������r
	return distance <= (a_radius + b_radius);
}


//��]�����`�Ƌ�`�̓����蔻��


struct Rect {
	VECTOR2 center;
	VECTOR2 size;
};

struct RotatedRect {
	VECTOR2 center;
	VECTOR2 size;
	float angle;
};

bool intersectRectRotatedRect(VECTOR2 _center, VECTOR2  _size, VECTOR2 rot_center, VECTOR2  rot_size, float angle) {

	const Rect& rect = { _center, _size };
	const RotatedRect& rotatedRect = { rot_center, rot_size, angle };
	// ��]�����`�̒��_���擾����
	VECTOR2 vertices[4];
	vertices[0] = { rotatedRect.center.x - rotatedRect.size.x / 2, rotatedRect.center.y - rotatedRect.size.y / 2 };
	vertices[1] = { rotatedRect.center.x + rotatedRect.size.x / 2, rotatedRect.center.y - rotatedRect.size.y / 2 };
	vertices[2] = { rotatedRect.center.x + rotatedRect.size.x / 2, rotatedRect.center.y + rotatedRect.size.y / 2 };
	vertices[3] = { rotatedRect.center.x - rotatedRect.size.x / 2, rotatedRect.center.y + rotatedRect.size.y / 2 };

	// ��]�s����v�Z����
	float cosAngle = std::cos(rotatedRect.angle);
	float sinAngle = std::sin(rotatedRect.angle);

	// ��]�����`�̒��_��ϊ�����
	for (int i = 0; i < 4; i++) {
		float x = vertices[i].x - rotatedRect.center.x;
		float y = vertices[i].y - rotatedRect.center.y;
		vertices[i].x = x * cosAngle - y * sinAngle + rotatedRect.center.x;
		vertices[i].y = x * sinAngle + y * cosAngle + rotatedRect.center.y;
	}

	// �����蔻������s����
	for (int i = 0; i < 4; i++) {
		if (rect.center.x - rect.size.x / 2 <= vertices[i].x && vertices[i].x <= rect.center.x + rect.size.x / 2 &&
			rect.center.y - rect.size.y / 2 <= vertices[i].y && vertices[i].y <= rect.center.y + rect.size.y / 2) {
			return true;
		}
	}

	return false;
}


//��]�����`�Ɖ~�̓����蔻��

bool intersectRectCircle(VECTOR2 rec_center, VECTOR2 size, float angle, VECTOR2 cir_center, float radius) {
	// ��]�s����v�Z����
	float cosAngle = std::cos(angle);
	float sinAngle = std::sin(angle);

	// ��`�̒��_���擾����
	VECTOR2 vertices[4];
	vertices[0] = { rec_center.x - size.x / 2, rec_center.y - size.y / 2 };
	vertices[1] = { rec_center.x + size.x / 2, rec_center.y - size.y / 2 };
	vertices[2] = { rec_center.x + size.x / 2, rec_center.y + size.y / 2 };
	vertices[3] = { rec_center.x - size.x / 2, rec_center.y + size.y / 2 };

	// ��]�s����g�p���Ē��_��ϊ�����
	for (int i = 0; i < 4; i++) {
		float x = vertices[i].x - rec_center.x;
		float y = vertices[i].y - rec_center.y;
		vertices[i].x = x * cosAngle - y * sinAngle + rec_center.x;
		vertices[i].y = x * sinAngle + y * cosAngle + rec_center.y;
	}

	// �����蔻������s����
	for (int i = 0; i < 4; i++) {
		VECTOR2 v = { cir_center.x - vertices[i].x, cir_center.y - vertices[i].y };
		float distance = std::sqrt(v.x * v.x + v.y * v.y);
		if (distance <= radius) {
			return true;
		}
	}

	return false;
}